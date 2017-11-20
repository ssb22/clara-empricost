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