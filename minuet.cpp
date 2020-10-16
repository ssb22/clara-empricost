/*
   Clara Empricost - Condition List Action Rejection
     Algorithm for the Evaluation of Music at Pseudo-Random
     Idea Construction Stage

   (C) 1996-2001 Silas S. Brown http://ssb22.user.srcf.net
    This code is no longer being maintained by the author.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
    
        http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#include "mappings.h"
#ifndef TSR_VERSION
#include "minuet.h"
//#define TESTING
Minuet::Minuet(NumBeats beatsPerBar,NumBeats anacrusis,KeyRef key,int barsInPhrase,Boolean rondoEpisode,ModulateStatus canModulate,Boolean willAddChrom) {
	isRondoEpisode=rondoEpisode;
#ifndef TESTING
	theMainMelody=new Melody(beatsPerBar,anacrusis,key,beatsPerBar*(barsInPhrase-1)+anacrusis+1+2*(beatsPerBar>2),1,1,1,canModulate,TRUE,NULL,willAddChrom);
	theOpenEnd=new Melody(beatsPerBar,anacrusis,key,beatsPerBar*(barsInPhrase-1)+anacrusis+1,1,1,0,canModulate,TRUE,NULL,willAddChrom);
	theClosedEnd=new Melody(beatsPerBar,anacrusis,key,beatsPerBar*(barsInPhrase-1)+anacrusis+1,1,0,0,canModulate,TRUE,NULL,willAddChrom);
#endif
	if (isRondoEpisode==FALSE) theMiddleSection=new Melody(beatsPerBar,anacrusis,key,beatsPerBar*(barsInPhrase*2-1)+anacrusis+1,2,1,0,MS_END,TRUE,NULL,willAddChrom); else theMiddleSection=NULL;
}

Minuet::~Minuet() {
	if (theMiddleSection) delete theMiddleSection;
#ifndef TESTING
	delete theClosedEnd; delete theOpenEnd; delete theMainMelody;
#endif
}

#ifndef SETUP_ONLY_VERSION
void Minuet::outputToMwr(Mwr &mwr,Part part,int needToInit,int shortenEpisode,const Key* transposeTo,Boolean addChromaticisms) {
	mwr.setPart(part);
#ifndef TESTING
	if (isRondoEpisode==FALSE || !shortenEpisode) {
		theMainMelody->outputToMwr(mwr,needToInit,0,transposeTo,addChromaticisms); theOpenEnd->outputToMwr(mwr,0,0,transposeTo,addChromaticisms);
	} if (isRondoEpisode==FALSE) {
		theMainMelody->outputToMwr(mwr,0,0,transposeTo,addChromaticisms); theClosedEnd->outputToMwr(mwr,0,0,transposeTo,addChromaticisms);
		theMiddleSection->outputToMwr(mwr,0,0,transposeTo,addChromaticisms);
	}
	theMainMelody->outputToMwr(mwr,needToInit*(isRondoEpisode==TRUE && shortenEpisode),0,transposeTo,addChromaticisms); theClosedEnd->outputToMwr(mwr,0,1,transposeTo,addChromaticisms);
#else
	theMiddleSection->outputToMwr(mwr,needToInit);
#endif
}
#endif
#endif