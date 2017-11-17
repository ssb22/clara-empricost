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
#ifndef SETUP_ONLY_VERSION
// Note: The order of testing for rejection in this module has been changed away
// from a "logical" one (ie grouping similar criteria together) in order to
// optimize for speed, based on statistics from a large run.
#include "chord.h"
#include <stdlib.h> // For abs
#include "rng.h"

const static Note sopHigh(DOMINANT,5,majKey);
const static Note sopLow(TONIC,4,majKey);
const static Note altHigh(TONIC,5,majKey);
const static Note altLow(DOMINANT,3,majKey);
const static Note tenHigh(DOMINANT,4,majKey);
const static Note tenLow(TONIC,3,majKey);
const static Note basHigh(TONIC,4,majKey);
const static Note basLow(DOMINANT,2,majKey);

// Returns 0 if sucessful
int Chord::twoPartCheck(Part upper,Part lower) const {
	Note nUpper=getPart(upper),nLower=getPart(lower);
	Figure fig=getFigure();
	Interval i(nUpper,nLower);
	// Avoid crossing
	if (i.isDescending()==FALSE) return(1); // #20 rejector with 13006 calls
	if (theLastChord) {
		Figure lastFig=theLastChord->getFigureIn(getKey());
		Note lUpper=theLastChord->getPart(upper),lLower=theLastChord->getPart(lower);
		Interval lastI(lUpper,lLower);
		Interval topProg(lUpper,nUpper);
		Interval btmProg(lLower,nLower);
		IntervalValue lastVal=lastI.getRoundedValue(),thisVal=i.getRoundedValue();
		// Avoid parallels
		if ((lastVal==i_unison || lastVal==i_fifth) && thisVal==lastVal && lastI.isPerfect() && i.isPerfect()) return(1); // #23 rejector with 7538 calls
		// If double 3rds must be by step
		if (((getNoteOfChord(upper)==N_THREE1 || getNoteOfChord(upper)==N_THREE2)
		&& (getNoteOfChord(lower)==N_THREE1 || getNoteOfChord(lower)==N_THREE2))
		|| ((theLastChord->getNoteOfChord(upper)==N_THREE1 || theLastChord->getNoteOfChord(upper)==N_THREE2)
		&& (theLastChord->getNoteOfChord(lower)==N_THREE1 || theLastChord->getNoteOfChord(lower)==N_THREE2))){
			if(topProg.getValue()>i_second || btmProg.getValue()>i_second) return(1); // #26 rejector with 5228 calls
			if (fig==V && lastFig!=VI) return(1); // #50 rejector with 43 calls
			if (fig==VI && lastFig!=V) return(1);
		}
		// Avoid exposed 8ves & 5ths
		if ((thisVal==i_unison || thisVal==i_fifth) && i.isPerfect()
		&& upper==P_SOP && lower==P_BAS
		&& topProg.getValue()>i_second
		&& topProg.isDescending()==btmProg.isDescending()) return(1); // #30 rejector with 2281 calls
		// Avoid overlaps
		if ((nLower.isHigherThan(&lUpper) || lLower.isHigherThan(nUpper)) && (lastFig!=fig || theLastChord->getInversion()!=getInversion())) return(1); // #32 rejector with 1842 calls
		// Don't have more than 1 note same as last
		if (nUpper.isEqualTo(&lUpper) && nLower.isEqualTo(lLower)) return(1); // #37 rejector with 1414 calls
		// S, A & T contrary to B, to nearest note, in IV-V, V-IV, if not inverted
		if (((fig==IV && lastFig==V)
		|| (fig==V && lastFig==IV)) && getInversion()==IROOT && theLastChord->getInversion()==IROOT) {
			if (topProg.isDescending()==btmProg.isDescending()) return(1); // #48 rejector with 75 calls
			if (topProg.getValue()>i_third) return(1); // #57 rejector with 17 calls
		}
		// Perfect fifth followed by diminished fifth or vice versa not permissible with bass - Don't need to check for diminished as already checked for parallels
		if (lower==P_BAS && lastVal==i_fifth && thisVal==i_fifth) return(1); // #56 rejector with 17 calls
	}
	// Never double leading-note
	if (nUpper.getDegreeOfScale()==LEADING_NOTE
	&& nLower.getDegreeOfScale()==LEADING_NOTE) return(1); // #40 rejector with 711 calls
	// Doubling of bass in diminished first inversions is ineffective in alto
	if (upper==P_ALT && lower==P_BAS && isDiminishedTriad()==TRUE && getInversion()==IFIRST && nUpper.getDegreeOfScale()==nLower.getDegreeOfScale()) return(1);
	// Avoid more than 8ve except T/B
	if (upper==lower+(Part)1 && !(upper==P_TEN && lower==P_BAS) && i.getRoundedValue()!=i.getValue()) return(1);
	return(0);
}

int Chord::checkRange(const Note &note,Part part) const {
	const Note* upper,*lower;
	switch(part) {
		case P_SOP: upper=&sopHigh; lower=&sopLow; break;
		case P_ALT: upper=&altHigh; lower=&altLow; break;
		case P_TEN: upper=&tenHigh; lower=&tenLow; break;
		case P_BAS: upper=&basHigh; lower=&basLow;
	}
	if (note.isHigherThan(upper) || lower->isHigherThan(note)) return(1); // #5 rejector with 727949 calls
	return(0);
}

/*int Chord::tuneIsFine() const {
	// This checks the soprano tune.  The rules are not to be found in a
	// harmony textbook but are my experiments.

	// Every strongbeat must be note of tonic chord unless chord V
	Note n=getPart(P_SOP);
	// NB This restriction removed as generated identical melodies what with this and using same figure
//	if (getBeatStrength()==S_1ST_BEAT && getFigure()!=V && n.getDegreeOfScale()!=TONIC && n.getDegreeOfScale()!=MEDIANT && n.getDegreeOfScale()!=DOMINANT) return(0);
	if (getBeatStrength()!=S_1ST_BEAT && theCadenceStatus==FALSE) {
		// Make sure part of the figure in use
		// NB *** This must be last thing in function, because can return(1);
		const Chord* chord=this;
		for (int chordLp=0; chordLp<theMelody->getBeatsPerBar(); chordLp++)
			{ chord=chord->getLastChord(); if (!chord) return(1); }
		if (chord->getLastChord()) { // Otherwise 1st note of anacrusis
			Interval lastInt=chord->getLastChord()->getPart(P_SOP).intervalWith(chord->getPart(P_SOP));
			Interval thisInt=theLastChord->getPart(P_SOP).intervalWith(n);
			if (abs(lastInt.getValue()-thisInt.getValue())>0) return(0); // Or >1
			if (theLastChord->getBeatStrength()!=S_1ST_BEAT) {
				// Check going same direction as well as intervals, or inverted
				if ((lastInt.isDescending()==thisInt.isDescending())
				!=(chord->getLastChord()->getLastChord()->getPart(P_SOP).intervalWith(chord->getLastChord()->getPart(P_SOP)).isDescending()==theLastChord->getLastChord()->getPart(P_SOP).intervalWith(theLastChord->getPart(P_SOP)).isDescending()))
					return(0);
			}
		}
	}
	return(1);
}*/

int Chord::checkMelody(Part part) const {
	Note note=getPart(part);
	// Check if going out of range
	if (checkRange(note,part)) return(1); // #6 rejector with 727937 calls
	// Arrange to have tonic in final S
	if (theMelody->needToEndFinal()==TRUE && part==P_SOP && theFinalChordStat && note.getDegreeOfScale()!=TONIC) return(1); // #13 rejector with 58753 calls
//	if (part==P_SOP && theSoprano.isEqualTo(undefinedNote) && !tuneIsFine()) return(1);
	if (theLastChord) {
		Figure lastFig=theLastChord->getFigureIn(getKey());
		// Leading note should rise to tonic, but fine to repeat once
		if (theLastChord->getPart(part).getDegreeOfScale()==LEADING_NOTE && note.getDegreeOfScale()!=TONIC
		&& (note.getDegreeOfScale()!=LEADING_NOTE || (theLastChord->getLastChord() && theLastChord->getLastChord()->getPart(part).getDegreeOfScale()==LEADING_NOTE))) return(1); // #14 rejector with 55779 calls
		// Don't leap augmented interval
		Interval leapInt(theLastChord->getPart(part),note);
		if (leapInt.isAugmented()) return(1); // #15 rejector with 45653 calls
		if (theLastChord->getLastChord()) {
			Interval leapInt2(theLastChord->getLastChord()->getPart(part),note);
			Interval lastLeap(theLastChord->getLastChord()->getPart(part),theLastChord->getPart(part));
			// No 7th, 9th+, inc note intervening
			if (leapInt2.getValue()==i_seventh || (leapInt2.getValue()!=leapInt2.getRoundedValue() && leapInt2.getValue()!=i_octave)
			|| leapInt.getValue()==i_seventh || (leapInt.getValue()!=leapInt.getRoundedValue() && leapInt.getValue()!=i_octave)) return(1); // #11 rejector with 102271 calls
			if (leapInt.isDescending()==leapInt2.isDescending()) {
				// Not within compass of last leap
				if (lastLeap.getValue()==i_octave || lastLeap.getValue()==i_sixth) return(1); // #17 rejector with 29631 calls
				if (lastLeap.isDiminished() && lastLeap.getRoundedValue()==i_fifth) return(1);
			}
			if (leapInt.getValue()==i_octave) {
				// 8ves must also be preceeded by note within compass
				if (lastLeap.isDescending()==leapInt2.isDescending()) return(1); // #24 rejector with 7432 calls
			}
		}
		// Must harmonize different chord if same melody note weak to strong
		if (part==P_SOP && leapInt.getValue()==i_unison && lastFig==getFigure() && theLastChord->getBeatStrength()<getBeatStrength()) return(1); // #19 rejector with 16842 calls
		// Bases rising a 3rd are poor weak to strong
		if (part==P_BAS && leapInt.getValue()==i_third && !leapInt.isDescending() && theLastChord->getBeatStrength()<getBeatStrength()) return(1); // #29 rejector with 2810 calls
		// No diminished 4th or 7th
		if (leapInt.isDiminished() && (leapInt.getRoundedValue()==i_fourth || leapInt.getRoundedValue()==i_seventh)) return(1); // #36 rejector with 1536 calls
		// // Avoid too many consecutive leaps (3+ here; could also be 4+)
		Chord* c=theLastChord; int noOfLeaps=0,noDescendingScale=0,noAscendingScale=0;
		for (int prevChord=1; prevChord<=3; prevChord++) {
			if (c->getLastChord()==NULL) break;
			Interval li(c->getLastChord()->getPart(part),c->getPart(part));
			if (li.getValue()>=i_third) noOfLeaps++;
			else {
				noOfLeaps=0;
				if (li.getValue()!=i_unison) {
					if (li.isDescending()==TRUE) noDescendingScale++;
					else noAscendingScale++;
				}
			}
			c=c->getLastChord();
		}
		// 3-note descending or ascending scale passage in bass should be followed by further step in same direction rather than a leap (in this implimentation a repeat is also allowed)
		if (part==P_BAS && !noOfLeaps && noAscendingScale>=3 && (leapInt.getValue()>=i_third || leapInt.isDescending()==TRUE)) return(1); // #39 rejector with 936 calls
		// S/B avoid remaining around one note for too long: If used more than once in previous 4 chords, reject
		if (part==P_SOP || part==P_BAS) {
			// Avoid too many consecutive leaps (3+ here; could also be 4+)
			if (noOfLeaps>=2 && leapInt.getValue()>=i_third) return(1); // #10 rejector with 108237 calls
			c=theLastChord; int usedBefore=0;
			for (prevChord=1; prevChord<=4; prevChord++) {
				if (note.isEqualTo(c->getPart(part))) usedBefore++;
				c=c->getLastChord(); if (!c) break;
			}
			if (usedBefore>1) return(1); // #18 rejector with 28458 calls
		}
		// If going from chord II, force upward resolution if going to tonic, or remain
		// the same if there is a subdominant in the chord.  This helps chromatic alteration
		// later.
		if (theMelody->willAddChromaticisms() && lastFig==II && theLastChord->getPart(part).getDegreeOfScale()==SUBDOMINANT) {
			if (getFigure()==I && note.getDegreeOfScale()!=DOMINANT) return(1); // #35 rejector with 1633 calls
			else if ((getFigure()==II || getFigure()==IV || getFigure()==VII) && note.getDegreeOfScale()!=SUBDOMINANT) return(1); // #33 rejector with 1720 calls
		}
		if (part==P_BAS && !noOfLeaps && noDescendingScale>=3 && (leapInt.getValue()>=i_third || leapInt.isDescending()==FALSE)) return(1);
	}
	return(0);
}

int Chord::invalidCadence() const {
	// If theCadenceStatus=TRUE, is last chord of cadence
	// Returns 1 if invalid cadence, eg. cadence where shouldn't be or not cadence where should be
	int cad=isCadence();
	if (cad) {
		// Must be weak to strong on cadence unless going to VI
		if (getFigure()!=VI && theLastChord->getBeatStrength()>=theBeatStrength) cad=0;
		Chord* pr1=theLastChord->getLastChord();
		Figure lastFig=theLastChord->getFigureIn(getKey());
		if (pr1) {
			// Cadence can't be preceeded by its final chord unless V-I-IV-I
			if (pr1->getFigureIn(getKey())==getFigure()) {
				if (getFigure()==I && pr1->isLastOfCadence() && pr1->getLastChord() && pr1->getLastChord()->getFigureIn(getKey())==V && lastFig==IV)
				; else cad=0;
			// Can't anticipate first chord of cadence
			} else if (pr1->getFigureIn(getKey())==lastFig) cad=0;
		}
	}
	if (theCadenceStatus==TRUE)	return(!cad); else {
		// Only V-I is unacceptable if not as actual cadence,
		// and only then if it isn't part of a modulation
		if (getFigure()==I && theLastChord && theLastChord->getFigureIn(getKey())==V && getInversion()==IROOT && theLastChord->getInversion()==IROOT
		&& (!theLastChord->getLastChord() || theLastChord->getLastChord()->getKey().isEqualTo(getKey())==TRUE)) return(1);
		return(0); //return(cad); avoids cadences where shouldn't be
	}
}

int Chord::isCadence() const {
	if (theLastChord) {
		Figure lastFig=theLastChord->getFigureIn(getKey());
		if (getInversion()==IROOT) {
			if (theLastChord->getInversion()==IROOT) {
				if (getFigure()==V) {
					if (lastFig==I || lastFig==II || lastFig==IV || lastFig==V) return(1); // #53 rejector with 31 calls
				} else if (getFigure()==I) {
					if (lastFig==V ||
					lastFig==IV) return(1); // #55 rejector with 24 calls
				} else if (getFigure()==VI && lastFig==V) return(1);
				else if (getFigure()==IV && lastFig==I) return(1); // Inverted plagal (see Addenda) - #62 rejector with 1 calls
			} else if (theLastChord->getInversion()==IFIRST) {
				if (getFigure()==V) {
					if (lastFig==I || lastFig==II || lastFig==IV) return(1); // NB Not VIb-V - #61 rejector with 5 calls
				}
			}
		}
	}
	return(0);
}

int Chord::isPossible() {
	// Add rules here: return(0) = bad progression
	// Make sure modulation fine if last of cadence
	if (theLastChord && theLastChord->getLastChord()
	&& theLastChord->getKey().isEqualTo(theLastChord->getLastChord()->getKey())==FALSE
	&& modulationIsFineI()==FALSE) return(0); // #1 rejector by nearly factor of 10 with 110001594 calls
	Figure fig=getFigure();
	if (theFinalChordStat && theMelody->needToEndFinal()==FALSE && fig==I) return(0); // Imperfect cadence if need to be - #2 rejector (nearly by factor of 10) with 18412347 calls
	if (theSoprano.isEqualTo(undefinedNote) && checkMelody(P_SOP)) return(0); // #3 rejector with 899778 calls
	// Should end on chord I
	if (theFinalChordStat && theMelody->needToEndFinal() && fig!=I) return(0); // #4 rejector with 763918 calls
	// Check against given notes
	if (!theSoprano.isEqualTo(&undefinedNote) && !getSoprano().isEqualTo(&theSoprano)) return(0);
	if (!theAlto.isEqualTo(&undefinedNote) && !getAlto().isEqualTo(&theAlto)) return(0);
	if (!theTenor.isEqualTo(&undefinedNote) && !getTenor().isEqualTo(&theTenor)) return(0);
	if (!theBass.isEqualTo(&undefinedNote) && !getBass().isEqualTo(&theBass)) return(0);
	// Avoid certain chords
	if (getInversion()==IROOT) {
		if (fig==VII) return(0); // #9 rejector with 130785 calls
	} else if (getInversion()==ISECOND) {
		if (fig!=I && fig!=IV && fig!=V) return(0); // #7 rejector (by nearly factor of 5) with 529366 calls
		if (!theLastChord) return(0); // #31 rejector with 1929 calls
	}
	if (theAlto.isEqualTo(undefinedNote) && checkMelody(P_ALT)) return(0); // #8 rejector with 150789 calls
	if (theMelody->needProperStart()) {
		if (!theLastChord) {
			if ((isUpbeat()==TRUE && fig!=V && fig!=I) || (isUpbeat()==FALSE && fig!=I)) return(0);
		} else if (!theLastChord->getLastChord() && getBeatStrength()>theLastChord->getBeatStrength() && fig!=I)
			return(0); // Some form of V-I
	}
	if (theTenor.isEqualTo(undefinedNote) && checkMelody(P_TEN)) return(0); // #12 rejector with 94482 calls
	if (theBass.isEqualTo(undefinedNote) && checkMelody(P_BAS)) return(0); // #16 rejector with 44579 calls
	// Check pairs of parts if not given
	if ((theSoprano.isEqualTo(undefinedNote) || theAlto.isEqualTo(undefinedNote)) && twoPartCheck(P_SOP,P_ALT)) return(0); // #21 rejector with 11260 calls
	if ((theAlto.isEqualTo(undefinedNote) || theTenor.isEqualTo(undefinedNote)) && twoPartCheck(P_ALT,P_TEN)) return(0); // #22 rejector with 7993 calls
	if ((theSoprano.isEqualTo(undefinedNote) || theBass.isEqualTo(undefinedNote)) && twoPartCheck(P_SOP,P_BAS)) return(0); // #27 rejector with 5207 calls
	if ((theSoprano.isEqualTo(undefinedNote) || theTenor.isEqualTo(undefinedNote)) && twoPartCheck(P_SOP,P_TEN)) return(0); // #28 rejector with 4800 calls
	if ((theTenor.isEqualTo(undefinedNote) || theBass.isEqualTo(undefinedNote)) && twoPartCheck(P_TEN,P_BAS)) return(0); // #34 rejector with 1682 calls
	if ((theAlto.isEqualTo(undefinedNote) || theBass.isEqualTo(undefinedNote)) && twoPartCheck(P_ALT,P_BAS)) return(0); // #38 rejector with 1230 calls
	// Check 3rd in chord
	if (!getNumThirds()) return(0); // #43 rejector with 352 calls
	// Must also have fifth if inversion (or III) - and must have root
	if ((getInversion()!=IROOT || fig==III) && (!getNumThirds(N_FIVE1,N_FIVE2) || !getNumThirds(N_ONE1,N_ONE2))) return(0); // #45 rejector with 191 calls
	// Doubling 3rd
	if (getNumThirds()>1 && fig!=VI && isMajorTriad()==TRUE) return(0); // #49 rejector with 52 calls
	if (theLastChord) {
		Figure lastFig=theLastChord->getFigureIn(getKey());
		// Don't have same chord weak to strong unless beginning, regardless of inversion
		if (theLastChord->getBeatStrength()<theBeatStrength && lastFig==fig && theLastChord->getLastChord()) return(0); // #44 rejector with 272 calls
		// 2nd inversions cannot be approached by leap from an inversion of another chord
		if (getInversion()==ISECOND && theLastChord->getInversion()!=IROOT && theLastChord->getBass().intervalWith(getBass()).getValue()>=i_third && lastFig!=fig) return(0); // #46 rejector with 129 calls
		// III must be followed by VI
		if (lastFig==III && fig!=VI) return(0); // #51 rejector with 35 calls
		// Avoid II-I and I-II
		if (((lastFig==II && fig==I) || (lastFig==I && fig==II)) && theLastChord->getInversion()==IROOT && getInversion()==IROOT) return(0); // #54 rejector with 27 calls
		// Double 3rd if IIb-V
		if (fig==V && lastFig==II && theLastChord->getInversion()==IFIRST && getInversion()==IROOT && theLastChord->getNumThirds()<2) return(0); // #59 rejector with 13 calls
		// Cannot have two second inversions adjacent to each other
		if (theLastChord->getInversion()==ISECOND && getInversion()==ISECOND) return(0); // #52 rejector with 31 calls
		if (theLastChord->getInversion()==ISECOND) {
			Chord* beforeLast=theLastChord->getLastChord(); // It will work (ie not NULL) as this was confirmed earlier
			Interval i=beforeLast->getBass().intervalWith(theLastChord->getBass());
			Interval j=theLastChord->getBass().intervalWith(getBass());
			if (i.getValue()==i_second && j.getValue()==i_second && i.isDescending()==j.isDescending()) {
				// Passing 6/4: 6/4 must be on weak beat; must be Ic or Vc
				if (beforeLast->getBeatStrength()<theLastChord->getBeatStrength() || getBeatStrength()<theLastChord->getBeatStrength()) return(0); // #60 rejector with 12 calls
				if (lastFig!=I && lastFig!=V) return(0);
			} else if (j.getValue()==i_unison && getInversion()==IROOT) {
				// Cadential 6/4: must be Ic or IVc; no leaps in any parts; 6/4 on stronger beat
				if (getBeatStrength()>theLastChord->getBeatStrength()) return(0); // #58 rejector with 15 calls
				if (theLastChord->getBass().intervalWith(getBass()).getValue()>=i_third ||
				theLastChord->getTenor().intervalWith(getTenor()).getValue()>=i_third ||
				theLastChord->getAlto().intervalWith(getAlto()).getValue()>=i_third ||
				theLastChord->getSoprano().intervalWith(getSoprano()).getValue()>=i_third) return(0); // #63 rejector with 1 calls
				if (lastFig!=I && lastFig!=IV) return(0);
			} else return(0); // Can't be explained as cadential or passing - #42 rejector with 382 calls
		}
		// Cadence check
		if (invalidCadence()) return(0); // #41 rejector with 627 calls
		// Avoid repetition of same chord with only 1 chord intervening
		if (theLastChord->getLastChord() && theLastChord->getLastChord()->getFigureIn(getKey())==fig && theLastChord->getLastChord()->getInversion()==getInversion()) return(0); // #47 rejector with 120 calls
		Interval sopLeap(theLastChord->getSoprano(),getSoprano());
		// V-IV: Sop 5th to root (rising 3rd)
		if (lastFig==V && fig==IV
		&& ChordPoss::getSop(theChosenPossibility)!=N_ONE1 && ChordPoss::getSop(theChosenPossibility)!=N_ONE2
		&& getInversion()==IROOT && theLastChord->getInversion()==IROOT
		&& sopLeap.getValue()!=i_third) return(0);
		// If last is IIa and minor key, this must be Va, and strong to weak
		if (getKey().isMajor()==FALSE && lastFig==II && theLastChord->getInversion()==IROOT && (fig!=V || getInversion()!=IROOT || getBeatStrength()>theLastChord->getBeatStrength())) return(0);
		// Avoid VIIb to anything except I or Ib (or VI in major key)
		if (lastFig==VII && (fig!=I || getInversion()==ISECOND) && (fig!=VI || !isMajorKey(getKey()))) return(0);
	}
	return(1);
}
#endif