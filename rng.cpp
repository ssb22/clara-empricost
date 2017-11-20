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
	srand(r); unsigned or=r; r=rand(); if (r==or) r++; // Just in case!
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
	for (int lp=0; lp<theNumCards; lp++) theCards[lp]=lp;
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