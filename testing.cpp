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
