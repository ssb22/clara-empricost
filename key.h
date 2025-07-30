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
extern const char* keyAccidentalType; // Type of each key (sharp or flat)

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
	int getReportLength() const { return(8); }
protected:
	// getModTranspose returns as if relative major for minor keys; getMajModTranspose doesn't
	int getModTranspose() const { return(((theTranspose+semitonesInOctave*(theTranspose<0))+3*(isMajor()==FALSE))%semitonesInOctave); }
	int getMajModTranspose() const { return(((theTranspose+semitonesInOctave*(theTranspose<0)))%semitonesInOctave); }
	/*const*/ int theTranspose; /*const*/ Boolean theMajorStatus;
};
#endif
