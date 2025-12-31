

<!-- usepackage polyglossia  -->
<!-- usepackage fontspec  -->
<!-- usepackage xunicode  -->
<!-- usepackage xltxtra  -->
<!-- usepackage url  -->
<!-- usepackage hyperref  -->
<!-- usepackage expex  -->
<!-- usepackage natbib  -->
<!-- usepackage booktabs  -->

<!-- makeatletter -->
\def\blfootnote{\gdef\@thefnmark\@footnotetext}
<!-- makeatother -->

\setmainfont[Mapping=tex-text]{Linux Libertine O}
<!-- set main language english  -->
<!-- set main language finnish -->

<!-- new if ifcameraready -->
\camerareadytrue

<!-- begin document -->

<!-- if cameraready -->
<!-- pagestyle empty -->
<!-- fi -->

# Neural and rule-based Finnish NLP models—expectations, experiments and experiences¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: This     work is licensed under a Creative Commons Attribution     4.0 International Licence.  Licence details:     <http://creativecommons.org/licenses/by/4.0/> )</span> 

<!-- if cameraready -->
**Authors:** Tommi A Pirinen

Universität Hamburg

Hamburger Zentrum für Sprachkorpora

Max-Brauer-Allee 60, D-22765 Hamburg

<tommi.antero.pirinen@uni-hamburg.de>

<!-- fi -->

**Date:** 

<!-- make title -->
<!-- if cameraready -->
<!-- thispagestyle empty -->
<!-- fi -->


**Abstract:**
In this article I take a critical look at some recent results in the
field of neural language modeling of Finnish in terms of popular shared
tasks. One novel point of view I present is comparing the neural methods’
results to traditional rule-based systems for the given tasks, since most of
the shared tasks have concentrated on the supervised learning
concept. The shared task results I re-evaluate, are morphological
regeneration by SIGMORPHON 2016, universal dependency parsing by CONLL-2018
and a machine translation application that imitates WMT 2018 for German
instead of English. The Uralic language used throughout is Finnish. I use
out of the box, best performing neural systems and rule-based systems and
evaluate their results.
<!-- end abstract -->

{\
\selectlanguage{finnish}

**Abstract:**
Tässä artikkelissa tarkastelemme joitain hiljattaisia tuloksia
niinkutsutuissa shared task -kilpailuissa suomen kielen hemroverkkomallien
osalta. Yksi tämän artikkelin kontribuutioista on hermoverkkomallien
tuottamien tulosten vertailu perinteisiin sääntöpohjaisiin
kielimallituloksiin, sillä shared task -kisailut pääosin keskittyvät täysin
tai osittain hallitsemattomien mallien oppimisen konseptiin. Shared taskit
joita tässä artikkelissa tarkastelemme ovat SIGMORPHONin 2016 morfologisen
uudelleengeneroinnin kisa, CONLL:n 2018 jäsennyskilpailu sekä WMT 2018:n
konekäännöskilpailu uudelleensovellettuna saksan kielelle. Uralilainen kieli
jota käytämme kaikissa kokeissa on suomi. Järjestelmät joita käytetään ovat
avoimen lähdekoodin järjestelmiä jotka ovat olleet parhaita näissä
kilpailuissa.
<!-- end abstract -->
}




## Introduction

The popularity of the neural networks in natural language processing is at the
moment climbing very rapidly to the extent that we commonly get to hear that
non-neural methods should be abandoned. While naturally the majority of this
hype is based on English-centric or mostly European NLP, there are some reports
of good successes within the less resourced and more morphological languages,
including Uralic languages. In this paper I compare directly the
state-of-the-art methods between the neural and rule-based language processing
for Finnish. I specifically devised experiments based on the following shared
tasks and popular systems:


    *  Generating morphology: Sigmorphon 2016
results \citep{cotterell2016sigmorphon} vs.
omorfi \citep{omorfi}
    *  Parsing of morphosyntax: Turku neural parser \citep{kanerva2018turku}
vs. omorfi \citep{omorfi}
    *  Machine translation between Finnish and German:
OpenNMT \citep{opennmt} vs.
apertium-fin-deu \citep{pirinen2018rulebased}


Comparing a few different tasks gives us a good overview of the state of the art
in the neural processing of Finnish. Parsing tasks give an idea of the potential
usability of the language models in various linguistic tasks, such as corpus
annotation, whereas the machine translation task provides an important view on
the full capacity of the models for a more wide-ranging language understanding
task.

One of the contributions of this paper is to gain more insight of the
similarities and differences of the traditional rule-based systems for the given
tasks, since the shared tasks are virtually always earmarked for more or less
supervised language learning, any evaluations between the neural and the
rule-based systems are not so commonly found in the literature.

The rest of article is organised as follows: in Section [(see: sec:background)](#sec:background),
I introduce the shared tasks and rule-based systems at large, in
Section [(see: sec:methods)](#sec:methods), I describe the systems used for the experiments,
in Section [(see: sec:setup)](#sec:setup), I describe the system setup, in
Section [(see: sec:evaluation)](#sec:evaluation), I go through the experiments and results,
in Section [(see: sec:errors)](#sec:errors), I perform the error analysis, in
Section [(see: sec:discussion)](#sec:discussion), I relate the results to current state of the
art as well as practical usage and development of the systems and finally
in Section [(see: sec:conclusion)](#sec:conclusion), I summarise the findings.

## Background
<a id="sec:background">(¶ sec:background)</a>

In recent years the neural network-based systems, especially so-called deep
neural systems, have been brought forward as a solution to all natural language
processing problems. Some results have also been provided for Uralic languages.
In the case of morphology, there was a popular task of morphological generation
as a shared task of the ACL 2016 SIGMORPHON
workshop \citep{cotterell2016sigmorphon}, which included the Finnish generation,
and showed some very promising results. In the context of the machine
translation, the shared task of the WMT conference has had a Finnish task since
2015, and since 2017 the participants have predominantly been the neural systems
(e.g. for 2018 c.f \citet{wmt2018findings}).  For the morphosyntax, the popular
shared task to test a parser with, is the CONLL task on the dependency
parsing \citep{zeman2018conll}.  What is common with these shared tasks, is that
they are aimed for supervised learning of such language models, while in the
Uralic NLP the predominant methodology is rule-based, expert-written
systems \citep{moshagen2014open}. In this article, I take a practical comparison
of building and using the systems for the given tasks as well as a tool in
actual linguistic research.

## Methods and Datasets
<a id="sec:methods">(¶ sec:methods)</a>

Omorfi (footnote: <https://flammie.github.io/omorfi/>) is a lexical database
of Finnish, that can be compiled into a finite-state automaton for efficient
parsing.  Omorfi has wide support for morphological analysis and generation
(matching the SIGMORPHON task of morphological regeneration) and parsing
(matching the CONLL task for parsing).
Apertium-fin-deu (footnote: <https://apertium.github.io/apertium-fin-deu>) is
a hand-crafted rule-based machine translation system based on omorfi, with an
addition of a bilingual dictionary and some sets of bilingual rules. This can be
used with the apertium tools to translate between German and Finnish.

The default mode of operation in a rule-based system is often based on the
concept of *all possible hypotheses*, this is in contrast to shared
tasks, which are based on 1-best parsing instead; measuring the results is based
on only a single hypothesis per token. To bridge this gap between rule-based
morphology and shared tasks, I have used a combination of popular strategies
implemented with python scripting
language. (footnote: <https://github.com/flammie/omorfi/tree/develop/src/python>)
These strategies build in principle on both constraint
grammar \citep{karlsson1990constraint,pirinen2015using} and my previous
experiences with unigram models in rule-based
morphologies \citep{pirinen2009weighting}, it may, however, be noteworthy that
at the time of the writing the solution described is very much a work in
progress, so it should not be understood as having any specific advances over
the above-referred previous experiments yet.  Furthermore, to perform the
SIGMORPHON and CONLL tasks I have written small python scripts to analyse and
map the analyses between omorfi’s formats and theirs.  For machine translation I
use the `apertium` command and discard the debugging symbols. Examples of
the output mangling we perform can be seen in listing [(see: listing:io-mangling)](#listing:io-mangling).
As can be seen in the example, the token 7 (*2017*) has no rule-based
dependency analysis, since it is not covered by the very basic dependency
labeling script we use.


**Figure:**
    <div style='font-size: x-small'>
        
```
<span class='math'> omorfi-analyse-text.sh -X test/test.text
Juankosken   WORD_ID=Juankoski UPOS=PROPN PROPER=GEO NUM=SG CASE=GEN
Juankosken   WORD_ID=juan UPOS=NOUN SEM=CURRENCY NUM=SG CASE=NOM
BOUNDARY=COMPOUND WORD_ID=koski UPOS=NOUN NUM=SG CASE=GEN

kaupunki    WORD_ID=kaupunki UPOS=NOUN NUM=SG CASE=NOM

liittyy    WORD_ID=liittyä UPOS=VERB VOICE=ACT MOOD=INDV TENSE=PRESENT PERS=SG0

liittyy    WORD_ID=liittyä UPOS=VERB VOICE=ACT MOOD=INDV TENSE=PRESENT PERS=SG3


Kuopion    WORD_ID=Kuopio UPOS=PROPN PROPER=GEO NUM=SG CASE=GEN
Kuopion    WORD_ID=kuopia UPOS=VERB VOICE=ACT MOOD=OPT PERS=SG1 STYLE=ARCHAIC

kaupunkiin    WORD_ID=kaupunki UPOS=NOUN NUM=SG CASE=ILL

vuoden    WORD_ID=vuoden UPOS=ADV
vuoden    WORD_ID=vuosi UPOS=NOUN NUM=SG CASE=GEN

2017    WORD_ID=2017 UPOS=NUM SUBCAT=DIGIT NUMTYPE=CARD
2017    WORD_ID=2017 UPOS=NUM SUBCAT=DIGIT NUMTYPE=CARD NUM=SG CASE=NOM

alussa    WORD_ID=alku UPOS=NOUN NUM=SG CASE=INE
alussa    WORD_ID=alunen UPOS=NOUN NUM=SG CASE=ESS STYLE=ARCHAIC
alussa    WORD_ID=alussa UPOS=ADP ADPTYPE=POST
alussa    WORD_ID=alussa_2 UPOS=ADV

.    WORD_ID=. UPOS=PUNCT BOUNDARY=SENTENCE

</span> omorfi-tokenise.py -a src/generated/omorfi.describe.hfst -O conllu -i
test/test.text |
omorfi-conllu.py -a src/generated/omorfi.describe.hfst
        –not-rules src/disamparsulation/omorfi.xml

# new doc id= test/test.text
# sent_id = 1
# text = Juankosken kaupunki liittyy Kuopion kaupunkiin vuoden 2017 alussa.
1   Juankosken   Juankoski   PROPN   N   Case=Gen|Number=Sing   2   nmod:poss
_   Weight=0.01
2   kaupunki   kaupunki   NOUN   N   Case=Nom|Number=Sing   3   nsubj   _
Weight=0.005
3   liittyy   liittyä   VERB   V
Mood=Ind|Number=Sing|Person=3|Tense=Pres|VerbForm=Fin|Voice=Act   0
root   _   Weight=0.21000000000000002
4   Kuopion   Kuopio   PROPN   N   Case=Gen|Number=Sing   5   nmod:poss   _
Weight=0.01
5   kaupunkiin   kaupunki   NOUN   N   Case=Ill|Number=Sing   3   obl   _
Weight=0.01
6   vuoden   vuosi   NOUN   N   Case=Gen|Number=Sing   3   obj   _   Weight=0.015
7   2017   2017   NUM   Num   NumType=Card   _   _   _   Weight=500.0
8   alussa   alku   NOUN   N   Case=Ine|Number=Sing   3   obl   _   Weight=0.025
9   .   .   PUNCT   Punct   _   3   punct   _   Weight=0.03

    
```

Same output is directly generated by TNPP\@:

```
$ cat  /github/flammie/omorfi/test/test.text |
python3 full_pipeline_stream.py –conf models_fi_tdt/pipelines.yaml –pipeline parse_plaintext
# newdoc
# newpar
# sent_id = 1
# text = Juankosken kaupunki liittyy Kuopion kaupunkiin vuoden 2017 alussa.
1   Juankosken   Juankoski   PROPN   N   Case=Gen|Number=Sing   2   nmod:poss _
_
2   kaupunki   kaupunki   NOUN   N   Case=Nom|Number=Sing   3   nsubj   _   _
3   liittyy   liittyä   VERB   V
Mood=Ind|Number=Sing|Person=3|Tense=Pres|VerbForm=Fin|Voice=Act   0
root   _   _
4   Kuopion   Kuopio   PROPN   N   Case=Gen|Number=Sing   5   nmod:poss   _   _
5   kaupunkiin   kaupunki   NOUN   N   Case=Ill|Number=Sing   3   obl   _   _
6   vuoden   vuosi   NOUN   N   Case=Gen|Number=Sing   8   nmod:poss   _   _
7   2017   2017   NUM   Num   NumType=Card   6   nummod   _   _
8   alussa   alku   NOUN   N   Case=Ine|Derivation=U|Number=Sing   3   obl   _
SpaceAfter=No
9   .   .   PUNCT   Punct   _   3   punct   _   SpacesAfter=\n



        
```

    </div>
(Caption: Example of omorfi’s outputs and the shared-task equivalents
converted.<a id="listing:io-mangling">(¶ listing:io-mangling)</a>)
<!-- end figure -->


Some statistics of the rule-based dictionaries can be seen in the
table [(see: table:dic-sizes)](#table:dic-sizes).


**Table:**
<div style='text-align: center'>


| Dictionary  |  <!-- bf -->Words  |  <!-- bf -->Rules|
| ---- | ---- | ---- |
| <!-- bf -->Omorfi  |  445,453  |  58 |
| <!-- bf -->Apertium-fin-deu  |  13,119  |  93 |

(Caption: Size of the dictionaries in rule-based systems.
<a id="table:dic-sizes">(¶ table:dic-sizes)</a>)
</div>
<!-- end table -->

The *Turku neural parsing pipeline* (refered from now on to as
TNPP) (footnote: <https://turkunlp.github.io/Turku-neural-parser-pipeline/>)
is a recent, popular parser for a language-independent parsing of the dependency
structures. They ranked highly in the 2018 CONLL shared task. For the
experiments of this paper, I have downloaded the system following the
instructions and have not changed any hyperparametres.  The model used is
`fi\_tdt`.

OpenNMT (footnote: <https://github.com/OpenNMT>) is one of the many popular
neural systems for machine translation. For these experiments I chose it because
it provides usable python bindings and it seemed most robust in our early
experiments.

The training was performed based on the instructions in the OpenNMT
README (footnote: <https://github.com/OpenNMT/OpenNMT-py\#quickstart>) and no
additional hyperparametre-tuning was performed. The training was based on
europarl version 7 \citep{koehn2005europarl}, pre-processed as suggested on
their website (footnote: <https://statmt.org/europarl/>). The resulting
corpus is summarised in Table [(see: table:corpora)](#table:corpora).


**Table:**
<div style='text-align: center'>


| Corpus  |  <!-- bf -->Sentences |
| ---- | ---- |
| <!-- bf -->Europarl train  |  1,768,817 |
| <!-- bf -->dev  |  1620 |
| <!-- bf -->test  |  1620 |

(Caption: Size of the corpora in sentences
<a id="table:corpora">(¶ table:corpora)</a>)
</div>
<!-- end table -->

## Experimental setup
<a id="sec:setup">(¶ sec:setup)</a>

An interesting part of this experiment is the setup, since one of the aspects we
present in this paper is usability testing of the neural vs. traditional methods
for use of an average Computational Uralist, I also want to get a feel of the
*user experience* (UX).

The system setup for all the systems is quite similar, all the free and open
software used in these experiments are hosted by github. After cloning, the
traditional rule-based systems rely on classical command-line installations,
this means that user is expected to install dependencies the best they see and
then run compilation of the data using `configure` and `make`
scripts, and neural systems use `python` equivalents. In terms of
dependencies, all systems are basically well covered with some easy way to
install necessary dependencies with single command, such as `pip` or
`apt-get`. A bit like rule-based systems, the neural systems need to
“compile” i.e. learn neural network binaries from large data, in practice the
experience for the end user is the same, except for the wait time, which is
slightly longer for the neural-based systems.  For Finnish analysers an option
is provided to download readily compiled models, while for translation models
there is no option.  This is equally true for both neural and rule-based models.
To parse or translate I have run the systems with default / suggested settings.

To get an idea of intended mode of use (instant, batch processing over the
weekend) of the systems and steps, I have collected some of our usage times in
the table [(see: table:times)](#table:times). The real bottleneck for our experiments was the
neural machine translation training time, the multi-day training period is
problematic in itself, but it is also fragile enough that minor impurities in
parallel corpus may ruin the whole model which means that on typical use case
user may need to train the model multiple times before reaching to a functional
one.


**Table:**
<div style='text-align: center'>


| Phase, System  |  <!-- bf -->omorfi  |  <!-- bf -->TNPP  |  <!-- bf -->apertium  |  <!-- bf -->OpenNMT |
| ---- | ---- | ---- | ---- | ---- |
| Compiling  |  15 minutes  |  —  |  40 seconds  |   | gt;5 days |
| (Downloading)  |  yes  |  yes  |  no  |  no|
| Parsing / translating  |  5 minutes  |  10 minutes   |  5 seconds  |  30 minutes |
| (Speed)  |  5 sents/s  |  3 sents/s  |  324 sents/s  |  0.9 sents/s |
| Model size  |  25 MiB  |  770 MiB  |  33 MiB  |  7420 MiB |

(Caption: Usage times of rule-based and neural systems, time-units are
indicated in the table. For TNPP I have found no documentation on how to
repeat model building or what time it has taken. Sents/s stands for
average sentences per second. Model sizes gives you the total size of
binaries on disk in binary-prefixed bytes (by `ls -h`).
<a id="table:times">(¶ table:times)</a>)
</div>
<!-- end table -->

To know how much time to create a system takes from scratch it is also useful to
know the amount of data is needed to build it; for rule-based systems this is
the size of dictionary, and rule-sets, for neural system it is the training
data set size. Both of these factors are especially interesting for Uralistic
usage, since the availability of free and open data is rather scarce. The
dictionaries are summarised in Table [(see: table:dic-sizes)](#table:dic-sizes) and the corpora in
Table [(see: table:corpora)](#table:corpora)

For my OpenNMT setup I have created an autotools-based model builder / test
runner, that is available in github for repeatability
purposes (footnote: <https://github.com/flammie/autostuff-moses-smt/>).

## Evaluation
<a id="sec:evaluation">(¶ sec:evaluation)</a>

I present an evaluation of the systems using the standard metrics from the
shared tasks.

For morphological generation, the shared task was evaluated by measuring average
precisions over all languages, for this experiment I compare the results for
Finnish on 1-best predictions only, as I am interested in specific comparison
relevant for a single Uralic language. The results are summarized in
table [(see: table:eval-sigmorphon)](#table:eval-sigmorphon).


**Table:**
<div style='text-align: center'>


| Test set  |  <!-- bf -->Baseline  |  <!-- bf -->Winning system  |  <!-- bf -->Omorfi |
| ---- | ---- | ---- | ---- |
| Task 1  |  64.45  |  97.30  |  93.92 |
| Task 2  |  59.59  |  97.40  |  93.20 |
| Task 3  |  56.95  |  96.56  |  92.18 |

(Caption: 1-Best precisions for SIGMORPHON shared task 2016 in Finnish,
the winning Neural system and omorfi scores.
<a id="table:eval-sigmorphon">(¶ table:eval-sigmorphon)</a>)
</div>
<!-- end table -->

For morphosyntactic analysis the standard evaluations would be based on
attachment scores, however, the rule-based system only creates partial
dependency graphs with potentially ambiguous roots; this does not work with
the official evaluation scripts, so I provide instead a raw 1-best precision
result for the specific fields in the CONLL-U format. The results
are shown in table [(see: table:eval-ud)](#table:eval-ud); The *lemma* row corresponds
3rd CONLL-U column, *UPOS* 4th, *Ufeats* 6th, *XPOS* 5th,
*Dephead* 7th, and *Deplabel* 8th. The match is made on strict
equality on the string comparison of the whole content, i.e. no re-arranging or
approximate matching is performed.


**Table:**
<div style='text-align: center'>


| Column  |  <!-- bf -->Turku Neural parsing pipeline  |  <!-- bf -->Omorfi |
| ---- | ---- | ---- |
| <!-- bf -->Lemma  |  95.54  |  82.63 |
| <!-- bf -->UPOS  |  96.91  |  83.88 |
| <!-- bf -->Ufeats  |  94.61  |  73.95|
| <!-- bf -->XPOS  |  97.89  |  89.58 |
| <!-- bf -->Dephead  |  90.89  |  33.13 |
| <!-- bf -->Deplabel  |  92.61  |  49.01 |

(Caption: 1-best precisions of Turku neural parsing system and
omorfi. The numbers were measured with our script since the official
test script does not handle partial dependency graphs or multiple roots.
<a id="table:eval-ud">(¶ table:eval-ud)</a>)
</div>
<!-- end table -->

For machine translation the standard shared task evaluation method is to
use well-known metrics that compare translations to reference, specifically
BLEU\@. In table [(see: table:eval-wmt)](#table:eval-wmt) I measure the BLEU scores for europarl
translations.


**Table:**
<div style='text-align: center'>


| Language pair  |  <!-- bf -->OpenNMT  |  <!-- bf -->Apertium |
| ---- | ---- | ---- |
| <!-- bf -->German to Finnish  |  7.09  |  0.6 |
| <!-- bf -->Finnish to German  |  7.12  |  0.3  |

(Caption: Automatic translation evaluations, metrics from WMT shared
tasks 2018 and corpora from europarl evaluation section. BLEU scores have
been measured with the tool `mteval-14.perl`.
<a id="table:eval-wmt">(¶ table:eval-wmt)</a>)
</div>
<!-- end table -->


## Error Analysis
<a id="sec:errors">(¶ sec:errors)</a>

As a general trend I see that the precision of the neural systems as well as the
BLEU score of the neural machine translation are above of the rule-based
systems. I also wanted to know if there is any systematicity to the errors, that
the different approaches make. Interesting way forward would be to gain some
insight on how the errors for each system could be fixed if at all.  One of the
commonly mentioned advantages of a rule-based system is that it is predictable
and easy to fix or extend; whether a missing form in generation or analysis is
caused by a missing word in lexicon, a missing word-form in paradigm or ordering
of the alternative forms, the solution is easy to see.  With a neural system the
possibilities are limited to adding more data or modifying hyperparametres.

When looking at the errors in the morphological regeneration test for rule-based
system, I can see several categories emerge: *True OOV* for lexemes
missing from the database (e.g. *ovovivivipaarisuus*), *Wrong
paradigm* for wordforms that are generated but with some errors, such as wrong
vowel harmony or consonant gradation (e.g. *manuskripteiltä* pro
*manuskripteilta* (from manuscripts)) and *Real allomorph /
homograph* for cases where the correct form is recalled but not at best-1 due to
ambiguous lexeme or free allomorphy (for example, I generate
*köykistämäisillänsä* pro *köykistämäisillään* (about to defeat),
but both are equally acceptable).  In the leftover category I found among
others, actual bugs in the generation functionality. For example, I was unable
to generate the forms of *aliluutnantti* (sub-lieutenant) since the
generation function failed to take into account extra semantic tags it
contains. (footnote: a bug has been since fixed but I include the original error
analysis in the article for an interesting reference) I sampled a total of 65
errors and the results can be seen in the table [(see: table:morph-gen-errors)](#table:morph-gen-errors).


**Table:**
<div style='text-align: center'>


| Type  |  <!-- bf -->Count  |  <!-- bf -->Percentage |
| ---- | ---- | ---- |
| OOVs  |  23  |  36 % |
| Wrong paradigm  |  20  |  31 % |
| Allomorphs  |  9  |  15 % |
| Others  |  13  |  20 % |
| <!-- bf -->Total  |  65  |  100% |

(Caption: Rule-based morphology generation errors classified.
<a id="table:morph-gen-errors">(¶ table:morph-gen-errors)</a>.)
</div>
<!-- end table -->

In the dependency parsing task one of the most common errors in the rule-based
system seems to be the `Person=0` feature with 766 occurrences in the
test set, as it is systematically ambiguous with `Person=3` for all
singulars, it is probably a true ambiguity in that there are not many context
clues to disambiguate it. Another systematic source of errors seems to be the
systematic ambiguity between auxiliary and common verbs, which also shows up in
the parsing of copula structures and in the morphological features. Similarly, a
common problem of rule-based systems in parsing tasks is the etymological
systematic ambiguity created by derivation and lexicalisation, that affects
participle above anything, but also less productive features. It would appear
that OOV’s do not contribute here greatly to the error mass, despite consisting
total of 460 appearances the baseline guess of singular nominative nominal for
the OOV’s is surprisingly often sufficient.

Looking at both rule-based and neural systems for MT, it is easy to
tell that for example the OOV’s constitute a large part of errors, and
exist in most sentences. Judging the actual translation quality by
sampling the sentences also reveals a quality that is overall not sufficient
for computer aided translation or gisting, to the extent that I believe
further analysis may not be fruitful without further development of the
underlying models first.

## Discussion
<a id="sec:discussion">(¶ sec:discussion)</a>

One of the goals in this experiment was to find out how usable the neural and
traditional models are for a computational linguist who might want to pick a
state-of-the-art parser off-the-shelf and use it for text analysis or
translation related tasks. Based on my initial impression, I would probably
recommend making use of the neural parsers for languages where enough training
data is available, and aiming to make training data where it is not. However,
for a low resource language, it might often be easier to create a sufficiently
large dictionary with rule-based model than to curate realistic corpus and
annotate it, and given that the results of a rule-based system are not such far
from the state-of-the-art in neural systems for the given metrics, they should
be well sufficient for parsing. On top of that, the resources created with a
rule-based system are a part of necessary NLP system for language survival
(writer’s tools, electronic dictionaries) that neural systems do not offer it
does not make sense to put all eggs in one neural network.


One thing that has been left out of the experiment is what is required for
developing a new system: dictionaries and grammars for rule-based systems,
treebanks or parallel texts for the neural systems. These are available at the
moment for the main Uralic languages: Finnish, Hungarian and Estonian, and to
smaller extent also for Northern Sámi, Erzya. The question then remains, is it
easier for a minority Uralic language to develop a treebank and a parallel
corpus, or dictionaries and grammar, or both.

One noteworthy point to the method of developing resources, as well as to our
evaluation, is, that the original Turku dependency treebank was in fact
developed based on the analyses provided by an old version of
omorfi [(cites: haverinen2014building)](#haverinen2014building), (footnote: we thank the anonymous reviewer
for bringing point up) and that was used as a basis for building the
UD-Finnish-TDT treebank, that is used as a model for the TNPP analyser. So a
traditional way to build resources for neural parsers still requires an existing
high-quality rule-based parser as well as a lot of native human annotation work
on the one hand, on the other hand, the combination of rule-based parses and
human annotation does result in a parser that is more precise at predicting in
basic setup.

One thing that might be a common expectation is, is that a rule-based systems
that have been developed for a long time, should score very highly in basic
tasks like morphological generation and parsing, since apart from real OOV’s and
bugs, correctly made morphology should virtually be able to generate 100 % of
the word-forms in its dictionary. For the precision of 1-best analyses however,
there can be small portion of word-forms that either exhibit unexpected (in
terms that writer of rule-based parser had expected form to be ungrammatical)
or free variation. For recall, which is typically the first goal for rule-based
analyser, the value is nearer to the virtual 100 % \citep{omorfi}.

One surprising thing I found out, that when testing the machine translations on
a non-English pair, the out-of-the-box results for both approaches are very
modest, suggesting that more work is needed to for a usable MT as a tool for
Uralist than just picking off-the-shelf product at the moment. While our test
was still based on non-Uralic language partly due to resource and time
constraints, I believe the results will still give a good indication of the
current state-of-the-art. Notably, it is not unlikely for a research group in
Uralistics to need machine translations of German or for example Russian as
well.

So far, I have only used the precision and BLEU measures to evaluate the
systems, it is likely that different metrics would show more favourable
results for a rule-based systems that typically maximise recall or coverage
first.

One of the surprising finds that I had when fitting the rule-based systems to
non-rule-based shared tasks is, is that I could repurpose the task as
a new automatic continuous integration test set for the lexical database, and
the tests have already proved useful for recognition several types of easily
fixable errors in the database. I note that, in the rule-based system fixing
the OOV-type errors and the paradigm type errors is typically a trivial fix
of one line of code taking less than a minute, however, improving the
allomorph selection or homograph disambiguation is an open research question.

For future work I will study both the neural and rule-based systems further
with hopefully intra-Uralic pairing as well, to find if it’s plausible for
actual use.

## Conclusion
<a id="sec:conclusion">(¶ sec:conclusion)</a>

I performed some experiments to find out what is the current state-of-the-art
status between neural and rule-based methods for Finnish, I have found out that
the neural methods perform admirably for all parsing approaches for the given
test sets that they were designed for, but rule-based methods are also still
within acceptable distance. For non-parsing task such as machine translation in
Uralic languages the methods are probably not yet sufficient to be efficiently
used as a tool for research, but further research and development is needed.


<!-- if cameraready -->
## Acknowledgments

The author was employed by CLARIN-D during the writing of the article.

<!-- fi -->

<!-- bib style: acl_natbib -->
# References

* <a id="haverinen2014building">**haverinen2014building**</a>:
    * author: Haverinen, Katri and Nyblom, Jenna and Viljanen, Timo and
    * journal: Language Resources and Evaluation
    * number: 3
    * pages: 493–531
    * publisher: Springer
    * title: Building the essential resources for Finnish: the Turku Depe...
    * volume: 48
    * year: 2014


<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

