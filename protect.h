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