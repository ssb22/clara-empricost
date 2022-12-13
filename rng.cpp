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
#include <stdio.h>
#include <stdlib.h>
#include "rng.h"
#include "fgetint.h"

#ifdef FAST_RANDOM
static unsigned randSeed=0;
static unsigned randomTable[FAST_RANDOM];
inline unsigned randomNumber() {
	return(randomTable[(++randSeed)%=FAST_RANDOM]);
}
void initRandom() {
	srand(0);
	for (int lp=0; lp<FAST_RANDOM; lp++) randomTable[lp]=rand();
}
#define rand() randomNumber()
#define srand(x) (randSeed=x)
#endif

static unsigned r;
unsigned origRandNoSeed;
unsigned RNGrandom(unsigned possibilities) {
#ifdef FAST_RANDOM
	return(randomNumber()%possibilities);
#else
	srand(r); unsigned lastR=r; r=rand(); if (r==lastR) r++; // Just in case!
	return(r%possibilities);
#endif
}

static unsigned pushed;
void pushRNG() {
	pushed=
#ifdef FAST_RANDOM
	randSeed
#else
	r
#endif
	;
}

void popRNG() {
#ifdef FAST_RANDOM
	randSeed
#else
	r
#endif
	=pushed;
}

void RNGseed(unsigned seed) { origRandNoSeed=r=seed; srand(seed); }

void saveRNG(FILE* file) {
#ifdef FAST_RANDOM
	fwrite(&randSeed,sizeof(randSeed),1,file);
#else
	fwrite(&r,sizeof(r),1,file);
#endif
	fwrite(&origRandNoSeed,sizeof(origRandNoSeed),1,file);
}

void loadRNG(FILE* file) {
#ifdef FAST_RANDOM
	fread(&randSeed,sizeof(randSeed),1,file);
#else
	fread(&r,sizeof(r),1,file);
#endif
	fread(&origRandNoSeed,sizeof(origRandNoSeed),1,file);
}

PackOfCards::PackOfCards(int numCards) : theNumCards(numCards) {
	theCards=new int[theNumCards];
	reShuffle();
}

void PackOfCards::reShuffle() {
	int lp; for (lp=0; lp<theNumCards; lp++) theCards[lp]=lp;
	for (lp=0; lp<theNumCards; lp++) {
		int swapWith=lp+RNGrandom(theNumCards-lp);
		int temp=theCards[lp]; theCards[lp]=theCards[swapWith];
		theCards[swapWith]=temp;
	}
}

PackOfCards::PackOfCards(FILE* file) : theNumCards(fgetInteger(file)) {
	theCards=new int[theNumCards];
	fread(theCards,sizeof(int),theNumCards,file);
}

void PackOfCards::reLoad(FILE* file) {
	fgetInteger(file); // Discard number of cards
	fread(theCards,sizeof(int),theNumCards,file);
}

void PackOfCards::saveTo(FILE* file) const {
	fwrite(&theNumCards,sizeof(theNumCards),1,file);
	fwrite(theCards,sizeof(int),theNumCards,file);
}
