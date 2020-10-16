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