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
#include "antisebi.h"
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