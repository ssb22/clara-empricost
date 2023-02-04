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
#ifndef SETUP_ONLY_VERSION
#include "chord.h"
#include <assert.h>
#include "rng.h"
#include "tsr.h"
#include "protect.h"

NoteOfChord ChordPoss::getSop(int possibility) {
	static int y=possChordDegrees*possOctaves;
	return((NoteOfChord)((possibility/possFigs)%y));
}

NoteOfChord ChordPoss::getAlt(int possibility) {
	static int x=possFigs*possChordDegrees*possOctaves,y=possChordDegrees*possOctaves;
	return((NoteOfChord)((possibility/x)%y));
}

NoteOfChord ChordPoss::getTen(int possibility) {
	static int x=possFigs*possChordDegrees*possOctaves*possChordDegrees*possOctaves;
	static int y=possChordDegrees*possOctaves;
	return((NoteOfChord)((possibility/x)%y));
}

NoteOfChord ChordPoss::getBas(int possibility) {
	static int x=possFigs*possChordDegrees*possOctaves*possChordDegrees*possOctaves*possChordDegrees*possOctaves;
	return((NoteOfChord)(possibility/x));
}

Chord::Chord(const Note &s,const Note &a,const Note &t,const Note &b,Melody* whichMelody,Chord* lastChord,NumBeats length,int possNo,int origPos/*,SuspendedStatusType suspendedStatus*/,Key* k)
: theLength(length), theSoprano(s), theAlto(a), theTenor(t), theBass(b) {
	revokeTime();
	theSuspendedStatus=/*suspendedStatus*/NO_SUSPENSIONS; theOrnament=ORN_NONE; theOrnPart=P_UNDEFINED;
	if (k) theKey=oldKey=*k; else theKey=oldKey=whichMelody->getKey();
	theMelody=whichMelody; possibilitiesEvaluated=0;
	theBeatStrength=theMelody->strengthOfNextBeat();
	theLastChord=lastChord; if (theLastChord) oldKey=theLastChord->getKey();
	if (theLastChord==NULL) theMelody->setFirstChord(this);
	else theLastChord->setNextChord(this);
	theCadenceStatus=theMelody->isNextChordCadence();
	theFinalChordStat=theMelody->isNextChordFinal();
	theMelody->addLength(theLength);
	theNextChord=NULL;
	if (possNo==undefinedPoss) {
		theUnmappedPossibility=origVal=RNGrandom(numPossibilities);
		chooseAPossibility(theUnmappedPossibility);
	} else {
		// Loading from file
		theUnmappedPossibility=possNo; origVal=origPos;
		theChosenPossibility=getPack()->getCard(theUnmappedPossibility,numPossibilities); calculateFigure();
		display();
	}
#ifndef TSR_VERSION
	thePassingNotes[0]=thePassingNotes[1]=NULL;
	havePassingNotes[0]=havePassingNotes[1]=P_UNDEFINED;
	if (theLastChord && theFinalChordStat) { theLastChord->selectSuspensions(); if (theMelody->doesHaveUnessentials()) theLastChord->selectPassNotes(); }
#endif
}

Chord* loadChord(FILE* file,Melody* whichMelody,Chord* lastChord) {
	NumBeats length; int possNo,origPos; //SuspendedStatusType suspendedStatus;
	if (file) {
		Note s(file),a(file),t(file),b(file);
		if (feof(file) || ferror(file) || !fread(&length,sizeof(length),1,file)) return(NULL);
		fread(&possNo,sizeof(possNo),1,file);
		fread(&origPos,sizeof(origPos),1,file);
//		fread(&suspendedStatus,sizeof(suspendedStatus),1,file);
		Key k=Key(file);
		return(new Chord(s,a,t,b,whichMelody,lastChord,length,possNo,origPos/*,suspendedStatus*/,&k));
	} else return(NULL);
}

void Chord::saveTo(FILE* file) const {
	theSoprano.saveTo(file); theAlto.saveTo(file);
	theTenor.saveTo(file); theBass.saveTo(file);
	fwrite(&theLength,sizeof(theLength),1,file);
	fwrite(&theUnmappedPossibility,sizeof(theUnmappedPossibility),1,file);
	fwrite(&origVal,sizeof(origVal),1,file);
//	fwrite(&theSuspendedStatus,sizeof(theSuspendedStatus),1,file);
	theKey.saveTo(file);
}

Chord::~Chord() {
	delPassNotes();
	if (theNextChord) delete theNextChord;
//	if (theLastChord) theLastChord->setNextChord(/*theNextChord*/NULL);
}

void Chord::delPassNotes() {
#ifndef TSR_VERSION
	if (thePassingNotes[0]) delete thePassingNotes[0];
	if (thePassingNotes[1]) delete thePassingNotes[1];
	thePassingNotes[0]=thePassingNotes[1]=NULL;
	havePassingNotes[0]=havePassingNotes[1]=P_UNDEFINED;
	accentPassNotes=FALSE;
#else
	;
#endif
}

Inversion Chord::getInversion() const {
	switch(ChordPoss::getBas(theChosenPossibility)) {
		case N_ONE1: case N_ONE2: return(IROOT);
		case N_THREE1: case N_THREE2: return(IFIRST);
		case N_FIVE1: case N_FIVE2: return(ISECOND);
		default: return(IUNDEFINED);
	}
}

#ifdef RUNNING_ON_DOS
#ifndef TSR_VERSION
#include <dir.h>
#include <process.h>
void checkStop() {
	struct ffblk ffblk;
	if (!findfirst("P:\\NEWS\\STOPCOMP.FIL",&ffblk,0)) {
		deleteFile("P:\\NEWS\\STOPCOMP.FIL");
		fcloseall(); deleteFile("COMPOS.LOD"); deleteFile("COMPOS.SAV");
		execv(_argv[0],_argv);
	}
}
void (*backgroundComposFunc)()=checkStop; // Can be adjusted for processing adventure messages
// in the background while composing at the same time
#endif
#endif

int Chord::findSomePossibility() {
	int ip=0,added=0;
	while (!ip && (theUnmappedPossibility!=origVal || possibilitiesEvaluated<2)) {
		revokeTime();
#ifdef TSR_VERSION
		if (needsToRemoveTSR) return(ip/*0*/);
#endif
		if (added) theUnmappedPossibility=(theUnmappedPossibility+1)%numPossibilities;
		theChosenPossibility=getPack()->getCard(theUnmappedPossibility,numPossibilities); calculateFigure();
		ip=isPossible();
		possibilitiesEvaluated++; added=1;
	} if (theUnmappedPossibility==origVal && possibilitiesEvaluated>1) ip=0;
#ifdef RUNNING_ON_DOS
#ifndef TSR_VERSION
	if (backgroundComposFunc) backgroundComposFunc();
#endif
#endif
	return(ip);
}

void Chord::chooseAPossibility(int startFrom) {
//	delPassNotes();
	char again=1; theUnmappedPossibility=startFrom;
	do {
		theKey=oldKey;
		if (!findSomePossibility()) {
			// Keep the "exit" code here (don't move it anywhere else)
			// or change MELODY.CPP
#ifdef TSR_VERSION
			if (needsToRemoveTSR) {
#else
			if (aKeyIsPressed()) { // If a key is pressed, save and exit
#ifdef RUNNING_ON_DOS
			if (getch()=='Q') { // Stop the people pressing Escape!
#endif
#endif
				// I never existed, honest!
				// (NB This means that this chord will not be deleted; however,
				// since the program is about to exit and all allocated memory
				// freed, this will not matter)
				if (theLastChord==NULL) theMelody->setFirstChord(NULL);
				else theLastChord->setNextChord(NULL);
				statusReport("Saving unfinished task");
				theMelody->saveYourself();
#ifdef TSR_VERSION
				while(1) { needsToRemoveTSR=0; revokeTime(); }
#else
				exit(0);
#endif
#ifdef RUNNING_ON_DOS
#ifndef TSR_VERSION
			}
#endif
#endif
			}
			if (theLastChord) {
				theLastChord->youAreNoGood();
				oldKey=theLastChord->getKey(); // theKey assigned at the beginning
				possibilitiesEvaluated=0; // origVal=theUnmappedPossibility; // Last statement not needed - it is anyway
			}
			else {
				statusReport("Fatal error: Unable to find solution");
#ifdef TSR_VERSION
				while(1) { needsToRemoveTSR=0; revokeTime(); }
#else
				printf("Error occured on addition of chord %d of %d\n",theMelody->getChordLp(),theMelody->getNumChords());
				exit(0);
#endif
			}
		} else {
			again=0;
			if (theMelody->canModulate()==TRUE && (isUpbeat() || theFinalChordStat) && theLastChord && theLastChord->getLastChord() && theLastChord->getKey().isEqualTo(theLastChord->getLastChord()->getKey())==TRUE
			&& (theMelody->evalLastChordYet()==FALSE || theKey.isEqualTo(theMelody->getDestinationKey())==FALSE)) {
				int transpose=RNGrandom(semitonesInOctave)-semitonesInOctave/2/*+1*/; int startTrans=transpose,breakout=0;
				for (int done=0; (transpose!=startTrans || !done) && !breakout; done=1,transpose=((transpose+semitonesInOctave/2)+1)%semitonesInOctave-semitonesInOctave/2) {
					for (Boolean majKey=RNGrandom(2)?TRUE:FALSE,c=FALSE; c<=TRUE; majKey=(Boolean)(!majKey),c=(Boolean)(c+1)) {
						Key k(majKey,transpose);
						if (k.isEqualTo(theKey)==FALSE && modulationIsFineV(k)==TRUE) {
							breakout=1; theKey=k; calculateFigure(); break;
						}
						// else theKey=oldKey;
					}
				}
			}
			// If we put || theMelody->evalLastChordYet(), takes back entire melody looking for prepared place to modulate which does not exist, then exits
			if ((theFinalChordStat || (isNextChordFinal() && theMelody->canModulateAtEnd()==FALSE)) && theKey.isEqualTo(theMelody->getDestinationKey())==FALSE) {
				theMelody->lastChordEval(); // youAreNoGood();
				// Code for youAreNoGood expanded in order to prevent a stack overflow
				if (theKey.isEqualTo(oldKey)==FALSE && modulationIsFineV(theMelody->getDestinationKey())==TRUE)
					{ theKey=theMelody->getDestinationKey(); calculateFigure(); }
				else if (oldKey.isEqualTo(theMelody->getDestinationKey())==TRUE) { theKey=oldKey; calculateFigure(); }
				else { oldKey=theLastChord->getKey(); theUnmappedPossibility=(theUnmappedPossibility+1)%numPossibilities; again=1; }
			} if (!again) display();
		}
	} while (again);
}

Note Chord::getPart(Part part) const {
	switch(part) {
		case P_SOP: return(getSoprano());
		case P_ALT: return(getAlto());
		case P_TEN: return(getTenor());
		case P_BAS: return(getBass());
		default: return(undefinedNote);
	}
}

Note Chord::getSoprano() const {
	return(realNote(ChordPoss::getSop(theChosenPossibility),SOP_OCTAVE,getFigure(),sopIsSuspended()));
}

Note Chord::getAlto() const {
	return(realNote(ChordPoss::getAlt(theChosenPossibility),ALT_OCTAVE,getFigure(),altIsSuspended()));
}

Note Chord::getTenor() const {
	return(realNote(ChordPoss::getTen(theChosenPossibility),TEN_OCTAVE,getFigure(),tenIsSuspended()));
}

Note Chord::getBass() const {
	return(realNote(ChordPoss::getBas(theChosenPossibility),BAS_OCTAVE,getFigure(),basIsSuspended()));
}

Boolean Chord::isPartSuspended(Part part) const {
	switch(part) {
		case P_SOP: return(sopIsSuspended()?TRUE:FALSE);
		case P_ALT: return(altIsSuspended()?TRUE:FALSE);
		case P_TEN: return(tenIsSuspended()?TRUE:FALSE);
		case P_BAS: return(basIsSuspended()?TRUE:FALSE);
		default: return(FALSE);
	}
}

Note Chord::realNote(NoteOfChord note,Octave octave,Figure figure,int addOne) const {
	DegreeOfScale deg;
	switch(note) {
		case N_ONE2: octave++; /* fall through */ case N_ONE1: deg=(DegreeOfScale)figure; break;
		case N_THREE2: octave++; /* fall through */ case N_THREE1: if (figure+incThird>=possFigs) octave++; deg=(DegreeOfScale)((figure+incThird)%possFigs); break;
		case N_FIVE2: octave++; /* fall through */ case N_FIVE1: if (figure+incFifth>=possFigs) octave++; deg=(DegreeOfScale)((figure+incFifth)%possFigs); break;
//		default: printf("Note=%d\n",note); assert(0);
    default: ;
	}
	if (((DegreeOfScale)((deg+(addOne!=0))%possFigs))<deg) octave++;
	deg=(DegreeOfScale)((deg+(addOne!=0))%possFigs);
	Note returnVal(deg,octave,getKey());
	return(returnVal);
}

Interval Chord::getIntBetween(Part p1,Part p2) const {
	Interval i(getPart(p1),getPart(p2));
	return(i);
}

Interval Chord::getSAInt() const {
	Interval i(getSoprano(),getAlto());
	return(i);
}

Interval Chord::getSTInt() const {
	Interval i(getSoprano(),getTenor());
	return(i);
}

Interval Chord::getSBInt() const {
	Interval i(getSoprano(),getBass());
	return(i);
}

Interval Chord::getATInt() const {
	Interval i(getAlto(),getTenor());
	return(i);
}

Interval Chord::getABInt() const {
	Interval i(getAlto(),getBass());
	return(i);
}

Interval Chord::getTBInt() const {
	Interval i(getTenor(),getBass());
	return(i);
}

int Chord::getNumThirds(NoteOfChord n1,NoteOfChord n2) const {
	return((ChordPoss::getSop(theChosenPossibility)==n1 || ChordPoss::getSop(theChosenPossibility)==n2)
	+(ChordPoss::getAlt(theChosenPossibility)==n1 || ChordPoss::getAlt(theChosenPossibility)==n2)
	+(ChordPoss::getTen(theChosenPossibility)==n1 || ChordPoss::getTen(theChosenPossibility)==n2)
	+(ChordPoss::getBas(theChosenPossibility)==n1 || ChordPoss::getBas(theChosenPossibility)==n2));
}

NoteOfChord Chord::getNoteOfChord(Part part) const {
	switch(part) {
		case P_SOP: return(ChordPoss::getSop(theChosenPossibility));
		case P_ALT: return(ChordPoss::getAlt(theChosenPossibility));
		case P_TEN: return(ChordPoss::getTen(theChosenPossibility));
		// Next changed to default because the compiler complained about function not returning value
		/*case P_BAS:*/default: return(ChordPoss::getBas(theChosenPossibility));
//		default: printf("part=%d\n",part); return(N_UNDEFINED);
	}
}

Boolean Chord::isMajorTriad() const {
	Interval i(realNote(N_ONE1,0,getFigure()),realNote(N_THREE1,0,getFigure()));
	return(i.isMajor());
}

Boolean Chord::isDiminishedTriad() const {
	Interval i(realNote(N_ONE1,0,getFigure()),realNote(N_FIVE1,0,getFigure()));
	return(i.isDiminished());
}

Note Chord::getPartOrPassNote(Part part) const {
	if (havePassingNotes[0]==part) return(*(thePassingNotes[0]));
	else if (havePassingNotes[1]==part) return(*(thePassingNotes[1]));
	else return(getPart(part));
}

Note Chord::getPassNote(Part part) const {
	if (havePassingNotes[0]==part) return(*(thePassingNotes[0]));
	else if (havePassingNotes[1]==part) return(*(thePassingNotes[1]));
	else return(undefinedNote);
}

#include <stdio.h>
#include <string.h>

#ifndef TSR_VERSION
static const char* suspensionText[]={"","(S susp)","(A susp)","(T susp)","(B susp)",
"(S/A susp)","(A/T susp)","(T/B susp)"};

void Chord::printReportTo(FILE* file) const {
	if (theLastChord && getBeatStrength()!=S_1ST_BEAT) theLastChord->printReportTo(file);
	static char passNoteString[50]; passNoteString[0]=0;
	if (havePassingNotes[0]!=P_UNDEFINED || havePassingNotes[1]!=P_UNDEFINED) {
		snprintf(passNoteString,sizeof(passNoteString),"(Unessential in %c","SATB?"[havePassingNotes[0]]);
		if (nextNeedsToAccent(havePassingNotes[0])==TRUE) strcat(passNoteString,"(accented)");
		if (havePassingNotes[1]!=P_UNDEFINED) {
			strcat(passNoteString,"/");
			strcat(passNoteString,"*"); passNoteString[strlen(passNoteString)-1]="SATB?"[havePassingNotes[1]];
			if (nextNeedsToAccent(havePassingNotes[1])==TRUE) strcat(passNoteString,"(accented)");
		} strcat(passNoteString,")");
	}
	fprintf(file,"%c%c%s%s%s ",
		"1234567?"[getFigure()],
		"abc?"[getInversion()],
		(isLastOfCadence()==TRUE)?"(cad)":"",
		suspensionText[theSuspendedStatus],
		passNoteString);
	if (theLastChord) {
		if (getKey().isEqualTo(theLastChord->getKey())==FALSE) {
			fprintf(file,"- Modulating to ");
			getKey().printReportTo(file);
		}
	} else getKey().printReportTo(file);
}
void flatten(char&c) { if (c=='#') c='n'; else c='-'; }
void sharpen(char&c) { if (c=='-') c='n'; else c='#'; }

int Chord::outputToMwr(Mwr &mwr,int extnOfLast,int &dot,int &d2,int &loop,int needToEndPart,const Key* transposeTo,Boolean addChromaticisms,Boolean doRepeatEnd) const {
	if (!extnOfLast) {
		loop=1;
		if ((!getPassNote(mwr.getPart()).isEqualTo(undefinedNote) && nextNeedsToAccent(mwr.getPart())==FALSE)) {
			if (theOrnPart==mwr.getPart() && theOrnament==ORN_DAGATA) mwr.setLen(16,d2);
			else mwr.setLen(8,d2);
			loop=2;
			if (theOrnament==ORN_SKIP && theOrnPart==mwr.getPart()) dot=1;
		} else if ((theLastChord && theLastChord->nextNeedsToAccent(mwr.getPart())==TRUE)) {
			if (theOrnPart==mwr.getPart() && (theOrnament==ORN_SKIP || theOrnament==ORN_DAGATA)) mwr.setLen(16,d2);
			else mwr.setLen(8,d2);
			loop=2;
		} else if (getPassNote(mwr.getPart()).isEqualTo(undefinedNote) && getNextChord() && getBeatStrength()>=getNextChord()->getBeatStrength() && mwr.getBeatsLeft()>2 && getPart(mwr.getPart()).isEqualTo(getNextChord()->getPart(mwr.getPart()))) {
			if (getNextChord()->getPassNote(mwr.getPart()).isEqualTo(undefinedNote)) { mwr.setLen(2,d2); return(1); }
			else if (!theMelody->isIn68()) {
				mwr.setLen(4,d2);
				// @@@ If d2, crotchet tied to semiquaver going to another semiquaver; this is limited implementation
				dot=1; loop=2;
				if (d2) { dot=0; d2=0; }
				return(1);
			} else mwr.setLen(4,d2);
		} else if (!getNextChord() && mwr.getBeatsLeft()/2-theMelody->getAnacrusis()>1) {
			if (mwr.getBeatsLeft()/2-theMelody->getAnacrusis()==2) mwr.setLen(2,d2); else if (mwr.getBeatsLeft()/2-theMelody->getAnacrusis()==4) mwr.setLen(1,d2);
			else { mwr.setLen(2,d2); dot=1; }
		} else mwr.setLen(4,d2);
	}
	char loopedBefore=0;
	while (loop) {
		Note* theNote;
		if (theLastChord && theLastChord->nextNeedsToAccent(mwr.getPart())==TRUE) {
			if (!loopedBefore) { Note n=theLastChord->getPartOrPass(1,mwr.getPart()); theNote=new Note(&n); }
			else { Note n=getPart(mwr.getPart()); theNote=new Note(&n); }
		} else theNote=new Note(getPartOrPass(loopedBefore,mwr.getPart()));
		if (transposeTo) theNote->transposeToKey(*transposeTo);
		char output[3]; theNote->initMwr(output);
		// By default, exactly as key signature for appropriate key
		if ((loopedBefore && theLastChord && theLastChord->nextNeedsToAccent(mwr.getPart())==FALSE && theNote->intervalWith(getPart(mwr.getPart())).getValue()==i_second)
		|| (loop==2 && theLastChord && theLastChord->nextNeedsToAccent(mwr.getPart())==TRUE)) {
			// Leading note not sharpened as a passing note - don't need to bother - UNLESS next note is higher
			// Submediant sharpened as a passing note (NB NOT if going down)
			if ((theNote->getDegreeOfScale()==SUBMEDIANT || theNote->getDegreeOfScale()==LEADING_NOTE) && theNote->getKey().isMajor()==FALSE && theNote->isHigherThan((loop==1?getNextChord():this)->getPart(mwr.getPart()))==FALSE)
				sharpen(output[1]);
			// Auxillary notes below the 5th are sharpened
			if (theNote->getDegreeOfScale()==SUBDOMINANT && (loop==1?this:getLastChord())->getPart(mwr.getPart()).getDegreeOfScale()==DOMINANT && (loop==1?getNextChord():this)->getPart(mwr.getPart()).getDegreeOfScale()==DOMINANT)
				sharpen(output[1]);
			if (addChromaticisms==TRUE) doChromaticUnessentials(output[1],theNote,(loop==1?this:getLastChord())->getPart(mwr.getPart()),(loop==1?getNextChord():this)->getPart(mwr.getPart()));
		} else {
			// Sharpen leading note and Tierce de Picadie
			if (((theNote->getDegreeOfScale()==LEADING_NOTE) || (theNote->getDegreeOfScale()==MEDIANT && !getNextChord() && theMelody->needToEndFinal()==TRUE)) && theNote->getKey().isMajor()==FALSE) sharpen(output[1]);
			// Submediant not sharpened - don't need to bother
			if (addChromaticisms==TRUE) changeChromaticAccidental(output[1],mwr.getPart());
		}
		mwr.setOctave(theNote->getMwrOctave()-(theNote->getDegreeOfScale()==LEADING_NOTE&&!strcmp(output,"b#"))); // bug workaround (key.cpp assumes harmonic minor, so Note will already have set b# in getSemitoneNumber which means getMwrOctave returns 1 too high for leading note in C# minor)
		for (int rptLp=0; rptLp<1+(mwr.getLength()==16 && theOrnPart==mwr.getPart() && (theOrnament==ORN_DAGATA || theOrnament==ORN_TADAGA)); rptLp++) {
			int oldDot=dot; dot+=d2; mwr.output(output,dot); dot=oldDot; d2=0;
			if (!loopedBefore && theLastChord && theLastChord->isPartSuspended(mwr.getPart())) mwr.directOutput("=+"); // Mordents on resolutions
			else if (!loopedBefore && theOrnament==ORN_TRILL && theOrnPart==mwr.getPart()) mwr.directOutput("==");
		}
		// Dotted quaver to semiquaver or vice versa: Semiquaver adds quaver, dot adds nothing (due to rounding down)
		// Quaver 2 semis or vice versa: 2 semis add quaver
		mwr.subtractBeats(8/((mwr.getLength()==16)?8:mwr.getLength()),this,(!theNextChord) && doRepeatEnd);
		if (dot) { mwr.subtractBeats(4/mwr.getLength(),this,(!theNextChord) && doRepeatEnd); dot=0; }
		if (loop==2) {
			if (!getNextChord() && mwr.getBeatsLeft()-theMelody->getAnacrusis()*2>1) { // More than a quaver left
				switch(mwr.getBeatsLeft()-theMelody->getAnacrusis()*2) {
					case 1: mwr.setLen(8,d2); break;
					case 2: mwr.setLen(4,d2); break;
					case 3: mwr.setLen(4,d2); dot=1; break;
					case 5: mwr.setLen(8,d2); mwr.output("r",d2); mwr.subtractBeats(8/mwr.getLength(),this,(!theNextChord) && doRepeatEnd); // fall through
					case 4: mwr.setLen(2,d2); break;
					case 7: mwr.setLen(8,d2); mwr.output("r",d2); mwr.subtractBeats(8/mwr.getLength(),this,(!theNextChord) && doRepeatEnd); // fall through
					case 6: mwr.setLen(2,d2); dot=1; break;
					case 8: mwr.setLen(1,d2); break;
					default: mwr.writeComment("Error in deciding final note length *****");
				}
			} else if (theOrnament==ORN_SKIP && theOrnPart==mwr.getPart()) {
				if (mwr.getLength()==8) mwr.setLen(16,d2);
				else if (mwr.getLength()==16) { mwr.setLen(8,d2); dot=1; }
				else mwr.setLen(8,d2); // Is dotted crotchet to quaver, so ignore it
			} else if (theOrnament==ORN_TADAGA && theOrnPart==mwr.getPart()) mwr.setLen(16,d2);
			else mwr.setLen(8,d2);
		}
		loop--; delete theNote; loopedBefore=1;
	}
	if (!getNextChord() && mwr.getBeatsLeft()!=theMelody->getBeatsPerBar()*2 && needToEndPart) {
		d2=0;
		int x=mwr.getBeatsLeft()/2;
		if (x==4) mwr.setLen(1,d2);
		else if (x==2) mwr.setLen(2,d2);
		else {
			mwr.setLen(4,d2);
			if (x==3) {
				mwr.output("r",d2); mwr.setLen(2,d2);
			}
		}
		mwr.output("r",d2);
		mwr.subtractBeats(8/mwr.getLength(),this,(!theNextChord) && doRepeatEnd);
	}
	return(0);
}
#endif

Boolean Chord::nextNeedsToAccent(Part part) const {
	if (part==P_UNDEFINED) return(accentPassNotes);
	else if (accentPassNotes==FALSE || getPassNote(part).isEqualTo(undefinedNote)==TRUE) return(FALSE);
	else return((getPassNote(part).intervalWith(getPart(part)).getValue()<i_third)?TRUE:FALSE);
}

#ifdef TSR_VERSION
#pragma argsused
#endif
static void displayNoteOfChord(NoteOfChord n,int addToOctave) {
#ifdef TSR_VERSION
	;
#else
	putchar("135"[(int)n%(int)N_ONE2]);
	putchar("_ '\""[(int)n/(int)N_ONE2+addToOctave]);
#endif
}

void Chord::display() const {
#ifdef TSR_VERSION
	;
#else
	putchar("1234567?"[getFigure()]); putchar("abc?"[getInversion()]);
	if (!theLastChord || getKey().isEqualTo(theLastChord->getKey())==FALSE) getKey().printReportTo(stdout);
	putchar('{');
	displayNoteOfChord(ChordPoss::getBas(theChosenPossibility),0);
	displayNoteOfChord(ChordPoss::getTen(theChosenPossibility),TEN_OCTAVE-BAS_OCTAVE);
	displayNoteOfChord(ChordPoss::getAlt(theChosenPossibility),ALT_OCTAVE-BAS_OCTAVE);
	displayNoteOfChord(ChordPoss::getSop(theChosenPossibility),SOP_OCTAVE-BAS_OCTAVE);
	putchar('}'); putchar(' ');
#endif
}

void Chord::erase() const {
#ifdef TSR_VERSION
	;
#else
	int spaces=13;
	if (!theLastChord || getKey().isEqualTo(theLastChord->getKey())==FALSE) spaces+=getKey().getReportLength();
	for (;spaces;spaces--) deleteChar();
#endif
}

void Chord::calculateFigure() {
	if(theKey.isEqualTo(oldKey)==FALSE) {
		Note x((DegreeOfScale)ChordPoss::getFigure(theChosenPossibility),BAS_OCTAVE,oldKey);
		x.adjustToKey(theKey);
		theFigure=(Figure)(x.getDegreeOfScale());
	} else theFigure=ChordPoss::getFigure(theChosenPossibility);
}
#endif
