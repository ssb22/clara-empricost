# clara-empricost
Automatic music composition experiment 1996-97 from http://ssb22.user.srcf.net/clara

(also mirrored at http://ssb22.gitlab.io/clara just in case)

Clara Empricost stands for “Condition List Action Rejection Algorithm for the Evaluation of Music at Pseudo-Random Idea COnstruction STage”.  It is a C++ program that is supposed to generate music. I wrote it at school in 1996 as an experiment; it generated some interest in the now-defunct Cambridge University New Music Society toward the end of 1997 and has since been featured in a Generative Creativity course at Sussex University.

To compile on modern Unix systems: `g++ -fno-for-scope -fno-operator-names -D__unix__ *.cpp -o clara`

Then run: `./clara`

To compile on other systems, you may have to modify `mappings.h`.

The program should then prompt you for a random number seed and the number of bars to write in each phrase, and then begin displaying things to indicate that it’s doing something. (Don’t try to log all this as the log can get very big.) When finished, it should leave the piece in a file with the extension .MWR, which is an input file to [Manuscript Writer](http://ssb22.user.srcf.net/mwrhome/).  On modern systems you should be able to use `mwr2ly` to convert this to Lilypond.

Because modern computers are generally much faster than they were in 1996, it should not be necessary to use parallel processing as I did at the time.  But if you wish, you can do so by running another instance of the program in the same directory: it should begin helping out the first instance. This can be done via multiple processors on the same machine, or on a cluster of machines sharing a filespace via NFS or other means of sharing a filespace.  The program was originally designed to run as a background task on about 20 DOS machines, and it is resilient to individual machines crashing etc (you can actually get it to save its state, but at today’s speeds there is little point).

How it works
============

1. An overall plan for the piece is generated, in terms of phrases (e.g. AABBA, ABACA, etc). Structures like sonata form can be pre-programmed. (See sonata.h, canon.h, minuet.h, rondo.h and symphony.h)

2. Each phrase is composed independently (although there are some common parameters such as how long it should be and what key it should start and finish in). The program writes all of these “compose a phrase” tasks to separate files on disk (each task to its own file).

3. Multiple copies of the program can now work on the different phrases in parallel (assuming that they all have access to the same disk directory). They look for a phrase file, load it, work on it until finished or interrupted, and save their state back (see network.cpp). When all of the files have been completely processed, the result is put together and output to Manuscript Writer files (see mwr.h); these can then be converted to MIDI or whatever by the music program Manuscript Writer.

The parameters for each phrase are as follows (see melody.h):

* Number of beats per bar

* Number of beats in the anacrusis (pick-up)

* Starting key

* Finishing key

* Number of chords that the phrase should contain

* Number of cadences in the phrase

* Whether the phrase should end on a perfect or an imperfect cadence

* Whether the phrase should start “properly” (i.e. with I or V-I)—this should be the case if the previous phrase ended in an imperfect cadence and is allowed to introduce a modulation at that point

* Whether the phrase is allowed to modulate, and whether it is allowed to introduce a modulation on the final cadence (one of these had better be set if the finishing key is any different from the starting key!)

* Whether passing notes are allowed

* Whether chromaticisms are allowed 

The values of these parameters depend on the piece being composed. For example, a development section may allow more chromaticisms and modulations than the first subject. Note that all of them are set in advance by the programmer; the computer does not choose any of the above values itself.

Each phrase is made up of chords (see chord.h). When a chord is constructed, it is only partially specified; the initial specification is:

* The length of the chord in beats (usually 1, but longer at cadences)

* The chords written so far (which are used in determining what is acceptable next)

* Whether it is the final chord, or part of a cadence; and the strength of the beat that the chord falls on (the first beat of the bar is more important and this affects what is acceptable)

* Any notes that have already been decided on. This is used when loading a partially-completed work from a file, and could also be used to cause the program to harmonise a given melody (or bass line or whatever) rather than decide on its own, although some modification would be required. 

The rest of the specification is filled in at ‘random’. The random choice is then evaluated against a set of rules (see rules.cpp) which were taken from a music harmony textbook; if it is found to be unacceptable then another random choice is made. The possibilities are tried in a random order without replacement; if after trying every possibility, no acceptable chord can be found, then the program backtracks—the previous chord is treated as unacceptable and another one is tried. If the program can’t find any solution even after trying all possibilities of the previous chord, the one before that is marked as unacceptable and so on. If you make the rules too draconian then the program will spend ages trying out every single possibility and then crash with an error message because it backtracked right to the start. (Prolog would just say “no”.)

In practice, what often happens is that the program quite quickly gets to a cadence point, then finds that there is no way to put a cadence on its current chord sequence, and has to do a lot of backtracking and re-trying until it finds a chord sequence that can lead to a cadence at that point.

The backtracking is optimised a little by noting that modulations can often cause problems, particularly if the cadence needs to be in some key that is unrelated to the current one. Therefore, if a chord has caused the phrase to modulate and it is found to be unacceptable, it will first try modulating to the phrase’s destination key rather than whatever key it happened to modulate to before; if that doesn’t solve the problem then it will try not modulating at all. Despite these optimisations, though, the backtracking is still very inefficient and it often takes a large amount of computer time to compose a work.

The parameters of a chord that have to be decided are as follows (see chord.h):

* The figure (tonic, supertonic, etc)

* For each part (soprano, alto, tenor, bass), the degree of the chord in that part (1, 3 or 5) and the octave it is in 

This is all a bit limited—I didn’t get as far as implementing sevenths, ninths etc (although the program can write seventh passing notes). Since there are 4 parts each with 2 possible octaves and 3 possible chord degrees, and there are 7 possible figures, the total number of possibilities for each chord is 9072; most of these would fail the rules immediately.

Selecting chords at random without replacement can be likened to writing each possible chord on a card, giving a pack of 9072 cards, and evaluating the chords in order after shuffling the pack. Because shuffling the pack can be computationally expensive (particularly on the old DOS machines for which this program was originally written), it is only shuffled once for each phrase, and the selection of each chord starts at a random position in the shuffled pack. If longer phrases are allowed then perhaps the pack should be shuffled more often.

Since most of the rules are written in terms of such things as the inversion of the chord, the intervals between various parts, and so on, the program calculates these from the notes.

Suspensions, passing notes, auxiliary notes, pedal notes, ornaments and chromaticisms are added after the chord sequence has been completed, using additional rules to determine what is acceptable, but this time no backtracking is necessary because the acceptability of an ornament etc does not depend on what has happened previously (one could argue that actually it does, but not in this program). Instrumentation is chosen at random (within some restrictions) and octave doubling of the soprano and bass is also performed.

The rules themselves are arranged in order of how frequently they are violated by choosing at random (this was determined emperically); this is so that an unacceptable choice can be identified as such as quickly as possible. Basically, the rules are as follows (see William Lovelock’s “First Year Harmony”, “Second Year Harmony” and “Third Year Harmony” for full details).

1. If this is the second chord in a modulation, check that the modulation works: It must be on a stronger beat than the previous chord, it must be a I (or a VI if the previous chord was a root position V), and if it’s of the same figure as the pivot chord in a gradual modulation then it must be a different inversion.

2. If this is a final chord and it’s chord I, and the phrase is not supposed to end on chord I, reject it (otherwise you get too many perfect cadences).

3. Perform a melody check on the soprano part. A melody check is defined as follows:

    1. Make sure it doesn’t go out of range

    2. If it’s the final chord, then the soprano part must have the tonic (reject anything else)
    
    3. The leading note should rise to the tonic (but it’s acceptable to repeat the leading note once before it does so)—reject anything else
    
    4. Reject a leap of an augmented interval
    
    5. Reject a leap of a seventh, or of a ninth or higher, even if there is one note intervening
    
    6. Reject any leap that does not land within the compass of the previous leap if the previous leap was an octave, a sixth, or a diminished fifth
    
    7. Octave leaps must also be preceded by notes within their compass
    
    8. If the soprano part has the same note from a weak beat to a strong beat then the chord’s figure must change (reject if it doesn’t)
    
    9. Reject bass parts that rise a third from weak to strong
    
    10. Reject leaps of diminished fourths and sevenths
    
    11. Avoid too many consecutive leaps (I’ve arbitrarily set “too many” to 3)
    
    12. A three-note descending or ascending scale passage in the bass part should be followed by further step in the same direction rather than a leap (it was unclear from the text whether a repetition of the same note is allowed; in this implementation I allowed it)
    
    13. The soprano and bass parts should avoid remaining around one note for too long. I interpreted this as: Reject pitches that have already been used more than once in the previous four notes
    
    14. If chromaticisms are to be added later, then the following rule is put in to help with progressions from chord II: If progressing to the tonic, force an upward resolution; if there is a subdominant of the scale in the chord then remain on the same note. 

4. If this is a final chord and the phrase needs to end on chord I, reject it if it isn’t I

5. Reject any chords whose notes do not match notes that were pre-defined (additionally, anything that has been pre-defined is not checked)—this is in case the code needs to be modified to harmonise a given melody or whatever

6. Avoid certain chords: VII in root position, any chord in second inversion except I, IV or V, and any chord in second inversion at the beginning of a phrase.

7. Check the melody of the alto part (as with the soprano part above)

8. Reject chords that cause a phrase to not start “properly” (I or V-I) when its specification said it should

9. Check the melody of the tenor part (as with the soprano part above)

10. Check the melody of the bass part (as with the soprano part above)

11. Check the following pairs of parts (in this order): soprano/alto, alto/tenor, soprano/bass, soprano/tenor, tenor/bass and alto/bass. For each pair, the following things need to be checked:

    1. Don’t cross the parts
    
    2. Avoid parallel octaves and fifths
    
    3. Don’t double the third, unless it’s on a V-VI or VI-V by stepwise motion
    
    4. In the soprano and bass, avoid exposed octaves and fifths (i.e. ones that are approached by similar motion in both parts, with some exceptions)
    
    5. Avoid overlaps (i.e. a note in one part “jumps over” the previous note in another)
    
    6. Avoid chords where two or more of the parts are playing the same note as in the previous chord
    
    7. If the progression is IV-V or V-IV (both in root position), make the soprano, alto and tenor move contrary to the bass and go to the nearst note (i.e. reject all chords that don’t do this)
    
    8. Avoid having a perfect fifth followed by a diminished fifth or vice versa between the bass and any other part
    
    9. Avoid doubling the leading note
    
    10. Avoid chords in which the alto doubles the bass if the chord is a diminished first inversion
    
    11. Avoid chords in which there is more than an octave between any two adjacent parts except tenor and bass 

12. Check that there is a third in the chord

13. Check that there is a root in the chord

14. If the chord is an inversion, or a chord III, then check that there is a fifth in the chord as well

15. Check that the third is not doubled in a major triad other than a chord VI

16. Check that the chord does not have the same figure as the previous one, unless the previous one was on a stronger beat or was the first chord in the phrase

17. Second inversions cannot be approached by leap (in the bass part) from an inversion of another chord

18. III must be followed by VI (reject anything else)

19. Avoid II-I and I-II (in root position)

20. Double the third if progressing IIb-V (i.e. reject anything that doesn’t)

21. Reject a second inversion if the previous chord was also a second inversion

22. More rules about second inversions: A passing 6/4: 6/4 must be on a weak beat and must be Ic or Vc; a cadential 6/4 must be on a stronger beat, must be Ic or IVc and must not contain leaps in any of the parts. Reject all second inversions that cannot be explained as cadential or passing.

23. If the chord is the final chord of a cadence, it must be weak to strong (unless the cadence is going to VI) and the cadence cannot be preceded by its final chord (except in the case of V-I-IV-I). Also reject if the first chord of the cadence has been anticipated by the previous chord.

24. If the chord is not the final chord of a cadence then check that it does not form the cadential progression V-I (unless it’s part of a modulation—if modulations are allowed then they can occur anywhere even if unspecified by the phrase specification). In retrospect, I think this is one reason why the modulations aren’t always so good—the above rule should probably have been checked as well before allowing them.

25. Avoid repetition of the same chord (figure and inversion) with only one chord intervening

26. In the progression V-IV, the soprano should rise a third, going from the fifth of V to the root of IV (reject if it doesn’t)

27. If the previous chord is IIa and the key is minor, then this chord must be Va and on a weaker beat (reject if not)

28. If the last chord was VIIb then avoid anything except I or Ib (or VI a in major key) 

Modulations are handled by noting whenever a chord could be the first of a modulatory cadence into any key, i.e. it must be some form of V, it cannot cause false relations (although there are exceptions here), and it must not be the final chord of the phrase unless the phrase is allowed to end in a modulating imperfect cadence. If these criteria are met (and the melody is allowed to modulate) then it does modulate, provided of course that a suitable chord can be found to follow it (this is why “check the modulation works” got to the top of the rules list).

Note that there are few rules about musical idioms. The program tends to ‘discover’ these for itself, since it is often the case that an idiom is almost the only solution.

While the output is harmonically correct, I thought it not sufficiently interesting to qualify as good music. The melodies are rarely lyrical, the cadences are predictable, and there are no climaxes or impressions. The instrumentation can sometimes be interesting, but this is very much dependent on the quality of the playback equipment in use. Bugs in the implementation can lead to small unintended deviations from the harmonic rules or the synchronisation of the parts, and this can add interest. While the above rules do not represent the entirety of Lovelock’s work on harmony, I felt that any further implementation was unlikely to deliver much improvement.
