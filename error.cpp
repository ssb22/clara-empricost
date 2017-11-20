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