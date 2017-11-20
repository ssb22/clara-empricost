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
#include "key.h"
#include <stdio.h> /* For rng.h */
#include "rng.h"
int majorKey[tonesInOctave]={0,2,4,5,7,9,11};
int minorKey[tonesInOctave]={0,2,3,5,7,8,11}; // Harmonic minor
int toneTranspose[semitonesInOctave]={0,1,1,2,2,3,3,4,5,5,6,6}; // Amount to add to tone number (C, D, E, etc.) in each key
int keyNumAccidentals[semitonesInOctave]={0,5,2,3,4,1,6,1,4,3,2,5}; // Number of accidentals in each key
char* keyAccidentalType="#-#-#-##-#-#"; // Type of each key (sharp or flat)
int minToneTranspose[semitonesInOctave]={0,0,1,1,2,3,3,4,4,5,6,6};

inline int modTranspose(int theTranspose) { int r=(theTranspose+semitonesInOctave*2)%semitonesInOctave; if (r>semitonesInOctave/2) r-=semitonesInOctave; return(r); }
Key Key::getRelatedKey(RelatedKeyType rel) const {
	Key*k;
	switch(rel) {
		case RK_RELATIVE:
			k=new Key((isMajor()==TRUE)?FALSE:TRUE,modTranspose((isMajor()==TRUE)?getTranspose()-3:getTranspose()+3));
			break;
		case RK_DOMINANT:
			k=new Key(isMajor(),modTranspose(getTranspose()+7));
			break;
		case RK_SUBDOMINANT:
			k=new Key(isMajor(),modTranspose(getTranspose()+5));
			break;
/*		case RK_ENHARMONIC:
			k=new Key((isMajor()==TRUE)?FALSE:TRUE,getTranspose());
			break;*/
	}
	Key rVal=*k; delete k; return(rVal);
}

Boolean Key::containsSemitone(int semitone) const {
	semitone-=getTranspose();
	for (int lp=0; lp<tonesInOctave; lp++) if (semitone==getArray(lp)) return(TRUE);
	return(FALSE);
}

void Key::printReportTo(FILE* file) const {
	// If change this output, change getReportLength also
	char tt=(isMajor()?toneTranspose:minToneTranspose)[getMajModTranspose()]+'C'; if (tt>'G') tt-=tonesInOctave;
	fprintf(file,"%c%c%s",tt,(isMajor()?" b b  # b b ":" # #  # # b ")[getMajModTranspose()],isMajor()?"major":"minor");
}

/*
	transpose	key		number	tone
	0			C		0		0
	1			Db		5b		1
	2			D		2#		1
	3			Eb		3b		2
	4			E		4#		2
	5			F		1b		3
	6			F#		6#		3
	7			G		1#		4
	8			Ab		4b		5
	9			A		3#		5
	10			Bb		2b		6
	11			B		5#		6
*/