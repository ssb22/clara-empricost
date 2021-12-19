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
