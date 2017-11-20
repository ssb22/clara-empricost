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
#ifndef RNG_H
#define RNG_H
#include <stdio.h> /* For FILE */
unsigned RNGrandom(unsigned possibilities);
void RNGseed(unsigned seed);
void saveRNG(FILE* file);
void loadRNG(FILE* file);
void pushRNG();
void popRNG();
#define scrambleRNG() RNGrandom(1)
// Using templates is probably better (rather than *int* numCards)
class PackOfCards {
public:
	PackOfCards(int numCards); // Constructor will change RNG position
	PackOfCards(FILE* file);
	~PackOfCards() { delete theCards; }
	// maxPoss may be specified so that numCards is less than required to save memory for TSR version
	// (Keep consistent throughout versions so that save files can be interchanged)
	int getCard(int cardNo,int maxPoss) const {
		return(theCards[cardNo%theNumCards]*(maxPoss/theNumCards)+cardNo/theNumCards); }
	void saveTo(FILE* file) const;
	void reShuffle();
	void reLoad(FILE* file);
protected:
	int* theCards;
	const int theNumCards;
};
#endif