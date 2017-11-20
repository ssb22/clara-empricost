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
#ifndef SYMPHONY_H
#define SYMPHONY_H
class Sonata; class Melody; class Minuet; class Rondo; class Canon;
class Symphony {
public:
	Symphony(int barsInPhrase=4);
	~Symphony();
	void outputAndClear();
protected:
	Sonata* theSonata; // 1st movement
	Canon* theCanon; // 2nd movement
	Minuet* theMinuet,*theTrio; // 3rd movement
	Rondo* theRondo; // 4th movement
};
#endif SYMPHONY_H