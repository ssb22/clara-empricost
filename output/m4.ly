\version "2.12.2"
#(set-global-staff-size 20) % (TODO adjust as needed: 25.2 is larger, 17.82 or 15.87 is smaller)
setup={\override Staff.TimeSignature #'style = #'numbered
\override Score.Hairpin #'after-line-breaking = ##t
#(set-accidental-style 'modern-cautionary) % not MWR behaviour but a nice addition
\set Score.skipBars = ##t % MWR needs $# to turn this on but we might as well have it by default
}
partA={ \setup 
%  Movement 4
\tempo 4 = 144 \override Score.BarNumber #'break-visibility = #end-of-line-invisible
\set Score.barNumberVisibility = #(every-nth-bar-number-visible 5)
\set Staff.midiInstrument = "piccolo"
\time 2/4 \key g \major %{ TODO check it's in all the parts %} r4 <a'' a'>8 <d''' d''> |
% 5b(Unessential in B/S) G major
<d''' d''>4 <a'' a'> |
% 1a(Unessential in B) 5c 
<g'' g'>2 |
% 1b 1a 
<a'' a'>4 <c''' c''> |
% 2b(Unessential in A) 4b(Unessential in T/B) 
<d''' d''> <c''' c''>8 <b'' b'> |
% 4a(Unessential in S) G major
<b'' b'> <a'' a'> <b'' b'>4 |
% 6b(Unessential in S) 3b(Unessential in T) 
<e'' e'> <a'' a'>8 <b'' b'> |
% 6a(Unessential in T/B) 5a(Unessential in S) 
<c''' c''> <a'' a'> <b'' b'>4 \trill |
% 7b(Unessential in S) 1a 
<a'' a'> <a'' a'>8 <d''' d''> |
% 5b(Unessential in B/S) G major
<d''' d''>4 <a'' a'> |
% 1a(Unessential in B) 5c 
<g'' g'>2 |
% 1b 1a 
<a'' a'>4 <c''' c''> |
% 2b(Unessential in A) 4b(Unessential in T/B) 
<d''' d''> <e'' e'> |
% 6b G major
<e''' e''> <b'' b'>8. <g'' g'>16 |
% 6b(Unessential in T) 6a(Unessential in S/A) 
<a'' a'>4 <g'' g'> |
% 2a(Unessential in B) 1b(Unessential in B) 
<a'' a'> <e'' e'> |
% 2b 4a(Unessential in B) 
<g'' g'> r |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "choir aahs"
\key g \major %{ TODO check it's in all the parts %} <e''' e''>8 <fis''' fis''> <e''' e''>4 |
% 1b(Unessential in S) E minor1b(Unessential in T) 
<g''' g''>8 <a''' a''> <g''' g''>4 |
% 6a(Unessential in S) 1c(Unessential in T) 
<fis''' fis''> <e''' e''> |
% 2b(Unessential in B) 1a 
<dis''' dis''>2 |
% 5a(cad) 
<e''' e''>4 <dis''' dis''> |
% 6a(Unessential in T/A) E minor5a(Unessential in T/A) 
<e''' e''> <g''' g''> |
% 4b(Unessential in B) 3b(Unessential in S(accented)) 
<a''' a''>8 <g''' g''> <e''' e''>4 |
% 6a 1b 
<fis''' fis''>2 |
% 5a(cad) 
<e''' e''>8 <fis''' fis''> <e''' e''>4 |
% 1b(Unessential in S) E minor1b(Unessential in T) 
<g''' g''>8 <a''' a''> <g''' g''>4 |
% 6a(Unessential in S) 1c(Unessential in T) 
<fis''' fis''> <e''' e''> |
% 2b(Unessential in B) 1a 
<dis''' dis''>2 |
% 5a(cad) 
<g''' g''>4 <e''' e''> |
% 6b(Unessential in B/T) E minor1b(Unessential in T) 
<e''' e''> <g''' g''>8 <e''' e''> |
% 4a(Unessential in T/B) 6b(Unessential in A/S) 
<fis''' fis''> <e''' e''> <dis''' dis''>4 |
% 2a(Unessential in T/S) 5a 
<e''' e''>2 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "piccolo"
\key g \major %{ TODO check it's in all the parts %} r4 <a'' a'>8 <d''' d''> |
% 5b(Unessential in B/S) G major
<d''' d''>4 <a'' a'> |
% 1a(Unessential in B) 5c 
<g'' g'>2 |
% 1b 1a 
<a'' a'>4 <c''' c''> |
% 2b(Unessential in A) 4b(Unessential in T/B) 
<d''' d''> <e'' e'> |
% 6b G major
<e''' e''> <b'' b'>8. <g'' g'>16 |
% 6b(Unessential in T) 6a(Unessential in S/A) 
<a'' a'>4 <g'' g'> |
% 2a(Unessential in B) 1b(Unessential in B) 
<a'' a'> <e'' e'> |
% 2b 4a(Unessential in B) 
<g'' g'> r |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "piccolo"
\key d \major %{ TODO check it's in all the parts %} <fis''' fis''> <b'' b'> |
% 1a(Unessential in A) D major2b 
<fis''' fis''> <e''' e''> |
% 6b(Unessential in B) 2a 
<d''' d''> <cis''' cis''> |
% 1b(Unessential in T) 5a 
<d''' d''>2 |
% 6a(cad) 
<g''' g''>8 <d''' d''> <fis''' fis''> <e''' e''> |
% 4a(Unessential in S) D major1a(Unessential in S) 
<e''' e''>4 <d''' d''>8. <cis''' cis''>16 |
% 2b 1c(Unessential in S) 
<d''' d''>4 <g''' g''> |
% 6a 4b 
<cis''' cis''>2 |
% 5a(cad) 
<fis''' fis''>4 <b'' b'> |
% 1a(Unessential in A) D major2b 
<fis''' fis''> <e''' e''> |
% 6b(Unessential in B) 2a 
<d''' d''> <cis''' cis''> |
% 1b(Unessential in T) 5a 
<d''' d''>2 |
% 6a(cad) 
<e''' e''>8 <d''' d''> <d''' d''> <cis''' cis''>16 <cis''' cis''> |
% 2b(Unessential in A/S) D major1a(Unessential in B/S) 
<b'' b'>8 <d''' d''> <d''' d''>4 |
% 4a(Unessential in S) 1b(Unessential in T) 
<e''' e''>2 |
% 2a 5a 
<d''' d''> |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "choir aahs"
\key g \major %{ TODO check it's in all the parts %} r4 <a'' a'>8 <d''' d''> |
% 5b(Unessential in B/S) G major
<d''' d''>4 <a'' a'> |
% 1a(Unessential in B) 5c 
<g'' g'>2 |
% 1b 1a 
<a'' a'>4 <c''' c''> |
% 2b(Unessential in A) 4b(Unessential in T/B) 
<d''' d''> <e'' e'> |
% 6b G major
<e''' e''> <b'' b'>8. <g'' g'>16 |
% 6b(Unessential in T) 6a(Unessential in S/A) 
<a'' a'>4 <g'' g'> |
% 2a(Unessential in B) 1b(Unessential in B) 
<a'' a'> <e'' e'> |
% 2b 4a(Unessential in B) 
<g'' g'> r |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "muted trumpet"
\key c \major %{ TODO check it's in all the parts %} 
<c'' c'> <g''' g''> |
% 1a C major1b(Unessential in A) 
<c''' c''>2 |
% 4a(Unessential in B) 4b(Unessential in B) 
<d''' d''>4 <g'' g'> |
% 5b 1a(Unessential in A(accented)) 
<f'' f'>2 |
% 4a(cad) 
<f''' f''>4 <c''' c''> |
% 4b(Unessential in B/A) C major1a(Unessential in B) 
<e''' e''> <d''' d''> |
% 6b 5c(Unessential in B) 
<c''' c''> <f''' f''> |
% 1b 2a(Unessential in T) 
<g''' g''>2 |
% 5a(cad) 
<c'' c'>4 <g''' g''> |
% 1a C major1b(Unessential in A) 
<c''' c''>2 |
% 4a(Unessential in B) 4b(Unessential in B) 
<d''' d''>4 <g'' g'> |
% 5b 1a(Unessential in A(accented)) 
<f'' f'>2 |
% 4a(cad) 
<e'' e'>4 <e''' e''>8. <c''' c''>16 |
% 3a(Unessential in B) C major6a(Unessential in S) 
<c''' c''>4 <d''' d''>8 <f''' f''> |
% 4b 2a(Unessential in A/S) 
<e''' e''> <c''' c''> <d''' d''> \trill <c''' c''> |
% 6b(Unessential in S) 5a(Unessential in S) 
<c''' c''>2 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "harpsichord"
\key g \major %{ TODO check it's in all the parts %} r4 <a'' a'>8 <d''' d''> |
% 5b(Unessential in B/S) G major
<d''' d''>4 <a'' a'> |
% 1a(Unessential in B) 5c 
<g'' g'>2 |
% 1b 1a 
<a'' a'>4 <c''' c''> |
% 2b(Unessential in A) 4b(Unessential in T/B) 
<d''' d''> <e'' e'> |
% 6b G major
<e''' e''> <b'' b'>8. <g'' g'>16 |
% 6b(Unessential in T) 6a(Unessential in S/A) 
<a'' a'>4 <g'' g'> |
% 2a(Unessential in B) 1b(Unessential in B) 
<a'' a'> <e'' e'> |
% 2b 4a(Unessential in B) 
<g'' g'> r |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "voice oohs"
\key c \major %{ TODO check it's in all the parts %} 
<g'' g'> <g''' g''> |
% 1b(Unessential in T/B) C major1a(Unessential in B) 
<e''' e''>8 <g''' g''> <e''' e''>4 |
% 3b(Unessential in S) 6a 
<f''' f''>2 |
% 4b 2a(Unessential in T) 
<g''' g''> |
% 5a(cad) 
<d''' d''>4 <a'' a'> |
% 5b C major6b(Unessential in B) 
<d''' d''>8 <e''' e''> <e''' e''>4 |
% 2b(Unessential in S) 1a(Unessential in B) 
<e''' e''> <f''' f''> |
% 6a(Unessential in B) 4b(Unessential in A) 
<b'' b'>2 |
% 5a(cad) 
<g'' g'>4 <g''' g''> |
% 1b(Unessential in T/B) C major1a(Unessential in B) 
<e''' e''>8 <g''' g''> <e''' e''>4 |
% 3b(Unessential in S) 6a 
<f''' f''>2 |
% 4b 2a(Unessential in T) 
<g''' g''> |
% 5a(cad) 
<g''' g''>4 <c''' c''> |
% 5a(Unessential in A/T) C major4b 
<c''' c''> <d''' d''> |
% 1b(Unessential in T/B) 2a(Unessential in B) 
<e''' e''> <a'' a'>8 <b'' b'> |
% 6b(Unessential in B/T) 4a(Unessential in T/S) 
<c''' c''>2 |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "violin"
\key g \major %{ TODO check it's in all the parts %} r4 <a'' a'>8 <d''' d''> |
% 5b(Unessential in B/S) G major
<d''' d''>4 <a'' a'> |
% 1a(Unessential in B) 5c 
<g'' g'>2 |
% 1b 1a 
<a'' a'>4 <c''' c''> |
% 2b(Unessential in A) 4b(Unessential in T/B) 
<d''' d''> <e'' e'> |
% 6b G major
<e''' e''> <b'' b'>8. <g'' g'>16 |
% 6b(Unessential in T) 6a(Unessential in S/A) 
<a'' a'>4 <g'' g'> |
% 2a(Unessential in B) 1b(Unessential in B) 
<a'' a'> <e'' e'> |
% 2b 4a(Unessential in B) 
<g'' g'> r |
% 1a(cad) 
\bar "||"
\set Staff.midiInstrument = "flute"
\bar "|." }
partB={ \setup \set Staff.midiInstrument = "clarinet"
\time 2/4 r4 d' |
b d' |
d' b |
e'8 d' c'4 |
a g' |
e' b |
b d' |
c' d' |
f' d' |
b d' |
d' b |
e'8 d' c'4 |
a b |
b' g'8 e' |
e'4 d' |
a c' |
d' r |
\bar "||"
\set Staff.midiInstrument = "harmonica"
\key g \major %{ TODO check it's in all the parts %} b b' |
e' b' |
c'' e' |
fis'2 |
g'8 a' b' a' |
a'4 g' |
c'' e' |
b'2 |
b4 b' |
e' b' |
c'' e' |
fis'2 |
c''4 b' |
e' c''8 g' |
a'4 fis' |
gis'2 |
\bar "||"
\set Staff.midiInstrument = "harpsichord"
\key g \major %{ TODO check it's in all the parts %} r4 d' |
b d' |
d' b |
e'8 d' c'4 |
a b |
b' g'8 e' |
e'4 d' |
a c' |
d' r |
\bar "||"
\set Staff.midiInstrument = "clarinet"
\key d \major %{ TODO check it's in all the parts %} d'8 fis' e'4 |
fis' g' |
a'2 |
fis' |
g'4 a' |
b' a' |
fis' g' |
a'2 |
d'8 fis' e'4 |
fis' g' |
a'2 |
fis' |
e'8 fis' fis'4 |
g' a' |
g' a' |
fis'2 |
\bar "||"
\set Staff.midiInstrument = "marimba"
\key g \major %{ TODO check it's in all the parts %} r4 d' |
b d' |
d' b |
e'8 d' c'4 |
a b |
b' g'8 e' |
e'4 d' |
a c' |
d' r |
\bar "||"
\set Staff.midiInstrument = "muted trumpet"
\key c \major %{ TODO check it's in all the parts %} 
g c'16 c' e'8 |
c'4 f' |
d' e' |
d'8 c'4. |
f'8 g' g'4 |
e' g' |
g' a' |
g'2 |
g4 c'16 c' e'8 |
c'4 f' |
d' e' |
d'8 c'4. |
b4 c' |
f' d'8 f' |
a'4 d' |
e'2 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 1"
\key g \major %{ TODO check it's in all the parts %} r4 d' |
b d' |
d' b |
e'8 d' c'4 |
a b |
b' g'8 e' |
e'4 d' |
a c' |
d' r |
\bar "||"
\set Staff.midiInstrument = "viola"
\key c \major %{ TODO check it's in all the parts %} 
c' g |
b c' |
f' d' |
b2 |
g'4 e' |
a' c' |
e' c'8 f' |
g'2 |
c'4 g |
b c' |
f' d' |
b2 |
b8 d' c'4 |
g' d' |
a' f' |
g'2 |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
\key g \major %{ TODO check it's in all the parts %} r4 d' |
b d' |
d' b |
e'8 d' c'4 |
a b |
b' g'8 e' |
e'4 d' |
a c' |
d' r |
\bar "||"
\set Staff.midiInstrument = "reed organ"
\bar "|." }
partC={ \setup \clef bass
\set Staff.midiInstrument = "tremolo strings"
\time 2/4 r4 a |
g f |
g d |
e g8 \trill e |
f4 e |
b f8 g |
g f f4 |
f g |
a a |
g f |
g d |
e g8 \trill e |
f4 e |
b8 e' b4 |
c' g |
e g |
b r |
\bar "||"
\set Staff.midiInstrument = "harpsichord"
\key g \major %{ TODO check it's in all the parts %} e b8 e'16 e' |
c'4 e16 e fis8 |
fis4 g |
b2 |
e'8 fis' fis' dis' |
e'4 dis' |
e' b |
dis'2 |
e4 b8 e'16 e' |
c'4 e16 e fis8 |
fis4 g |
b2 |
g'8 e' b8. e'16 |
c'8 b c'4 |
c'8 a b4 |
b2 |
\bar "||"
\set Staff.midiInstrument = "trombone"
\key g \major %{ TODO check it's in all the parts %} r4 a |
g fis |
g d |
e g8 \trill e |
fis4 e |
b8 e' b4 |
c' g |
e g |
b r |
\bar "||"
\set Staff.midiInstrument = "oboe"
\key d \major %{ TODO check it's in all the parts %} a b |
b e' |
a8 d' e'4 |
d'2 |
b4 a |
e' fis' |
b d' |
e'2 |
a4 b |
b e' |
a8 d' e'4 |
d'2 |
b4 d' |
d' a8 d'16 d' |
b4 cis' |
d'2 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
\key g \major %{ TODO check it's in all the parts %} r4 a |
g fis |
g d |
e g8 \trill e |
fis4 e |
b8 e' b4 |
c' g |
e g |
b r |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
\key c \major %{ TODO check it's in all the parts %} 
e g |
a c' |
g2 |
a |
c'4 e' |
a b |
c' a8 d'16 d' |
b2 |
e4 g |
a c' |
g2 |
a |
g4 a |
c' f |
a b |
c'2 |
\bar "||"
\set Staff.midiInstrument = "english horn"
\key g \major %{ TODO check it's in all the parts %} r4 a |
g fis |
g d |
e g8 \trill e |
fis4 e |
b8 e' b4 |
c' g |
e g |
b r |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
\key c \major %{ TODO check it's in all the parts %} 
g8 f e4 |
e a |
c' a8 \trill g |
g2 |
g4 a |
a g |
c' f |
g2 |
g8 f e4 |
e a |
c' a8 \trill g |
g2 |
g8 f f4 |
g8 e f4 |
a8 b c' \trill d' |
e'2 |
\bar "||"
\set Staff.midiInstrument = "cello"
\key g \major %{ TODO check it's in all the parts %} r4 a |
g fis |
g d |
e g8 \trill e |
fis4 e |
b8 e' b4 |
c' g |
e g |
b r |
\bar "||"
\set Staff.midiInstrument = "acoustic grand"
\bar "|." }
partD={ \setup \clef bass
\set Staff.midiInstrument = "harmonica"
\time 2/4 r4 f8 d |
g, a, a,4 |
b, g, \trill |
c e8 c |
d4 c |
g, d |
e8 d d4 |
a, g, |
d f8 d |
g, a, a,4 |
b, g, \trill |
c e8 c |
d4 g, |
g, e |
a,8 c b,16 b, c8 |
c4. \trill g,8 |
g,4 r |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
\key g \major %{ TODO check it's in all the parts %} g, g |
c b, |
a,8 c e4 |
b,2 |
c'4 b, |
c8 a, b,4 |
c g |
b,2 |
g,4 g |
c b, |
a,8 c e4 |
b,2 |
e8 g g4 |
a8 e e4 |
fis b, |
e2 |
\bar "||"
\set Staff.midiInstrument = "trombone"
\key g \major %{ TODO check it's in all the parts %} r4 fis8 d |
g, a, a,4 |
b, g, \trill |
c e8 c |
d4 g, |
g, e |
a,8 c b,16 b, c8 |
c4. \trill g,8 |
g,4 r |
\bar "||"
\set Staff.midiInstrument = "harmonica"
\key d \major %{ TODO check it's in all the parts %} d g, |
d8 fis e4 |
fis a |
b2 |
g,4 d |
g, a, |
b,2 |
a, |
d4 g, |
d8 fis e4 |
fis a |
b2 |
g,4 d8 fis |
g4 fis |
e a |
d2 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
\key g \major %{ TODO check it's in all the parts %} r4 fis8 d |
g, a, a,4 |
b, g, \trill |
c e8 c |
d4 g, |
g, e |
a,8 c b,16 b, c8 |
c4. \trill g,8 |
g,4 r |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
\key c \major %{ TODO check it's in all the parts %} 
c e |
f8 c a,8. c16 |
b,4 c |
f2 |
a,8 c c16 c e8 |
c4 d8 \trill e |
e4 d |
g,2 |
c4 e |
f8 c a,8. c16 |
b,4 c |
f2 |
e8 b, a,4 |
a, d |
c g, |
c2 |
\bar "||"
\set Staff.midiInstrument = "acoustic grand"
\key g \major %{ TODO check it's in all the parts %} r4 fis8 d |
g, a, a,4 |
b, g, \trill |
c e8 c |
d4 g, |
g, e |
a,8 c b,16 b, c8 |
c4. \trill g,8 |
g,4 r |
\bar "||"
\set Staff.midiInstrument = "english horn"
\key c \major %{ TODO check it's in all the parts %} 
e8 d c8. g,16 |
g,4 a, |
a, d |
g,2 |
b,4 c8 \trill e |
f4 c8 \trill b, |
a, g, a,4 |
g,2 |
e8 d c8. g,16 |
g,4 a, |
a, d |
g,2 |
g,4 a, |
e8 c d c16 c |
c8 e f4 |
c2 |
\bar "||"
\set Staff.midiInstrument = "acoustic grand"
\key g \major %{ TODO check it's in all the parts %} r4 fis8 d |
g, a, a,4 |
b, g, \trill |
c e8 c |
d4 g, |
g, e |
a,8 c b,16 b, c8 |
c4. \trill g,8 |
g,4 r |
\bar "||"
\set Staff.midiInstrument = "harpsichord"
\bar "|." }
partE={ \setup \clef bass
\set Staff.midiInstrument = "bagpipe"
\time 2/4 r4 d, |
d,2 |
d, |
d, |
d, |
R2*4 |
d,2 |
d, |
d, |
d, |
g, |
g, |
g, |
g, |
\bar "||"
\set Staff.midiInstrument = "voice oohs"
\key g \major %{ TODO check it's in all the parts %} R2*16 |
\bar "||"
\set Staff.midiInstrument = "tubular bells"
\key g \major %{ TODO check it's in all the parts %} r4 d, |
d,2 |
d, |
d, |
d, |
g, |
g, |
g, |
g, |
\bar "||"
\set Staff.midiInstrument = "fx 1 (rain)"
\key d \major %{ TODO check it's in all the parts %} R2*16 |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
\key g \major %{ TODO check it's in all the parts %} r4 d, |
d,2 |
d, |
d, |
d, |
g, |
g, |
g, |
g, |
\bar "||"
\set Staff.midiInstrument = "tubular bells"
\key c \major %{ TODO check it's in all the parts %} 
R2*16 |
\bar "||"
\set Staff.midiInstrument = "tremolo strings"
\key g \major %{ TODO check it's in all the parts %} r4 d, |
d,2 |
d, |
d, |
d, |
g, |
g, |
g, |
g, |
\bar "||"
\set Staff.midiInstrument = "string ensemble 2"
\key c \major %{ TODO check it's in all the parts %} 
R2*16 |
\bar "||"
\set Staff.midiInstrument = "tubular bells"
\key g \major %{ TODO check it's in all the parts %} r4 d, |
d,2 |
d, |
d, |
d, |
g, |
g, |
g, |
g, |
\bar "||"
\set Staff.midiInstrument = "fx 1 (rain)"
%  Random number seed was 53850
%  Current time is Sat Sep 14 13:43:10 1996
\bar "|." }
\bookpart{ %{ TODO add \header{} block for the score %}
\score { <<
\new Staff << \context Voice = PartAB { << \partA \\ \partB >> } >>
\new Staff << \context Voice = PartCD { << \partC \\ \partD >> } >>
\new Staff << \context Voice = PartE { \partE } >>
>> \layout{} \midi{} }
}
