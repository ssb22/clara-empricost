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