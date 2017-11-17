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
#ifndef INTERVAL_H
#define INTERVAL_H
#include "boolean.h"
class Note;
static const int semitonesInOctave=12;
#define tonesInOctave 7
typedef char IntervalValue;
static const IntervalValue i_unison=1,i_second=2,i_third=3,i_fourth=4,
						   i_fifth=5,i_sixth=6,i_seventh=7,i_octave=8,i_ninth=9;
#define isMajorKey(x) ((x).isMajor())
class Interval {
public:
	Interval(const Note &note1,const Note &note2);
	Interval(IntervalValue val,Boolean raise,Boolean lower,Boolean firstHighest);
	~Interval() {};
	Boolean isAugmented() const;
	Boolean isDiminished() const;
	Boolean isPerfect() const;
	Boolean isMajor() const;
	Boolean isMinor() const;
	Boolean isDescending() const;
	IntervalValue getValue() const;
	IntervalValue getRoundedValue() const;
protected:
	Boolean raised;
	Boolean lowered;
	Boolean descending;
	IntervalValue theValue;
};

inline IntervalValue Interval::getValue() const {
	return(theValue);
}

inline IntervalValue Interval::getRoundedValue() const {
	return((getValue()-i_unison)%tonesInOctave+i_unison);
}

inline Boolean Interval::isDescending() const {
	return(descending);
}
#endif