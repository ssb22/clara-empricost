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
#ifndef SETUP_ONLY_VERSION
#include "testing.h"
#ifdef WILL_BE_TESTING
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static struct TestingStruct {
	long theNumCalls;
	int theLineNumber;
	char* theFileName;
} theTest[MAX_LOG];

static int logPtr=0;
int countCalls(char*file,int line) {
	for (int lp=0; lp<logPtr; lp++)
		if (!stricmp(theTest[lp].theFileName,file) && theTest[lp].theLineNumber==line)
			{ theTest[lp].theNumCalls++; if (theTest[lp].theNumCalls<0) { printTestReport(); exit(0); } return(0); }
	theTest[logPtr].theNumCalls=1; theTest[logPtr].theLineNumber=line; theTest[logPtr].theFileName=file;
	logPtr++; return(0);
}

static int sort_function(const void* v1,const void* v2) {
	if ((((TestingStruct*)v1)->theNumCalls)>(((TestingStruct*)v2)->theNumCalls))
		return(1);
	else if ((((TestingStruct*)v1)->theNumCalls)==(((TestingStruct*)v2)->theNumCalls))
		return(0);
	else return(-1);
}

void printTestReport() {
	FILE* reportFile=fopen("COMPOS.LOG","at");
	fprintf(reportFile,"-------- RESULTS OF TEST -----------\n");
	fprintf(reportFile,"Number of calls encountered: %d\n",logPtr);
	qsort((void*)theTest,logPtr,sizeof(theTest[0]),sort_function);
	for (int lp=0; lp<logPtr; lp++)
		fprintf(reportFile,"%d\tFile %s line %d\t%ld calls\n",lp,theTest[lp].theFileName,theTest[lp].theLineNumber,theTest[lp].theNumCalls);
	fclose(reportFile);
}
#pragma exit printTestReport
#endif
#endif
#endif