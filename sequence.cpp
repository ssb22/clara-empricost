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
