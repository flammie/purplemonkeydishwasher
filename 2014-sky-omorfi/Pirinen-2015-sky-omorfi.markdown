

<!-- new if iffinal -->
<!-- fi -->naltrue

<!-- usepackage fontspec  -->
<!-- usepackage xunicode  -->
<!-- usepackage xltxtra  -->
<!-- usepackage expex  -->
<!-- usepackage pdfpages  -->

<!-- usepackage url  -->
<!-- usepackage hyperref  -->

<!-- usepackage geometry [margin=3cm] -->

<!-- usepackage natbib  -->
<!-- set length \bibsep 0pt -->
<!-- linespread 1.2 -->

<!-- default font feat Mapping=tex-text -->
<!-- set main font Times New Roman  -->

<!-- usepackage titlesec  -->

\titleformat*{\section}{\bfseries}
\titleformat*{\subsection}{\bfseries}


# Development and Use of Computational Morphology of Finnish in the Open Source and Open Science Era—Notes on Experiences with Omorfi Development¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: The official publication in 2016, from doc format version, will differ quite a bit in formatting.)</span>
<!-- if final -->
**Authors:** Tommi A Pirinen 

Dublin City University

ADAPT—School of Computing
<!-- fi -->
**Date:** 
<!-- begin document -->

<!-- make title -->

**Abstract:**

This article describes a contemporary system for the computational
modeling of the morphology of Finnish word-forms called Omorfi. The
purpose of this article is to present new developments and open
development model of the morphological analysis of Finnish to the
linguistic audience. We also describe some of the advances from the
earlier analysers. The article shows Omorfi as a full-fledged, stable
system for real-world usage in linguistic research and computational
linguistics applications, as opposed to presenting a new technological
feature in a limited experiment. We describe results from experimenting
the system in large-scale linguistic analysis setting. We also present a
selection of real-world use cases for the morphological analysers that
have affected the development of Omorfi.

Our system is based fully on free and open source data and methods. This
has brought forth some new possibilities to the lexicographical data collection using
crowd\-sour\-ced dictionary Wiktionary, as well as statistical modelling
with e.g., the Wikipedia data.  One of the reasons of this article is to 
describe the successful use of the community-driven development model in
Omorfi, including crowd-sourcing as well as independent expert
contributions.

We evaluated our analyser to give a rough idea of its usefulness and
applications in linguistic work. To do this, we processed large text
corpora with Omorfi and verified that only 1 % of the word-forms
remains unknown to the system. Omorfi was also verified to match the
FinnTreeBank 3.1 standard analyses at 93 % faithfulness per token
count.
<!-- end abstract -->

## Introduction

Computational morphological models and management of lexicographical data
are a central component for most of the computational applications of
linguistic analysis. Computational morphology of the Finnish language was
first described some 30 years ago [(cites: koskenniemi1983twolevel)](#koskenniemi1983twolevel). The aim
of this article is to present Omorfi (footnote: 
<https://github.com/flammie/Omorfi/>) as a matured scientific project
involving contributions from scientific community as well as crowd-sourced
lexicographical additions, as a full-fledged project for managing
lexicographical database on one hand and its natural language parser on the
other hand.  We will discuss our approach to lexicography and parser
building in collaboration with crowds and experts. On technical side, we
highlight some of the new features in the parser, especially from the point
of view of linguists and end-users. The new features of the system at large,
that we bring to focus in the article consists of two items: the
inter-operation of statistical and rule-based parsing methods and the open
development model.

This article records a state of the state-of-the-art morphological analysis
of Finnish. For a system overview in the article to be interesting and
usable, we only highlight the long-term design goals of the system instead
of transitional and volatile features of a fast-moving computer software
that is developed by a base of open-source and language
enthusiasts. (footnote: for up-to-date documentation for implementation
details and rapidly changing features, the project web site is the place
to go: <https://github.com/flammie/omorfi/wiki>)

The scientific advances within the development of the various features of
Omorfi have been documented in scientific publications in various fora. The
main advance to previous systems is the introduction of statistical language
parsing component (c.f. [(cites: manning1999foundations)](#manning1999foundations)), including it’s combination with
traditional rule-based model. The novelty in this article is not in singular
experiments gone into Omorfi but a large-coverage system composed of all the
state-of-the-art results in the field of computational morphology in
weighted finite-state and relate technologies. This is, to our knowledge,
one of the only on-going, mature, high-coverage statistical-rule based
finite-state natural language parser, developed and used jointly by
scientists, engineers and open source contributors via crowd-sourcing.


One notable practical distinction in our system is its licensing policy. Omorfi
analyser is a free and open source product.  In contemporary computational
linguistics, freeness of systems and data is rightly seen as a cornerstone of
properly conducted science, as it fulfills the requirement of repeatability by
not setting unnecessary fences for the repetition of the scientific results.
There is a large base of recent research supporting this, specifically for
Finnish the latest is by [(cites: koskenniemi2008build)](#koskenniemi2008build). For computer-savvy end
users this means that the tools necessary to perform linguistic analysis with
Omorfi can be downloaded to and used on any average PC. There is an
installation in the data centers of CSC maintained by CSC
staff, (footnote: <http://www.csc.fi/english/research/sciences/linguistics>)
that is available for researchers.

## Prior and Related Work
<a id="sec:prior-work">(¶ sec:prior-work)</a>

Omorfi is based on the tradition of finite-state morphologies, a theoretical
framework laid out by [(cites: koskenniemi1983twolevel)](#koskenniemi1983twolevel). While our implementation
is not directly related and was written from the scratch, Omorfi was created in
the context of University of Helsinki, parallel to a project to update,
open-source and maintain the software necessary to build systems akin original
two-level morphology [(cites: hfst2012)](#hfst2012). (footnote: <http://hfst.sf.net>)
Omorfi roots are in a master’s thesis project [(cites: pirinen2008suomen)](#pirinen2008suomen) based
on the newly released open source word list from kotus at the
time. (footnote: Nykysuomen sanalista,
<http://kaino.kotus.fi/sanat/nykysuomi>) From a typical single-author
project of that time, Omorfi has  become a large coverage multi-author
project with crowd-sourced lexical data sources.

Many of scientific advances made by research groups in language technology
department of University of Helsinki have directly or indirectly affected
Omorfi. The research on sub-word <span class='math'>n</span>-gram
models [(cites: pirinen2009weighted,pirinen2009weighting)](#pirinen2009weighted,pirinen2009weighting) has been transferred
to Omorfi compound disambiguation schemes. The methodology for
semi-automatic lexical data harvesting, e.g.
by [(cites: linden2008probabilistic)](#linden2008probabilistic), has been largely influential on
gathering of the huge lexical database in Omorfi. Finally, the work on
coupling statistical and rule-based approaches for
disambiguation [(cites: pirinen2015using)](#pirinen2015using), based on a grammar and a parsing
approach by [(cites: karlsson1995constraint)](#karlsson1995constraint), and is included in the recent
versions of Omorfi.

There have been competing and complementary approaches to computational
parsing of Finnish. For example, in machine learning,
 [(cites: durrett2013supervised)](#durrett2013supervised) (footnote: We thank the anonymous reviewer for
bringing this recent research to our attention) show, that unsupervised
learning from Wiktionary data will create an analyser with recall in
prediction of inflected word-forms in the ballpark of 83—87 %, However,
their goal was to learn to predict Wiktionary’s example inflection table’s
28 forms per noun and 53 forms per verb, and they only performed intrinsic
evaluation on held-out Wiktionary pages. Our approach to the usage of Wiktionary
data is to collect the lexemes and their inflectional patterns already
confirmed and written down by human language users, (footnote: in our opinion,
trying to machine learn data that is already available and verified by
humans is not largely useful) and use hand-written rules to inflect, which
yields to virtually 100 % recall (bar bugs in our code) for the full
paradigms. For this reason, it is hard to directly compare these two
approaches, at all. On the other hand, statistical language parsing systems
have been built on top of Omorfi that go far and beyond the language parsing
capabilities of a morphological parser, such as the universal dependency
parser of Finnish [(cites: pyysalo2015universal)](#pyysalo2015universal).

One source of development in related works is the applications, Omorfi has been
used in many real-world scientific applications to handle Finnish language.
For example spell-checking [(cites: pirinen2014weighted)](#pirinen2014weighted), language
generation [(cites: toivanen2012corpus)](#toivanen2012corpus), machine
translation [(cites: clifton2011combining,rubino2015abumatran)](#clifton2011combining,rubino2015abumatran), and statistical
language modelling [(cites: haverinen2013building,bohnet2013joint)](#haverinen2013building,bohnet2013joint).  On top of
adding lexical data and statistical models, the vast array of applications has
necessitated for Omorfi to take strong software engineering best common
practices in use, in order to keep different end-applications usable. This is
one of the key developments we wish to highlight in this article, the concept
of continuous development by cooperation of computer scientists, linguists and
common crowds via crowd-sourcing is as far as we know unique and
underdocumented for such a long-term free and open-source project as Omorfi is.
The development by linguists and language technologists has been studied, e.g.
by [(cites: maxwell2008joint)](#maxwell2008joint), and we have done our best to adapt and extend it
to large open source development setting described in this article.




## Methods
<a id="sec:methods">(¶ sec:methods)</a>

The implementation of our analyser follows the traditional works on
*Finite State Morphology* by [(cites: beesley2003finite)](#beesley2003finite). On top of
that we have applied recent extensions from the research of finite-state
morphology, such as weighted finite-state methods [(cites: openfst,hfst2012)](#openfst,hfst2012).
What this means in practice is basic unigram probabilities of word-forms
composed (footnote: using the finite-state algebra operation composition that
is well-defined in terms of weighted automata) over the analyser from a
corpus.  Finally, probabilities are used in conjunction with constraint
grammar rules [(cites: karlsson1995constraint)](#karlsson1995constraint) to disambiguate.  This brings
the traditional rule-based language analyser towards the statistical
language analysers that are widely popular in the handling of
morphologically less complex languages.  A diagram of the combination is
shown in figure [(see: fig:combo)](#fig:combo), the figure is much simplified version of
real implementation, just to show how few forms of select words interact in
the system, the statistical component also omits the existence of known
compounds to simplify the presentation. The flow of the system is following:
from database we generate a rule based analyser. The statistical data is
counted from the corpora, and applied over the automaton using the formula
by [(cites: pirinen2009weighted)](#pirinen2009weighted). The resulting automaton is used to analyse
word-forms and the sentence context is used by constraint grammar to further
select the best analyses.


**Figure:**[tb!]
![combo-crop](combo-crop)
(Caption: Diagram of Omorfi technology showing a few example words (vesi
    ’water’, and käsi ’hand’) and forms in the database, analyser and
statistical training. Not shown in the automaton but used are also words
putous ’fall’ and jakaja ’divider’ used to demonstrate compound formation
and probablity calculations for vesiputous ’waterfall’ and vedenjakaja
’watershed’. In finite-state representation, the double circle marks the end
state, and the arrow leading away from the figure is cropped out of the
example. The sub-strings in automaton drawing were compacted to single
transitions where possible. <a id="fig:combo">(¶ fig:combo)</a>)
<!-- end figure -->

The implementation of finite-state morphology in Omorfi is based on
arrangement of stems, stem variations and suffix morphs, without
intermediate morphographemic processing. This relies on word classification
to include data about stem patterns and vowel harmony for example. The
classified dictionary words are stripped of their varying stem parts, and
then concatenated with the variations and then stems, followed by all
suffixes and optionally extended by compounding. This is done using standard
finite-state morphology approach. E.g.  in figure [(see: fig:combo)](#fig:combo), we have a
dictionary words *vesi* ‘water’ and *käsi* ‘hand’ with stem
invariants *ve-* and *kä* resp., and stem variation in
*-si* <span class='math'>\sim</span> *-de-* ..., and respectively suffixes
<span class='math'>∅</span> (nominative) <span class='math'>\sim</span> *-n* (genitive, ‘water’s’) <span class='math'>\sim</span>
*-ssä* (inessive ‘in water’)  <span class='math'>\sim</span> *-stä* (elative, ´from
water’) ... and so forth. This simple concatenation forms altogether
some thousands of word-forms per dictionary word, as well as returns back to
new words for compounding where applicable.

The baseline statistical methods for morphological models are applied over
the finite-state formulation within the same framework, as is shown in the
example in figure [(see: fig:combo)](#fig:combo).  The formulation we use is the schoolbook
unigram training (c.f. [(cites: manning1999foundations)](#manning1999foundations)): get the likelihood
<span class='math'>P(w)</span> for the surface form <span class='math'>w</span>, by counting the amount of word-forms <span class='math'>f(w)</span>
in a corpus and divide it by the number of word-forms in the whole corpus
<span class='math'>CS</span>: <span class='math'>P(w) = \frac{f(w)}{CS}</span>.  To get around the problems with the
probability of <span class='math'>0</span> for unseen word-forms, we use additive
smoothing [(cites: chen1999empirical)](#chen1999empirical), which estimates frequency of each type
as <span class='math'>1</span> larger than it is and the size of corpus as number of types larger
<span class='math'>P(\hat w) = \frac{f(w) + 1}{CS + TC}</span>, where <span class='math'>TC</span> is a type count. The
acquired likelihoods are combined to the finite-state morphological analyser
by producing a weighted finite-state automaton for language model and
composing it over the analyser to create a morphological analyser capable of
producing both analyses and their likelihoods as shown in the last frame of
figure [(see: fig:combo)](#fig:combo). (footnote: The availability of accurate probabilistic
data on the analyser is dependent on acquisition of suitable huge corpora,
the default build includes “toy” weights that estimate probabilities by
linguistic insights). The probability-weighted analysis can be combined with
rule-based probability-aware constraint grammars to produce robust
disambiguating analysers [(cites: pirinen2015using)](#pirinen2015using).

## Data
<a id="sec:data">(¶ sec:data)</a>

There are a few freely available open resources for lexicographical data of
Finnish. The first one we used is based on lexicographical data of the
dictionary from institute of languages of Finland, that has been available
under free software licence GNU LGPL since 2007, in a column titled
*Kotus* (footnote: <http://kaino.kotus.fi/sanat/nykysuomi>).  The
second source of lexical data we acquired from the internet is a free, open
source database named
*Joukahainen.* (footnote: <http://joukahainen.puimula.org>) For
another source of lexical data we use the popular crowd-sourced
*Wiktionary* project.  We have used data from
*FinnWordNet* [(cites: linden2010finnwordnet)](#linden2010finnwordnet), as well as gathered data
from students and various yet unpublished projects of University of Helsinki,
and finally a number of contributors within project have added word-forms and
attributes specifically for *Omorfi* using semi-automatic and manual
approaches. The current dictionary includes 424,259 lexemes, classified in over
17 categories, including semantic features like biological gender, proper noun
categories as well as morphosyntactic features like argument structures and
defective paradigms. (footnote: figures change nearly weekly, up-to-date
information is on the project web site)



## Experimental Setup and Evaluation
<a id="sec:evaluation">(¶ sec:evaluation)</a>

In this section we evaluate Omorfi to give an impression of its usefulness
in various tasks and potential caveats when using for linguistic research.
For evaluation we use only freely available corpora. The size of the corpora
is detailed in table [(see: table:corpora)](#table:corpora). Following corpora are included:
ebooks of project Gutenberg (footnote: <http://gutenberg.org>), the data
of Finnish Wikipedia (footnote: <http://fi.wikipedia.org>), and the JRC
acquis corpus (footnote: <http://ipsc.jrc.ec.europa.eu/index.php?id=198>).
For downloading and preprocessing these corpora we use freely available
scripts  (footnote: <https://github.com/flammie/bash-corpora>). The
scripts retain most of the punctuation and white-space as-is. The resulting
token counts are given in table [(see: table:corpora)](#table:corpora). Some further tests were
made with fully tokenised and analysed
FinnTreeBank [(cites: voutilainen2012specifying)](#voutilainen2012specifying) version 3.1.  The scripts
used for this evaluation are part of Omorfi source code and are usable for
anyone.


**Table:**
    <div style='font-size: xx-small'>
<!-- centering -->


| ---- | ---- | ---- |
| <!-- bf -->Feature:  |  Tokens      |  Types     |
| <!-- bf -->Corpus    |              |            |
| Gutenberg     |  36,743,872  |  1,590,642 |
| Wikipedia     |  55,435,341  |  3,223,985 |
| JRC Acquis    |  42,265,615  |  1,425,532 |
| FTB 3.1       |  76,369,439  |  1,648,420 |

(Caption: Corpora used for evaluations. Tokens are all strings extracted from
corpus and types are unique strings, both include punctuation and some
codified expressions like URLs, addresses etc.
  <a id="table:corpora">(¶ table:corpora)</a>)
  </div>
<!-- end table -->

First we measure how big proportion of data in the material are
out-of-vocabulary items. This gives us naive coverage, formally defined as
<span class='math'>\mathrm{Coverage} = \frac{\mathrm{Analysed}}{\mathrm{Corpus size}}</span>.
The results are presented in table [(see: table:coverage)](#table:coverage) for all the
corpora we have.


**Table:**
    <div style='font-size: xx-small'>
<!-- centering -->


| ---- | ---- | ---- | ---- | ---- |
| Corpus:             |  <!-- bf -->Gutenberg  |  <!-- bf -->Wiki  |  <!-- bf -->JRC acquis  |  <!-- bf -->FTB 3.1 |
| Coverage (tokens):  |  97.2 %        |  93.3 %   |  92.2 %         |  96.8 % |
| Coverage (types):   |  90.9 %        |  87.6 %   |  82.9 %         |  87.6 % |

(Caption: Naive coverages when analysing common corpora
    <a id="table:coverage">(¶ table:coverage)</a>)
  </div>
<!-- end table -->


Faithfulness is measured as a proportion of equal analyses, formally <span class='math'>\mathrm{Faithfulness} =
\frac{\mathrm{Matched}}{\mathrm{Correct} + \mathrm{Missing}}</span>. In
table [(see: table:quality)](#table:quality) we show the results for FTB3.1 corpus and
analyses, first by proportion of all tokens in data then by unique tokens.


**Table:**
    <div style='font-size: xx-small'>
<!-- centering -->


| ---- | ---- | ---- |
| <!-- bf -->Corpus  |  <!-- bf -->Faithfulness |
| FTB (tokens)  |  93.3 % |
| FTB (types)   |  77.0 % |

(Caption: The amount of FTB3.1 analyses Omorfi can analyse with exact
match in results, from FTB3.1 reference corpus<a id="table:quality">(¶ table:quality)</a>)
  </div>
<!-- end table -->

The sizes and processing speeds for automata built from the data described in
section [(see: sec:data)](#sec:data) using Debian packaged HFST software
version 3.8.3 (footnote: <http://wiki.apertium.org/wiki/Prerequisites_for_Debian>)
on a Dell XPS 13 laptop are given in table [(see: table:size-speed)](#table:size-speed). The speed
was averaged over three runs using 1 million first tokens from europarl.


**Table:**
    <div style='font-size: xx-small'>
<!-- centering -->


| ---- | ---- |
| <!-- bf -->Feature  |  <!-- bf -->Value |
| Size  |  22M |
| Speed  |  11,099 wps|

(Caption: Size of Omorfi analyser as measured by `ls -lh`, speed
of analysis using hfst-lookup in words per second averaged over three runs
    <a id="table:size-speed">(¶ table:size-speed)</a>)
    </div>
<!-- end table -->

This result is in line with previous research on speed of optimised finite-state
automata in natural language processing by [(cites: silfverberg2009hfst)](#silfverberg2009hfst).

## Discussion and Future Work
<a id="sec:discussion">(¶ sec:discussion)</a>

We have showed mature, jointly developed open source natural language analyser
using both rule-based and statistical analysis approaches, and crowd-sourced
lexicography development.The techniques of statistical language parsing in
Omorfi are quite modest at modern standards, while successful combination of
statistical parsing and rule-based disambiguation is shown to be usable for a
range of NLP applications, it would be interesting to see the effects of more
representative corpora used with different methods to parsing quality of
Omorfi.  In particular, it would be interesting to see some development on an
end-user application that necessitates a use of high-quality disambiguated
morphological analyses.  We expect that development towards universally
recognised and comparable linguistic resources by projects like Universal
dependencies will be crucial to future development of Omorfi to the direction
of state-of-the-art language processing.

One of the key components to recent success of Omorfi that this article also
outlines is its adaptability and usefulness over various end uses.  While it
seems from the number of end users that it is in fact possible for independent
researchers to use and develop Omorfi, it would be interesting to see how more
linguists and lexicographers using Omorfi might improve the description as well
as end application quality.

### Error Analysis

The coverage of the analyser is systematically around 98 %, this is virtually
at the upper limits of reasonable results with the given corpora.  This can be
noticed by analysing the errors or the out-of-vocabulary word-forms left in the
current corpora. For Wikipedia, we get word-forms codes like *Lä*,
*amp*, English like *of*, *The*, and so forth. In the
Gutenberg corpus, we get, among some missing proper nouns, archaic and
dialectal forms like: *nämät*, *kauvan*, *sitte*.  While
these can be added to the analyser quite easily, the  examples will show what
is known as *Zipfian distribution* of language data: rare word-forms and
phenomena get exponentially rarer, thus the effect of collecting and
classifying further lexemes will become insignificantly small (compare
to [(cites: manning2011part)](#manning2011part)). For applications requiring higher, potentially
100 % coverage, using guessing techniques, e.g. [(cites: mikheev1997automatic)](#mikheev1997automatic),
should be investigated.

FTB3.1 evaluation is presented here as an example of customising Omorfi for an
end user, and the faithfulness evaluations are based on comparison against an
unknown closed source commercial tagger of FTB3.1. While we have mostly done
our best to match the reference analyses, we have not degraded the analyser
quality to match analyses what we view as bugs in the corpus. As an example of
mismatched analyses right now: top wrong word-forms *oli* ‘was’,
*olivat* ‘were’ are analysed as present tense in their annotations. We
feel this is incorrect and does not warrant such analysis. In the near future
we will use a free and open source, human-verified reference corpora instead,
such as UD Finnish [(cites: pyysalo2015universal)](#pyysalo2015universal), to gain stable high-quality
analysis.


## Conclusion
<a id="sec:conclusion">(¶ sec:conclusion)</a>

In this article we present a new fully open source Finnish
morphological lexicon. We confirm that it is full-fledged and mature lexical
database that can be used as a baseline morphological analyser with large
coverage, suitable for linguistic research, as well as in external applications
such as spelling correction and machine translation. We have shown
some approaches that make available use of modern natural language processing
techniques like statistics in conjunction with analysers built from our data
and paved a way forward for researchers interested those topics. We also
provide some easy-to-access ways for linguists and researchers to use and
extend our database via publicly maintained servers and crowd-sourced web-based
services.

<!-- bib style: apalike -->
# References

* <a id="koskenniemi1983twolevel">**koskenniemi1983twolevel**</a>:
    * author: Kimmo Koskenniemi
    * title: Two-level Morphology: A General Computational Model for Word...
    * school: University of Helsinki
    * year: 1983
    * url: http://www.ling.helsinki.fi/koskenni/doc/Two-LevelMorphology...
* <a id="manning1999foundations">**manning1999foundations**</a>:
    * title: Foundations of statistical natural language processing
    * author: Manning, Christopher D and Schütze, Hinrich
    * year: 1999
    * publisher: MIT press
* <a id="koskenniemi2008build">**koskenniemi2008build**</a>:
    * title: How to Build an Open Source Morphological Parser Now
    * author: Koskenniemi, Kimmo
    * journal: Resourceful Language Technology: Festschrift in Honor of Ann...
    * pages: 86–
    * year: 2008
* <a id="hfst2012">**hfst2012**</a>:
    * author: Krister Lind
’{e}n and Erik Axelson and Senka Drobac and Sa...
    * title: Using HFST for Creating Computational Linguistic Application...
    * booktitle: Proceedings of Computational Linguistics - Applications, 201...
    * year: 2012
* <a id="pirinen2008suomen">**pirinen2008suomen**</a>:
    * title: Suomen kielen äärellistilainen automaattinen morfologinen an...
    * year: 2008
    * author: Tommi Pirinen
    * school: Helsingin yliopisto
    * url: http://www.helsinki.fi/%7Etapirine/gradu/
* <a id="pirinen2009weighted">**pirinen2009weighted**</a>:
    * Author: Krister Lindén and Tommi Pirinen
    * Booktitle: Nodalida 2009
    * series: NEALT Proceedings
    * volume: 4
    * editor: Kristiina Jokinen and Eckhard Bick
    * Title: Weighted Finite-State Morphological Analysis of Finnish Comp...
    * URL: http://www.ling.helsinki.fi/klinden/pubs/linden09dnodalida.p...
    * Year: 2009
* <a id="pirinen2009weighting">**pirinen2009weighting**</a>:
    * Author: Krister Lindén and Tommi Pirinen
    * Booktitle: FSMNLP 2009
    * editor: Bruce Watson and Derrick Courie and Loek Cleophas and Pierre...
    * month: July
    * isbn: 978-1-86854-743-2
    * Title: Weighting Finite-State Morphological Analyzers using HFST to...
    * URL: http://www.ling.helsinki.fi/klinden/pubs/fsmnlp2009weighting...
    * Year: 2009
* <a id="linden2008probabilistic">**linden2008probabilistic**</a>:
    * title: A probabilistic model for guessing base forms of new words b...
    * author: Lindén, Krister
    * booktitle: Computational Linguistics and Intelligent Text Processing
    * pages: 106–116
    * year: 2008
    * publisher: Springer Berlin Heidelberg
* <a id="pirinen2015using">**pirinen2015using**</a>:
    * title: Using weighted finite state morphology with VISL CG-3—Some e...
    * author: Pirinen, Tommi A
    * booktitle: Workshop on Constraint Grammars in NODALIDA 2015
    * year: 2015
* <a id="karlsson1995constraint">**karlsson1995constraint**</a>:
    * title: Constraint Grammar: a Language-Independent System for Parsin...
    * author: Karlsson, Fred and Voutilainen, Atro and Heikkilä, Juha and ...
    * volume: 4
    * year: 1995
    * publisher: De Gruyter Mouton
* <a id="durrett2013supervised">**durrett2013supervised**</a>:
    * title: Supervised Learning of Complete Morphological Paradigms
    * author: Greg Durrett and John DeNero
    * year: 2013,
    * URL: http://aclweb.org/anthology//N/N13/N13-1138.pdf
    * booktitle: Proceedings of the North American Chapter of the
* <a id="pyysalo2015universal">**pyysalo2015universal**</a>:
    * title: Universal Dependencies for Finnish
    * author: Pyysalo, Sampo and Kanerva, Jenna and Missilä, Anna and Laip...
    * booktitle: Nordic Conference of Computational Linguistics NODALIDA 2015
    * pages: 163
    * year: 2015
* <a id="pirinen2014weighted">**pirinen2014weighted**</a>:
    * author: Pirinen, Tommi A
    * title: Weighted Finite-State Methods for Spell-Checking and Correct...
    * school: University of Helsinki
    * year: 2014
* <a id="toivanen2012corpus">**toivanen2012corpus**</a>:
    * title: Corpus-Based Generation of Content and Form in Poetry
    * author: Toivanen, Jukka and Toivonen, Hannu and Valitutti, Alessandr...
    * booktitle: Proceedings of the Third International Conference on Computa...
    * year: 2012
* <a id="clifton2011combining">**clifton2011combining**</a>:
    * author: Clifton, Ann and Sarkar, Anoop
    * title: Combining Morpheme-based Machine Translation with Post-proce...
    * booktitle: Proceedings of the 49th Annual Meeting of the Association fo...
    * series: HLT ’11
    * year: 2011
    * isbn: 978-1-932432-87-9
    * location: Portland, Oregon
    * pages: 32–42
    * numpages: 11
    * url: http://dl.acm.org/citation.cfm?id
    * acmid: 2002477
    * publisher: Association for Computational Linguistics
    * address: Stroudsburg, PA, USA
    * flammie: smt eng-fin
* <a id="rubino2015abumatran">**rubino2015abumatran**</a>:
    * title: Abu-MaTran at WMT 2015 Translation Task: Morphological Segme...
    * author: Rubino, Raphael and Tommi Pirinen andMiquel Esplà-Gomis and ...
    * journal: EMNLP 2015
    * pages: 
    * year: 2015
    * note: (to appear)
* <a id="haverinen2013building">**haverinen2013building**</a>:
    * year: 2013
    * issn: 1574-020X
    * journal: Language Resources and Evaluation
    * doi: 10.1007/s10579-013-9244-1
    * title: Building the Essential Resources for Finnish: the Turku Depe...
    * url: http://dx.doi.org/10.1007/s10579-013-9244-1
    * publisher: Springer Netherlands
    * keywords: Treebank; Finnish; Parsing; Morphology
    * author: Haverinen, Katri and Nyblom, Jenna and Viljanen, Timo and La...
    * pages: 1-39
    * language: English
* <a id="bohnet2013joint">**bohnet2013joint**</a>:
    * title: Joint Morphological and Syntactic Analysis for Richly Inflec...
    * year: 2013
    * author: Bernd Bohnet and Joakim Nivre and Igor Bouguavsky and Richár...
    * booktitle: Transactions of the Association for Computational Linguistic...
    * number: 1
    * pages: 415–428
* <a id="maxwell2008joint">**maxwell2008joint**</a>:
    * title: Joint Grammar Development by Linguists and Computer Scientis...
    * author: Michael Maxwell and Anne David
    * year: 2008
    * booktitle: Workshop on NLP for Less Privileged Languages, Third Interna...
    * address: Hyderabad, India
* <a id="beesley2003finite">**beesley2003finite**</a>:
    * title: Finite State Morphology
    * year: 2003
    * author: Kenneth R Beesley and Lauri Karttunen
    * pages: 503
    * publisher: CSLI publications
    * isbn: 978-1575864341
* <a id="openfst">**openfst**</a>:
    * author: Cyril Allauzen and Michael Riley and Johan Schalkwyk and Woj...
    * year: 2007
    * title: OpenFst: A General and Efficient Weighted Finite-State Trans...
    * pages: 11–23
    * booktitle: Proceedings of the Twelfth International Conference on Imple...
    * series: Lecture Notes in Computer Science
    * volume: 4783
    * publisher: Springer
    * url: http://www.openfst.org
* <a id="chen1999empirical">**chen1999empirical**</a>:
    * title: An Empirical Study of Smoothing Techniques for Language Mode...
    * author: Chen, Stanley F and Goodman, Joshua
    * journal: Computer Speech & Language
    * volume: 13
    * number: 4
    * pages: 359–393
    * year: 1999
    * publisher: Elsevier
* <a id="linden2010finnwordnet">**linden2010finnwordnet**</a>:
    * title: FinnWordNet-WordNet på finska via översättning
    * author: Lindén, Krister and Carlson, Lauri
    * journal: LexicoNordica
    * year: 2010
    * publisher: Nordisk Forening för Leksikografi
* <a id="voutilainen2012specifying">**voutilainen2012specifying**</a>:
    * title: Specifying Treebanks, Outsourcing Parsebanks: Finntreebank 3
    * author: Voutilainen, Atro and Muhonen, Kristiina and Purtonen, Tanja...
    * booktitle: Proceedings of LREC 2012 8th ELRA Conference on Language Res...
    * year: 2012
* <a id="silfverberg2009hfst">**silfverberg2009hfst**</a>:
    * title: Hfst runtime format—a compacted transducer format allowing f...
    * author: Silfverberg, Miikka and Lindén, Krister
    * booktitle: FSMNLP
    * volume: 13
    * year: 2009
* <a id="manning2011part">**manning2011part**</a>:
    * title: Part-of-speech tagging from 97
% to 100
%: is it time for ...
    * author: Manning, Christopher D
    * booktitle: Computational Linguistics and Intelligent Text Processing
    * pages: 171–189
    * year: 2011
    * publisher: Springer
* <a id="mikheev1997automatic">**mikheev1997automatic**</a>:
    * author: Mikheev, Andrei
    * title: Automatic Rule Induction for Unknown-word Guessing
    * journal: Comput. Linguist.
    * issue_date: September 1997
    * volume: 23
    * number: 3
    * month: sep,
    * year: 1997
    * issn: 0891-2017
    * pages: 405–423
    * numpages: 19
    * url: http://dl.acm.org/citation.cfm?id
    * acmid: 972708
    * publisher: MIT Press
    * address: Cambridge, MA, USA

<!-- if final -->
<!-- new page -->
<div style='font-size: small'>
<!-- no indent --> Contact Information:



Tommi A Pirinen

Ollscoil Chathair Bhaile Átha Cliath

IE-D09 W6Y4

Éire

e-mail: <Tommi.Pirinen@computing.dcu.ie>

</div>
<!-- fi -->
<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

