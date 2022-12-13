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
#include "mwr.h"
#include <time.h>
#include "chord.h"
#include <string.h>
#include <ctype.h>
#include "rng.h"
int randomMIDIinst(Part part);
void fileFromObjNo(long objNo,char* buffer) { // Imported from adventure game (hence objNo)
	for (int lp=0,value=19683; lp<4; lp++,value/=27) {
		buffer[lp]='@'+(objNo%(value*27L))/value;
	}
}
#ifndef SETUP_ONLY_VERSION
#ifndef TSR_VERSION
#define MAX_MOVEMENTS 4
int metMark[MAX_MOVEMENTS]={120,72,96,144};
Mwr::Mwr(FILE* stream,Octave octave,int length,int l2,int movementNumber) {
	startTime=time(NULL); initYet=FALSE; thePart=P_SOP; in68=FALSE;
	if (!stream) {
		// Open a file which doesn't already exist
		char name[13]; long count=0,r=(long)time(NULL);
		while (!stream) {
			count++; putchar('.');
			fileFromObjNo(count+r,name); strcpy(name+4,"COMP.MWR");
			stream=fopen(name,"rb"); if (stream) { fclose(stream); stream=NULL; continue; }
			stream=fopen(name,"wb");
		} setbuf(stream,NULL);
	}
	theStream=stream; theOctave=octave; theLength=length;
	theL2=l2;
	if (movementNumber) fprintf(theStream,"; Movement %d\n",movementNumber);
	fprintf(theStream,"~x0litt.chr\n$x0,6Page ª\n$-$c%di3,5y9#z3u5,0,-8,6w16h12m0\n",(movementNumber<=MAX_MOVEMENTS)?metMark[movementNumber-1]:120);
}

extern unsigned origRandNoSeed;
Mwr::~Mwr() {
	long x=time(NULL)-startTime;
	fprintf(theStream,"; Runtime for this movement %ld hours %ld minutes %ld seconds\n",x/3600L,(x%3600L)/60L,x-x/60L*60L);
	fprintf(theStream,"; Random number seed was %u\n",origRandNoSeed);
	fprintf(theStream,"; Should this program ever reach the stage where it would become necessary\n"
	"; to give it a name in order to get it past some concert organizer, try Clara\n");
	fprintf(theStream,"; Empricost - Condition List Action Rejection Algorithm for the Evaluation of\n"
	"; Music at Pseudo Random Idea COnstruction STage\n");
	fprintf(theStream,"; For best results use MIDI output or output to MID file with /OUTCMF\n");
	time_t t=time(NULL); fprintf(theStream,"; Current time is %s",ctime(&t));
	fputc('@',theStream);
	fclose(theStream);
}

void Mwr::setLen(int len,int&dot) {
	theLength=len;
	if (in68==TRUE) {
		// Quick fix for 6/8.  This is dependent on the way the composition program works
		// eg. assumes no syncopation, etc.
		// The program should use 4 beats to bar
		if (theBeatsLeft==6 || theBeatsLeft==5 || theBeatsLeft==2 || theBeatsLeft==1) len*=2;
		else if (len<=2) { len*=2; dot=1; }
		if (theL2!=len && (theBeatsLeft==5 || theBeatsLeft==1)) len/=2; // Fix thing again (see @@@ below)
	}
	if (theL2!=len) {
		theL2=len;
		fprintf(theStream,"L%d",len);
	}
}

void Mwr::initPart(int beatsPerBar) {
	if (!initYet) {
		fprintf(theStream,"P%d",thePart+1);
		if (thePart==P_TEN) fputc('t',theStream);
		fprintf(theStream,"$i-%d",randomMIDIinst(getPart()));
	} if (!initYet || theBeatsPerBar!=beatsPerBar) {
		theBeatsPerBar=beatsPerBar;
		fprintf(theStream,in68?"J%d,8":"J%d,4",in68?6:theBeatsPerBar);
	} initYet=TRUE;
}

void Mwr::setKey(Key newKey) {
	theKey=newKey;
	fprintf(theStream,"K%d%c",theKey.getNumAccidentals(),theKey.getAccidentalType());
	initAccidentals();
}

void Mwr::printDoubleBar() {
	fprintf(theStream,"$|\n\n");
	fprintf(theStream,"$i-%d",randomMIDIinst(getPart()));
}

void Mwr::output(const char* toOutput,int &dot) {
	char o2[3]; strcpy(o2,toOutput); strupr(o2);
	if (o2[0]>='A' && o2[0]<'A'+tonesInOctave) {
		if (accType[o2[0]-'A']==toOutput[1]) {o2[0]=toOutput[0];toOutput=o2;o2[1]=0; } // Surplus accidental
		else accType[o2[0]-'A']=toOutput[1];
	}
	// Do the doubling first so that octave signs don't get in the way of ornaments
	if (o2[0]>='A' && o2[0]<'A'+tonesInOctave) {
		/*if (thePart==P_BAS) { // Double up an 8ve lower staccato
			fprintf(theStream,"<%s",o2); if (dot) fputc('.',theStream);
			fprintf(theStream,"&>");
		} else*/ if (thePart==P_SOP) { // Double up an 8ve higher
			fprintf(theStream,">%s",toOutput); if (dot) fputc('.',theStream);
			fprintf(theStream,"&<");
		}
	}
	fprintf(theStream,"%s",toOutput); if (dot) fputc('.',theStream);
	dot=0;
}

void Mwr::restBeats(int beats) {
	int d2=0; if (!beats) beats=theBeatsPerBar;
	while (beats>=4) { setLen(1,d2); output("r",d2); beats-=4; subtractBeats(8/getLength()); }
	while (beats>=2) { setLen(2,d2); output("r",d2); beats-=2; subtractBeats(8/getLength()); }
	if (beats) { setLen(4,d2); output("r",d2); subtractBeats(8/getLength()); }
}

void Mwr::subtractBeats(int beats,const Chord* report,int repeatEnd) {
	if (beats) {
		theBeatsLeft-=beats;
		if (!theBeatsLeft) {
			theBeatsLeft=theBeatsPerBar*2;
			if (repeatEnd) fputc(']',theStream);
			if (!((++barNo)%4)) fputc('\n',theStream);
			fputc(' ',theStream); initAccidentals();
			if (thePart==P_SOP && report) { fputc(';',theStream); report->printReportTo(theStream); fputc('\n',theStream); }
		}
	}
}

void Mwr::setOctave(Octave octave) {
	if (octave==theOctave+1) fputc('>',theStream);
	else if (octave==theOctave-1) fputc('<',theStream);
	else if (octave!=theOctave) fprintf(theStream,"O%d",octave-1);
	theOctave=octave;
}

void Mwr::initAccidentals() {
	int lp; for (lp=0; lp<tonesInOctave; lp++) accType[lp]='n';
	int offset=(theKey.getAccidentalType()=='#')?('F'-'A'):('B'-'A');
	for (lp=0; lp<theKey.getNumAccidentals(); lp++) {
		accType[offset]=theKey.getAccidentalType();
		offset=(offset+((theKey.getAccidentalType()=='#')?sharpIncrement:flatIncrement))%tonesInOctave;
	}
}
#endif
#endif
