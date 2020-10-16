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
#ifndef SONATA_H
#define SONATA_H
#include "minuet.h"
#include "sequence.h"
#include "key.h"
#include <stdio.h>
#define SONATA_TIME 4
#define SONATA_ANACRUSIS 0 /* The code will require changing if anything else */
#define BRIDGE_BARS 3
#define CODETTA_BARS 4
#define SHORT_BRIDGE_BARS 2
#define CODA_BARS 8
class Sonata {
public:
	Sonata(Key key,int barsInPhrase);
	~Sonata();
	void outputToMwr(Mwr &mwr,Part part);
protected:
	Melody* theSettingKey,*theOtherSettingKey,*theBridge,*theShortBridge,*theCodetta,*theCoda;
	Sequence* theDevelopment1,*theDevelopment2;
	Minuet* theSubj1A,*theSubj1B,*theSubj2;
	const Key theInitKey,theRelatedKey;
};
#endif