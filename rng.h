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
