

<!-- usepackage fontspec  -->
<!-- usepackage booktabs  -->

<!-- set main font Liberation Serif  -->


<!-- new if ifcameraready -->\camerareadytrue
<!-- usepackage enumitem  -->
<!-- set list noitemsep, label={\large\textbullet [itemize] -->}

<!-- begin document -->

# Building minority dependency treebanks, dictionaries and computational grammars at the same time: an experiment in Karelian treebanking

<!-- if cameraready -->
**Authors:** Tommi A Pirinen

Universität Hamburg

Hamburger Zentrum für Sprachkorpora

Max-Brauer-Allee 60, D-22765 Hamburg

<tommi.antero.pirinen@uni-hamburg.de>

<!-- fi -->

**Date:** (date of conversion: 2025-12-31)


<!-- make title -->


**Abstract:**
Building a treebank from scratch can easily be an elaborate, highly time
consuming task, especially when working with a minority
language with moderately complex morphology and no existing resources. It is
also then typically true that language experts and informants with
suitable skill sets are a very scarce resource.  In this experiment I have
attempted to work in parallel on building NLP resources while gathering and
annotating the treebank. In particular, I aim to build a decent coverage
morphologically annotated lexicon suitable for rule-based morphological
analysis as well as accompanying rules for basic morphosyntactic analysis.
I propose here a workflow, that I have found useful in avoiding redoing same
work with related NLP resource construction.
<!-- end abstract -->



## Introduction

Karelian languages are languages closely related to Finnish spoken mainly in the
republic of Karelia in Russia and surroundings. The languages are split in the
ISO 639–3 standard between a few language codes: *Karelian* (krl) and
*Livvi* or Olonets karelian (olo) for the two main branches of the
language. The fact that ‘krl’ is commonly refered to as just Karelian can be
confusing because ‘olo’ is also Karelian but I try to make the distinction clear
throughout the article by using the ISO codes when necessary. The division is
not totally unproblematic but I have followed it in the treebank for ease of
development and use. There are some 35,000 native speakers of Karelian
(krl)  (footnote: <https://www.ethnologue.com/18/language/krl/>) and 31,000
for Livvi (olo)  (footnote: <https://www.ethnologue.com/18/language/olo/>)
according to Ethnologue, and both are classified as “Developing”.  The
languages are developed enough to have some
grammars [(cites: zaikov2013vienankarjalan,ahtia1938karjalan,markianova2002karjalan)](#zaikov2013vienankarjalan,ahtia1938karjalan,markianova2002karjalan),
dictionaries and books written, as well as some regular newspapers and
broadcasts, but very few digital or computational resources so far. For
unannotated corpora I have found a source with freely usable texts classified
according to ISO language codes.

This paper discusses creation and ongoing work for two Karelian treebanks and
compatible morphological parsers. The first part of the Karelian data will be
included in the 2.4 release of the Universal Dependencies and I hope to enlarge
and verify the data with native informants as well as include the Livvi data
by the next release. The treebanks were named under the abbreviation of KKPP or
*Karjalan kielten puupankit* which is Finnish for Karelian treebanks.

The rest of the article is organised as follows: in Section [(see: sec:background)](#sec:background)
I describe the languages and our goals for the treebanking, in
Section [(see: sec:methods)](#sec:methods) I describe the tools and methods for building
treebanks, in Section [(see: sec:data)](#sec:data) I describe the corpus selection and
finally in Section [(see: sec:discussion)](#sec:discussion) I summarise the article and talk about
future work and ideas.

## Background
<a id="sec:background">(¶ sec:background)</a>

As languages with very few available NLP resources, one of our first goals is to
get annotated corpora. The universal dependencies format is a good choice for a
standard for writing a new treebank at the moment; it has been used with many
Uralic languages already that provide for reference for difficult situations.
Also, the North Saami treebank was made based on a rule-based finite-state
morphological analyser [(cites: sheyanova2017annotation)](#sheyanova2017annotation), building one of which is
also a goal for us, so I can safely say that the two formats are compatible and
complement each other.  One of the reasons why  I make morphological analysers
is to be able to provide number of end-user tools like spell-checking and
correction as well as the reference corpus, for example in other Uralic
languages there are plenty of resources hosted by
giellatekno [(cites: moshagen2014open)](#moshagen2014open).

When I started with the treebanking, morphological analyser writing task, there
were virtually no freely available corpora for Karelian and also no electronical
dictionaries or analysers for Karelian krl. There was an existing analyser for
Livvi and for that reason I have started our project with Karelian first. For
digitised paper dictionaries, I have a dictionary for Karelian
languages (footnote: <http://kaino.kotus.fi/cgi-bin/kks/kks_etusivu.cgi>),
that covers both Karelian and Livvi. The overall format and transcription
differences, however, make it not directly usable for a source dictionary for
morphological analyser for Karelian languages but rather an semi-automated
source reference.

One of the thing I have established in the research of under-resourced
languages in Uralic space is that for the survival and digital survival of
a language certain technological resources need to be developed, and our
aim with this project is to build as many of the necessary resources rapidly as
possible.

One of the things that I have taken into consideration working on this
treebank is how corpora are built within Uralic linguistic community
outside the Universal Dependencies, e.g. in documentary linguistics.
One of the prominent paradigms there is based on the line of tools
from SIL shoebox to Fieldworks Explorer (FLeX), the workflow within
those makes use of building corpora and dictionary simultaneously
and this experiment is in a way our precursory study to implementing
a similar tool for dependency treebanking style of linguistics. For reference on
such Uralic research within computational linguistics
see [(cites: blokland2015language)](#blokland2015language).

Furthermore I are developing a morpho-syntactic rule-based methodology that can
provide partial, ambiguous dependency graphs. The approach of building
rule-based analysers first is very prominent within computational linguistics
research of Uralic languages. In this article I are aiming to connect the
traditional development of rule-based morphological analysers into treebanking
workflow in a manner that optimises the usage of native informants’ and the
computational linguists’ time, which is a crucial component for development in
a very under-resourced setting.

Finally, I aim to have wide coverage of Uralic languages in the Universal
Dependency project treebanks, and further study and experiment in the
state-of-the-art methodology in large variety of NLP and typological research
topics that have been empowered by the project. At the moment there are 6 Uralic
treebanks available:
Finnish [(cites: haverinen2014building,voutilainen2012specifying)](#haverinen2014building,voutilainen2012specifying),
Estonian [(cites: muischnek2016estonian)](#muischnek2016estonian),
Hungarian [(cites: vincze2010hungarian)](#vincze2010hungarian),
North Saami [(cites: sheyanova2017annotation)](#sheyanova2017annotation),
Komi [(cites: partanen2018first)](#partanen2018first), and
Erzya [(cites: rueter2018towards)](#rueter2018towards), out of some 30 that can easily have treebanks.

## Methods
<a id="sec:methods">(¶ sec:methods)</a>

One of the contributions of this article is, that I am developing a sustainable
workflow for creation of a wide array of technological resources for a seriously
under-resourced language. For language technology infrastructure I will make
use of an existing language technology infrastructure developed
by [(cites: moshagen2014open)](#moshagen2014open), which I have selected because it provides a number
of necessary components for free once morphological analysers are built, e.g.
automatic spell-checking, machine-translation and so on.

The morphological analysis is based on the finite-state
morphology [(cites: beesley2003finite)](#beesley2003finite), this means in practice that one needs to
build a dictionary and morphological rules describing the morphological
processes. To couple the dictionary building with treebanking effort I have
developed a method to generate lexicon entries from the annotated treebank data.
I also use the analysers to generate suggestions for the annotators for the
dependency annotations.

To give an example of the resource building workflow, a sentence might be
annotated in CONLL-U format like:

<div style='font-size: xx-small'>

```

# sent_id = vepkar-1774.7
# text = – Myö toivomma, jotta meijän kuččuh vaššatah starinankertojat ta guslinšoittajat, jotta kaččojat šuahah nähä
vanhanaikasien rahvahantapojen rekonstruointie, koroššetah järještäjät..
1       –       –       PUNCT   PUNCT   _       3       punct   _       Weight=0.0033333333333333335
2       Myö     myö     PRON    PRON    Case=Nom|Number=Sing|Person=1|PronType=Prs      3       nsubj   _       Weight
=500.0
3       toivomma        toivuo  VERB    VERB    Mood=Ind|Number=Plur|Person=1|Tense=Pres|VerbForm=Fin|Voice=Act 0
root    _       Weight=0.0194|SpaceAfter=No
4       ,       ,       PUNCT   PUNCT   _       8       punct   _       Weight=518.6755555555555
5       jotta   jotta   SCONJ   SCONJ   _       8       mark    _       Weight=0.002142857142857143
6       meijän  myö     PRON    PRON    Case=Gen|Number=Plur|Person=1|PronType=Prs      7       nmod:poss       _
Weight=500.0
7       kuččuh  kučču   NOUN    NOUN    Case=Ill|Number=Sing    8       obl     _       Weight=500.0
8       vaššatah        vaššata VERB    VERB    Mood=Ind|Number=Plur|Person=3|Tense=Pres|VerbForm=Fin|Voice=Act 3
ccomp   _       Weight=500.0248
9       starinankertojat        starinan#kertoja        NOUN    NOUN Case=Nom|Number=Plur    15      nsubj   _  _

```

</div>

For a rule-based morphological parser an entry is needed to have at least
dictionary form or lemma, and a paradigm for inflectional information; for
languages like Karelian one cannot fully guess an entry for an inflectional
paradigm from a single example but can usually give quite short list of
plausible choices. So, I always extend our dictionaries with the entries from
the annotated trees.


Likewise when annotating, I use the morphological analyser that is readily
built with UD analyses: lemmas, UPOS and morphological features as well as
some rough guesses when possible for the deps (e.g. puncts, Case-based
dependencies); the python-based guesser for dependencies can currently handle
things like: select `PUNCT` and suggest an attachment to each of the
`VERB`s in sentence with `punct` dep,
or select feature `Case=Acc` and suggest attachment to all
`VerbForm=Fin` in the sentence with an `obj` dep.
Thus, I can generate suggestion lists like:

<div style='font-size: xx-small'>

```

# sent-id: &lt;stdin&gt;.21
# text: Koštamukšelaiset toivotah, jotta Koštamukšen ta Petroskoin šekä muijen
# kaupunkien välillä olis järješšetty šiännöllini lentoyhteyš.
1  Koštamukšelaiset  Koštamukšelaiset  X  X  _  _  _  _  SpaceBefore=No|_
2  toivotah  toivuo  VERB  VERBMood=Ind|Number=Plur|Person=3|Tense=Pres|VerbForm=Fin|Voice=Act  0  root  _ _
2  toivotah  toivuo  VERB  VERB  Mood=Ind|Tense=Pres|VerbForm=Fin|Voice=Pass  0  root  _  SpaceAfter=No
3  ,  ,  SYM  SYM  _  _  _  _  SpaceBefore=No|Weight=506.4
3  ,  ,  PUNCT  PUNCT  _  2  punct  _  SpaceBefore=No|Weight=0.0033333333333333335
3  ,  ,  PUNCT  PUNCT  _  13  punct  _  SpaceBefore=No|Weight=0.03333333333333333
4  jotta  jotta  SCONJ  SCONJ  _  13  mark  _  Weight=0.0225
5  Koštamukšen  Koštamukšen  X  X  _  _  _  _  _
6  ta  ta  CCONJ  CCONJ  _  7  cc  _  Weight=0.01
7  Petroskoin  Petroskoi  PROPN  PROPN  Case=Gen|Number=Sing  2  obj  _  PropnType=Top|Weight=0.016666666666666666

```

</div>

A linguist is provided with this suggestion list per token in order defined by
the weights,at the moment expert-determined rule-weighting but when we have
large enough corpus I can easily incorporate the unigram log probabilities into
weights as well. It should be noted that the linguist is allowed to discard all
suggestions and this shall not be considered an unusual case while
simultaneously building the analyser and the treebank. The current annotators
also use an editor that is automatically running the validation
tests (footnote: <https://github.com/universaldependencies/tools/validate.py
>) for UD after each edit and highlighting problems on the fly. The tools that
I have developed so far will also be released with a free/libre open source
licence.

When working on the annotation and guidelines I relied quite heavily on
existing Uralic treebanks, especially Finnish since it is a closely related
language with three treebanks and documentation. For many structures it is
possible to find near or exact match using treebank
search  (footnote: <http://bionlp-www.utu.fi/dep_search/>). For example, the
copula structure including the possession structure is marked in the same way in
Finnish and Karelian languages, and generally many cases, function words and so
forth, overlap with few systematic changes (e.g. in most parts of Karelian
(krl) adessive and ablative have same form). Many of the examples where I did
not find equivalents in Finnish I looked at other Uralic languages, or Russian,
for example in elliptical structures a long hyphen is often used in Karelian and
Russian to mark some elided tokens but not in contemporary Finnish in the genres
of the UD treebanks at least.

Finally, this workflow goes on to ensure that the morphological analysers I
build will have virtually a 100 % coverage of the treebank released, with a
very high rate of recall for the treebank fields: lemma, UPOS and the lexical
and morphological feature definitions. The reason recall is not 100 % is that
there will be some annotations that, while theoretically correct, are not
wanted in a normative analyser, e.g. colloquial uses of certain case forms in
a role that is not the literary standard, as well as typos and mistakes,
however, I might change this practice in the future with universal feature
`Style=Coll`. (footnote: I thank the anonymous reviewer for the helpful
suggestion.)


**Table:**
    <div style='text-align: center'>


| Language  |  Lexicon size |
| ---- | ---- |
| Karelian  |  1452 |
| Livvi  |  56,377 |

(Caption: The sizes of analysers of Uralic languages.<a id="table:analysers">(¶ table:analysers)</a>)
    </div>
<!-- end table -->

## Data
<a id="sec:data">(¶ sec:data)</a>

There is not a great amount of available data written in Karelian languages to
begin with. Furthermore, while there have been written texts for some time, the
newest standard ortographies are quite recent, and there is some amount of
variation from text to text in the written forms that is not the same as with
older more standardised languages. Added to that is that telling languages
apart, especially in less standard more dialectal writing, becomes non-trivial
task. I started my data collection with web-crawling, and eventually found a
corpus collection web site with open licencing policy, and the languages I want
to work on categorised by language and genre, called
VepKar. (footnote: <http://dictorpus.krc.karelia.ru/>) The open licence also
lets us work on articles instead of shuffled sentences, so it is another
advantage.

By the time of writing I have developed a releasable treebank for Karelian and
a morphological analyser, which are summarised in the table [(see: table:stats)](#table:stats),
I have also begun the work on Livvi treebank, which already had a usable
analyser in place. For comparison I show some of the other existing Uralic
treebanks for reference. Number of dependency trees annotated for
non-Karelian languages is based on universaldependencies.org’s statistics.


**Table:**
    <div style='text-align: center'>


| Treebank  |  Dependency trees  |  Syntactic words|
| ---- | ---- | ---- |
| Karelian  |  228  |  3094 |
| Livvi  |  20  |  461 |
| Finnish  |  34,859  |  377,822 |
| Estonian  |  32,385  |  461,531 |
| North Saami  |  3122  |  26,845 |
| Hungarian  |  1800  |  42,032 |
| Erzya  |  1550  |  15,790 |
| Komi  |  307  |  3304 |

(Caption: The sizes of treebanks of Uralic languages.
Dependency trees is number of annotated sentences and syntactic words
as defined in UD guidelines.<a id="table:stats">(¶ table:stats)</a>)
    </div>
<!-- end table -->

## Discussion and future work
<a id="sec:discussion">(¶ sec:discussion)</a>

I have achieved a baseline universal dependency treebank and a morphological
analyser for a minority language without pre-existing resources, and started
working on a second treebank on a language with pre-existing analyser. In the
next part I will contact more experts to verify the analyses and work on
extending the treebanks as well as the analysers.

## Acknowledgments
<a id="sec:acknowledgments">(¶ sec:acknowledgments)</a>

<!-- if camerareadyThe --> author was employed by CLARIN-D during the project.
<!-- fi -->

<!-- bib style: unsrt -->
# References

* <a id="zaikov2013vienankarjalan">**zaikov2013vienankarjalan**</a>:
    * author: Zaikov, Pekka
    * subtitle: Lisänä harjotuk{š}ie ta lukemisto
    * title: Vienankarjalan kielioppi
    * year: 2013
* <a id="ahtia1938karjalan">**ahtia1938karjalan**</a>:
    * author: Ahtia, Edvard Vilhelm
    * publisher: Karjalan Kansalaisseura
    * title: Karjalan kielioppi
    * year: 1938
* <a id="markianova2002karjalan">**markianova2002karjalan**</a>:
    * author: Markianova, Ludmila
    * journal: Periodika, Petroskoi
    * title: Karjalan kielioppi 5-9
    * url: https://opastajat.net/opastus/grammar/index.html
    * year: 2002
* <a id="sheyanova2017annotation">**sheyanova2017annotation**</a>:
    * author: Mariya Sheyanova and Francis M. Tyers
    * booktitle: Proceedings of the 3rd International Workshop for
    * pages: 66–75
    * title: Annotation schemes in North Sámi dependency parsing
    * year: 2017
* <a id="moshagen2014open">**moshagen2014open**</a>:
    * author: Moshagen, Sjur and Rueter, Jack and Pirinen, Flammie and
    * booktitle: Proceedings of e Ninth International Conference on Language
    * pages: 71–77
    * title: Open-Source Infrastructures for Collaborative Work on
    * year: 2014
* <a id="blokland2015language">**blokland2015language**</a>:
    * author: Blokland, Rogier and Fedina, Marina and Gerstenberger, Cipri...
    * booktitle: Septentrio Conference Series
    * number: 2
    * pages: 8–18
    * title: Language documentation meets language technology
    * year: 2015
* <a id="haverinen2014building">**haverinen2014building**</a>:
    * author: Haverinen, Katri and Nyblom, Jenna and Viljanen, Timo and
    * journal: Language Resources and Evaluation
    * number: 3
    * pages: 493–531
    * publisher: Springer
    * title: Building the essential resources for Finnish: the Turku Depe...
    * volume: 48
    * year: 2014
* <a id="voutilainen2012specifying">**voutilainen2012specifying**</a>:
    * author: Voutilainen, Atro and Muhonen, Kristiina and Purtonen, Tanja
    * booktitle: Proceedings of LREC 2012 8th ELRA Conference on Language
    * organization: European Language Resources Association (ELRA)
    * title: Specifying treebanks, outsourcing parsebanks: Finntreebank 3
    * year: 2012
* <a id="muischnek2016estonian">**muischnek2016estonian**</a>:
    * author: Muischnek, Kadri and Müürisep, Kaili and Puolakainen,
    * booktitle: LREC
    * title: Estonian Dependency Treebank: from Constraint Grammar tagset...
    * year: 2016
* <a id="vincze2010hungarian">**vincze2010hungarian**</a>:
    * author: Vincze, Veronika and Szauter, Dóra and Almási, Attila and
    * publisher: European Language Resources Association
    * title: Hungarian dependency treebank
    * year: 2010
* <a id="partanen2018first">**partanen2018first**</a>:
    * author: Partanen, Niko and Blokland, Rogier and Lim, KyungTae and
    * booktitle: Second Workshop on Universal Dependencies (UDW 2018), Novemb...
    * pages: 126–132
    * title: The first Komi-Zyrian Universal Dependencies treebanks
    * year: 2018
* <a id="rueter2018towards">**rueter2018towards**</a>:
    * author: Rueter, Jack and Tyers, Francis
    * booktitle: Proceedings of the Fourth International Workshop on
    * pages: 106–118
    * title: Towards an open-source universal-dependency treebank for Erz...
    * year: 2018
* <a id="beesley2003finite">**beesley2003finite**</a>:
    * author: Kenneth R Beesley and Lauri Karttunen
    * flammie: fsa
    * isbn: 978-1575864341
    * pages: 503
    * publisher: CSLI publications
    * title: Finite State Morphology
    * year: 2003


<!-- if cameraready -->**Authors:** Tommi A Pirinen 

Universität Hamburg 

Max-Brauer-Allee 60 

D-22765, Hamburg  

  `tommi.antero.pirinen@uni-hamburg.de` 

<!-- fi -->
<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

