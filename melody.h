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
#ifndef MELODY_H
#define MELODY_H
#include "boolean.h"
#include "mwr.h"
#include <stdio.h> /* For FILE */
#include "rng.h"
#define PEDAL_OCTAVE 2
typedef unsigned char NumBeats;
enum Strength {
S_NOT_BEAT,
S_4TH_BEAT,
S_2ND_BEAT,
S_3RD_BEAT,
S_1ST_BEAT
};

enum ModulateStatus { MS_FALSE, MS_TRUE, MS_END };
// MS_END = can have imperfect cadence at end of melody as start of modulation
// NB: If you do this, next melody must be properStart == TRUE

class Chord;
class Melody {
public:
	Melody(NumBeats beatsPerBar,NumBeats anacrusis,KeyRef key,int numChords=0,int cadences=1,int imperfectEnd=0,int properStart=1,ModulateStatus canMod=MS_FALSE,Boolean canHavePassing=TRUE,const Key* finishKey=NULL,Boolean willAddChr=FALSE);
	Melody(FILE* file);
	~Melody(); // Deletes first chord
	void addLength(NumBeats noteLen); // Reset theCadenceStatus as well
	void saveTo(FILE* file) const;
	Strength strengthOfNextBeat() const;
	void setFirstChord(Chord* chord);
	Key getKey();
	Chord* getFirstChord();
	Boolean isNextChordCadence() const;
	void nextChordIsCadence();
	Boolean isNextChordFinal() const;
	void nextChordIsFinalCadence();
	// If needToEndPart==2, outputs repeat as well
	void outputToMwr(Mwr &mwr,int needToInitPart=1,int needToEndPart=1,const Key* transposeTo=NULL,Boolean addChromaticisms=FALSE,NumBeats changeAnacrusis=0,Boolean mute=FALSE);
	NumBeats getBeatsPerBar() const { return(theBeatsPerBar); }
	Boolean needToEndFinal() const { return(doNeedEndFinal); }
	Boolean needProperStart() const { return(properStartStatus); }
	NumBeats getAnacrusis() const { return(theAnacrusis); }
	Boolean canModulate() const { return((theCanModulate!=MS_FALSE)?TRUE:FALSE); }
	Boolean doesHaveUnessentials() const { return(canHaveUnessentials); }
	Key getDestinationKey() const { return(theFinishKey); }
	Boolean willAddChromaticisms() const { return(theAddChrStatus); }
	Boolean canModulateAtEnd() const { return((theCanModulate==MS_END)?TRUE:FALSE); }
	// evalLastChordYet, etc. used for forced modulation to destinationKey
	Boolean evalLastChordYet() const { return(theEvalLastChordStatus); }
	void lastChordEval() { theEvalLastChordStatus=TRUE; }
	Boolean isIn68() const { return(in68); }
	void saveYourself() const;
	int getNumChords() const { return(theNumberOfChords); }
	int getChordLp() const { return(chordLp); }
	// Other parts of the program only need to call generate() if they have
	// constructed a Melody from a file and that file may be incomplete
	void generate(FILE* loadFrom=NULL); // If loadFrom, stops when got to end of file
	static void deleteAllFiles();
	PackOfCards* getPack() const { return(thePack); }
	int getNumber() const { return(theNumber); }
protected:
	// Because there is only one PackOfCards in memory at once, it is declared
	// static so it doesn't have to be re-created every time
	static PackOfCards* thePack;
	Boolean theEvalLastChordStatus;
	const Boolean canHaveUnessentials;
	const Boolean doNeedEndFinal;
	const NumBeats theBeatsPerBar;
	NumBeats theBeatsLeft;
	const NumBeats theAnacrusis;
	Key theKey,theFinishKey;
	Chord* theFirstChord;
	Chord* theLastChord;
	Boolean theCadenceStatus;
	Boolean theFinalStatus;
	const Boolean properStartStatus;
	const ModulateStatus theCanModulate;
	const Boolean theAddChrStatus;
	const int theNumberOfChords,theNumberOfCadences;
	Note* thePedalNote;
	Boolean isComplete;
	const Boolean in68;
	const int theNumber;
	static int nextMelodyNumber;
	int chordLp;
};

inline void Melody::setFirstChord(Chord* chord) {
	theFirstChord=chord;
}

inline Chord* Melody::getFirstChord() {
	return(theFirstChord);
}

inline Key Melody::getKey() {
	return(theKey);
}

inline Boolean Melody::isNextChordCadence() const {
	return(theCadenceStatus);
}

inline void Melody::nextChordIsCadence() {
	theCadenceStatus=TRUE;
}

inline Boolean Melody::isNextChordFinal() const {
	return(theFinalStatus);
}

inline void Melody::nextChordIsFinalCadence() {
	theFinalStatus=TRUE; theCadenceStatus=TRUE;
}

#endif