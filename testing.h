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