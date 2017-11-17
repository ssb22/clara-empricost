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
#ifndef MAPPINGS_H
#define MAPPINGS_H

// MAPPINGS.H: INCLUDED AT THE BEGINNING OF EVERY MODULE

// This mappings.h has been hacked to get the thing running
// on Unix.
// Compile with g++ -fno-for-scope *.cpp

// If the program is to compile on DOS, this file should include
// #define RUNNING_ON_DOS

// If not running on DOS, aKeyIsPressed, deleteFile,etc. should be updated
// It should be a function returning non-0 if a key has been pressed

//#define TSR_VERSION /* Defined in TSR.PRO (TSR.PRJ renamed) in dialogue box */

/* Defining BYPASS_MALLOC causes operator new to be overloaded so that the
   program interfaces with DOS for itself, for use as a TSR or whatever.
   It is rather wasteful as it does it in 16-byte blocks. */
// *** NB IF YOU DEFINE BYPASS_MALLOC, MAKE SURE THAT CHORD IS DELETED WHEN
// IT SETS ITS SURROUNDING POINTERS TO NULL ON SHIFT-Q; SEE COMMENTS IN
// CHORD.CPP
// #define BYPASS_MALLOC

// Generate code for 286 instruction set
// #pragma option -2

// Note: The "Memory model" options must occur before any declarations
// or use of macros beginning with 2 underscores in #if... directives.
// Hence this lot should be placed near the beginning of MAPPINGS.H
#ifdef TSR_VERSION
// Turn off "word allignment" for size optimize
#pragma option -a-
// Turn off "Test stack overflow"
// because the events would be using the stacks of other applications
#pragma option -N-
// No inline expansion (for size optimize)
#pragma option -vi-
// Bias optimization for size over speed
#pragma option -G-
// No debugging, so don't have assertions
#define NDEBUG
// Safety space: Extra bytes added to program size for TSR exit function,
// just in case ...
#define SAFETY_SPACE 256
// Next 3 lines may be commented out
/*#ifndef BYPASS_MALLOC
#define BYPASS_MALLOC
#endif*/
#endif

// This "memory model" chunk may be commented out
/*// NB Was #ifdef BYPASS_MALLOC
#ifdef TSR_VERSION
// Switch to Medium memory model
#pragma option -mm
#else
// Switch to Large memory model
#pragma option -ml
#endif*/

// Now all clear to make declarations, etc.

// #define RUNNING_ON_DOS
// #define DIR_SEPARATOR '\\'
// #define DIR_SEPARATOR '/'
#define DIR_SEPARATOR '-' // just put it all in one directory
// #define FAST_RANDOM 232 /* Length of random table; don't define if call RNG directly */

// #include <conio.h>
// #define aKeyIsPressed kbhit
inline int return0() { return 0; }
#define aKeyIsPressed return0

// #include <dos.h>
// #include <dir.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <fnmatch.h>

#define deleteFile remove
#define renameFile rename /* Returns 0 on sucess */
char* filenameMatching(char* wildcard);
#ifndef __TCPLUSPLUS__
char* upperCase(char* string);
#define strupr upperCase
#endif

#define WILDCARD_LIT "*"

//inline void deleteChar() {
//if (wherex()==1) gotoxy(80,wherey()-1);
//else gotoxy(wherex()-1,wherey());
//clreol();
//}
//#define deleteChar() printf("\x8 \x8") doesn't seem to work with split lines
#define deleteChar() printf("\b \b")
// (this works on Unix, although you have to wait for the buffer to flush)

#ifdef BYPASS_MALLOC
typedef unsigned size_t;
void* operator new(size_t size);
void operator delete(void*p);
#endif

// #define makeDirectory(c) mkdir((c),0755)
#define makeDirectory(c) (0)

#define emailExtention ".CNM"
#define EMAIL_DIRECTORY "Y:\\MAIL\\4000006"
#define MAILDIR_SEARCH "Y:\\MAIL\\*.*"
#define YMAIL "Y:\\MAIL\\"
#define ALT_EMAIL_DIR "N:\\USERS\\YEAR97\\BROWN\\COMPUTIN.G\\PROGRAMS\\C\\COMPOS\\WRITING\\"
#define FINISHED_DIR "WRITING-"
#define UNFINISHED_DIR "WORKING-"
#define MIN_DATE_FILE "READING-MINDATE.DAT"
#define MAX_DATE_FILE "READING-MAXDATE.DAT"
#define MEL_EXTENTION ".MEL"
#define MEL_FINISHED_CHAR 'F'
#define MEL_FINISHED_LIT "WRITING-F"
#define MEL_UNFINISHED_CHAR 'I'
#define MEL_UNFINISHED_LIT "WORKING-I"
#define MEL_TEMP_CHAR 'T'
#define SETTINGS_FNAME "WRITING-RNGSEED.DAT"
#define SYSTEM_VOLUME "SYS:"
#define MAIL_DRIVE_TO_MAP ('Y'-'A'+1)
#define WORK_DRIVE_TO_MAP ('N'-'A'+1)
#define WORK_VOLUME "WORK:"
#ifndef MAXPATH
#define MAXPATH 80
#endif

#endif
