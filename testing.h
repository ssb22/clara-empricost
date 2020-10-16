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
#ifndef TESTING_H
#define TESTING_H

#ifndef TSR_VERSION
// Do NOT compile the testing code in the TSR version !!!!!!!!!!!!!!!
//#define WILL_BE_TESTING
#endif

#ifdef WILL_BE_TESTING
#define MAX_LOG 1000
int countCalls(char*file,int line);
void printTestReport();
#define countReturn(x) return(countCalls(__FILE__,__LINE__)?(x):(x))
#else
#define countCalls(file,line) (0)
#define countReturn(x) return(x)
#define printTestReport() (0)
#endif
#endif