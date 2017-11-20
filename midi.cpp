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

static char shuffle[NUM_MIDI_INSTS];

int randomMIDIinst(Part part) {
	static int doneBefore=0;
	if (!doneBefore) {
		doneBefore=1;
		for (int lp=0; lp<NUM_MIDI_INSTS; lp++) shuffle[lp]=lp;
		pushRNG();
		for (lp=0; lp<NUM_MIDI_INSTS; lp++) {
			int s1=RNGrandom(NUM_MIDI_INSTS),s2=RNGrandom(NUM_MIDI_INSTS);
			int temp=shuffle[s1]; shuffle[s1]=shuffle[s2]; shuffle[s2]=temp;
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
		if (instrumentRange[shuffle[lp]]&bit) return(shuffle[lp]);
		lp=(lp+1)%NUM_MIDI_INSTS;
	}
}
#endif
#endif