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
#ifndef SETUP_ONLY_VERSION
#include "part.h"
#include "rng.h"
#define IR_SOP 1
#define IR_ALT 2
#define IR_TEN 4
#define IR_BAS 8
#define IR_PED 16
#define IR_ALL 15
#define IR_REALLY_ALL 31
#define IR_LOWLONG (IR_TEN+IR_BAS+IR_PED)
#define NUM_MIDI_INSTS 127
static char instrumentRange[NUM_MIDI_INSTS]={
IR_ALL,0,0,0,0,0,IR_ALL,IR_SOP,IR_SOP,IR_SOP,0,IR_SOP+IR_ALT,IR_SOP+IR_ALT,
IR_SOP,IR_PED,0,0,0,0,IR_REALLY_ALL,IR_ALL,IR_ALL,IR_ALL,0,IR_ALL,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,IR_SOP,IR_ALT,IR_LOWLONG,
0,IR_REALLY_ALL,IR_ALL,IR_SOP+IR_ALT,IR_PED,IR_REALLY_ALL,IR_REALLY_ALL,
0,0,IR_REALLY_ALL,IR_REALLY_ALL,0,0,IR_SOP+IR_ALT,IR_LOWLONG,
IR_LOWLONG,IR_SOP+IR_ALT,IR_SOP+IR_ALT,0,0,0,0,0,0,0,IR_TEN,
IR_LOWLONG,IR_LOWLONG,IR_SOP+IR_ALT,IR_SOP,IR_SOP,IR_SOP,IR_SOP+IR_ALT,0,0,
IR_SOP,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,IR_PED,0,0,0,0,0,0,0,0,0,0,0,0,
IR_PED,IR_ALT,0,IR_SOP,0,0,IR_PED,0,IR_PED,0,0,0,0,0,0,0,0,0
};

static char instrument_shuffle[NUM_MIDI_INSTS];

int randomMIDIinst(Part part) {
	static int doneBefore=0;
	if (!doneBefore) {
		doneBefore=1; int lp;
		for (lp=0; lp<NUM_MIDI_INSTS; lp++) instrument_shuffle[lp]=lp;
		pushRNG();
		for (lp=0; lp<NUM_MIDI_INSTS; lp++) {
			int s1=RNGrandom(NUM_MIDI_INSTS),s2=RNGrandom(NUM_MIDI_INSTS);
			int temp=instrument_shuffle[s1]; instrument_shuffle[s1]=instrument_shuffle[s2]; instrument_shuffle[s2]=temp;
		}
		popRNG();
	}
	int bit=0; switch(part) {
		case P_SOP: bit=IR_SOP; break;
		case P_ALT: bit=IR_ALT; break;
		case P_TEN: bit=IR_TEN; break;
		case P_BAS: bit=IR_BAS; break;
		case P_PEDAL: bit=IR_PED; break;
		default: return(0);
	}
	int lp=RNGrandom(NUM_MIDI_INSTS); while (1) {
		if (instrumentRange[instrument_shuffle[lp]]&bit) return(instrument_shuffle[lp]);
		lp=(lp+1)%NUM_MIDI_INSTS;
	}
}
#endif
#endif
