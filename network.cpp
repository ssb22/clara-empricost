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
#include <stdio.h>
#include <string.h>
#include "network.h"
#include "tsr.h"
#include "protect.h"

char* getFilename(int number,Boolean complete);
char* getFilename2(char* fname) {
	static char f2[MAXPATH]; strcpy(f2,fname);
	*(strrchr(f2,DIR_SEPARATOR)?(strrchr(f2,DIR_SEPARATOR)+1):f2)=MEL_TEMP_CHAR; return(f2);
}

#ifndef SETUP_ONLY_VERSION
int useYourTimeUsefully() {
#ifdef TSR_VERSION
	needsToRemoveTSR=0; revokeTime();
#endif
	char* fname=filenameMatching(MEL_UNFINISHED_LIT WILDCARD_LIT MEL_EXTENTION);
	if (fname && checkFileDate(fname)) {
		char* f2=getFilename2(fname);
		if (!renameFile(fname,f2)) {
			// My memory allocation: Gets stuck on first fopen
			// Their memory allocation: fopen returns NULL
			FILE* file=fopen(f2,"rb");
//			while (!file) { needsToRemoveTSR=0; revokeTime(); file=fopen(f2,"rb"); statusReport("Re-trying fopen(%s)",f2); }
			if (authentic(file)) {
				statusReport("Processing task %s",fname);
				Melody* mel=new Melody(file);
				fclose(file); deleteFile(f2);
				if (!filenameMatching(getFilename(mel->getNumber(),TRUE))) { // In case it was already finished
					// (NB last line corrupted fname; doesn't matter as contains same number for status report)
					mel->generate();
					mel->saveYourself();
				}
				delete mel;
				statusReport("Task %s completed",fname);
			} else { fclose(file); deleteFile(f2); }
		}
		else statusReport("Error - failed to obtain task %s",fname);
	} else return(0);
	return(1);
}
#endif

char* getFilename(int number,Boolean complete) {
#ifdef TSR_VERSION
	netwareMap(WORK_DRIVE_TO_MAP,WORK_VOLUME); // In case someone deletes the mapping
#endif
	static char fName[MAXPATH]="";
#ifdef TSR_VERSION
	strcpy(fName,_argv[0]);
#endif
	sprintf(
#ifdef TSR_VERSION
	strchr(fName,DIR_SEPARATOR)?(strrchr(fName,DIR_SEPARATOR)+1):
#endif
	fName,"%s%c%d"MEL_EXTENTION,
	complete?FINISHED_DIR:UNFINISHED_DIR,complete?MEL_FINISHED_CHAR:MEL_UNFINISHED_CHAR,number);
	return(fName);
}

#ifdef RUNNING_ON_DOS
/*#ifdef TSR_VERSION
// Need to bypass C++'s findfirst etc functions because they don't work
// when the program is TSR
// ---- THIS FUNCTION DOES NOT RETURN CORRECT VALUE WHEN FOUND ----
// static char newDta[256],far*save_dta;
// (We don't need to worry about the DTA etc because we are intercepting
// the wrong interrupt)
// No register variables please
#pragma option -r-
int myFindfirst(char* wildcard,int attrib,struct find_t* ffblk) {
//	save_dta=getdta(); setdta(newDta);
	int temp1=FP_OFF(wildcard),temp2=FP_SEG(wildcard);
	asm mov ax,0x4E00;
	asm mov cx,attrib;
	asm mov dx,temp1;
	asm push ds; // Will be needed later
	asm mov ds,temp2;
	asm int 0x21;
	asm mov bx,0;  // Because I don't know
	asm adc bx,0;  // how to get the carry bit otherwise
	asm pop ds;
	unsigned xseg=_BX; // Get the carry flag
	memcpy(ffblk,/*new_dta*//*getdta(),43); // Especially the 13 bytes from offset &1E - the filename
//	setdta(save_dta);
	return(xseg);
}
// Register variables back on again
#pragma option -r
#define _dos_findfirst myFindfirst
#endif
*/
char* filenameMatching(char* wildcard) {
	static char internal[MAXPATH];
#ifdef TSR_VERSION
	strcpy(internal,_argv[0]);
#endif
	strcpy(
#ifdef TSR_VERSION
	strchr(internal,DIR_SEPARATOR)?(strrchr(internal,DIR_SEPARATOR)+1):
#endif
	internal,wildcard);
	struct find_t ffblk;
	if (_dos_findfirst(wildcard,_A_NORMAL,&ffblk)) return(NULL);
	strcpy((strrchr(internal,DIR_SEPARATOR)?(strrchr(internal,DIR_SEPARATOR)+1):internal),ffblk.name);
	return(internal);
}
#endif