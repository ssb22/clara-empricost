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
#include <iostream.h>
#include <time.h> // For RNG init
#include "rng.h"
#include "symphony.h"
#include "network.h"
#include "melody.h"
#include <stdlib.h> /* For atexit */
#include <ctype.h>
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
	makeDirectory("WORKING"); makeDirectory("READING"); makeDirectory("WRITING");
	FILE* prevFile=fopen(SETTINGS_FNAME,"rb");
	if (!prevFile && filenameMatching(MEL_UNFINISHED_LIT WILDCARD_LIT MEL_EXTENTION)) {
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
	for (int lp=0; lp<strlen(string); lp++)
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
char* filenameMatching(char* wildcard) {
  DIR* dp=opendir ("./");
  if(dp) {
    int found=0;
    static char buf[MAXPATH];
    struct dirent *ep;
    while(ep=readdir(dp)) {
      if(!fnmatch(wildcard,ep->d_name,FNM_PATHNAME|FNM_NOESCAPE)) {
        strcpy(buf,ep->d_name);
        found=1; break;
      }
    }
    closedir(dp);
    if(found) return buf;
  } else puts("Warning: Couldn't open the directory.");
}
#endif
