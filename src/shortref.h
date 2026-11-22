#ifdef Elara
/* Elara's 4th experiment */
#include "melody.h"
#include "key.h"
#include "work.h"
class ShortRefrain : public Work {
public:
	ShortRefrain(Key key,int barsInPhrase,NumBeats beatsPerBar=4);
	~ShortRefrain();
	void outputToMwr(Mwr &mwr,Part part);
	void outputAndClear();
protected:
	Melody* theRefrain;
	Melody* theVerse[3];
	Melody* theMiddle;
	const Key theInitKey,theRelatedKey;
};
#endif
