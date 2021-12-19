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
#ifndef NOTE_H
#define NOTE_H
#include "degscl.h"
#include "octave.h"
#include "interval.h"
#include "boolean.h"
#include "key.h"
#include <stdio.h>
#define OCT_TRANS_FOR_MWR (-1)
class Note {
public:
	Note(DegreeOfScale degree,Octave octave,Key key);
	Note(const Note* note);
	Note(FILE* file);
	~Note() {};
	Note* increment();
	Note* decrement();
	DegreeOfScale setDegreeOfScale(DegreeOfScale degree);
	Octave setOctave(Octave octave);
	Note* set(DegreeOfScale degree,Octave octave);
	DegreeOfScale getDegreeOfScale() const;
	Octave getOctave() const;
	Octave getMwrOctave() const { return(getSemitoneNumber()/semitonesInOctave+OCT_TRANS_FOR_MWR); }
	int getSemitoneNumber() const;
	Interval intervalWith(const Note &note) const;
	Interval intervalWith(const Note* note) const;
	Boolean isToneAwayFrom(const Note &note) const;
	Boolean isHigherThan(const Note &note) const;
	Boolean isHigherThan(const Note* note) const;
	Boolean isEqualTo(const Note &note) const;
	Boolean isEqualTo(const Note* note) const;
	void saveTo(FILE* file) const;
	void adjustToKey(KeyRef key);
	void transposeToKey(KeyRef key) { theKey=key; }
	Key getKey() const { return(theKey); }
	void initMwr(char* output) const; // mwr is 2-byte: Note and accidental; defaults to appropriate key signature (ie no extras)
	Boolean isInKey(KeyRef key) const { return(key.containsSemitone(getSemitoneNumber()%semitonesInOctave)); }
protected:
	Key theKey;
	DegreeOfScale theDegreeOfScale;
	Octave theOctave;
};
extern const Key majKey;
extern const Note undefinedNote;

inline DegreeOfScale Note::getDegreeOfScale() const {
	return(theDegreeOfScale);
}

inline Octave Note::getOctave() const {
	return(theOctave);
}

inline DegreeOfScale Note::setDegreeOfScale(DegreeOfScale degree) {
	return(theDegreeOfScale=degree);
}

inline Octave Note::setOctave(Octave octave) {
	return(theOctave=octave);
}

inline Interval Note::intervalWith(const Note &note) const {
	return(intervalWith(&note));
}

inline Interval Note::intervalWith(const Note* note) const {
	Interval i(*this,*note);
	return(i);
}

inline Boolean Note::isHigherThan(const Note &note) const {
	return(isHigherThan(&note));
}

inline Boolean Note::isEqualTo(const Note &note) const {
	return(isEqualTo(&note));
}

inline Note* Note::set(DegreeOfScale degree,Octave octave) {
	setDegreeOfScale(degree);
	setOctave(octave);
	return(this);
}

inline Boolean Note::isHigherThan(const Note* note) const {
	if (getSemitoneNumber()>note->getSemitoneNumber()) return(TRUE);
	else return(FALSE);
}

inline Boolean Note::isEqualTo(const Note* note) const {
	if (note->getSemitoneNumber()==getSemitoneNumber()) return(TRUE);
	else return(FALSE);
}

#endif
