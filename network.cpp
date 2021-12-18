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
