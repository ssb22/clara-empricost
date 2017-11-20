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
#ifndef PROTECT_H
#define PROTECT_H
#include <stdio.h>
#include "mappings.h"
// Code itself is signature: Won't work due to number of versions
extern char* binarySignature;
#define BIN_SIG_LIT "\aI am a file.  Leave me alone.\n\r\x1A\x0\xc\x1f"
#define BINARY_SIG_SIZE 37 /* Including 0 at end */
int authentic(FILE* file); // Check binary signature, return 1 if fine or trigger alert if not
inline void makeAuthentic(FILE* file) { fwrite(binarySignature,BINARY_SIG_SIZE,1,file); }
void statusReport(char* report,char* r2=NULL);
int checkFileDate(char* filename); // If invalid, deletes file & returns 0
//void netwareMap(int drive,char* path); // drive is 0 default, 1=A ...
#define netwareMap(drive,path)
#endif