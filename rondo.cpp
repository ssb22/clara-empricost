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
#ifndef TSR_VERSION
#include "rondo.h"
Rondo::Rondo(NumBeats beatsPerBar,NumBeats anacrusis,Key key,int barsInPhrase,int numberOfEpisodes)
: theNumberOfEpisodes(numberOfEpisodes) {
	theEpisodes=new Minuet*[theNumberOfEpisodes];
	theEpisodes[0]=new Minuet(beatsPerBar,anacrusis,key,barsInPhrase,TRUE,MS_FALSE);
	for (int lp=1; lp<theNumberOfEpisodes; lp++)
		theEpisodes[lp]=new Minuet(beatsPerBar,(NumBeats)0,key.getRandomRelatedKey(),barsInPhrase,TRUE,MS_END);
}

Rondo::~Rondo() {
	for (int lp=0; lp<theNumberOfEpisodes; lp++) delete theEpisodes[lp];
	delete theEpisodes;
}

#ifndef SETUP_ONLY_VERSION
void Rondo::outputToMwr(Mwr &mwr,Part part) const {
	theEpisodes[0]->outputToMwr(mwr,part,1,0);
	for (int lp=1; lp<theNumberOfEpisodes; lp++) {
		theEpisodes[lp]->outputToMwr(mwr,part,/*0*/1,0);
		theEpisodes[0]->outputToMwr(mwr,part,/*0*/1,1);
	}
}
#endif
#endif