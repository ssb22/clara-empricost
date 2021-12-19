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
#include "rondo.h"
Rondo::Rondo(NumBeats beatsPerBar,NumBeats anacrusis,Key key,int barsInPhrase,int numberOfEpisodes)
: theNumberOfEpisodes(numberOfEpisodes) {
	theEpisodes=new Minuet*[theNumberOfEpisodes];
	theEpisodes[0]=new Minuet(beatsPerBar,anacrusis,key,barsInPhrase,TRUE,MS_FALSE);
	for (int lp=1; lp<theNumberOfEpisodes; lp++)
		theEpisodes[lp]=new Minuet(beatsPerBar,(NumBeats)0,key.getRandomRelatedKey(),barsInPhrase,TRUE,MS_END);
}

Rondo::~Rondo() {
	for (int lp=0; lp<theNumberOfEpisodes; lp++) delete theEpisodes[lp];
	delete theEpisodes;
}

#ifndef SETUP_ONLY_VERSION
void Rondo::outputToMwr(Mwr &mwr,Part part) const {
	theEpisodes[0]->outputToMwr(mwr,part,1,0);
	for (int lp=1; lp<theNumberOfEpisodes; lp++) {
		theEpisodes[lp]->outputToMwr(mwr,part,/*0*/1,0);
		theEpisodes[0]->outputToMwr(mwr,part,/*0*/1,1);
	}
}
#endif
#endif
