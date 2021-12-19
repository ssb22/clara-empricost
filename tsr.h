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
#ifndef TSR_H
#define TSR_H
#include "mappings.h"

#ifdef TSR_VERSION

// Don't suppress redundant loads
#pragma option -Z-

// #define ON_SCREEN /* Defined if C in top-right corner */
// #define MEM_REPORT /* Report if out of memory */
// #define PLAY_TUNE_VERSION /* Orchestra thing (not to do with compos prog) */

extern char canGiveTime;
extern char needsToRemoveTSR;
int installCheck(); // Returns 1 if installed

#include <setjmp.h>
extern jmp_buf backgroundProgram;
void tsr_exit(); // First call exits as TSR, subsequently longjmp's to foregroundProgram
inline void revokeTime() { if (canGiveTime && !setjmp(backgroundProgram)) tsr_exit(); }
inline void initRevokeTime() { canGiveTime=1; revokeTime(); }
#else
#define initRevokeTime()
#define revokeTime()
#endif
#endif
