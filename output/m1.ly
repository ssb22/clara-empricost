\version "2.12.2"
#(set-global-staff-size 20) % (TODO adjust as needed: 25.2 is larger, 17.82 or 15.87 is smaller)
setup={\override Staff.TimeSignature #'style = #'numbered
\override Score.Hairpin #'after-line-breaking = ##t
#(set-accidental-style 'modern-cautionary) % not MWR behaviour but a nice addition
\set Score.skipBars = ##t % MWR needs $# to turn this on but we might as well have it by default
}
partA={ \setup 
%  Movement 1
\tempo 4 = 120 \override Score.BarNumber #'break-visibility = #end-of-line-invisible
\set Score.barNumberVisibility = #(every-nth-bar-number-visible 5)
\set Staff.midiInstrument = "vibraphone"
\time 4/4 \key f \major %{ TODO check it's in all the parts %} <fis''' fis''>4 <eis''' eis''> <dis''' dis''>2 |
% 1a D#minor5a 6a(cad) 
%  1st Subject
\repeat volta 2 {
<dis''' dis''>4 <fis''' fis''> \trill <b'' b'> <ais'' ais'>8 \trill <dis''' dis''> |
% 1a D#minor3b 6a(Unessential in T) 1b(Unessential in S) 
<b'' b'>4 <fis''' fis''> <eis''' eis''>2 |
% 4a 1a(Unessential in T) 5a(cad) 
<fis''' fis''>4 <eis''' eis''> <eis''' eis''> <ais'' ais'> |
% 1b(Unessential in T) D#minor2b(Unessential in T) 5b(T susp)(Unessential in A) 1a(Unessential in T) 
<b'' b'>1 |
% 4a(cad) 
<dis''' dis''>4 <fis''' fis''> \trill <b'' b'> <ais'' ais'>8 \trill <dis''' dis''> |
% 1a D#minor3b 6a(Unessential in T) 1b(Unessential in S) 
<b'' b'>4 <fis''' fis''> <eis''' eis''>2 |
% 4a 1a(Unessential in T) 5a(cad) 
<dis''' dis''>4 <fis''' fis''> <fis''' fis''>8 <eis''' eis''> <eis''' eis''>8. \mordent <dis''' dis''>16 |
% 4a(Unessential in A) D#minor6b 2a(S susp)(Unessential in S) 5a(Unessential in S) 
<dis''' dis''>1 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "harmonica"
<dis''' dis''>8 <cis''' cis''> <cis''' cis''> <dis''' dis''> <dis''' dis''>4 <ais'' ais'>8. <cis''' cis''>16 |
% 1a(Unessential in S) D#minor5c(Unessential in S) 1b(Unessential in A(accented)) 3a(Unessential in B/S) 
<fis''' fis''>4 <dis''' dis''> <cis''' cis''>2 |
% 6a 4b(Unessential in B) 5a(cad) 
<b'' b'>4 <fis''' fis''> <dis''' dis''> <eis''' eis''>8. <cis''' cis''>16 |
% 6a(Unessential in B) D#minor6b(Unessential in A/T) 1a(Unessential in T/A) 5a(Unessential in S) 
<dis''' dis''>1 |
% 6a(cad) 
<dis''' dis''>8 <cis''' cis''> <cis''' cis''> <dis''' dis''> <dis''' dis''>4 <ais'' ais'>8. <cis''' cis''>16 |
% 1a(Unessential in S) D#minor5c(Unessential in S) 1b(Unessential in A(accented)) 3a(Unessential in B/S) 
<fis''' fis''>4 <dis''' dis''> <cis''' cis''>2 |
% 6a 4b(Unessential in B) 5a(cad) 
<ais'' ais'>8 <dis''' dis''> <dis''' dis''>4 <eis''' eis''>2 |
% 1a(Unessential in S) D#minor1b(Unessential in T/B) 2a 5a 
<dis''' dis''>1 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "clarinet"
%  Transition
\key bes \major %{ TODO check it's in all the parts %} <bes'' bes'>4 <f''' f''> <bes'' bes'> <c''' c''> |
% 4b(Unessential in B) Bbmajor5b(Unessential in T) 1a 2b 
<d''' d''> <bes'' bes'> <c''' c''>8 <f''' f''> <d''' d''>4 |
% 6a(Unessential in B) 1a(Unessential in B) 5b(Unessential in S/B(accented)) 6b 
<c''' c''> <d''' d''> <bes'' bes'>2 |
% 5a(Unessential in T) 5a - Modulating to G minor6a(cad) 
%  2nd Subject
\key bes \major %{ TODO check it's in all the parts %} <bes'' bes'>4 <g'' g'> <fis'' fis'> <g'' g'>8 <a'' a'> |
% 1a(Unessential in B) G minor1a(Unessential in T) 5a(Unessential in B) 1b(Unessential in S) 
<a'' a'>4 <fis'' fis'> <g'' g'> <bes'' bes'> |
% 2b(Unessential in B) 3a(Unessential in B) 6a(Unessential in T) 6b(Unessential in A) 
<g'' g'>8 <bes'' bes'> <d''' d''> <fis''' fis''> <d''' d''>4 <ees''' ees''> |
% 1a(Unessential in S) 5c(Unessential in S/B) 1b(Unessential in A) 4a 
<a'' a'> <bes'' bes'>8. <g'' g'>16 <a'' a'>2 |
% 2b(Unessential in A) 1a(Unessential in T/S) 5a(cad) 
<ees'' ees'>4 <ees''' ees''>8. <bes'' bes'>16 <a'' a'>4 <bes'' bes'>8. <d''' d''>16 |
% 6b(Unessential in B) G minor6b(Unessential in S) 2b 3b(Unessential in S) 
<bes'' bes'>4 <c''' c''> <g'' g'> <d''' d''>8. <fis''' fis''>16 |
% 6a 7b(Unessential in A) 1b(Unessential in B) 5c(Unessential in S) 
<d''' d''>8 <e''' e''> <ees''' ees''>4 <c''' c''>8 <a'' a'> <a'' a'> <fis'' fis'>16 <fis'' fis'> |
% 1a(Unessential in S) 6a 2a(Unessential in S) 5a(Unessential in S) 
<g'' g'>1 |
% 6a(cad) 
<bes'' bes'>4 <g'' g'> <fis'' fis'> <g'' g'>8 <a'' a'> |
% 1a(Unessential in B) G minor1a(Unessential in T) 5a(Unessential in B) 1b(Unessential in S) 
<a'' a'>4 <fis'' fis'> <g'' g'> <bes'' bes'> |
% 2b(Unessential in B) 3a(Unessential in B) 6a(Unessential in T) 6b(Unessential in A) 
<g'' g'>8 <bes'' bes'> <d''' d''> <fis''' fis''> <d''' d''>4 <ees''' ees''> |
% 1a(Unessential in S) 5c(Unessential in S/B) 1b(Unessential in A) 4a 
<a'' a'> <bes'' bes'>8. <g'' g'>16 <a'' a'>2 |
% 2b(Unessential in A) 1a(Unessential in T/S) 5a(cad) 
<a'' a'>4 <g''' g''> <d''' d''> <ees''' ees''> |
% 5a(Unessential in B) G minor4b(Unessential in A) 3a(T susp)(Unessential in T/B) 6a(Unessential in B/T) 
<d''' d''> <ees''' ees''> <a'' a'> <bes'' bes'> |
% 1b(Unessential in T/B) 4a(Unessential in T/A) 2b(Unessential in T/B) 3a(Unessential in B) 
<bes'' bes'>8 <a'' a'> <g'' g'> <bes'' bes'> <c''' c''>4 <fis'' fis'> |
% 6a(Unessential in B/S) 6a(Unessential in S) 2a(T susp)(Unessential in B/T) 5a(Unessential in B) 
<g'' g'>1 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "harpsichord"
%  Codetta
<g'' g'>4 <a'' a'> <g'' g'> <a'' a'> |
% 1b(Unessential in B) G minor2b(Unessential in A) 1a 5a 
<c''' c''> <g'' g'>8 <a'' a'>16 <a'' a'> <a'' a'>4 <g'' g'>8 \trill <bes'' bes'> |
% 4b(Unessential in T) 1c(Unessential in S) 2b(Unessential in T) 6a(Unessential in S) 
<c''' c''>4 <d''' d''> <c''' c''>8 <a'' a'> <a'' a'>4 |
% 4a 1b 2a(Unessential in A/S) 5a 
<g'' g'>1 }
|
% 1a(cad) 
\set Staff.midiInstrument = "trumpet"
%  Start of development
\key f \major %{ TODO check it's in all the parts %} <fis''' fis''>4 <eis''' eis''> <dis''' dis''>2 |
% 1a D#minor5a 6a(cad) 
<dis''' dis''>4 <fis''' fis''> \trill <b'' b'> <ais'' ais'>8 \trill <dis''' dis''> |
% 1a D#minor3b 6a(Unessential in T) 1b(Unessential in S) 
<b'' b'>4 <fis''' fis''> <eis''' eis''>2 |
% 4a 1a(Unessential in T) 5a(cad) 
<fis''' fis''>4 <e''' e''> <eis''' eis''> <ais'' ais'> |
% 1b(Unessential in T) D#minor2b(Unessential in T) 5b(T susp)(Unessential in A) 1a(Unessential in T) 
<b'' b'>1 |
% 4a(cad) 
<dis''' dis''>4 <fis''' fis''> \trill <b'' b'> <ais'' ais'>8 \trill <dis''' dis''> |
% 1a D#minor3b 6a(Unessential in T) 1b(Unessential in S) 
<b'' b'>4 <fis''' fis''> <eis''' eis''>2 |
% 4a 1a(Unessential in T) 5a(cad) 
<dis''' dis''>4 <fis''' fis''> <f''' f''>8 <eis''' eis''> <eis''' eis''>8. \mordent <dis''' dis''>16 |
% 4a(Unessential in A) D#minor6b 2a(S susp)(Unessential in S) 5a(Unessential in S) 
<dis''' dis''>1 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "clarinet"
<gis'' gis'>8 <ais'' ais'> <ais'' ais'>4 <cis''' cis''> %  Sequences
<g''' g''> |
% 6b Bbmajor
<bes'' bes'> <c''' c''> <g''' g''> <c''' c''> |
% 6b Bbmajor4b(Unessential in B/T) 2a(Unessential in T/A) 6b 5c 
<bes'' bes'> <c''' c''> <bes'' bes'> <g'' g'> |
% 4a(Unessential in B) G minor
<bes'' bes'> <a'' a'> <g'' g'> <a'' a'>16 <a'' a'> <c''' c''>8 |
% 4a(Unessential in B) G minor1a 5c - Modulating to G major1b(Unessential in B) 2a(Unessential in S/T) 
<bes'' bes'>4 <a'' a'> <g'' g'> r |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "harmonica"
%  Recapitulation
<fis''' fis''> <eis''' eis''> <dis''' dis''>2 |
% 1a D#minor5a 6a(cad) 
<dis''' dis''>4 <fis''' fis''> \trill <b'' b'> <ais'' ais'>8 \trill <dis''' dis''> |
% 1a D#minor3b 6a(Unessential in T) 1b(Unessential in S) 
<b'' b'>4 <fis''' fis''> <eis''' eis''>2 |
% 4a 1a(Unessential in T) 5a(cad) 
<fis''' fis''>4 <eis''' eis''> <eis''' eis''> <ais'' ais'> |
% 1b(Unessential in T) D#minor2b(Unessential in T) 5b(T susp)(Unessential in A) 1a(Unessential in T) 
<b'' b'>1 |
% 4a(cad) 
<dis''' dis''>4 <fis''' fis''> \trill <b'' b'> <ais'' ais'>8 \trill <dis''' dis''> |
% 1a D#minor3b 6a(Unessential in T) 1b(Unessential in S) 
<b'' b'>4 <fis''' fis''> <eis''' eis''>2 |
% 4a 1a(Unessential in T) 5a(cad) 
<dis''' dis''>4 <fis''' fis''> <fis''' fis''>8 <eis''' eis''> <eis''' eis''>8. \mordent <dis''' dis''>16 |
% 4a(Unessential in A) D#minor6b 2a(S susp)(Unessential in S) 5a(Unessential in S) 
<dis''' dis''>1 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "harmonica"
<dis''' dis''>8 <cis''' cis''> <cis''' cis''> <dis''' dis''> <dis''' dis''>4 <ais'' ais'>8. <cis''' cis''>16 |
% 1a(Unessential in S) D#minor5c(Unessential in S) 1b(Unessential in A(accented)) 3a(Unessential in B/S) 
<fis''' fis''>4 <dis''' dis''> <cis''' cis''>2 |
% 6a 4b(Unessential in B) 5a(cad) 
<b'' b'>4 <fis''' fis''> <dis''' dis''> <eis''' eis''>8. <cis''' cis''>16 |
% 6a(Unessential in B) D#minor6b(Unessential in A/T) 1a(Unessential in T/A) 5a(Unessential in S) 
<dis''' dis''>1 |
% 6a(cad) 
<dis''' dis''>8 <cis''' cis''> <cis''' cis''> <dis''' dis''> <dis''' dis''>4 <ais'' ais'>8. <cis''' cis''>16 |
% 1a(Unessential in S) D#minor5c(Unessential in S) 1b(Unessential in A(accented)) 3a(Unessential in B/S) 
<fis''' fis''>4 <dis''' dis''> <cis''' cis''>2 |
% 6a 4b(Unessential in B) 5a(cad) 
<ais'' ais'>8 <dis''' dis''> <dis''' dis''>4 <eis''' eis''>2 |
% 1a(Unessential in S) D#minor1b(Unessential in T/B) 2a 5a 
<dis''' dis''>1 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "xylophone"
\key bes \major %{ TODO check it's in all the parts %} <g'' g'>4 <d''' d''> <ees''' ees''> <bes'' bes'> |
% 4a(Unessential in B) Bbmajor6b 4b(Unessential in B/T) 6a 
<c''' c''>8 <d''' d''> <d''' d''>4 <bes'' bes'>2 |
% 5b(A susp)(Unessential in S) 1a(Unessential in T) 4a(cad) 
<d''' d''>4 <bes'' bes'> <a'' a'> <bes'' bes'>8 <c''' c''> |
% 1a(Unessential in B) G minor1a(Unessential in T) 5a(Unessential in B) 1b(Unessential in S) 
<c''' c''>4 <a'' a'> <bes'' bes'> <d''' d''> |
% 2b(Unessential in B) 3a(Unessential in B) 6a(Unessential in T) 6b(Unessential in A) 
<bes'' bes'>8 <d''' d''> <f''' f''> <a''' a''> <f''' f''>4 <g''' g''> |
% 1a(Unessential in S) 5c(Unessential in S/B) 1b(Unessential in A) 4a 
<c''' c''> <d''' d''>8. <bes'' bes'>16 <c''' c''>2 |
% 2b(Unessential in A) 1a(Unessential in T/S) 5a(cad) 
<g'' g'>4 <g''' g''>8. <d''' d''>16 <c''' c''>4 <d''' d''>8. <f''' f''>16 |
% 6b(Unessential in B) G minor6b(Unessential in S) 2b 3b(Unessential in S) 
<d''' d''>4 <ees''' ees''> <bes'' bes'> <f''' f''>8. <a''' a''>16 |
% 6a 7b(Unessential in A) 1b(Unessential in B) 5c(Unessential in S) 
<f''' f''>8 <g''' g''> <g''' g''>4 <ees''' ees''>8 <c''' c''> <c''' c''> <a'' a'>16 <a'' a'> |
% 1a(Unessential in S) 6a 2a(Unessential in S) 5a(Unessential in S) 
<bes'' bes'>1 |
% 6a(cad) 
<d''' d''>4 <bes'' bes'> <a'' a'> <bes'' bes'>8 <c''' c''> |
% 1a(Unessential in B) G minor1a(Unessential in T) 5a(Unessential in B) 1b(Unessential in S) 
<c''' c''>4 <a'' a'> <bes'' bes'> <d''' d''> |
% 2b(Unessential in B) 3a(Unessential in B) 6a(Unessential in T) 6b(Unessential in A) 
<bes'' bes'>8 <d''' d''> <f''' f''> <a''' a''> <f''' f''>4 <g''' g''> |
% 1a(Unessential in S) 5c(Unessential in S/B) 1b(Unessential in A) 4a 
<c''' c''> <d''' d''>8. <bes'' bes'>16 <c''' c''>2 |
% 2b(Unessential in A) 1a(Unessential in T/S) 5a(cad) 
<c''' c''>4 <bes''' bes''> <f''' f''> <g''' g''> |
% 5a(Unessential in B) G minor4b(Unessential in A) 3a(T susp)(Unessential in T/B) 6a(Unessential in B/T) 
<f''' f''> <g''' g''> <c''' c''> <d''' d''> |
% 1b(Unessential in T/B) 4a(Unessential in T/A) 2b(Unessential in T/B) 3a(Unessential in B) 
<d''' d''>8 <c''' c''> <bes'' bes'> <d''' d''> <ees''' ees''>4 <a'' a'> |
% 6a(Unessential in B/S) 6a(Unessential in S) 2a(T susp)(Unessential in B/T) 5a(Unessential in B) 
<bes'' bes'>1 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "accordion"
%  Coda
<f'' f'>8 <bes'' bes'> <f''' f''>4 <bes'' bes'> <c''' c''>8 <ees''' ees''> |
% 1a(Unessential in S) Bbmajor5c 1b 2b(Unessential in S) 
<d''' d''>4. \trill <g''' g''>8 <ees''' ees''>4 <bes'' bes'> |
% 3b 6a(Unessential in S) 4b(Unessential in T) 4b(Unessential in B) 
<g'' g'> <f'' f'>8 <g'' g'> <g'' g'>4 <f'' f'> |
% 6a(Unessential in A/T) 5b(Unessential in B/S) 4c(Unessential in A) 1a(Unessential in T) 
<bes'' bes'> <g'' g'>8. <ees'' ees'>16 <f'' f'>4 <ees'' ees'>8 <f'' f'> |
% 4b(Unessential in B/A) 2a(Unessential in S) 1b(Unessential in T) 2b(Unessential in S) 
<f'' f'> <a'' a'> <g'' g'>4 <bes'' bes'>4. \trill <a'' a'>8 |
% 3a(Unessential in S) 6a(Unessential in B) 4b(Unessential in B/T) 1a(Unessential in S/B) 
<g'' g'>4 <ees''' ees''>16 <ees''' ees''> <c''' c''>8 <d''' d''> <g''' g''> <ees''' ees''>4 |
% 6b(Unessential in T) 2a(Unessential in T/S) 6a(Unessential in S) 7b(Unessential in T/A) 
<bes'' bes'>8 <d''' d''> <g''' g''>4 <d''' d''> <c''' c''> |
% 1b(Unessential in T/S) 4a(Unessential in T) 6b 5a(Unessential in T/A(accented)) 
<bes'' bes'>1 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "church organ"
\bar "|." }
partB={ \setup \set Staff.midiInstrument = "acoustic grand"
\time 4/4 \key f \major %{ TODO check it's in all the parts %} ais'2 fis' |
%  1st Subject
\repeat volta 2 {
fis' fis'4 dis' |
gis' ais' ais'2 |
dis'4 b' eis'8 fis' fis'4 |
gis'1 |
fis'2 fis'4 dis' |
gis' ais' ais'2 |
gis'8 dis' fis'4 \trill gis' cis' |
dis'1 |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
ais4 eis' ais' gis'8 fis' |
fis'4 gis' eis'2 |
fis'4 b'8 fis'16 fis' fis'8 ais' ais'4 |
fis'1 |
ais4 eis' ais' gis'8 fis' |
fis'4 gis' eis'2 |
ais4 ais' eis' cis' |
dis'1 |
\bar "||"
\set Staff.midiInstrument = "muted trumpet"
%  Transition
\key bes \major %{ TODO check it's in all the parts %} ees'4 f' d' g' |
g' d' f' d' |
a'2 g' |
%  2nd Subject
\key bes \major %{ TODO check it's in all the parts %} g4 d' d'2 |
ees'4 d' ees'4. bes8 |
bes4 a d'8 c' c'4 |
ees'8 d' d'4 d'2 |
bes4 ees' ees' bes |
ees' c'8 d' d'2 |
bes4 ees' ees' d' |
bes1 |
g4 d' d'2 |
ees'4 d' ees'4. bes8 |
bes4 a d'8 c' c'4 |
ees'8 d' d'4 d'2 |
fis'4 g'8 fis'16 fis' fis'4 g' |
d' c'8 ees' ees'4 d' |
bes ees' ees' d' |
d'1 |
\bar "||"
\set Staff.midiInstrument = "orchestral strings"
%  Codetta
d'4 ees'8. d'16 d'4 fis' |
g' d' ees'2 |
ees'4 d' ees'8 d' d'4 |
b1 }
|
\set Staff.midiInstrument = "french horn"
%  Start of development
\key f \major %{ TODO check it's in all the parts %} ais'2 fis' |
fis' fis'4 dis' |
gis' ais' ais'2 |
dis'4 b' eis'8 fis' fis'4 |
gis'1 |
fis'2 fis'4 dis' |
gis' ais' ais'2 |
gis'8 dis' fis'4 \trill gis' cis' |
dis'1 |
\bar "||"
\set Staff.midiInstrument = "clarinet"
dis'4 fis' eis' %  Sequences
d' |
ees' c'8 d' d'4 f' |
f' f'8 ees' d'4 c' |
d'2 d'4 c' |
bes8 d' d' bes b4 r |
\bar "||"
\set Staff.midiInstrument = "pizzicato strings"
%  Recapitulation
ais'2 fis' |
fis' fis'4 dis' |
gis' ais' ais'2 |
dis'4 b' eis'8 fis' fis'4 |
gis'1 |
fis'2 fis'4 dis' |
gis' ais' ais'2 |
gis'8 dis' fis'4 \trill gis' cis' |
dis'1 |
\bar "||"
\set Staff.midiInstrument = "harmonica"
ais4 eis' ais' gis'8 fis' |
fis'4 gis' eis'2 |
fis'4 b'8 fis'16 fis' fis'8 ais' ais'4 |
fis'1 |
ais4 eis' ais' gis'8 fis' |
fis'4 gis' eis'2 |
ais4 ais' eis' cis' |
dis'1 |
\bar "||"
\set Staff.midiInstrument = "harmonica"
\key bes \major %{ TODO check it's in all the parts %} ees'4 g' bes' g' |
g' f' \mordent ees'2 |
bes4 f' f'2 |
g'4 f' g'4. d'8 |
d'4 c' f'8 ees' ees'4 |
g'8 f' f'4 f'2 |
d'4 g' g' d' |
g' ees'8 f' f'2 |
d'4 g' g' f' |
d'1 |
bes4 f' f'2 |
g'4 f' g'4. d'8 |
d'4 c' f'8 ees' ees'4 |
g'8 f' f'4 f'2 |
a'4 bes'8 a'16 a' a'4 bes' |
f' ees'8 g' g'4 f' |
d' g' g' f' |
f'1 |
\bar "||"
\set Staff.midiInstrument = "church organ"
%  Coda
bes4 f' f' g' |
d' g' bes' ees' |
d'8 bes c'4 ees'8 bes d'4 |
ees'8 bes g4 bes c' |
d'2 ees'4 bes |
d' g' bes' ees'8 f' |
f'4 bes' d' f' |
ees'8 r d'2. |
\bar "||"
\set Staff.midiInstrument = "acoustic grand"
\bar "|." }
partC={ \setup \clef bass
\set Staff.midiInstrument = "english horn"
\time 4/4 \key f \major %{ TODO check it's in all the parts %} dis'4 cis' dis'2 |
%  1st Subject
\repeat volta 2 {
dis'4 cis' dis'8 b ais4 |
dis'4. ais16 ais cis'2 |
ais8 b b16 b eis'8 b4 ais8. \mordent fis16 |
gis1 |
dis'4 cis' dis'8 b ais4 |
dis'4. ais16 ais cis'2 |
b b4 ais |
fis1 |
\bar "||"
\set Staff.midiInstrument = "oboe"
fis4 ais ais cis' |
dis' gis ais2 |
dis'4 fis'8 dis' ais dis' cis'4 |
dis'1 |
fis4 ais ais cis' |
dis' gis ais2 |
fis4 ais8 fis gis4 ais |
fis1 |
\bar "||"
\set Staff.midiInstrument = "reed organ"
%  Transition
\key bes \major %{ TODO check it's in all the parts %} bes4 c'8 bes bes4 g |
bes f c' g |
c'8 a fis4 g2 |
%  2nd Subject
\key bes \major %{ TODO check it's in all the parts %} d4 bes8 g a4 d |
a bes bes8 g ees4 |
d fis g2 |
a4 d8 g fis2 |
ees4 bes a fis |
g fis g fis |
g2 a4 fis |
g1 |
d4 bes8 g a4 d |
a bes bes8 g ees4 |
d fis g2 |
a4 d8 g fis2 |
a4 c' c'8 fis bes \mordent g16 g |
g8 fis g a a g fis4 |
g bes bes8 a a4 \mordent |
b1 |
\bar "||"
\set Staff.midiInstrument = "trombone"
%  Codetta
bes4 a bes a |
g8 c' bes4 ees8 a bes4 |
c' g a fis |
g1 }
|
\set Staff.midiInstrument = "acoustic grand"
%  Start of development
\key f \major %{ TODO check it's in all the parts %} dis'4 cis' dis'2 |
dis'4 cis' dis'8 b ais4 |
dis'4. ais16 ais cis'2 |
ais8 b b16 b eis'8 b4 ais8. \mordent fis16 |
gis1 |
dis'4 cis' dis'8 b ais4 |
dis'4. ais16 ais cis'2 |
b b4 ais |
fis1 |
\bar "||"
\set Staff.midiInstrument = "church organ"
b8 ais ais4 ais %  Sequences
g |
ees8 f ees f g4 a |
bes a8 a bes4 ees |
d f g ees8 f |
fis4 f g r |
\bar "||"
\set Staff.midiInstrument = "harmonica"
%  Recapitulation
dis' cis' dis'2 |
dis'4 cis' dis'8 b ais4 |
dis'4. ais16 ais cis'2 |
ais8 b b16 b eis'8 b4 ais8. \mordent fis16 |
gis1 |
dis'4 cis' dis'8 b ais4 |
dis'4. ais16 ais cis'2 |
b b4 ais |
fis1 |
\bar "||"
\set Staff.midiInstrument = "accordion"
fis4 ais ais cis' |
dis' gis ais2 |
dis'4 fis'8 dis' ais dis' cis'4 |
dis'1 |
fis4 ais ais cis' |
dis' gis ais2 |
fis4 ais8 fis gis4 ais |
fis1 |
\bar "||"
\set Staff.midiInstrument = "pizzicato strings"
\key bes \major %{ TODO check it's in all the parts %} bes4 d' bes8 c' d'4 |
c' bes8. f16 g2 |
f4 d'8 bes c'4 f |
c' d' d'8 bes g4 |
f a bes2 |
c'4 f8 bes a2 |
g4 d' c' a |
bes a bes a |
bes2 c'4 a |
bes1 |
f4 d'8 bes c'4 f |
c' d' d'8 bes g4 |
f a bes2 |
c'4 f8 bes a2 |
c'4 ees' ees'8 a d' \mordent bes16 bes |
bes8 a bes c' c' bes a4 |
bes d' d'8 c' c'4 \mordent |
d'1 |
\bar "||"
\set Staff.midiInstrument = "trombone"
%  Coda
d4 a bes g |
a bes ees'8 bes ees4 |
bes8 g f4 ees f16 f d8 |
ees2 f8 g g4 |
a bes bes8 g d4 |
g8 a g c' g4 a8 bes |
bes d' bes8. g16 g4 a8 c' |
bes1 |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
\bar "|." }
partD={ \setup \clef bass
\set Staff.midiInstrument = "cello"
\time 4/4 \key f \major %{ TODO check it's in all the parts %} dis4 ais, b,2 |
%  1st Subject
\repeat volta 2 {
dis4 ais, b, fis |
gis dis ais2 |
fis4 gis cis dis |
gis,1 |
dis4 ais, b, fis |
gis dis ais2 |
gis,4 dis eis ais, |
dis1 |
\bar "||"
\set Staff.midiInstrument = "church organ"
dis4 eis fis4. cis8 |
b,4. gis,8 ais,2 |
b8 fis dis4 dis ais |
b1 |
dis4 eis fis4. cis8 |
b,4. gis,8 ais,2 |
dis4 fis8 \trill dis eis4 ais, |
dis1 |
\bar "||"
\set Staff.midiInstrument = "pizzicato strings"
%  Transition
\key bes \major %{ TODO check it's in all the parts %} g,8 bes, a,4 bes, ees \trill |
g,8 a, bes,16 bes, a,8 a,4 bes,8 bes, |
f4 d ees2 |
%  2nd Subject
\key bes \major %{ TODO check it's in all the parts %} g,8 a, g,4 d8 c bes,4 |
c8 a, bes, d16 d ees4 g, |
g, a,16 a, bes,8 bes,4 c |
c g, d2 |
g,8 bes, g4 c d |
ees a, bes,8 g, a,4 |
g, ees a, d |
ees1 |
g,8 a, g,4 d8 c bes,4 |
c8 a, bes, d16 d ees4 g, |
g, a,16 a, bes,8 bes,4 c |
c g, d2 |
d8 fis ees4 bes,8 d ees bes, |
bes, d c4 c8 bes, bes,16 bes, d8 |
ees d ees4 a,8 c d8. a,16 |
g,1 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
%  Codetta
bes,8 d c4 g, d |
ees d c ees |
c bes, \trill a, d \trill |
g,1 }
|
\set Staff.midiInstrument = "string ensemble 2"
%  Start of development
\key f \major %{ TODO check it's in all the parts %} dis4 ais, b,2 |
dis4 ais, b, fis |
gis dis ais2 |
fis4 gis cis dis |
gis,1 |
dis4 ais, b, fis |
gis dis ais2 |
gis,4 dis e ais, |
dis1 |
\bar "||"
\set Staff.midiInstrument = "harpsichord"
gis,4 dis \trill ais, %  Sequences
bes, |
g,8 bes, c4 bes, c |
f2 bes,4 c8 g, |
g,4 a, bes,8 a, a,4 |
d d16 d bes,8 g,4 r |
\bar "||"
\set Staff.midiInstrument = "pizzicato strings"
%  Recapitulation
dis ais, b,2 |
dis4 ais, b, fis |
gis dis ais2 |
fis4 gis cis dis |
gis,1 |
dis4 ais, b, fis |
gis dis ais2 |
gis,4 dis eis ais, |
dis1 |
\bar "||"
\set Staff.midiInstrument = "choir aahs"
dis4 eis fis4. cis8 |
b,4. gis,8 ais,2 |
b8 fis dis4 dis ais |
b1 |
dis4 eis fis4. cis8 |
b,4. gis,8 ais,2 |
dis4 fis8 \trill dis eis4 ais, |
dis1 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
\key bes \major %{ TODO check it's in all the parts %} ees8 bes, bes,4 g,8 f, g,4 |
a, bes, ees2 |
bes,8 c bes,4 f8 ees d4 |
ees8 c d f16 f g4 bes, |
bes, c16 c d8 d4 ees |
ees bes, f2 |
bes,8 d bes4 ees f |
g c d8 bes, c4 |
bes, g c f |
g1 |
bes,8 c bes,4 f8 ees d4 |
ees8 c d f16 f g4 bes, |
bes, c16 c d8 d4 ees |
ees bes, f2 |
f8 a g4 d8 f g d |
d f ees4 ees8 d d16 d f8 |
g f g4 c8 ees f8. c16 |
bes,1 |
\bar "||"
\set Staff.midiInstrument = "trombone"
%  Coda
bes,4 c d ees |
f g g g,8 f, |
g,4 a,8 \trill c bes,2 |
g,8 bes, c4 d ees |
d g8 d g, bes, bes, a, |
bes,4 c g, c |
d ees bes, f |
bes,1 |
\bar "||"
\set Staff.midiInstrument = "cello"
\bar "|." }
partE={ \setup \clef bass
\set Staff.midiInstrument = "woodblock"
\time 4/4 \key f \major %{ TODO check it's in all the parts %} %  1st Subject
R1 |
\repeat volta 2 {
ais,1 |
ais, |
R1*2 |
ais,1 |
ais, |
dis, |
dis, |
\bar "||"
\set Staff.midiInstrument = "tubular bells"
ais, |
ais, |
R1*2 |
ais,1 |
ais, |
dis, |
dis, |
\bar "||"
\set Staff.midiInstrument = "fx 1 (rain)"
%  Transition
\key bes \major %{ TODO check it's in all the parts %} %  2nd Subject
R1*3 |
\key bes \major %{ TODO check it's in all the parts %} d,1 |
d, |
d, |
d, |
R1*4 |
d,1 |
d, |
d, |
d, |
R1*4 |
\bar "||"
\set Staff.midiInstrument = "tubular bells"
%  Codetta
g,1 |
g, |
g, |
g, }
|
\set Staff.midiInstrument = "choir aahs"
%  Start of development
\key f \major %{ TODO check it's in all the parts %} R1 |
ais,1 |
ais, |
R1*2 |
ais,1 |
ais, |
dis, |
dis, |
\bar "||"
\set Staff.midiInstrument = "woodblock"
%  Sequences
R1*5 |
\bar "||"
\set Staff.midiInstrument = "melodic tom"
%  Recapitulation
R1 |
ais,1 |
ais, |
R1*2 |
ais,1 |
ais, |
dis, |
dis, |
\bar "||"
\set Staff.midiInstrument = "tubular bells"
ais, |
ais, |
R1*2 |
ais,1 |
ais, |
dis, |
dis, |
\bar "||"
\set Staff.midiInstrument = "english horn"
\key bes \major %{ TODO check it's in all the parts %} R1*2 |
f,1 |
f, |
f, |
f, |
R1*4 |
f,1 |
f, |
f, |
f, |
R1*4 |
\bar "||"
\set Staff.midiInstrument = "english horn"
%  Coda
bes,1 |
bes, |
bes, |
bes, |
bes, |
bes, |
bes, |
bes, |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
%  Random number seed was 53850
%  Current time is Sat Sep 14 13:43:08 1996
\bar "|." }
\bookpart{ %{ TODO add \header{} block for the score %}
\score { <<
\new Staff << \context Voice = PartAB { << \partA \\ \partB >> } >>
\new Staff << \context Voice = PartCD { << \partC \\ \partD >> } >>
\new Staff << \context Voice = PartE { \partE } >>
>> \layout{} } \score { \unfoldRepeats { <<
\new Staff << \context Voice = PartA { \partA } >>
\new Staff << \context Voice = PartB { \partB } >>
\new Staff << \context Voice = PartC { \partC } >>
\new Staff << \context Voice = PartD { \partD } >>
\new Staff << \context Voice = PartE { \partE } >>
>> } \midi{} }
}
