





\lstset{
literate=         {á}{{\’a}}1
}

<!-- new command \samit --> 
<!-- new command BibTeX -->

# Building an Extremely Low Resource Language to High Resource Language Machine Translation System from Scratch

**Authors:** Flammie A Pirinen

UiT Norgga árktalaš universitehta

Tromsø, Norway

`firstname.lastname@uit.no` 
and


Linda Wiechetek

UiT Norgga árktalaš universitehta

Tromsø, Norway

`firstname.lastname@uit.no`
**Date:** 

<!-- begin document -->
<!-- make title -->

**Abstract:**
Building a machine translation system for an extremely low-resource language
is a problem in contemporary computational linguistics.  In this article, we
show how to use existing morpho-syntactic analysers and a modern rule-based
machine translation system to rapidly build a baseline system for a language
pair where a neural model approach is not feasible due to the total lack of
high-quality parallel corpora.  Our experiment produces a freely available
open-source North Sámi to German machine translator, which provides us
useful insights into rule-based machine translation of unrelated languages
with varying levels of morphological complexity. As German is a language
taught in Scandinavian schools this MT system would be of immediate
relevance for Sámi school children learning German. In addition, there is a
strong Finno-Ugric tradition in the German linguistics space that has in the
past produced important publications on the Sámi language, so the system is
immediately useful for researchers and enthusiasts as well as language
users.
<!-- end abstract -->




## Introduction

### Motivation

Machine translation is an important tool for language users.  The most common
contemporary method for implementing machine translation is to curate
professionally translated texts and use machine learning methodology to learn
the translations.  This presupposes the availability of perhaps several millions
of professionally translated sentences, which is unfeasible for under-resourced
marginalised languages, where very little parallel corpora or even monolingual
corpora are available.  To put the low-resourcedness of North Sámi in context,
the largest available monolingual corpus [(cites: sikor_06.11.2018)](#sikor_06.11.2018) is only 38
million tokens, and for the bilingual corpora at most 10,000s of aligned
phrases, most of which are from Linux program GUI
translations (footnote: <https://opus.nlpl.eu/KDE4.php>).  Given the
circumstances, we do not find it reasonable to try to train a neural network for
this task.  The sensible solution is to use linguistic knowledge to build a
rule-based machine translation system.  What we are presenting in this article
is a machine translation from North Sámi to German, a language pair that to our
knowledge has not brought forth any system before, and that does not have enough
resources for a neural machine translation system.  Furthermore, our
contribution consists in exploring a newly created module in a rule-based
machine translation system, and we are looking at workflows for the rapid
development of a baseline machine translator.

The rule-based system took us only some 100 hours to write and is the work of
one programmer/linguist/advanced learner of German and native speaker of
Finnish, an expert on Apertium—and one computational linguist, native speaker
of German with high proficiency in North Sámi (but not a native speaker of it).
The system described here is a work-in-progress, yet it is a proof-of-concept
that rapid building of a machine translation system is plausible without big
data corpus resources.  Our motivation to build this system is two-fold: we are
building a tool for users, as well as surveying the use of newly introduced
techniques in a language pair that is not within the same language family and
not English.  This is also the *novel research* in our experiment: we
provide further insights on the usage of the *new additions* to
methodologies in a recently updated machine translation system in a
typologically varied setting, that has not been tried before to our knowledge.

In the context of machine translation as a tool for supporting under-resourced
language use, one must practice a certain level of carefulness in order to not
cause more damage than good.  For example, creating a system for generating
large amounts of translations from the majority language to minority languages,
for example, might sound like a lucrative offering to generate big data, but may
result in creating larger bodies of automatically translated texts that overtake
what there exists of naturally written texts which in the long run can be rather
problematic.  On the other hand, creating a system that translates well enough
for *language understanding* (gisting) for majority language users will
enable the minority language communities to wider use of their language in
digital contexts.  We stick to the ethics of not flooding the web with
low-quality North Sámi text by building the system the other way around (German
- North Sámi). Clean data is still of great value, and we do not want to put
that in danger.

The machine translation system we created is freely available and open source in
Apertium’s GitHub
repository (footnote: <https://github.com/apertium/apertium-sme-deu>). The
dependent North Sámi language model we developed earlier is also available at
our github (footnote: <https://github.com/giellalt/lang-sme>) and German model
from Apertium’s
collection (footnote: <https://github.com/apertium/apertium-deu>). (footnote: For
reproducibility purposes, the tag `konvens2022` is available in the
mentioned repos)

### Languages

North Sámi is a Finno-Ugric language belonging to the Uralic languages spoken in
Norway, Sweden, and Finland by approximately 25,700
speakers [(cites: Ethnologue2022)](#Ethnologue2022). It is a synthetic language, where the open
*parts-of-speech* (PoS)—e.g. nouns, adjectives—inflect for case,
person, number, and more. The grammatical categories are expressed by a
combination of suffixes and stem-internal processes affecting root vowels and
consonants alike, making it perhaps the most fusional of all Uralic languages.
In addition to compounding, inflection and derivation are common morphological
processes in North Sámi.  German, on the other hand, is an Indo-European
language.  In contrast to all previous work, there is neither language family
similarity, nor geographical proximity or political relation. The latter would
be the case for Sámi—Norwegian where despite language typological
unrelatedness there are (even syntactic) loans due to coexistence and
interaction of the languages.

As German was the previous century’s language of science, a lot of scientific
literature on the Sámi language was published in German. Newer publications
include the North Sámi—German, German—North Sámi
dictionary [(cites: Sammallahti2006sami)](#Sammallahti2006sami) of high quality (containing valencies,
idiomatic phrases, examples of use).  German has also been one of the languages
that school children get to pick as a foreign language at school.  For both
these reasons, it makes sense to have MT systems between these two languages.

Morphologically, the languages have similar features: both are morphologically
richer and suffixing, and mark case for nominals and some tense, aspect, and
mood as well as person for verbs, however, North Sámi also marks other
grammatical features such as possession and aktionsart in morphology. Both
languages also have the productive compounding of nominals.  The syntactic
differences are notable, while the neutral word order for both is SVO, there are
a number of mismatching features in the syntax: pro-drop for 1. and 2. person in
Sámi, separable verbs in German, adverbial positioning, word order in
sub-clauses, question clauses or after adverbial extensions, etc.

## Background

Previous MT systems involving North Sámi are North Sámi—Lule
Sámi [(cites: tyers2009developing,Wiechetek2010shooting)](#tyers2009developing,Wiechetek2010shooting), North
Sámi—Norwegian [(cites: trosterud2012evaluating)](#trosterud2012evaluating), North Sámi—South Sámi
[(cites: Antonsen2017northsaami)](#Antonsen2017northsaami), North
Sámi—Finnish [(cites: johnson2017north)](#johnson2017north).  The systems were all based on
previous versions of Apertium, the state-of-the-art in rule-based machine
translation.

There is an Apertium-based system for translating North Sámi to
Norwegian, (footnote: <https://gtweb.uit.no/jorgal>) that has been in end-user
use.  As German and Norwegian (Bokmål) are related languages, we expect to be
able to use them as a reference when implementing our system.


We chose to use Apertium [(cites: khanna2021recent)](#khanna2021recent) as it is popular in the
context of under-resourced languages.  The system is based, roughly speaking, on
doing a morpho-syntactic analysis of the source text, transferring the analysis
to the target language morpho-syntactic description, and generating it into the
target text.  There is a diagrammatic presentation of the system pipeline in
Figure [(see: fig:my_label)](#fig:my_label).  This means that the system consists of morphological
analyser-generators of target and source languages, based on finite-state
morphology [(cites: Beesley2003finite)](#Beesley2003finite), and a constraint
grammar [(cites: karlsson1990constraint,Didriksen2016constraint)](#karlsson1990constraint,Didriksen2016constraint) for syntactic and
semantic analysis suitable for transferring the source language structures to
target language structures.

See examples [(see: example-sme)](#example-sme) and [(see: example-deu)](#example-deu) for a concrete example.  In
our experiment, we had pre-existing morphological analysers for North
Sámi (footnote: <https://github.com/giellalt/lang-sme>) and
German (footnote: <https://github.com/apertium/apertium-deu>), and we have
written a bilingual translation dictionary as well as the grammatical rules.

**Linguistic example group:**

Boadát go dál?<a id="example-sme">(¶ example-sme)</a>

come<span style='font-variant: small-caps'>.v.2sg</span> <span style='font-variant: small-caps'>qst</span> now<span style='font-variant: small-caps'>.adv</span>?

‘Are you coming now’

**Linguistic example group:**

Kommst du jetzt?<a id="example-deu">(¶ example-deu)</a>

come<span style='font-variant: small-caps'>.v.2sg</span> you<span style='font-variant: small-caps'>.prn.2sg</span> now<span style='font-variant: small-caps'>.adv</span>?

‘Are you coming now?’

From the example we see that there is some level of syntactic mapping to be done
between the languages: North Sámi is generally pro-drop i.e. missing the subject
pronoun morphologically encoded in the verb where German requires this.
Furthermore, North Sámi indicates question with a question particle that is not
easily glossed in English or German—perhaps an approximate gloss could be ‘is
it such that’—in German, the word order change indicates the question-format
of the sentence.

We base our system on the tools developed within the *GiellaLT*
infrastructure for North Sámi and tools developed within Apertium community for
German, these include state-of-the-art FST-based morphological analyzers, with
Constraint Grammar syntactic analysis and disambiguation. We have done a few
slight adjustments to both monolingual systems, but our main work is in the
bilingual part. In Figure [(see: fig:my_label)](#fig:my_label), the part we work on concerns the
part under *transfer*, specifically we have used the *recursive
structural transfer* path in this experiment, which is a newly built part of
Apertium in 2021 [(cites: khanna2021recent)](#khanna2021recent).


**Figure:**[htb]
<!-- centering -->
![pipeline_box.pdf](pipeline_box.pdf)
(Caption: Apertium pipeline structure from [(cites: khanna2021recent)](#khanna2021recent)
    <a id="fig:my_label">(¶ fig:my_label)</a>)
<!-- end figure* -->

To give an impression of concrete resources and rules, we show in
Figure [(see: fig:code)](#fig:code) (footnote: <https://github.com/apertium/apertium-sme-deu/apertium-sme-deu.sme-deu.trx>)
what the dictionaries and the rules look like:


**Figure:**
<!-- small -->
**Bilingual dictionary**
   
```
[numbers=left]
    &lt;e&gt;&lt;p&gt;&lt;l&gt;áddet&lt;/l&gt;&lt;r&gt;verstehen&lt;/r&gt;&lt;/p&gt;&lt;par n="vblex"/&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;addit&lt;/l&gt;&lt;r&gt;geben&lt;/r&gt;&lt;/p&gt;&lt;par n="vblex"/&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;addit&lt;/l&gt;&lt;r&gt;liefern&lt;/r&gt;&lt;/p&gt;&lt;par n="vblex"/&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;álbmut&lt;/l&gt;&lt;r&gt;schaufeln&lt;/r&gt;&lt;/p&gt;&lt;par n="vblex"/&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;álggahit&lt;/l&gt;&lt;r&gt;anfangen&lt;/r&gt;&lt;/p&gt;&lt;par n="vblex"/&gt;&lt;/e&gt;
   
```

**Syntactic rules**
   
```
[numbers=left]
S -&gt; VP NP { 1 _
    *(maybe_adp)[case=2.case]
    *(maybe_art)[number=2.number,case=2.case,gender=2.gender,def=ind]
2 } ;
V -&gt;                number = (if (1.number = du) pl else 1.number)] } ;
   
```

(Caption: Bilingual dictionary format and syntactic rule format
 <a id="fig:code">(¶ fig:code)</a>)
<!-- end figure* -->



## Development

We predominantly used pre-existing morphological analysers and morpho-syntactic
disambiguation for the North Sámi morphological analysis and disambiguation and
German morphological generation (and vice versa, but this direction was not the
main objective of this article). Our contribution in terms of developed
resources is a bilingual lexicon i.e. North Sámi to German translation
dictionary, and the development of bilingual grammatical rules that determine
for example word order changes and introduction of words that don’t exist in the
source language, such as articles.


The bilingual lexicon development was done by hand by a linguist, in the
following three steps:


1. Translating words of initial reference bilingual
corpus (footnote: <https://github.com/apertium/apertium-sme-deu/blob/master/sme-deu-corpus.txt>)
1. Translating high-frequency words (from
SIKOR) (footnote: <https://gtsvn.uit.no/langtech/trunk/words/lists/sme/sme_lemma.freq>)
1. Translating words from a random sample of large monolingual corpus
        (from SIKOR)


The final result has been verified by a linguist with near-native language
skills. The first two steps ensure high coverage in general, whereas the third
step is necessary to have high enough coverage in the genres of evaluation
corpus for the human evaluation to even be possible.



The grammatical transfer was developed based on the reference bilingual corpus
first.  We ran the translation system through our reference corpus and located
easy-to-fix syntactic differences, such as missing articles and pronouns, and
local word order changes, and wrote the rules for those.  We also needed to
write transfer rules to account for purely morphological mismatches: for
example, German only has grammatical cases: nominative, genitive, accusative,
and dative, whereas North Sámi also has local cases and other cases that
translate into prepositional phrases in German. The prepositions for each case
do not translate one-to-one. Typically, one case will translate into several
prepositions depending on the semantic/valency context.

The resulting lexicon and rules are summarised in Table [(see: table:data)](#table:data).


**Table:**[htb]
<!-- centering -->


| <!-- bf -->Data set  |  <!-- bf -->Data size  |  <!-- bf -->Note|
| ---- | ---- | ---- |
| Translation dictionary  |  4,340 LU pairs  |  newly built |
| Translation grammar  |  17 rules  |  newly built |
| German dictionary  |  100,390 LUs  |  extended |
| North Sámi dictionary  |  154,557 LUs  |   extended |
| Development corpus  |  1469 sentences  |  manually translated |
| SIKOR  |  38,94 Mtokens  |  monolingual corpus |
| Test set  |  7083 tokens  |  random sample|

(Caption: <span class='math'>LU</span> is a lexical unit e.g. an entry in the dictionaries, <span class='math'>token</span>
is a token in a running text e.g. word-form or punctuation, <span class='math'>Mtokens</span> is
millions of tokens, and <span class='math'>sentences</span> in the text are based on our sentence
boundary finding algorithm.  <a id="table:data">(¶ table:data)</a>)
<!-- end table* -->


## Evaluation

As a corpus for evaluation of the translation quality, we randomly picked 300
paragraphs from *SIKOR*. This corpus is summarised in
Table [(see: table:data)](#table:data).  We measured the naïve coverage of the monolingual
analyser as well as our bilingual dictionary of the whole corpus to get an idea
of how far we are in the process of building a translation dictionary suitable
for any running texts.


**Table:**[htb]
<!-- centering -->


| <!-- bf -->Corpus  |  <!-- bf -->Naïve coverage |
| ---- | ---- |
| Development corpus  |  99.8 % |
| Test set  |  88.2 % |
| SIKOR  |  84.6 % |

<!-- vspace 1em --> 



| <!-- bf -->Metric  |  <!-- bf -->Test Corpus |
| ---- | ---- |
| Post-Edit WER  |  76 % |

(Caption: Evaluation of our North Sámi - German MT system)
    <a id="tab:my_label">(¶ tab:my_label)</a>
<!-- end table -->

### Word Error Rate on Post-Edited text

We did a *Word Error Rate* (WER) test on our randomly selected corpus
that was post-edited by a native speaker of German.  Word error rate is a simple
measure that calculates the proportion of the wrongly translated words, in this
case when comparing the machine translation output to the translation that a
human translator has post-edited.  For example, if one word in a 10-word
sentence is mistranslated, the word-error rate is 10 % and an exact match is
0 %. Notably, if the translation contains too many words, the word error rate
can exceed 100 %.  It is noteworthy that WER is also a rather naïve metric, for
example, a wrong article or case is given the same weight as a completely wrong
word. However, for understandability the latter is a much bigger obstacle than
the wrong article.  For the WER test, we used the `apertium-eval` tool
available on their
github (footnote: <https://github.com/apertium/apertium-eval-translator>).
The results of this evaluation are shown in Table [(see: tab:my_label)](#tab:my_label).


## Discussion and error analysis

One of the prevailing problems at this point of development is dictionary
coverage.  Creating the dictionary is one of the most time-consuming parts of
the rule-based machine translation work. However, the resulting human-curated
translation dictionary is a very valuable resource and therefore worth the
effort. Once created, a translation dictionary can be included in any other
future tool.  Many of the errors we saw in the evaluation were due to low
frequency, rather domain-specific words, such as *attorney general* or
*vice candidate*, which had not been added to the bilingual dictionary
yet.

Some of the machine-translated sentences are intelligible despite  grammatical
errors. The translation of ex. [(see: original)](#original) in ex. [(see: output)](#output) requires
lexical edits: *saamisch<span class='math'>\rightarrow</span>Saamischsprachige*, *des
Saamen<span class='math'>\rightarrow</span>saamische*, *um<span class='math'>\rightarrow</span>über*,
*Lebensunterhalte<span class='math'>\rightarrow</span>Gewerbe*, most of which are at least
semantically related as can be seen in the correct translation of the sentence
in ex. [(see: original)](#original). In addition to the lexical edits, there are a number of
word order issues, e.g.  *treffen andere ... <span class='math'>\rightarrow</span>andere
... treffen*.  And also, e.g.*aufhören <span class='math'>\rightarrow</span> hören ...
auf*.


**Linguistic examples:**

So können die Schüler treffen andere *saamisch, und  lernen bißchen traditioneller *um *Lebensunterhalte *des Saamen.<a id="output">(¶ output)</a>



**Linguistic example group:**

Nu besset oahppit deaivvadit eará sámegielagiiguin, ja oahppat veaháš árbevirolaš sámi ealáhusaid birra.<a id="original">(¶ original)</a>

so können<span style='font-variant: small-caps'>.3pl</span> Schüler<span style='font-variant: small-caps'>.pl</span> treffen andere Saamischsprachig<span style='font-variant: small-caps'>.kom.pl</span>, und lernen etwas traditionell saamisch Gewerbe<span style='font-variant: small-caps'>.akk.pl</span> über;um

‘So können die Schüler andere Saamischsprachige treffen, und ein bißchen über die traditionellen saamischen Gewerbe lernen.’



One of the interesting findings in this experiment is that, since the source and
target languages are not related to each other (footnote: Within Europe, the
Finno-Ugric and Indo-European are as far apart as they can get.) and the
syntactic differences are notable, one focus of our work has been the tasks of
word reordering and generation, which have typically been ignored in rule-based
approaches to machine translation earlier.  We found that the new recursive
syntax-based approach in Apertium together with the high-quality Constraint
Grammar-based syntactic analysis in the source language allows us to resolve
reordering in an efficient way.


Looking at the edits we made in the post-edit, some errors are not as critical
as the raw WER might suggest, for example, problems with the grammatical forms
of the articles or compound splitting as well as separable verb processing may
falsely increase the error rate more than it affects the readability.  In the
future, we will continue adding words as well as improve the description.

In a qualitative evaluation we found a lot of noise in the source text that
affected the quality of our output.  Noise in source texts is a much bigger
problem in extremely low-resource languages like North Sámi and is due to newer
or lacking language norms, lesser literacy and lesser use of the language in
writing. [(cites: wiechetek2022unmasking)](#wiechetek2022unmasking) We found the following types of noise:
formatting errors and syllable splitting (potentially caused by corpus
collection methods), spelling errors like accent errors and compound
misspellings, grammatically doubtful sentences (potentially due to translations)
and other grammatical errors like case errors.




## Conclusion

We have developed the first North Sámi - German machine translation system in a
short amount of time (100h) without any bilingual big data, based on the
well-known Apertium system and the rule-based morpho-syntactic tools for North
Sámi that are available in the  *GiellaLT* infrastructure.  The system is
able to handle a number of syntactic transfer issues such as the generation of
articles and longer distance reordering, such as the verb placement in a
subordinate clause.  We have evaluated our system and managed to develop a
state-of-the-art system that is useful in terms of gisting, but still needs
further development to serve as a post-editing tool.  Our research contribution
is not only an MT tool for a new language pair of completely unrelated languages
but also, because of the unrelatedness, practical solutions to structural
transfer problems that have been either ignored or marginalised in the past.

## Acknowledgments
We thank Daniel Swanson from Apertium for his help and answers about the new system and Lene Antonsen for her help with the North Sámi Apertium usage.

# References

* <a id="sikor_06.11.2018">**sikor_06.11.2018**</a>:
    * author: SIKOR
    * title: SIKOR UiT Norgga árktalaš universitehta ja Norgga Sámedikki ...
    * howpublished: 
url{http://gtweb.uit.no/korp}
    * note: Accessed: 2024-10-01
    * year: 2021
* <a id="Ethnologue2022">**Ethnologue2022**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="Sammallahti2006sami">**Sammallahti2006sami**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="tyers2009developing">**tyers2009developing**</a>:
    * author: Francis M. Tyers and L. Wiechetek and Trond Trosterud
    * booktitle: Proceedings of the 13th Annual Conference of the European
    * pages: 120–128
    * title: Developing prototypes for machine translation between two {S...
    * year: 2009
* <a id="Wiechetek2010shooting">**Wiechetek2010shooting**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="trosterud2012evaluating">**trosterud2012evaluating**</a>:
    * author: Trond Trosterud and Kevin Brubeck Unhammer
    * booktitle: Third International Workshop on Free/Open-Source Rule-Based
    * pages: 13–25
    * title: Evaluating North Sámi to Norwegian assimilation RBMT
    * year: 2012
* <a id="Antonsen2017northsaami">**Antonsen2017northsaami**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="johnson2017north">**johnson2017north**</a>:
    * author: Johnson, Ryan and Pirinen, Tommi A and Puolakainen, Tiina an...
    * booktitle: Proceedings of the 21st Nordic Conference on Computational
    * number: 131
    * organization: Linköping University Electronic Press
    * pages: 115–122
    * title: North-Sámi to Finnish rule-based machine translation system
    * year: 2017
* <a id="khanna2021recent">**khanna2021recent**</a>:
    * author: Khanna, Tanmai and Washington, Jonathan North and Tyers, Fra...
    * doi: 10.1007/s10590-021-09260-6
    * journal: Machine Translation
    * month: 10
    * publisher: Springer
    * title: Recent advances in Apertium, a free/open-source rule-based
    * year: 2021
* <a id="Beesley2003finite">**Beesley2003finite**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="karlsson1990constraint">**karlsson1990constraint**</a>:
    * address: Helsinki
    * author: Fred Karlsson
    * booktitle: Proceedings of the 13th International Conference of
    * editor: H. Karlgren
    * pages: 168–173
    * title: Constraint Grammar as a Framework for Parsing Unrestricted T...
    * volume: 3
    * year: 1990
* <a id="Didriksen2016constraint">**Didriksen2016constraint**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="wiechetek2022unmasking">**wiechetek2022unmasking**</a>:
    * address: Marseille, France
    * author: Wiechetek, Linda  and  Hiovain-Asikainen, Katri  and  Mikkel...
    * booktitle: Proceedings of the Language Resources and Evaluation
    * month: June
    * pages: 1167–1177
    * publisher: European Language Resources Association
    * title: Unmasking the Myth of Effortless Big Data - Making an Open S...
    * url: https://aclanthology.org/2022.lrec-1.125
    * year: 2022

<!-- bib style: unsrt -->

<!-- end document -->



* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

