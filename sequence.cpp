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
#include "sequence.h"
#include <assert.h>
Sequence::Sequence(Key origKey,Key finalKey,NumBeats beatsPerBar,Boolean willAddChr)
 : theInitKey(origKey), theFinalKey(finalKey), doAddChr(willAddChr) {
	int maxCount=0;
	theSeqType=NUM_REL_KEY_TYPE;
	for (int seqType=0; seqType<(int)NUM_REL_KEY_TYPE; seqType++) /* if (seqType!=(int)RK_ENHARMONIC) */ {
		Key x=theInitKey; int count=0;
		do { count++;
			x=x.getRelatedKey((RelatedKeyType)seqType);
		} while (x.isEqualTo(theFinalKey)==FALSE && x.isEqualTo(theInitKey)==FALSE && count<50);
		// The 50 thing is to stop it crashing, since there are only 48 keys (or 24 depending on how you argue)
		if (count<50 && count>=maxCount && x.isEqualTo(theFinalKey)==TRUE) { maxCount=count; theSeqType=(RelatedKeyType)seqType; }
	}
	assert(theSeqType!=NUM_REL_KEY_TYPE); // Also remove theSeqType=NUM_REL_KEY_TYPE and the #include if removing this
	Key intermediateKey=theInitKey.getRelatedKey(theSeqType);
	theMelody=new Melody(beatsPerBar,1,theInitKey,beatsPerBar,1,0/*Imperfect end*/,0/*proper start*/,MS_TRUE,TRUE,&intermediateKey,willAddChr);
}

Sequence::~Sequence() {
	delete theMelody;
}

#ifndef SETUP_ONLY_VERSION
void Sequence::outputToMwr(Mwr &mwr,int end) {
	Key transposeTo=theInitKey;
	do {
		theMelody->outputToMwr(mwr,0,(transposeTo.getRelatedKey(theSeqType).isEqualTo(theFinalKey) && end)?1:0,&transposeTo,doAddChr);
		transposeTo=transposeTo.getRelatedKey(theSeqType);
	} while (transposeTo.isEqualTo(theFinalKey)==FALSE);
}
#endif
#endif