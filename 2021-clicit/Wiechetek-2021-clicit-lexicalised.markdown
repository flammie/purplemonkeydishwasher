












<!-- new command \samit --> 



# *Suoidne-varra-bleahkka-mála-bihkka-senet-dielku* ‘hay-blood-ink-paint-tar-mustard-stain’ – 
 Should compounds be lexicalized in NLP? ¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: Creative Commons CC-BY-SA by conference, the official version published in CEUR-WS at <http://ceur-ws.org/Vol-2769/paper_49.pdf>)</span>


**Authors:** Linda Wiechetek   Chiara Argese   Tommi A Pirinen   Trond Trosterud

{<!-- small --> linda.wiechetek@uit.no   {<!-- small --> chiara.argese@uit.no}   {<!-- small --> tommi.pirinen@uit.no}   {<!-- small --> trond.trosterud@uit.no}



<!-- vspace 2ex -->
Divvun \& Giellatekno,
UiT Norgga árktalaš universitehta 
}


**Date:** 

<!-- begin document -->
<!-- make title -->

**Abstract:**
**English.**

<!-- small --> Lexicalizing compounds, in addition to treating them dynamically,
is a key element in giving us
idiomatic translations and detecting compound errors.
We present and evaluate an e-dictionary (*NDS*) and
a grammar checker (*GramDivvun*) for North Sámi. We achieve a coverage of
98% for *NDS*-queries and
of 96% for compound error detection in *GramDivvun*.
<!-- end abstract -->


**Abstract:**
 \textrm{\bf{Italiano.}}

<!-- small --> La lessicalizzazione delle parole composte, in aggiunta a trattarle in maniera dinamica, è un elemento chiave
per ottenere traduzioni idiomatiche e rilevare errori nelle stesse.
Presentiamo e valutiamo un e-dizionario (*NDS*) e un correttore
grammaticale (*GramDivvun*) per il Sami del Nord. Otteniamo una
copertura del 98% per le ricerche in *NDS* e del 96% per il rilevamento di errori nelle parole composte in
*GramDivvun*.

<!-- end abstract -->

## Introduction


In this paper (footnote: Copyright ©️2020 for this paper by its authors. Use permitted under Creative Commons License Attribution 4.0 International (CC BY 4.0).), we discuss the use and necessity of the lexicalization of
compounds – in addition to the dynamic approach to compounding – in two rule-based Natural Language Processing (NLP)
applications, a grammar checker *GramDivvun* and an electronic
dictionary *NDS* (short for *Neahttadigisánit*).
We argue for a dual approach and support this view with an
evaluation of these tools. For comparison, we also look at a third
application, a corpus tool (*Korp*) for the North Sámi corpus
*SIKOR*. SIKOR, the Sámi International KORpus, is the collection of texts in different Sámi languages compiled by UiT The Arctic University of Norway and the Norwegian Sámi Parliament.

In the past, we have mostly focussed on the dynamic approach to morphological analysis. This means that we have a lexicon with lemmata and stems, which in a finite-state manner are combined with inflectional and derivational affixes and other stems and modified when morpho-phonological processes apply.
In this way the linguistic processes inflection, derivation and compounding are modelled in a dynamic way, i.e. by means of concatenation and composition as opposed to listing of all forms.
Lexicalization, i.e. listing compounds or inflected word forms as such, is the alternative approach to the dynamic one.
In addition to these two approaches we also use guessers for certain tasks, i.e. proper name guessing in morpho-syntactic parsing. Our approach is entirely rule-based and open source. Within our 20 year experience with language tools for the Sámi languages and other languages with complex morphology, we have achieved good results and produced reliable tools.

There are a number of approaches to error detection of a few errortypes for morphologically complex - although less complex than North Sámi - languages like Latvian [(cites: Deksne2019)](#Deksne2019) and Russian [(cites: Rozovskaya2019)](#Rozovskaya2019).
The Latvian neural network grammar checker focusses on preposition-postposition confusion, adjective-noun agreement, mood errors in verb forms, number and case in noun forms, definiteness of adjectives and missing commata. All of these error types have a good performance with precisions between 78% and 98.5%.
Judging from their regular expressions to insert artificial errors, most of their error types seem to be fairly local errors that can be resolved based on bigrams.

The Russian system focusses on more advanced error types - case, number agreement, gender agreement, preposition and aspect. However, the results show that the system is still in its initial phase with low precision and recall for most error types (precision is between 22% and 56%, only gender agreement reaches 68%, and recall is significantly lower, between 9% and 36%).
None of these approaches deals with compound error detection.


For neural network approaches, large corpora with error mark-up are necessary, which are not available for North Sámi. The error marked-up corpus contains 120 459 words, and when looking at specific error types – as in this case compound errors – the corpus is even smaller.
The Russian system is based on an error-marked corpus of 200k words (deemed too small by its authors), the Latvian system works with artificial errors, an approach that can be problematic as it does not reflect real text errors.

In compounding, two or several words are combined to form a new
In compounding, two or several words are combined to form a new
word. In Sámi, Finnic and Germanic languages, compounding is a
productive process and new compounds like in \Next can be made on
the fly. (footnote: To avoid confusion with hyphenated compounds, “<span class='math'>|</span>” is used to mark word boundaries in compounds)
In Romance languages, these compounds typically correspond to
prepositional constructions (ital. ‘la federa del cuscino del
divano’). (footnote: Although there are a number of real compounds in
Italian, such as *fruttivendolo*, as well.)


**Linguistic example group:**

soffá<span class='math'>|</span>guoddá<span class='math'>|</span>olggoža ({North Sámi})<a id="sami">(¶ sami)</a>

sofa<span class='math'>|</span>pute<span class='math'>|</span>trekk (Norwegian)

‘sofa pillow cover (English)’


The initial motivation for extensive lexicalization of compounds of
North Sámi goes back to adapting the spellchecker to users’ needs,
i.e. avoiding false alarms in *Ávvir* newspaper’s texts.  
North Sámi is a Uralic language spoken in Norway, Sweden and Finland by
approximately 25 700 speakers [(cites: Ethnologue2018)](#Ethnologue2018). It is a synthetic language,
where the open parts of speech (PoS) – nouns, adjectives, etc. – inflect for
case, person and number. The grammatical categories are expressed by a
combination of suffixes and stem-internal processes affecting root vowels and
consonants alike, making it perhaps the most fusional of all Uralic languages.
In addition to compounding, inflection and derivation are common morphological processes in North Sámi.


North Sámi has seven morpho-syntactic cases, i.e. nominative (Nom.), genitive (Gen.), accusative (Acc.), illative (Ill.), locative (Loc.), comitative (Com.), and essive (Ess.).
Case plays a more central role in Sámi than in preposition-based case languages, since here syntactic functions are identified based on case only.
In addition, nouns can bear possessive suffixes.
Verbs are inflected for person, number (singular, dual, plural), tense (present and past tense) and mood (indicative, conditional, and potential).  Derivational processes (passive, causative, inchoative, diminutive, reflexive, to name only some of them) enhance the combinatory possibilities of each verb.


Table [(see: pos-compounds)](#pos-compounds) illustrates that compounding in North Sámi
is by no means restricted to noun noun combinations, but includes a
number of other *parts-of-speech* (PoS) as well, also as
heads. (footnote: The following abbreviations are used: N=noun, V=verb, A=adjective, Attr=attributive,
Adv=adverb, Pron=pronoun, Pcle=particle, PrfPrc=past participle, Num=numeral, Prop=propernoun.)



**Table:**[h]
<!-- small -->
<div style='text-align: center'>


|p{2.4cm}|p{2.8cm}|}
| | ---- | ---- | <!-- bf -->Type  |  <!-- bf -->Example  |  <!-- bf -->Gloss and translation | | ---- | ---- |
| N N  |  láhka<span class='math'>|</span>rievdadusat  |  law<span class='math'>|</span>change<span style='font-variant: small-caps'>.pl</span> ‘law changes’|
| A.Attr N  |  boahtte<span class='math'>|</span>áigi  |  coming<span class='math'>|</span>time ‘future’|
| Adv N  |  dáppe<span class='math'>|</span>olmmoš  |  here<span class='math'>|</span>person ‘person from here’|
| Pron A  |  iešguđet<span class='math'>|</span>lágan  |  each<span class='math'>|</span>alike ‘different kinds of’|
| Pron N  |  eanet<span class='math'>|</span>lohku  |  more<span class='math'>|</span>number ‘majority’|
| Adv Pcle  |  dušše<span class='math'>|</span>fal  |  only<span class='math'>|</span>really ‘just’ |
| Adv V  |  vuostái<span class='math'>|</span>váldojuvvo  |  against<span class='math'>|</span>take<span style='font-variant: small-caps'>.pass.3sg</span> ‘received’ |
| PrfPrc N  |  mearridan<span class='math'>|</span>fápmu  |  decide<span style='font-variant: small-caps'>.prfprc</span><span class='math'>|</span>power ‘authority’|
| Num Num  |  okta<span class='math'>|</span>nuppe<span class='math'>|</span>lohkái  |  one<span class='math'>|</span>second<span class='math'>|</span>ten<span style='font-variant: small-caps'>.ill</span> ‘eleven’| Num N  |  1978<span class='math'>|</span>-láhka  |  1978<span class='math'>|</span>-law ‘1978 law’| Num A  |  3<span class='math'>|</span>-ivnnat  |  3<span class='math'>|</span>-colored ‘3-colored’|
| Num A  |  golmma<span class='math'>|</span>ivnnat  |  three<span class='math'>|</span>colored ‘three colored’| 

</div>
(Caption: <a id="pos-compounds">(¶ pos-compounds)</a> Compound types according to PoS; ‘<span class='math'>|</span>’ is used to mark word boundaries)
<!-- end table -->


In North Sámi, compounds are formed without a hyphen, except for those involving a proper noun, a digit, or an acronym like *Davvi-Norgii* ‘Northern Norway (Ill.)’,
*3-juvllatsykkel* ‘tricycle’,
and *ILO-álgoálbmotsoahpamuš* ‘ILO-indigenous people agreement’ [(cites: callinravagirji2015[p.46])](#callinravagirji2015). There are a number of multiwords where a space is obligatory (*albma ládje* ‘properly’ and *duollet dálle* ‘sometimes’). Also genitive first compounds have an alternative interpretation when
written apart, which makes error detection more difficult.


## Background

The North Sámi tools described in this article – *NDS*, *Korp* for *SIKOR* and
*GramDivvun* [(cites: Wiechetek2012)](#Wiechetek2012) – all rely on the *GiellaLT*
infrastructure [(cites: Moshagen2013BuildingAO)](#Moshagen2013BuildingAO), a technological framework
for managing lexical data and building it into language technology applications
including e-dictionaries and grammar checkers.  All of them make use of a
morphological analyzer, an *FST* (Finite-State Transducer) described in
Pirinen [(cites: Pirinen2014)](#Pirinen2014), where word formation processes are moduled.
Additionally, *SIKOR* and *GramDivvun* include a Constraint
Grammar-based syntactic analysis. The full modular structure of the latter is
described in Wiechetek [(cites: Wiechetek2019)](#Wiechetek2019).


The computational modeling of the language is done using finite-state
morphology [(cites: Beesley2003)](#Beesley2003). The method of recognizing grammatical
words as well as querying their grammatical information is based on
looking up the words in an FST that contains the morphological
dictionary of the language.  There are two types of compounds in the
language model: the ones that are stored in the lexicon as lexicalized
units and the ones generated dynamically using a compounding model.
Table [(see: table:lexicalised-compounds)](#table:lexicalised-compounds) gives the statistics over the length of lexicalized compounds. (footnote: The table is based on the dictionary size at the time of the writing (September 2020); it is actively  developed daily. Further abbreviations are Adp<span class='math'>=</span>adposition, Conj<span class='math'>=</span>conjunction.)

Lexicalized four-element compounds are quite common in the noun lexicon,
e.g. *davvisámegielterminologiija* ‘North Sámi language
terminology’.
Even six-element compounds (*sáiva\-čáhce\-guolle\-vuostáiváldindilli* ‘fresh water fish receive situation’) can be found.


The different types of North Sámi
compounds in Table [(see: pos-compounds)](#pos-compounds) are not treated equally in the
morphological analyzer. Only the compounds in the first two lines can
be derived dynamically.
All others need to be lexicalized, i.e. listed in the lexicon, to receive a compound analysis. Numeral compounding is not treated dynamically in the FST.
The dynamic compounds are generated from the dictionary by concatenating
word forms (such as a genitive or nominative noun
followed by other noun) and adding a compound tag `+Cmp`. The
main dynamic compounds are (derived and non-derived) noun + noun
pairs. One feature of the underlying technology is that the compounding mechanism is
capable of modeling infinitely long compounds: for example nouns of
any magnitude are compounds and modeled by the finite-state
automaton. Since the compounding mechanism of an FST is very powerful, it
also leads to ambiguity. When we allow arbitrary lexemes to combine
to form compounds, some will overlap other existing lexemes, cf. ex. [(see: regivudna)](#regivudna).

**Linguistic example group:**

Davvi **regiuvdna**<a id="regivudna">(¶ regivudna)</a>
 North region;direction.oven
 ‘The northern region’
Here, *regiuvdna* ‘region’ has a typical spelling error, o&gt;u. The FST analyzes it as a misspelling of *regiovdna* ‘region’, but also as a compound with the elements *regi*, a common wrong form of  *regiija* ‘direction’, and *uvdna* ‘oven’.
While this example has only two possible analyses, twenty or more different analyses are not uncommon.






**Table:**[htb]
 <div style='text-align: center'>


| ---- | ---- | ---- | ---- | ---- | ---- |
| \diagbox[height=7ex,width=8ex]{PoS}{Roots}  |  2  |  3  |  4  |  5  |  6+ | 
| **N**     |  16 603  |  1 048  |  1 665  |  86  |  15 |
| **Num**   |  408     |  1 048  |  42     |  0   |  4 |
| **Prop**  |  11 680  |  3 005  |   115   |  9   |  1 |
| **A**     |  3 854   |  333    |  13     |  0   |  0  |
| **V**     |  478     |  4      |  0      |  0   |  9  |
| **Adv**   |  896     |  109    |  1      |  0   |  0  |
| **Adp**   |  152     |  49     |  0      |  0   |  0  |
| **Conj**  |  3       |  0      |  0      |  0   |  0  |

(Caption: Lexical compounds in the lexicon by the PoS of their
head and the number of their roots<a id="table:lexicalised-compounds">(¶ table:lexicalised-compounds)</a>)
</div>
<!-- end table -->

## Compounds in three NLP applications

We present three applications, an e-dictionary, a corpus tool, and a grammar checker tool.

### An e-dictionary (NDS)<a id="ndssection">(¶ ndssection)</a>

The North Sámi – Norwegian dictionary contains 25 000 lemmata and uses
an FST.
The e-dictionary was first implemented in 2013 with no use of relational databases (all linguistic resources are contained within static files and external command-line tools) [(cites: Johnson2013)](#Johnson2013).
It is an intelligent dictionary in the sense that is able to look up North Sámi word forms and find lemmas via the FST.
It also allows a tolerant mode, which accepts the letters *acdnstz* for *áčđŋš\samit{*ž} in addition to their usual values.
The e-dictionary can split compounds to provide the user with its elements
as well as the whole compound if a translation is available.
The lexicalization of compounds is important since the translation of the
compound cannot necessarily be derived from the translation of its parts [(cites: Antonsen18[p.54])](#Antonsen18).

In the FST 90% of the 100 000 nouns, and in the dictionary 75% of the 25 000 nouns
are compounds.  
### A corpus tool

The web application and corpus search tool *Korp* [(cites: Borin2012)](#Borin2012) does
not show the internal structure of compounds in *SIKOR*.  Neither
lexicalized, nor dynamic compounds are searchable as either the lexicalized
analysis is picked instead of the dynamic one or – in the case of compounds
that are not listed in the lexicon – a lexicalized compound is made by the
preprocessor. This is a problem inherent in the implementation of the tool.
However, when searching for the compound tag used in the FST
(`+Cmp`), there are 94 658 results. The reason for that is that the first
element in split compounds in coordination receives a specific compound tag
(`+Cmp/SplitR`) as well.

Table [(see: table:sikor-compounds)](#table:sikor-compounds) shows the statistics for compounds in
*SIKOR*. (footnote: The search was done on 2020-09-07.)  The results are obtained using the scripts that can be found in *GiellaLT*. (footnote: {<a id="footnote_scripts">(¶ footnote_scripts)</a><https://github.com/giellalt/conf-clicit2021>)} According to our analyses 8.6%
of the tokens in corpus are compounds, and 86% are lexicalized.  The rest is
mainly composed of 2-elements compounds (13.4%) and a very small part of 4-7 elements (0.5%). 
Many of the longer compounds in *SIKOR* are quite creative and are
hyphenated as the one in ex. [(see: productivecompoundsikor)](#productivecompoundsikor).

<div style='font-size: small'>
**Linguistic example group:**

**suoidne-varra-bleahkka-mála-bihkka-senet-dielku** mu báiddis lei dušše lihkohisvuohta.<a id="productivecompoundsikor">(¶ productivecompoundsikor)</a>

hay-blood-ink-paint-tar-mustard-stain my shirt<span style='font-variant: small-caps'>.loc</span> was only mishap

‘The hay-blood-ink-paint-tar-mustard-stain on my shirt was only a mishap.’

</div>




**Table:**[h]
 <div style='text-align: center'>


| ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| \diagbox[height=7ex,width=8ex]{PoS}{Parts}  |  2  |  3  |  4  |  5  |  6/7  |
| **N**    	 |  96.2  |  98.9  |  89.2  |  80  |  66.7 |
| **Prop**  |  3.8  |  1.1  |  10.8  |  20  |  33.3 |

(Caption: Compound types in SIKOR by the PoS of their head and the number of their root (amounts given in percentage)<a id="table:sikor-compounds">(¶ table:sikor-compounds)</a>)
</div>
<!-- end table -->


The current public version of the Sámi corpus *SIKOR* [(cites: sikor_06.11.2018)](#sikor_06.11.2018) (in Korp) consists of 32.2
million words. It was analyzed with a
preprocessor that does not distinguish between lexicalized and
dynamic compounds. The (non-public) version of SIKOR used in this article
makes this distinction, though, as will future versions in Korp.

A search for compound tags only returns split compounds,
i.e. the first coordinated hyphenated nominal element, cf. in
ex. \Next, i.e. *riddo-* ‘coast-’.

**Linguistic example group:**

**riddo-** ja vuotnaguovlluin<a id="split">(¶ split)</a>

coast- and fjordregion<span style='font-variant: small-caps'>.loc.pl</span>

 ‘in coastal and fjord regions’


*GiellaLT* has already produced a solution, i.e. a tag for cohorts with
a dynamic compound (`&lt;with-dynamic-compound&gt;`) added by a Constraint Grammar module.
However, this tag does not provide any information
about the number of elements and the beginning and ending of each element.

### A grammar checker (GramDivvun)

*GramDivvun*, the
North Sámi grammar checker [(cites: Wiechetek2019)](#Wiechetek2019) takes input from the FST to a number of other modules, the core of which are several Constraint Grammar modules.  Constraint Grammar
is a rule-based formalism for writing disambiguation and syntactic
annotation grammars [(cites: Karlsson:1990,Karlsson:1995)](#Karlsson:1990,Karlsson:1995).
In our work, we use the free open source implementation VISLCG-3 [(cites: Didriksen2015)](#Didriksen2015). All components are compiled and built
using the *GiellaLT*
infrastructure [(cites: Moshagen2013BuildingAO)](#Moshagen2013BuildingAO).

Lexicalization of compounds is relevant for grammar checking within compound error detection. One common error that cannot be resolved by a spellchecker is the spelling of compounds as two or more words.
*GramDivvun* performs this type of error detection as part of the tokenization.
The tokenization is done in two steps. In the first step potential compounds are tokenized ambiguously (either as one or as two words, the first of which is accompanied by an errortag). In the second step, a Constraint Grammar module (footnote: <https://github.com/giellalt/lang-sme/blob/3a43911929458fd39da309ed23178bf5dbd04bcd/tools/tokenisers/mwe-dis.cg3>) selects or removes the error reading.
Two conditions need to be met to find the compound error:
1. the compound needs to be lexicalized, and 2. the syntactic context needs to support the compound reading.

The syntactic context is specified in hand-written Constraint Grammar rules. The REMOVE-rule below removes the compound error reading (identified by the tag Err/SpaceCmp) if the head is a 3rd person singular verb (cf. l.2) and the first element of the potential compound is a noun in nominative case (cf. l.3). The context condition further specifies that there should be a finite verb (VFIN) somewhere in the sentence (cf. l.4) for the rule to apply.


```
[frame=single,framerule=0.2mm,framesep=3mm,fontsize=<!-- footnotesize -->,baselinestretch=1,numbers=left]
REMOVE (Err/SpaceCmp)
(0/0 (V Sg3))
(0/1 (N Sg Nom))
(*0 VFIN);

```



All possible compounds written apart are considered
to be errors by default, unless the lexicon specifies a two or
several word compound or a syntactic rule removes the error reading.
There are numerous syntactic contexts where the potential parts of
compounds make perfectly sense.
In the case of noun-noun compounds, the second element can for example be a simple adverbial,
as in ex. [(see: manna)](#manna). The second element can be homonymous with another PoS, it can be a finite verb or an infinitive.


**Linguistic example group:**

son lea boarráseamus **mánná** **joavkkus**.<a id="manna">(¶ manna)</a>

s/he is oldest child group<span style='font-variant: small-caps'>.loc</span>

‘s/he is the oldest child in the group.’



## Evaluation

We evaluate the e-dictionary (coverage) and the grammar checker (precision, recall) for compounding (errors). The corpus search tool does not exhibit compounding information and is therefore not evaluated.


### An e-dictionary (NDS)

We analyzed the logs for NDS (*Neahttadigisánit*) for 2019, and found that 12.6% of
the types in the user queries are compounds. The results are obtained using the
scripts that can be found in *GiellaLT*The amount of lexicalized compounds in the logs (72.1%) is approximately
the same as in the dictionary, where it is 75% (cf. Section [(see: ndssection)](#ndssection) above).
As much as 98% of the compound queries get a translation, either a lexicalized one or of its parts. Thus dynamic compounding
contributes with a substantial improvement to dictionary coverage.
If the alternatives are “getting no help from the dictionary” and “getting help to translate the parts” then the latter is to be preferred, even though the correct translation would be different from just joining the parts.
For example, the compound word *ruhtahearrá* ‘rich man’ is not lexicalized in NDS but it does get a translation of its parts  *ruhta* ‘money’ and *hearrá* ‘man’, which can help the user to understand the meaning of the compound word itself.

Most of the non lexicalized compounds are composed of 2 elements (96% in the logs and 93% in the entries).
When analyzing the entries in the dictionary, we found that 24.8% are compounds and of those 97.6% are lexicalized.
Table [(see: tab:table1)](#tab:table1) shows PoS for compounds in NDS logs and entries.


**Table:**[h]
<!-- small -->
  <div style='text-align: center'>


| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| ****   |  | <!-- FIXME: multicolumn 4 |c| -->{**Logs**}   |  | <!-- FIXME: multicolumn 4 |c| -->{**Entries**}  |
| \diagbox[height=7.5ex,width=8ex]{PoS}{Parts}  |  L  |  2  |  3  |  4   |  L  |  2  |  3  |  4 |
| N 	 |  90 	 |  87 	 |  85  |  100  |  86  |  87  |  82  |  0|
| A 	 |  3 	 |  0 	 |  0  |  0  |  2  |  0  |  0  |  0 |
| Prop 	 |  3 	 |  0 	 |  0  |  0  |  12  |  4  |  0  |  0 |
| V 	 |  2 	 |  13 	 |  14  |  0  |  0  |  8  |  18  |  0|
| Adv 	 |  1 	 |  0 	 |  0  |  0  |  0  |  0  |  0  |  0 |

(Caption: Compounds according to the number of their parts and PoS in NDS logs and entries (L=lexicalized))
    <a id="tab:table1">(¶ tab:table1)</a>
  </div>
<!-- end table -->



### A grammar checker (GramDivvun)

We evaluate error detection for syntactic compound errors (i.e. words that are written
apart and should be a compound) in *GramDivvun* in two ways.
Firstly, we compare last year’s results in Wiechetek [(cites: Wiechetek2019b)](#Wiechetek2019b) with a
newer version of *GramDivvun*, from now on referred to as the *Nodalida*-corpus. Last year’s results are based on version *r183544* [(cites: Wiechetek2019b)](#Wiechetek2019b) (footnote: <https://github.com/giellalt/lang-sme/releases/tag/nodalida-2018> on 2019-09-26). The new results are based on version {r28510} (footnote: <https://github.com/giellalt/lang-sme/releases/tag/clicit> on 2020-09-07) of *GramDivvun*.

However, as the focus in the last analysis was a different one, i.e. we evaluated other error types as well, we ran a second evaluation on a
2 363 word-corpus (footnote: <http://gtsvn.uit.no/freecorpus/orig/sme/odda_mahppa/compounds.correct.txt>)
specifically made to test compound error detection, i.e. every sentence contains a potential compound. These sentences are hand-selected from *SIKOR*.

The results of the evaluation are presented in Table [(see: quantevaltbl)](#quantevaltbl). We can see that precision has gone significantly up, i.e. the average precision is 95.5%. However, the recall has gone down to average 46%. We are investigating the reasons for that. But in general, a high precision is desirable in grammar checking, even at the cost of a lower recall.

The results of the evaluation of *GramDivvun* compound grammar checking are shown in
Table [(see: quantevaltbl)](#quantevaltbl).




**Table:**[h]
 <div style='text-align: center'>


| ---- | ---- | ---- | ---- |
| **Measure**  |  (2019)  |  | <!-- FIXME: multicolumn 2 |c| -->{(2020)} |
| ****   |  | <!-- FIXME: multicolumn 2 |c| -->{**Nodalida**}   |  **Compound** | ****   |  | <!-- FIXME: multicolumn 2 |c| -->{**corpus**}   |  **corpus** |
| **Precision**     |   75.0%  |  93.1%  |  98.0% |
| **Recall**        |   72.9%  |  43.2%  |  48.5% |
| **F1-Score**      |    73.9  |  59.0     |  64.9|
| **TP**            |  51  |  54  |  50 |
| **FP**            |  17  |  4   |  1 |
| **FN**            |  19  |  67  |  53|

(Caption: Measures for GramDivvun (TP/FP= true/false
positives, FN=false negatives)<a id="quantevaltbl">(¶ quantevaltbl)</a>)
</div>
<!-- end table -->


False negatives are typically due to the lack of lexicalization.
Many of those are proper noun combinations which are very productive, e.g. *Murmánska-aviisa* ‘Murmansk newspaper’, *Várggát-festiválas* ‘at the Várggát festival’, *km-galba* ‘km sign’ and *Divttasvuotna-regiovnna* ‘Divttasvuotna region’. 
Other reasons are certain (unlikely) analyses of especially the first element, e.g.
that generally suggest a syntactic construction rather than a compound as in
ex. [(see: duorastat)](#duorastat). Here the first element *duorastat* ‘Thursday’ has a finite verb reading as well.


**Linguistic example group:**

dán **duorastat veaiggi**.<a id="duorastat">(¶ duorastat)</a>
 this<span style='font-variant: small-caps'>.gen</span> {Thursday twilight<span style='font-variant: small-caps'>.gen</span>}
 ‘this Thursday evening’



The false positive is due to an error in the recognition of the span of the
target. In ex. [(see: lullisami)](#lullisami), *lulli sámi guvlui* is concatenated, but it should only be *lulli sámi*.

**Linguistic example group:**

dohko **lulli** **sámi** guvlui.<a id="lullisami">(¶ lullisami)</a>
 thither South Sámi area<span style='font-variant: small-caps'>.ill</span>
 ‘thither towards the South Sámi area.’



## Conclusion

We have shown that the lexicalization of compounds – in addition to their dynamic
treatment –
is useful and necessary
for two language applications for North Sámi, an e-dictionary (*NDS*) and a
grammar checker (*GramDivvun*).  The evaluation of
*NDS* shows that we get a good coverage: 98% of the compounds logged do get a translation and 72% are lexicalized in the FST.
The evaluation
of *GramDivvun* has shown that we manage to identify compound
errors with a precision of 98% and a recall of 49% utilising a
combination of information from the lexicon and syntax.


We conclude that there are perfectly
good reasons for lexicalizing compounds, i.e. providing idiomatic translations for when it
cannot be derived from the parts, and to support compound grammar checking. At the same time, lexicalization can
dissimulate word formation information in corpus tools.
This can be resolved and we have already implemented a solution in Constraint Grammar to make the information available in a
future version of the corpus tool.
As dynamic compounding is limited to few PoS at the moment, in the
future we want to investigate and model compounding of other PoS (in the FST).
Also experiments with neural network approaches and a comparison of the results to our rule-based grammar checker could be an interesting future project.




## Acknowledgments
Thank you to Thomas Omma for doing the error corpus mark-up and for fun linguistic discussions, and to Lene Antonsen for digging in our corpus and helping to find just the right example.

<!-- bib style: acl -->
# References

* <a id="Deksne2019">**Deksne2019**</a>:
    * author: Daiga Deksne
    * title: Bidirectional LSTM Tagger for Latvian Grammatical Error Dete...
    * booktitle: Ekštein K. (eds) Text, Speech, and Dialogue. TSD 2019. Lectu...
    * year: 2019
    * url: https://doi.org/10.1007/978-3-030-27947-9_5
* <a id="Rozovskaya2019">**Rozovskaya2019**</a>:
    * author: Alla Rozovskaya and Dan Roth
    * title: Grammar Error Correction in Morphologically Rich Languages: ...
    * booktitle: Transactions of the Association for Computational Linguistic...
    * year: 2019
    * url: https://www.aclweb.org/anthology/Q19-1001.pdf
* <a id="Ethnologue2018">**Ethnologue2018**</a>:
    * editor: Simons, Gary F. and {Charles D.} Fennig
    * title: Ethnologue: Languages of the World
    * year: 2018
    * address: Dallas, Texas
    * publisher: SIL International
    * url: http://www.ethnologue.com (Accessed 2018-10-09)
    * edition: twenty-first
* <a id="callinravagirji2015">**callinravagirji2015**</a>:
    * author: Riektačállinrávvagat
    * title: Riektačállinrávvagat
    * howpublished: Sámedikki giellaossodat/Sámedikki oahpahusossodat, Guovdagea...
    * year: 2015,
    * url: https://www.sametinget.no/content/download/870/13825 (Access...
    * note: 
    * keywords: grammarchecking
    * key: Riektačállinrávvagat
* <a id="Wiechetek2012">**Wiechetek2012**</a>:
    * author: Linda Wiechetek
    * title: {Constraint Grammar} based correction of grammatical errors ...
    * booktitle: Proceedings of the Workshop on Language Technology for Norma...
    * year: 2012
    * month: may
    * date: 22
    * address: Istanbul, Turkey
    * editor: G. De Pauw and G-M de Schryver and M.L. Forcada and K. Saras...
    * publisher: European Language Resources Association (ELRA)
    * pages: 35–40
* <a id="Moshagen2013BuildingAO">**Moshagen2013BuildingAO**</a>:
    * title: Building an open-source development infrastructure for langu...
    * author: Sjur N. Moshagen and Tommi A. Pirinen and Trond Trosterud
    * booktitle: NODALIDA
    * year: 2013
* <a id="Pirinen2014">**Pirinen2014**</a>:
    * author: Pirinen, Tommi A. and Lindén, Krister
    * title: State-of-the-Art in Weighted Finite-State Spell-Checking
    * booktitle: Proceedings of the 15th International Conference on Computat...
    * series: CICLing 2014
    * year: 2014
    * location: Kathmandu, Nepal
    * pages: 519–532
    * numpages: 14
    * publisher: Springer-Verlag
    * address: Berlin, Heidelberg
    * keywords: error models, spell-checking, weighted finite-state technolo...
* <a id="Wiechetek2019">**Wiechetek2019**</a>:
    * title: Many shades of grammar checking – Launching a Constraint Gr...
    * booktitle: Proceedings of the NoDaLiDa 2019 Workshop on Constraint Gram...
    * series: NEALT Proceedings Series 33:8
    * author: Linda Wiechetek and Sjur Nørstebø Moshagen and Børre Gaup an...
    * year: 2019
    * pages: 35–44
* <a id="Beesley2003">**Beesley2003**</a>:
    * author: Kenneth R. Beesley and Lauri Karttunen
    * title: Finite State Morphology
    * publisher: CSLI Publications
    * series: CSLI Studies in Computational Linguistics
    * year: 2003,
    * address: Stanford
* <a id="Johnson2013">**Johnson2013**</a>:
    * title: Using finite state transducers for making efficient reading ...
    * booktitle: Proceedings of the 19th Nordic Conference of Computational L...
    * series: Proceedings Series 16: 59–71
    * author: Ryan Johnson , Lene Antonsen, Trond Trosterud
    * year: 2013
* <a id="Antonsen18">**Antonsen18**</a>:
    * Address: Tromsø
    * Author: Lene Antonsen
    * Date-Modified: 2020-01-04 15:55:28 +0200
    * Keywords: FST, CG, TWOL, spell checker,ICALL
    * School: UiT The Arctic University of Norway
    * Title: Sámegielaid modelleren – huksen ja heiveheapmi duohta
    * Url: https://hdl.handle.net/10037/12884
    * Year: 2018
    * Bdsk-Url-1: https://hdl.handle.net/10037/12884
* <a id="Borin2012">**Borin2012**</a>:
    * title: Korp – the corpus infrastructure of Språkbanken
    * booktitle: Proceedings of the 8th International Conference on Language ...
    * author: Borin, Lars and Forsberg, Markus and Roxendal, Johan
    * year: 2012
    * editor: Nicoletta Calzolari and Khalid Choukri and Thierry Declerck ...
    * publisher: European Language Resources Association (ELRA)
* <a id="sikor_06.11.2018">**sikor_06.11.2018**</a>:
    * author: SIKOR
    * title: SIKOR UiT Norgga árktalaš universitehta ja Norgga Sámedikki ...
    * url: http://gtweb.uit.no/korp
    * year: 2018,
    * note: Accessed: 2018-11-06
* <a id="Karlsson:1990">**Karlsson:1990**</a>:
    * address: Helsinki, Finland
    * author: Karlsson, Fred
    * booktitle: Proceedings of the 13th Conference on Computational Linguist...
    * editor: Karlgren, Hans
    * pages: 168–173
    * title: {Constraint Grammar as a Framework for Parsing Running Text}
    * publisher: Association for Computational Linguistics
    * volume: 3,
    * year: 1990,
* <a id="Karlsson:1995">**Karlsson:1995**</a>:
    * author: Fred Karlsson and Atro Voutilainen and Juha Heikkilä and Art...
    * title: Constraint Grammar: A Language-Independent System for Parsin...
    * address: Berlin
    * publisher: Mouton de Gruyter
    * year: 1995,
* <a id="Didriksen2015">**Didriksen2015**</a>:
    * author: Bick, Eckhard and Didriksen, Tino
    * booktitle: Proceedings of the 20th Nordic Conference of Computational L...
    * pages: 31–39
    * publisher: Linköping University Electronic Press, Linköpings universite...
    * editor: Beáta Megyesi
    * title: {CG-3} – Beyond Classical {Constraint Grammar}
    * year: 2015
    * issn: 1650-3740
* <a id="Wiechetek2019b">**Wiechetek2019b**</a>:
    * title: {Seeing more than whitespace – Tokenisation and disambiguat...
    * author: Linda Wiechetek and Kevin {Brubeck Unhammer} and Sjur {Nørst...
    * year: 2019
    * booktitle: Proceedings of the third Workshop on the Use of Computationa...
    * venue: Honolulu, Hawai’i
    * url: https://www.aclweb.org/anthology/W19-6007
    * pages: 46–55


<!-- end document -->

















* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

