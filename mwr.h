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
#ifndef MWR_H
#define MWR_H
#include "part.h"
#include "note.h"
#include "key.h"
#include <stdio.h>
class Chord;
class Mwr {
public:
	Mwr(FILE* stream=NULL,Octave octave=2,int length=4,int l2=4,int movementNumber=0);
	~Mwr();
	void setLen(int len,int &dot);
	void initPart(int beatsPerBar);
	void setKey(Key newKey);
	Key getKey() const { return(theKey); }
	void setBeatsLeft(unsigned char beatsLeft) { theBeatsLeft=beatsLeft; }
	void printDoubleBar();
	void output(char* toOutput,int &dot);
	void setPart(Part part) { if (thePart!=part) { thePart=part; initYet=FALSE; } }
	Part getPart() const { return(thePart); }
	int getBeatsLeft() const { return(theBeatsLeft); }
	Boolean fullBarAhead() const { return((theBeatsLeft==theBeatsPerBar*2)?TRUE:FALSE); }
	void subtractBeats(int beats,const Chord* report=NULL,int repeatEnd=0);
	void restBeats(int beats=0);
	int getLength() const { return(theLength); }
	void setOctave(Octave octave);
	void writeComment(char* comment) { fprintf(theStream,"; %s\n",comment); }
	void directOutput(char* output) { fprintf(theStream,"%s",output); }
	void setIn68(Boolean newIn68) { in68=newIn68; }
protected:
	Part thePart; Key theKey;
	FILE* theStream;
	Octave theOctave;
	unsigned char theLength,theL2; // l2 is part of 6/8 fix
	unsigned char theBeatsLeft;
	int theBeatsPerBar;
	int barNo;
	void initAccidentals(); char accType[tonesInOctave];
	long startTime; Boolean initYet;
	Boolean in68;
};
#endif
