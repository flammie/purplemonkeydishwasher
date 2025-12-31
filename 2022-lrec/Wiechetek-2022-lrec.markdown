













\lstset{language=,
extendedchars = true,
mathescape = false,
basicstyle=<!-- footnotesize -->\ttfamily,
keywordstyle=<!-- footnotesize -->\color{blue}\ttfamily,
}




\newcommand{\secref}[1]{\StrSubstitute{\getrefnumber{#1}}{.}{ }}



<!-- set length \belowcaptionskip -10pt -->
<!-- set length \abovecaptionskip 1pt -->



<!-- begin document -->

# Unmasking the Myth of Effortless Big Data — 
 Making an Open Source Multilingual Infrastructure and Building Language Resources from Scratch¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: LREC is open access with CC-BY-NC licence. Print version can be found at <https:/2022.lrec-conf.org/>)</span>



**Authors:** 
Linda Wiechetek 
and


Katri Hiovain-Asikainen 
and


Inga Lill Sigga Mikkelsen 
and


Sjur N. Moshagen 
and


Flammie A. Pirinen 
and


Trond Trosterud 
and


Børre Gaup

Department of Language and Culture, UiT the Arctic University of Norway 

giellalt@uit.no





**Abstract:***Machine learning* (ML) approaches have dominated *Natural
Language Processing* (NLP) during the last two decades.  From machine
translation and speech technology, machine learning tools are now also in use
for spellchecking and grammar checking, with a blurry distinction between the
two.

We unmask the myth of effortless big data by illuminating the efforts and time
that lay behind building a multi-purpose corpus with regard to collecting,
marking up and building from scratch.  We also discuss what kind of language
technology tools minority language communities actually need, and to what extent
the dominating paradigm has been able to deliver these tools.  In this context
we present our alternative to corpus-based language technology—knowledge-based
language technology—and we show how this approach can provide
language technology solutions for languages being outside the reach of machine
learning procedures.  We present a stable and mature infrastructure
(*GiellaLT*) containing more than hundred languages and building a number
of language technology tools that are useful for language communities.  

\newline *keywords:* infrastructure, corpus, text processing, minority languages,
finite state technology, knowledge-based nlp, grammar checking, TTS, ASR, speech
technology, spellchecking}



<!-- make title -->

## Introduction





During the last two decades, i.e. early 2000s, machine learning approaches have
dominated the field of *natural language processing* (NLP). The
philosophy has been to have machines learn behaviour from large corpora, thereby
offering speech technology, machine translation and spelling and grammar
checking.

For at least 3/4 of the world’s languages, this is bad news. They have less than
20,000 speakers, and even with a school system teaching mother tongue literacy
and a language policy encouraging publishing, such small populations would have
a hard time producing enough text to be able to model the language in a reliable
way using the dominating NLP paradigm. On top of that, weak literary traditions
give rise to corpora too unreliable to be able to function as a model for NLP
tools.

From the reactions we get on our work in the current academic NLP community
contexts, we experience an absence of understanding for why we choose to work
rule-based, despite our explanations of unavailable noise-free data. There seems
to be the idea that big data comes for free.  In addition, since most of the
work within the dominating methodology is done on morphologically simple
languages, there seems to be a general lack of understanding of the
methodologies and technologies needed to work efficiently with polysynthetic and
other morphologically complex languages.

This article has a clear answer to the big data question — corpus data does
not come for free, as illustrated in the three test cases we present. Building
corpora requires proficient writers or speakers of the language. In addition, it
requires proof-readers, translators and experts who can mark up the texts with
regard to errors or other traits of the text. While these may be available for
some languages before developing language tools, many languages need to build
them from scratch.

However, there is a way to produce the NLP tools needed by the language
community without Big Data. We show how a set of knowledge-based methods is able
to analyse and generate morphologically complex languages reliably, as well as a
language-independent infrastructure that makes it possible to share
developmental costs among the languages involved.

We have within 20 years built language resources for several Sámi languages from
scratch—this includes lexica, morphological and syntactic analysers.  Even
though we had a number of non-digital resources available, these were far from
exhaustive. This means that our work also included normative discussions,
requests and suggestions to the language normative organs, error
classifications, grammatical descriptions of phenomena not included in grammar
books. In several cases, these phenomena needed traditional linguistic research.

We argue that both a functioning literacy and thereby also corpus-based
approaches are dependent upon rule-based tools of the type produced via our
approach.























## Background<a id="sec:background">(¶ sec:background)</a>





















### What does the language community need?

At present, several minority language communities with a weak literary tradition
try to strengthen the position of the language in society.  In doing so, they
find themselves in a situation lacking the infrastructure needed to do so,
infrastructure that majority language speakers take for granted.

Looking at the writing process, there must be a keyboard layout. Most
orthographies contain letters outside the A-Z (or Cyrillic А-Я) range, these
letters must be placed on the keyboard in ergonomically sound positions. Layouts
should be easy to install on the operating systems on both computers and mobile
devices.

In order to produce text with a consistent spelling in an efficient way, the
language community will need a spelling checker. Since there are few proofread
texts, a spelling checker can not be made by learning from an existing corpus.
Not only will the existing corpora be too small, they will typically also be too
unreliable. With a weak literary tradition, text often deviates from the norm,
and the existing body of text thus can not be taken as a substitute for an
explicit norm.

Language communities wanting to strengthen their language do not start from
scratch. In practice, the languages of such communities have already been
described to a certain extent. Given the present state of linguistic typology
research, there will in all relevant cases be scholars devoted to the language,
who have made dictionaries covering the core vocabulary and a basic grammar. In
order to teach the language to new speakers and to publish texts, the language
will still need a practical orthography, an orthography with design principles
radically different from the ones used by philologists and typologists. Making a
good practical orthography and rewriting the philologists’ grammars and
dictionaries by using this orthography is at the core of the language planning
process.

Machine translation into a minority language is of no use when the output is
unreliable and the language community bilingual, thus in a position to choose
the majority language original instead. Translation from the minority language
is of no use if there is no monolingual text to translate.






Based upon experience with around 50 language models (cf.
*[giellalt.github.io](https://giellalt.github.io/LanguageModels.html)*)
we found that if the lexicon is electronically available and the grammatical
structure reasonably clear, a grammatical model covering around 80 \



### Related work<a id="sec:relwork">(¶ sec:relwork)</a>


Several studies discuss key aspects of the infrastructure presented here,
e.g. [(cites: pirinen2021building)](#pirinen2021building), [(cites: moshagen2013building)](#moshagen2013building).  We are not
aware of too many similar open source infrastructures that contain both the same
amount of languages and different end user applications that actually work. One
example is the rule-based machine-translation system
Apertium [(cites: khanna2021recent)](#khanna2021recent) that hosts repositories for language resources
for 51 machine translators. In addition to containing machine translation pairs
in use in different practical applications, the language models underlying them
may also be used for a wide range of applications. As a part of the
*GiellaLT* infrastructure work we have made a pipeline for including our
language models in the *Apertium* pipeline, our MT programs are thus made
using the *Apertium* formalism.


The producers of statistical and corpus-based models have also started to gather
their data and models into larger multilingual repositories. If we try to draw
parallels, for example within the recent neural models, one could compare our
repository to the likes of
*[huggingface.co](https://huggingface.co)* that hosts a repository
of language models and APIs to access them [(cites: wolf2020transformers)](#wolf2020transformers). However,
they are still mainly targeting English and a handful of well-resourced
languages, and while a number of lower-resourced languages are provided with
models and data, the data seems to be very limited.  In speech technology and
corpora, there is also the common voice project from Mozilla that gathers speech
resources for multiple languages [(cites: ardila2019common)](#ardila2019common), and eventually
provides spoken language models.


























## A multilingual infrastructure from scratch<a id="sec:infra">(¶ sec:infra)</a>

In this article, we will assume that the basic language planning work has been
done and that there is a practical orthography and access to the lexicon of the
language in machine-readable format and a basic grammar. This description holds
for a large group of languages that still have no language technology tools in
place.


















### The *GiellaLT* infrastructure

The foundation for the work presented in this article is the multilingual
infrastructure *[GiellaLT](https://github.com/giellalt)*, which
includes numerous languages — 130 altogether — that have little or no data,
a rare case in the NLP world.

Everything produced in the *GiellaLT* infrastructure is under free and
open licences and freely available.  The corpora are available with free
licensing where possible.  The infrastructure is split code-wise in three GitHub
organisations: *[GiellaLT](https://github.com/giellalt)* containing
the language data for each language,
*[Divvun](https://github.com/divvun)* containing language
independent code for the infrastructure, and
*[Giellatekno](https://github.com/giellatekno)* for corpus
infrastructure.  End user tools served by the Divvun group are at
*[divvun.no](https://divvun.no)* \&
*[divvun.org](https://divvun.org)*, and tools served by the
Giellatekno group at
*[giellatekno.uit.no](https://giellatekno.uit.no)*, both at
*UiT—Norway’s Arctic University*.

We build systems that include lexical data as well as rules governing
morphophonology, syntax and semantics as well as a number of application
specific information, e.g. grammatical rules for grammar checking, phonetic
rules for *Text-To-Speech* (TTS) and so forth.

The language-independent work is currently done within the infrastructure, the
language-independent features and updates that are relevant to all languages are
semi-automatically merged as they are developed.  To ensure that language
independent and common features and updates do not destroy existing language
data or use case, we enforce a rigorous continuous integration based testing
regime.  The current system for testing is a combination of our long-term
investment in testing within the infrastructure locally for
developers—combined with modern automatic testing currently supplied by
[GitHub actions](https://github.com/divvun/actions).

Another part of the *GiellaLT* philosophy is that of reusable and
multi-purposeful resources, cf. [(cites: antonsen2010reusing)](#antonsen2010reusing). This is
true for all of our work, from corpus collection to cross-lingual cooperation.

Despite the lack of data, there are high-level tools in *GiellaLT* such
as machine translation, TTS, spelling and grammar checkers and more, that have
been very well received in the language communities. This would not have been
possible without first developing basic tools such as keyboards, morphological
analysers and spelling checkers.





### Keyboards

To be able to type and write a language, you need a keyboard. Using the tool
`[kbdgen](https://github.com/divvun/kbdgen)`, one can easily specify
a keyboard layout in a *[YAML](https://yaml.org)* file, mimicking
the actual layout of the keyboard. The listing below shows the definition of the
Android mobile keyboard layout for Lule Sámi. The `kbdgen` tool takes
this definition and a bit of metadata, combines it with code for an Android
keyboard app, compiles everything, signs the built artefact and uploads it to
the Google Play Store, ready for testing.



```
[frame=single]
modes:
android:
default: |
á w e r t y u i o p å
a s d f g h j k l ø æ
z x c v b n m ŋ

```













The tool supports generating keyboard apps or installer packages for Android,
iOS, macOS, Windows, Linux (X11 and m17n) and Chrome OS. There is also
experimental support for generating
[*Common Language Data Repository](https://cldr.unicode.org) (CLDR)*
XML files, *Scalable Vector Graphics* (SVG) files for fast layout
debugging, and finite state transducers for neighbour key mistyping error
models. The Windows installer includes a tool to register unknown languages, so
that even languages never seen on a Windows computer will be properly
registered, and thus making it ready to support proofing tools and other
language processing tools.




### Morphological analysers<a id="section.morphanalysis">(¶ section.morphanalysis)</a>

The foundation for all linguistic processing in the *GiellaLT*
infrastructure is the morphological analyser, built using formalisms from Xerox:
`lexc`, `xfst` and optionally `twolc`. From these source
files, the infrastructure creates ¸*finite state transducers* (FST’s)
using one of three supported FST compilers: Xerox
tools [(cites: beesley2003finite)](#beesley2003finite),
*[HFST](https://hfst.github.io)* [(cites: linden2013hfst)](#linden2013hfst), or
Foma [(cites: hulden2009foma)](#hulden2009foma).



All language models are written as rule-based, full form lexicons with explicit
morphological descriptions and morphophonological alternations. This makes it
possible to create language models for any language, including minority and
indigenous languages with no digital presence, as long as there is cooperation
with the language community and native speakers.

Support for multiple usages and reuse of the same lexical data is added through
analyser tags, so that the compiled FST can be filtered and manipulated to fit a
specific usage scenario.




### Morphological and syntactic disambiguation and tagging

All higher-order linguistic processing is done using the VISLCG3
(*[visl.sdu.dk](http://visl.sdu.dk)*)
implementation [(cites: Didriksen2016constraint)](#Didriksen2016constraint) of Constraint
Grammar [(cites: karlsson1990constraint)](#karlsson1990constraint).

It has over the years proven both robust, fast and flexible, allowing rule-based
morphological disambiguation, as well as syntactic and semantic tagging, cf.
Table [(see: samiPR)](#samiPR). It has also successfully been applied in high-quality
grammar checker applications and machine translation systems, and is often used
to create the reference tagged corpus used to train machine learning models.
Ambiguity in the Sámi languages is mostly based on homonymy between
morphological forms of the same part of speech, and less on PoS homonymy between
uninflected lemmata.


**Table:**[htb]
<div style='text-align: center'>


| ****  |  | <!-- FIXME: multicolumn 2 |c| -->{**North Sámi**}  | 
| <!-- FIXME: multicolumn 2 |c| -->{**Lule Sámi**} |
| ****  |  **Prec**  |  **Recall**  |  **Prec**  |  **Recall** |
| **PoS**  |  0.99  |  0.99  |  0.94  |  0.97 |
| **morph. dis.**  |  0.93  |  0.95  |  0.83  |  0.94 |
| **dependencies**  |  1  |  1  |  1  |  1 |


(Caption: North and Lule Sámi analysers.<a id="table:anlyserpr">(¶ table:anlyserpr)</a>)<a id="samiPR">(¶ samiPR)</a>
</div>
<!-- end table -->


### Tokenisers

Tokenisation is based on an FST model initially presented by
[(cites: karttunen2011beyond)](#karttunen2011beyond) in the Xerox tool `pmatch`. The resulting
FST is applied using `hfst-tokenise`.  The basic idea is to use an FST as
a pattern matching tool for natural languages, and add markup to the input text
for matching patterns. The FST is used as a tokeniser in a left-to-right,
longest-match manner.  The tokeniser performs tokenisation and analysis in one
go and can handle both known and out-of-vocabulary items.  Secondly, the
formalism has been extended with explicit backtracking functionality, to allow
for multiple tokenisations.

The output of ambiguous tokens is disambiguated using linguistic rules with
VISLCG3 to specify the correct tokenisation given the context and the available
linguistic analyses. This makes it possible to achieve near-perfect
tokenisation.  In our tokenisation, sentence boundary detection is treated as a
special case of ambiguous tokenisation, and solved in the same way, approaching
near-perfect sentence boundary identification, cf.
[(cites: wiechetek-etal-2019-seeing)](#wiechetek-etal-2019-seeing).



### Spelling checkers

As mentioned briefly above in Section [(see: section.morphanalysis)](#section.morphanalysis), in the
*GiellaLT* infrastructure a descriptive language model can be turned into
a normative one by way of FST filtering: removing all strings tagged as
non-normative. This makes it easy to create acceptors for spelling checkers.
Modelling typical spelling errors is also done using FST’s, with a default setup
that should give reasonable suggestion quality out of the box, but with great
flexibility and possibilities for fine-tuning and alternative ways of building
error models.

The *GiellaLT* infrastructure also includes a fast implementation of a
speller engine using FST’s (the acceptor and the error model), and integration
with the most popular operating systems and office packages. Combined with a
distribution and update tool called
*[pahkat](https://github.com/divvun/?q=pahkat)* as well as
continuous integration and delivery, it is possible to develop, test and deliver
spellers to the language community with very short cycles. This allows for a
good feedback cycle between the language community and the developers of the
spelling checker, where the community members can see that their feedback is
acted upon, and new updates available in short time.


The rule-based framework allows building high quality spellers even without
digital data resources. It should also be pointed out that reusing a language
model as a spelling checker would not have been possible using a non-rule-based
framework.



### Grammar checkers

Since 2019 the *GiellaLT* infrastructure supports building grammar
checkers [(cites: Wiechetek2019many)](#Wiechetek2019many).  The grammar checker setup is chaining together
several of the modules described above into a pipeline, roughly as follows:
`tokenisation \& analysis` ⇒ `*Multiword expression` (MWE)
disambiguation* ⇒ `spellchecking of unknowns` ⇒ `disambiguation` ⇒
`error detection` ⇒ `error correction`. The main technologies used
are `hfst-tokenise`, VISLCG3 and our spelling checkers.

Evaluations of different error types show good results of the North Sámi grammar
checker *GramDivun*. Compound error correction reaches a precision of
81.0 Regression tests give up to 88.8 The framework for the grammar checker is
Constraint Grammar [(cites: karlsson1990constraint,Didriksen2016constraint)](#karlsson1990constraint,Didriksen2016constraint).
Constraint Grammar as a rule-based approach is a very good fit as it

allows partial parses, unfinished disambiguation, and is robust against
remaining ambiguities. In addition, the rule-based approach makes it possible to
build grammar checkers for languages with no or very little digital resources.

### Machine translation

Another high-level tool available within the *GiellaLT* infrastructure is
machine translation. It works in cooperation with the
*[Apertium](https://github.com/apertium)*
infrastructure [(cites: khanna2021recent)](#khanna2021recent), which is also largely rule-based and
FST-based. The monolingual resources are developed within the *GiellaLT*
infrastructure, using the same morphological analysers as for other tools, but
slightly tweaked to match the requirements in Apertium. The output is a set of
FST’s made available to Apertium, which contain the bilingual resources for a
given language pair.

This has resulted in systems with Word Error Rates as good as 0.11 (cf.
[(cites: antonsen2017machine)](#antonsen2017machine), for North to Inari Sámi). The North Sámi to Norwegian
*Machine Translation* (MT) system delivers close to 1,000 translations a
day (footnote: [jorgal.uit.no/](http://jorgal.uit.no/). The system is
documented at
[giellalt.github.io/mt/MachineTranslation.html](https://giellalt.github.io/mt/MachineTranslation.html).)
(cf. [(cites: Antonsen2020samiske[p. 60])](#Antonsen2020samiske)).


## Corpus — Three test cases<a id="sec:cases">(¶ sec:cases)</a>

This section deals with building and handling corpus in the *GiellaLT*
infrastructure. The question of big data is usually not addressed in articles
that use the data for their machine learning approaches without creating the
data.  However, when calculating time-efficiency of the approach, this should be
part of the equation.  With our three test cases, we illuminate the actual work
behind an adequate corpus for a certain tool and the challenges behind the
corpus work.  Building a corpus with good quality requires selecting native
language texts from different domains, marking up a corpus to make it multi-use,
and also building a special-purpose corpus (i.e. for speech technology) from
scratch.










### Collecting corpus texts

With our infrastructure, it is possible to build tools without corpora but with
the help of native speakers. With curated corpora, we can verify that our tools
work on a wide range of real-world linguistic phenomena.

We have collected corpora for five of the Sámi languages: North, Lule, South,
Inari and Skolt Sámi as well as for 13 other circumpolar languages. The Sámi
corpus is owned by the Norwegian Sámi parliament, and all corpora are
administered and made accessible to the public by the Divvun and Giellatekno
groups.  The corpora are split in two based on restrictions set by the copyright
owners. Researchers and anyone else can freely download the free part. The whole
corpus, also the restricted part, is accessible via a public search
interface (footnote: [gtweb.uit.no/korp](https://gtweb.uit.no/korp) (Sámi),
[gtweb.uit.no/f\_korp](https://gtweb.uit.no/f_korp) (Baltic Finnic and
Faroese), [gtweb.uit.no/u\_korp](https://gtweb.uit.no/u_korp) (other Uralic
languages). Cf. also
[More info about
the corpora.](https://giellalt.github.io/ling/corpus_repositories.html)).  We have written a tool named
[CorpusTools](https://github.com/giellalt/CorpusTools) to administer,
convert and analyse the corpus texts. Original texts and their metadata are
saved in svn repositories, then converted to a common XML format, to ease
further use of the texts.



Texts in Sámi languages are published daily in both media and by public bodies
required to communicate in writing in Sámi. We have written crawlers to ease the
collection of and to maintain consistent metadata about these texts. The
crawlers gather parallel language versions from those sites that have
unambiguous links to such data. Since most of the publishers (typically online)
have to provide their site in both Sámi and the majority languages, and they
provide interlinks between these page, we are able to build up a rather
comprehensive parallel corpus, as well.

Having gathered text since 2005, the largest Sámi corpus is the one for North
Sámi, with 38.94 million tokens. The four other Sámi corpora all contain less
than 3 million words.

The North Sámi corpus is a quite big corpus for an indigenous language, but
small compared to majority languages. The respective majority language corpora
contain 18.4 billion words (Norwegian), 13.9 billion tokens (Swedish) and 14.1
billion words (Finnish) (footnote: For Norwegian, see
[(cites: kummervold-etal-2021-operationalizing)](#kummervold-etal-2021-operationalizing), which presents the corpus
underlying a language model for Norwegian. The Swedish and Finnish corpora are
searchable at [spraakbanken.gu.se/korp](https://spraakbanken.gu.se/korp)
and [korp.csc.fi/korp/](https://korp.csc.fi/korp/), respectively.).  It
goes without saying that corpora containing billions of words offer
possibilities not available to corpora containing millions of words or even
less.

This does not mean that smaller corpora are not useful. To the contrary,
[(cites: Antonsen2020samiske)](#Antonsen2020samiske) show that the South and Skolt Sámi language
communities (constituting less than 500 speakers each) over a 3-month period via
a dictionary interface accessed their respective corpora (containing 1.5 and 0.2
million words, respectively) 47,000 times each. The language community sees the
corpora as useful, despite their small size.















We would also like to have a balanced corpus with regard to regional dialects of
the same language. The Sámi languages have a stronger legal protection in Norway
than in Sweden, our corpus therefore consist of more text written in Norway than
in Sweden. This has consequences for some of the tools we are developing, quite
clearly for translation memory, but also to some extent for other types of tools
such as TTS.




For North Sámi and Norwegian, we have managed to build a parallel corpus
containing 3.9 million words. For the other Sámi languages, the corresponding
pairs contain 230,000 words or fewer. These corpora mainly contain
administrative texts. They may be used as a foundation for vocabulary
development, using word alignment methods developed for phrase-based machine
translation, [(cites: Gerstenberger2013digging)](#Gerstenberger2013digging) or as a source for dictionary
examples {[(cites: Antonsen2020samiske)](#Antonsen2020samiske)}.






### Corpus mark-up — upgrading a corpus

The next step towards corpus-assisted NLP is its refinement.  When we want to
use a corpus for specific tasks, underlying structures need to be made
accessible in addition to raw text. This can be part-of-speech, morphological,
syntactic, semantic, pragmatic information on the one hand, and error mark-up
together with error categorisation and correction, on the other hand.

The approaches for these two are contrastive. Part-of-speech (PoS),
morphological, syntactic and semantic mark-up is done automatically by our
rule-based FST and Constraint Grammar analysers and made available to the
language community in the online application *Korp*.  The error mark-up
is done manually serving as a database for testing and evaluating the quality of
our spellcheckers and handwritten grammar checker rules.

The earliest manual error mark-up started in 2006 and served as unseen test data
for Lule and North Sámi spellers.  It was further used to automatise
spellchecker testing for Greenlandic, Icelandic, and South Sámi.
[(cites: Moshagen2008language)](#Moshagen2008language) describes an initial testbench for spellcheckers, and
[(cites: Antonsen2012improving)](#Antonsen2012improving) takes a first step towards a grammar checker testbench by
adding mark-up of real word errors in addition to non-word spelling errors (i.e.
errors that require syntactic context).  The L2 corpus of North Sámi has 4,633
words, 800 sentences, 739 misspellings.


Today’s version of the marked-up North Sámi corpus (*ErrMark-SIKOR*) has
182,450 words and contains mostly administrative and news texts, but also a bit
of fiction and the previously mentioned L2 corpus. However, as the rest of the
corpus, it is enhanced by error mark-up for grammatical and formatting errors in
addition to spelling errors.




Alternatively, synthetic errors can be created if larger corpora are needed,
e.g. to train neural networks for e.g. grammar checking
modules. [(cites: wiechetek-etal-2021-rules)](#wiechetek-etal-2021-rules) For a synthetically created corpus
with congruence errors for a neural-network based grammar checker, we generated
20,846,804 sentences and 2,551,236,949 words.  The problematic part with a
synthetic corpus is that we cannot rely on it. For the previously mentioned
corpus, even though synthetic errors were inserted carefully (correct forms
replacing incorrect), unexpected homonymies or unclear contexts can lead to the
inserted forms still being correct. This can only be discovered by manual checks
or a rule-based grammar checker.  Another problematic issue is that the corpus
will not reflect the actual distribution of errors made in the real world.







The Lule Sámi corpus mark-up started in 2013 with 29,527 words of unpublished
native speakers texts, with 1,505 non-word errors.  With a multi-use in mind,
this corpus was proofread and marked up with other error types including 1,322
morpho-syntactic, syntactic and lexical errors.



The texts had neither been spellchecked nor proofread. The large part of errors
(altogether 2,827) is probably due to the young written tradition. A standard
had first been established in 1983 [(cites: magga1994hvordan)](#magga1994hvordan).  This also illustrates the
urgent need for spelling and grammar aiding tools developed within
*GiellaLT*.





A systematic error mark-up has originally been developed for spellchecking, but
then been extended to grammatical error mark-up, formatting, punctuation and
more. The goal behind it is the development of a machine-readable multi-purpose
corpus without changing its originality.  Important principles are, therefore,
consistent mark-up (in terms of range and error type) and compatibility with our
tools. That means, for example, that if we have listed a lexical item as a
multi-word, we also need to mark it up as a multi-word.




The error mark-up syntax follows a number of
guidelines (footnote: [giellalt.uit.no/proof/spelling/testdoc/error-markup.html](https://giellalt.uit.no/proof/spelling/testdoc/error-markup.html)) [(cites: moshagen2014test)](#moshagen2014test)
and applies eight different general error types: orthographic, real word,
morpho-syntactic, syntactic, lexical, formatting, foreign language and
unclassified errors.  The error is enclosed in curly brackets, followed by its
correction in another set of curly brackets.  The second curly bracket may or
may not include a part-of-speech, morpho-syntactic criteria and a
subclassification of the error type.

*Orthographic errors* include non-words only. They are misspellings
confined to single (error) strings, and the traditional speller should detect
them.

*Real word errors* are misspellings that cannot be detected by a
traditional speller, they are seen as errors due to the context in which they
occur.

*Morpho-syntactic errors* are case, agreement, tense, mode errors. They
require an analysis of (parts of) the sentence to be detected.

*Syntactic errors* (marked by ¥) require a partial or full analysis
of (parts of) the sentence. They include word order errors, compound errors,
missing words, and redundant words.

*Lexical errors* include wrong derivations.

*Foreign language* includes words in other languages that do not require a
correction.  *Formatting errors* include spacing errors in combination with
punctuation.


In ex. [(see: illajahkken)](#illajahkken), the syntactic error is a missing word and the
correction is adding the subjunctive *ahte* ‘that’.

**Linguistic example group:**

Illá \{jáhkken\}<span style='color: red'>¥\{missing<span class='math'>|</span>jáhkken ahte\</span>} lei
duohta.<a id="illajahkken">(¶ illajahkken)</a>

hardly think<span style='font-variant: small-caps'>.past.1sg</span> be<span style='font-variant: small-caps'>.past.3Sg</span> true

‘I hardly thought that it was true.’

Regarding the span of an error, we typically mark as little as possible, even if
larger parts of the sentence are responsible for the identification of the
error.

This is done to facilitate matching error mark-up with grammar checker marking
of the error, and it has a direct effect on automatic evaluation.  Most of the
frameworks we use to process language material in context, e.g. Constraint
Grammar, take a token-based approach to language processing, and therefore
marking several words can get cumbersome and should be avoided if possible.







The marking of errors has had consequences beyond of what we had originally
envisioned.  Not only has it resulted in a corpus that can be used in automatic
evaluation of our tools, it has also forced us to categorise errors according to
the underlying principles of the spelling and grammar checker, which had not
necessarily been the same ones a linguist would see in the first place. It
became apparent that grammatical errors marked-up before we started working on a
grammar checker needed to be recategorised, and their span needed to be
shortened.  The biggest challenge in marking up a corpus has been consistency,
i.e. the same type of error should always be marked in the same way. In
addition, marking errors should follow the same pattern in all languages in the
*GiellaLT* infrastructure.  The mark-up process resulted in an overview
of challenges native speakers have with the written languages, which can help to
improve literacy education in school [(cites: Antonsen2012improving)](#Antonsen2012improving).  It also
revealed where the written language lacks writing rules and norms, which could
then be passed on to *Giellagálldo*, the normative organ for the Sámi
languages.






### Speech corpora and Text-To-Speech


A TTS tool is made to be able to synthesise intelligible speech output from any
unseen text input in a particular language. The main objective for developing
speech technology tools for indigenous languages is to meet the needs of modern
language users in all language communities equally. For the Sámi languages, this
would mean equal possibilities to use Sámi in the same contexts as the majority
languages. In this way, developing speech and language technology tools for the
Sámi languages also contribute to the revitalisation of these languages.
Additionally, speech technology tools are useful for many users, also those with
special needs. These include language learners [(cites: yaneva2021speech)](#yaneva2021speech), people
with dyslexia, vision impaired individuals, and speakers of the language that
are not used to read it.





Developing TTS for an indigenous language with few resources available can be
challenging. Any linguistic description, grammar or language learning material
is useful, but for speech technology purposes, it is important to have at least
some amount of speech material and corresponding text, provided by a native
speaker of the language. In this way, it is possible to study the relationship
between text and speech in a particular language and to produce a phonetic
description in a form of a grapheme-to-phoneme mapping. This mapping (or
*text-to-IPA* rule set) can already be used to build a very simple and
“old-fashioned” but still usable TTS application, such as
[the espeak formant
synthesis](https://github.com/espeak-ng) [(cites: kastrati2014opportunity,pronk2013adding)](#kastrati2014opportunity,pronk2013adding). As this framework
does not require a speech corpus but only a set of phonetic and phonological
rules, any language can be added to the list of the languages covered by
`espeak`, only utilising the knowledge of native speakers.


#### Building a speech corpus

The modern approaches to TTS involve machine learning and complex modelling of
speech, which brings in the requirement for big amounts of speech data to build
the models from, ideally covering all phonological contrasts and sound
combinations (diphones, triphones) in a given language. This is because in a
data-driven or *corpus-based* speech synthesis developed that utilize
deep neural networks, the association between textual features and acoustic
parameters is learned directly from paired data—the sentence-long sound files
and the corresponding texts. The sum of the learned knowledge from the paired
data construct the acoustic model (see, e.g., [(cites: watts2016hmms)](#watts2016hmms)).



The building of the speech corpus starts from collecting a suitable text corpus
which corresponds to at least 10 hours of recorded read speech, that has been
shown to be enough to achieve an end-user suitable
[TTS system for North
Sámi](https://github.com/divvun/lang-sme-ml-speech) [(cites: makashova2021speech)](#makashova2021speech). In Divvun, we focus on open-source
methodologies, in which case it is important to build a collection of open
source texts, with a CC-BY (Creative Commons) licence.


For our on-going Lule Sámi TTS  project we reused a part of a Lule Sámi gold
corpus from 2013, and collected additional texts we knew to be well written and
already proofread, before proofreading these texts once more to avoid confusion
when reading the text aloud.

We collected and constructed a Lule Sámi text corpus consisting of various text
styles (news, educational, parliament etc.) with altogether over 74,000 words.
This will approximately correspond to 12 hours of speech recordings when read
aloud by professional voice talents.


















#### Text processing


Most orthographies are underspecified with respect to the pronunciation. This
creates interesting questions when converting a standard orthographic text to
audio waves. In the cases of Lule and North Sámi there is a class of nouns where
consonant gradation (i.e. length alternation) is not expressed in the
orthography, while still being grammatically crucial, as it is the sole marker
of the difference between different syntactic functions, especially
*singular nominative* vs *singular genitive*, and for North Sámi
also  *singular accusative*. That is, for this class of nouns the only
difference between the subject and the possessor or between the subject and the
object, is expressed through a length distinction that is *not* present
in the standard orthography, as seen in
Tables [(see: tab:squirrel)](#tab:squirrel) and [(see: tab:golli)](#tab:golli). That distinction has to be
recreated when converting the orthographic text to a phonemic representation.
There are other underspecifications in the orthography, but these are the most
crucial.



**Table:**[htb]


|  |  Orth.  |  IPA  |  Transl. |
| <!-- footnotesize -->{Q3}  |  *oarre*  |  [\textipa{P\t{oA}r:rIE}]  |  ‘a squirrel’
<span style='font-variant: small-caps'>Nom.Sg</span> |
| <!-- footnotesize -->{Q2}  |  *oarre*  |  [\textipa{PoAr:IE}]       |  ‘a squirrel’s’
<span style='font-variant: small-caps'>Gen.Sg</span> |
|  |                  |                            |  ‘a reason’     <span style='font-variant: small-caps'>Nom.Sg</span> |
| <!-- footnotesize -->{Q1}  |  *oare*   |  [\textipa{PoArIE}]        |  ‘a reason’s’
<span style='font-variant: small-caps'>Gen.Sg</span> |

<!-- small -->skip
(Caption: Ternary length contrast of consonants in Lule Sámi, underspecified in
the orthography. Abbreviations: Q3—overlong, Q2—long, Q1—short.
Originally presented in [(cites: fangel2014quantity)](#fangel2014quantity).<a id="tab:squirrel">(¶ tab:squirrel)</a>)
<!-- end table -->



**Table:**[htb]


|  |  Orth.  |  IPA  |  Transl. |
| <!-- footnotesize -->{Q3}  |  *beassi*  |  [\textipa{p\t{e\ae}s:sI}]  |  ‘birchbark’
<span style='font-variant: small-caps'>Nom.Sg</span> |
| <!-- footnotesize -->{Q2}  |  *beassi*  |  [\textipa{pe\ae s:I}]      |  ‘birchbark’
<span style='font-variant: small-caps'>Acc.Sg</span> |
|  |                   |                             |  ‘(bird’s)
nest’     <span style='font-variant: small-caps'>Nom.Sg</span> |
| <!-- footnotesize -->{Q1}  |  *beasi*   |  [\textipa{pe\ae sI}]       |  ‘(bird’s)
nest’ <span style='font-variant: small-caps'>Acc.Sg</span> |

<!-- small -->skip
(Caption: Ternary length contrast of consonants in North Sámi, underspecified in
the orthography. Abbreviations as in
Table [(see: tab:squirrel)](#tab:squirrel).<a id="tab:golli">(¶ tab:golli)</a>)
<!-- end table -->


The length contrast is encoded in the FST model at an intermediate level, but
during compilation, this information is lost. We have enhanced the
`hfst-pmatch` code to allow the analyser/tokeniser FST to be an
on-the-fly composition of two separate FST’s, and outputting that intermediate
string representation, in effect creating a fake three-tape FST.




With the morphological analysis of all tokens available, we can proceed by
disambiguating the sentence, and leaving only the analyses that fit the
morphosyntactic context. The end result is that we will be left with the proper
analysis (subject or object) *and* with information of the proper length
of the word form, to be fed to the module for conversion to IPA.  As always,
this is done using rule-based components, so we have full control of every step
and are able to correct errors in the IPA transcription. There is still a
fallback module for cases of unknown words and names.

The IPA transcription provided by the FST technology described above can further
improve the accuracy of the TTS, especially the alignment between sounds and
characters. When training a speech model with the IPA transcriptions as text
input (instead of standard orthography) in a deep neural network structure, the
letter-to-sound correspondence will likely be more transparent, also with the
ternary quantity cases described above.

The rule-based approach, reusing many components from other parts of the
*GiellaLT* infrastructure, also means that high quality speech synthesis
is within reach for most language communities.


#### Approaches to Text-to-Speech



We have experimented with two different open source TTS methodologies:
[Ossian](https://github.com/CSTR-Edinburgh/Ossian) [(cites: suni2014simple4all)](#suni2014simple4all)
and a Tacotron implementation (largely based on [(cites: shen2018natural)](#shen2018natural)),
specially adapted for low-resource languages, like the Sámi
languages [(cites: makashova2021speech)](#makashova2021speech).





In our experiments, we used a data set consisting of approximately one hour of
speech from a native speaker of Lule Sámi, producing nearly intelligible speech.

It is clear that for getting better results, at least 10 hours of training data
would be needed, but piloting the methods using small experimental data gives us
better insight on the requirements for the speech corpus, i.e. the size and
audio quality of the data.




As the expectations for the quality of TTS are very high due to the examples
from well-resourced languages such as English, using a neural vocoder (such as
*WaveNet*, [(cites: oord2016wavenet)](#oord2016wavenet)) that produces realistic, human-like
speech is necessary for good usability and user experience. One should not
forget that the environmental cost for complex modelling of speech is
high [(cites: makashova2021speech)](#makashova2021speech), but it is possible to adapt existing speech
models by training the models further with additional data and pre-trained
models from a “neighbouring” language. This so-called *transfer
learning* [(cites: tu2019end)](#tu2019end) allows for utilising smaller data sets for training,
making it possible to use e.g. the North Sámi TTS model as the starting point
for the Lule Sámi TTS.

#### Future work: approaches to automatic speech recognition



In addition to TTS, we are working towards developing a tool for
*automatic speech recognition* (ASR) for Sámi. In
[(cites: makashova2021speech)](#makashova2021speech), TTS and ASR models were trained simultaneously in
a dual transformation loop, using the same *read speech* data set,
corresponding to only six hours of speech from two speakers, three hours each.
The model was trained for 30 000 steps and for the evaluation of the model, it
reached a WER (Word-Error-Rate) of 41\

One of the most important differences between training the TTS and ASR models
would be that for TTS, the training material needs to be very clean in terms of
sound quality and there needs to be as many recordings from a single speaker as
possible. For ASR, on the other hand, the recorded materials can be of poorer
sound quality and preferably from multiple speakers and from different areal
varieties of a language as long as there are good transcriptions of the speech.

State-of-the-art ASR frameworks normally require up to 10,000 hours of
multi-speaker data for training reliable and universal models that are able to
generalise to any unseen speaker [(cites: hannun2014deep)](#hannun2014deep). As collecting these
amounts of data from small minority languages is not a realistic goal,
alternatives such as utilising existing archive materials can be considered for
developing speech technology for Sámi. These are provided by, e.g.,
*[The language bank of
Finland](https://www.kielipankki.fi/language-bank/)* and
*\href{https://www.nb.no/sprakbanken/en/resource-catalogue/oai-tekstlab-uio-no-lia-sapmi/*
{The language bank of Norway}}. As these archive materials contain spontaneous,
transcribed spoken materials from various dialects of North Sámi, we are able to
significantly improve the WER of our North Sámi ASR.









In summary, the procedures and pipelines described above could be applied to any
(minority) language with a low-resource setting, in the task of developing
speech technology applications. Most of the applications discussed here can be
piloted with or further developed with relatively small data sets (even with &lt;
10 hrs of paired data), compared to the amounts of data used for respective
tools for majority languages. This is largely possible thanks to the available
open source materials and technologies, especially those relying on, e.g.,
*transfer learning*.









## Discussion: Big Data

As the previous test cases have shown, big data in terms of large amounts of
data of good quality cannot be assumed in a minority language context. One can
probably go as far as saying that it cannot be expected in any context except
the few big (written) languages. However, big data is usually assumed to just be
available when doing a scientific study or developing language technology tools,
and the judgement “too little data” can mercilessly decide over the
construction of an MT program, inclusion in predominant writing programs (MS
Word etc) as well as whole platforms (Android, iOS).


The often heard question of “why not just train a neural model” can usually
readily be answered by the lack of data and also the quality of the data for a
given task, for example grammatically perfect language data when training a
neural model for grammar correction. The lower bounds of required data have been
the centre of machine learnt NLP research in recent years. For example, for
morphology, the annual SIGMORPHON task has found that a machine learnt model can
learn to fill in dictionary inflection tables from just 200,000 gold annotated
examples at 20  In machine translation, similar results have been shown in WMT
shared task on *very low resource MT* [(cites: fraser-2020-findings)](#fraser-2020-findings), where
it is shown that 60,000 aligned sentences is sufficient for MT between
high-resource and low-resource language, in the example German-Sorbian.  Similar
studies exist for many of the fields of NLP, but the general point is that one
still needs tens to hundreds of thousands of annotated, aligned, and
representative samples to even begin.


## Conclusion









In this article we have presented our rule-based tools in the *GiellaLT*
multilingual infrastructure built during the last 20 years. The
*GiellaLT* infrastructure contains building blocks and support for most
of the language technology needs of indigenous and minority languages, from the
very basic input technologies like keyboards to high-level advanced tools like
world-class grammar checking and machine translation. It does this by using
rule-based technologies that makes it possible for any language community to get
the language technology tools they want and need.  All that is needed is a
linguist.

Secondly, we discussed the question of costless and efficient corpus-based
machine learning models for building NLP tools needed by a language community
(keyboards, spell and grammar checkers, machine translation and Text-to-Speech
tools) and also presented an alternative to these models.


We have illustrated the challenges and efforts in collecting good quality native
speaker texts and making them digitally available, as well as further marking up
the corpus texts in a consistent way in order to use them for NLP tasks such as
spelling and grammar checking.



Multi-billion word corpora are the result of decades of work by countless
authors, proof-readers and publishers. For most languages, these resources do
not exist, and relying upon them for making language models will in practice
exclude the vast majority of languages from getting high-quality tools.
Secondly, when corpora exist, they are too dispersed to constitute a foundation
for normative language models.  For certain tasks like TTS, if a speech corpus
must be built from scratch, it has to be designed to prioritise quality over
quantity of the corpus. We ensure a good quality and multi-purpose speech corpus
by working with professional voice talents and language experts that are native
speakers of the language.


In conclusion, building corpora is based on big efforts, requires expertise and
is time-costly. We have illuminated the work behind three important steps within
building corpora - firstly, collecting and digitalising, secondly upgrading,
i.e. adding annotation for special purposes, and proofreading, and thirdly
converting from one medium/language to another as in  recording speech,
translating, or other.

So, for machine learning approaches that simply make use of existing corpora,
this work does not come for free, it simply has been done by others.





With our multilingual infrastructure and our language resources we show that
while there is a need for corpus data for certain tasks, high quality tools
needed by a language community can be built time-efficiently without big data in
a rule-based manner.



















## Bibliographical References<a id="reference">(¶ reference)</a>


<!-- bib style: unsrt -->
# References

* <a id="pirinen2021building">**pirinen2021building**</a>:
    * author: Pirinen, Tommi A and Tyers, Francis M
    * journal: Multilingual Facilitation
    * pages: 53
    * publisher: Rootroo Ltd
    * title: Building language technology infrastructures to support a
    * year: 2021
* <a id="moshagen2013building">**moshagen2013building**</a>:
    * address: Oslo, Norway
    * author: Moshagen, Sjur N.  and Pirinen, Flammie  and Trosterud, Tron...
    * booktitle: Proceedings of the 19th Nordic Conference of Computational
    * month: may
    * pages: 343–352
    * publisher: Linköping University Electronic Press, Sweden
    * title: Building an Open-Source Development Infrastructure for Langu...
    * url: https://www.aclweb.org/anthology/W13-5631
    * year: 2013
* <a id="khanna2021recent">**khanna2021recent**</a>:
    * author: Khanna, Tanmai and Washington, Jonathan North and Tyers, Fra...
    * doi: 10.1007/s10590-021-09260-6
    * journal: Machine Translation
    * month: 10
    * publisher: Springer
    * title: Recent advances in Apertium, a free/open-source rule-based
    * year: 2021
* <a id="wolf2020transformers">**wolf2020transformers**</a>:
    * author: Wolf, Thomas and Chaumond, Julien and Debut, Lysandre and Sa...
    * booktitle: Proceedings of the 2020 Conference on Empirical Methods in
    * pages: 38–45
    * title: Transformers: State-of-the-art natural language processing
    * year: 2020
* <a id="ardila2019common">**ardila2019common**</a>:
    * author: Ardila, Rosana and Branson, Megan and Davis, Kelly and Henre...
    * journal: arXiv preprint arXiv:1912.06670
    * title: Common voice: A massively-multilingual speech corpus
    * year: 2019
* <a id="antonsen2010reusing">**antonsen2010reusing**</a>:
    * address: Stroudsburg
    * author: Lene Antonsen and Linda Wiechetek and Trond Trosterud
    * booktitle: Proceedings of the 7th International Conference on Language
    * pages: 2782–2789
    * publisher: The Association for Computational Linguistics
    * title: Reusing Grammatical Resources for New Languages
    * year: 2010
* <a id="beesley2003finite">**beesley2003finite**</a>:
    * author: Kenneth R Beesley and Lauri Karttunen
    * flammie: fsa
    * isbn: 978-1575864341
    * pages: 503
    * publisher: CSLI publications
    * title: Finite State Morphology
    * year: 2003
* <a id="linden2013hfst">**linden2013hfst**</a>:
    * author: Lindén, Krister and Axelson, Erik and Drobac, Senka and
    * booktitle: International workshop on systems and frameworks for
    * organization: Springer
    * pages: 53–71
    * title: Hfst—a system for creating nlp tools
    * year: 2013
* <a id="hulden2009foma">**hulden2009foma**</a>:
    * author: Hulden, Mans
    * booktitle: Proceedings of the Demonstrations Session at EACL 2009
    * pages: 29–32
    * title: Foma: a finite-state compiler and library
    * year: 2009
* <a id="Didriksen2016constraint">**Didriksen2016constraint**</a>:
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
* <a id="karttunen2011beyond">**karttunen2011beyond**</a>:
    * author: Karttunen, Lauri
    * booktitle: International Workshop on Systems and Frameworks for
    * organization: Springer
    * pages: 1–13
    * title: Beyond morphology: Pattern matching with FST
    * year: 2011
* <a id="wiechetek-etal-2019-seeing">**wiechetek-etal-2019-seeing**</a>:
    * address: Honolulu
    * author: Wiechetek, Linda  and Moshagen, Sjur Nørstebø  and
    * booktitle: Proceedings of the 3rd Workshop on the Use of Computational
    * month: feb
    * pages: 46–55
    * publisher: Association for Computational Linguistics
    * title: Seeing more than whitespace {—} Tokenisation and disambigu...
    * url: https://www.aclweb.org/anthology/W19-6007
    * year: 2019
* <a id="Wiechetek2019many">**Wiechetek2019many**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="antonsen2017machine">**antonsen2017machine**</a>:
    * author: A. Antonsen and C. Gerstenberger and M. Kappfjell and S. Ráh...
    * booktitle: Proceedings of the 21st Nordic Conference on Computational
    * pages: 123–131
    * title: Machine translation with {North Saami} as a pivot language
    * year: 2017
* <a id="Antonsen2020samiske">**Antonsen2020samiske**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="kummervold-etal-2021-operationalizing">**kummervold-etal-2021-operationalizing**</a>:
    * address: Reykjavik, Iceland (Online)
    * author: Kummervold, Per E  and De la Rosa, Javier  and Wetjen, Fredd...
    * booktitle: Proceedings of the 23rd Nordic Conference on Computational
    * pages: 20–29
    * publisher: Linköping University Electronic Press, Sweden
    * title: Operationalizing a National Digital Library: The Case for a
    * url: https://aclanthology.org/2021.nodalida-main.3
    * year: 2021
* <a id="Gerstenberger2013digging">**Gerstenberger2013digging**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="Moshagen2008language">**Moshagen2008language**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="Antonsen2012improving">**Antonsen2012improving**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="wiechetek-etal-2021-rules">**wiechetek-etal-2021-rules**</a>:
    * author: Wiechetek, Linda  and Pirinen, Flammie  and
    * booktitle: Proceedings of the International Conference on Recent Advanc...
    * month: sep
    * title: Rules Ruling Neural Networks - Neural vs. Rule-Based Grammar
    * year: 2021
* <a id="magga1994hvordan">**magga1994hvordan**</a>:
    * author: Ole Henrik Magga
    * journal: Festskrift til Ørnulv Vorren
    * pages: 269–282
    * publisher: Tromsø Museum
    * title: Hvordan den nyeste nordsamiske rettskrivingen ble til
    * year: 1994
* <a id="moshagen2014test">**moshagen2014test**</a>:
    * address: UiT Norges arktiske universitet
    * author: Moshagen, Sjur
    * date: 2014-11-13
    * month: 11
    * note: presentation at the NorWEST2014 workshop
    * title: Test data and testing of spelling checkers
    * url: https://divvun.no/events/workshops/NorWEST2014/presentations...
    * urldate: 2021-08-05
    * year: 2014
* <a id="yaneva2021speech">**yaneva2021speech**</a>:
    * author: Yaneva, Alexandrina
    * school: Universitat Pompeu Fabra
    * title: Speech technologies applied to second language learning. A u...
    * year: 2021
* <a id="kastrati2014opportunity">**kastrati2014opportunity**</a>:
    * author: Kastrati, Ramiz and Hamiti, Mentor and Abazi, Lejla
    * booktitle: Proceedings of the 15th International Conference on Computer
    * pages: 179–186
    * title: The opportunity of using eSpeak as Text-to-Speech synthesize...
    * year: 2014
* <a id="pronk2013adding">**pronk2013adding**</a>:
    * author: Pronk, Richard and Intelligentie, Bachelor Opleiding Kunstma...
    * journal: University of Amsterdam
    * title: Adding {Japanese} language synthesis support to the eSpeak s...
    * year: 2013
* <a id="watts2016hmms">**watts2016hmms**</a>:
    * author: Watts, Oliver and Henter, Gustav Eje and Merritt, Thomas and...
    * booktitle: 2016 IEEE International Conference on Acoustics, Speech and
    * organization: IEEE
    * pages: 5505–5509
    * title: From HMMs to DNNs: where do the improvements come from?
    * year: 2016
* <a id="makashova2021speech">**makashova2021speech**</a>:
    * author: Makashova, Liliia
    * pages: 26
    * school: University of Gothenburg
    * title: SPEECH SYNTHESIS AND RECOGNITION FOR A LOW-RESOURCE LANGUAGE...
    * year: 2021
* <a id="fangel2014quantity">**fangel2014quantity**</a>:
    * author: Fangel-Gustavson, Nora and Ridouane, Rachid and
    * booktitle: Proceedings of the 10th International Seminar on Speech
    * pages: 106–109
    * title: Quantity contrast in {Lule Saami}: A three-way system
    * year: 2014
* <a id="suni2014simple4all">**suni2014simple4all**</a>:
    * author: Suni, Antti and Raitio, Tuomo and Gowda, Dhananjaya and Karh...
    * booktitle: Proc. Blizzard Challenge
    * organization: Citeseer
    * title: The simple4all entry to the blizzard challenge 2014
    * year: 2014
* <a id="shen2018natural">**shen2018natural**</a>:
    * author: Shen, Jonathan and Pang, Ruoming and Weiss, Ron J and Schust...
    * booktitle: 2018 IEEE International Conference on Acoustics, Speech and
    * organization: IEEE
    * pages: 4779–4783
    * title: Natural tts synthesis by conditioning wavenet on mel spectro...
    * year: 2018
* <a id="oord2016wavenet">**oord2016wavenet**</a>:
    * author: Oord, Aaron van den and Dieleman, Sander and Zen, Heiga andS...
    * journal: arXiv preprint arXiv:1609.03499
    * title: Wavenet: A generative model for raw audio
    * year: 2016
* <a id="tu2019end">**tu2019end**</a>:
    * author: Tu, Tao and Chen, Yuan-Jui and Yeh, Cheng-chieh and Lee, Hun...
    * journal: arXiv preprint arXiv:1904.06508
    * title: End-to-end text-to-speech for low-resource languages by
    * year: 2019
* <a id="hannun2014deep">**hannun2014deep**</a>:
    * author: Hannun, Awni and Case, Carl and Casper, Jared and Catanzaro,...
    * journal: arXiv preprint arXiv:1412.5567
    * title: Deep speech: Scaling up end-to-end speech recognition
    * year: 2014
* <a id="fraser-2020-findings">**fraser-2020-findings**</a>:
    * address: Online
    * author: Fraser, Alexander
    * booktitle: Proceedings of the Fifth Conference on Machine Translation
    * month: nov
    * publisher: Association for Computational Linguistics
    * title: Findings of the WMT 2020 Shared Tasks in Unsupervised MT and
    * url: https://aclanthology.org/2020.wmt-1.80
    * year: 2020




<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

