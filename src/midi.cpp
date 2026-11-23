/*
   Clara Empricost - Condition List Action Rejection
     Algorithm for the Evaluation of Music at Pseudo-Random
     Idea Construction Stage

   (C) 1996 Silas S. Brown https://ssb22.user.srcf.net

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
#ifdef Elara
#include <stdlib.h> /* getenv */
#endif
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
#ifdef Elara
		/* Elara 2026: a cheap General-MIDI synth does pianos, bells and
		   plucked things much better than it does strings and brass, so
		   let a listener ask for the instruments that survive a synth.
		   Unset by default: the 1996 behaviour is unchanged. */
		if (getenv("CLARA_SYNTH_INSTS")) {
			static const int synthOK[]={0,6,8,9,11,12,13,14,/*19,20,21,22,*/24,45,46,47/*,52*/}; /* SSB: commented out organs and choir as Elara wants to stick to plucked things i.e. avoid sample loops */
			char keep[NUM_MIDI_INSTS]; int n;
			for (n=0; n<NUM_MIDI_INSTS; n++) keep[n]=0;
			for (n=0; n<(int)(sizeof(synthOK)/sizeof(synthOK[0])); n++) keep[synthOK[n]]=1;
			for (n=0; n<NUM_MIDI_INSTS; n++) if (!keep[n]) instrumentRange[n]=0;
		}
#endif
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
