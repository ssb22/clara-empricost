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
#include "protect.h"
#include "tsr.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
void fileFromObjNo(long objNo,char* buffer);

#ifdef RUNNING_ON_DOS
void report2(char* report,char* r2,char* emailDir) {
	FILE* stream=NULL; char name[L_tmpnam],tmpBuf[MAXPATH]; long count=0,r=(long)time(NULL);
	while (!stream) {
		count++; if (count>5) return;
		fileFromObjNo(count+r,name); strcpy(name+4,emailExtention);
		sprintf(tmpBuf,"%s\\%s",emailDir,name);
		stream=fopen(tmpBuf,"rb"); if (stream) { fclose(stream); stream=NULL; continue; }
		stream=fopen(tmpBuf,"wb");
	}
	fprintf(stream,"From:    Composition program\r\n");
	fprintf(stream,"To:      Silas Brown\r\n");
	time_t t=time(NULL);
	fprintf(stream,"Date:    %s",ctime(&t));
	fprintf(stream,"Subject: STATUS REPORT\r\n\r\n");
	fprintf(stream,report,r2); fprintf(stream,"\r\n");
	fclose(stream);
}
#endif

char* binarySignature=BIN_SIG_LIT;

#ifndef SETUP_ONLY_VERSION
#define SIG_NOT_MATCH_MSG "SECURITY ALERT: \aBinary signature does not match"
#define DATE_NOT_MATCH_MSG "SECURITY ALERT: \aDate of file %s not within task creation range"

#ifdef TSR_VERSION
#ifdef ON_SCREEN
char lastReport[80];
//extern unsigned int* screen;
#define screen ((unsigned int*)MK_FP(0xB800,0))
#endif
#endif
void statusReport(char* report,char* r2) {
#ifndef TSR_VERSION
#ifdef RUNNING_ON_DOS
	if(wherex()>1)
#endif
		printf("\n");
	printf(report,r2); printf("\n");
#else
#ifdef ON_SCREEN
#define ATTR 0x1E00
	sprintf(lastReport,report,r2);
	for (int lp=0; lp<strlen(lastReport); lp++) screen[lp+160]=lastReport[lp]+ATTR;
#endif
//	netwareMap(MAIL_DRIVE_TO_MAP,SYSTEM_VOLUME);
//	report2(report,r2,EMAIL_DIRECTORY);
	report2(report,r2,ALT_EMAIL_DIR);
#endif
}

int authentic(FILE* file) {
	for (int lp=0; lp<BINARY_SIG_SIZE; lp++) if (fgetc(file)!=((unsigned char*)binarySignature)[lp]) {
	statusReport(SIG_NOT_MATCH_MSG);
#ifdef RUNNING_ON_DOS
		sound(500+rand()%500);
#endif
		return(0);
	} return(1);
}

int checkFileDate(char* filename) {
#ifdef RUNNING_ON_DOS
	struct find_t ffblk,min,max;
	_dos_findfirst(filename,0,&ffblk);
	_dos_findfirst(MIN_DATE_FILE,0,&min);
	_dos_findfirst(MAX_DATE_FILE,0,&max);
	if((unsigned long)ffblk.wr_date*65536L+(unsigned long)ffblk.wr_time<(unsigned long)min.wr_date*65536L+(unsigned long)min.wr_time
//	|| (unsigned long)ffblk.wr_date*65536L+(unsigned long)ffblk.wr_time>(unsigned long)max.wr_date*65536L+(unsigned long)max.wr_time
	) {
		statusReport(DATE_NOT_MATCH_MSG,filename);
		sound(1000+rand()%1000);
		deleteFile(filename);
		return(0);
	}
#endif
	return(1);
}

/*#ifdef TSR_VERSION
// No register variables
#pragma option -r-
// Save registers, just in case
#pragma saveregs
void netwareMap(int drive,char* path) {
	// Don't forget we may be running TSR standalone
	unsigned t1=FP_SEG(path),t2=FP_OFF(path);
//	do {
//		if (_AX) revokeTime();
		asm mov ax,0xE905; // 0xE906 for MAP DEL (then don't need path)
		asm push ds;
		asm mov dx,t2;
		asm mov bx,drive;
		asm mov ds,t1;
		asm int 0x21;
		asm pop ds;
//		asm mov ax,0; asm adc ax,0;
//	} while (_AX); // Because CF clear on success
}
// Register variables now fine
#pragma option -r
#endif*/

// (SETUP_ONLY_VERSION)
#endif