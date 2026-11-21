#ifdef Elara
/* Elara's 4th experiment - not yet plumbed in to main.cpp */
#include "melody.h"
#include "key.h"
class ShortRefrain {
 public:
  ShortRefrain(Key key,int barsInPhrase,NumBeats beatsPerBar=4);
  ~ShortRefrain();
  void outputToMwr(Mwr &mwr,Part part);
 protected:
  Melody* theRefrain;
  Melody* theVerse[3];
  Melody* theMiddle;
  const Key theInitKey,theRelatedKey;
};
#endif
