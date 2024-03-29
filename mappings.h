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
#ifndef MAPPINGS_H
#define MAPPINGS_H

// MAPPINGS.H: INCLUDED AT THE BEGINNING OF EVERY MODULE

#ifdef __TCPLUSPLUS__
#define RUNNING_ON_DOS
#endif

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

#define SINGLE_DIRECTORY /* not for TSR version */
#ifdef SINGLE_DIRECTORY
#define DIR_SEPARATOR '-'
#else
// #define DIR_SEPARATOR '\\'
#define DIR_SEPARATOR '/'
#endif
// #define FAST_RANDOM 232 /* Length of random table; don't define if call RNG directly */

#ifdef RUNNING_ON_DOS
#include <conio.h>
#define aKeyIsPressed kbhit
#include <dos.h>
#include <dir.h>
#else
inline int return0() { return 0; }
#define aKeyIsPressed return0
#endif

#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

#ifdef __TCPLUSPLUS__
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#include <unistd.h>
#include <fnmatch.h>
#endif

#define deleteFile remove
#define renameFile rename /* Returns 0 on sucess */
char* filenameMatching(const char* wildcard);
#ifndef __TCPLUSPLUS__
char* upperCase(char* string);
#define strupr upperCase
#endif

#define WILDCARD_LIT "*"

#ifdef RUNNING_ON_DOS
inline void deleteChar() {
if (wherex()==1) gotoxy(80,wherey()-1);
else gotoxy(wherex()-1,wherey());
clreol();
}
//#define deleteChar() printf("\x8 \x8") doesn't seem to work with split lines
#else
#define deleteChar() printf("\b \b")
// (this works on Unix, although you have to wait for the buffer to flush)
#endif

#ifdef BYPASS_MALLOC
typedef unsigned size_t;
void* operator new(size_t size);
void operator delete(void*p);
#endif

#define emailExtention ".CNM"
#define EMAIL_DIRECTORY "Y:\\MAIL\\4000006"
#define MAILDIR_SEARCH "Y:\\MAIL\\*.*"
#define YMAIL "Y:\\MAIL\\"
#define ALT_EMAIL_DIR "N:\\USERS\\YEAR97\\BROWN\\COMPUTIN.G\\PROGRAMS\\C\\COMPOS\\WRITING\\"
#define FINISHED_DIR "WR-"
#define UNFINISHED_DIR "WK-"
#define MIN_DATE_FILE "MINDATE.DAT"
#define MAX_DATE_FILE "MAXDATE.DAT"
#define MEL_EXTENSION ".MEL"
#define MEL_FINISHED_CHAR 'F'
#define MEL_FINISHED_LIT "WR-F"
#define MEL_UNFINISHED_CHAR 'I'
#define MEL_UNFINISHED_LIT "WK-I"
#define MEL_TEMP_CHAR 'T'
#define SETTINGS_FNAME "WR-SEED.DAT"
#define SYSTEM_VOLUME "SYS:"
#define MAIL_DRIVE_TO_MAP ('Y'-'A'+1)
#define WORK_DRIVE_TO_MAP ('N'-'A'+1)
#define WORK_VOLUME "WORK:"
#ifndef MAXPATH
#define MAXPATH 80
#endif

#endif
