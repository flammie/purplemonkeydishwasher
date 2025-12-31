
<!-- usepackage latexsym  -->


# Compiling Apertium morphological dictionaries with HFST and using them in HFST applications¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: This article was published in saltmil workshop in LREC 2011 in Malta. Original version  <http://ixa2.si.ehu.es/saltmil/>.)</span>

**Authors:** Tommi A Pirinen, Francis M. Tyers

University of Helsinki,
Universitat d’Alacant

FI-00014 University of Helsinki Finland,
E-03071 Alacant Spain 

<tommi.pirinen@helsinki.fi>, <ftyers@dlsi.ua.es>


**Date:** Last modifications: (date of conversion: 2025-12-31)


<!-- begin document -->

<!-- make title -->


**Abstract:**
In this paper we aim to improve interoperability and re-usability of the
morphological dictionaries of Apertium machine translation system by
formulating a generic finite-state compilation formula that is implemented in
HFST finite-state system to compile Apertium dictionaries into general purpose
finite-state automata. We demonstrate the use of the resulting automaton in
FST-based spell-checking system.

Keywords: finite-state, dictionary, spell-checking
<!-- end abstract -->


## Introduction

Finite-state automata are one of the most effective format for representing
natural language morphologies in computational format. The finite-state
automata, once compiled and optimised via process of minimisation are very
effective for parsing running text. This format is also used when running
morphological dictionaries in machine-translation system
Apertium [(cites: Apertium/2011)](#Apertium/2011) (footnote: <http://www.apertium.org>). In this
paper we propose a generic compilation formula  to compile the
dictionaries into weighted finite state automata for use with any FST 
tool or application.  We implement this system using a free/libre
open-source finite-state API
HFST [(cites: hfst/2011)](#hfst/2011) (footnote: <http://hfst.sf.net>). HFST is a general
purpose programming interface using a selection of freely-available
finite-state libraries for the handling of finite-state automata.

While Apertium uses the dictionaries and the finite-state automata for machine
translation, HFST is used in multitude of other applications ranging from
basic morphological analysis [(cites: hfst/2011)](#hfst/2011)
to end-user applications such as spell-checking [(cites: pirinen/2010/lrec)](#pirinen/2010/lrec) and
predictive text-entry for mobile phones [(cites: silfverberg/2011/cla)](#silfverberg/2011/cla). In this
article we show how to generate automatically a spell-checker from an Apertium
dictionary and evaluate roughly the usability of the automatically generated
spell-checker.

The rest of the article is laid out as follows: In section [(see: sec:methods)](#sec:methods)
we describe the generic compilation formula for the HFST-based compilation of
Apertium dictionaries and the formula for induction of spell-checkers error
model from Apertium’s dictionary. In section [(see: sec:materials)](#sec:materials) we introduce
the Apertium dictionary repository and the specific dictionaries we use to
evaluate our systems. In section [(see: sec:evaluation)](#sec:evaluation) we evaluate speed and
memory usage of compilation and application of our formula against Apertium’s
own system and show that our system has roughly same coverage and explain
the differences arise from.

## Methods
<a id="sec:methods">(¶ sec:methods)</a>

The compilation of Apertium dictionaries is relatively straight-forward. We
assume here standard notations for finite-state algebra. The morphological
combinatorics of Apertium dictionaries are defined in following terms: There is
one set of root morphs (finite strings) and arbitrary number of named sets of
affix morphs called {<!-- tt -->pardef}s. Each set of affix morphs is associated with a
name. Each morph can also be associated with a paradigm reference pointing to a
named subset of affixes. As an example, a language of singular and plural of
*cat* and *dog* in English would be described by root dictionary
consisting of morphs `cat` and `dog`, both of which point on the
right-hand side to pardef named `number`. The number affix morphs are
defined then as set of two morphs, namely `s` for plural marker and
empty string for singular marker.

Each morph can be compiled into single-path finite-state automaton (footnote: the
full formula allows any finite-state language as morph, compiled from regular
expressions, the extension to this is trivial but for readability we present
the formula for string morphs) containing the actual morph as string of UTF-8
arcs <span class='math'>m</span>. The morphs in the root dictionary are extended from left or right
sides by joiner markers iff they have a pardef definition there and each affix
dictionary is extended on the left (for suffixes) or right (for prefixes) by
the pardef name marker. In the example of *cats, dogs* language this would
mean finite state paths `c a t NUMBER`, `d o g NUMBER`,
`NUMBER s` and `NUMBER <span class='math'>ε</span>`, where <span class='math'>ε</span> as usual
marks zero-length string (footnote: In the current implementation we have used
temporarily a special non-epsilon marker as this decreases the local
indeterminism and thus compilation time).  These sets of roots and affixes can
be compiled into disjunction of such joiner delimited morphs.  Now, the
morphotactics can be defined as related to joiners by any such path that
contains joiners only as pairs of adjacent identical paradigm references, such
as `c a t NUMBER NUMBER s` or `d o g NUMBER NUMBER <span class='math'>ε</span>`,
but not `c a t NUMBER d o g NUMBER` or `NUMBER s NUMBER s`. The
finite-state formula for this morphotactics is defined by

<div class='math'><a id="formula:morphotax">(¶ formula:morphotax)</a>
M_x = (Σ ∪ ∪_{x ⊂ p} x x)^{★},
</div>

where <span class='math'>p</span> is set of pardef names and <span class='math'>Σ</span> the set
of symbols in morphs not including the set of pardef names.  Now the final
dictionary is simply composition of these morphotactic rules over the repetion
of affixes and roots:

<div class='math'><a id="formula:lexical">(¶ formula:lexical)</a>
(M_a ∪ M_r)^{★} • M_x,
</div>

where <span class='math'>M_{a}</span> is the disjunction of affixes with joiners, <span class='math'>M_{r}</span> the
disjunction of roots with joiners, and <span class='math'>M_x</span> the morphotactics defined in
formula [(see: formula:morphotax)](#formula:morphotax). This is a variation of morphology compilation
formula presented in various HFST documentation, such as [(cites: hfst/2011)](#hfst/2011).

### Implementation Details

There are lot of finer details we will not thoroughly cover in this article, as
they are mainly engineering details. In this section we shortly summarise
specific features of HFST-based FST compilation that result in meaningful
differences in automaton structure or working. One of the main source of
differences is that HFST automata are two-sided and compiled only ones from the
source code whereas Apertium generates two different automata for analysis and
generation. In these automata the structure may be different, since Apertium
dictionaries have ways of marking morphs limited to generation or analysis
only, so they will only be included in one of the automatons. Our approach to
this is to use special symbols called flag-diacritics [(cites: beesley/2003)](#beesley/2003) to
limit the paths as analysis only or generation only on runtime, but still
including all paths in the one transducer that gets compiled.

Another main difference in processing comes from the special word-initial, 
word-final and separate morphs that in Apertium are contained in separate
automata altogether, but HFST tools do not support use of multiple automata
for analysis, so these special morphs will be concatenated optionally to
beginning or end of the word, or disjuncted to the final automata respectively.
These special morphs include things like article *l’* in French as bound
form.

### Creating a Spell-Checker Automatically

To create a finite-state spell-checker we need two automata, one for the
language model, for which the dictionary compiled as described earlier will do,
and one for the error model [(cites: pirinen/2010/lrec)](#pirinen/2010/lrec). A classic baseline error
model is based on the edit distance
algorithm [(cites: levenshtein/1966,damerau/1964)](#levenshtein/1966,damerau/1964), that defines typing errors of
four types: pressing extra key (insertion), not pressing a key (deletion),
pressing wrong key (change) and pressing two keys in wrong order (swap). There
have been many finite-state formulations of this, we use the one defined
in [(cites: schulz/2002,pirinen/2010/lrec)](#schulz/2002,pirinen/2010/lrec). The basic version of this where the
typing errors of each sort have equal likelihood for each letters can be
induced from the compiled language model, and this is what we use in this
paper. The induction of this model is relatively straightforward; when
compiling the automaton, save each unique UTF-8 codepoint found in the
morphs (footnote: The description format of Apertium requires declaration of
exemplar character set as well, but as this is only used in the tokenisation
algorithm [(cites: garrido-alenda02)](#garrido-alenda02) , which is not going to be used, we induce
the set from the morphs). For each character generate the identities in start
and end state to model correctly typed runs. For each of the error types the
generate one arc from initial state to the end state modelling that error,
except for swap which it requires one auxiliary state for each character pair.

## Materials
<a id="sec:materials">(¶ sec:materials)</a>

The Apertium project hosts a large number of morphological dictionaries for
each of the languages translated. From these we have selected three
dictionaries to be tested: Basque from Basque-Spanish pair as it is 
released dictionary with the biggest on-disk size, Norwegian Nynorsk from the Norwegian pair as a language
that has some additional morphological complexity, such as compounding, and
Manx from  as a language that currently lacks spell-checking tools to
demonstrate the plausibility of automatic conversion of Apertium dictionary
into a spell-checker (footnote: We also provide a Makefile script to
recreate results of this article for any language in Apertium’s repository).

To evaluate the use of resulting morphological dictionaries and spell-checkers
we use following Wikipedia database
dumps (footnote: <http://download.wikipedia.org/>):
`euwiki-20120219-pages-articles.xml.bz2`,
`nnwiki-20120215-pages-articles.xml.bz2`, and
`gvwiki-20120215-pages-articles.xml.bz2`. For the purpose of this
article we performed very crude cleanup and preprocessing to Wikipedia data
picking up the text elements of the article and discarding most of Wikipedia
markup naïvely (footnote: For details see the script in
<http://hfst.svn.sourceforge.net/viewvc/hfst/trunk/lrec-2011-apertium/>.).

## Test Setting and Evaluation
<a id="sec:evaluation">(¶ sec:evaluation)</a>


To get one view on differences made by generic compilation formula instead of
direct automata building used by Apertium we look at the created automata, this
will also give us a rough idea of what its efficiency might be. In
table [(see: table:graph-size)](#table:graph-size) we give the counts of nodes and edges, in that
order, in the graphs compiled from the dictionaries. Note, that in case
of Apertium it is the sum of all the separate automata states and edges that
is counted. The small differences in sizes of graphs are mostly caused by
the different handling of generation vs. analysis mode. The difference in sizes
of automata on disk in is shown in table [(see: table:size)](#table:size).
The size of HFST automata can be attributed to the clever compression
algorithm used by HFST [(cites: silfverberg/2009/fsmnlp)](#silfverberg/2009/fsmnlp).


**Table:**[h]
<div style='text-align: center'>


| ---- | ---- | ---- | ---- |
| <!-- bf -->Lang.  |  <!-- bf -->Apertium {<!-- tt -->{<!-- small --> LR}}  |  <!-- bf -->Apertium {<!-- tt -->{<!-- small --> RL}}  |  <!-- bf -->HFST |
| Basq.       |  30,114   |  34,005   |  34,824  |
|  |  59,321   |  68,030   |  68,347  |
| Norg.  |  56,226   |  55,722   |  56,871  |
|  |  138,217  |  132,475  |  139,259 |
| Manx          |  13,055   |  12,955   |  12,920  |
|  |  28,220   |  27,062   |  27,031  |

(Caption: Size of HFST-based system against original (count of nodes first, then
edges)
<a id="table:graph-size">(¶ table:graph-size)</a>)
</div>
<!-- end table -->


**Table:**[h]
<div style='text-align: center'>


| ---- | ---- | ---- | ---- |
| <!-- bf -->Lang.  |  <!-- bf -->Apertium {<!-- tt -->{<!-- small --> LR}}  |  <!-- bf -->Apertium {<!-- tt -->{<!-- small --> RL}}   |  <!-- bf -->HFST |
| Basq.        |  252 KiB  |  289 KiB  |  1,7 MiB |
| Norg.  |  558 KiB  |  535 KiB  |  3,7 MiB |
| Manx          |  108 KiB  |  110 KiB  |  709 KiB |

(Caption: Size of HFST-based system against original (as B on disk)
<a id="table:size">(¶ table:size)</a>)
</div>
<!-- end table -->

To test efficiency we measure times of running various tasks.  The times and
memory usage have been measured using GNU `time` utility and
`getrusage` system call’s `ru\_utime` field, averaged over three
test runs. The tests were performed on quad-core Intel Xeon E5450 @ 3.00 GHz
with 64 GiB of RAM. 

First we measure speed of analysing a full corpus with the result automaton.
The speed is measured in the table [(see: table:speed)](#table:speed), in
seconds to precision that was available in our system. Curiously the results
do not give direct advantage to either of the system but it seems to
depend on the language which system is a better choice for corpus analysis.


**Table:**[h]
<div style='text-align: center'>


| ---- | ---- | ---- |
| <!-- bf -->Language  |  <!-- bf -->Apertium  |  <!-- bf -->HFST |
| Basque        |  32.0 s |  18.4 s |
| Norwegian     |  2.4 s  |  5.5  s |
| Manx          |  1.6 s  |  2.2  s |

(Caption: Speed of HFST-based system against original in corpus analysis
 (as s in user time)
<a id="table:speed">(¶ table:speed)</a>)
</div>
<!-- end table -->

Similarly we measure the speed of current compilation process in 
table [(see: table:compile-speed)](#table:compile-speed). In here there’s an obvious advantage to
manual building of the automaton (see [(cites: rojas2005)](#rojas2005) for the precise algorithm
used) over the finite-state algebra method, as is
in line with earlier results for lexc building in [(cites: pirinen/2009/sfcm)](#pirinen/2009/sfcm).


**Table:**[h]
<div style='text-align: center'>


| ---- | ---- | ---- |
| <!-- bf -->Language  |  <!-- bf -->Apertium time  |  <!-- bf -->HFST time |
| Basque        |  35.7 s  |  160.0  s |
| Norwegian     |  6.6 s   |  200.2 s |
| Manx          |  0.8 s   |  11.2  s |

(Caption: Speed of HFST-based system against original in compilation
 (as seconds of user time)
<a id="table:compile-speed">(¶ table:compile-speed)</a>)
</div>
<!-- end table -->

Finally we evaluate the usability of dictionaries meant for machine translation
as spell-checkers by running the finite-state spell checkers we produced
automatically through a large corpus and show the measure both speed and
quality of the results. The errors were automatically generated to Wikipedia
text’s correct words using simple algorithm that may generate one Levenshtein
error per each character position at probability of <span class='math'>\frac{1}{33}</span>.  This test
shows only rudimentary results on the plausibility of using machine translation
dictionary for spell-checking; for more thorough evaluation of efficiency of
finite-state spell-checking see [(cites: hassan/2008)](#hassan/2008).


**Table:**[h]
<div style='text-align: center'>


| ---- | ---- | ---- |
| <!-- bf -->Language  |  <!-- bf -->Speed (words/sec) |
| Basque        |   7,900 |
| Norwegian     |   9,200 |
| Manx          |   4,700 |

(Caption: Efficiency of spelling correction in artificial test setup, average 
over three runs.)
<a id="table:spelling">(¶ table:spelling)</a>
</div>
<!-- end table -->

## Conclusions
<a id="sec:conclusions">(¶ sec:conclusions)</a>

In this article we have shown a general formula to compile morphological
dictionaries from machine-translation system Apertium in generic FST system of
HFST and using the result in HFST-based application of spell-checking.

## Future Work
<a id="sec:future">(¶ sec:future)</a>

In this article we showed a basic method to gain more inter-operability between
generic FST system of HFST and a specialised morphological dictionary writing
formalism of machine-translation system Apertium by implementing a generic
compilation formula to compile the language descriptions. In future research
we are leveraging this and other related formulas into automatic optimisation
of the final automata using the information present in the language description
to optimise instead of relying generic graph algorithms for the final minimised
result automata.
 
We demonstrated importing the compiled dictionary as a language model and
inducing error model for real-world spell-checking applications. Further
development in this direction should aim for interoperable formalisms, formats
and mechanisms for language models and end applications of all relevant
language technology tools.

## Acknowledgements

We thank the HFST and Apertium contributors for fruitful internet relayed chats,
and the two anonymous reviewers for their helpful suggestions.

<!-- bib style: unsrt -->
# References

* <a id="Apertium/2011">**Apertium/2011**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="hfst/2011">**hfst/2011**</a>:
    * title: HFST—Framework for Compiling and Applying Morphologies
    * publisher: Springer
    * author: Krister Lindén and Miikka Silfverberg and Erik Axelson and S...
    * year: 2011
    * editor: Cerstin Mahlow and Michael Pietrowski
    * volume: Vol. 100
    * isbn: 978-3-642-23137-7
    * series: Communications in Computer and Information Science
    * pages: 67-85
    * booktitle: Systems and Frameworks for Computational Morphology
* <a id="pirinen/2010/lrec">**pirinen/2010/lrec**</a>:
    * author: Tommi A Pirinen and Krister Lind
’{e}n
    * title: Finite-State Spell-Checking with Weighted Language and Error...
    * booktitle: Proceedings of the Seventh SaLTMiL workshop on creation and ...
    * year: 2010
    * address: Valletta, Malta
    * pages: 13–18
    * url: http://siuc01.si.ehu.es/
%7Ejipsagak/SALTMIL2010_Proceeding...
* <a id="silfverberg/2011/cla">**silfverberg/2011/cla**</a>:
    * title: Improving Predictive Entry of Finnish Text Messages using IR...
    * author: Miikka Silfverberg and Mirka Hyvärinen and Tommi Pirinen
    * year: 2011
    * pages: 69-76
* <a id="beesley/2003">**beesley/2003**</a>:
    * title: Finite State Morphology
    * year: 2003
    * author: Kenneth R Beesley and Lauri Karttunen
    * pages: 503
    * publisher: CSLI publications
    * isbn: 978-1575864341
* <a id="levenshtein/1966">**levenshtein/1966**</a>:
    * author: V. I. Levenshtein
    * title: Binary codes capable of correcting deletions, insertions, an...
    * journal: Soviet Physics—Doklady 10, 707–710. Translated from Doklad...
    * year: 1966
    * pages: 845–848
* <a id="damerau/1964">**damerau/1964**</a>:
    * author: F J Damerau
    * title: A technique for computer detection and correction of spellin...
    * journal: Commun. ACM
    * year: 1964
    * number: 7
* <a id="schulz/2002">**schulz/2002**</a>:
    * author: Klaus Schulz and Stoyan Mihov
    * title: Fast String Correction with Levenshtein-Automata
    * journal: International Journal of Document Analysis and Recognition
    * year: 2002
    * volume: 5
    * pages: 67–85
* <a id="garrido-alenda02">**garrido-alenda02**</a>:
    * author: Alicia Garrido-Alenda and Mikel L. Forcada and Rafael C. Car...
    * title: Incremental Construction and Maintenance of Morphological An...
    * booktitle: Proceedings of TMI 2002 (Theoretical and Methodological Issu...
    * pages: 53–62
    * year: 2002
* <a id="silfverberg/2009/fsmnlp">**silfverberg/2009/fsmnlp**</a>:
    * title: HFST Runtime Format—A Compacted Transducer Format Allowing...
    * author: Miikka Silfverberg and Krister Lind
’{e}n
    * year: 2009
    * booktitle: FSMNLP 2009
    * crossref: conf/fsmnlp/2009
    * url: http://www.ling.helsinki.fi/ klinden/pubs/fsmnlp2009runtime....
* <a id="rojas2005">**rojas2005**</a>:
    * title: Construcci
’on y minimizaci
’on eficiente de transductores...
    * author: Sergio Ortiz Rojas and Mikel L. Forcada and Gema Ram
’irez ...
    * year: 2005,
    * number: 35,
    * journal: Procesamiento del Lenguaje Natural
    * pages: 51–57
* <a id="pirinen/2009/sfcm">**pirinen/2009/sfcm**</a>:
    * title: HFST Tools for Morphology—An Efficient Open-Source Package...
    * author: Krister Lind
’{e}n and Miikka Silfverberg and Tommi Pirinen
    * year: 2009
    * booktitle: sfcm 2009
    * pages: 28—47
    * crossref: conf/sfcm/2009
    * uri: http://www.helsinki.fi/
%7Etapirine/publications/Pirinen-sf...
* <a id="hassan/2008">**hassan/2008**</a>:
    * author: Ahmed Hassan and Sara Noeman and Hany Hassan
    * title: Language Independent Text Correction using Finite State Auto...
    * year: 2008
    * booktitle: Proceedings of the Third International Joint Conference on N...
    * volume: 2
    * location: Hyderabad, India
    * pages: 913–918



<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

