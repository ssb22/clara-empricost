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
#ifndef SETUP_ONLY_VERSION
#ifdef RUNNING_ON_DOS
#include "tsr.h"
#include <stdlib.h>
#include <mem.h>
#include <time.h> // For playtune
#include <malloc.h> // For farmalloc
#if (defined(BYPASS_MALLOC) || defined(TSR_VERSION))
#if (defined(ON_SCREEN) || defined(MEM_REPORT))
//#define ATTR 0x7900
#define ATTR 0x1E00
//unsigned int* screen=(unsigned int*)MK_FP(0xB800,0); // 0xB000 for monochrome systems;
#define screen ((unsigned int*)MK_FP(0xB800,0))
#endif
#endif
#if (defined(BYPASS_MALLOC) || (defined(TSR_VERSION) && !(defined(__MEDIUM__))))
#ifndef RUNNING_ON_DOS
#error Need to be RUNNING_ON_DOS for BYPASS_MALLOC
#endif
// Malloc, etc. for the library functions, because default malloc etc can't
// co-exist with our memory allocation
void* malloc(size_t size) {
#ifdef BYPASS_MALLOC
	unsigned int segment;
	// Return value: 7 = memory control block destroyed, 8 = insufficent memory
	while (_dos_allocmem(size/16+((size%16)!=0),&segment)) {
#else
	void*p;
	while(!(p=farmalloc(size))) {
#endif
#if (defined(ON_SCREEN) || defined(MEM_REPORT))
#define message "Please free some memory"
#define MESSAGE_LEN 23
		for (int lp=0; lp<MESSAGE_LEN; lp++) screen[lp]=message[lp]+ATTR;
#endif
		revokeTime(); // Only executes if already initialised
#if (defined(ON_SCREEN) || defined(MEM_REPORT))
		for (lp=0; lp<MESSAGE_LEN; lp++) screen[lp]=ATTR;
#endif
	}
#ifdef BYPASS_MALLOC
	return(((void _seg*)segment)+((void near*)0));
#else
	return(p);
#endif
}
#ifdef BYPASS_MALLOC
void free(void* block) { freemem(FP_SEG(block)); }
#endif
// That's probably all overloading required, but just in case the standard
// libraries haven't used top-down functional decomposition ...
void* calloc(size_t nitems,size_t size) { return(malloc(nitems*size)); }
void* realloc(void* block,size_t size) {
	void* b2=malloc(size);
	if(block && b2) memcpy(b2,block,size);
	return(b2);
}
// Assuming in a large memory model anyway and not handling
// data in large chunks:
#ifdef BYPASS_MALLOC
void far* farmalloc(unsigned long size) { return(malloc((size_t)size)); }
#endif
void farfree(void far* block) { free(block); }
void far* farcalloc(unsigned long nitems,unsigned long size) { return(calloc((size_t)nitems,(size_t)size)); }
void far* farrealloc(void far* block,unsigned long size) { return(realloc(block,(size_t)size)); }
// Also overload new and delete, just in case
void* operator new(unsigned size) { return(malloc(size)); }
void operator delete(void*p) { free(p); }
#endif

#ifdef TSR_VERSION
#ifndef RUNNING_ON_DOS
#error Need to be RUNNING_ON_DOS for TSR_VERSION
#endif

#include <setjmp.h>
char canGiveTime=0,needsToRemoveTSR=0;

//#define CLOCK_INTR 0x1C /* 18.2 times per second interrupt */
#define CLOCK_INTR 0x28 /* DOS 2+: IDLE ie called on input wait loops */
#define UNINSTALL_INTR 0x6F
#define UNINSTALL_AX 0x636F /* "co" */
#define UNINSTALL_BX 0x6D70 /* "mp" */
#define UNINSTALL_CX 0x6F73 /* "os" */
#define TEST_INSTALL_CX 0x696E /* "in "*/

//#define HEAP_LEN 32768U // 32K should be about right
//#define HEAP_LEN 20480U // Commented out after reducing size of PackOfCards
#define HEAP_LEN 2498U

#ifdef __MEDIUM__
#ifdef BYPASS_MALLOC
extern unsigned _heaplen=256; // Call that a heap !?
/* Can't have _heaplen == 0 because the thing'll allocate as much
memory as it can.  Setting it to a value such as 1 is dangerous because
it may try to fit a lookup table in there.  Hence its value.
*/
#else
/* Using C++'s malloc() in Medium memory model: This cuts into a previously
allocated heap which avoids memory fragmentation (many programs can't cope
with too much memory fragmentation because they try to increase the size
of the program itself)
NB This is what C++ does with malloc() anyway if there isn't a heap
*/
extern unsigned _heaplen=HEAP_LEN;
#endif
#endif

static void interrupt (*oldhandler)(...);
static void interrupt (*oldhandler2)(...);

jmp_buf foregroundProgram,backgroundProgram;

// Because the foreground and background programs have different stack
// segments, there is no danger of the stacks interfering with each other

// Put the statics outside the function, just in case
//static int reEntry=0; // Don't need reEntry due to inDos checking etc

static char* inDosFlag,*criticalErrorFlag;

#ifdef PLAY_TUNE_VERSION
#include <math.h>
static clock_t timeOut=0;
static long objNoFromFile(char* file) {
	long retVal=0;
	for (long lp=0,value=19683L; lp<4; lp++,value/=27L) {
		retVal+=value*(file[lp]-'@');
	}
	return(retVal);
} static void noteFile(int note,long duration) {
	if (note && note<100) {
		sound((int)(110.0*pow(2.0,(double)(note-15.0)/12.0)));
		timeOut=clock()+duration;
	} else nosound();
} static void playTune() {
	if (timeOut && clock()>timeOut) { timeOut=0; nosound(); }
	else {
		struct find_t ffblk;
		if (!_dos_findfirst(MAILDIR_SEARCH,FA_DIREC,&ffblk)) {
			// Declaring this char: Don't forget that we're on the DOS (or application) stack!
			char temp[MAXPATH]; sprintf(temp,YMAIL "%s\\*.PUN",ffblk.name); // Y:\\MAIL\\ ffblk.name \\ *.PUN
			if (!_dos_findfirst(temp,0,&ffblk) {
				noteFile(objNoFromFile(ffblk.name),objNoFromFile(ffblk.name+4));
				sprintf(strrchr(temp,DIR_SEPARATOR)+1),ffblk.name); deleteFile(temp);
			}
		}
	}
}
#endif

// No register variables:
#pragma option -r-
// Save registers:
#pragma saveregs
void interrupt handler(...) {
	// Don't do anything like setting / getting DTAs in this handler!
	oldhandler();
	/*disable();*/ if (/*!reEntry &&*/ (*inDosFlag)<=1 && !(*criticalErrorFlag)) { //reEntry=1;
#ifdef PLAY_TUNE_VERSION
		playTune();
#endif
#ifdef ON_SCREEN
		screen[79]='C'+ATTR;
#endif
		if (!setjmp(foregroundProgram)) longjmp(backgroundProgram,1);
#ifdef ON_SCREEN
		screen[79]='c'+ATTR;
#endif
		/*enable();*/ //reEntry=0;
	} //oldhandler();
//	/*if (oldhandler)*/ _chain_intr(oldhandler);
}

static void interrupt handler2(...);
static int doneBefore=0;
static void unloadInterrupt() {
	// disable();
	if (getvect(CLOCK_INTR)==handler && getvect(UNINSTALL_INTR)==handler2) {
		setvect(CLOCK_INTR,oldhandler); setvect(UNINSTALL_INTR,oldhandler2);
		// Free the memory:
		asm mov ah,0x49; // Free memory block
		asm push es;
		asm mov es,_psp; // Block to free
		asm int 0x21;
		asm pop es;
	} // enable();
}
int installCheck() {
	int installed=0; unsigned ofs=FP_OFF(&installed);
	asm mov AX,UNINSTALL_AX;
	asm mov BX,UNINSTALL_BX;
	asm mov CX,TEST_INSTALL_CX;
	asm mov DX,ofs;
	asm int UNINSTALL_INTR;
	return(installed);
}
// No register variables:
#pragma option -r-
// Save registers:
#pragma saveregs
static void interrupt handler2(...) {
	asm cmp AX,UNINSTALL_AX;
	asm jnz skip;
	asm cmp BX,UNINSTALL_BX;
	asm jnz skip;
	asm cmp CX,UNINSTALL_CX;
	asm jnz skip2;
	needsToRemoveTSR=1; while (needsToRemoveTSR) asm int CLOCK_INTR;
	unloadInterrupt();
	return;
skip2:
	asm cmp CX,TEST_INSTALL_CX;
	asm jnz skip;
	asm mov bx,dx;
	asm mov (SS:[bx]),ax;
	return;
skip:
	oldhandler2();
}
// No register variables
#pragma option -r-
#pragma saveregs
static void getDOSaddresses() { // In separate function so can saveregs
	unsigned t1,t2;
	asm mov ax,0x3400;
	asm push es;
	asm int 0x21; // Returns InDOSFlag address in ES:BX
	asm mov dx,es; asm pop es;
	inDosFlag=(char*)(MK_FP(_DX,_BX));
	asm mov ax,0x5D06; // DOS 3.1+ ONLY
	asm push si; asm push ds;
	asm int 0x21; // Returns DS:SI -> Critical error byte
	asm mov dx,ds; asm pop ds;
	asm mov bx,si; asm pop si;
	criticalErrorFlag=(char*)(MK_FP(_DX,_BX));
}
// Register variables fine now
#pragma option -r

void tsr_exit() {
	if (doneBefore) longjmp(foregroundProgram,1);
	else {
		doneBefore=1;
		getDOSaddresses();
		// Free environment block: Segment is at PSP offset 2Ch
		_dos_freemem(*((unsigned*)(&(((char*)MK_FP(_psp,0))[0x2C]))));
		oldhandler2=getvect(UNINSTALL_INTR);
		setvect(UNINSTALL_INTR,handler2);
		oldhandler=getvect(CLOCK_INTR);
		setvect(CLOCK_INTR,handler);
		/*
			The size of the program in segments is the end of the stack
			minus the Program Segment Prefix (PSP)
			(well that's the theory ...)
			(The first parameter for keep is the program's errorlevel exit code)
		*/
		// Also add any data already allocated on the heap by startup routines NEEDATTENTION More safety!
		_dos_keep(0,_SS+(_stklen+SAFETY_SPACE+HEAP_LEN)/16-_psp);
	}
}

// (TSR_VERSION)
#endif

// (SETUP_ONLY_VERSION)
#endif
#endif
