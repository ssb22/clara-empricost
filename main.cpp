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
#include <time.h> // For RNG init
#include "rng.h"
#include "symphony.h"
#include "network.h"
#include "melody.h"
#include <stdlib.h> /* For atexit */
#include <ctype.h>
#include <string.h> // strcpy
#include "tsr.h"

#ifdef RUNNING_ON_DOS
#include <process.h> // For adventure game thing at end
#ifdef TSR_VERSION
extern unsigned _stklen=5120U;
#else
extern unsigned _stklen=20480U;
#endif
//extern unsigned _stklen=50000U;
#endif

#ifdef FAST_RANDOM
void initRandom();
#endif

void saveSettings();
static int barsInPhraseToUse=4;
#ifndef SETUP_ONLY_VERSION
static char noSaveSettings=0;
#endif

int main() {
#ifdef RUNNING_ON_DOS
#ifndef TSR_VERSION
	int gettingInput=(_argc<=1); // Because called by adventure game
	// (Parameters are those to pass back to adventure game afterwards)
#endif
#endif
#ifdef FAST_RANDOM
	initRandom();
#endif
#ifdef TSR_VERSION
	if (installCheck()) /*{ cout << "Already installed";*/ return; /*}*/
	initRevokeTime();
	while(1) useYourTimeUsefully();
#else
	FILE* prevFile=fopen(SETTINGS_FNAME,"rb");
	if (!prevFile && filenameMatching(MEL_UNFINISHED_LIT WILDCARD_LIT MEL_EXTENSION)) {
#ifndef SETUP_ONLY_VERSION
		while(useYourTimeUsefully())
#endif
		;
	} else {
	// The default values for the variables are for leaving overnight runs by remote control on adventure server
		unsigned seed=(unsigned)time(NULL);
		if (prevFile) {
			fread(&seed,sizeof(seed),1,prevFile);
			cout << "Using previous random number seed " << seed << endl;
			fread(&barsInPhraseToUse,sizeof(barsInPhraseToUse),1,prevFile);
			fclose(prevFile);
		} else {
			cout << "Enter random number seed: ";
#ifdef RUNNING_ON_DOS
			if (gettingInput) {
#endif
				cin >> seed;
#ifdef RUNNING_ON_DOS
			}
#endif
			cout << "Enter bars per phrase: ";
#ifdef RUNNING_ON_DOS
			if (gettingInput) {
#endif
				cin >> barsInPhraseToUse;
#ifdef RUNNING_ON_DOS
			}
#endif
		}
		RNGseed(seed); atexit(saveSettings);
		FILE* t=fopen(MIN_DATE_FILE,"rb");
		if (t) fclose(t); else fclose(fopen(MIN_DATE_FILE,"wb"));
		Symphony theSymphony(barsInPhraseToUse);
		fclose(fopen(MAX_DATE_FILE,"wb"));
		cout << "You may now start copies of the program running on other workstations" << endl;
		cout << "in the same directory with full privileges" << endl;
		// cout << "Note: Proper way to exit (on DOS) is Shift-Q; if everything interrupted, can" << endl;
		// cout << "resume if directory untouched" << endl;
#ifndef SETUP_ONLY_VERSION
		theSymphony.outputAndClear();
		noSaveSettings=1;
#endif
	}
// (TSR_VERSION)
#endif
    return 0;
}

// This lot can be a problem if the program is being used for the replicator
/*#ifdef RUNNING_ON_DOS
#ifndef TSR_VERSION
void exitFunc() {
	// This is something to do with running compos prog at night on
	// adventure computer
	if (_argc>1) execv("N:\\USERS\\YEAR97\\BROWN\\COMPUTIN.G\\PROGRAMS\\C\\NETV\\NETV.EXE",_argv);
}
#pragma exit exitFunc
#endif
#endif*/

#ifdef strupr
char* upperCase(char* string) {
	for (int lp=0; string[lp]; lp++)
		string[lp]=toupper(string[lp]);
	return(string);
}
#endif

extern unsigned origRandNoSeed;
void saveSettings() {
#ifndef SETUP_ONLY_VERSION
	if (!noSaveSettings) {
#endif
		cout << "Saving settings" << endl;
		FILE* prevFile=fopen(SETTINGS_FNAME,"wb");
		fwrite(&origRandNoSeed,sizeof(origRandNoSeed),1,prevFile);
		fwrite(&barsInPhraseToUse,sizeof(barsInPhraseToUse),1,prevFile);
		fclose(prevFile);
#ifndef SETUP_ONLY_VERSION
	} else {
		Melody::deleteAllFiles();
		cout << "Symphony complete" << endl;
		deleteFile(SETTINGS_FNAME);
	}
#endif
}

#ifdef __unix__
char* filenameMatching(const char* wildcard) {
  DIR* dp=opendir ("./");
  if(dp) {
    int found=0;
    static char buf[MAXPATH];
    struct dirent *ep;
    while((ep=readdir(dp))!=NULL) {
      if(!fnmatch(wildcard,ep->d_name,FNM_PATHNAME|FNM_NOESCAPE)) {
        strcpy(buf,ep->d_name);
        found=1; break;
      }
    }
    closedir(dp);
    if(found) return buf;
  } else puts("Warning: Couldn't open the directory.");
  return NULL;
}
#endif
