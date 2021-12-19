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
#include "sonata.h"
#include "mwr.h"
#include "key.h"
#include <ctype.h>
#include "rng.h"
#include <string.h>
#include <stdlib.h>
#include "symphony.h"
#include "canon.h"

#define RONDO_EPISODES 5 /* TODO vary? */

#define NUM_IN_SELECTION 6
static int beatSelection[]={2,3,3,4,4,6};

Boolean newMelodiesIn68=FALSE;
Symphony::Symphony(int barsInPhrase) {
	for (int movementNumber=1; movementNumber<=4; movementNumber++) {
		newMelodiesIn68=FALSE;
		int beatsPerBar=beatSelection[RNGrandom(NUM_IN_SELECTION)];
		if (beatsPerBar==6) { beatsPerBar=4; newMelodiesIn68=TRUE; } // Part of 6/8 fix
		int anacrusis=RNGrandom(beatsPerBar);
		Boolean majorKey=RNGrandom(2)?TRUE:FALSE;
		Key minuetKey(majorKey,RNGrandom(semitonesInOctave)-semitonesInOctave/2);
		switch(movementNumber) {
			case 1:
				/* beatsPerBar=4; anacrusis=0; */ newMelodiesIn68=FALSE;
				theSonata=new Sonata(minuetKey,barsInPhrase); // I0..I16
				break;
			case 2:
				theCanon=new Canon((NumBeats)beatsPerBar,minuetKey,barsInPhrase); // I17..I18
				break;
			case 3:
				beatsPerBar=3; newMelodiesIn68=FALSE; anacrusis=0;
				theMinuet=new Minuet((NumBeats)beatsPerBar,(NumBeats)anacrusis,minuetKey,barsInPhrase); // I19..I22
				theTrio=new Minuet((NumBeats)beatsPerBar,(NumBeats)anacrusis,minuetKey.getRandomRelatedKey(),barsInPhrase); // I23..I26
				break;
			case 4:
				newMelodiesIn68=FALSE;
				theRondo=new Rondo((NumBeats)beatsPerBar,(NumBeats)anacrusis,minuetKey,barsInPhrase,RONDO_EPISODES); // I27..I41
				break;
		}
	}
}

Symphony::~Symphony() {
	if (theRondo) delete theRondo;
	if (theTrio) delete theTrio; if (theMinuet) delete theMinuet;
	if (theCanon) delete theCanon;
	if (theSonata) delete theSonata;
}

#ifndef SETUP_ONLY_VERSION
void Symphony::outputAndClear() {
	for (int movementNumber=1; movementNumber<=4; movementNumber++) {
		Mwr mwr(NULL,3,4,4,movementNumber);
		switch(movementNumber) {
			case 1:
				theSonata->outputToMwr(mwr,P_SOP); theSonata->outputToMwr(mwr,P_ALT);
				theSonata->outputToMwr(mwr,P_TEN); theSonata->outputToMwr(mwr,P_BAS);
				theSonata->outputToMwr(mwr,P_PEDAL);
				delete theSonata; theSonata=NULL;
				break;
			case 2:
				mwr.setPart(P_SOP); theCanon->outputToMwr(mwr);
				mwr.setPart(P_ALT); theCanon->outputToMwr(mwr);
				mwr.setPart(P_TEN); theCanon->outputToMwr(mwr);
				mwr.setPart(P_BAS); theCanon->outputToMwr(mwr);
				mwr.setPart(P_PEDAL); theCanon->outputToMwr(mwr);
				delete theCanon; theCanon=NULL;
				break;
			case 3:
				theMinuet->outputToMwr(mwr,P_SOP); theTrio->outputToMwr(mwr,P_SOP,0); theMinuet->outputToMwr(mwr,P_SOP,0);
				theMinuet->outputToMwr(mwr,P_ALT); theTrio->outputToMwr(mwr,P_ALT,0); theMinuet->outputToMwr(mwr,P_ALT,0);
				theMinuet->outputToMwr(mwr,P_TEN); theTrio->outputToMwr(mwr,P_TEN,0); theMinuet->outputToMwr(mwr,P_TEN,0);
				theMinuet->outputToMwr(mwr,P_BAS); theTrio->outputToMwr(mwr,P_BAS,0); theMinuet->outputToMwr(mwr,P_BAS,0);
				theMinuet->outputToMwr(mwr,P_PEDAL); theTrio->outputToMwr(mwr,P_PEDAL,0); theMinuet->outputToMwr(mwr,P_PEDAL,0);
				delete theMinuet; delete theTrio; theMinuet=theTrio=NULL;
				break;
			case 4:
				theRondo->outputToMwr(mwr,P_SOP); theRondo->outputToMwr(mwr,P_ALT);
				theRondo->outputToMwr(mwr,P_TEN); theRondo->outputToMwr(mwr,P_BAS);
				theRondo->outputToMwr(mwr,P_PEDAL);
				delete theRondo; theRondo=NULL;
				break;
		}
	}
}
#endif
#endif
