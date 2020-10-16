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
#ifndef SETUP_ONLY_VERSION
#include "interval.h"
#include "note.h"
#include "key.h"
inline int semDif(int toneDif,KeyRef key) {
	if (toneDif<0)
		return(-key.getArray(-toneDif));
	else return(key.getArray(toneDif));
}

Interval::Interval(const Note &note1,const Note &note2) {
	Note n1=note1,n2=note2; n2.adjustToKey(n1.getKey());
	descending=FALSE;
	raised=FALSE;
	lowered=FALSE;
	if (n1.isHigherThan(n2)) { // But what about octaves?
		const Note temp=n1;
		n1=n2;
		n2=temp;
		descending=TRUE;
	} // Note 2 is now higher than note 1
	// Predict semitone difference if 1st note is root
	int semitoneDiff=semDif((int)n2.getDegreeOfScale()-(int)n1.getDegreeOfScale(),majKey)
	+semitonesInOctave*(n2.getOctave()-n1.getOctave());
	// Now find real semitone difference
	int realDiff=n2.getSemitoneNumber()-n1.getSemitoneNumber();
	if (realDiff>semitoneDiff) raised=TRUE;
	else if (realDiff<semitoneDiff) lowered=TRUE;
	theValue=(IntervalValue)((int)n2.getDegreeOfScale()-(int)n1.getDegreeOfScale()
	+tonesInOctave*((int)n2.getOctave()-(int)n1.getOctave()) // Get the octaves right
	+(int)i_unison);
}

Interval::Interval(IntervalValue val,Boolean raise,Boolean lower,Boolean firstHighest) {
	theValue=val;
	raised=raise;
	lowered=lower;
	descending=firstHighest;
}

Boolean Interval::isAugmented() const {
//	IntervalValue r=getRoundedValue();
	if (/*(r==i_fourth || r==i_fifth || r==i_second) &&*/ raised) return(TRUE);
	else return(FALSE);
}

Boolean Interval::isDiminished() const {
	IntervalValue r=getRoundedValue();
	if ((r==i_fourth || r==i_fifth || r==i_unison) && lowered) return(TRUE);
	else return(FALSE);
}

Boolean Interval::isPerfect() const {
	IntervalValue r=getRoundedValue();
	if ((r==i_fourth || r==i_fifth || r==i_unison) && !raised && !lowered)
		return(TRUE);
	else return(FALSE);
}

Boolean Interval::isMajor() const {
	IntervalValue r=getRoundedValue();
	if (r==i_fourth || r==i_fifth || r==i_unison || raised || lowered) return(FALSE);
	else return(TRUE);
}

Boolean Interval::isMinor() const {
	IntervalValue r=getRoundedValue();
	if (r==i_fourth || r==i_fifth || r==i_unison) return(FALSE);
	else if (lowered) return(TRUE);
	else return(FALSE);
}
#endif