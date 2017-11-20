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
#include "sonata.h"

Sonata::Sonata(Key key,int barsInPhrase)
 : theInitKey(key), theRelatedKey(key.getRandomRelatedKey()) {
	theSettingKey=new Melody(SONATA_TIME,SONATA_ANACRUSIS,key,SONATA_TIME-1,1,1,1,MS_FALSE,FALSE); // I0
	theOtherSettingKey=new Melody(SONATA_TIME,SONATA_ANACRUSIS,key,SONATA_TIME-1,1,1,0,MS_FALSE,TRUE,NULL,TRUE); // I1
	theSubj1A=new Minuet(SONATA_TIME,SONATA_ANACRUSIS,key,barsInPhrase/2,TRUE,MS_FALSE,TRUE); // I2, I3, I4
	theSubj1B=new Minuet(SONATA_TIME,SONATA_ANACRUSIS,key,barsInPhrase/2,TRUE); // I5, I6, I7
	theBridge=new Melody(SONATA_TIME,SONATA_ANACRUSIS,key,SONATA_TIME*BRIDGE_BARS-1,1,1/*imperfect end*/,0/*proper start*/,MS_END,TRUE,&theRelatedKey); // I8
	if (key.isMajor()==FALSE) theSubj2=new Minuet(SONATA_TIME,SONATA_ANACRUSIS,key,barsInPhrase,TRUE); // I9, I10, I11
	else theSubj2=new Minuet(SONATA_TIME,SONATA_ANACRUSIS,theRelatedKey,barsInPhrase,TRUE); // (So we are prepared for the dreaded major/minor messup in the recapitualtion!)
	theCodetta=new Melody(SONATA_TIME,SONATA_ANACRUSIS,theRelatedKey,SONATA_TIME*(CODETTA_BARS-1)+1,1); // I12
	// SONATA_TIME didn't say *2 before
	theDevelopment1=new Sequence(theInitKey,theRelatedKey,SONATA_TIME*2,FALSE); // I13
	theDevelopment2=new Sequence(theRelatedKey,theInitKey,SONATA_TIME*2,TRUE); // I14
	theShortBridge=new Melody(SONATA_TIME,SONATA_ANACRUSIS,key,SONATA_TIME*SHORT_BRIDGE_BARS-1,1,1,0); // I15
	theCoda=new Melody(SONATA_TIME,SONATA_ANACRUSIS,key,SONATA_TIME*(CODA_BARS-1)+1,1); // I16
}

Sonata::~Sonata() {
	delete theCoda; delete theShortBridge;
	delete theDevelopment2; delete theDevelopment1;
	delete theCodetta; delete theSubj2; delete theBridge;
	delete theSubj1B; delete theSubj1A; delete theSettingKey;
}

#ifndef SETUP_ONLY_VERSION
void Sonata::outputToMwr(Mwr &mwr,Part part) {
	mwr.setPart(part);
	// Exposition : -
	theSettingKey->outputToMwr(mwr,1,0);
	mwr.writeComment("1st Subject");
	mwr.directOutput("["); // (End of repeat added by codetta)
	theSubj1A->outputToMwr(mwr,part,0); theSubj1B->outputToMwr(mwr,part,0);
	mwr.writeComment("Transition");
	theBridge->outputToMwr(mwr,0,0);
	mwr.writeComment("2nd Subject");
	theSubj2->outputToMwr(mwr,part,0,0,&theRelatedKey);
	mwr.writeComment("Codetta");
	theCodetta->outputToMwr(mwr,0,2);
	// Development : -
	mwr.writeComment("Start of development");
	theSettingKey->outputToMwr(mwr,0,0); theSubj1A->outputToMwr(mwr,part,0,0,NULL,TRUE);
	theOtherSettingKey->outputToMwr(mwr,0,0,NULL,TRUE,1); // Leave the anacrusis there this time
	mwr.writeComment("Sequences");
	theDevelopment1->outputToMwr(mwr); theDevelopment2->outputToMwr(mwr,1);
	// Recapitulation : -
	mwr.writeComment("Recapitulation");
	theSettingKey->outputToMwr(mwr,0,0);
	theSubj1A->outputToMwr(mwr,part,0); theSubj1B->outputToMwr(mwr,part,0);
	theShortBridge->outputToMwr(mwr,0,0);
	theSubj2->outputToMwr(mwr,part,0,0,&theInitKey);
	mwr.writeComment("Coda");
	theCoda->outputToMwr(mwr,0,1);
}
#endif
#endif