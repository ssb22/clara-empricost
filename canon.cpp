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