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
#ifndef KEY_H
#define KEY_H

#define KeyRef const Key &
//#define KeyRef Key
//#define KeyRef const Key

// #define MINOR_TESTING

#include "boolean.h"
#include "fgetint.h"
#include <stdio.h> /* For FILE */
unsigned RNGrandom(unsigned possibilities);
#define tonesInOctave 7
#define semitonesInOctave 12
extern int majorKey[tonesInOctave];
extern int minorKey[tonesInOctave];
extern int toneTranspose[semitonesInOctave]; // Amount to add to tone number (C, D, E, etc.) in each key
extern int minToneTranspose[semitonesInOctave];
extern int keyNumAccidentals[semitonesInOctave]; // Number of accidentals in each key
extern char* keyAccidentalType; // Type of each key (sharp or flat)

enum RelatedKeyType { RK_RELATIVE,RK_DOMINANT,RK_SUBDOMINANT/*,RK_ENHARMONIC*/,
NUM_REL_KEY_TYPE };

#define sharpIncrement 4
#define flatIncrement 3
class Key {
public:
	Key(Boolean majKey=TRUE,int transpose=0) : theTranspose(transpose),theMajorStatus(
#ifndef MINOR_TESTING
	majKey
#else
	FALSE
#endif
) {};
	Key(Key* key) : theTranspose(key->getTranspose()),theMajorStatus(key->isMajor()) {};
	~Key() {};
	void saveTo(FILE* file) const { fwrite(&theTranspose,sizeof(theTranspose),1,file); fputc(theMajorStatus,file); }
	Key(FILE* file) : theTranspose(fgetInteger(file)),theMajorStatus((Boolean)fgetc(file)) {};
	int getArray(int offset) const { return(theMajorStatus?majorKey[offset]:minorKey[offset]); }
	int getTranspose() const { return(theTranspose); }
	int getToneTranspose() const { return((isMajor()?toneTranspose:minToneTranspose)[getMajModTranspose()]); }
	Boolean isMajor() const { return(theMajorStatus); }
	Boolean isEqualTo(const Key&key) const { return((getTranspose()==key.getTranspose() && isMajor()==key.isMajor())?TRUE:FALSE); }
	int getNumAccidentals() const { return(keyNumAccidentals[getModTranspose()]); }
	char getAccidentalType() const { return(keyAccidentalType[getModTranspose()]); }
	Key getRelatedKey(RelatedKeyType rel) const;
	Key getRandomRelatedKey() const { return(getRelatedKey((RelatedKeyType)RNGrandom(NUM_REL_KEY_TYPE))); }
	Boolean containsSemitone(int semitone) const; // In the range 0-11, used in NOTE.H
	void printReportTo(FILE* file) const;
	int getReportLength() const { return(7); }
protected:
	// getModTranspose returns as if relative major for minor keys; getMajModTranspose doesn't
	int getModTranspose() const { return(((theTranspose+semitonesInOctave*(theTranspose<0))+3*(isMajor()==FALSE))%semitonesInOctave); }
	int getMajModTranspose() const { return(((theTranspose+semitonesInOctave*(theTranspose<0)))%semitonesInOctave); }
	/*const*/ int theTranspose; /*const*/ Boolean theMajorStatus;
};
#endif