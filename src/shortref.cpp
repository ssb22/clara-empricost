#ifdef Elara
/* Elara's 4th experiment */
/* Short Refrain: verses freshly composed, the return is one bar long. */
#include "shortref.h"
#include <stdlib.h>
#include <string.h>
ShortRefrain::ShortRefrain(Key key,int barsInPhrase,NumBeats beatsPerBar)
 : theInitKey(key), theRelatedKey(key.getRandomRelatedKey()) {
	NumBeats anacrusis=0;
	const char* only=getenv("CLARA_SR_ONLY");
	int verseChords=beatsPerBar*(barsInPhrase-1)+anacrusis+1;
	theRefrain=NULL; theMiddle=NULL; for (int i=0;i<3;i++) theVerse[i]=NULL;
	if (!only || !strcmp(only,"refrain")) {
		int rl=beatsPerBar+1; { const char* e=getenv("CLARA_SR_REF_LEN"); if (e) rl=atoi(e); }
		int ri=0; { const char* e=getenv("CLARA_SR_REF_IMP"); if (e) ri=atoi(e); }
		theRefrain=new Melody(beatsPerBar,anacrusis,key,rl,1,ri,1,MS_FALSE,TRUE,NULL,FALSE);
	}
	if (!only || !strcmp(only,"verse"))
		for (int i=0;i<3;i++)
			theVerse[i]=new Melody(beatsPerBar,anacrusis,key,verseChords,1,1,1,MS_FALSE,TRUE,NULL,FALSE);
	if (!only || !strcmp(only,"middle"))
		theMiddle=new Melody(beatsPerBar,anacrusis,theRelatedKey,verseChords,1,1,1,MS_FALSE,TRUE,NULL,FALSE);
}
ShortRefrain::~ShortRefrain() {
	delete theRefrain; delete theMiddle;
	for (int i=0;i<3;i++) delete theVerse[i];
}
void ShortRefrain::outputToMwr(Mwr &mwr,Part part) {
	mwr.setPart(part);
	if (theVerse[0]) { mwr.writeComment("Verse 1"); theVerse[0]->outputToMwr(mwr,1,0); }
	if (theRefrain) { mwr.writeComment("Refrain"); theRefrain->outputToMwr(mwr,0,0); }
	if (theVerse[1]) { mwr.writeComment("Verse 2"); theVerse[1]->outputToMwr(mwr,0,0); }
	if (theRefrain) { mwr.writeComment("Refrain"); theRefrain->outputToMwr(mwr,0,0); }
	if (theMiddle) { mwr.writeComment("Middle"); theMiddle->outputToMwr(mwr,0,0,&theRelatedKey); }
	if (theRefrain) { mwr.writeComment("Refrain"); theRefrain->outputToMwr(mwr,0,0,&theInitKey); }
	if (theVerse[2]) { mwr.writeComment("Verse 3"); theVerse[2]->outputToMwr(mwr,0,0); }
	if (theRefrain) { mwr.writeComment("Refrain"); theRefrain->outputToMwr(mwr,0,1); }
}
void ShortRefrain::outputAndClear() {
	Mwr mwr(NULL,3,4,4,0);
	outputToMwr(mwr,P_SOP);
	outputToMwr(mwr,P_ALT);
	outputToMwr(mwr,P_TEN);
	outputToMwr(mwr,P_BAS);
	outputToMwr(mwr,P_PEDAL);
}
void AbacForm::outputAndClear() { /* same (TODO: polymorphism?) */
	Mwr mwr(NULL,3,4,4,0);
	outputToMwr(mwr,P_SOP);
	outputToMwr(mwr,P_ALT);
	outputToMwr(mwr,P_TEN);
	outputToMwr(mwr,P_BAS);
	outputToMwr(mwr,P_PEDAL);
}
AbacForm::AbacForm(Key key,int barsInPhrase,NumBeats beatsPerBar)
   : theInitKey(key), theRelatedKey(key.getRandomRelatedKey()) {
	NumBeats anacrusis=0;
	int verseChords=beatsPerBar*(barsInPhrase-1)+anacrusis+1;
	int aImperfect=1; { const char* e=getenv("CLARA_ABAC_A_IMP"); if (e) aImperfect=atoi(e); }
	int bl=beatsPerBar+1; { const char* e=getenv("CLARA_ABAC_B_LEN"); if (e) bl=atoi(e); }
	int bImp=0; { const char* e=getenv("CLARA_ABAC_B_IMP"); if (e) bImp=atoi(e); }
	int cl=verseChords; { const char* e=getenv("CLARA_ABAC_C_LEN"); if (e) cl=atoi(e); }
	int cImp=0; { const char* e=getenv("CLARA_ABAC_C_IMP"); if (e) cImp=atoi(e); }
	theA[0]=new Melody(beatsPerBar,anacrusis,key,verseChords,1,aImperfect,1,MS_FALSE,TRUE,NULL,FALSE);
	theB=new Melody(beatsPerBar,anacrusis,key,bl,1,bImp,1,MS_FALSE,TRUE,NULL,FALSE);
	theA[1]=new Melody(beatsPerBar,anacrusis,key,verseChords,1,aImperfect,1,MS_FALSE,TRUE,NULL,FALSE);
	theC=new Melody(beatsPerBar,anacrusis,key,cl,1,cImp,1,MS_FALSE,TRUE,NULL,FALSE);
}
AbacForm::~AbacForm() {
	delete theB; delete theC;
	for (int i=0;i<2;i++) delete theA[i];
}
void AbacForm::outputToMwr(Mwr &mwr,Part part) {
	mwr.setPart(part);
	if (theA[0]) { mwr.writeComment("A1"); theA[0]->outputToMwr(mwr,1,0); }
	if (theB)    { mwr.writeComment("B");  theB->outputToMwr(mwr,0,0); }
	if (theA[1]) { mwr.writeComment("A2"); theA[1]->outputToMwr(mwr,0,0); }
	if (theC)    { mwr.writeComment("C");  theC->outputToMwr(mwr,0,1); }
}
#endif
