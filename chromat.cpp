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
#ifndef TSR_VERSION
#include "chord.h"
void flattern(char&c);
void sharpen(char&c);
void Chord::changeChromaticAccidental(char &accidental,Part whichPart) const {
	Figure fig=getFigure(); NoteOfChord noteOfChord=getNoteOfChord(whichPart);
	Figure nextFig=fig; if (theNextChord) nextFig=theNextChord->getFigureIn(getKey());
	// "Supertonic chromatic common chord", T Keighley Mus D FRCO etc 1914 p110
	// NEEDATTENTION Also if going to V7; see also RULES.CPP in this case, and make some choice between this and Neapolitan 6th
	if (fig==II && theNextChord && (nextFig==I || nextFig==II || nextFig==IV || nextFig==VII)) {
		if ((getKey().isMajor()==FALSE && (noteOfChord==N_FIVE1 || noteOfChord==N_FIVE2))
		|| noteOfChord==N_THREE1 || noteOfChord==N_THREE2)
			sharpen(accidental);
	// "Major chord on minor 2nd of scale" (p112) (1st inversion known as Neapolitan 6th)
	} else if (fig==II && theNextChord && (nextFig==I || nextFig==V) && getInversion()!=ISECOND) {
		if ((getKey().isMajor()==TRUE && (noteOfChord==N_FIVE1 || noteOfChord==N_FIVE2))
		|| noteOfChord==N_ONE1 || noteOfChord==N_ONE2)
			flattern(accidental);
	// "Diatonic Triads in the Minor Key used as Chromatic Triads in the Major Key" (p113)
	} else if (getPart(whichPart).getDegreeOfScale()==SUBMEDIANT && getKey().isMajor()==TRUE)
		flattern(accidental);
	// Flatterned dominant - this is one of mine
	else if (getPart(whichPart).getDegreeOfScale()==LEADING_NOTE && getKey().isMajor()==TRUE && fig==V)
		flattern(accidental);
}

void Chord::doChromaticUnessentials(char &accidental,const Note &note,const Note &before,const Note &after) const {
	if ((note.isToneAwayFrom(before)==TRUE && note.isEqualTo(after)==TRUE) // Unaccented chromatic passing note
	|| (note.isToneAwayFrom(after)==TRUE && before.isEqualTo(after)==TRUE)) { // Chromatic auxilliary note
		// Can push it one semitone in direction of before
		if (note.isHigherThan(before)==TRUE) flattern(accidental);
		else sharpen(accidental);
	}
}
#endif
#endif