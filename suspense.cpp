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
#ifndef SETUP_ONLY_VERSION
#ifndef TSR_VERSION
#include "chord.h"
#include <stdio.h> // For putc() for passing notes
#include <stdlib.h> // For abs
#include "rng.h"
int Chord::initPassNotes(int combination) {
	for (int l=0; l<2; l++) {
		havePassingNotes[l]=getPassPart(l,combination);
		if (l && havePassingNotes[l]==havePassingNotes[0]) { havePassingNotes[l]=P_UNDEFINED; break; }
		else if (havePassingNotes[l]==P_UNDEFINED) continue;
		Interval leapInt(getPart(havePassingNotes[l]),theNextChord->getPart(havePassingNotes[l]));
		switch(getPassType(l,combination)) {
			case 0: // Passing notes
				thePassingNotes[l]=new Note(getPart(havePassingNotes[l]));
				if (leapInt.getValue()>i_third) return(0); // Passing notes must be approached and quitted by step in same direction; aux notes, anticipation etc. also allowed by this line
				if (leapInt.isDescending()==TRUE || (leapInt.getValue()==i_unison && RNGrandom(2))) thePassingNotes[l]->decrement(); else thePassingNotes[l]->increment();
				break;
			case 1: // "Unessential" harmony notes - also in direction of next note (but may go further)
				if (getNoteOfChord(havePassingNotes[l])==N_ONE1 || getNoteOfChord(havePassingNotes[l])==N_FIVE2) return(0); // So doesn't drop off the edge!
				NoteOfChord n=(NoteOfChord)(getNoteOfChord(havePassingNotes[l])+((leapInt.isDescending()==TRUE)?-1:1));
				Octave oct; switch(havePassingNotes[l]) { case P_SOP: oct=SOP_OCTAVE; break; case P_ALT: oct=ALT_OCTAVE; break; case P_TEN: oct=TEN_OCTAVE; break; case P_BAS: oct=BAS_OCTAVE; break; default: return(0); } // Should never reach default
				Note foo=realNote(n,oct,ChordPoss::getFigure(theChosenPossibility)); thePassingNotes[l]=new Note(&foo);
				if (checkRange(*thePassingNotes[l],havePassingNotes[l])) return(0); // Don't go out of range!
				// Avoid overlaps
				switch(havePassingNotes[l]) {
					case P_SOP: if (getAlto().isHigherThan(thePassingNotes[l])==TRUE) return(0); break;
					case P_ALT: if (getTenor().isHigherThan(thePassingNotes[l])==TRUE || getSoprano().isHigherThan(thePassingNotes[l])==FALSE) return(0); break;
					case P_TEN: if (getBass().isHigherThan(thePassingNotes[l])==TRUE || getAlto().isHigherThan(thePassingNotes[l])==FALSE) return(0); break;
					case P_BAS: if (getTenor().isHigherThan(thePassingNotes[l])==FALSE) return(0); break;
                default: ;
				}
				break;
		}
	}
	return(1);
}

#define CMAX 64

void Chord::selectPassNotes() {
	putchar('P');
	if (isLastOfCadence()==FALSE) {
		int start=RNGrandom(CMAX-1)+1,done=0,d2=0;
		for (int combination=start; combination!=start || !done; combination=(combination+1)%CMAX) {
			done=1; if (combination!=start) d2=1;
			delPassNotes();
			if (initPassNotes(combination)) {
				// Now check them
				for (int l=0; l<2; l++) if (havePassingNotes[l]!=P_UNDEFINED) for (Part p=P_SOP; p<=P_BAS; p=(Part)(p+1)) if (p!=havePassingNotes[l] && p!=havePassingNotes[!l]) {
					Interval i(getPartOrPassNote(p),getPassNote(havePassingNotes[l]));
					// No interval of 2nd or unison with note in another part
					if (i.getValue()==i_second || i.getValue()==i_unison) done=0;
					// Don't have minor ninths
					if (i.getValue()==i_ninth && i.isMinor()==TRUE) done=0;
					// Don't introduce fifths
					if (i.getRoundedValue()==i_fifth && theNextChord->getIntBetween(havePassingNotes[l],p).getRoundedValue()==i_fifth) done=0;
				}
				if (havePassingNotes[0]!=P_UNDEFINED && havePassingNotes[1]!=P_UNDEFINED) {
					Interval i(getPassNote(havePassingNotes[0]),getPassNote(havePassingNotes[1]));
					Interval prog0(getPart(havePassingNotes[0]),theNextChord->getPart(havePassingNotes[0]));
					Interval prog1(getPart(havePassingNotes[1]),theNextChord->getPart(havePassingNotes[1]));
					if (i.getValue()==i_sixth || i.getValue()==i_third) {
						// Make sure going parallel if both passing notes
						if (prog0.isDescending()!=prog1.isDescending() && prog0.getValue()==i_third && prog1.getValue()==i_third) done=0;
					} else if (i.getRoundedValue()==i_unison && i.getValue()!=i_unison) {
						// Make sure contrary motion if both passing notes
						if (prog0.isDescending()==prog1.isDescending() && prog0.getValue()==i_third && prog1.getValue()==i_third) done=0;
					} else if (i.getRoundedValue()!=i_fifth) done=0;
				}
				if (done) break; else done=1;
			} else delPassNotes();
		}
		if (!d2) delPassNotes(); // Couldn't find any!
		if (canAccentPassNotes()) accentPassNotes=TRUE; /*else accentPassNotes=FALSE;*/ // Set to FALSE on delPassNotes()
		if (theLastChord && ((theLastChord->getBeatStrength()>getBeatStrength() && !theMelody->isIn68()) || (theLastChord->getBeatStrength()<getBeatStrength() && theMelody->isIn68()))) {
			// (Rule is reversed for 6/8 because otherwise problems with demisemiquavers)
			theOrnament=(OrnamentType)RNGrandom(MAX_ORNAMENT_TYPE);
			if (havePassingNotes[0]!=P_UNDEFINED || havePassingNotes[1]!=P_UNDEFINED)
				theOrnPart=havePassingNotes[RNGrandom(1+(havePassingNotes[1]!=P_UNDEFINED))];
			else if (theOrnament==ORN_TRILL) theOrnPart=(Part)RNGrandom(((int)P_BAS)+1);
		}
	}
	if (theLastChord) theLastChord->selectPassNotes();
}

Boolean Chord::canSuspendPart(Part part) const {
	// May suspend if repeated in next chord and step higher in last chord, and stronger than last chord
	Note _last=theLastChord->getPart(part),_this=getPart(part);
	Interval i(_last,_this);
	if (theNextChord->getPart(part).isEqualTo(_this) && getBeatStrength()>theLastChord->getBeatStrength() && getBeatStrength()>theNextChord->getBeatStrength() && i.isDescending() && i.getValue()==i_second) {
		// Cannot sound resolution in SAT against suspension
		Note s=getPart(P_SOP),a=getPart(P_ALT),t=getPart(P_TEN);
		Interval sb(s,_this),ab(a,_this),tb(t,_this);
		if ((sb.getRoundedValue()==i_unison && part!=P_SOP) || (ab.getRoundedValue()==i_unison && part!=P_ALT) || (tb.getRoundedValue()==i_unison && part!=P_TEN)) return(FALSE);
		if (part==P_BAS) {
			// Only suspend 3rd of chord if in bass
			if (getNoteOfChord(part)!=N_THREE1 || getNoteOfChord(part)!=N_THREE2) return(FALSE);
		}
		if ((getNoteOfChord(part)==N_FIVE1 || getNoteOfChord(part)==N_FIVE2) && getInversion()!=i_second) return(FALSE);
		return(TRUE);
	} return(FALSE);
}

void Chord::selectSuspensions() {
	// TODO Poss problems with passing or harmony notes on same chord as suspension
	theSuspendedStatus=NO_SUSPENSIONS;
	if (theLastChord) {
		Note s=getPart(P_SOP),a=getPart(P_ALT),t=getPart(P_TEN),b=getPart(P_BAS);
		Interval sa(s,a),at(a,t),tb(t,b);

		if (canSuspendPart(P_SOP) && canSuspendPart(P_ALT) && (sa.getValue()==i_third || sa.getValue()==i_sixth)) theSuspendedStatus=SA_SUSPENDED;
		else if (canSuspendPart(P_ALT) && canSuspendPart(P_TEN) && (at.getValue()==i_third || at.getValue()==i_sixth)) theSuspendedStatus=AT_SUSPENDED;
		else if (canSuspendPart(P_TEN) && canSuspendPart(P_BAS) && (tb.getValue()==i_third || tb.getValue()==i_sixth)) theSuspendedStatus=TB_SUSPENDED;
		else {
			if (canSuspendPart(P_SOP)) theSuspendedStatus=SOP_SUSPENDED;
			if (canSuspendPart(P_ALT) && (theSuspendedStatus==NO_SUSPENSIONS || !RNGrandom(2))) theSuspendedStatus=ALT_SUSPENDED;
			if (canSuspendPart(P_TEN) && (theSuspendedStatus==NO_SUSPENSIONS || !RNGrandom(2))) theSuspendedStatus=TEN_SUSPENDED;
			if (canSuspendPart(P_BAS) && (theSuspendedStatus==NO_SUSPENSIONS || !RNGrandom(2))) theSuspendedStatus=BAS_SUSPENDED;
		}
		theLastChord->selectSuspensions();
	}
}

inline Boolean isFifth(NoteOfChord n) { return((n==N_FIVE1 || n==N_FIVE2)?TRUE:FALSE); }
Boolean Chord::canAccentPassNotes() const {
	if (!theNextChord || (theNextChord->hasPassingNotes()==TRUE && theNextChord->nextNeedsToAccent()==FALSE) || hasPassingNotes()==FALSE) return(FALSE);
	// Don't need to worry about harmony notes here as these are handled separately
	// Resolved part not in unison (regardless of 8ve) with S, A or T (of resolve chord)
	Note s=theNextChord->getPart(P_SOP),a=theNextChord->getPart(P_ALT),t=theNextChord->getPart(P_TEN);
	for (int lp=0; lp<2; lp++) if (havePassingNotes[lp]!=P_UNDEFINED && (getPassNote(havePassingNotes[lp]).intervalWith(getPart(havePassingNotes[lp])).getValue()<i_third)) {
		// The second "if" condition avoids checking harmony notes
		// APN not struck against res., but fine if res. held over from last chord, ie last chord stronger & repeated
		Note _this=theNextChord->getPart(havePassingNotes[lp]);
		Interval sb(s,_this),ab(a,_this),tb(t,_this);
		if ((sb.getRoundedValue()==i_unison && havePassingNotes[lp]!=P_SOP && (getBeatStrength()<theNextChord->getBeatStrength() || getPart(P_SOP).intervalWith(s).getValue()!=i_unison))
		|| (ab.getRoundedValue()==i_unison && havePassingNotes[lp]!=P_ALT && (getBeatStrength()<theNextChord->getBeatStrength() || getPart(P_ALT).intervalWith(s).getValue()!=i_unison))
		|| (tb.getRoundedValue()==i_unison && havePassingNotes[lp]!=P_TEN && (getBeatStrength()<theNextChord->getBeatStrength() || getPart(P_TEN).intervalWith(s).getValue()!=i_unison)))
			return(FALSE);
		// Neither chord can be 2nd inversion if in bass
		if (havePassingNotes[lp]==P_BAS && (theNextChord->getInversion()==ISECOND || getInversion()==ISECOND)) return(FALSE);
	}
	Boolean descending=thePassingNotes[thePassingNotes[0]?0:1]->intervalWith(theNextChord->getPart(havePassingNotes[thePassingNotes[0]?0:1])).isDescending();
	if (havePassingNotes[0]!=P_UNDEFINED && havePassingNotes[1]!=P_UNDEFINED) {
		// Cannot be in parallel 6ths
		if (thePassingNotes[0]->intervalWith(thePassingNotes[1]).getValue()==i_sixth) return(FALSE);
		// If ascending, neither are 5th of chord and next chord must be same chord
		if (descending==FALSE &&
			(isFifth(getNoteOfChord(havePassingNotes[0])) || isFifth(getNoteOfChord(havePassingNotes[1]))
			|| theNextChord->getFigureIn(getKey())!=getFigure())) return(FALSE);
	} else {
		// Must be descending
		if (descending==FALSE) return(FALSE);
	}
	return(TRUE);
}
#endif
#endif
