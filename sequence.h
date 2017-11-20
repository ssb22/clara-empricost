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
#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "melody.h"
#include "key.h"
#include <stdio.h>
// Note: A 1-beat anacrusis is assumed, but the final bar is filled
class Sequence {
public:
	Sequence(Key origKey,Key finalKey,NumBeats beatsPerBar,Boolean willAddChr);
	~Sequence();
	void outputToMwr(Mwr &mwr,int end=0);
protected:
	Melody* theMelody;
	const Key theInitKey,theFinalKey;
	const Boolean doAddChr;
	RelatedKeyType theSeqType;
};
#endif