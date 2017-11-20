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
#include "note.h"
Note::Note(DegreeOfScale degree,Octave octave,Key key) : theKey(key) {
	theDegreeOfScale=degree;
	theOctave=octave;
}
const Key majKey;
const Note undefinedNote(TONIC,(Octave)127,majKey);

#ifndef SETUP_ONLY_VERSION
Note::Note(const Note* note) : theKey(note->getKey()) {
	theDegreeOfScale=note->getDegreeOfScale();
	theOctave=note->getOctave();
}

Note* Note::increment() {
	if (theDegreeOfScale==LEADING_NOTE) theOctave++;
	theDegreeOfScale=(DegreeOfScale)(((int)theDegreeOfScale+1)%7);
	return(this);
}

Note* Note::decrement() {
	if (theDegreeOfScale==TONIC) { theOctave--; theDegreeOfScale=LEADING_NOTE; }
	else theDegreeOfScale=(DegreeOfScale)((int)theDegreeOfScale-1);
	return(this);
}

void Note::saveTo(FILE* file) const {
	theKey.saveTo(file);
	fwrite(&theDegreeOfScale,sizeof(theDegreeOfScale),1,file);
	fwrite(&theOctave,sizeof(theOctave),1,file);
}

Note::Note(FILE* file) : theKey(file) {
	fread(&theDegreeOfScale,sizeof(theDegreeOfScale),1,file);
	fread(&theOctave,sizeof(theOctave),1,file);
}

int Note::getSemitoneNumber() const {
	return(theKey.getTranspose()+theKey.getArray(theDegreeOfScale)+semitonesInOctave*theOctave);
}

void Note::initMwr(char* output) const {
	int element=theDegreeOfScale+theKey.getToneTranspose();
	while (element<0) element+=tonesInOctave; element%=tonesInOctave;
	output[0]="cdefgab"[element];
	output[1]='n'; output[2]=0;
	for (int lp=0,offset=(theKey.getAccidentalType()=='#')?('F'-'A'):('B'-'A'); lp<theKey.getNumAccidentals(); lp++,offset=(offset+((theKey.getAccidentalType()=='#')?sharpIncrement:flatIncrement))%tonesInOctave)
		if (offset==output[0]-'a') output[1]=theKey.getAccidentalType();
}

void Note::adjustToKey(KeyRef key) {
	int oldSemitones=getSemitoneNumber();
	theKey=key;
	while (getSemitoneNumber()>oldSemitones) decrement();
	while (getSemitoneNumber()<oldSemitones) increment();
}

Boolean Note::isToneAwayFrom(const Note &note) const {
	if (intervalWith(note).getValue()!=i_second) return(FALSE);
	int s1=getSemitoneNumber(),s2=note.getSemitoneNumber();
	return(((s1-s2==2) || (s1-s2==-2))?TRUE:FALSE);
}
#endif