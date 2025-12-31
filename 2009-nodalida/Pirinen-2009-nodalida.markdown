
<!-- usepackage latexsym  -->


\hypersetup{
pdfinfo={
Author={Krister Linden and Tommi Pirinen},
Title={Weighted Finite-State Morphological Analysis of Finnish Inflection and Compounding},
CreationDate={D:20090101123456},
Subject={Finite-State Morphology},
Keywords={FSM;FST;Morphology}
    }
}


# Weighted Finite-State Morphological Analysis
   of Finnish Inflection and Compounding¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: The official   publication was in Nodalida 2009 organised in Odense,   <http://beta.visl.sdu.dk/nodalida2009/>, the electronic publication was   available at <http://dspace.utlib.ee/dspace/handle/10062/9206> on   (date of conversion: 2025-12-31).)</span>   

**Authors:** Krister Lindén

University of Helsinki

Helsinki, Finland

  {<!-- tt -->Krister.Linden@helsinki.fi 
and


Tommi Pirinen

University of Helsinki

Helsinki, Finland

  {<!-- tt -->Tommi.Pirinen@helsinki.fi} }

**Date:** Last modification: (date of conversion: 2025-12-31)

<!-- begin document -->
<!-- make title -->

**Abstract:**
Finnish has a very productive compounding and a rich inflectional
system, which causes ambiguity in the morphological segmentation of
compounds made with finite state transducer methods. In order to
disambiguate the compound segmentations, we compare three different
strategies, which we cast in a probabilistic framework. We present a
method for implementing the probabilistic framework as part of the
building process of lexc-style morpheme sub-lexicons creating
weighted lexical transducers. To implement the structurally
disambiguating morphological analyzer, we use the <span style='font-variant: small-caps'>hfst-lexc</span>
tool which is part of the open source *Helsinki Finite-State
Technology*. This is the first time all three principles are cast
in a probabilistic framework and compared on the same corpus using
one tool. On our Finnish test corpus, the best method succeeds with
99,98 % precision and recall.
<!-- end abstract -->

## Introduction

In languages with productive multipart compounding, such as Finnish,
German and Swedish, approximately 9-10 % of the word tokens in a
corpus are compounds [(cites: hedlund/2002)](#hedlund/2002) and approximately 2/3 of the
dictionary entries are compounds, cf. a publicly available Finnish
dictionary [(cites: kotus/2007)](#kotus/2007).

There have been various attempts at curbing the potential
combinatorial explosion of segmentations that a prolific compounding
mechanism produces. Karlsson [(cites: karlsson/1992)](#karlsson/1992) showed that for
Swedish the most significant factor in disambiguating compounds was
the counting of the number of parts in the analysis, where the
analysis with the fewest parts almost always was the best
candidate. This has later been corroborated by others. In particular,
it was the main disambiguation criterion formulated by
[(cites: schiller/2005)](#schiller/2005) on German compounding. In addition, Schiller used
frequency information for disambiguating between compounds with an
equal number of parts. Schiller estimated her figures from compound
part frequencies, which requires a considerable amount of manual
labour in order to create the training corpora consisting of attested
compound words and their correct segmentations.

We suggest two modifications to the strategies of Karlsson and
Schiller. First we suggest that the word segment probabilities can be
estimated from non-compound word frequencies in the corpus. The
motivation for our approach is that compounds are formed in order to
distinguish between instances of frequently occurring phenomena and
therefore compounds are more often formed for more frequently
discussed phenomena. We assume that the frequency by which phenomena
are discussed is reflected in the non-compound word frequencies,
i.e. high-frequency words should in general have more compounds.

In addition, we suggest that the special penalty suggested by Karlsson
and maintained by Schiller is unnecessary when framing the problem in
a probabilistic framework. This has also been suggested by others, see
e.g. Marek [(cites: marek/2006)](#marek/2006). However, this is the first time the
disambiguation principles of Karlsson and of Schiller are compared
with a fully probabilistic approach on the same corpus.

Previously, there has been no publicly available general framework for
conveniently integrating both a full-fledged morphological description
and for representing probabilities for general morphological compound
and inflectional analysis. Karlsson [(cites: karlsson/1992)](#karlsson/1992) used
applied a post-processing phase to count the parts, and Schiller
[(cites: schiller/2005)](#schiller/2005) used the proprietary weighted finite-state compiler
of Xerox [(cites: kempe/2003)](#kempe/2003), which compiles regular expressions. We
therefore introduce the open source software tool
<span style='font-variant: small-caps'>hfst-lexc</span> (footnote: <http://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstLexC>),
which is similar to the Xerox lexc tool [(cites: beesley/2003)](#beesley/2003). In
addition to the fact that <span style='font-variant: small-caps'>hfst-lexc</span> compiles lexc-style
lexicons, it also has a mechanism for adding weights to compound parts
and morphological analyses.

The remainder of the article is structured as follows. In
Sections [(see: Sect1)](#Sect1) and [(see: Sect2)](#Sect2), we introduce a version of
Finnish morphology for compounding. In Section [(see: Sect3)](#Sect3), we
introduce the probabilistic formulation of the methods for weighting
the lexical entries. In Section [(see: Sect4)](#Sect4), we briefly introduce the
test and training corpora. In Section [(see: Sect5)](#Sect5), we present the
results. Finally, in Sections [(see: Sect6)](#Sect6), [(see: Sect7)](#Sect7) and
[(see: Sect8)](#Sect8), we give some notes on the implementation, discuss the
results and draw the conclusions.

## Inflection and Compounding in Finnish
<a id="Sect1">(¶ Sect1)</a>

In Finnish morphology, the inflection of typical nouns produces
several thousands of forms for the productive inflection. Finnish
compounding theoretically allows nominal compounds of arbitrary length
to be created from initial parts of certain forms of nouns, and the
final part inflects in all possible forms.

For example the compounds describing ancestors are compounded from
zero or more of *isän* ‘father <span style='font-variant: small-caps'>singular genitive</span>’ and
*äidin* ‘mother <span style='font-variant: small-caps'>singular genitive</span>’ and then one of any
inflected forms of *isä* or *äiti*, creating forms such as
*äidinisälle* ‘grandfather (maternal) <span style='font-variant: small-caps'>singular allative</span>’
or *isänisänisänisä* ‘great great grandfather <span style='font-variant: small-caps'>singular
nominative</span>’.  As for the potential ambiguity, Finnish also has the
noun *nisä* ‘udder’, which creates ambiguity for any paternal
grandfather, e.g. *isän\#isän\#isän\#isä*,
*isän\#isä\#nisän\#isä*, *isä\#nisä\#nisä\#nisä*, ...

However, much of the ambiguity in Finnish compounds is aggravated by
the ambiguity of the inflected forms of the head words. For example
*isän*, has several possible analyses,
e.g. <span style='font-variant: small-caps'>isä+sg+gen</span>, <span style='font-variant: small-caps'>isä+sg+acc</span> and <span style='font-variant: small-caps'>isä+sg+ins</span>.

Finnish compounding also includes forms of compounding where all parts of
words are inflected with same form, but this is limited to part of adjective
initial compounds. Similarly some inflected verb forms may appear as parts
of compounds. These both are more rare than nominal compounds [(cites: visk)](#visk)
and not considered in this paper.

## Morphological analysis of Finnish
<a id="Sect2">(¶ Sect2)</a>

Pirinen [(cites: pirinen/2008)](#pirinen/2008) presented an open source
implementation of a finite state morphological analyzer for Finnish.
We use that implementation as a baseline for the compounding analysis
as Pirinen’s analyzer has a fully productive compounding
mechanism. Fully productive compounding means that it allows compounds
of arbitrary length with any combination of nominative singulars,
genitive singulars, or genitive plurals in the initial part and any
inflected form of a noun as the final part.

The morphotactic combination of morphemes is achieved with sublexicon
combinatorics as defined in [(cites: beesley/2003)](#beesley/2003). We use the open source
software called <span style='font-variant: small-caps'>hfst-lexc</span> with a similar interface as the
Xerox lexc tool. The <span style='font-variant: small-caps'>hfst-lexc</span> tool includes preliminary
support for weights on the lexical entries.

In this implementation, each lexical entry constitutes one full word
form, i.e., we create a full form lexicon using the previously
mentioned analyzer [(cites: pirinen/2008)](#pirinen/2008). This creates a text file of 22
GB for the purely inflectional morphology of approximately 40 000
non-compound lexical entries for Finnish, which were stored in a
single CompoundFinalNoun lexicon as shown in
Figure [(see: fig:unweighted)](#fig:unweighted). The figure demonstrates an unweighted
lexicon and also shows how we model the compounding by dividing the
word forms into two categories: compound non-final (i.e., nominative
singular, genitive singular, and genitive plural) and compound final
forms allowing us to give weights to each form or compound part as
needed.


**Figure:**[htb]
<div style='font-size: small'>

```

LEXICON Root
## CompoundNonFinalNoun ;
## CompoundFinalNoun ;

LEXICON Compound
#:0 CompoundNonFinalNound "weight: 0" ;
#:0 CompoundFinalNound "weight: 0" ;

LEXICON CompoundNonFinalNoun
isä   Compound  "weight: 0" ;
isän  Compound  "weight: 0" ;
äiti  Compound  "weight: 0" ;
äidin Compound  "weight: 0" ;

LEXICON CompoundFinalNoun
isä:isä+sg+nom     ## "weight: 0" ;
isän:isä+sg+gen    ## "weight: 0" ;
isälle:isä+sg+all  ## "weight: 0" ;

LEXICON ##
## # ;

```

(Caption: Unweighted lexicon.
)<a id="fig:unweighted">(¶ fig:unweighted)</a>
</div>
<!-- end figure -->

Compounding implemented with the unweighted sublexicons in
Figure [(see: fig:unweighted)](#fig:unweighted) is equivalent to the original baseline
analyzer. The root sublexicon specifies that we can have start directly
from compound final noun forms, forming single part words, or start from
compound initial forms, forming multiword compounds. The compound initial
lexicon is a listing of all singular nominatives, singular genitives and
plural genitives, which is followed by compound boundary marker on in separate
sublexicon, and another word from either compound initial sublexicon or compound
final sublexicon. The compound final sublexicon contains the long listing of all
possible forms of all words, and their analyses, 

## Methodology  
<a id="Sect3">(¶ Sect3)</a>

We define the weight of a token through its probability to occur in
the corpus, i.e. we use the count,*c*, which is proportional to
the frequency with which a token appears in a corpus divided by the
corpus size, *cs*. The probability, *p(a)*, for a token,
*a*, is defined by Equation [(see: eqn:prob)](#eqn:prob).

<div style='font-size: small'>
  <div class='math'>
    <a id="eqn:prob">(¶ eqn:prob)</a>
    \mathrm{p}(a) = \mathrm{c}(a)/\mathrm{cs}
  </div>
</div>

Tokens known to the lexicon but unseen in the corpus need to be
assigned a small probability mass different from 0, so they get
*c(x) = 1*, i.e. we define the count of a token as its corpus
frequency plus 1 as in Equation [(see: eqn:count)](#eqn:count).

<div style='font-size: small'>
  <div class='math'>
    <a id="eqn:count">(¶ eqn:count)</a>
    \mathrm{c}(a) = 1 + \mathrm{frequency}(a)
  </div>
</div>

If a token, e.g. *isän*, has several possible analyses, e.g.
<span style='font-variant: small-caps'>isä+sg+gen</span> and <span style='font-variant: small-caps'>isä+sg+acc</span>, the total count for
*isän* will be divided among the analyses in a disambiguated
training corpus. If the disambiguation result removes all readings
<span style='font-variant: small-caps'>isä+sg+acc</span> from the disambiguated result, the count for this
reading is still 1 according to Equation [(see: eqn:count)](#eqn:count). We need the
total probability mass of all the tokens in the lexicon to sum up to
1, so we define the corpus size as the number of all lexical token
counts according to Equation [(see: eqn:corpussize)](#eqn:corpussize).

<div style='font-size: small'>
  <div class='math'>
    <a id="eqn:corpussize">(¶ eqn:corpussize)</a>
    \mathrm{cs} = \sum_{x} \mathrm{c}(x)
  </div>
</div>

To use the probabilities as weights in the lexicon we implement them in
the tropical semiring, which means that we use the negative
log-probabilities as defined by Equation [(see: eqn:logprob)](#eqn:logprob).

<div style='font-size: small'>
  <div class='math'>
    <a id="eqn:logprob">(¶ eqn:logprob)</a>
w(a) = -\mathrm{log}(p(a))
  </div>
</div>

For an illustration of how the weighting scheme is implemented in the
lexicon, see Figure [(see: fig:weighted1)](#fig:weighted1).


**Figure:**[htb!]
<div style='font-size: small'>

```

LEXICON Root
## CompoundNonFinalNoun ;
## CompoundFinalNoun ;

LEXICON Compound
0:# CompoudNonFinalNoun "weight: 0" ;
0:# CompoudFinalNoun "weight: 0" ;

LEXICON CompoundNonFinalNoun
isä   Compound  "weight: -log(c(isä)/cs)" ;
isän  Compound  "weight: -log(c(isän)/cs)" ;
äiti  Compound  "weight: -log(c(äiti)/cs)" ;
äidin Compound  "weight: -log(c(äidin)/cs)" ;

LEXICON CompoundFinalNoun
isä:isä+sg+nom     ## "weight:-log(c(isä+sg+nom)/cs)" ;
isän:isä+sg+gen    ## "weight:-log(c(isä+sg+gen)/cs)" ;
isälle:isä+sg+all  ## "weight:-log(c(isä+sg+all)/cs)" ;
isin:isä+pl+ins    ## "weight:-log(c(isä+sg+all)/cs)" ;

LEXICON ##
## # ;

```

(Caption: Structure weighting scheme using token penalties.
)<a id="fig:weighted1">(¶ fig:weighted1)</a>
</div>
<!-- end figure* -->

According to Karlsson [(cites: karlsson/1992)](#karlsson/1992) and
Schiller [(cites: schiller/2005)](#schiller/2005), we may need to ensure that the
weight of the compound segmentation *ab* of a word always is
greater than the weight of a non-compound analysis *c* of the
same word, so for compounds we use Equation [(see: eqn:compoundweight)](#eqn:compoundweight),
where *a* is the first part of the compound and *x* is the
remaining part, which may be split in to additional parts applying the
equation recursively.

<div style='font-size: small'>
  <div class='math'>
    <a id="eqn:compoundweight">(¶ eqn:compoundweight)</a>
w(ax) = w(a) + M + w(x)
  </div>
</div>

In particular, it is true that <span class='math'>w(ab) &gt; w(c)</span> if *M* is
defined as in Equation [(see: eqn:compoundweight2)](#eqn:compoundweight2).

<div style='font-size: small'>
  <div class='math'>
    <a id="eqn:compoundweight2">(¶ eqn:compoundweight2)</a>
M = -\mathrm{log}(1/(\mathrm{cs}+1))
  </div>
</div>

For an illustration of how a structure weighting scheme with compound
penalties is implemented in the lexicon, see
Figure [(see: fig:weighted2)](#fig:weighted2).


**Figure:**[htb!]
<div style='font-size: small'>

```

LEXICON Root
## CompoundNonFinalNoun ;
## CompoundFinalNoun ;

LEXICON Compound
0:# CompoundNonFinalNoun "weight: -log(1/(cs+1))" ;
0:# CompoundFinalNoun "weight: -log(1/(cs+1))" ;

LEXICON CompoundNonFinalNoun
isä   Compound  "weight: -log(c(isä)/cs)" ;
isän  Compound  "weight: -log(c(isän)/cs)" ;
äiti  Compound  "weight: -log(c(äiti)/cs)" ;
äidin Compound  "weight: -log(c(äidin)/cs)" ;

LEXICON CompoundFinalNoun
isä:isä+sg+nom     ## "weight:-log(c(isä+sg+nom)/cs)" ;
isän:isä+sg+gen    ## "weight:-log(c(isä+sg+gen)/cs)" ;
isälle:isä+sg+all  ## "weight:-log(c(isä+sg+all)/cs)" ;
isin:isä+pl+ins    ## "weight:-log(c(isä+sg+all)/cs)" ;

LEXICON ##
## # ;

```

(Caption: Structure weighting scheme using token and compound penalties.
)<a id="fig:weighted2">(¶ fig:weighted2)</a>
</div>
<!-- end figure* -->

In order to compare with the original principle suggested by
Karlsson [(cites: karlsson/1992)](#karlsson/1992), we create a third lexicon for which
structural weights are placed on the compound borders only, so for
compounds we use Equation [(see: eqn:compoundmaxweight)](#eqn:compoundmaxweight).

<div style='font-size: small'>
  <div class='math'>
    <a id="eqn:compoundmaxweight">(¶ eqn:compoundmaxweight)</a>
w(ax) = M + w(x)
  </div>
</div>

For an illustration of how a weighting scheme with the compound
penalty suggested by Karlsson is implemented in the lexicon, see
Figure [(see: fig:weighted3)](#fig:weighted3).


**Figure:**[htb!]
  <div style='font-size: small'>

```

LEXICON Root
## CompoundNonFinalNoun ;
## CompoundFinalNoun ;

LEXICON Compound
0:# CompoundNonFinalNoun "weight: -log(1/(cs+1))" ;
0:# CompoundFinalNoun "weight: -log(1/(cs+1))" ;

LEXICON CompoundNonFinalNoun
isä   Compound  "weight: 0" ;
isän  Compound  "weight: 0" ;
äiti  Compound  "weight: 0" ;
äidin Compound  "weight: 0" ;

LEXICON CompoundFinalNoun
isä:isä+sg+nom     ## "weight:-log(c(isä+sg+nom)/cs)" ;
isän:isä+sg+gen    ## "weight:-log(c(isä+sg+gen)/cs)" ;
isälle:isä+sg+all  ## "weight:-log(c(isä+sg+all)/cs)" ;
isin:isä+pl+ins    ## "weight:-log(c(isä+sg+all)/cs)" ;

LEXICON ##
## # ;

```

(Caption: Structure weighting scheme using compound penalties.
    )<a id="fig:weighted3">(¶ fig:weighted3)</a>
  </div>
<!-- end figure* -->


## Training and Test Data
<a id="Sect4">(¶ Sect4)</a>

For training and testing purposes, we use a compilation of three
years, 1995-1997, of daily issues of Helsingin Sanomat, which is the
most wide-spread Finnish newspaper. This collection contained
approximately 2.4 million different words, i.e. types. We
disambiguated the corpus using Machinese for
Finnish (footnote: Machinese is available from Connexor Ltd.,
www.connexor.com) which provided one reading in context for each
word based on syntactic parsing.

To create the test material from the corpus, we selected all word
forms with more than 20 characters for which our baseline analyzer
[(cites: pirinen/2008)](#pirinen/2008) gave a compound analysis, i.e. 53 270 types. Of
these, we selected the types which had a structural ambiguity and
found 4 721 such words, i.e. approximately 8.9 % of all the compound
words analyzed by our baseline analyzer. Of the remaining more than
20-character compounds 63.7 % contained no ambiguities or only
inflectional ambiguities. At most, the combination of structural and
inflectional ambiguities amounted to 30 readings in three different
words which after all is a fairly moderate number. On the average, the
structural and inflectional ambiguity amounts to 2.79 readings per
word. Examples of structurally ambiguous words are
*aktivointi\-mahdollisuuksien* with the ambiguity
*aktivointi\#mahdollisuus* ’of the opportunities to activate’ vs.
*akti\#vointi\#mahdollisuus* ’of the opportunities to act health’
and *hiihto\-harjoittelu\-paikassa* with the ambiguity
*hiihto\#harjoittelu\#paikka* ’in the ski training location’
vs. *hiihto\#harjoittelu\#pai\#kassa* ’ski training pie cashier’.

The characteristics of all the compounds in the corpus is presented in
Table [(see: tab:compounds)](#tab:compounds).


**Table:**[htb!]
  <div style='font-size: small'>


| ---- | ---- | ---- | ---- | ---- | ---- |
| | <!-- FIXME: multicolumn 3 c -->{\# of Characters}  |  | <!-- FIXME: multicolumn 3 c -->{\# of Segments} |
| Min.  |   Max.  |   Avg.  |  Min.  |  Max.  |  Avg. |
| 2  |  44  |  15.34  |  2  |  6  |  2.19 |

(Caption: Evaluation of compounds, segments and readings.
    )<a id="tab:compounds">(¶ tab:compounds)</a>
  </div>
<!-- end table -->

Examples of six-part compounds are:

*  *elo\#kuva\#teat\-teri\#tuki\#työ\#ryhmä* 

’movie theater support workgroup’ 
*  *jatko\#koulu\-tus\#yhteis\#työ\#toimi\#kunta* 

’higher education cooperation committee’
*  *lähi\#alue\#yhtei\#työ\#määrä\#raha* 

’regional cooperation reserve’


The longest compounds found in the corpus is
*liiken\-ne\#turval\-lisuus\#asiain\#neuvot\-telu\#kunnassa* ’in the road
safety issue negotiating committee’

## Tests and  Results
<a id="Sect5">(¶ Sect5)</a>

We estimate the probabilities for the non-compound words in the 1995
part of the corpus. Since we do not use the compounds for training we
can test on the compounds of all three years.

We evaluated the weighting schemes described in Section [(see: Sect3)](#Sect3),
i.e. the probabilistic method without compound boundary weighting, the
probabilistic method combined with compound weighting and the
traditional pure compound weighting. The precision and recall is
presented in Table [(see: tab:results)](#tab:results). Since we only took the first of
the best results, the precision is equal to recall.


**Table:**[htb!]
  <div style='font-size: small'>


| ---- | ---- | ---- | ---- | 
| Parameters  |  Precision |
| Only compound penalty  |  99.94 % |
| Compound penalty and prefix weights  |  99.98 % |
| No compound penalty and prefix weights  |  99.98 % |

(Caption: Precision equals recall for the test results when we use
only the first result.
    )<a id="tab:results">(¶ tab:results)</a>
  </div>
<!-- end table -->

## Implementation Note
<a id="Sect6">(¶ Sect6)</a>

In <span style='font-variant: small-caps'>hfst-lexc</span>, we use OpenFST [(cites: openfst/2007)](#openfst/2007) as the underlying
finite-state software library for handling weighted finite-state
transducers. The estimated probabilities are encoded as weights in the
tropical semiring, see [(cites: mohri/1997)](#mohri/1997). To extract the n-best
results, we use a single-source n-best paths algorithm, see
[(cites: mohri/2002)](#mohri/2002).

## Discussion and Further Research
<a id="Sect7">(¶ Sect7)</a>

Previous results for structural compound disambiguation for German
using word probabilities and compound penalties [(cites: schiller/2005)](#schiller/2005) or
using only word probabilities [(cites: marek/2006)](#marek/2006) also achieved results
with precision and recall in the region of 97-99 %. In German the
ambiguities of long compounds may produce even 120 readings, but on
the average the ambiguity in compounds is between 2-3 readings
[(cites: schiller/2005)](#schiller/2005), which is on par with the ambiguity of 2.8
readings found for long Finnish compounds. As pointed out initially
[(cites: hedlund/2002)](#hedlund/2002), the amount of compounds occurring in Finnish,
Swedish and German texts is also on a comparable level.

If a disambiguated corpus is not available for calculating the word
probabilities, using only the structural penalties may still be an
acceptable replacement in Finnish. However, we need to note, that a
similar strategy in German, i.e. using only compound penalties on all
compound prefixes, did not seem to perform as well
[(cites: schiller/2005)](#schiller/2005). This may be due to the fact that German contains a
high number of very short one-syllable words which interfere with the
compounding, whereas Finnish is more restricted in the number of short
words. Scandinavian languages are similar to German in that they have
a number of short one-syllable nouns. Using probabilistic approach with
swedish compound disambiguation is demonstrated in [(cites: sjobergh/2004)](#sjobergh/2004),
which shows results of 86 % accuracy of compound segmenting when using
compound component frequencies and 90 % for number of compound components.
However, it is a question for
further research whether a pure probabilistic approach could fare as
well for Scandinavian languages.

## Conclusions
<a id="Sect8">(¶ Sect8)</a>

For Finnish, weighting compound complexity gives excellent results
around 99.9 % almost regardless of the approach. However, from a
theoretical point of view, we can still verify the two hypotheses we
postulated initially. Most importantly, there seems to be no need to
extract the counts from lists of disambiguated compounds, i.e., it is
quite feasible to use general word occurrence probabilities for
structurally disambiguating compounds. In addition, we can also
corroborate the observation that when using word probabilities, it is
possible to forego a specific structural penalty and rely only on the
word probabilities. From a practical point of view, we introduced the
open source tool, <span style='font-variant: small-caps'>hfst-lexc</span>, and demonstrated how it can be
successfully used to encode various compound weighting schemes.

## Acknowledgments

This research was funded by the Finnish Academy and the Finnish
Ministry of Education. We are also grateful to the HFST-Helsinki
Finite State Technology research team and to the anonymous reviewers.

<!-- bib style: unsrt -->
# References

* <a id="hedlund/2002">**hedlund/2002**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="kotus/2007">**kotus/2007**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="karlsson/1992">**karlsson/1992**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="schiller/2005">**schiller/2005**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="marek/2006">**marek/2006**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="kempe/2003">**kempe/2003**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="beesley/2003">**beesley/2003**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="visk">**visk**</a>:
    * crossref: hakulinen2008iso
* <a id="pirinen/2008">**pirinen/2008**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="openfst/2007">**openfst/2007**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="mohri/1997">**mohri/1997**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="mohri/2002">**mohri/2002**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="sjobergh/2004">**sjobergh/2004**</a>:
    * error: <strong style="color: red">missing from bibs</strong>


<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

