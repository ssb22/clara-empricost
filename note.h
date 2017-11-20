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