#ifdef Elara
/* Elara's 4th experiment - not yet plumbed in to main.cpp */
#include "shortref.h"
ShortRefrain::ShortRefrain(Key key,int barsInPhrase,NumBeats beatsPerBar)
  : theInitKey(key), theRelatedKey(key.getRandomRelatedKey()) {
  NumBeats anacrusis=0;
  int verseChords=beatsPerBar*(barsInPhrase-1)+anacrusis+1;
  theRefrain=new Melody(beatsPerBar,anacrusis,key,beatsPerBar+1,1,0,1,MS_FALSE,TRUE,NULL,FALSE);
  for (int i=0;i<3;i++)
    theVerse[i]=new Melody(beatsPerBar,anacrusis,key,verseChords,1,1,1,MS_FALSE,TRUE,NULL,FALSE);
  theMiddle=new Melody(beatsPerBar,anacrusis,theRelatedKey,verseChords,1,1,1,MS_FALSE,TRUE,NULL,FALSE);
}
void ShortRefrain::outputToMwr(Mwr &mwr,Part part) {
  mwr.setPart(part);
  mwr.writeComment("Verse 1"); theVerse[0]->outputToMwr(mwr,1,0);
  mwr.writeComment("Refrain"); theRefrain->outputToMwr(mwr,0,0);
  mwr.writeComment("Verse 2"); theVerse[1]->outputToMwr(mwr,0,0);
  mwr.writeComment("Refrain"); theRefrain->outputToMwr(mwr,0,0);
  mwr.writeComment("Middle");  theMiddle->outputToMwr(mwr,0,0,&theRelatedKey);
  mwr.writeComment("Refrain"); theRefrain->outputToMwr(mwr,0,0,&theInitKey);
  mwr.writeComment("Verse 3"); theVerse[2]->outputToMwr(mwr,0,0);
  mwr.writeComment("Refrain"); theRefrain->outputToMwr(mwr,0,1);
}
#endif