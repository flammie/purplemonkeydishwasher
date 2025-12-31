


<!-- usepackage algorithm  -->
<!-- usepackage algorithmic  -->[2]
<!-- usepackage listings  -->
<!-- usepackage amsmath [cmex10] -->

\lstset{stepnumber=2,numbers=left,extendedchars=true,escapeinside={|-}{-|},gobble=4}

<!-- begin document -->

# Building and Using Existing Hunspell Dictionaries and TeX Hyphenators   as Finite-State Automata¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: The official publication was in   Computational Linguistics – Applications 2010 in Wis\l a, Poland.   <https://fedcsis.org/2010/pg/395/305>.)</span>

**Authors:** Tommi A Pirinen 
and

Krister Lind\’{en

University of Helsinki,

Department of Modern Languages

Unionkatu 40, FI-00014 University of Helsinki, Finland

Email: \{tommi.pirinen,krister.linden\}@helsinki.fi}


**Date:** Last modification: (date of conversion: 2025-12-31)

<!-- make title -->


**Abstract:**
There are numerous formats for writing spell-checkers for
open-source systems and there are many descriptions for languages
written in these formats. Similarly, for word hyphenation by
computer there are TeX rules for many languages. In this paper we
demonstrate a method for converting these spell-checking lexicons
and hyphenation rule sets into finite-state automata, and present a
new finite-state based system for writer’s tools used in current
open-source software such as Firefox, OpenOffice.org and enchant via
the spell-checking library voikko.
<!-- end abstract -->


## Introduction
<a id="sec:introduction">(¶ sec:introduction)</a>

Currently there is a wide range of different free open-source
solutions for spell-checking and hyphenation by computer. For
hyphenation the ubiquitous solution is the original TeX algorithm
described in [(cites: liang/1983)](#liang/1983).  The most popular of the spelling
dictionaries are the various instances of *spell software, i.e.
ispell (footnote: <http://www.lasr.cs.ucla.edu/geoff/ispell.html>),
aspell (footnote: <http://aspell.net>), myspell and
hunspell (footnote: <http://hunspell.sf.net>) and other *spell
derivatives.  The TeX hyphenation patterns are readily available on
the Internet to cover some 49 languages. The hunspell dictionaries
provided with the OpenOffice.org suite cover 98 languages.

The program-based spell-checking methods have their limitations
because they are based on specific program code that is extensible
only by coding new features into the system and getting all users to
upgrade. E.g. hunspell has limitations on what affix morphemes you can
attach to word roots with the consequence that not all languages with
rich inflectional morphologies can be conveniently implemented in
hunspell. This has already resulted in multiple new pieces of software
for a few languages with implementations to work around the
limitations, e.g.  emberek (Turkish), hspell (Hebrew), uspell
(Yiddish) and voikko (Finnish). What we propose is to use a generic
framework of finite-state automata for these tasks. With finite-state
automata it is possible to implement the spell-checking functionality
as a one-tape weighted automaton containing the language model and a
two-tape weighted automaton containing the error model. This also
allows simple use of unigram training for optimizing spelling suggestion
results [(cites: conf/lrec/Pirinen2010)](#conf/lrec/Pirinen2010). With this model, extensions to
context-based n-gram models for real-word spelling error problems
[(cites: DBLP:conf/cicling/Wilcox-OHearnHB08)](#DBLP:conf/cicling/Wilcox-OHearnHB08) are also possible.

We also provide a method for integrating the finite-state spell-checking
and hyphenation into applications using an open-source spell-checking
library voikko (footnote: <http://voikko.sf.net>), which provides a
connection to typical open-source software, such as Mozilla Firefox,
OpenOffice.org and the Gnome desktop via enchant.

## Definitions
<a id="sec:definitions">(¶ sec:definitions)</a>

In this article we use weighted two-tape finite-state automata—or
weighted finite-state transducers—for all processing. We use the
following symbol conventions to denote the parts of a weighted
finite-state automaton: a transducer <span class='math'>T = (Σ, Γ, Q, q_0,
Q_f, δ, ρ)</span> with a semi-ring <span class='math'>(S, \oplus, \otimes,
\overline{0}, \overline{1})</span> for weights. Here <span class='math'>Σ</span> is a set with
the input tape alphabet, <span class='math'>Γ</span> is a set with the output tape
alphabet, <span class='math'>Q</span> a finite set of states in the transducer, <span class='math'>q_0 ⊂ Q</span> is
an initial state of the transducer, <span class='math'>Q_f \subset Q</span> is a set of finite
states, <span class='math'>δ: Q × Σ × Γ × S → Q</span>
is a transition relation, <span class='math'>ρ: Q_f → S</span> is a final weight
function. A successful path is a list of transitions from an initial
state to a final state with a weight different from <span class='math'>\overline{0}</span>
collected from the transition function and the final state function in
the semi-ring <span class='math'>S</span> by the operation <span class='math'>\otimes</span>. We typically denote a
successful path as a concatenation of input symbols, a colon and a
concatenation of output symbols. The weight of the successful path is
indicated as a subscript in angle brackets,
<span class='math'>*input:output*_{&lt;w&gt;}</span>. A path transducer is denoted by
subscripting a transducer with the path.  If the input and output
symbols are the same, the colon and the output part can be omitted.

The finite-state formulation we use in this article is based on Xerox
formalisms for finite-state methods in natural language processing
[(cites: beesley/2003)](#beesley/2003), in practice lexc is a formalism for writing right linear
grammars using morpheme sets called lexicons. Each morpheme in a lexc grammar
can define their right follower lexicon, creating a finite-state network called
a *lexical transducer*. In formulae, we denote a lexc style lexicon named <span class='math'>X</span> as
<span class='math'>Lex_X</span> and use the shorthand notation <span class='math'>Lex_X ∪*input:output Y*</span> to
denote the addition of a lexc string or morpheme, `input:output Y ;` to
the `LEXICON X`.  In the same framework, the twolc formalism is used to
describe context restrictions for symbols and their realizations in the form of
parallel rules as defined in the appendix of [(cites: beesley/2003)](#beesley/2003). We use
<span class='math'>Twol_Z</span> to denote the rule set <span class='math'>Z</span> and use the shorthand notation <span class='math'>Twol_Z \cap
*a:b* \leftrightarrow *l e f t* \_ *r i g h t*</span> to denote
the addition of a rule string `a:b &lt;=&gt; l e f t \_ r i g h t ;` to the
rule set <span class='math'>Z</span>, effectively saying that *a:b* only applies in
the specified context.

A spell-checking dictionary is essentially a single-tape finite-state
automaton or a language model <span class='math'>T_L</span>, where the alphabet <span class='math'>Σ_L =
Γ_L</span> are characters of a natural language. The successful paths
define the correctly spelled word-forms of the language
[(cites: conf/lrec/Pirinen2010)](#conf/lrec/Pirinen2010). If the spell-checking automaton is
weighted, the weights may provide additional information on a word’s
correctness, e.g. the likelihood of the word being correctly spelled
or the probability of the word in some reference corpus. The
spell-checking of a word <span class='math'>s</span> is performed by creating a path automaton
<span class='math'>T_s</span> and composing it with the language model, <span class='math'>T_s • T_L</span>. A
result with the successful path <span class='math'>s_{&lt;W&gt;}</span>, where <span class='math'>W</span> is greater than
some threshold value, means that the word is correctly spelled. As the
result is not needed for further processing as an automaton and as the language model
automaton is free of epsilon cycles, the spell-checking can be
optimized by performing a simple traversal (lookup) instead, which
gives a significant speed-advantage over full composition
[(cites: conf/fsmnlp/Silfverberg2009)](#conf/fsmnlp/Silfverberg2009).

A spelling correction model or an error model <span class='math'>T_E</span> is a two-tape
automaton mapping the input text strings of the text to be
spell-checked into strings that may be in the language model. The
input alphabet <span class='math'>Σ_E</span> is the alphabet of the text to be
spell-checked and the output alphabet is <span class='math'>Γ_E = Σ_L</span>. For
practical applications, the input alphabet needs to be extended by a
special any symbol with the semantics of a character not belonging to
the alphabet of the language model in order to account for input text
containing typos outside the target natural language alphabet. The
error model can be composed with the language model, <span class='math'>T_L • T_E</span>,
to obtain an error model that only produces strings of the target
language. For space efficiency, the composition may be carried out
during run-time using the input string to limit the search space. The
weights of an error model may be used as an estimate for the likelihood of the
combination of errors. The error model is applied as a filter between
the path automaton <span class='math'>T_s</span> compiled from the erroneous string, <span class='math'>s \notin
T_L</span>, and the language model, <span class='math'>T_L</span>, using two compositions, <span class='math'>T_s
• T_E • T_L</span>. The resulting transducer consists of a
potentially infinite set of paths relating an incorrect string with
correct strings from <span class='math'>L</span>. The paths, <span class='math'>s:s^i_{&lt;w_i&gt;}</span>, are weighted by
the error model and language model using the semi-ring multiplication
operation, <span class='math'>\otimes</span>. If the error model and the language model
generate an infinite number of suggestions, the best suggestions may
be efficiently enumerated with some variant of the n-best-paths
algorithm [(cites: mohri/2002)](#mohri/2002). For automatic spelling corrections, the
best path may be used. If either the error model or the language model
is known to generate only a finite set of results, the suggestion
generation algorithm may be further optimized.

A hyphenation model <span class='math'>T_H</span> is a two-tape automaton mapping input text
strings of the text to be hyphenated to possibly hyphenated strings of
the text, where the input alphabet, <span class='math'>Σ_E</span>, is the alphabet of the
text to be hyphenated and the output alphabet, <span class='math'>Γ_E</span>, is
<span class='math'>Σ_E ∪H</span>, where <span class='math'>H</span> is the set of symbols marking hyphenation
points. For simple applications, this equals hyphens or discretionary
(soft) hyphens <span class='math'>H = {-}</span>. For more fine-grained control over
hyphenation, it is possible to use several different hyphens or
weighted hyphens.  Hyphenation of the word <span class='math'>s</span> is performed with the
path automaton <span class='math'>T_s</span> by composing, <span class='math'>T_s • T_H</span>, which results in
an acyclic path automaton containing a set of strings mapped to the
hyphenated strings with weights <span class='math'>s:s^h_{&lt;w_h&gt;}</span>. Several alternative hyphenations
may be correct according to the hyphenation rules. A conservative hyphenation algorithm
should only suggest the hyphenation points agreed on by all the alternatives.

## Material
<a id="sec:material">(¶ sec:material)</a>

In this article we present methods for converting the hunspell and
TeX dictionaries and rule sets for use with open-source finite-state
writer’s tools.  As concrete dictionaries we use the repositories of
free implementations of these dictionaries and rule sets found on the
internet, e.g. for the hunspell dictionary files found on the
OpenOffice.org spell-checking
site (footnote: <http://wiki.services.openoffice.org/wiki/Dictionaries>).
For hyphenation, we use the TeX hyphenation patterns found on the
TeX hyphen page (footnote: <http://www.tug.org/tex-hyphen/>).

In this section we describe the parts of the file formats we are
working with. All of the information of the hunspell format specifics
is derived from the
`hunspell(4)` (footnote: <http://manpages.ubuntu.com/manpages/dapper/man4/hunspell.4.html>)
man page, as that is the only normative documentation of hunspell we
have been able to locate. For TeX hyphenation patterns, the
reference documentation is Frank Liang’s doctoral thesis
[(cites: liang/1983)](#liang/1983) and the TeX book [(cites: knuth/1986)](#knuth/1986).

### Hunspell File Format
<a id="subsec:material-hunspell">(¶ subsec:material-hunspell)</a>

A hunspell spell-checking dictionary consists of two files: a
dictionary file and an affix file. The dictionary file contains only
root forms of words with information about morphological affix classes
to combine with the roots.  The affix file contains lists of affixes
along with their context restrictions and effects, but the affix file
also serves as a settings file for the dictionary, containing all
meta-data and settings as well.

The dictionary file starts with a number that is intended to be the
number of lines of root forms in the dictionary file, but in practice
many of the files have numbers different from the actual line count,
so it is safer to just treat it as a rough estimate. Following the
initial line is a list of strings containing the root forms of the
words in the morphology. Each word may be associated with an arbitrary
number of classes separated by a slash. The classes are encoded in one
of the three formats shown in the examples of
Figure [(see: fig:hunspell-dic-examples)](#fig:hunspell-dic-examples): a list of binary octets
specifying classes from 1–255 (minus octets for CR, LF etc.), as in
the Swedish example on lines
[(see: vrb:hunspelldicsvstart)](#vrb:hunspelldicsvstart)–[(see: vrb:hunspelldicsvend)](#vrb:hunspelldicsvend), a list of
binary words, specifying classes from 1–65,535 (again ignoring octets
with CR and LF) or a comma separated list of numbers written in digits
specifying classes 1–65,535 as in the North Sámi examples on lines
[(see: vrb:hunspelldicsestart)](#vrb:hunspelldicsestart)–[(see: vrb:hunspelldicseend)](#vrb:hunspelldicseend). We refer to
all of these as continuation classes encoded by their numeric decimal
values, e.g. ’abakus’ on line [(see: vrb:hunspelldicsvstart)](#vrb:hunspelldicsvstart) would have
continuation classes 72, 68 and 89 (the decimal values of the ASCII
code points for H, D and Y respectively). In the Hungarian example,
you can see the affix compression scheme, which refers to the line
numbers in the affix file containing the continuation class listings,
i.e. the part following the slash character in the previous two
examples. The lines of the Hungarian dictionary also contain some
extra numeric values separated by a tab which refer to the morphology
compression scheme that is also mentioned in the affix definition
file; this is used in the hunmorph morphological analyzer
functionality which is not implemented nor described in this paper.


**Figure:**[tbp]
<!-- centering -->
  
```

    # Swedish
abakus/HDY|-<a id="vrb:hunspelldicsvstart">(¶ vrb:hunspelldicsvstart)</a>-|
abalienation/AHDvY
abalienera/MY|-<a id="vrb:hunspelldicsvend">(¶ vrb:hunspelldicsvend)</a>-|
    # Northern S|-\’{a}-|mi
okta/1|-<a id="vrb:hunspelldicsestart">(¶ vrb:hunspelldicsestart)</a>-|
guokte/1,3
golbma/1,3|-<a id="vrb:hunspelldicseend">(¶ vrb:hunspelldicseend)</a>-|
    # Hungarian
    |-ü-|z|-\’{e}-|r/1  1|-<a id="vrb:hunspelldichustart">(¶ vrb:hunspelldichustart)</a>-|
    |-ü-|zlet|-\’{a}-|g/2       2
    |-ü-|zletvezet|-ö-|/3   1
    |-ü-|zletszerz|-ö-|/4   1|-<a id="verb:hunspelldichuend">(¶ verb:hunspelldichuend)</a>-|
  
```

(Caption: Excerpts of Swedish, Northern S|-\’{a)-|mi and Hungarian dictionaries}
  <a id="fig:hunspell-dic-examples">(¶ fig:hunspell-dic-examples)</a>
<!-- end figure -->

The second file in the hunspell dictionaries is the affix file,
containing all the settings for the dictionary, and all non-root
morphemes. The Figure [(see: fig:hunspell-aff-examples)](#fig:hunspell-aff-examples) shows parts of
the Hungarian affix file that we use for describing different setting
types.  The settings are typically given on a single line composed of
the setting name in capitals, a space and the setting values, like the
NAME setting on line [(see: vrb:hunspellaffname)](#vrb:hunspellaffname). The hunspell files
have some values encoded in UTF-8, some in the ISO 8859 encoding, and
some using both binary and ASCII data at the same time. Note that in the examples in this article, we have
transcribed everything into UTF-8 format or the nearest relevant encoded
character with a displayable code point.

The settings we have used for building the spell-checking automata can
be roughly divided into the following four categories: meta-data, error
correction models, special continuation classes, and the actual
affixes. An excerpt of the parts that we use in the Hungarian affix file
is given in Figure [(see: fig:hunspell-aff-examples)](#fig:hunspell-aff-examples).

The meta-data section contains, e.g., the name of the dictionary on
line [(see: vrb:hunspellaffname)](#vrb:hunspellaffname), the character set encoding on
line [(see: vrb:hunspellaffset)](#vrb:hunspellaffset), and the type of parsing used for
continuation classes, which is omitted from the Hungarian lexicon
indicating 8-bit binary parsing.

The error model settings each contain a small part of the actual error
model, such as the characters to be used for edit distance, their weights,
confusion sets and phonetic confusion sets. The list of word
characters in order of popularity, as seen on
line [(see: vrb:hunspellafftry)](#vrb:hunspellafftry) of
Figure [(see: fig:hunspell-aff-examples)](#fig:hunspell-aff-examples), is used for the edit distance
model. The keyboard layout, i.e. neighboring key sets, is specified
for the substitution error model on
line [(see: vrb:hunspellaffkey)](#vrb:hunspellaffkey). Each set of the characters, separated by
vertical bars, is regarded as a possible slip-of-the-finger typing
error. The ordered confusion set of possible spelling error pairs is
given on
lines [(see: vrb:hunspellaffrepstart)](#vrb:hunspellaffrepstart)–[(see: vrb:hunspellaffrepend)](#vrb:hunspellaffrepend),
where each line is a pair of a ‘mistyped’ and a ‘corrected’ word
separated by whitespace.

The compounding model is defined by special continuation classes,
i.e. some of the continuation classes in the dictionary or affix file
may not lead to affixes, but are defined in the compounding section of
the settings in the affix file. In
Figure [(see: fig:hunspell-aff-examples)](#fig:hunspell-aff-examples), the compounding rules are
specified on
lines [(see: vrb:hunspellaffcompoundstart)](#vrb:hunspellaffcompoundstart)–[(see: vrb:hunspellaffcompoundend)](#vrb:hunspellaffcompoundend). The
flags in these settings are the same as in the affix definitions, so
the words in class 118 (corresponding to lower case v) would be
eligible as compound initial words, the words with class 120 (lower
case x) occur at the end of a compound, and words with 117 only occur
within a compound. Similarly, special flags are given to word forms
needing affixes that are used only for spell checking but not for the
suggestion mechanism, etc.

The actual affixes are defined in three different parts of the file:
the compression scheme part on the
lines [(see: vrb:hunspellaffafstart)](#vrb:hunspellaffafstart)–[(see: vrb:hunspellaffafend)](#vrb:hunspellaffafend), the
suffix definitions on the
lines [(see: vrb:hunspellaffsfxstart)](#vrb:hunspellaffsfxstart)–[(see: vrb:hunspellaffsfxend)](#vrb:hunspellaffsfxend), and
the prefix definitions on the
lines [(see: vrb:hunspellaffpfxstart)](#vrb:hunspellaffpfxstart)–[(see: vrb:hunspellaffpfxend)](#vrb:hunspellaffpfxend).

The compression scheme is a grouping of frequently co-occurring
continuation classes. This is done by having the first AF line list a
set of continuation classes which are referred to as the continuation
class 1 in the dictionary, the second line is referred to the
continuation class 2, and so forth. This means that for example
continuation class 1 in the Hungarian dictionary refers to the classes
on line [(see: vrb:hunspellaffafone)](#vrb:hunspellaffafone) starting from 86 (V) and ending
with 108 (l).

The prefix and suffix definitions use the same structure. The prefixes
define the left-hand side context and deletions of a dictionary entry
whereas the suffixes deal with the right-hand side. The first line of
an affix set contains the class name, a boolean value defining whether
the affix participates in the prefix-suffix combinatorics and the
count of the number of morphemes in the continuation class, e.g. the
line [(see: vrb:hunspellaffpfxstart)](#vrb:hunspellaffpfxstart) defines the prefix continuation
class attaching to morphemes of class 114 (r) and it combines with
other affixes as defined by the Y instead of N in the third field. The
following lines describe the prefix morphemes as triplets of removal,
addition and context descriptions, e.g., the line
[(see: vrb:hunspellaffsfxone)](#vrb:hunspellaffsfxone) defines removal of ’ö’, addition of
’\H{o}s’ with continuation classes from AF line 1108, in case the
previous morpheme ends in ’ö’. The context description may also
contain bracketed expressions for character classes or a fullstop
indicating any character (i.e. a wild-card) as in the POSIX regular
expressions, e.g. the context description on line
[(see: vrb:hunspellaffsfxend)](#vrb:hunspellaffsfxend) matches any Hungarian vowel except a, e or
ö, and the [(see: vrb:hunspellaffpfxend)](#vrb:hunspellaffpfxend) matches any context.  The
deletion and addition parts may also consist of a sole ‘0’ meaning a
zero-length string. As can be seen in the Hungarian example, the lines
may also contain an additional number at the end which is used for the
morphological analyzer functionalities.


**Figure:**[tbp]
<!-- centering -->
  
```

AF 1263 |-<a id="vrb:hunspellaffafstart">(¶ vrb:hunspellaffafstart)</a>-|
AF V|-\"{E}-|-jxLn|-\’{O}-||-\’{e}-||-\‘{e}-|3|-\"{A}-||-ä-|TtYc,4l # 1 |-<a id="vrb:hunspellaffafone">(¶ vrb:hunspellaffafone)</a>-|
AF Um|-\"{O}-|yiYc|-\c{C}-| # 2
AF |-\"{O}-|CWR|-\’{I}-|-j|-ð-||-\’{O}-||-\’{i}-|y|-\’{E}-||-\’{A}-||-\"{y}-|Yc2 # 3 |-<a id="vrb:hunspellaffafend">(¶ vrb:hunspellaffafend)</a>-|

NAME Magyar Ispell helyes|-\’{i}-|r|-\’{a}-|si sz|-\’{o}-|t|-\’{a}-|r     |-<a id="vrb:hunspellaffname">(¶ vrb:hunspellaffname)</a>-|
LANG hu_HU     |-<a id="vrb:hunspellafflang">(¶ vrb:hunspellafflang)</a>-|
SET UTF-8     |-<a id="vrb:hunspellaffset">(¶ vrb:hunspellaffset)</a>-|
KEY |-ö-||-ü-||-\’{o}-||qwertzuiop|-\H{o}-||-\’{u}-|| # wrap
asdfghjkl|-\’{e}-||-\’{a}-||-\H{u}-||-\’{i}-|yxcvbnm        |-<a id="vrb:hunspellaffkey">(¶ vrb:hunspellaffkey)</a>-|
TRY |-\’{i}-||-\’{o}-||-\’{u}-|taeslz|-\’{a}-|norhgki|-\’{e}-| # wrap
dmy|-\H{o}-|pv|-ö-|bucfj|-ü-|yxwq-.|-\’{a}-|      |-<a id="vrb:hunspellafftry">(¶ vrb:hunspellafftry)</a>-|
    
COMPOUNDBEGIN v     |-<a id="vrb:hunspellaffcompoundstart">(¶ vrb:hunspellaffcompoundstart)</a>-|
COMPOUNDEND x     
ONLYINCOMPOUND |     |-<a id="vrb:hunspellaffcompoundend">(¶ vrb:hunspellaffcompoundend)</a>-|
NEEDAFFIX u     
    
REP 125        |-<a id="vrb:hunspellaffrepstart">(¶ vrb:hunspellaffrepstart)</a>-|
REP |-\’{i}-| i       
REP i |-\’{i}-|       
REP |-\’{o}-| o       
REP oliere oli|-\’{e}-|re
REP cc gysz       
REP cs ts       
REP cs ds       
REP ccs ts       |-<a id="vrb:hunspellaffrepend">(¶ vrb:hunspellaffrepend)</a>-|
    # 116 more REP lines
    
SFX ? Y 3 |-<a id="vrb:hunspellaffsfxstart">(¶ vrb:hunspellaffsfxstart)</a>-|
SFX ? |-ö-| |-\H{o}-|s/1108 |-ö-| 20973 |-<a id="vrb:hunspellaffsfxone">(¶ vrb:hunspellaffsfxone)</a>-|
SFX ? 0 |-ö-|s/1108 [^a|-\’{a}-|e|-\’{e}-|i|-\’{i}-|o|-\’{o}-||-ö-||-\H{o}-|u|-ü-||-\H{u}-|] 20973
SFX ? 0 s/1108 [|-\’{a}-||-\’{e}-|i|-\’{i}-|o|-\’{o}-||-\’{u}-||-\H{o}-|u|-\’{u}-||-ü-||-\H{u}-|-] 20973 |-<a id="vrb:hunspellaffsfxend">(¶ vrb:hunspellaffsfxend)</a>-|
    
PFX r Y 195 |-<a id="vrb:hunspellaffpfxstart">(¶ vrb:hunspellaffpfxstart)</a>-|
PFX r 0 leg|-\’{u}-|jra/1262 . 22551
PFX r 0 leg|-\’{u}-|jj|-\’{a}-|/1262 . 22552 |-<a id="vrb:hunspellaffpfxend">(¶ vrb:hunspellaffpfxend)</a>-|
    # 193 more PFX r lines
  
```

(Caption: Excerpts from Hungarian affix file)
  <a id="fig:hunspell-aff-examples">(¶ fig:hunspell-aff-examples)</a>
<!-- end figure -->

### TeX Hyphenation Files
<a id="subsec:material-tex">(¶ subsec:material-tex)</a>

The TeX hyphenation scheme is described in Frank Liang’s
dissertation [(cites: liang/1983)](#liang/1983), which provides a packed suffix tree
structure for storing the hyphenation patterns, which is a special
optimized finite-state automaton.  This paper merely reformulates the
finite-state form of the patterns, for the purpose of obtaining a
general finite-state transducer version of the rules to be combined
with other pieces of the finite-state writer’s tools.  In principle,
the TeX hyphenation files are like any TeX source files, they may
contain arbitrary TeX code, and the only requirement is that they
have the ‘patterns’ command and/or the ‘hyphenation’ command. In
practice, it is a convention that they do not contain anything else
than these two commands, as well as a comment section describing the
licensing and these conventions. The patterns section is a whitespace
separated list of hyphenation pattern strings. The pattern strings are
simple strings containing characters of the language as well as
numbers marking hyphenation points, as shown in
Figure [(see: fig:tex-hyph-example)](#fig:tex-hyph-example). The odd numbers add a potential
hyphenation point in the context specified by non-numeric characters,
and the even numbers remove one, e.g. on line [(see: vrb:texhyphpat25)](#vrb:texhyphpat25),
the hyphen with left context ‘f’ and right context ‘fis’ would be
removed, and a hyphen with left context ‘ff’ and right context ‘is’ is
added. The numbers are applied in ascending order.  The full-stop
character is used to signify a word boundary so the rule on
line [(see: vrb:texhyphpatstart)](#vrb:texhyphpatstart) will apply to ‘ache’ but not to
‘headache’. The hyphenation command on
lines [(see: vrb:texhyphypstart)](#vrb:texhyphypstart)–[(see: vrb:texhyphypend)](#vrb:texhyphypend) is just a list
of words with all hyphenation points marked by hyphens. It has higher
precedence than the rules and it is used for fixing mistakes made
by the rule set.


**Figure:**[tbp]
<!-- centering -->
  
```

    \patterns{
      .ach4 |-<a id="vrb:texhyphpatstart">(¶ vrb:texhyphpatstart)</a>-|
      .ad4der
      .af1t
      .al3t
      .am5at
f5fin.
f2f5is |-<a id="vrb:texhyphpat25">(¶ vrb:texhyphpat25)</a>-|
f4fly
f2fy |-<a id="vrb:texhyphpatend">(¶ vrb:texhyphpatend)</a>-|
    }
<!-- hyphenation 
as-so-ciate |-<a id="vrb:texhyphypstart">(¶ vrb:texhyphypstart)</a>-|
      
project
ta-ble |-<a id="vrb:texhyphypend">(¶ vrb:texhyphypend)</a>-|
     -->
    
  
```

(Caption: Excerpts from English TeX hyphenation patterns)
  <a id="fig:tex-hyph-example">(¶ fig:tex-hyph-example)</a>
<!-- end figure -->

## Methods
<a id="sec:methods">(¶ sec:methods)</a>

This article presents methods for converting the existing spell-checking
dictionaries with error models, as well as hyphenators to finite-state
automata. As our toolkit we use the free open-source HFST
toolkit (footnote: <http://HFST.sf.net>), which is a general purpose API for
finite-state automata, and a set of tools for using legacy data, such as Xerox
finite-state morphologies. For this reason this paper presents the algorithms
as formulae such that they can be readily implemented using finite-state
algebra and the basic HFST tools.

The lexc lexicon model is used by the tools for describing parts of the
morphotactics. It is a simple right-linear grammar for specifying finite-state
automata described in [(cites: beesley/2003,conf/sfcm/Linden2009)](#beesley/2003,conf/sfcm/Linden2009). The twolc rule
formalism is used for defining context-based rules with two-level automata and
they are described in [(cites: koskenniemi/1983,conf/sfcm/Linden2009)](#koskenniemi/1983,conf/sfcm/Linden2009).

This section presents both a pseudo-code presentation for the conversion
algorithms, as well as excerpts of the final converted files from the material
given in Figures [(see: fig:hunspell-dic-examples)](#fig:hunspell-dic-examples),
[(see: fig:hunspell-aff-examples)](#fig:hunspell-aff-examples) and [(see: fig:tex-hyph-example)](#fig:tex-hyph-example) of
Section [(see: sec:material)](#sec:material).  The converter code is available in the HFST SVN
repository (footnote: <http://hfst.svn.sourceforge.net/viewvc/hfst/trunk/conversion-scripts/>)
, for those who wish to see the specifics of the implementation in
lex, yacc, c and python.

### Hunspell Dictionaries

The hunspell dictionaries are transformed into a finite-state transducer
language model by a finite-state formulation consisting of two parts: a lexicon
and one or more rule sets. The root and affix dictionaries are turned into
finite-state lexicons in the lexc formalism. The Lexc formalism models the part
of the morphotax concerning the root dictionary and the adjacent suffixes. The
rest is encoded by injecting special symbols, called flag diacritics, into the
morphemes restricting the morpheme co-occurrences by implicit rules that have
been outlined in [(cites: beesley/1998)](#beesley/1998); the flag diacritics are denoted in lexc
by at-sign delimited substrings. The affix definitions in hunspell also define
deletions and context restrictions which are turned into explicit two-level
rules.

The pseudo-code for the conversion of hunspell files is provided in
Algorithm [(see: algo:dic-aff-lex)](#algo:dic-aff-lex) and excerpts from the conversion of the examples
in Figures [(see: fig:hunspell-dic-examples)](#fig:hunspell-dic-examples) and [(see: fig:hunspell-aff-examples)](#fig:hunspell-aff-examples)
can be found in Figure [(see: fig:lexc-twolc-dictionary)](#fig:lexc-twolc-dictionary). The dictionary file of
hunspell is almost identical to the lexc root lexicon, and the conversion is
straightforward. This is expressed on lines [(see: a)](#a)–[(see: b)](#b) as simply going
through all entries and adding them to the root lexicon, as in
lines [(see: c)](#c)—[(see: d)](#d) of the example result. The handling of
affixes is similar, with the exception of adding flag diacritics for
co-occurrence restrictions along with the morphemes. This is shown on
lines [(see: g)](#g)—[(see: h)](#h) of the pseudo-code, and applying it will create the
lines [(see: e)](#e)—[(see: f)](#f) of the Swedish example, which does not contain further
restrictions on suffixes.

To finalize the morpheme and compounding restrictions, the final lexicon in the
lexc description must be a lexicon checking that all prefixes with forward requirements
have their requiring flags turned off.


**Algorithm:**[tbp]
(Caption: Extracting morphemes from hunspell dictionaries)
  <a id="algo:dic-aff-lex">(¶ algo:dic-aff-lex)</a>
<!-- algoritmic -->[2]
1. <span class='math'>finalflags ← ε</span>
    \FORALL{lines <span class='math'>morpheme/Conts</span> in dic}
1. <span class='math'>flags ← ε</span>
    \FORALL{<span class='math'>cont</span> in <span class='math'>Conts</span> <a id="a">(¶ a)</a>}
1. <span class='math'>flags ← flags + *@C.cont@*</span>
1. <span class='math'>Lex_{Conts} ← Lex_{Conts} ∪*0:[&lt;cont] cont*</span>
1. ENDFOR }
1. <span class='math'>Lex_{Root} ← Lex_{Root} ∪*flags + morpheme Conts*</span>
1. ENDFOR } <a id="b">(¶ b)</a>
    \FORALL{suffixes <span class='math'>lex, deletions, morpheme/Conts, context</span> in aff <a id="g">(¶ g)</a>}
1. <span class='math'>flags ← ε</span>
    \FORALL{<span class='math'>cont</span> in <span class='math'>Conts</span>}
1. <span class='math'>flags ← flags + *@C.cont@*</span>
1. <span class='math'>Lex_{Conts} ← Lex_{Conts} ∪*0 cont*</span>
1. ENDFOR }
1. <span class='math'>Lex_{lex} ← Lex_{lex} ∪*flags* + [&lt;lex] + *morpheme Conts*</span>
    \FORALL{<span class='math'>del</span> in <span class='math'>deletions</span>}
1. <span class='math'>lc ← context + deletions\textrm{ before del}</span>
1. <span class='math'>rc ← deletions \textrm{ after del} + [&lt;lex] + morpheme</span>
1. <span class='math'>Twol_{d} ← Twol_{d} ∩*del:0* \Leftrightarrow *lc \_ rc*</span>
1. ENDFOR }
1. <span class='math'>Twol_{m} ← Twol_{m} ∩[&lt;lex]:0 \Leftrightarrow *context \_ morpheme*</span>
1. ENDFOR }
    \FORALL{prefixes <span class='math'>lex, deletions, morpheme/conts, context</span> in aff}
1. <span class='math'>flags ← *@P.lex@*</span>
1. <span class='math'>finalflags ← finalflags + *@D.lex@*</span>
1. <span class='math'>lex → prefixes</span>
1. // {othewise as with suffixes, swapping left and right}
1. ENDFOR } <a id="h">(¶ h)</a>
1. <span class='math'>Lex_{end} ← Lex_{end} ∪*finalflags \#*</span>
  \end{algorithmic}
\end{algorithm}


**Figure:**[tbp]
<!-- centering -->
  
```

LEXICON Root
HUNSPELL_pfx ;
HUNPELL_dic ;
    
    ! swedish lexc
LEXICON HUNSPELL_dic |-<a id="c">(¶ c)</a>-|
    @C.H@@C.D@@C.Y@abakus HDY ; 
    @C.A@@C.H@@C.D@@C.v@@C.Y@abalienation 
HUNSPELL_AHDvY ;
    @C.M@@C.Y@abalienera MY ; |-<a id="d">(¶ d)</a>-|
    
LEXICON HDY 
0:[&lt;H]    H ;
0:[&lt;D]    D ;
0:[&lt;Y]    Y ;
    
LEXICON H |-<a id="e">(¶ e)</a>-|
er  HUNSPELL_end ;
ers  HUNSPELL_end ;
er  HUNSPELL_end ;
ers  HUNSPELL_end ; |-<a id="f">(¶ f)</a>-|
    
LEXICON HUNSPELL_end
    @D.H@@D.D@@D.Y@@D.A@@D.v@@D.m@ # ;

    ! swedish twolc file
Rules
    "Suffix H allowed contexts"
             a _ e r s ;
a:0 _ e r ;
a:0 _ e r s ;

    "a deletion contexts"
a:0 &lt;=&gt; _         _   
```

(Caption: Converted dic and aff lexicons and rules governing the deletions)
  <a id="fig:lexc-twolc-dictionary">(¶ fig:lexc-twolc-dictionary)</a>
<!-- end figure -->

### Hunspell Error Models

The hunspell dictionary configuration file, i.e. the affix file, contains
several parts that need to be combined to achieve a similar error correction
model as in the hunspell lexicon.

The error model part defined in the KEY section allows for one slip of
the finger in any of the keyboard neighboring classes. This is implemented by
creating a simple homogeneously weighted crossproduct of each class, as given
on lines [(see: vrb:pseudokeystart)](#vrb:pseudokeystart)–[(see: vrb:pseudokeyend)](#vrb:pseudokeyend) of
Algorithm [(see: algo:try-key-rep)](#algo:try-key-rep). For the first part of the example on
line [(see: vrb:hunspellaffkey)](#vrb:hunspellaffkey) of Figure [(see: fig:hunspell-aff-examples)](#fig:hunspell-aff-examples), this
results in the lexc lexicon on
lines [(see: lexcerrorkeystart)](#lexcerrorkeystart)–[(see: lexcerrorkeyend)](#lexcerrorkeyend) in
Figure [(see: fig:lexc-error-models)](#fig:lexc-error-models).

The error model part defined in the REP section is an arbitrarily long ordered
confusion set. This is implemented by simply encoding them as increasingly
weighted paths, as shown in lines
[(see: vrb:pseudorepstart)](#vrb:pseudorepstart)–[(see: vrb:pseudorepend)](#vrb:pseudorepend) of the pseudo-code in
Algorithm [(see: algo:try-key-rep)](#algo:try-key-rep).

The TRY section such as the one on line [(see: vrb:hunspellafftry)](#vrb:hunspellafftry) of
Figure [(see: fig:hunspell-aff-examples)](#fig:hunspell-aff-examples), defines characters to be tried as the
edit distance grows in descending order. For a more detailed formulation of a
weighted edit distance transducer, see e.g.  [(cites: conf/lrec/Pirinen2010)](#conf/lrec/Pirinen2010)).  We
created an edit distance model with the sum of the positions of the characters
in the TRY string as the weight, which is defined on
lines [(see: vrb:pseudotrystart)](#vrb:pseudotrystart)–[(see: vrb:pseudotryend)](#vrb:pseudotryend) of the pseudo-code in
Algorithm [(see: algo:try-key-rep)](#algo:try-key-rep). The initial part of the converted example
is displayed on lines [(see: lexcerrortrystart)](#lexcerrortrystart)–[(see: lexcerrortryend)](#lexcerrortryend) of
Figure [(see: fig:lexc-error-models)](#fig:lexc-error-models).

Finally to attribute different likelihood to different parts of the error
models we use different weight magnitudes on different types of errors, and 
to allow only correctly written substrings, we restrict the result by the
root lexicon and morfotax lexicon, as given on
lines [(see: lexcerrorrootstart)](#lexcerrorrootstart)–[(see: lexcerrorretend)](#lexcerrorretend) of
Figure [(see: fig:lexc-error-models)](#fig:lexc-error-models).  With the weights on
lines [(see: lexcerrorrootstart)](#lexcerrorrootstart)–[(see: lexcerrorrootend)](#lexcerrorrootend), we ensure that KEY
errors are always suggested before REP errors and REP errors before TRY errors.
Even though the error model allows only one error of any type, simulating the
original hunspell, the resulting transducer can be transformed into an error
model accepting multiple errors by a simple FST algebraic concatenative
n-closure, i.e. repetition.


**Algorithm:**[tbp]
(Caption: Extracting patterns for hunspell error models)
  <a id="algo:try-key-rep">(¶ algo:try-key-rep)</a>
<!-- algoritmic -->[2]
    \FORALL{neighborsets <span class='math'>ns</span> in KEY <a id="vrb:pseudokeystart">(¶ vrb:pseudokeystart)</a>}
    \FORALL{character <span class='math'>c</span> in <span class='math'>ns</span>}
    \FORALL{character <span class='math'>d</span> in <span class='math'>ns</span> such that <span class='math'>c != d</span>}
1. <span class='math'>Lex_{KEY} ← Lex_{KEY} ∪c:d_{&lt;0&gt;} \#  </span>
1. ENDFOR }
1. ENDFOR }
1. ENDFOR } <a id="vrb:pseudokeyend">(¶ vrb:pseudokeyend)</a>
1. <span class='math'>w ← 0</span>
    \FORALL{pairs <span class='math'>wrong, right</span> in REP <a id="vrb:pseudorepstart">(¶ vrb:pseudorepstart)</a>}
1. <span class='math'>w ← w + 1</span>
1. <span class='math'>LEX_{REP} ← LEX_{REP} ∪wrong:right_{&lt;w&gt;} \#  </span>
1. ENDFOR } <a id="vrb:pseudorepend">(¶ vrb:pseudorepend)</a>
1. <span class='math'>w ← 0</span>
    \FORALL{character <span class='math'>c</span> in TRY <a id="vrb:pseudotrystart">(¶ vrb:pseudotrystart)</a>}
1. <span class='math'>w ← w + 1</span>
1. <span class='math'>Lex_{TRY} ← Lex_{TRY} ∪c:0_{&lt;w&gt;} \#  </span>
1. <span class='math'>Lex_{TRY} ← Lex_{TRY} ∪0:c_{&lt;w&gt;} \#  </span>
    \FORALL{character <span class='math'>d</span> in TRY such that <span class='math'>c != d</span>}
1. <span class='math'>Lex_{TRY} ← Lex_{TRY} ∪c:d_{&lt;w&gt;} \#  </span>
1. // {for swap: replace <span class='math'>\#</span> with <span class='math'>cd</span> and add <span class='math'>Lex_{cd} ∪d:c_{&lt;0&gt;} \#</span>}
1. ENDFOR }
1. ENDFOR } <a id="vrb:pseudotryend">(¶ vrb:pseudotryend)</a>
  \end{algorithmic}
\end{algorithm}


**Figure:**[tbp]
<!-- centering -->
  
```

LEXICON HUNSPELL_error_root |-<a id="lexcerrorrootstart">(¶ lexcerrorrootstart)</a>-|
    &lt; ? &gt; HUNSPELL_error_root ; 
HUNSPELL_KEY "weight: 0" ;
HUNSPELL_REP "weight: 100" ;
HUNSPELL_TRY "weight: 1000" ; |-<a id="lexcerrorrootend">(¶ lexcerrorrootend)</a>-|
    
LEXICON HUNSPELL_errret |-<a id="lexcerrorretstart">(¶ lexcerrorretstart)</a>-|
    &lt; ? &gt; HUNSPELL_errret ; 
    # ;  |-<a id="lexcerrorretend">(¶ lexcerrorretend)</a>-|
    
LEXICON HUNSPELL_KEY |-<a id="lexcerrorkeystart">(¶ lexcerrorkeystart)</a>-|
    |-ö-|:|-ü-| HUNSPELL_errret "weight: 0" ; 
    |-ö-|:|-\’{o}-| HUNSPELL_errret "weight: 0" ;
    |-ü-|:|-ö-| HUNSPELL_errret "weight: 0" ;
    |-ü-|:|-\’{o}-| HUNSPELL_errret "weight: 0" ;
    |-\’{o}-|:|-ö-| HUNSPELL_errret "weight: 0" ;
    |-\’{o}-|:|-ü-| HUNSPELL_errret "weight: 0" ; 
    ! same for other parts |-<a id="lexcerrorkeyend">(¶ lexcerrorkeyend)</a>-|
    
LEXICON HUNSPELL_TRY |-<a id="lexcerrortrystart">(¶ lexcerrortrystart)</a>-|
    |-\’{i}-|:0 HUNSPELL_errret "weight: 1" ;
0:|-\’{i}-| HUNSPELL_errret "weight: 1" ;
    |-\’{i}-|:|-\’{o}-| HUNSPELL_errret "weight: 2" ;
    |-\’{o}-|:|-\’{i}-| HUNSPELL_errret "weight: 2" ;
    |-\’{o}-|:0 HUNSPELL_errret "weight: 2" ;
0:|-\’{o}-| HUNSPELL_errret "weight: 2" ;
    ! same for rest of the alphabet |-<a id="lexcerrortryend">(¶ lexcerrortryend)</a>-|
    
LEXICON HUNSPELL_REP |-<a id="lexcerrorrepstart">(¶ lexcerrorrepstart)</a>-|
    |-\’{i}-|:i HUNSPELL_errret "weight: 1" ;
i:|-\’{i}-| HUNSPELL_errret "weight: 2" ;
    |-\’{o}-|:o HUNSPELL_errret "weight: 3" ;       
oliere:oli|-\‘{e}-|re HUNSPELL_errret "weight: 4" ; 
cc:gysz HUNSPELL_errret "weight: 5" ;       
cs:ts HUNSPELL_errret "weight: 6" ;       
cs:ds HUNSPELL_errret "weight: 7" ;       
ccs:ts HUNSPELL_errret "weight: 8" ;  
    ! same for rest of REP pairs... |-<a id="lexcerrorrepend">(¶ lexcerrorrepend)</a>-|
    
  
```

(Caption: Converted error models from aff file)
  <a id="fig:lexc-error-models">(¶ fig:lexc-error-models)</a>
<!-- end figure -->

### TeX Hyphenation

The formulation of hyphenation as finite-state transducers is simple.  We use
the hyphenation alphabet <span class='math'>Σ_H = {-}</span>. To model the context-based deletions
and additions of hyphenation patterns, we use twol rules with centers of
<span class='math'>ε:-</span> for addition and <span class='math'>-:ε</span> for deletion. The algorithm for
creating the rule sets described in Algorithm [(see: algo:texpat)](#algo:texpat) simply goes
through the patterns, and for each hyphenation point of each pattern extracts
left and right context strings and adds them to the contexts of a rule. 
The result is exemplified in Figure [(see: fig:twolc-hyphen-models)](#fig:twolc-hyphen-models).
There is one rule for each of the hyphenation point numbers. The rules may be 
composed into one single transducer at compile time or applied as cascade at runtime.

The TeX hyphenation pattern also contains explicit exceptions to the
hyphenation patterns, which are simply specific word forms with hyphenations,
and can be compiled as simple paths: e.g. for the pattern\{as-so-ciate\} we
create a path <span class='math'>asε soε ciate:as-so-ciate</span>


**Algorithm:**[tbp]
(Caption: Extracting hyphenation patterns from TeX)
  <a id="algo:texpat">(¶ algo:texpat)</a>
<!-- algoritmic -->[2]
    \FORALL{patterns <span class='math'>p</span>}
    \FORALL{digits <span class='math'>d</span> in <span class='math'>p</span>}
1. <span class='math'>l, r ←</span> split <span class='math'>p</span> on <span class='math'>d</span>
    \IF{<span class='math'>d</span> odd}
1. <span class='math'>l, r ← l, r &lt;&lt; 0:ε</span>
1. <span class='math'>Twol_d ← Twol_d ∩0:ε \leftrightarrow l \_ r ;</span>
    \ELSE
1. <span class='math'>l, r ← l, r &lt;&lt; ε:0</span>
1. <span class='math'>Twol_d ← Twol_d ∩ε:0 \leftrightarrow l \_ r ;</span>
    \ENDIF
1. ENDFOR }
1. ENDFOR }
    \FORALL{hyphenations <span class='math'>h</span>}
1. <span class='math'>word ← h - hyphens</span>
1. <span class='math'>Lex_{exceptions} ← Lex_{exceptions} ∪*word:h \#*</span>
1. ENDFOR }
  \end{algorithmic}
\end{algorithm}


**Figure:**[tbp]
<!-- centering -->
  
```

    "Hyphen insertion 1"
0:    ...
  
```

(Caption: Converted hyphenation models from TeX examples)
  <a id="fig:twolc-hyphen-models">(¶ fig:twolc-hyphen-models)</a>
<!-- end figure -->

## Implementation and Tests

We have implemented the spell-checkers and hyphenators as finite-state
transducers using program code and scripts with a Makefile.  To test the code, we have
converted 49 hyphenation pattern files and more than 42 hunspell
dictionaries from various language families. They consist of the dictionaries that were accessible from the
aforementioned web sites at the time of writing. The
Tables [(see: table:texhyph-automata)](#table:texhyph-automata) and [(see: table:hunspell-automata)](#table:hunspell-automata)
gives an overview of the sizes of the compiled automata. The size is given in binary multiples
of bytes as reported by `ls -hl`. 

In the hyphenation table, the second
column gives the number of patterns in the rules. The total size is a result of
composing all hyphenation rules into one transducer; it may be noted that
both separate rules and a single composed transducer are equally usable at runtime. The separated
version requires less memory whereas the single composed version is faster.  For large results, such as the
Norwegian (footnote: both Nynorsk and bokmål `input` the same patterns)
one, it may still be beneficial to keep the rules separated. In the Norwegian
case, the four separately compiled rules are each of sizes between 1.2 MiB and 9.7 MiB.

For the hunspell automata in Table [(see: table:hunspell-automata)](#table:hunspell-automata), we also give the
number of roots in the dictionary file and the affixes in affix file. These numbers
should also help with identifying the version of the dictionary, since there are multiple
different versions available in the downloads.

The resulting transducers were tested by hand using the results of the
corresponding TeX `hyphenate` command and `hunspell -d` as well
as the authors’ language skills to judge errors. As testing material, a wikipedia
article on the Finnish
language (footnote: <http://en.wikipedia.org/wiki/Finnish+language> and its
international links) were used for most languages, and some arbitrary articles
where this particular article was not found. In both tests, the majority of differences come from
the lack of normalization or case folding. E.g. this resulted in our converted
transducers failing to hyphenate words where uppercase letters would have been equal to
their lowercase variants. 

The hunspell model was built incrementally
starting from the basic set of affixes and dictionary, and either adding or
skipping all directive types of the file format as found in the wild. Some of
the omissions show up e.g. in the English results, where omitting of the PHONE
directive for the suggestion mechanism results in some of the differing suggestions
in English tests, e.g.  first suggestion for  *calqued* in
hunspell is *catafalqued*. Without implementing the phonetic folding,
we get no results within 1 hunspell error, and get word forms like *chalked*,
*caulked*, and so forth, within 2 hunspell errors. No other language has .aff
files with PHONE rules, e.g. in French *comitatif* gets the suggestions *commutatif* and
*limitatif* as the first ones in both systems. 


**Table:**[tbp]
(Caption: Compiled hyphenation automata sizes)
  <a id="table:texhyph-automata">(¶ table:texhyph-automata)</a>
<!-- centering -->


| ---- | ---- | ---- |
| **Language**  |  **Hyphenator total**  |  **Number of patterns** |
| Norwegian  |  978 MiB  |  27,166 |
| German (Germany, 1996)  |  72 MiB  |  14,528 |
| German (Germany, 1901)  |  66 MiB  |  14,323 |
| Dutch  |  58 MiB  |  12,742 |
| English (Great Britain)  |  38 MiB  |  8,536 |
| Irish  |  20 MiB  |  6,046|
| English (U.S.)  |  19 MiB  |  4,948|
| Hungarian  |  15 MiB  |   13,469 |
| Swedish  |  12 MiB  |  4,717 |
| Icelandic  |  12 MiB  |  4,199|
| Estonian  |  8.8 MiB  |  3,701|
| Russian  |  4.2 MiB  |  4,820|
| Czech  |  3.1 MiB  |  3,646|
| Ancient Greek  |  2.4 MiB  |  2,005|
| Ukrainian  |  1.5 MiB  |  1,269|
| Danish  |  1.4 MiB  |  1,153|
| Slovak  |  1.1 MiB  |  2,483|
| Slovenian  |  939 KiB  |  1,086|
| Spanish  |  546 KiB  |  971|
| French  |  521 KiB  |  1,184|
| Interlingua  |  382 KiB  |  650|
| Greek (Polyton)  |  325 KiB  |  798|
| Upper Sorbian  |  208 KiB  |  1,524 |
| Galician  |  160 KiB  |  607 |
| Romanian  |  151 KiB  |  665 |
| Mongolian  |  135 KiB  |  532 |
| Finnish  |  111 KiB  |  280|
| Catalan  |  95 KiB  |  231 |
| Greek (Monoton)  |  91 KiB  |  429|
| Serbian  |  76 KiB  |  2,681 |
| Serbocroatian  |  56 KiB  |  2,681 |
| Sanskrit  |  32 KiB  |  550 |
| Croatian  |  32 KiB  |  1,483|
| Coptic  |  30 KiB  |  128 |
| Latin  |  26 KiB  |  87 |
| Bulgarian  |  24 KiB  |  1,518|
| Portuguese  |  19 KiB  |  320|
| Basque  |  15 KiB  |  49|
| Indonesian  |  14 KiB  |  46|
| Turkish  |  8 KiB  |  602|
| Chinese (Pinyin)  |  868  |  202 |

<!-- end table -->


**Table:**[tbp]
(Caption: Compiled Hunspell automata sizes)
  <a id="table:hunspell-automata">(¶ table:hunspell-automata)</a>
<!-- centering -->


| ---- | ---- | ---- | ---- |
| **Language**  |  **Dictionary**  |  **Roots**  |  **Affixes** |
| Portugese (Brazil)  |  14 MiB  |  307,199  |  25,434 |
| Polish  |  14 MiB  |  277,964  |  6,909 |
| Czech  |  12 MiB  |  302,542  |  2,492 |
| Hungarian  |  9.7 MiB  |  86,230  |  22,991 |
| Northern S\’{a}mi  |  8.1 MiB  |  527,474  |  370,982 | 
| Slovak  |  7.1 MiB  |  175,465  |  2,223 |
| Dutch  |  6.7 MiB  |  158,874  |  90|
| Gascon  |  5.1 MiB  |  2,098,768  |  110 |
| Afrikaans  |  5.0 MiB  |  125,473  |  48 |
| Icelandic  |  5.0 MiB  |  222087  |  0 |
| Greek  |  4.3 MiB  |  574,961  |  126 |
| Italian  |  3.8 MiB  |  95,194  |  2,687 |
| Gujarati  |  3.7 MiB  |  168,956  |  0 |
| Lithuanian  |  3.6 MiB  |  95,944  |  4,024 |
| English (Great Britain)  |  3.5 MiB  |  46,304  |  1,011 |
| German  |  3.3 MiB  |  70,862  |  348 |
| Croatian  |  3.3 MiB  |  215,917  |  64 |
| Spanish  |  3.2 MiB  |  76,441  |  6,773 |
| Catalan  |  3.2 MiB  |  94,868  |  996 |
| Slovenian  |  2.9 MiB  |  246,857  |  484 |
| Faeroese  |  2.8 MiB  |  108,632  |  0 |
| French  |  2.8 MiB  |  91,582  |  507 |
| Swedish  |  2.5 MiB  |  64,475  |  330 |
| English (U.S.)  |  2.5 MiB  |  62,135  |  41 |
| Estonian  |  2.4 MiB  |  282,174  |  9,242|
| Portugese (Portugal)  |  2 MiB  |  40.811  |  913 |
| Irish  |  1.8 MiB  |  91,106  |  240 |
| Friulian  |  1.7 MiB  |  36,321  |  664 |
| Nepalese  |  1.7 MiB  |  39,925  |  502 |
| Thai  |  1.7 MiB  |  38,870  |  0 |
| Esperanto  |  1.5 MiB  |  19,343  |  2,338 |
| Hebrew  |  1.4 MiB  |  329237  |  0 |
| Bengali  |  1.3 MiB  |  110,751  |  0 |
| Frisian |  1.2 MiB  |  24,973  |  73 |
| Interlingua  |  1.1 MiB  |  26850  |  54 |
| Persian  |  791 KiB  |  332,555  |  0 |
| Indonesian  |  765 KiB  |  23,419  |  17 |
| Azerbaijani  |  489 KiB  |  19,132  |  0 |
| Hindi  |  484 KiB  |  15,991  |  0 |
| Amharic  |  333 KiB  |  13,741  |  4 |
| Chichewa  |  209 KiB  |  5,779  |  0 |
| Kashubian  |  191 KiB  |  5,111  |  0 |

<!-- end table -->

## Conclusion

We have demonstrated a method and created the software to convert legacy
spell-checker and hyphenation data to a more general framework of
finite-state automata and used it in a real-life application. We have
also referred to methods for extending the system to more advanced
error models and the inclusion of other more complex models in the
same system. We are currently developing a platform for finite-state
based spell-checkers for open-source systems in order to improve the
front-end internationalization.

The next obvious development for the finite-state spell checkers is to
apply the unigram training [(cites: conf/lrec/Pirinen2010)](#conf/lrec/Pirinen2010) to the automata,
and extend the unigram training to cover longer n-grams and real word
error correction.


## Acknowledgment

The authors would like to thank Miikka Silfverberg and others in the
HFST research team as well as the anonymous reviewers for useful comments on the
manuscript.

<!-- bib style: IEEEtran -->
# References

* <a id="liang/1983">**liang/1983**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="conf/lrec/Pirinen2010">**conf/lrec/Pirinen2010**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="DBLP:conf/cicling/Wilcox-OHearnHB08">**DBLP:conf/cicling/Wilcox-OHearnHB08**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="beesley/2003">**beesley/2003**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="conf/fsmnlp/Silfverberg2009">**conf/fsmnlp/Silfverberg2009**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="mohri/2002">**mohri/2002**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="knuth/1986">**knuth/1986**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="conf/sfcm/Linden2009">**conf/sfcm/Linden2009**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="koskenniemi/1983">**koskenniemi/1983**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="beesley/1998">**beesley/1998**</a>:
    * error: <strong style="color: red">missing from bibs</strong>


<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

