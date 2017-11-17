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
#include "canon.h"
#ifndef TSR_VERSION
Canon::Canon(NumBeats beatsPerBar,KeyRef key,int barsInPhrase) : theBarsInPhrase(barsInPhrase) {
	theOpenMelody =new Melody(beatsPerBar,(NumBeats)0,key,beatsPerBar*barsInPhrase-1,1,1/*imperfect end*/,1/* proper start*/,MS_FALSE,TRUE,NULL,FALSE/*add chr*/); // I17
	Key key2=key.getRelatedKey(RK_RELATIVE);
	theCloseMelody=new Melody(beatsPerBar,(NumBeats)0,key2,beatsPerBar*barsInPhrase-1,1,1/*imperfect end*/,0/* proper start*/,MS_FALSE,TRUE,NULL,TRUE/*add chr*/); // I18
}

#ifndef SETUP_ONLY_VERSION
void Canon::outputToMwr(Mwr &mwr) {
	for (int lp=P_BAS; lp>=P_SOP; lp--) theOpenMelody->outputToMwr(mwr,lp==P_BAS,0,NULL,FALSE,0,(lp<=mwr.getPart() || (mwr.getPart()==P_PEDAL && lp==P_SOP))?FALSE:TRUE);
	for (lp=P_SOP; lp<=P_BAS; lp++) theCloseMelody->outputToMwr(mwr,1,1,NULL,(lp==P_ALT)?TRUE:FALSE,0,(lp<=mwr.getPart() || mwr.getPart()==P_PEDAL)?FALSE:TRUE);
}
#endif
#endif