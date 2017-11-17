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
#ifndef CHORD_H
#define CHORD_H

#define incThird 2
#define incFifth 4
#define SOP_OCTAVE 4
#define ALT_OCTAVE 3
#define TEN_OCTAVE 3
#define BAS_OCTAVE 2

#include "melody.h"
#include "note.h"
#include "interval.h"
#include <stdlib.h>
#include "part.h"
#include "mwr.h"

enum Inversion {IROOT,IFIRST,ISECOND,IUNDEFINED};
enum Figure {I=0,II,III,IV,V,VI,VII,FUNDEFINED};

// 1/3/5 in each part, *2 8ves, *7 figures
#define possOctaves 2
#define possChordDegrees 3
#define possFigs 7
#define BITS_PER_BYTE 8
#define FULLBYTE 255
//#define numPossibilities possOctaves*possChordDegrees*possOctaves*possChordDegrees*possOctaves*possChordDegrees*possOctaves*possChordDegrees*possFigs
#define numPossibilities 9072
#define packSize 81
// packSize: Or 16, etc. (goes into numPossibilities but NOT multiple of possFigs)

enum NoteOfChord { N_ONE1,N_THREE1,N_FIVE1,N_ONE2,N_THREE2,N_FIVE2,N_UNDEFINED };

// Choose at random occasionally, more likely in sop, on weak beats
// Ornament theOrnPart if defined
enum OrnamentType {
	ORN_NONE,    // No ornament
	ORN_DAGATA,  // Split a quaver into two semiquavers then have a quaver
	ORN_TADAGA,  // Quaver then the two semis
	ORN_SKIP,    // Make passing note from quaver to semiquaver, dotting the previous quaver (including "Scotch snap" for accented passing notes)
//	ORN_RPT,     // Repeat the note after a harmony note eg. L8cL16ec
	ORN_TRILL,   // Trill (NOT the passing note!): ACCEPTABLE EVEN IF NO PASS NOTE
	MAX_ORNAMENT_TYPE // Value for number of possibilities for OrnamentType
};

enum SuspendedStatusType { NO_SUSPENSIONS,SOP_SUSPENDED,ALT_SUSPENDED,TEN_SUSPENDED,BAS_SUSPENDED,SA_SUSPENDED,AT_SUSPENDED,TB_SUSPENDED};

class ChordPoss {
public:
	static NoteOfChord getSop(int possibility);
	static NoteOfChord getAlt(int possibility);
	static NoteOfChord getTen(int possibility);
	static NoteOfChord getBas(int possibility);
	static Figure getFigure(int possibility);
};
#define undefinedPoss (-1) /* Used when loading chords from a file */
class Chord {
public:
	Chord(const Note &s,const Note &a,const Note &t,const Note &b,Melody* whichMelody,Chord* lastChord=NULL,NumBeats length=1,int possNo=undefinedPoss,int origPos=undefinedPoss/*,SuspendedStatusType suspendedStatus=NO_SUSPENSIONS*/,Key*k=NULL);
	// constructor generates possibilities within SATB (undefinedNote is poss)
	~Chord();
	Chord* setNextChord(Chord* chord);
	Inversion getInversion() const;
	Figure getFigure() const { return(theFigure); }
	Figure getFigureIn(KeyRef key) const;
	void youAreNoGood();
	Note getPart(Part part) const;
	Note getSoprano() const;
	Note getAlto() const;
	Note getTenor() const;
	Note getBass() const;
	Note getPassNote(Part part) const;
	Note getPartOrPassNote(Part part) const;
	Note getPartOrPass(int pass,Part part) const { if (pass) return(getPassNote(part)); return(getPart(part)); }; // For MWR
	Strength getBeatStrength() const;
	Chord* getLastChord() const;
	Chord* getNextChord() const;
	Interval getIntBetween(Part p1,Part p2) const;
	Interval getSAInt() const;
	Interval getSTInt() const;
	Interval getSBInt() const;
	Interval getATInt() const;
	Interval getABInt() const;
	Interval getTBInt() const;
	int getNumThirds(NoteOfChord n1=N_THREE1,NoteOfChord n2=N_THREE2) const;
	Boolean isMajorTriad() const;
	Boolean isDiminishedTriad() const;
	NoteOfChord getNoteOfChord(Part part) const;
	Boolean isLastOfCadence() const;
	Boolean isFinalChord() const;
	Boolean hasPassingNotes() const { return((havePassingNotes[0]!=P_UNDEFINED || havePassingNotes[1]!=P_UNDEFINED)?TRUE:FALSE); }
	Boolean nextNeedsToAccent(Part part=P_UNDEFINED) const;
	void saveTo(FILE* file) const;
	void printReportTo(FILE* file) const;
	int outputToMwr(Mwr &mwr,int extnOfLast,int &dot,int &d2,int &loop,int needToEndPart=0,const Key* transposeTo=NULL,Boolean addChromaticisms=FALSE,
		Boolean doRepeatEnd=FALSE) const; // Returns 1 if next chord needs to be extention of the two
	Key getKey() const { return(theKey); }
	Key* getKeyPtr() /*const*/ { return(&theKey); } // Not const because this version of the compiler complains!
	Boolean isInKey(KeyRef key) const { return((getSoprano().isInKey(key)==TRUE && getAlto().isInKey(key)==TRUE && getTenor().isInKey(key)==TRUE && getBass().isInKey(key)==TRUE)?TRUE:FALSE); }
	int sopIsSuspended() const { return(theSuspendedStatus==SOP_SUSPENDED || theSuspendedStatus==SA_SUSPENDED); }
	int altIsSuspended() const { return(theSuspendedStatus==ALT_SUSPENDED || theSuspendedStatus==SA_SUSPENDED || theSuspendedStatus==AT_SUSPENDED); }
	int tenIsSuspended() const { return(theSuspendedStatus==TEN_SUSPENDED || theSuspendedStatus==TB_SUSPENDED || theSuspendedStatus==AT_SUSPENDED); }
	int basIsSuspended() const { return(theSuspendedStatus==BAS_SUSPENDED || theSuspendedStatus==TB_SUSPENDED); }
	Boolean isPartSuspended(Part part) const;
	Boolean isUpbeat() const;
protected:
	/* Chords select a possibility at random, and did add 1 to that
	possibility until they found one which is acceptable.  However,
	if there is a large gap in the acceptable possibilities, then this
	increases the probability of choosing the possibility after this
	gap, and this bias is unwanted.  Hence the indirection of the
	selection via a "PackOfCards".  However, it would be unweildy in both
	processing time and storage space to allocate a separate PackOfCards
	to each Chord.  Allocating one to each Melody is feasible because the
	more the better due to possible gaps in the remapped version, and Melodies
	are treated as self-contained "tasks" in parallel processing, by the TSR
	version, and when the program is interrupted part-way through.
	*/
	PackOfCards* getPack() const { return(theMelody->getPack()); }
	void display() const;
	void erase() const;
	void calculateFigure();
	Figure theFigure;
	Boolean hasNoteInCommonWith(Chord* chord) const {
		return((getSoprano().isEqualTo(chord->getSoprano())==TRUE || getAlto().isEqualTo(chord->getAlto())==TRUE || getTenor().isEqualTo(chord->getTenor())==TRUE || getBass().isEqualTo(chord->getBass())==TRUE)?TRUE:FALSE);
	}
	Boolean isFalseRelation() const;
	Boolean modulationIsFineV(KeyRef newKey) /*const*/; // Call after 1st chord of cadence formed
	Boolean modulationIsFineI() const; // Call after 2nd chord of cadence formed
	Boolean theCadenceStatus;
	void changeChromaticAccidental(char &accidental,Part whichPart) const;
	void doChromaticUnessentials(char &accidental,const Note &note,const Note &before,const Note &after) const;
	void chooseAPossibility(int start);
	int findSomePossibility();
	int theChosenPossibility,origVal,theUnmappedPossibility;
	Melody* theMelody;
	const NumBeats theLength;
	Chord* theLastChord;
	Chord* theNextChord;
	const Note theSoprano,theAlto,theTenor,theBass;
	Note realNote(NoteOfChord note,Octave octave,Figure figure,int addOne=0) const;
	int isPossible();
	Strength theBeatStrength;
	int twoPartCheck(Part upper,Part lower) const;
	int checkMelody(Part part) const;
	int invalidCadence() const;
	int isCadence() const;
	Boolean theFinalChordStat;
	Boolean isNextChordFinal() const { return(theNextChord?(theNextChord->isFinalChord()):(theMelody->isNextChordFinal())); }
	Boolean canSuspendPart(Part part) const; // Next and last chords must be present
	Part havePassingNotes[2];
	Note* thePassingNotes[2];
	void delPassNotes();
	void selectPassNotes(); // Only called when next chord is defined
	void selectSuspensions(); // Ditto
	Part getPassPart(int index,int combination);
	char getPassType(int index,int combination);
	int initPassNotes(int combination);
	int checkRange(const Note &note,Part part) const;
//	int tuneIsFine() const;
	SuspendedStatusType theSuspendedStatus; // Applicable to percussion of suspension
	Boolean canAccentPassNotes() const;
	Boolean accentPassNotes; OrnamentType theOrnament; Part theOrnPart;
	Key theKey,oldKey;
	char possibilitiesEvaluated;
};

Chord* loadChord(FILE* file,Melody* whichMelody,Chord* lastChord=NULL);

inline Figure ChordPoss::getFigure(int possibility) {
	return((Figure)(possibility%possFigs));
}

inline Chord* Chord::setNextChord(Chord* chord) {
	theNextChord=chord;
	return(this);
}

inline Figure Chord::getFigureIn(KeyRef key) const {
	if (key.isEqualTo(oldKey)==TRUE) return(ChordPoss::getFigure(theChosenPossibility));
	Note x((DegreeOfScale)ChordPoss::getFigure(theChosenPossibility),BAS_OCTAVE,oldKey);
	x.adjustToKey(key);
	return((Figure)(x.getDegreeOfScale()));
}

inline void Chord::youAreNoGood() {
	erase();
	// Using the fact that whenever the program CAN modulate, it WILL,
	// can change any EXISTING modulations to go to the destination key
	// if this is the problem
	if (theMelody->evalLastChordYet() && theKey.isEqualTo(oldKey)==FALSE && theKey.isEqualTo(theMelody->getDestinationKey())==FALSE && modulationIsFineV(theMelody->getDestinationKey())==TRUE)
		{ theKey=theMelody->getDestinationKey(); calculateFigure(); display(); }
	// Otherwise, it could be a modulation causing the problem, so don't modulate
	else if (theKey.isEqualTo(oldKey)==FALSE) { theKey=oldKey; calculateFigure(); display(); }
	// Failing all that, it's "back to the drawing board" ....
	else { if (theLastChord) oldKey=theLastChord->getKey(); chooseAPossibility((theUnmappedPossibility+1)%numPossibilities); } // chooseAPossibility also assigns theKey
}

inline Strength Chord::getBeatStrength() const {
	return(theBeatStrength);
}

inline Chord* Chord::getLastChord() const {
	return(theLastChord);
}

inline Chord* Chord::getNextChord() const {
	return(theNextChord);
}

inline Boolean Chord::isLastOfCadence() const {
	return(theCadenceStatus);
}

inline Boolean Chord::isFinalChord() const {
	return(theFinalChordStat);
}

inline Part Chord::getPassPart(int index,int combination) {
	return((Part)((combination/(index?1:4))%4));
}

inline char Chord::getPassType(int index,int combination) {
	return((char)((combination/(index?16:32))%2));
}

inline Boolean Chord::isUpbeat() const {
	return(((theNextChord?theNextChord->getBeatStrength():theMelody->strengthOfNextBeat())>getBeatStrength())?TRUE:FALSE);
}
#endif
