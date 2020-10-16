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
#include "tsr.h"
#ifdef RUNNING_ON_DOS
#ifndef SETUP_ONLY_VERSION
#include <new.h>
#include <process.h>
#pragma warn -par

#ifndef TSR_VERSION
#pragma saveregs
int handler(int errval,int ax,int bp,int si) {
	cputs("Retrying hardware error");
	return(1); // Retry
}
#pragma warn +par

static void startup(void) {
	harderr(handler);
}
#pragma startup startup

int c_break(void) {
	cputs("Retrying Ctrl-Break");
	return(1); // Keep going
}
#endif

#ifndef BYPASS_MALLOC
#if (defined(ON_SCREEN) || defined(MEM_REPORT))
//extern unsigned int* screen;
#define screen ((unsigned int*)MK_FP(0xB800,0))
#define ATTR 0x1E00
#endif
void fatalNewHandler() {
#ifdef TSR_VERSION
#if (defined(ON_SCREEN) || defined(MEM_REPORT))
#define message "Please free some memory"
#define MESSAGE_LEN 23
	for (int lp=0; lp<MESSAGE_LEN; lp++) screen[lp]=message[lp]+ATTR;
#endif
	revokeTime();
#else
	cputs("Not enough memory\r\n");
	exit(0);
#endif
}
#endif

void setBrk(void) {
#ifndef TSR_VERSION
	ctrlbrk(c_break);
#endif
#ifndef BYPASS_MALLOC
	set_new_handler(fatalNewHandler);
#endif
#ifndef TSR_VERSION
	setcbrk(1);
#endif
}
#pragma startup setBrk
#endif
#endif