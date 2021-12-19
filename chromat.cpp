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
#ifndef TSR_VERSION
#include "chord.h"
void flatten(char&c);
void sharpen(char&c);
void Chord::changeChromaticAccidental(char &accidental,Part whichPart) const {
	Figure fig=getFigure(); NoteOfChord noteOfChord=getNoteOfChord(whichPart);
	Figure nextFig=fig; if (theNextChord) nextFig=theNextChord->getFigureIn(getKey());
	// "Supertonic chromatic common chord", T Keighley Mus D FRCO etc 1914 p110
	// TODO Also if going to V7; see also RULES.CPP in this case, and make some choice between this and Neapolitan 6th
	if (fig==II && theNextChord && (nextFig==I || nextFig==II || nextFig==IV || nextFig==VII)) {
		if ((getKey().isMajor()==FALSE && (noteOfChord==N_FIVE1 || noteOfChord==N_FIVE2))
		|| noteOfChord==N_THREE1 || noteOfChord==N_THREE2)
			sharpen(accidental);
	// "Major chord on minor 2nd of scale" (p112) (1st inversion known as Neapolitan 6th)
	} else if (fig==II && theNextChord && (nextFig==I || nextFig==V) && getInversion()!=ISECOND) {
		if ((getKey().isMajor()==TRUE && (noteOfChord==N_FIVE1 || noteOfChord==N_FIVE2))
		|| noteOfChord==N_ONE1 || noteOfChord==N_ONE2)
			flatten(accidental);
	// "Diatonic Triads in the Minor Key used as Chromatic Triads in the Major Key" (p113)
	} else if (getPart(whichPart).getDegreeOfScale()==SUBMEDIANT && getKey().isMajor()==TRUE)
		flatten(accidental);
	// Flatterned dominant - this is one of mine
	else if (getPart(whichPart).getDegreeOfScale()==LEADING_NOTE && getKey().isMajor()==TRUE && fig==V)
		flatten(accidental);
}

void Chord::doChromaticUnessentials(char &accidental,const Note &note,const Note &before,const Note &after) const {
	if ((note.isToneAwayFrom(before)==TRUE && note.isEqualTo(after)==TRUE) // Unaccented chromatic passing note
	|| (note.isToneAwayFrom(after)==TRUE && before.isEqualTo(after)==TRUE)) { // Chromatic auxilliary note
		// Can push it one semitone in direction of before
		if (note.isHigherThan(before)==TRUE) flatten(accidental);
		else sharpen(accidental);
	}
}
#endif
#endif
