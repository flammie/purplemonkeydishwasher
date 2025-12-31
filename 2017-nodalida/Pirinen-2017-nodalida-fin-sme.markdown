


# North Sámi to Finnish rule-based machine translation system¹ 

<span style='font-size:8pt'>(¹ Authors' archival version:      Originally published in NoDaLiDa 2017 in Göteborg.     Official vresion available from ACL anthology:     <http://aclweb.org/anthology/W17-0214> as well as Linköping university     repository: <http://www.ep.liu.se/ecp/article.asp?issue=131&article=014> Authors are listed in alphabetical order)</span> 


**Authors:** Ryan Johnson¹ 
and

Tommi A Pirinen² 
and

Tiina Puolakainen³ 
and

Francis
Tyers¹ 
and

Trond Trosterud¹ 
and

Kevin Unhammer¹

¹ UiT Norgga \’Arktala\v{s universitehta, Giela ja kultuvrra instituhtta, Romssa, Norga 

² Universität Hamburg, Hamburger Zentrum für Sprachkorpora, Deutschland 

³ Institute of the Estonian Language, Estonia

ryan.txanson@gmail.com, tommi.antero.pirinen@uni-hamburg.de, 
 tiina.puolakainen@eki.ee,
\{francis.tyers, trond.trosterud\}@uit.no 

kevin@unhammer.org
}




<!-- begin document -->
<!-- make title -->

**Abstract:**
This paper presents a machine translation system between Finnish and North Sámi, two Uralic languages.
In this paper we concentrate on the translation direction to Finnish.
As a background, the differences between the two languages is presented, followed by how the system was designed to handle some of these differences.
We then provide an evaluation of the system’s performance and directions for future work.
<!-- end abstract -->


## Introduction
<a id="sec:introduction">(¶ sec:introduction)</a>
This paper presents a prototype shallow-transfer rule-based machine translation system between Finnish and North Sámi.
The paper will be laid out as follows: Section [(see: sec:previous-work)](#sec:previous-work) gives a short review of some previous work in the area of Uralic-Uralic language machine translation; Section [(see: sec:languages)](#sec:languages) introduces Finnish and North Sámi and compares their grammar; Section [(see: sec:system)](#sec:system) describes the system and the tools used to construct it; Section [(see: sec:evaluation)](#sec:evaluation) gives a preliminary evaluation of the system; and finally Section [(see: sec:conclusions)](#sec:conclusions) describes our aims for future work and some concluding remarks.

## Previous work
<a id="sec:previous-work">(¶ sec:previous-work)</a>

Within the Apertium platform, work on several MT systems from North Sámi to Norwegian and to other Sámi languages have been developed [(cites: tyers09,wiechetek10,trosterud12,smesma)](#tyers09,wiechetek10,trosterud12,smesma)).
Besides these systems, several previous works on making machine translation systems between Uralic languages exist, although to our knowledge none are publicly available, except for North Sámi to Norwegian (footnote: <https://gtweb.uit.no/jorgal>), and the translation between Estonian, Finnish and Hungarian being available via English as a pivot language in Google Translate. (footnote: <https://translate.google.com>)
For non-Uralic pairs there are also numerous similarly laid out systems e.g. in Apertium’s Turkic pairs, e.g. [(cites: salimzyanov2013free)](#salimzyanov2013free), that can offer insights on how the pair is implemented, which are detailed later in the article but the main parts are the same.

## The languages
<a id="sec:languages">(¶ sec:languages)</a>

North Sámi and Finnish belong to the Sámi and Finnic branches of the Uralic languages, respectively.
The languages are mutually unintelligible, but grammatically quite similar. The orthographical conventions between Finnish and North Sámi written in Finland were quite similar until 1979, when an unified North Sámi orthography widened the distance to Finnish.
Finnish is primarily spoken in Finland, where it is the national language, sharing status with Swedish as an official language.
The total number of speakers is at least 6 million people.
North Sámi is spoken in the Northern parts of Norway, Sweden and Finland by approximately 24.700 people, and it has, alongside the national language, some official status in the municipalities and counties where it is spoken.
North Sámi speakers  are bilingual in  their mother tongue and in their respective national language, many also speak the neighbouring official language.
An MT system between North Sámi and Finnish is potentially of great use to the language communities, although fulfilling different functions. In Finland, it may be used to understand Sámi text, and in Norway and Sweden, it may be used by North Sámi speakers to understand Finnish text. In principle, the system may also be used for North Sámi text production, although further development will be needed to fulfil such a function.


### Phonological differences
<a id="subseC:phonological-differences">(¶ subseC:phonological-differences)</a>

As related languages, Finnish and North Sámi share several phonological processes, the most important one being consonant gradation.
However, North Sámi consonant gradation involves the vast majority of stem-internal consonant clusters, whereas the Finnish counterpart involves only the stops *p, t, k*. Vowel length has a more central role in Finnish than in North Sámi, Several instances of final vowel apocopy in North Sámi, as well as a neutralisation of *p, t, k* in word-final position, has also resulted in quite extensive morphological homonymy. A richer inventory of affricates and fricatives in North Sámi, as well as preaspiration, also add to the difference.

### Orthographic differences
<a id="subsec:orthographic-differences">(¶ subsec:orthographic-differences)</a>

In the native vocabulary, neither Finnish nor North Sámi distinguish between voiced and unvoiced plosives,  but whereas  Finnish writes them as *p, t, k*, North Sámi writes  *b, d, g*, as in *kirja : girji* “book”. Finnish marks vowel length with double letter symbols. In North Sámi this distinction is marked for one vowel only, <span class='math'>a</span>, and with acute accent. Apart from this the orthographic principles of the two languages is quite similar, the almost total lack of free rides is a result of different phonology.

### Morphological differences
<a id="subsec:morphological-differences">(¶ subsec:morphological-differences)</a>

There are a number of examples where the morphologies of Finnish and North Sámi are rather different.

North Sámi has a separate dual number, whereas Finnish has not.  Otherwise the North Sámi and Finnish finite verb morphology is almost identical. The infinite  verb conjugation is more different, though: Finnish has a rich array of infinitives that are inflected in different subsets of the case system.

Finnish has more than twice the number of cases as  North Sámi has. Where  North Sámi only has one case for the direct object (accusative), Finnish has two  (accusative and partitive). The Finnish system of adverbial cases consist of a 2x3 matrix of inner/outer to/in/from cases,  North Sámi has only one of these distinctions (to/in\ from), thus the 6 Finnish cases corresponds to 2 North Sámi ones. In principle, Finnish and North Sámi have the same system of possessive suffixes, but in  North Sámi its use is  far more restricted than in Finnish.


### Syntactic differences
<a id="subsec:syntactic-differences">(¶ subsec:syntactic-differences)</a>


Syntactically speaking, there are two varieties of North Sámi, one  used within and one outside of Finland. The Finnish variety is much closer to Finnish than the Scandinavian one. Comparing Finnish with the Scandinavian variety of North Sámi, the most striking difference is  participle constructions vs. relative clauses. Where North Sámi uses subordinate clauses,  written Finnish often use  head-final participle constructions instead. Since both varieties are found in Finnish, at least to some degree, we at the moment let most “Scandinavian” varieties of North Sámi through, thereby giving North Sámi from Norway and Finland a different stylistic flavour in the Finnish output.

The  North Sámi passive is a derivational process, whereas it for Finnish is an inflectional one, resulting in quite  different syntactic patterns for passive. Finnish has a richer array of indefinite verb forms.

Finnish adjectives agree with their head noun in case and number, whereas North Sámi has an invariant <span class='math'>attribute</span> form for all but one adjective, the adjective *buorre* ‘good’, and partial
agreement for determiners.

Existential and habitive clauses have the same structure in the two languages, *possessor.local-case copula possessed* and *adverbial copula e-subject* (*on me / in street is car* ‘I have a car/There is a car in the street’). except that in Finnish, the possessed/e-subject behaves like objects, whereas it in North Sámi they behave like subjects. Thus, in North Sámi, the copula agrees with the possessed / e-subject, whereas in Finnish, it does not.


## System
<a id="sec:system">(¶ sec:system)</a>

The system is based on the Apertium (footnote: <http://apertium.sf.net>) machine translation platform [(cites: forcada2011apertium)](#forcada2011apertium).
The platform was originally aimed at the Romance languages of the Iberian peninsula, but has also been adapted for other, more distantly related, language pairs.
The whole platform, both programs and data, are licensed under the Free Software Foundation’s General Public Licence (footnote: <https://www.gnu.org/licenses/gpl-3.0.en.html>) (GPL) and all the software and data for the 30 released language pairs (and the other pairs being worked on) is available for download from the project website.

### Architecture of the system
<a id="subsec:architecture-of-the-system">(¶ subsec:architecture-of-the-system)</a>

The Apertium translation engine consists of a Unix-style pipeline or assembly line with the following modules (see Figure [(see: fig:apertium)](#fig:apertium)):



**Figure:**
![Apertium-structure](Apertium-structure)
(Caption: Apertium structure (Image from apertium wiki by user Rcrowther)
<http://wiki.apertium.org/wiki/Workflow_diagram>
<a id="fig:apertium">(¶ fig:apertium)</a>)
<!-- end figure* -->


*  A deformatter which encapsulates the format information in the input as *superblanks* that will then be seen as blanks between words by the other modules.
*  A morphological analyser which segments the text in surface forms (SF) (words, or, where detected, multiword lexical units or MWLUs) and for each, delivers one or more lexical forms (LF) consisting of lemma, lexical category and morphological information.
*  A morphological disambiguator (CG) which chooses, using linguistic rules the most adequate sequence of morphological analyses for an ambiguous sentence.
*  A lexical transfer module which reads each SL LF and delivers the corresponding target-language (TL) LF by looking it up in a bilingual dictionary encoded as an FST compiled from the corresponding XML file.
The lexical transfer module may return more than one TL LF for a single SL LF.
*  A lexical selection module (Tyers et al., 2012b) which chooses, based on context rules, the most adequate translation of ambiguous source language LFs.
*  A structural transfer module, which performs local syntactic operations, is compiled from XML files containing rules that associate an action to each defined LF pattern.
Patterns are applied left-to-right, and the longest matching pattern is always selected.
*  A morphological generator which delivers a TL SF for each TL LF, by suitably inflecting it.
*  A reformatter which de-encapsulates any format information.


Table [(see: table:translation)](#table:translation) provides an example of a single phrase as it moves through the pipeline.








**Table:**
<div style='font-size: small'>


| ---- |
<!-- bf -->North Sámi input: Sámegielat leat gielat maid sámit hállet. |
Morphological analysis: |
| \^Sámegielat/ sámegielat | lt;adj | gt;  | lt;attr | gt;/ sámegielat | lt;adj | gt;  | lt;sg | gt; | lt;nom | gt;/ |
| sámegiella | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;/ sámegiella | lt;n | gt;  | lt;sg | gt; | lt;acc | gt; | lt;px2sg | gt;/ |
| sámegiella | lt;n | gt;  | lt;sg | gt; | lt;gen | gt; | lt;px2sg | gt;/ sámegiella | lt;n | gt;  | lt;sg | gt; | lt;acc | gt; | lt;px2sg | gt;/ |
| sámegiella | lt;n | gt;  | lt;sg | gt; | lt;gen | gt; | lt;px2sg | gt;\<span class='math'> |
|
| \^leat/ leat | lt;vblex | gt; | lt;iv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;conneg | gt;/ |
| leat | lt;vblex | gt; | lt;iv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;p1 | gt; | lt;pl | gt;/ leat | lt;vblex | gt; | lt;iv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;p2 | gt; | lt;sg | gt;/ | leat | lt;vblex | gt; | lt;iv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;/ leat | lt;vblex | gt; | lt;iv | gt;  | lt;inf | gt;\</span> |
| \^gielat/ giella | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;/ giella | lt;n | gt;  | lt;sg | gt; | lt;acc | gt; | lt;px2sg | gt;/ |
|
| giella | lt;n | gt;  | lt;sg | gt; | lt;gen | gt; | lt;px2sg | gt;/ giella | lt;n | gt;  | lt;sg | gt; | lt;acc | gt; | lt;px2sg | gt;/|
| giella | lt;n | gt;  | lt;sg | gt; | lt;gen | gt; | lt;px2sg | gt;\<span class='math'> \^maid/ maid | lt;adv | gt;/ mii | lt;prn | gt; | lt;itg | gt;  | lt;pl | gt; | lt;acc | gt;/ |
|
| mii | lt;prn | gt; | lt;itg | gt;  | lt;pl | gt; | lt;gen | gt;/ mii | lt;prn | gt; | lt;itg | gt;  | lt;sg | gt; | lt;acc | gt;/ mii | lt;prn | gt; | lt;rel | gt;  | lt;pl | gt; | lt;acc | gt;/ |
| mii | lt;prn | gt; | lt;rel | gt;  | lt;pl | gt; | lt;gen | gt;/ mii | lt;prn | gt; | lt;rel | gt;  | lt;sg | gt; | lt;acc | gt;\</span> |
|
| \^sámit/ sápmi | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;/ sápmi | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;\<span class='math'> |
|
| \^hállet/ hállat | lt;vblex | gt; | lt;tv | gt;  | lt;imp | gt; | lt;p2 | gt; | lt;pl | gt;/ |
| hállat | lt;vblex | gt; | lt;tv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;/ hállat | lt;vblex | gt; | lt;tv | gt;  | lt;indic | gt; | lt;pret | gt; | lt;p2 | gt; | lt;sg | gt;\</span> |
| \^./. | lt;sent | gt;\<span class='math'>
|
Morphological disambiguation: |
| \^Sámegielat/sámegiella | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@SUBJ</span>\rightarrow<span class='math'> | gt;\</span> |
| \^leat/leat | lt;vblex | gt; | lt;iv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;  | lt;@+FMAINV | gt;\<span class='math'> |
| \^gielat/giella | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@</span>\leftarrow<span class='math'>SPRED | gt;\</span> |
| \^maid/mii | lt;prn | gt; | lt;rel | gt;  | lt;pl | gt; | lt;acc | gt;  | lt;@OBJ<span class='math'>\rightarrow</span> | gt;\<span class='math'> |
| \^sámit/sápmi | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@SUBJ</span>\rightarrow<span class='math'> | gt;\</span> |
| \^hállet/hállat | lt;vblex | gt; | lt;tv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;  | lt;@+FMAINV | gt;\<span class='math'>
| \^./. | lt;sent | gt;\</span>
|
Lexical translation: |
| \^Sámegiella | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@SUBJ<span class='math'>\rightarrow</span> | gt;/ Saamekieli | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@SUBJ<span class='math'>\rightarrow</span> | gt;/ |
| Saame | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@SUBJ<span class='math'>\rightarrow</span> | gt;\<span class='math'> |
|
| \^leat | lt;vblex | gt; | lt;iv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;  | lt;@+FMAINV | gt;/ |
| olla | lt;vblex | gt;  | lt;actv | gt; | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;  | lt;@+FMAINV | gt;/ |
| sijaita | lt;vblex | gt;  | lt;actv | gt; | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;  | lt;@+FMAINV | gt;\</span> |
|
| \^giella | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@<span class='math'>\leftarrow</span>SPRED | gt;/ kieli | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@<span class='math'>\leftarrow</span>SPRED | gt;/ |
| ansa | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@<span class='math'>\leftarrow</span>SPRED | gt;\<span class='math'> |
|
| \^mii | lt;prn | gt; | lt;rel | gt;  | lt;pl | gt; | lt;acc | gt;  | lt;@OBJ</span>\rightarrow<span class='math'> | gt;/ mikä | lt;prn | gt; | lt;rel | gt;  | lt;pl | gt; | lt;acc | gt;  | lt;@OBJ</span>\rightarrow<span class='math'> | gt;\</span> |
|
| \^sápmi | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@SUBJ<span class='math'>\rightarrow</span> | gt;/ saame | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;  | lt;@SUBJ<span class='math'>\rightarrow</span> | gt;\<span class='math'> |
|
| \^hállat | lt;vblex | gt; | lt;tv | gt;  | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;  | lt;@+FMAINV | gt;/ |
| puhua | lt;vblex | gt;  | lt;actv | gt; | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;  | lt;@+FMAINV | gt;/ |
| mekastaa | lt;vblex | gt;  | lt;actv | gt; | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;  | lt;@+FMAINV | gt;\</span>\^. | lt;sent | gt;/. | lt;sent | gt;\<span class='math'>
|
Structural transfer: |
| \^Saamekieli | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;\</span>
| \^olla | lt;vblex | gt;  | lt;actv | gt; | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;\<span class='math'> |
| \^kieli | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;\</span>
| \^mikä | lt;prn | gt; | lt;rel | gt;  | lt;pl | gt; | lt;par | gt;\<span class='math'> |
| \^saame | lt;n | gt;  | lt;pl | gt; | lt;nom | gt;\</span>
| \^puhua | lt;vblex | gt;  | lt;actv | gt; | lt;indic | gt; | lt;pres | gt; | lt;p3 | gt; | lt;pl | gt;\<span class='math'>\^. | lt;sent | gt;\</span>
|
Finnish translation: |
Saamekielet ovat kielet \#mikä saamet puhuvat |

(Caption: Translation process for the North Sámi phrase *Sámegielat leat gielat maid sámit hállet* (The Sámi languages are the languages that the Sámis speak)
<a id="table:translation">(¶ table:translation)</a>)
</div>
<!-- end table* -->



### Morphological transducers
<a id="subsec:morphological-transducers">(¶ subsec:morphological-transducers)</a>

The morphological transducers are compiled with the Helsinki Finite State Technology [(cites: linden2009hfst)](#linden2009hfst), (footnote: <https://hfst.github.io>) a free/open-source  reimplementation of the Xerox finite-state tool-chain, popular in the field of morphological analysis.
It implements both the lexc morphology description language for defining lexicons, and the twol and xfst scripting languages for modeling morphophonological rules.
This toolkit has been chosen as it—or the equivalent XFST—has been widely used for other Uralic  languages [(cites: koskenniemi1983two,pirinen2015development,moshagen2013building)](#koskenniemi1983two,pirinen2015development,moshagen2013building), and is available under a free/open-source licence.
The morphologies of both languages are implemented in lexc, and the morphophonologies of both languages are implemented in twolc.




The same morphological description is used for both analysis and generation.
To avoid overgeneration, any alternative forms are marked with one of two marks, LR (only analyser) or RL (only generator).
Instead of the usual compile/invert to compile the transducers, we compile twice, once the generator, without the LR paths, and then again the analyser without the RL paths.

### Bilingual lexicon
<a id="subsec:bilingual-lexicon">(¶ subsec:bilingual-lexicon)</a>

The bilingual lexicon currently contains 19,415 stem-to-stem correspondences (of which 8044 proper nouns) and was built partly upon an available North Sámi—Finnish dictionary (footnote: <https://gtweb.uit.no/langtech/trunk/words/dicts/smefin/src/>), and partly by hand (i.e., by translating  North Sámi stems unrecognised by the morphological analyser into Finnish). The proper nouns were taken from existing lexical resources.
Entries consist largely of one-to-one stem-to-stem correspondences with part of speech, but also include some entries with ambiguous translations (see e.g., Figure [(see: fig:bilingual)](#fig:bilingual)).


**Figure:**

```

    &lt;e&gt;&lt;p&gt;&lt;l&gt;sálten&lt;s n="n"/&gt;&lt;/l&gt;&lt;r&gt;suolaus&lt;s n="n"/&gt;&lt;/r&gt;&lt;/p&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;sálti&lt;s n="n"/&gt;&lt;/l&gt;&lt;r&gt;suola&lt;s n="n"/&gt;&lt;/r&gt;&lt;/p&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;sámeduodji&lt;s n="n"/&gt;&lt;/l&gt;&lt;r&gt;käsityö&lt;s n="n"/&gt;&lt;/r&gt;&lt;/p&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;sámegiella&lt;s n="n"/&gt;&lt;/l&gt;&lt;r&gt;saame&lt;s n="n"/&gt;&lt;/r&gt;&lt;/p&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;sámegiella&lt;s n="n"/&gt;&lt;/l&gt;&lt;r&gt;saamekieli&lt;s n="n"/&gt;&lt;/r&gt;&lt;/p&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;sámi&lt;s n="n"/&gt;&lt;/l&gt;&lt;r&gt;saame&lt;s n="n"/&gt;&lt;/r&gt;&lt;/p&gt;&lt;/e&gt;
    &lt;e&gt;&lt;p&gt;&lt;l&gt;sámil&lt;s n="n"/&gt;&lt;/l&gt;&lt;r&gt;sammal&lt;s n="n"/&gt;&lt;/r&gt;&lt;/p&gt;&lt;/e&gt;


```

(Caption: Example entries from the bilingual transfer lexicon. Finnish is on the right, and North Sámi on the left.
<a id="fig:bilingual">(¶ fig:bilingual)</a>
)
<!-- end figure* -->

### Disambiguation rules

The system has a morphological disambiguation module in the form of a Constraint Grammar [(cites: karlsson1995constraint)](#karlsson1995constraint).
The version of the formalism used is vislcg3. (footnote: <http://visl.cg.sdu.dk>)
The output of each morphological analyser is highly ambiguous, measured at around 2.4 morphological analyses per form for Finnish and 2.6 for North Sámi (footnote: Cf. [(cites: Trosterud07)](#Trosterud07)).
The goal of the CG rules is to select the correct analysis when there are multiple analyses.
Given the similarity of Finnish and North Sámi, ambiguity across parts of speech may often be passed from one language to the other and not lead to many translation errors.
Disambiguating between forms within the inflectional paradigms in case of homonymy, on the other hand, are crucial for choosing the correct form of the target language, and there has been put much effort into developing CG rules to resolve such ambiguity for North Sámi. Currently, ambiguity is down to 1.08 for North Sámi (analysed with the disambigator used for MT on a 675534 word newspaper corpus (footnote: Cf. [(cites: AntonsenTrosterudFST)](#AntonsenTrosterudFST) for a presentation of the North Sámi CG.). The corresponding number for Finnish is 1.36, for a subcorpus of 770999 words of Wikipedia text. The Finnish CG rules are a conversion of Fred Karlsson’s original CG1 rules for Finnish [(cites: karlsson1990constraint)](#karlsson1990constraint), and the poorer results for Finnish are due to conversion problems between the different CG version, and between CG1 and our Finnish FST.








## Evaluation
<a id="sec:evaluation">(¶ sec:evaluation)</a>


All evaluation was tested against a specific version of Apertium SVN (footnote: <https//svn.code.sf.net/p/apertium/svn/nursery/apertium-sme-fin>: revision 76019) and Giellatekno SVN (footnote: <https://victorio.uit.no/langtech/trunk/langs/sme>: revision 147464).
The lexical coverage of the system was calculated over freely available corpora of North Sámi.
We used a recent dump of Wikipedia  (footnote: <http://se.wikipedia.org>) as well as a translation of the New Testament.
The corpora were divided into 10 parts each; the coverage numbers given are the averages of the calculated percentages of number of words analysed for each of these parts, and the standard deviation presented is the standard deviation of the coverage on each corpus.
As shown in Table [(see: table:coverage)](#table:coverage), the na\"{i}ve coverage (footnote: A non-naïve coverage would require manual evaluation of correctness for the cases where word-forms are covered accidentally by e.g., morphological processes.) of the North Sámi to Finnish MT system over the corpora approaches that of a broad-coverage MT system, with one word in ten unknown.



**Table:**


| ---- | ---- | ---- | ---- |
| <!-- bf -->Corpus  |  <!-- bf -->Tokens  |  <!-- bf -->Cov.  |  <!-- bf -->std |
| se.wikipedia.org  |  190,894  |  76,81 %   |  <span class='math'>\pm</span>10|  New Testament     |  162,718  |  92,45 %  |  <span class='math'>\pm</span>0.06 |  

(Caption: Na\"{i)ve coverage of sme-fin system
<a id="table:coverage">(¶ table:coverage)</a>}
<!-- end table -->


The coverage over the Wikipedia corpus is substantially worse, due to the fact that this corpus is “dirtier”: it contains orthographical errors, wiki code  (footnote: While we have tried to clean the data from most of the Mediawiki codes and notations, there is always some left after the cleanup, due to new wiki codes after creation of the cleanup script or actual broken data), repetitions, lot of English texts, as well as quite a few proper nouns, this is easily seen in the large deviation between divided parts.
The New Testament on the other hand is rather well covered and has practically uniformly distributed coverage throughout.

To measure the performance of the translator we used the Word Error Rate metric—an edit-distance metric based on Levenshtein distance [(cites: levenshtein1966binary)](#levenshtein1966binary).
We had three small North Sámi corpora along with their manually post-edited translations into Finnish to measure the WER.
We have chosen not to measure the translation quality with automatic measures such as BLEU, as they are not the best suited to measure quality of translations for the use case, for further details see also [(cites: callison2006re,smith2016climbing,smith2014bleu)](#callison2006re,smith2016climbing,smith2014bleu).

For translation post-edition we used three freely available parallel texts from the internet: one from the Finnish Sámi parliament site (footnote: <http://samediggi.fi>), one from a Swedish regulation of minority people and languages and the story that is used with all Apertium language pairs as initial development set (“Where is James?”).
Table [(see: table:wer)](#table:wer) presents the WER for the corpora.


**Table:**



| ---- | ---- | ---- | ---- |
| <!-- bf -->Corpus  |  <!-- bf -->Tokens  |  <!-- bf -->OOV  |  <!-- bf -->WER |
| Redigering.se  |  1,070  |  95  |  34.24 |
| Samediggi.fi  |  570  |  33  |  36.32 |
| The Story  |  361  |  0  |  19.94 |

(Caption: Word error rate over the corpora; OOV is the number of out-of-vocabulary (unknown) words.
<a id="table:wer">(¶ table:wer)</a>)

<!-- end table -->

Analysing the changes in post-edition, a few classes of actual errors can be identified.
One common example arises from the grammatical differences in the case system systems, in particular the remaining adpositions are often turned into a case suffix for the dependent noun phrase, e.g., the North Sámi “birra” has been turned into the Finnish adposition “ymp\"ari” (around), where elative case is required, similarly for the translation “seassa” (among) instead of inessive case.
Also visible, especially in the story text is the lack of possessive suffix agreement e.g. “heid\"an \"aiti” (their mother <span style='font-variant: small-caps'>n sg nom</span>) instead of “heid\"an \"aitins\"a” (their mother <span style='font-variant: small-caps'>n sp nom/gen pxsp3</span>), while the former is perfectly acceptable in standard spoken Finnish it is not accepted as formal written language form.
Another issue that appeared a number of times, maybe partially due to the genre of the texts selected, i.e. law texts, was the selection of adverb (form), e.g. the word-form “mukana” (with) was corrected to “mukaan” (according to).
A large amount of simple lexical problems is due to the vocabulary of the selected texts as well: “hallintoalue” (governmental area), “seurantavastuu” (responsibility of surveillance), “itsehallinto” (autonomy), and their compounds, are all either missing or partially wrong due to lexical selections.

## Concluding remarks
<a id="sec:conclusions">(¶ sec:conclusions)</a>

To our knowledge we have presented the first MT system from Finnish to North Sámi.
With a WER of above 30%, it still is far from production-level performance, and it is also at the prototype-level in terms of the number of rules.
Although the impact of this relatively low number of rules on the quality of translation is extensive (cf., the difference in WER between the development and testing corpora), the outlook is promising and the current results suggest that a high quality translation between morphologically-rich agglutinative languages is possible.
We plan to continue development on the pair; the coverage of the system is already quite high, although we intend to increase it to 95 % on the corpora we have
we estimate that this will mean adding around 5,000 new stems and take 1–2 months.
The remaining work will be improving the quality of translation by adding more rules, starting with the CG module.
The long-term plan is to integrate the data created with other open-source data for Uralic languages in order to make transfer systems between all the Uralic language pairs.
Related work is currently ongoing from North Sámi to South, Lule and Inari Sámi, from North  Sámi to Norwegian, and between Finnish and Estonian.
The system is available as free/open-source software under the GNU GPL and the whole system may be downloaded from Sourceforge and the open repository of Giellatekno.


## Acknowledgements
<a id="sec:acknowlegdements">(¶ sec:acknowlegdements)</a>
The work on this North Sámi-Finnish machine translation system was partially funded by the Google Summer of Code and Google Code-In programmes, and partly by a Norsk forsingsråd grant (234299) on machine translation between Sámi languages.
<!-- bib style: unsrt -->
# References

* <a id="tyers09">**tyers09**</a>:
    * Author: Francis Tyers and Linda Wiechetek and Trond Trosterud
    * Booktitle: Proceedings of the 13th Annual Conference of the European As...
    * Pages: 120–128
    * Title: {Developing prototypes for machine translation between two S...
    * year: 2009
* <a id="wiechetek10">**wiechetek10**</a>:
    * Author: Linda Wiechetek and Francis Tyers and Thomas Omma
    * Journal: Lecture Notes in Artificial Intelligence
    * Pages: 418–429
    * Title: {Shooting at flies in the dark: Rule-based lexical selection...
    * Volume: 6233,
    * year: 2010
* <a id="trosterud12">**trosterud12**</a>:
    * Author: Trond Trosterud and Kevin Brubeck Unhammer
    * Booktitle: Proceedings of the Third International Workshop on Free/Open...
    * Pages: 13–26
    * Series: Technical report
    * Volume: 3
    * Title: {Evaluating North Sámi to Norwegian assimilation RBMT}
    * Publisher: Department of Computer Science and Engineering, Chalmers Uni...
    * year: 2013
* <a id="smesma">**smesma**</a>:
    * Author: Lene Antonsen and Trond Trosterud and Francis Tyers
    * Title: A North Saami to South Saami Machine Translation Prototype
    * Year: 2016
    * booktitle: NEJLT Special Issue on Uralic Languages
    * pages: 11—27
    * volume: 4
    * doi: 	10.3384/nejlt.2000-1533.1642
    * publisher: Linköping University Press
* <a id="salimzyanov2013free">**salimzyanov2013free**</a>:
    * title: A free/open-source Kazakh-Tatar machine translation system
    * author: Salimzyanov, Ilnar and Washington, J and Tyers, F
    * journal: Machine Translation Summit XIV
    * year: 2013
* <a id="forcada2011apertium">**forcada2011apertium**</a>:
    * title: Apertium: a free/open-source platform for rule-based machine...
    * author: Forcada, Mikel L and Ginestí-Rosell, Mireia and Nordfalk, Ja...
    * journal: Machine translation
    * volume: 25
    * number: 2
    * pages: 127–144
    * year: 2011
    * publisher: Springer
* <a id="linden2009hfst">**linden2009hfst**</a>:
    * title: HFST tools for morphology–an efficient open-source package ...
    * author: Lindén, Krister and Silfverberg, Miikka and Pirinen, Tommi
    * booktitle: International Workshop on Systems and Frameworks for Computa...
    * pages: 28–47
    * year: 2009
    * organization: Springer
* <a id="koskenniemi1983two">**koskenniemi1983two**</a>:
    * title: Two-level morphology—A General Computational Model for Wor...
    * school: Department of General Linguistics. University of Helsinki, F...
    * author: Koskenniemi, Kimmo
    * year: 1983
* <a id="pirinen2015development">**pirinen2015development**</a>:
    * title: Development and Use of Computational Morphology of Finnish i...
    * author: Pirinen, Tommi A
    * journal: SKY Journal of Linguistics
    * volume: 28
    * pages: 381–393
    * year: 2015
* <a id="moshagen2013building">**moshagen2013building**</a>:
    * title: Building an open-source development infrastructure for langu...
    * author: Moshagen, Sjur N and Pirinen, Tommi A and Trosterud, Trond
    * booktitle: Proceedings of the 19th Nordic Conference of Computational L...
    * number: 085
    * pages: 343–352
    * year: 2013
    * organization: Linköping University Electronic Press
* <a id="karlsson1995constraint">**karlsson1995constraint**</a>:
    * title: Constraint Grammar: a language-independent system for parsin...
    * author: Karlsson, Fred and Voutilainen, Atro and Heikkilae, Juha and...
    * volume: 4
    * year: 1995
    * publisher: Walter de Gruyter
* <a id="Trosterud07">**Trosterud07**</a>:
    * author: Trond Trosterud and Linda Wiechetek
    * title: Disambiguering av homonymi i {Nord- og Lulesamisk}
    * address: Helsinki
    * journal: Suomalais-Ugrilaisen Seuran Toimituksia $nno-Ougrienne.  Sám...
    * volume: 253
    * pages: 375–395
    * year: 2007
* <a id="AntonsenTrosterudFST">**AntonsenTrosterudFST**</a>:
    * Author: Lene Antonsen and Trond Trosterud
    * Title: Ord sett innafra og utafra – en datalingvistisk analyse av n...
    * note: Norsk Lingvistisk Tidsskrift
    * year: forthcoming
* <a id="karlsson1990constraint">**karlsson1990constraint**</a>:
    * title: Constraint grammar as a framework for parsing running text
    * author: Karlsson, Fred
    * booktitle: Proceedings of the 13th conference on Computational linguist...
    * pages: 168–173
    * year: 1990
    * organization: Association for Computational Linguistics
* <a id="levenshtein1966binary">**levenshtein1966binary**</a>:
    * title: Binary codes capable of correcting deletions, insertions, an...
    * author: Levenshtein, Vladimir I
    * booktitle: Soviet physics doklady
    * volume: 10
    * number: 8
    * pages: 707–710
    * year: 1966
* <a id="callison2006re">**callison2006re**</a>:
    * title: Re-evaluation the Role of Bleu in Machine Translation Resear...
    * author: Callison-Burch, Chris and Osborne, Miles and Koehn, Philipp
    * booktitle: EACL
    * volume: 6
    * pages: 249–256
    * year: 2006
* <a id="smith2016climbing">**smith2016climbing**</a>:
    * title: Climbing Mount BLEU: The Strange World of Reachable High-BLE...
    * author: Smith, Aaron and Hardmeier, Christian and Tiedemann, Jörg
    * journal: Baltic Journal of Modern Computing
    * volume: 4
    * number: 2
    * pages: 269
    * year: 2016
    * publisher: University of Latvia
* <a id="smith2014bleu">**smith2014bleu**</a>:
    * title: Bleu is not the colour: How optimising bleu reduces translat...
    * author: Smith, Aaron and Hardmeier, Christian and Tiedemann, Jörg
    * year: 2014

<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

