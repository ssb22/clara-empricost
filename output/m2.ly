\version "2.12.2"
#(set-global-staff-size 20) % (TODO adjust as needed: 25.2 is larger, 17.82 or 15.87 is smaller)
setup={\override Staff.TimeSignature #'style = #'numbered
\override Score.Hairpin #'after-line-breaking = ##t
#(set-accidental-style 'modern-cautionary) % not MWR behaviour but a nice addition
\set Score.skipBars = ##t % MWR needs $# to turn this on but we might as well have it by default
}
partA={ \setup 
%  Movement 2
\tempo 4 = 72 \override Score.BarNumber #'break-visibility = #end-of-line-invisible
\set Score.barNumberVisibility = #(every-nth-bar-number-visible 5)
\set Staff.midiInstrument = "celesta"
\time 3/4 \key e \major %{ TODO check it's in all the parts %} r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
<gis'' gis'> <e''' e''> <dis''' dis''> |
% 1a C#minor1a(Unessential in T) 2b 
<cis''' cis''>8 <dis''' dis''> <e''' e''>4 <fis''' fis''> |
% 1b(Unessential in S) 6a(Unessential in B) 4b(Unessential in T) 
<cis''' cis''> <dis''' dis''> <e''' e''>8 <cis''' cis''> |
% 1b(Unessential in T) 2b(Unessential in B/T) 1a(Unessential in S) 
<dis''' dis''> <cis''' cis''> <cis''' cis''>2 |
% 5a(Unessential in A/S) 6a(cad) 
\key e \major %{ TODO check it's in all the parts %} <dis''' dis''>4 <e''' e''>8 <dis''' dis''>16 <dis''' dis''> <e''' e''>4 |
% 5a E major4b(Unessential in S) 1b 
<fis''' fis''> <cis''' cis''> <cis''' cis''>8 <dis''' dis''> |
% 2a(Unessential in B) 6b(Unessential in B) 4a(Unessential in B/S) 
<e''' e''>4 <fis''' fis''> <e''' e''> |
% 1b(Unessential in T) 5b 1a(Unessential in T) 
<fis''' fis''> <cis''' cis''>2 |
% 5a 6a(cad) 
\bar "||"
\set Staff.midiInstrument = "clarinet"
r r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "harmonica"
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "harpsichord"
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "clarinet"
\bar "|." }
partB={ \setup \set Staff.midiInstrument = "marimba"
\time 3/4 \key e \major %{ TODO check it's in all the parts %} r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
cis' gis' dis' |
gis' e' cis' |
gis' dis' gis' |
gis'8 fis' e'2 |
cis'4 gis' dis' |
gis' e' cis' |
gis' dis' gis' |
gis'8 fis' e'2 |
\key e \major %{ TODO check it's in all the parts %} b'4 a' b' |
a' gis' a' |
e' b' gis' |
b' gis'2 |
\bar "||"
\set Staff.midiInstrument = "muted trumpet"
b'4 a' b' |
a' gis' a' |
e' b' gis' |
b' gis'2 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 1"
r r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "viola"
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
\bar "|." }
partC={ \setup \clef bass
\set Staff.midiInstrument = "reed organ"
\time 3/4 \key e \major %{ TODO check it's in all the parts %} r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
e gis16 gis cis'8 a4 |
gis cis' fis8 gis |
gis ais a fis gis4 |
bis' cis'2 |
e4 gis16 gis cis'8 a4 |
gis cis' fis8 gis |
gis ais a fis gis4 |
bis' cis'2 |
e4 gis16 gis cis'8 a4 |
gis cis' fis8 gis |
gis ais a fis gis4 |
bis' cis'2 |
\key e \major %{ TODO check it's in all the parts %} fis'4 e' b |
cis'2 e'4 |
b8 cis' b4 b8 cis' |
dis'4 e'2 |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
fis'4 e' b |
c'2 e'4 |
b8 c' b4 b8 cis' |
d'4 e'2 |
\bar "||"
\set Staff.midiInstrument = "harpsichord"
fis'4 e' b |
cis'2 e'4 |
b8 cis' b4 b8 cis' |
dis'4 e'2 |
\bar "||"
\set Staff.midiInstrument = "trombone"
r r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "oboe"
\bar "|." }
partD={ \setup \clef bass
\set Staff.midiInstrument = "string ensemble 2"
\time 3/4 \key e \major %{ TODO check it's in all the parts %} cis2 fis4 |
e a,8. b16 a,4 |
e fis16 fis dis8 cis4 |
gis a2 |
cis fis4 |
e a,8. b16 a,4 |
e fis16 fis dis8 cis4 |
gis a2 |
cis fis4 |
e a,8. b16 a,4 |
e fis16 fis dis8 cis4 |
gis a2 |
cis fis4 |
e a,8. b16 a,4 |
e fis16 fis dis8 cis4 |
gis a2 |
\key e \major %{ TODO check it's in all the parts %} b4 cis gis |
fis8 e e8. cis16 a,8 gis, |
gis,4 dis e |
b, cis2 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
b4 c gis |
fis8 eis e8. cis16 a,8 gis, |
gis,4 d e |
b, c2 |
\bar "||"
\set Staff.midiInstrument = "english horn"
b4 cis gis |
fis8 e e8. cis16 a,8 gis, |
gis,4 dis e |
b, cis2 |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
b4 cis gis |
fis8 e e8. cis16 a,8 gis, |
gis,4 dis e |
b, cis2 |
\bar "||"
\set Staff.midiInstrument = "cello"
\bar "|." }
partE={ \setup \clef bass
\set Staff.midiInstrument = "melodic tom"
\time 3/4 \key e \major %{ TODO check it's in all the parts %} r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\key e \major %{ TODO check it's in all the parts %} r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "timpani"
r2 r4 |
r2 r4 |
r2 r4 |
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
%  Random number seed was 53850
%  Current time is Sat Sep 14 13:43:09 1996
\bar "|." }
\bookpart{ %{ TODO add \header{} block for the score %}
\score { <<
\new Staff << \context Voice = PartAB { << \partA \\ \partB >> } >>
\new Staff << \context Voice = PartCD { << \partC \\ \partD >> } >>
\new Staff << \context Voice = PartE { \partE } >>
>> \layout{} \midi{} }
}
