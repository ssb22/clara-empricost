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