/*
   Clara Empricost - Condition List Action Rejection
     Algorithm for the Evaluation of Music at Pseudo-Random
     Idea Construction Stage

   (C) 1996-2001 Silas S. Brown (St John's College,
       Cambridge, UK, http://www.cus.cam.ac.uk/~ssb22 )
    This code is no longer being maintained by the author.

    This code was written in 1996.  I am aware that it could be better,
    but do not have time to re-write it all.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; see the file COPYING.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
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