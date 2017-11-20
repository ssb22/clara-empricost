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
#include "chord.h"
Boolean Chord::isFalseRelation() const {
	if (theLastChord)
		for (Part p1=P_SOP; p1<=P_BAS; p1=(Part)(p1+1))
			for (Part p2=P_SOP; p2<=P_BAS; p2=(Part)(p2+1))
				if (p2!=p1) {
					Interval i=getPart(p1).intervalWith(theLastChord->getPart(p2));
					if (i.getRoundedValue()==i_unison && getPart(p1).isEqualTo(theLastChord->getPart(p2))==FALSE
					// Fine if also chromatically alters in this part
					&& getPart(p1).intervalWith(theLastChord->getPart(p1)).getRoundedValue()!=i_unison
					// Fine if root of this chord is 3rd of last
					&& realNote(N_ONE1,BAS_OCTAVE,getFigure()).isEqualTo(realNote(N_THREE1,BAS_OCTAVE,theLastChord->getFigure()))==FALSE)
					// NEEDATTENTION Also fine if second note is 7 of V7
						return(TRUE);
				}
	return(FALSE);
}

Boolean Chord::modulationIsFineV(KeyRef newKey) /*const*/ {
// There is a nasty "goto" in this function for size optimize in TSR
	Key k=theKey;
	theKey=oldKey; calculateFigure();
	// Must be some form of V
	// Can't be false relation
	// Can't be final chord unless theMelody->canModulateAtEnd()
	if (!theLastChord || getFigureIn(newKey)!=V || isFalseRelation()==TRUE || (theFinalChordStat==TRUE && theMelody->canModulateAtEnd()==FALSE)) goto itIsNoGood;
	// For transition, must share at least 1 note with last chord, which can't be also found in this key
	// NEEDATTENTION Transitions: When impliment dominant 7, see para 10 in Modulations
	if (hasNoteInCommonWith(theLastChord)==FALSE || theLastChord->isInKey(newKey)==TRUE) {
		// In that case, "gradual" modulation must be used if any
		// Last chord is pivot chord: Must be in both keys
		if (theLastChord->isInKey(newKey)==FALSE || theLastChord->getLastChord()->isInKey(newKey)==FALSE) goto itIsNoGood;
		// Last but 1 chord cannot be found in this key
		if (!theLastChord->getLastChord() || theLastChord->getLastChord()->isInKey(newKey)==TRUE) goto itIsNoGood;
		// Pivot chords in second inversion should be avoided:
		if (theLastChord->getInversion()==ISECOND) goto itIsNoGood;
		// If last but 1 chord contains chromatically altered note from this, must be in a different part
		for (Part p=P_SOP; p<=P_BAS; p=(Part)(p+1))
			if (getPart(p).intervalWith(theLastChord->getLastChord()->getPart(p)).getRoundedValue()==i_unison) goto itIsNoGood;
	} else {
		// Drop of chromatic semitone in abrupt modulation needs care
		for (Part p=P_SOP; p<=P_BAS; p=(Part)(p+1)) {
			Interval i=getPart(p).intervalWith(theLastChord->getPart(p));
			if (i.getRoundedValue()==i_unison && i.isDescending()==TRUE && getPart(p).isEqualTo(theLastChord->getPart(p))==FALSE) {
				// continue; if fine
				// NEEDATTENTION When impliment V7, also fine if this note is 7 of V7
				// Fine if 3rd and this chord == last chord
				if (getFigureIn(newKey)==theLastChord->getFigureIn(newKey) && (getNoteOfChord(p)==N_THREE1 || getNoteOfChord(p)==N_THREE2)) continue;
				goto itIsNoGood;
			}
		}
	}
	// To ensure modulationIsFineI() on first chord of next Melody
	if (theFinalChordStat && theMelody->canModulateAtEnd()==TRUE && theLastChord->isInKey(newKey) && theLastChord->getFigureIn(newKey)==I) {
itIsNoGood:
		theKey=k; calculateFigure(); return(FALSE);
	}
	theKey=k; calculateFigure(); return(TRUE);
}

// Next melody must be properStart==1 if this canModulateAtEnd()

Boolean Chord::modulationIsFineI() const {
	// Must be weak to strong
	// (The strength thing taken out because isUpbeat is called before modulationIsFineV)
	if (!theLastChord /*|| theLastChord->getBeatStrength()>=getBeatStrength()*/ || !theLastChord->getLastChord()) return(FALSE);
	// Must be some form of I, or VI if last is root position V
	if (getFigure()!=I && (getFigure()!=VI || theLastChord->getFigure()!=V || theLastChord->getInversion()!=IROOT)) return(FALSE);
	// If gradual modulation and pivot chord is same figure as this, must be different inversion
	if (theLastChord->getLastChord()->isInKey(getKey()) && getFigure()==theLastChord->getLastChord()->getFigureIn(getKey()) && getInversion()==theLastChord->getLastChord()->getInversion()) return(FALSE);
	return(TRUE);
}
#endif