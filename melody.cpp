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
#include "melody.h"
#include "chord.h"
#include "rng.h"
#include <stddef.h> // For NULL
#include <stdio.h>
#include <assert.h>
#include <iostream.h>
#include "protect.h"

#ifndef TSR_VERSION
extern Boolean newMelodiesIn68;
#endif
int Melody::nextMelodyNumber=0;

int useYourTimeUsefully();
char* getFilename(int number,Boolean complete);
char* getFilename2(char* fname);

void Melody::deleteAllFiles() {
	for (int lp=0; lp<nextMelodyNumber; lp++)
		deleteFile(getFilename(lp,TRUE));
}

PackOfCards* Melody::thePack=NULL;

#ifndef TSR_VERSION
Melody::Melody(NumBeats beatsPerBar,NumBeats anacrusis,KeyRef key,int numChords,int cadences,int imperfectEnd,int properStart,ModulateStatus canMod,Boolean canHavePassing,const Key* finishKey,Boolean willAddChr)
 : theKey(key), theFinishKey(finishKey?(*finishKey):key), theAddChrStatus(willAddChr),
 theAnacrusis(anacrusis), theCanModulate(canMod), canHaveUnessentials(canHavePassing),
 doNeedEndFinal(imperfectEnd?FALSE:TRUE), properStartStatus(properStart?TRUE:FALSE),
 theBeatsPerBar(beatsPerBar), theNumberOfChords(numChords), theNumberOfCadences(cadences),
 in68(newMelodiesIn68), theNumber(nextMelodyNumber++) {
	if (!thePack) thePack=new PackOfCards(packSize); else thePack->reShuffle();
	theFirstChord=theLastChord=NULL; isComplete=FALSE; chordLp=1;
	if (filenameMatching(getFilename(theNumber,TRUE)))
		cout << "Task " << theNumber << " was already completed" << endl;
	else if (!filenameMatching(getFilename(theNumber,isComplete))) {
		if (filenameMatching(getFilename2(getFilename(theNumber,isComplete)))) {
			cout << "Task " << theNumber << " had been incorrectly aborted; re-initialising from last recorded position" << endl;
			renameFile(getFilename2(getFilename(theNumber,isComplete)),getFilename(theNumber,isComplete));
		} else {
			cout << "Initialising task " << theNumber << endl;
			saveYourself();
		}
	} else cout << "Task " << theNumber << " was interrupted, can be resumed" << endl;
	scrambleRNG();
}
#endif

void Melody::saveYourself() const {
	char* c=getFilename2(getFilename(theNumber,isComplete));
	// Start with file of different name in case anyone tries to open it while we are saving
	// - NetWare lets you get away with murder
	FILE* file=fopen(c,"wb");
	makeAuthentic(file);
	saveTo(file); fclose(file);
	renameFile(c,getFilename(theNumber,isComplete));
}

#ifndef SETUP_ONLY_VERSION
Melody::Melody(FILE* file)
// Lots of initialisers so that the compiler doesn't complain
// (Note that we can't load from file here because the order of evaluation
// of the initialisers is liable to vary)
 : canHaveUnessentials(TRUE), doNeedEndFinal(TRUE), theBeatsPerBar((NumBeats)0),
 theAnacrusis((NumBeats)0), properStartStatus(FALSE), theCanModulate(MS_FALSE),
 theAddChrStatus(FALSE), theNumberOfChords(0), theNumberOfCadences(0),
 in68(FALSE), theNumber(0)
	{
	isComplete=FALSE; theFirstChord=theLastChord=NULL; chordLp=1; generate(file);
}
#endif

void Melody::saveTo(FILE* file) const {
	thePack->saveTo(file);
	saveRNG(file);
	fwrite(&canHaveUnessentials,sizeof(canHaveUnessentials),1,file);
	fwrite(&doNeedEndFinal,sizeof(doNeedEndFinal),1,file);
	fwrite(&theBeatsPerBar,sizeof(theBeatsPerBar),1,file);
	fwrite(&theAnacrusis,sizeof(theAnacrusis),1,file);
	theKey.saveTo(file); theFinishKey.saveTo(file);
	fwrite(&properStartStatus,sizeof(properStartStatus),1,file);
	fwrite(&theCanModulate,sizeof(theCanModulate),1,file);
	fwrite(&theAddChrStatus,sizeof(theAddChrStatus),1,file);
	fwrite(&theNumberOfChords,sizeof(theNumberOfChords),1,file);
	fwrite(&theNumberOfCadences,sizeof(theNumberOfCadences),1,file);
	fwrite(&theNumber,sizeof(theNumber),1,file);
	fwrite(&in68,sizeof(in68),1,file);
	fwrite(&theEvalLastChordStatus,sizeof(theEvalLastChordStatus),1,file);
#ifndef SETUP_ONLY_VERSION
	Chord* x=theFirstChord;
	while (x) {
		x->saveTo(file);
		x=x->getNextChord();
	}
#endif
}

#ifndef SETUP_ONLY_VERSION
void Melody::generate(FILE* loadFrom) {
	if (loadFrom) {
		if (!thePack) thePack=new PackOfCards(loadFrom); else thePack->reLoad(loadFrom);
		loadRNG(loadFrom);
		fread((void*)&canHaveUnessentials,sizeof(canHaveUnessentials),1,loadFrom);
		fread((void*)&doNeedEndFinal,sizeof(doNeedEndFinal),1,loadFrom);
		fread((void*)&theBeatsPerBar,sizeof(theBeatsPerBar),1,loadFrom);
		fread((void*)&theAnacrusis,sizeof(theAnacrusis),1,loadFrom);
		Key k1(loadFrom); Key k2(loadFrom); theKey=k1; theFinishKey=k2;
		fread((void*)&properStartStatus,sizeof(properStartStatus),1,loadFrom);
		fread((void*)&theCanModulate,sizeof(theCanModulate),1,loadFrom);
		fread((void*)&theAddChrStatus,sizeof(theAddChrStatus),1,loadFrom);
		fread((void*)&theNumberOfChords,sizeof(theNumberOfChords),1,loadFrom);
		fread((void*)&theNumberOfCadences,sizeof(theNumberOfCadences),1,loadFrom);
		fread((void*)&theNumber,sizeof(theNumber),1,loadFrom);
		fread((void*)&in68,sizeof(in68),1,loadFrom);
		fread((void*)&theEvalLastChordStatus,sizeof(theEvalLastChordStatus),1,loadFrom);
	} else {
		if (chordLp>theNumberOfChords) return;
		// thePack will always be initialised
	}
	if (chordLp==1) {
		if (theAnacrusis) theBeatsLeft=theBeatsPerBar-theAnacrusis; else theBeatsLeft=theBeatsPerBar;
		theFirstChord=theLastChord=NULL;
		theCadenceStatus=theFinalStatus=theEvalLastChordStatus=FALSE;
	} else if (!loadFrom)
		// In this case, we are generating after a load, and don't forget
		// that, just before the save, theLastChord was about to be told
		theLastChord->youAreNoGood();
	for (; chordLp<=theNumberOfChords; chordLp++) {
		if (chordLp==theNumberOfChords) nextChordIsFinalCadence();
		// Otherwise make on 3rd beat if 3, last but 1 if >3, 1st if 2
		// Bar number = (chordLp-theAnacrusis)/theBeatsPerBar+1
		// Total bars = (numChords-theAnacrusis)/theBeatsPerBar+1
		// Bar numbers for cadences: !(barNumber%(totalBars/cadences))
		// Beat of bar = chordLp-theAnacrusis
		// For chordLp read chordLp-1
		// So altogether we have:-
		else if (chordLp>theAnacrusis &&
		(!(((chordLp-1-theAnacrusis)/theBeatsPerBar+1)%(((theNumberOfChords-theAnacrusis)/theBeatsPerBar+1)/theNumberOfCadences)) && ((chordLp-theAnacrusis-1)%theBeatsPerBar)+1==((theBeatsPerBar==3)?3:theBeatsPerBar-1)))
			nextChordIsCadence();
		Chord* temp=loadChord(loadFrom,this,theLastChord);
		if (temp) theLastChord=temp;
		else {
			if (loadFrom) return;
			if (theLastChord) theLastChord=new Chord(undefinedNote,undefinedNote,undefinedNote,undefinedNote,this,theLastChord,(NumBeats)1,undefinedPoss,undefinedPoss,theLastChord->getKeyPtr());
			else theLastChord=new Chord(undefinedNote,undefinedNote,undefinedNote,undefinedNote,this,theLastChord);
		}
	}
#ifndef TSR_VERSION
	thePedalNote=NULL;
	if (canModulate()==FALSE) {
		Figure f1=theLastChord->getFigure(),f2=theFirstChord->getFigure();
		if (f1==V && (f2==I || f2==III || f2==V))
			thePedalNote=new Note(DOMINANT,PEDAL_OCTAVE,theKey);
		else if (f1==I && (f2==IV || f2==VI || f2==I))
			thePedalNote=new Note(TONIC,PEDAL_OCTAVE,theKey);
	}
#endif
	isComplete=TRUE;
}
#endif

Melody::~Melody() {
#ifndef SETUP_ONLY_VERSION
	if (theFirstChord) delete theFirstChord
#endif
	;
}

#ifndef SETUP_ONLY_VERSION
void Melody::addLength(NumBeats noteLen) {
	theCadenceStatus=FALSE;
	theBeatsLeft-=noteLen;
	if (theBeatsLeft<=0) theBeatsLeft+=theBeatsPerBar;
}

Strength Melody::strengthOfNextBeat() const {
	if (theBeatsLeft==theBeatsPerBar) return(S_1ST_BEAT);
	else if (theBeatsLeft*2==theBeatsPerBar || theBeatsLeft*3==theBeatsPerBar) return(S_3RD_BEAT);
	else if (theBeatsLeft*4==theBeatsPerBar) return(S_4TH_BEAT);
	else if (theBeatsLeft*4/3==theBeatsPerBar || theBeatsLeft*3/2==theBeatsPerBar) return(S_2ND_BEAT);
	else return(S_NOT_BEAT);
}

#ifndef TSR_VERSION
void Melody::outputToMwr(Mwr &mwr,int needToInitPart,int needToEndPart,const Key* transposeTo,Boolean addChromaticisms,NumBeats changeAnacrusis,Boolean mute) {
	while (isComplete==FALSE) {
		FILE* file;
		while ((file=fopen(getFilename(theNumber,TRUE),"rb"))==NULL || !authentic(file)) {
			if (file) { fclose(file); deleteFile(getFilename(theNumber,TRUE)); }
			if (!useYourTimeUsefully()) {
				cout << "Error - no tasks available to this workstation, waiting for " << theNumber << endl;
#ifndef TSR_VERSION
				if (aKeyIsPressed()) { // Exit without saving anything
#ifdef RUNNING_ON_DOS
				if (getch()=='Q') { // Stop the people pressing Escape!
#endif
				exit(0);
#ifdef RUNNING_ON_DOS
				}
#endif
			}
#endif
			}
		}
		generate(file); fclose(file);
	}
	if (needToInitPart) mwr.initPart(theBeatsPerBar);
	mwr.setIn68(in68);
	Key key=(transposeTo?(*transposeTo):theKey);
	mwr.setBeatsLeft((theAnacrusis?theAnacrusis:theBeatsPerBar)*2);
	if (needToInitPart || (key.isEqualTo(mwr.getKey())==FALSE && mwr.fullBarAhead())) mwr.setKey(key);
	int dot=0,d2=0; // d2 is part of 6/8 fix
	if (theAnacrusis && needToInitPart) {
		NumBeats anacrusis=theBeatsPerBar-theAnacrusis;
		while (anacrusis>=2) { mwr.setLen(2,d2); mwr.output("r",d2); anacrusis-=2; }
		if (anacrusis) { mwr.setLen(4,d2); mwr.output("r",d2); }
	}

	// Don't change theAnacrusis until here, because it is for leaving an anacrusis at the end of the piece
	NumBeats oldAnacrusis=theAnacrusis;
	// "Liberal" interpretation of const object, because will be changed back before the function is done
	if (changeAnacrusis) *((NumBeats*)(&theAnacrusis))=changeAnacrusis;

	Chord* chord=theFirstChord;
	int lastRetVal=0,loop=1,pedalBeatsLeft=0,firstTime=1; // firstTime is for setting beatsLeft to 0
	while (chord) {
		if (mwr.getPart()==P_PEDAL || mute==TRUE) {
			if (pedalBeatsLeft) pedalBeatsLeft--;
			else {
				char pedalNote[3]="r"; if (thePedalNote && mute==FALSE) {
					mwr.setOctave(/*thePedalNote->getMwrOctave()*/PEDAL_OCTAVE+OCT_TRANS_FOR_MWR); // NOT note.getMwrOctave
					Note note=*thePedalNote; // So any transposition is not kept
					if (transposeTo) note.transposeToKey(*transposeTo);
					note.initMwr(pedalNote);
				}
				int opbl=pedalBeatsLeft=mwr.getBeatsLeft()/2;
				if (!needToInitPart && oldAnacrusis && firstTime) {
					opbl=0; // Because previous Melody would have filled the bar
					// (Leave pedalBeatsLeft as it is to count down)
					mwr.setBeatsLeft(theBeatsPerBar*2); // To counteract setBeatsLeft above
					// (ie get ready for next bar)
				}
				firstTime=0;
				while (opbl>=4) { mwr.setLen(1,d2); mwr.output(pedalNote,d2); opbl-=4; mwr.subtractBeats(8/mwr.getLength(),NULL,(!(chord->getNextChord()) && needToEndPart==2)?TRUE:FALSE); }
				while (opbl>=2) { mwr.setLen(2,d2); mwr.output(pedalNote,d2); opbl-=2; mwr.subtractBeats(8/mwr.getLength(),NULL,(!(chord->getNextChord()) && needToEndPart==2)?TRUE:FALSE); }
				if (opbl) { mwr.setLen(4,d2); mwr.output(pedalNote,d2); mwr.subtractBeats(8/mwr.getLength(),NULL,(!(chord->getNextChord()) && needToEndPart==2)?TRUE:FALSE); }
				pedalBeatsLeft--;
			}
		} else lastRetVal=chord->outputToMwr(mwr,lastRetVal,dot,d2,loop,needToEndPart,transposeTo,addChromaticisms,(needToEndPart==2)?TRUE:FALSE);
		chord=chord->getNextChord();
	}
	if (needToEndPart) mwr.printDoubleBar();
	*((NumBeats*)(&theAnacrusis))=oldAnacrusis;
}
#endif
#endif