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
