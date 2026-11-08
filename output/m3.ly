\version "2.12.2"
#(set-global-staff-size 20) % (TODO adjust as needed: 25.2 is larger, 17.82 or 15.87 is smaller)
setup={\override Staff.TimeSignature #'style = #'numbered
\override Score.Hairpin #'after-line-breaking = ##t
#(set-accidental-style 'modern-cautionary) % not MWR behaviour but a nice addition
\set Score.skipBars = ##t % MWR needs $# to turn this on but we might as well have it by default
}
partA={ \setup 
%  Movement 3
\tempo 4 = 96 \override Score.BarNumber #'break-visibility = #end-of-line-invisible
\set Score.barNumberVisibility = #(every-nth-bar-number-visible 5)
\set Staff.midiInstrument = "clav"
\time 3/4 \key a \major %{ TODO check it's in all the parts %} <e''' e''>4 <fis''' fis''> <d''' d''>8 <cis''' cis''> |
% 1a(Unessential in T) A major4a 2a(Unessential in S/A) 
<cis''' cis''>4 <e''' e''> <e''' e''> |
% 6b 5b(Unessential in T/A) 1a(Unessential in B) 
<d''' d''> <cis''' cis''> <b'' b'> |
% 4a(Unessential in B) 6a(Unessential in B) 2a 
<fis''' fis''> <a'' a'> <a'' a'> |
% 6b 1a(Unessential in T/A) 4a(cad) 
<a'' a'>8 <d''' d''> <d''' d''>4 <cis''' cis''>8 <fis''' fis''> |
% 4a(Unessential in S) A major2a(Unessential in B) 6b(Unessential in S) 
<fis''' fis''>4 <d''' d''> <fis'' fis'> |
% 4a 7b 6a(Unessential in B) 
<gis'' gis'> <a'' a'> <cis''' cis''>8 <b'' b'> |
% 5a(Unessential in T) 4b 1a(Unessential in S) 
<b'' b'>2. |
% 5a(cad) 
<e''' e''>4 <fis''' fis''> <d''' d''>8 <cis''' cis''> |
% 1a(Unessential in T) A major4a 2a(Unessential in S/A) 
<cis''' cis''>4 <e''' e''> <e''' e''> |
% 6b 5b(Unessential in T/A) 1a(Unessential in B) 
<d''' d''> <cis''' cis''> <b'' b'> |
% 4a(Unessential in B) 6a(Unessential in B) 2a 
<fis''' fis''> <a'' a'> <a'' a'> |
% 6b 1a(Unessential in T/A) 4a(cad) 
<gis'' gis'> <a'' a'> <gis'' gis'>8 <fis'' fis'> |
% 5a(Unessential in T/A) A major1b(Unessential in S(accented)) 2b 
<cis''' cis''> <e''' e''> <cis''' cis''>4 <d''' d''> |
% 3a(Unessential in S) 6a 2a(Unessential in B) 
<a'' a'>8 <b'' b'> <b'' b'>4 <fis'' fis'>8 <a'' a'> |
% 1b(Unessential in T/S) 2b 4a(Unessential in B/S) 
<a'' a'>2. |
% 1a(cad) 
<b'' b'>4 <a'' a'> <a'' a'> |
% 5b A major1a 5a(Unessential in T) - Modulating to G major
<e'' e'>8 <fis'' fis'> <g'' g'>4 <b'' b'> |
% 6a(Unessential in S) 6a 1a 
<a'' a'> <g'' g'> \trill <c''' c''> |
% 2b(Unessential in T) 1c 4b(Unessential in T) 
<g''' g''> <b'' b'>8. <c''' c''>16 <c''' c''>4 |
% 6a(Unessential in T) 1a(Unessential in A/S) 4a(cad) 
<b'' b'> <c''' c''> <g'' g'> |
% 6b(Unessential in B) 2a 1b(Unessential in B) 
<e''' e''>8 <b'' b'> <b'' b'>4 <a'' a'> |
% 6b(Unessential in B/S) 6a 2a 
<g'' g'> <d''' d''> <e''' e''> |
% 1b(Unessential in T) 3a(Unessential in T) 5a(Unessential in S(accented)) - Modulating to A major
<d''' d''>8 r <cis''' cis''>2 |
% 6a(cad) 
<e''' e''>4 <fis''' fis''> <d''' d''>8 <cis''' cis''> |
% 1a(Unessential in T) A major4a 2a(Unessential in S/A) 
<cis''' cis''>4 <e''' e''> <e''' e''> |
% 6b 5b(Unessential in T/A) 1a(Unessential in B) 
<d''' d''> <cis''' cis''> <b'' b'> |
% 4a(Unessential in B) 6a(Unessential in B) 2a 
<fis''' fis''> <a'' a'> <a'' a'> |
% 6b 1a(Unessential in T/A) 4a(cad) 
<gis'' gis'> <a'' a'> <gis'' gis'>8 <fis'' fis'> |
% 5a(Unessential in T/A) A major1b(Unessential in S(accented)) 2b 
<cis''' cis''> <e''' e''> <cis''' cis''>4 <d''' d''> |
% 3a(Unessential in S) 6a 2a(Unessential in B) 
<a'' a'>8 <b'' b'> <b'' b'>4 <fis'' fis'>8 <a'' a'> |
% 1b(Unessential in T/S) 2b 4a(Unessential in B/S) 
<a'' a'>2. |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "clarinet"
\key e \major %{ TODO check it's in all the parts %} <b'' b'>4 <a'' a'> <b'' b'>8 <cis''' cis''> |
% 1a(Unessential in T) E major4a(Unessential in T/A) 3a(Unessential in S) 
<cis''' cis''>4 <e''' e''> <cis''' cis''> |
% 6a(Unessential in B) 1c(Unessential in T) 4a(Unessential in T) 
<b'' b'>2 <e''' e''>8 <fis''' fis''> |
% 1a(Unessential in T) 1b(Unessential in A) 6a(Unessential in S) 
<fis''' fis''> <e''' e''> <e''' e''>4 <cis''' cis''> |
% 5b(Unessential in S) 1a(Unessential in B) 4a(cad) 
<cis''' cis''> <b'' b'> <gis'' gis'> |
% 2a E major5b(Unessential in B/T) 1a(Unessential in T) 
<cis''' cis''> <e''' e''> <e''' e''>8 <fis''' fis''> |
% 6b 1b(Unessential in T/A) 4a(Unessential in S) 
<fis''' fis''>4 <cis''' cis''> <b'' b'> |
% 2a(Unessential in A) 6b(Unessential in A) 1a(Unessential in A(accented)) 
<a'' a'>2. |
% 4a(cad) 
<b'' b'>4 <a'' a'> <b'' b'>8 <cis''' cis''> |
% 1a(Unessential in T) E major4a(Unessential in T/A) 3a(Unessential in S) 
<cis''' cis''>4 <e''' e''> <cis''' cis''> |
% 6a(Unessential in B) 1c(Unessential in T) 4a(Unessential in T) 
<b'' b'>2 <e''' e''>8 <fis''' fis''> |
% 1a(Unessential in T) 1b(Unessential in A) 6a(Unessential in S) 
<fis''' fis''> <e''' e''> <e''' e''>4 <cis''' cis''> |
% 5b(Unessential in S) 1a(Unessential in B) 4a(cad) 
<cis''' cis''> <a'' a'> <a'' a'>8 <b'' b'> |
% 4a(Unessential in T) E major4b(Unessential in A) 2a(Unessential in T/S) 
<b'' b'> <cis''' cis''> <cis''' cis''>4 <fis''' fis''> |
% 1b(Unessential in S) 4a(Unessential in T) 5b 
<e''' e''>8 <b'' b'> <cis''' cis''>16 <cis''' cis''> <dis''' dis''>8 <e''' e''> <cis''' cis''> |
% 1a(Unessential in S) 2b(Unessential in S) 4a(Unessential in S) 
<e'' e'>2. |
% 1a(cad) 
<dis''' dis''>8 <e''' e''> <e''' e''>4 <cis''' cis''> |
% 5a(Unessential in S) E major4b(Unessential in B) 6a(Unessential in B) 
<fis''' fis''> <b'' b'>8. <e''' e''>16 <c''' c''>4 |
% 5b(Unessential in A) 1a(Unessential in S) 5a(Unessential in T) - Modulating to Dbmajor
<des''' des''> <f''' f''> <des''' des''> |
% 1a(Unessential in B) 6a 4b 
<ees''' ees''> <f''' f''> <des''' des''> |
% 5b(Unessential in B) 1a(Unessential in T) 4a(cad) 
<ees''' ees''>8 <ges''' ges''> <ges''' ges''>4 <bes'' bes'> |
% 2a(Unessential in S/B) 2a(Unessential in T) 6b 
<c''' c''> <des''' des''> <bes'' bes'> |
% 5a(Unessential in B) 6a 2a(Unessential in B) 
<f''' f''> <ges''' ges''> \trill <aes''' aes''>8 <fis''' fis''> |
% 6b(Unessential in B) 4a(Unessential in S(accented)) 5a - Modulating to E major
<cis''' cis''>2. |
% 6a(cad) 
<b'' b'>4 <a'' a'> <b'' b'>8 <cis''' cis''> |
% 1a(Unessential in T) E major4a(Unessential in T/A) 3a(Unessential in S) 
<cis''' cis''>4 <e''' e''> <cis''' cis''> |
% 6a(Unessential in B) 1c(Unessential in T) 4a(Unessential in T) 
<b'' b'>2 <e''' e''>8 <fis''' fis''> |
% 1a(Unessential in T) 1b(Unessential in A) 6a(Unessential in S) 
<fis''' fis''> <e''' e''> <e''' e''>4 <cis''' cis''> |
% 5b(Unessential in S) 1a(Unessential in B) 4a(cad) 
<cis''' cis''> <a'' a'> <a'' a'>8 <b'' b'> |
% 4a(Unessential in T) E major4b(Unessential in A) 2a(Unessential in T/S) 
<b'' b'> <cis''' cis''> <cis''' cis''>4 <fis''' fis''> |
% 1b(Unessential in S) 4a(Unessential in T) 5b 
<e''' e''>8 <b'' b'> <cis''' cis''>16 <cis''' cis''> <dis''' dis''>8 <e''' e''> <cis''' cis''> |
% 1a(Unessential in S) 2b(Unessential in S) 4a(Unessential in S) 
<e'' e'>2. |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "piccolo"
\key a \major %{ TODO check it's in all the parts %} <e''' e''>4 <fis''' fis''> <d''' d''>8 <cis''' cis''> |
% 1a(Unessential in T) A major4a 2a(Unessential in S/A) 
<cis''' cis''>4 <e''' e''> <e''' e''> |
% 6b 5b(Unessential in T/A) 1a(Unessential in B) 
<d''' d''> <cis''' cis''> <b'' b'> |
% 4a(Unessential in B) 6a(Unessential in B) 2a 
<fis''' fis''> <a'' a'> <a'' a'> |
% 6b 1a(Unessential in T/A) 4a(cad) 
<a'' a'>8 <d''' d''> <d''' d''>4 <cis''' cis''>8 <fis''' fis''> |
% 4a(Unessential in S) A major2a(Unessential in B) 6b(Unessential in S) 
<fis''' fis''>4 <d''' d''> <fis'' fis'> |
% 4a 7b 6a(Unessential in B) 
<gis'' gis'> <a'' a'> <cis''' cis''>8 <b'' b'> |
% 5a(Unessential in T) 4b 1a(Unessential in S) 
<b'' b'>2. |
% 5a(cad) 
<e''' e''>4 <fis''' fis''> <d''' d''>8 <cis''' cis''> |
% 1a(Unessential in T) A major4a 2a(Unessential in S/A) 
<cis''' cis''>4 <e''' e''> <e''' e''> |
% 6b 5b(Unessential in T/A) 1a(Unessential in B) 
<d''' d''> <cis''' cis''> <b'' b'> |
% 4a(Unessential in B) 6a(Unessential in B) 2a 
<fis''' fis''> <a'' a'> <a'' a'> |
% 6b 1a(Unessential in T/A) 4a(cad) 
<gis'' gis'> <a'' a'> <gis'' gis'>8 <fis'' fis'> |
% 5a(Unessential in T/A) A major1b(Unessential in S(accented)) 2b 
<cis''' cis''> <e''' e''> <cis''' cis''>4 <d''' d''> |
% 3a(Unessential in S) 6a 2a(Unessential in B) 
<a'' a'>8 <b'' b'> <b'' b'>4 <fis'' fis'>8 <a'' a'> |
% 1b(Unessential in T/S) 2b 4a(Unessential in B/S) 
<a'' a'>2. |
% 1a(cad) 
<b'' b'>4 <a'' a'> <a'' a'> |
% 5b A major1a 5a(Unessential in T) - Modulating to G major
<e'' e'>8 <fis'' fis'> <g'' g'>4 <b'' b'> |
% 6a(Unessential in S) 6a 1a 
<a'' a'> <g'' g'> \trill <c''' c''> |
% 2b(Unessential in T) 1c 4b(Unessential in T) 
<g''' g''> <b'' b'>8. <c''' c''>16 <c''' c''>4 |
% 6a(Unessential in T) 1a(Unessential in A/S) 4a(cad) 
<b'' b'> <c''' c''> <g'' g'> |
% 6b(Unessential in B) 2a 1b(Unessential in B) 
<e''' e''>8 <b'' b'> <b'' b'>4 <a'' a'> |
% 6b(Unessential in B/S) 6a 2a 
<g'' g'> <d''' d''> <e''' e''> |
% 1b(Unessential in T) 3a(Unessential in T) 5a(Unessential in S(accented)) - Modulating to A major
<d''' d''>8 r <cis''' cis''>2 |
% 6a(cad) 
<e''' e''>4 <fis''' fis''> <d''' d''>8 <cis''' cis''> |
% 1a(Unessential in T) A major4a 2a(Unessential in S/A) 
<cis''' cis''>4 <e''' e''> <e''' e''> |
% 6b 5b(Unessential in T/A) 1a(Unessential in B) 
<d''' d''> <cis''' cis''> <b'' b'> |
% 4a(Unessential in B) 6a(Unessential in B) 2a 
<fis''' fis''> <a'' a'> <a'' a'> |
% 6b 1a(Unessential in T/A) 4a(cad) 
<gis'' gis'> <a'' a'> <gis'' gis'>8 <fis'' fis'> |
% 5a(Unessential in T/A) A major1b(Unessential in S(accented)) 2b 
<cis''' cis''> <e''' e''> <cis''' cis''>4 <d''' d''> |
% 3a(Unessential in S) 6a 2a(Unessential in B) 
<a'' a'>8 <b'' b'> <b'' b'>4 <fis'' fis'>8 <a'' a'> |
% 1b(Unessential in T/S) 2b 4a(Unessential in B/S) 
<a'' a'>2. |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "reed organ"
\bar "|." }
partB={ \setup \set Staff.midiInstrument = "muted trumpet"
\time 3/4 e'4 d' f'8 e' |
f'4 e'8 d' c'4 |
f' a' f' |
f' c'8 e' d'4 |
d' f' f' |
a' d' c' |
e' d' e' |
g'2. |
e'4 d' f'8 e' |
f'4 e'8 d' c'4 |
f' a' f' |
f' c'8 e' d'4 |
e'8 d' e'4 d' |
e' f' f' |
e' b d' |
e'2. |
e'2 d'4 |
b e' d' |
e' b g' |
e' d'8 e' e'4 |
b a d' |
b e' e' |
d' b b |
f'2. |
e'4 d' f'8 e' |
f'4 e'8 d' c'4 |
f' a' f' |
f' c'8 e' d'4 |
e'8 d' e'4 d' |
e' f' f' |
e' b d' |
e'2. |
\bar "||"
\set Staff.midiInstrument = "acoustic grand"
\key e \major %{ TODO check it's in all the parts %} gis'4 e'8 fis' gis'4 |
gis' e' a' |
gis' e'16 e' fis'8 gis'4 |
b'2 a'4 |
fis'2 e'4 |
gis' e'8 \trill gis' a'4 |
cis'8 fis' gis'16 gis' e'8 e'4 |
fis'8 r e'2 |
gis'4 e'8 fis' gis'4 |
gis' e' a' |
gis' e'16 e' fis'8 gis'4 |
b'2 a'4 |
a' e'8 \trill fis' fis'4 |
e' a' b' |
gis' fis' cis' |
b2. |
fis'4 a' gis' |
fis'8 b' gis'4 ees' |
f' des' ges' |
ees' aes' ges' |
ges' bes' f' |
aes' f' ges' |
bes'2 b'4 |
gis'2. |
gis'4 e'8 fis' gis'4 |
gis' e' a' |
gis' e'16 e' fis'8 gis'4 |
b'2 a'4 |
a' e'8 \trill fis' fis'4 |
e' a' b' |
gis' fis' cis' |
b2. |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
\key a \major %{ TODO check it's in all the parts %} e'4 d' fis'8 e' |
fis'4 e'8 d' cis'4 |
fis' a' fis' |
fis' cis'8 e' d'4 |
d' fis' fis' |
a' d' cis' |
e' d' e' |
gis'2. |
e'4 d' fis'8 e' |
fis'4 e'8 d' cis'4 |
fis' a' fis' |
fis' cis'8 e' d'4 |
e'8 d' e'4 d' |
e' fis' fis' |
e' b d' |
e'2. |
e'2 d'4 |
b e' d' |
e' b g' |
e' d'8 e' e'4 |
b a d' |
b e' e' |
d' b b |
fis'2. |
e'4 d' fis'8 e' |
fis'4 e'8 d' cis'4 |
fis' a' fis' |
fis' cis'8 e' d'4 |
e'8 d' e'4 d' |
e' fis' fis' |
e' b d' |
e'2. |
\bar "||"
\set Staff.midiInstrument = "marimba"
\bar "|." }
partC={ \setup \clef bass
\set Staff.midiInstrument = "acoustic grand"
\time 3/4 c'8 a a4 b |
c' b8 g a4 |
a f' d' |
c' a8 \trill g f4 |
f b f |
d' g a |
b8 a a4 a |
b2. |
c'8 a a4 b |
c' b8 g a4 |
a f' d' |
c' a8 \trill g f4 |
b8 g e4 b |
g a f |
a8 e f4 a |
c'2. |
b4 c' f8 g |
g4 b g |
e8 a g4 g8 c' |
b g g4 g |
e2 d4 |
e g c' |
g8 d f8. g16 gis4 |
a2. |
c'8 a a4 b |
c' b8 g a4 |
a f' d' |
c' a8 \trill g f4 |
b8 g e4 b |
g a f |
a8 e f4 a |
c'2. |
\bar "||"
\set Staff.midiInstrument = "reed organ"
\key e \major %{ TODO check it's in all the parts %} b8 e' cis' dis' dis'4 |
e' gis8. a16 a8 b |
b gis e4 cis' |
b gis e' |
a b8 cis' b cis' |
cis'4 b8 cis' cis'4 |
a cis' gis |
cis'2. |
b8 e' cis' dis' dis'4 |
e' gis8. a16 a8 b |
b gis e4 cis' |
b gis e' |
e'8 cis' a4 cis'8 b |
b4 e'8 \trill fis' fis'4 |
b cis' a |
gis2. |
b4 a e' |
b2 aes8 bes |
aes4 bes \trill des' |
aes4. des'8 bes4 |
ees' bes8 \trill c' bes4 |
ees' bes bes |
bes ges' dis' |
e'2. |
b8 e' cis' dis' dis'4 |
e' gis8. a16 a8 b |
b gis e4 cis' |
b gis e' |
e'8 cis' a4 cis'8 b |
b4 e'8 \trill fis' fis'4 |
b cis' a |
gis2. |
\bar "||"
\set Staff.midiInstrument = "harmonica"
\key a \major %{ TODO check it's in all the parts %} cis'8 a a4 b |
cis' b8 gis a4 |
a fis' d' |
cis' a8 \trill gis fis4 |
fis b fis |
d' gis a |
b8 a a4 a |
b2. |
cis'8 a a4 b |
cis' b8 gis a4 |
a fis' d' |
cis' a8 \trill gis fis4 |
b8 gis e4 b |
gis a fis |
a8 e fis4 a |
cis'2. |
b4 cis' fis8 g |
g4 b g |
e8 a g4 g8 c' |
b g g4 g |
e2 d4 |
e g c' |
g8 d fis8. g16 gis4 |
a2. |
cis'8 a a4 b |
cis' b8 gis a4 |
a fis' d' |
cis' a8 \trill gis fis4 |
b8 gis e4 b |
gis a fis |
a8 e fis4 a |
cis'2. |
\bar "||"
\set Staff.midiInstrument = "harmonica"
\bar "|." }
partD={ \setup \clef bass
\set Staff.midiInstrument = "trombone"
\time 3/4 a,4 d b, |
a, g, a,8 c |
d f f c b,4 |
a,2 d4 |
d b,8 a,16 a, a,4 |
d b, f8 c |
e4 f a, |
e2. |
a,4 d b, |
a, g, a,8 c |
d f f c b,4 |
a,2 d4 |
e c d |
c f b,8 c |
c4 d d8 a, |
a,2. |
g4 a, d |
e2 g,4 |
c d e |
e g, c |
g,8 b, a,4 b,8 g, |
g, b, e4 a, |
b,2 e4 |
f2. |
a,4 d b, |
a, g, a,8 c |
d f f c b,4 |
a,2 d4 |
e c d |
c f b,8 c |
c4 d d8 a, |
a,2. |
\bar "||"
\set Staff.midiInstrument = "church organ"
\key e \major %{ TODO check it's in all the parts %} e4 a gis |
cis8 b, b,4 a, |
e gis, cis |
dis e16 e b,8 a,4 |
fis dis8. fis16 e4 |
e gis a |
fis e e |
a,2. |
e4 a gis |
cis8 b, b,4 a, |
e gis, cis |
dis e16 e b,8 a,4 |
a cis fis |
gis a dis |
e a a, |
e2. |
b,4 cis8 b, cis dis |
dis4 e aes, |
des8 c bes,4 bes, |
c8 ees des4 ges |
ees8 ges ees4 des |
aes,8 bes, bes,4 ees8 bes, |
des f ges4 b, |
cis2. |
e4 a gis |
cis8 b, b,4 a, |
e gis, cis |
dis e16 e b,8 a,4 |
a cis fis |
gis a dis |
e a a, |
e2. |
\bar "||"
\set Staff.midiInstrument = "acoustic grand"
\key a \major %{ TODO check it's in all the parts %} a,4 d b, |
a, gis, a,8 cis |
d fis fis cis b,4 |
a,2 d4 |
d b,8 a,16 a, a,4 |
d b, fis8 cis |
e4 fis a, |
e2. |
a,4 d b, |
a, gis, a,8 cis |
d fis fis cis b,4 |
a,2 d4 |
e cis d |
cis fis b,8 cis |
cis4 d d8 a, |
a,2. |
gis4 a, d |
e2 g,4 |
c d e |
e g, c |
g,8 b, a,4 b,8 g, |
g, b, e4 a, |
b,2 e4 |
fis2. |
a,4 d b, |
a, gis, a,8 cis |
d fis fis cis b,4 |
a,2 d4 |
e cis d |
cis fis b,8 cis |
cis4 d d8 a, |
a,2. |
\bar "||"
\set Staff.midiInstrument = "acoustic grand"
\bar "|." }
partE={ \setup \clef bass
\set Staff.midiInstrument = "choir aahs"
\time 3/4 r2 r4 |
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
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "melodic tom"
\key e \major %{ TODO check it's in all the parts %} r2 r4 |
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
e,2 e,4 |
e,2 e,4 |
e,2 e,4 |
e,2 e,4 |
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
e,2 e,4 |
e,2 e,4 |
e,2 e,4 |
e,2 e,4 |
\bar "||"
\set Staff.midiInstrument = "timpani"
\key a \major %{ TODO check it's in all the parts %} r2 r4 |
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
r2 r4 |
\bar "||"
\set Staff.midiInstrument = "fx 1 (rain)"
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
