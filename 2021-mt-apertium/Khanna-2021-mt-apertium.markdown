


<!-- hyphenation Che-ri-vi-rala Mar-tí-nez Sán-chez–Mar-tí-nez -->





\restylefloat{table}



\floatstyle{plaintop}
\restylefloat{table}



\newcommand{\tag}[1]{`&lt;#1&gt;`}
\newcommand{\examp}[1]{*#1*}
\newcommand{\morphform}[1]{`#1`}
\newcommand{\node}[1]{

#1
}

<!-- makeatletter -->
\@mparswitchfalse
<!-- makeatother -->
<!-- set length \marginparwidth 6cm -->

<!-- begin document -->

# Recent advances in Apertium, a free / open-source rule-based machine translation platform for low-resource languages ¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: Springer Open Access publication. This version from pre-print latex form does not contain some changes made in the editorial process. Published version available: <https://link.springer.com/article/10.1007/s10590-021-09260-6>)</span> 




**Authors:** Tanmai Khanna 

Language Technologies Research Centre

IIIT Hyderabad, Telangana India 500032

              <tanmai.khanna@research.iiit.ac.in>
           
and


Jonathan N Washington 

Swarthmore College

Swarthmore, PA USA 19081

              <jonathan.washington@swarthmore.edu>
           
and


Francis M Tyers 

Indiana University

Bloomington, IN USA 47401

              <ftyers@iu.edu>
           
and


Sevilay Bayatlı 

Beykent Üniversitesi

İstanbul, Turkey

              <sewaletaha@beykent.edu.tr>
           
and


Daniel G Swanson 

Swarthmore College

Swarthmore, PA USA 19081

              <dswanso1@gmail.com>
           
and


Flammie A Pirinen 

UiT—Norgga árktalaš universitehta

NO-9000, Romssa

              <tommi.pirinen@uit.no>
           
and


Irene Tang 

University of Chicago

Chicago, IL USA 60637

              <itang1@uchicago.edu>
           
and


Hèctor {Alòs i Font 

Centre de Recerca en Sociolingüística i Comunicació

Universitat de Barcelona

              <hectoralos@gmail.com>
}

**Date:** This version: (date of conversion: 2025-12-31)


<!-- make title -->


**Abstract:**
This paper presents an overview of Apertium, a free and open-source
rule-based machine translation platform.  Translation in Apertium happens
through a pipeline of modular tools, and the platform continues to be
improved as more language pairs are added.  Several advances have been
implemented since the last publication, including some new optional modules:
a module that allows rules to process recursive structures at the structural
transfer stage, a module that deals with contiguous and discontiguous
multi-word expressions, and a module that resolves anaphora to aid
translation.  Also highlighted is the hybridisation of Apertium through
statistical modules that augment the pipeline, and statistical methods that
augment existing modules.  This includes morphological disambiguation,
weighted structural transfer, and lexical selection modules that learn from
limited data.  The paper also discusses how a platform like Apertium can be
a critical part of access to language technology for so-called low-resource
languages, which might be ignored or deemed unapproachable by popular
corpus-based translation technologies.  Finally, the paper presents some of
the released and unreleased language pairs, concluding with a brief look at
some supplementary Apertium tools that prove valuable to users as well as
language developers.  All Apertium-related code, including language data, is
free/open-source and available at <https://github.com/apertium>.


Keywords: machine translation 
and

low-resource languages 
and

rule-based
machine translation 
and

hybrid machine translation<!-- end abstract -->

## Introduction
<a id="sec:intro">(¶ sec:intro)</a>

 (footnote: Several of the advances described in this paper were supported by
Google Summer of Code funding, for which the authors are very grateful.)

Apertium [(cites: forcada2011apertium)](#forcada2011apertium) is a free/open-source platform for
rule-based machine translation (RBMT). It was designed to use the shallow
transfer based approach to translation, and most modules in the pipeline work on
rules written by language developers and linguists. The platform provides an
accessible way to create language data and rules, such that apart from language
developers, speakers of a language with a limited understanding of programming
and/or linguistics can create decent translation systems for their languages as
well. This is a superior model for creating translation systems for low-resource
languages both because it involves stakeholders from the language communities,
and because the languages lack widely available corpora that would be needed for
fully data-driven approaches. Apart from developing RBMT systems for
low-resource languages, the Apertium open source organisation also develops and
supports tools for the creation of RBMT systems.


Several advances to the Apertium platform (Release version 3.6) have been
implemented since the previous publication [(cites: forcada2011apertium)](#forcada2011apertium). These
include organisational improvements, additional tools, additional methods to
augment RBMT with corpus-based methods, new modules for more precise
translation, a few additional tools not directly involved in the RBMT pipeline,
and resources for many more languages and translation pairs.

Organisational changes include a migration of the codebase from subversion
(hosted by SourceForge) to git (hosted by GitHub), a switch from two-letter ISO
codes (ISO 639-1) to three-letter ISO codes (ISO 639-3), and a three-directory
model for translation pairs (one for components specific to each language, and
one for the common components). Additionally, morphological transducers for a
number of languages make use of Helsinki Finite-State Technology (HFST)
[(cites: linden2011hfst)](#linden2011hfst), morphological disambiguation has been improved in many
languages by using Visual Interactive Syntax Learning Constraint Grammar (VISL
CG-3) [(cites: bick2015cg)](#bick2015cg), and several new features have been incorporated into
the lexical selection module.

Section [(see: sec:ApertiumOV)](#sec:ApertiumOV) overviews the design of the Apertium RBMT platform.
Section [(see: sec:HyberdisationOFApertium)](#sec:HyberdisationOFApertium) discusses modules used by Apertium to
augment RBMT using corpus-based methods. Section [(see: sec:NewModules)](#sec:NewModules) introduces
the new modules in the pipeline: a module that allows rules to process recursive
structures at the structural transfer stage, a module that deals with contiguous
and discontiguous multiword expressions, and one that resolves anaphors to aid
translation. Section [(see: sec:LinguisticsOfEnden)](#sec:LinguisticsOfEnden) discusses Apertium’s
contribution to language revitalisation and reclamation efforts.
Section [(see: sec:OtherValuableTools)](#sec:OtherValuableTools) introduces several supplementary Apertium
tools. Section [(see: sec:Conclusion)](#sec:Conclusion) concludes.

## Overview of the Apertium platform<a id="sec:ApertiumOV">(¶ sec:ApertiumOV)</a>

The overall design of Apertium is a pipeline with a series of modules. Each
stage of the pipeline reads from and writes to text streams in a consistent
format so that modules can easily be added or removed according to the needs of
the languages in question.

Apertium consists of both the management of the pipeline (the main
`apertium` executable) and all the stages in this pipeline, except where
outside tools (such as HFST for morphological analysis and generation, or CG for
morphological disambiguation) are used. Each stage consists of a general
processor which modifies the stream based on hand-crafted “rules” (coded
linguistic generalisations) for a given language or language pair.
Figure [(see: fig:pipeline)](#fig:pipeline) shows the entire pipeline, including optional modules.


**Figure:**
<!-- centering -->
![pipeline_box](pipeline_box)
(Caption: The architecture of Apertium, a transfer-based machine translation
system.  Each rounded box is a module available for language-specific or
pair-specific development.  Broken lines show optional modules.  Lines with
arrows represent the flow of data through the pipeline.  The stages in the
pipeline are grouped by whether they are relevant to source-language
analysis, bilingual transfer, or target-language generation—the three
logical sections of the pipeline.  The deformatter and reformatter are
language-agnostic and provided by Apertium.)<a id="fig:pipeline">(¶ fig:pipeline)</a>
<!-- end figure* -->

A short overview of each of the stages of the pipeline is provided below.  The
new ones are discussed in further detail in Section [(see: sec:NewModules)](#sec:NewModules).


    * [<span class='math'>-</span>]**Deformatter:** Encapsulates any document formatting tags so
that they go through the rest of the translation pipeline untouched.
This is a language-agnostic part of Apertium.



    * [<span class='math'>-</span>]**Source Language morphological analyser:** Segments the
surface form of text (words or multi-word lexical units) using a
finite-state transducer (FST) and delivers one or more lexical forms (or
        “analyses”), each of which includes a lemma and a part-of-speech label
        (encoded as a “tag”), as well as any relevant subcategory and
grammatical (e.g., inflectional) information (also encoded as tags).



    *  **Source Language morphological disambiguator:** Tries to choose
the best sequence of morphological analyses for an ambiguous sentence.

The original Apertium disambiguator used a first-order hidden Markov
model (HMM). Other statistical models, such as averaged weighted
Perceptron, have since been added and are currently in use for various
languages. Additionally, CG [(cites: bick2015cg)](#bick2015cg) is often combined with a
statistical model for a two-step process.  The different approaches are
discussed in Section [(see: sec:MorphologicalDis)](#sec:MorphologicalDis).



    *  **Source Language retokenization:** Adjusts token boundaries for
multi-word expressions, which can be non-contiguous (such as separable
verbs in Germanic languages), in preparation for translation.  Often
this consists of combining component parts into single multi-word
expressions.  This module is discussed in more detail in
Section [(see: sec:ApertiumSeparable)](#sec:ApertiumSeparable).



    *  **Lexical transfer:** Reads each source-language (SL) lexical
form and delivers a set of corresponding target-language (TL) lexical
forms by looking it up in a bilingual dictionary, implemented as an FST.



    *  **Lexical selection:** Based on context rules, chooses the most
adequate translation of ambiguous SL lexical forms. The original
module [(cites: tyers2012flexible)](#tyers2012flexible) has been extended with new features
like macros.  This is discussed in more detail in
Section [(see: sec:lexicalSel)](#sec:lexicalSel).



    *  **Source Language anaphora resolution:** Resolves references to
earlier items in discourse. Using saliency metrics, this module attaches
the lexical unit of the antecedent to its corresponding anaphor to aid
translation. This module is discussed in more detail in
Section [(see: sec:AnaphoraResol)](#sec:AnaphoraResol).



    *  **Shallow structural transfer:** Apertium’s shallow structural
transfer module implements a sequence of one or more finite-state
constraint rules on the output of the lexical selection module. It
generally consists of three sub-modules: a chunker mode, an interchunk
mode, and a postchunk mode.

Apertium 1.0 had one single structural transfer step.  This was
considered enough for the translators between the closely related
Iberian Romance languages which constituted the first Apertium
translators. The one-step strategy is still used in the current released
versions of many of them, including the Catalan-Spanish translation
pair, which since then has been continuously improved and is widely
used. (footnote: In 2020, the Softcatalà-hosted Apertium translators
served an average of 4.6 million requests per month from Spanish to
Catalan and 1.1 million from Catalan to Spanish (data kindly provided by
Xavier Ivars).)
 Beginning with the implementation of the
Spanish-English and Catalan-English language pairs, a three-step
transfer architecture was developed, leading to the release of Apertium
2.0. The first step creates chunks in the source language and reorders
words inside the chunk as per the transfer rules. The second step
reorders chunks based on the target language syntax, and the final step
makes the stream ready for the generator. This is currently the standard
Apertium structural transfer architecture. Several pairs have additional
transfer steps, such as Catalan-Esperanto (5 steps) and French-Occitan
        (4 steps).

In the Catalan-Esperanto translator there are three “interchunk" steps
aimed at a deeper syntactic analysis, with the overarching objective of
generating the correct case morphology on various types of nominals in
the target language (Esperanto), since the source language (Catalan)
lacks case morphology except in its pronominal system.  The shallow
transfer system is used creatively in other ways as well.



    *  **Recursive structural transfer:**
This module is a recently developed alternative to the shallow
structural transfer module (chunker, interchunk, and postchunk). Its
linguistic data is specified as context-free grammars (CFGs) and it uses
a Generalized Left-right Right-reduce (GLR) parser rather than
finite-state chunking to more effectively implement long-distance
reordering.  This module is discussed further in
Section [(see: sec:RecursiveStruc)](#sec:RecursiveStruc).



    *  **Target Language retokenization:** Adjusts token boundaries for
multi-word expressions, which can be non-contiguous (such as separable
verbs in Germanic languages), in preparation for target-language
morphological generation.  Often this consists of separating multi-word
expressions into their component parts.  This module is discussed in
more detail in Section [(see: sec:ApertiumSeparable)](#sec:ApertiumSeparable).



    *  \textbf {Target Language morphological generator:} Delivers the
sequence of TL surface forms for each corresponding TL lexical form
received from earlier modules in the pipeline.



    *  **Target Language Post-generator:** Performs mainly orthographic
operations across tokens, for example elision (such as *lo + òme
        = l’òme* in Occitan), fusion (such as *da + il = dal* in
Italian), epenthesis (such as *a &gt; an* in English, or *с &gt;
со* and *о &gt; об* in Russian), or dissimilation (such as
        *la + agua &gt; el agua* in Spanish).



    *  **Reformatter:** De-encapsulates any formatting information to
prepare a finally formatted document in the target language. This is a
language-agnostic part of Apertium.


The reader is referred to the Apertium
wiki (footnote: <http://wiki.apertium.org/wiki/Pipeline>) for more information
about file naming conventions, mode naming conventions, and dates of
introduction for each stage of the pipeline. Any further additions to the
pipeline will be documented on this wiki.

It should be added that a major difference in the organisation of Apertium
language pairs as compared to the original model is the three-directory
structure currently used for most (but not all) of the released translation
pairs. Initially, every translation pair was developed in a single
self-contained repository that included all relevant linguistic data. Currently,
monolingual data, such as morphological dictionaries, morphological
disambiguators and post-generators, are shared by different translators,
allowing much easier reuse of data and cooperation in the improvement of
linguistic resources [(cites: marting2014fst)](#marting2014fst). Thus, for instance, compiling the
`apertium-spa-cat` pair now depends on the `apertium-spa` and
`apertium-cat` modules, which are also used by other translation pairs.

## Use of corpus-based approaches in Apertium modules
<a id="sec:HyberdisationOFApertium">(¶ sec:HyberdisationOFApertium)</a>

Several methods of incorporating corpus-based approaches into Apertium RBMT
systems are available. These methods fall into the domains of morphological
disambiguation (Section [(see: sec:MorphologicalDis)](#sec:MorphologicalDis)), lexical selection
(Section [(see: sec:lexicalSel)](#sec:lexicalSel)), and structural transfer
(Section [(see: sec:StructuralTr)](#sec:StructuralTr)).

### Morphological disambiguation<a id="sec:MorphologicalDis">(¶ sec:MorphologicalDis)</a>

The goal of morphological disambiguation is to choose the correct morphological
analysis if there are multiple possible analyses for a given lexical unit.

The oldest and most commonly used morphological disambiguation method in
Apertium [(cites: sanchez2006speeding, sanchez2007training)](#sanchez2006speeding, sanchez2007training) is a module that relies on patterns
learned from a corpus. This bigram-based morphological disambiguator chooses one
analysis from among those returned by the morphological analyser based on a
probabilistic model of sequences of part-of-speech tags given the surrounding
context.

Some Apertium disambiguators are implemented instead using statistical methods
based on Hidden Markov Models (HMM), which processes the result of the
application of constraint-grammar rules [(cites: karlsson1995constraint)](#karlsson1995constraint). The
perceptron tagger [(cites: zhang2011syntactic)](#zhang2011syntactic) in the English language
module (`apertium-eng`) follows one such method.

Furthermore, VISL CG-3 [(cites: bick2015cg)](#bick2015cg) has become a popular method among
Apertium developers of implementing morphological disambiguation using
hand-crafted heuristics.  For many languages, it is combined with one of the
other methods for a two-step disambiguation stage.

### Lexical selection<a id="sec:lexicalSel">(¶ sec:lexicalSel)</a>

The goal of lexical selection is to choose an adequate translation in the target
language from among several possible translations for a given source-language
lexical unit.  An FST-based module that allows the writing of rules has been in
use for some time [(cites: tyers2012flexible)](#tyers2012flexible).

Apart from manually written rules, a system has also been developed that learns
rules through a maximum-entropy model trained in an unsupervised
manner [(cites: tyers2014unsupervised)](#tyers2014unsupervised).  The training method requires only a source language
corpus, a statistical target-language language model, and the RBMT system
itself.  All possible translations are scored against the TL language model, and
these scores are normalized to provide fractional counts to train
source-language maximum-entropy lexical selection models.

### Structural transfer module<a id="sec:StructuralTr">(¶ sec:StructuralTr)</a>

Structural transfer handles differences between the source and target languages
in terms of word order and morphological information by applying transfer rules.
In the chunker module, these transfer rules function by matching a source
language pattern of lexical items, creating chunks and applying a sequence of
actions to convert the word order and morphological properties of the chunk as
per the target language. There can, however, be more than one potential sequence
of actions for each source language pattern, as well as overlapping patterns. To
generate an accurate translation, transfer rules are applied to the input using
a left-right-longest match algorithm.

Work has been done to extract, or “learn”, chunking rules using Alignment
Templates [(cites: hutchison2006using,sanchez2007automatic,
martinez2008using,sanchez2009inferring, sanchez-cartagena2015generalised)](#hutchison2006using,sanchez2007automatic,
martinez2008using,sanchez2009inferring, sanchez-cartagena2015generalised).  A
parallel corpus is searched for sequences of lexical units that exhibit
differences in order or morphological information.

In addition, chunker rules can now be weighted so as to apply different rules in
different overlapping lexical environments. These weights can be learned using
an unsupervised maximum entropy approach [(cites: bayatli2019unsupervised)](#bayatli2019unsupervised).

The basic goal of this method is to choose between conflicting structural
transfer rules based on the lexical environment.  For example, the Spanish
sentence *Encontré el pastel muy bueno* has (at least) two different
(hypothetical) translations to English depending on the syntactic parse in
Spanish: (a) “I found the cake very good” or (b) “I found the very good
cake”.  That is, *muy bueno* may be parsed (a) as a complement to the verb
*encuentro* or (b) as a modifier to the noun *el pastel*.  These
parses correspond to different sets of transfer rules, each of which could be
matched: (a) a single verb phrase consisting of V DET N ADV ADJ, or (b) a verb
V, followed by a noun phrase DET N ADV ADJ.  The noun phrase rule would specify
that the elements be output in a different order, DET ADV ADJ N, and both rules
that match the verb would add a lexical unit for the pronominal subject.

A model is produced by running SL text through all possible transfer rules,
comparing the potential translations that are output to a TL language model, and
dividing the scores by the series of SL lemmas that matched each transfer rule
pattern for a given potential translation.  If the example above were part of
the training data, then the potential translation *I found the cake very
good* would score higher than *I found the very good cake* against an
English language model due to having a higher probability.  These different
scores are then distributed as weights, along with the input lemmas, attached to
the rules that each translation is the result of.  In this example, the weight
assigned to the V DET N ADV ADJ rule for the Spanish lemmas is higher than the
sum of the weights assigned to the V and DET N ADV ADJ rules for these same
lemmas, and hence the V DET N ADV ADJ rule will be selected.

During translation, when a string of SL text matches multiple transfer rules,
the system is able to choose between them (infer the “correct” one) based on
the weights associated with the rules that the SL lemmas trigger.  For example,
if this same sentence were being translated, the V DET N ADV ADJ rule would be
matched, resulting in the output “I found the cake very good”.

A contrasting example, *Encontré un pastel muy bueno*, would match the same
two sets of rules, but would result in translation occurring through the other
rule set.  This is because the lemmas of the potential translation *I found
a very good cake* would result in higher combined weights for the V and DET N
ADV ADJ rules than the V DET N ADV ADJ rule.  This reason for this is that
translations containing these lemmas would have scored higher against an English
language model than translations like *I find a cake very good*, resulting
in higher weights for this set of Spanish lemmas attached to this set of rules.

In both examples of Spanish inputs, using this approach and a suitable corpus to
train an English language model, the set of transfer rules that results in the
more likely English translation is chosen.

This method has been tested using the Kazakh–Turkish, Kyrgyz–Turkish, and
Spanish–English translation pairs, and it has been observed that the results
are better when there is a greater number of ambiguous rules.  The module has
not yet been included in any released translation system.

## New modules<a id="sec:NewModules">(¶ sec:NewModules)</a>

Several previously-unpublished modules are now available for the Apertium
pipeline.  Discussed in this section are `apertium-recursive`, which
provides for true recursive transfer; `apertium-separable`, which enables
the processing of multi-word expressions; and `apertium-anaphora`, which
allows the resolution of anaphors in the source text.

### Recursive structural transfer<a id="sec:RecursiveStruc">(¶ sec:RecursiveStruc)</a>


**Figure:**
<!-- minipage \textwidth -->
<!-- centering -->
    
```

NP -&gt; det n { 2 + 1 } |
NP PP { 2 _ 1 } ;

PP -&gt; pr NP { 2 + 1 } ;
    
```

(Caption: A simple set of recursive rules translating a subset of noun
phrases and prepositional phrases from English to Basque.  A noun phrase
    (`NP`) in the source language consists of a determiner (`det`)
and a noun (`n`), and may optionally include a prepositional phrase
    (`PP`), and a prepositional phrase consists of a preposition
    (`pr`) and a noun phrase.  All three output rules reverse the order
of the two nodes: the order of a determiner and a noun is reversed, the
order of a noun phrase and a prepositional phrase is reversed, and the order
of an adposition (preposition/postposition) and a noun phrase is reversed.
The action part of the rules (building up the target translation) appears
between braces `\{...`).  The indices, `1` and `2`,
indicate the position of the unit matched in the input, `\_`
represents a space in the output, and `+` indicates that the words on
either side of it will be conjoined without a space. }
    <a id="fig:recursion">(¶ fig:recursion)</a>
<!-- /minipage -->

<!-- minipage \textwidth -->
<!-- centering -->
    \missingfigure{forest: 1}
(Caption: A source language parse tree for the phrase *the house by
the side of that road* built using the rules in
figure [(see: fig:recursion)](#fig:recursion). When no further application of the rules is
possible, this tree will be transformed into the tree shown in
figure [(see: tree:recursion-eus)](#tree:recursion-eus).)<a id="tree:recursion-eng">(¶ tree:recursion-eng)</a>
<!-- /minipage -->

<!-- minipage \textwidth -->
<!-- centering -->
    \missingfigure{forest: 2}
(Caption: The target language tree resulting from applying the action
steps of the rules in figure [(see: fig:recursion)](#fig:recursion) to the tree in
figure [(see: tree:recursion-eng)](#tree:recursion-eng).  The analyses yielded by this tree will
generate the Basque phrase *kale haren ertzeko etxea* ‘the house by
the side of the road’. The final step of combining definite articles and
postpositions with the immediately preceding words is not
shown.)<a id="tree:recursion-eus">(¶ tree:recursion-eus)</a>
<!-- /minipage -->

<!-- end figure -->

Given the range of possible syntactic structures, it is common for any two
languages to have significantly different word orders.  For example, in Welsh,
verbs tend to be at the beginning of a sentence; in English they tend to be in
the middle; and in Kyrgyz, they tend to be at the end.

These differences are problematic for Apertium’s finite-state chunking module,
which matches fixed sequences of words that must be contiguous.  This limitation
means it is fairly easy to write rules which perform operations such as changing
the order of nouns and adjectives, since these are usually adjacent, but
changing larger structures is much harder. Switching the order of the subject
and the main verb, for instance, would generally require writing a rule for each
sequence of words that can make up each of those parts. The English-Spanish pair
has more than 30 chunking rules for handling noun phrases with different numbers
of determiners and adjectives, and those rules don’t attempt to deal with all
structures that may occur in noun phrases, such as relative clauses.

To deal with the limitations of finite-state chunking, the
`apertium-recursive` module [(cites: swanson2020tree)](#swanson2020tree) was developed by
Daniel Swanson as part of Google Summer of Code
2019 (footnote: <https://summerofcode.withgoogle.com/archive/2019/projects/6746718069063680/>.)
to apply structural transfer rules recursively using context-free grammars
(CFGs) and a Generalized Left-right Right-reduce (GLR) parser. This makes it
possible to process nested structures such as relative clauses or prepositional
phrases within prepositional phrases. An example of the latter is shown in
Figures [(see: tree:recursion-eng)](#tree:recursion-eng) and [(see: tree:recursion-eus)](#tree:recursion-eus), with the relevant
rules in Figure [(see: fig:recursion)](#fig:recursion).  In this example, the word order of a set
of nested prepositional phrases needs to be completely reversed (or in
linguistic terms, the order of noun phrases (NPs) and adpositional phrases (PPs)
each needs to be reversed), regardless of the number of prepositional phrases
involved in order to translate from English to Basque.

A recursive approach to transfer can be helpful for translation pairs between
syntactically more similar languages as well. For example, in the case of the
English-Spanish noun phrase rules mentioned above, the more than 30 rules
required for handling determiners, adjectives, and nouns can be simplified to
less than 10 rules in `apertium-recursive` because more complicated
structures can be handled by composing simpler ones. In fact, the majority of
these can be covered by just 3 rules saying that a noun phrase is composed of a
noun, or an adjective and a noun phrase, or a determiner and a noun phrase.
These 3 rules can immediately handle any number of determiners and adjectives.

### Processing multi-word expressions<a id="sec:ApertiumSeparable">(¶ sec:ApertiumSeparable)</a>

Multi-word expressions (MWEs) are compound expressions composed of two or more
words, such as phrasal verbs (*take out*, *wake up*, *make a
call*) and phrasal nouns (*telephone pole*). Separable multi-word
expressions are those that may be split by an intermediary word or phrase (such
as *take out* in *take the trash out*). This phenomenon can be seen in
a number of languages. In English, the multi-word “take away” can remain
unified, such as in ***take away the item***, or be split up, such as
in ***take the item away***—both phrasings have identical meanings.
This phenomenon can also be seen in some German verbs, where the separable
particle can detach from its lexical core, such as with the separable verb
*anrufen* ‘to call’: ***rufe meine Freundin an*** ‘call my
friend’. See [(cites: constant2017multiword)](#constant2017multiword) for more on this phenomenon.

Separable MWEs are particularly problematic for Apertium’s rule-based
translation. Prior to the introduction of the `apertium-separable`
module, the individual components of both non-separable and separable
multi-words were translated as individual tokens, often leading to less-optimal
translations. For example, during the English-to-Spanish translation of
***take the trash away***, the phrase’s individual components were
translated to produce *tomar la basura fuera* which isn’t a phrase that
native speakers of Spanish would produce. The more optimal solution is to
process *take away* as a single unit in order to obtain the correct
expression *sacar la basura*. Similarly, the Arpitan verbal expression
*tornar fâre* ‘to redo’ has negative forms of the type *tornar pas
fâre* which were not previously recognised nor correctly generated.

`Apertium-separable` provides a framework to address mistranslations
arising from this sort of non-contiguous word ordering.
Section [(see: sec:separable-module)](#sec:separable-module) describes the module and
section [(see: sec:separable-usage)](#sec:separable-usage) describes its usage.

#### The apertium-separable module<a id="sec:separable-module">(¶ sec:separable-module)</a>

The `apertium-separable` module was developed by Irene Tang as part of
Google Summer of Code
2017 (footnote: <https://summerofcode.withgoogle.com/archive/2017/projects/4690909727817728/>.)
to handle both contiguous and discontiguous (or “separable”) MWEs. The module
accepts an XML-format dictionary as input, which contains a list of phrase types
and a list of mappings between MWEs and their component elements—and in the
case of non-contiguous MWEs, a specification of the possible phrase types that
might separate the elements of the MWE.

As an example, one phrase-type entry that the `eng` dictionary might
include is the definition a noun phrase (NP) as (among other patterns) any
sequence of words such that the first contains a \tag{det} tag, the second an
\tag{adj} tag, and the last a \tag{n} tag. The `eng` dictionary should
then also include an entry specifying how *take away* as an MWE followed by
such a noun phrase may be mapped to its component elements.  These phrase-type
and vocabulary entries work together as a framework for handling MWEs.

The XML dictionary is compiled into a finite state transducer. As a parser feeds
the input text into the transducer one character or tag at a time, it looks out
for sequences of characters and tags that match anything in the dictionary. If a
match is found, then the parser outputs the corresponding substitution.


Processors for this module may be included in two places in the Apertium RBMT
pipeline: immediately following morphological tagging and preceding lexical
transfer, and immediately following structural transfer and preceding
morphological generation.  The former use allows “assembly” of source-language
MWEs for transfer, and the latter “disassembles” transferred target-language
MWEs for morphological generation.

#### Usage<a id="sec:separable-usage">(¶ sec:separable-usage)</a>
Both contiguous and discontiguous multi-word expressions can also be handled by
this module.  Processing seemingly simple contiguous MWEs in this way allows for
more robust bilingual dictionary entries with fairly vanilla morphological
transducers. For example, it may not make sense to have an entry for
\examp{little brother} in an English morphological transducer that already
contains the component words, but it is useful to have an entry like this in a
bilingual dictionary with a language like Kyrgyz, which has two words for
brother with the difference in meaning associated with relative age to a
sibling.  In this situation, the `apertium-separable` module processes
the analysis of \examp{little brother} as an adjective and a noun
(\morphform{\^little\tag{adj}\<span class='math'>} \morphform{\^brother\tag{n}\tag{sg}\</span>}) and
retokenizes it as a multi-word noun (\morphform{\^little
brother\tag{n}\tag{sg}\<span class='math'>}). Note that the assembly of the MWE (as described
here) would occur in the English-Kyrgyz translation direction before bilingual
dictionary lookup, and the disassembly of the MWE (the reverse) would occur in
the Kyrgyz-English translation direction before morphological generation.

The module is used extensively in the French-Catalan pair, particularly in the
verbal phrases included in the dictionaries. Thus, for example, it is defined
that \examp{faire appel} ‘to do appeal’ should be translated as \examp{apel·lar}
‘to appeal’.  However, there are often adverbs between the verb *faire* and
the noun \examp{appel}, for example when negated: \examp{ne fait pas appel}
‘does not appeal’. The module is used to reorder the phrase before lexical
transfer as *ne fait appel pas* (with *fait appel* as a single lexical
unit).  Since the adverb now follows the multi-word verb instead of appearing
between its components, structural transfer does not need to treat such a
sentence any differently than sentences containing single-word verbs.  Similar
examples are found in the [unreleased] Kazakh-Kyrgyz pair.

### Anaphora resolution<a id="sec:AnaphoraResol">(¶ sec:AnaphoraResol)</a>

The `apertium-anaphora` module was developed by Tanmai Khanna as part of
Google Summer of Code
2019 (footnote: <https://summerofcode.withgoogle.com/archive/2019/projects/5434868157120512/>.)
to handle anaphora resolution in the Apertium pipeline. Anaphora resolution is
the process of resolving references to earlier items in the discourse. This is
necessary in a Machine Translation pipeline as languages have different ways of
using anaphors, and sometimes it is necessary to know the antecedent of an
anaphor to translate it correctly.

For example, in Catalan, the masculine singular possessive determiner is
\examp{el seu}.  Its gender and number are inflectional properties relating to
how it agrees with nouns, but its referent may be any gender or number.  Hence
it could be translated to English as any of \examp{his/her/its/their}, the
gender and number of which relate to the referent and not to a modified noun. To
pick the correct translation in English, then, it is necessary to know what
\examp{el seu} refers to. Without a module in an Apertium translation pipeline
to do this, a default translation of the anaphor appears in the target language.
For instance, in the case of English possessive determiners, the default is
currently \examp{his}.

While there are several statistical methods to resolve anaphors using machine
learning, Apertium is focused on supporting low-resource language pairs, which
usually don’t have enough data available for these methods to be viable.  Common
rule-based approaches, on the other hand, often use parse trees
[(cites: lappin1994algorithm,baldwin1997cogniac,trouilleux2002rule,lee2013deterministic,loaiciga2015rule,zeldes2016when)](#lappin1994algorithm,baldwin1997cogniac,trouilleux2002rule,lee2013deterministic,loaiciga2015rule,zeldes2016when).
The `apertium-anaphora` module uses a rule-based approach to anaphora
resolution which does not require any training data, nor rely on parse trees.
Based on Mitkov’s algorithm [(cites: mitkov1999multilingual)](#mitkov1999multilingual), it gives saliency
scores to candidate antecedents in the context (the current and previous three
sentences) based on **saliency indicators**, which are syntactic or lexical
indicators that are expected to correlate to a higher or lower likelihood that a
candidate antecedent is the correct one, using positive and negative scores
respectively.  For example, indefinite nouns can be given a small negative score
and proper nouns can be given a small positive score, as it has been shown
empirically that they are less or more likely to be the antecedent of anaphors,
respectively [(cites: mitkov1999multilingual)](#mitkov1999multilingual).  After the scores of all the
indicators are applied, the candidate with the highest score, hence considered
most salient, is chosen as the antecedent.  A complete example of this is
presented in section [(see: sec:ARExampleUsage)](#sec:ARExampleUsage).  These saliency indicators are
added in the `apertium-anaphora` module as manually written rules.  These
rules are written for and are applied based on source-language forms only.
Because of this, a ruleset can be reused for multiple translation pairs with the
same source language.

Apart from manually written rules, a universal indicator is the Referential
Distance indicator.  This indicator, which was also discovered empirically
[(cites: mitkov1999multilingual)](#mitkov1999multilingual), tells the algorithm that as the distance
between the anaphor and candidate antecedent increases, the candidate is less
likely to be the correct antecedent of the anaphor.  Penalisation of candidates
that are further from the anaphor is implemented by adding to candidates in the
same sentence as the anaphor a `+1` score, candidates in the preceding
sentence a `+0` score, in the sentence before the preceding sentence a
`-1` score, and so on.

In the next few sections, some unique features of this module are discussed
([(see: sec:ARUniqueFeatures)](#sec:ARUniqueFeatures)), an example highlighting the process and benefit of
having anaphora resolution in the Machine Translation pipeline is shown
([(see: sec:ARExampleUsage)](#sec:ARExampleUsage)), a preliminary evaluation of the module is presented
([(see: sec:AREvaluation)](#sec:AREvaluation)), and future work for this module is outlined
([(see: sec:ARFutureIdeas)](#sec:ARFutureIdeas)).

#### Some unique features<a id="sec:ARUniqueFeatures">(¶ sec:ARUniqueFeatures)</a>
Unlike [(cites: mitkov1999multilingual)](#mitkov1999multilingual) original algorithm, this module is
extremely customisable.  The linguistic patterns to be detected and the scores
to be assigned are all defined in an XML file specific to each translation
direction. These patterns help identify and rank potential antecedents, and can
include references to various types of surrounding words and even the anaphor
whose antecedent is being resolved.  The translation pair developer also has the
ability to define multiple types of anaphors—such as possessive determiners,
reflexive pronouns, zero anaphors, etc.—so as to be able to write separate
rules for the resolution of each of them.

#### Example Usage<a id="sec:ARExampleUsage">(¶ sec:ARExampleUsage)</a>


**Table:**[ht]
(Caption: A Catalan-English translation example which highlights a use case for `apertium-anaphora`.)
<a id="tab:ARExample">(¶ tab:ARExample)</a>


p{0.55\linewidth}}
| **Input sentence (Catalan)** | Els grups del Parlament han mostrat aquest dimarts **el seu** suport al batle d’Alaró.|
| ---- | ---- |
| **Reference translation (English)** | Parliamentary groups showed **their** support for the mayor of Alaró on Tuesday.|
| **Apertium translation without `apertium-anaphora` (English)** | The bands of the Parliament have shown this Tuesday **his** support at the mayor of Alaró.|
| **Apertium translation with `apertium-anaphora` (English)** | The bands of the Parliament have shown this Tuesday **their** support at the mayor of Alaró.|

<!-- end table -->

A sample translation which highlights the usage of `apertium-anaphora`
has been given in Table [(see: tab:ARExample)](#tab:ARExample). The source sentence goes through a
series of modules in the translation pipeline, as described in
Section [(see: sec:ApertiumOV)](#sec:ApertiumOV). The output of the lexical selection module
contains a stream of lexical units, including the morphological analysis and the
translation of each lexical unit. This is taken as the input to the
`apertium-anaphora` module. The lexical unit of the example anaphor,
*el seu*, at this stage in the stream is as follows:


```
 ^el seu&lt;det&gt;&lt;pos&gt;&lt;m&gt;&lt;sg&gt;/his&lt;det&gt;&lt;pos&gt;&lt;m&gt;&lt;sg&gt;</span> 
```


The antecedent of the possessive determiner *el seu* is *els
grups* ‘the groups’, which is plural, and hence it should be translated as
*their* in English and not *his*.  The anaphora resolution module
attempts to resolve this anaphor and identify its antecedent by applying all
rules that match the context.  For instance, the `First NP` rule gives a
positive score to the first noun of the sentence (*grups*), as the first
noun of a sentence is more likely to be the antecedent of an anaphor. The
`Preposition NP` rule gives a negative score to a noun that is part of a
prepositional phrase (*Parlament*), as a noun inside a prepositional
phrase is less likely to be the antecedent of an anaphor. Both of these
tendencies have been observed empirically [(cites: mitkov1999multilingual)](#mitkov1999multilingual), and
have been implemented as language-specific rules.

After application of all the rules on all candidate antecedents, the one with
the highest score is considered the most salient antecedent for the anaphor.  If
the rules are successful, then the correct antecedent should have the highest
score (in this case, *bands*).  The anaphora resolution module then
attaches this antecedent (in the target language) to the lexical unit of the
anaphor:


```

^el seu&lt;det&gt;&lt;pos&gt;&lt;m&gt;&lt;sg&gt;/his&lt;det&gt;&lt;pos&gt;&lt;m&gt;&lt;sg&gt;/band&lt;n&gt;&lt;pl&gt;<span class='math'>

```


Based on the properties of the attached antecedent, the anaphor is modified
during structural transfer (*his* </span>\rightarrow<span class='math'> *their*, as the
antecedent is plural), resulting in the following lexical unit:


```

^their&lt;det&gt;&lt;pos&gt;&lt;m&gt;&lt;sg&gt;</span>

```


The final Apertium translation, after each lexical unit output from structural
transfer has gone through morphological generation, can be seen in
Table [(see: tab:ARExample)](#tab:ARExample). The translation of the anaphor is fixed due to the
use of `apertium-anaphora` in the pipeline. While the final Apertium
translation is still not ideal, other aspects of this translation may be fixed
through adjustments to other modules in the translation pipeline: the
preposition \examp{for} instead of \examp{at} in lexical selection, not using
the article \examp{the} with \examp{Parliament} in structural transfer or
lexical selection, the placement of the adjunct \examp{this Tuesday} in
structural transfer, and \examp{groups} for \examp{bands} in lexical selection.

#### Preliminary evaluation<a id="sec:AREvaluation">(¶ sec:AREvaluation)</a>

The `apertium-anaphora` module has been manually evaluated on two
language pairs—Spanish–English and Catalan–Italian—by rating the
translation of anaphors with and without the module in the pipeline. Since this
is a preliminary evaluation, only third person possessive determiners were
marked as anaphors.

In Spanish, there is a possessive determiner *su*, which can be
translated to English as *his/her/its/their* depending on the gender,
number, and animacy of the antecedent. The first 1000 sentences from the Spanish
Europarl corpus were translated to English using Apertium with and without
`apertium-anaphora` in the translation pipeline, and a basic rule-set was
used for the anaphora resolution. (footnote: The rule set used is the one
contained in the revision of
<https://github.com/apertium/apertium-eng-spa/blob/anaphora-transfer/apertium-eng-spa.spa-eng.arx>
as of the time of publication.)  120 sentences out of these had at least one
possessive determiner, and a manual evaluation was done to check the accuracy of
the translated anaphors in English.

In Catalan, there is a possessive determiner *el seu* which can translate
as *il suo* ‘his/her/its’ or *il loro* ‘their’ in Italian,
depending on the number of the antecedent. A corpus was created using articles
from Kataluna Esperantisto (footnote: The journal can be found at
<https://esperanto.cat/Kataluna-Esperantisto>.), a freely available journal,
and random paragraphs were translated.  A total of 108 sentences had at least
one possessive determiner, and a manual evaluation was done to check the
accuracy of the translated anaphors in Italian.

The results of these evaluations (footnote: The complete evaluation data can be
found at
<https://github.com/apertium/apertium-anaphora/tree/master/evaluation>.) are
shown in Table [(see: tab:AREval)](#tab:AREval). Without a module for anaphora resolution, the
anaphor just translates to whatever is provided in the bilingual dictionary,
which in these pairs is the male singular possessive determiner.


**Table:**[ht]
<!-- centering -->
(Caption: A preliminary evaluation of translation with and without anaphora
resolution (AR) in the pipeline. Accuracy is the percentage of anaphors
translated correctly.)
<a id="tab:AREval">(¶ tab:AREval)</a>


|
| ---- | ---- | ---- | ---- |
|  |  **Number of**  |  | <!-- FIXME: multicolumn 2 c -->{**Accuracy (%)**} |
| **Systems** | **anaphors evaluated** | **Without AR** | **With AR**|
| **Spanish–English** | 120 | 29.2 | 54.2|
| **Catalan–Italian** | 108 | 83.3 | 75.0|


<!-- end table -->

For Spanish–English translation, use of the module led to an increase in
accuracy of anaphor translation, but for Catalan–Italian it resulted in a
slight decrease in the accuracy of resolution. It is important to note here that
the results without anaphora resolution for Catalan–Italian, where all targeted
anaphors by default are translated as singular, still showed an accuracy of
83.3%.  This indicates that the test data was not evenly distributed in terms
of the grammatical number of the antecedents of these anaphors.

It is also important to note that the saliency indicators and their respective
scores can be tuned to the domain of the text to get better results. In the
preliminary evaluation, the rule-set was modified after an initial look at the
results. For example, since the Spanish-English evaluation data was transcribed
speech data (Europarl), we were able to add an “impeding indicator” to
patterns that contained a proper noun followed by a comma, which attaches a
slight negative score to such patterns.  These are patterns that are likely to
be the speaker addressing an interlocutor, such as *Madam President*,
*Mister Speaker*, etc.  The interlocutor in these examples is likely to
not be the antecedent for a third-person possessive determiner anaphor that
follows in the context.

#### Future Work<a id="sec:ARFutureIdeas">(¶ sec:ARFutureIdeas)</a>
For now, the linguistic markers used by the anaphora resolution module and their
corresponding scores need to be manually defined by language experts.  The
markers provide linguistic cues for anaphora resolution and the scores are
arrived upon empirically.

If these scores can be learnt from a corpus, it would make it much simpler to
have an anaphora module with decent accuracy. Since the scope of the rules would
be largely defined, it would require much less data to learn the scores as
compared to training a corpus-based (machine learning) model to perform anaphora
resolution from scratch.

Another idea is to learn these scores from related languages, as the linguistic
cues for anaphora resolution shouldn’t vary much among related language pairs.
For example, the rules and scores can be learnt from Spanish, which has abundant
data, and applied to Catalan, which is a low-resource language.

## Supporting minoritised languages <a id="sec:LinguisticsOfEnden">(¶ sec:LinguisticsOfEnden)</a>

It is argued by [(cites: kornai2013digital)](#kornai2013digital) that many languages that are not considered
endangered do not have a sufficient level of access to language technology to
survive (i.e., maintain intergenerational transmission) in the digital age.  He
presents evidence of a “massive die-off caused by the digital divide,” and
suggests that access to language technology is critical for the continued
survival of any currently used language.

We consider MT to be a crucial part of this access to language technology.
Specifically, MT allows speakers of a low-resource language to access resources
in other languages by translating them into their own language.  Additionally,
MT enables much more efficient translation of content into low-resource
languages—for example, a small team of speakers of a low-resource language may
use MT to quickly translate Wikipedia pages from a language with large numbers
of high-quality Wikipedia pages.  This, of course, requires some attention to
post-editing the results of MT, but that is often far less work than translating
the information by hand.

It must be stated that the Apertium community does not consider MT to be a
single solution for making production-ready translations of texts like marketing
materials, literature, and legal documents—a perception that we have
encountered anecdotally.  Any production-ready translation absolutely requires
at a minimum an editor who knows the target language well, and preferably also
with expertise in translation from the source language.  In such environments,
MT is simply a solution that reduces the time investment for human translators
to produce a quality translation.  It is also meant as a tool for people who do
not know the source language to make sense of material in that language.  In
these ways, MT can be a useful tool for speakers of low-resource languages.

Apertium is designed for rule-based MT.  In reference to using corpus-based
approaches to developing MT systems for low-resource languages,
[(cites: martín-mor2017technologies)](#martín-mor2017technologies) states that “most minoritised languages \dots do not
have a sufficient number of texts in digital format, because of a lack of
digital texts, a lack of consensus on the standardisation models, etc. In those
cases, Rule-Based Machine Translation (RBMT) is especially useful, since rules
can be manually written even when languages are not fully standardised”.   In
other words, what can be done with corpus-based approaches is limited when the
amount of parallel text is limited.  That said, Apertium is open to leveraging
corpus-based methods as much as possible given the limitations, as outlined in
Section [(see: sec:HyberdisationOFApertium)](#sec:HyberdisationOFApertium).  In reality, many Apertium pairs are
technically hybrid MT systems, although the level of incorporation of
corpus-based methods can vary from absolutely none to a rather large amount with
recent advancements.

### Released translation pairs<a id="sec:ReleasedLan">(¶ sec:ReleasedLan)</a>


**Table:**[t]
<!-- centering -->
(Caption: Released translation systems per language family and sub-family.)
<a id="tab:Lang">(¶ tab:Lang)</a>
<!-- scalebox 0.97  -->



|
| ---- | ---- | ---- | ---- | ---- |
|  |   |   |  | <!-- FIXME: multicolumn 2 c -->{**Translation systems** |
| **Language family** |  | **Languages**  | **In-family** |  **Out-of-family** |
| **Afro-Asiatic** | **Semitic** | 2 | 1 | 0  |
| **Austronesic** | **Malayo-Polynesian** | 2 | 1 | 0|
| **Indo-European** |  | 34 | 44 | 3 |
|  | **Celtic** | 2 | 0 | 2 |
|  | **Germanic** | 8 | 7 | 9 |
|  | **Indo-Iranian** | 2 | 1 | 0 |
|  | **Romance** | 12 | 19 | 8 |
|  | **Slavic** | 9 | 6 | 2 |
|  | **Constructed** | 1 | 0 | 4|
| **Turkic** |  | 4 | 2 | 0 |
| **Uralic** | **Finno-Ugric** | 1 | 0 | 1 |
| **Basque** |  | 1 | 0 | 2 |
| **Total** |  | 44 | 48 | 3 |

}
<!-- end table* -->


**Table:**[ht]
<!-- centering -->
(Caption: Released translation pairs with available evaluation data. Coverage is
the percentage of tokens which receive at least one analysis from the
morphological analyser. WER (Word Error Rate), PER (Position-independent
Word Error Rate), and BLEU scores are computed against a reference
translation. A relatively low WER/PER score or a relatively high BLEU score
generally denotes better translation quality.)
<a id="tab:NmRB">(¶ tab:NmRB)</a>
<!-- scalebox 0.87  -->

\begin{threeparttable


|
| ---- | ---- | ---- | ---- | ---- |
| **Systems** | **Coverage (%)** | **WER (%)**  | \textbf {PER (%)} |  **BLEU (0–1)** |
| **Aragonese–Spanish**\tnote{a}  | 94.33 | 11.61–14.12 |  | 0.72–0.79 |
**Belarusian–Russian**\tnote{b}
|  | 84.3 | 25.72 |    |  |
**Breton–French**\tnote{c}
|  | 87–90 | 38 | 22 |  |
**Catalan–Aragonese**\tnote{w}
|  | 87.6–93.2 | 19.37 | 17.85 |  |
**Catalan–Italian**\tnote{d}
|  | 94.7 | 14.2 |    |  |
**Catalan–Romanian**\tnote{e}
|  | 88.7 |  | 29 |  |
**Catalan–Sardinian**\tnote{f}
|  | 94.4 | 20.5 | 13.9 |  |
**Danish–Bokmål Norwegian**\tnote{g}
|  | 88.1–95.9 | 10.87 |    |  |
**Danish–Nynorsk Norwegian**\tnote{h}
|  | 87.3–92.7 | 13.64–22.64 |  |
**French–Arpitan**\tnote{v}
|  | 92.8–95.8 | 5.7 |    |  |
**French–Occitan**\tnote{i}
|  | 92.3 | 10.0 |    |  |
**Italian–Catalan**\tnote{j}
|  | 91.2 | 15.7 |    |  |
**Italian–Sardinian**\tnote{k}
|  | 89.3–96.4 | 9.9 |    |  |
**North Sámi–Bokmål Norwegian**\tnote{l}
|  | 77.52–94.72 | 39.68–53.31 |    |  |
**Nynorsk–Bokmål Norwegian**\tnote{m}
|  | 92.6–99.2 | 10.71 |    |  |
**Portuguese–Catalan**\tnote{n}
|  | 91.4 | 14.0 |    |  |
**Romanian–Catalan**\tnote{o}
|  | 86.8 |  | 46 |  |
**Russian–Belarusian**\tnote{q}
|  | 83.6 | 23.93 |    |  |
| **Spanish–Aragonese**\tnote{r}  | 95.22 | 16.83–19.37 |  | 0.65–0.71 |
**Serbo-Croatian–Macedonian**\tnote{s}
|  | 74.5–90.96 | 48.33 | 48.33 | 0.36 |
**Swedish–Danish**\tnote{t}
|  | 83.7–88.0 | 31 |    |  |
| **Ukranian–Russian**\tnote{p} | 80.9–90.0 | 14.74 |  |  |
**Welsh–English**\tnote{u}
|  |  | 53.40–64.94 | 27.22–34.35 | 0.16–0.32 |

\begin{tablenotes}
* [a] [(cites: martinez2012free)](#martinez2012free) 

* [b] <http://wiki.apertium.org/wiki/Belarusian_and_Russian/Work_plan> 

* [c] [(cites: tyers2009rule, tyers2010rule)](#tyers2009rule, tyers2010rule) 

* [d] <http://wiki.apertium.org/wiki/Hectoralos/GSOC_2019_final_report> 

* [e] <http://wiki.apertium.org/wiki/Romanian_and_Catalan/GSOC_2018> 

* [f] [(cites: fronteddu2017eina)](#fronteddu2017eina) 

* [g] <http://wiki.apertium.org/wiki/Scandinavian_MT_project>

* [h] <http://wiki.apertium.org/wiki/Scandinavian_MT_project> 

* [i] <http://wiki.apertium.org/wiki/User:Capsot/GSOC_2018_Occitan_French>

* [j] <http://wiki.apertium.org/wiki/Hectoralos/GSOC_2019_final_report> 

* [k] [(cites: tyers2017rule)](#tyers2017rule) 

* [l] [(cites: trosterud2012evaluating)](#trosterud2012evaluating) 

* [m] <http://wiki.apertium.org/wiki/Scandinavian_MT_project> 

* [n] <http://wiki.apertium.org/wiki/Hectoralos/GSOC_2019_final_report> 

* [o] <http://wiki.apertium.org/wiki/Romanian_and_Catalan/GSOC_2018> 

* [p] <http://wiki.apertium.org/wiki/Russian_and_Ukrainian/Work_plan> 

* [q] <http://wiki.apertium.org/wiki/Belarusian_and_Russian/Work_plan> 

* [r] [(cites: martinez2012free)](#martinez2012free) 

* [s] [(cites: peradin2012rule)](#peradin2012rule) 

* [t] <http://wiki.apertium.org/wiki/Scandinavian_MT_project>

* [u] [(cites: tyers2009apertiumcy)](#tyers2009apertiumcy)

* [v] <https://wiki.apertium.org/wiki/Hectoralos/GSOC_2020_rapport_final>

* [w] <http://wiki.apertium.org/wiki/Aragonese_and_Catalan/Evaluation>
\end{tablenotes}
\end{threeparttable}
}
<!-- end table* -->


As of December 2020, there are 51 translation pairs released, corresponding to
44 languages of 6 language families (Table  [(see: tab:Lang)](#tab:Lang)). See
Appendix [(see: app:translationPairs)](#app:translationPairs) for the full list. The vast majority of the
languages are Indo-European—and many of these are Romance, Slavic, or Germanic
languages. Non Indo-European languages are Afro-Asiatic (Arabic and Maltese),
Austronesian (Indonesian and Malay), Turkic (Crimean Tatar, Kazakh, Tatar and
Turkish), Uralic (North-Sámi) and isolates (Basque). Table [(see: tab:NmRB)](#tab:NmRB) shows
quality metrics for some of the released pairs.

For the most part, translation systems are constructed between languages of the
same family. There are only three released translators between unrelated
languages: North Sámi–Norwegian (Bokmål), Basque–English, and Basque–Spanish.
Examples of translation systems developed for translation between closely
related languages include Malay–Indonesian, Maltese–Arabic, Dutch–Afrikaans
[(cites: otte2011rapid)](#otte2011rapid), Crimean Tatar–Turkish [(cites: gokirmak2017dependency)](#gokirmak2017dependency), and
Kazakh–Tatar [(cites: salimzyanov2013free)](#salimzyanov2013free). Even inside subfamilies, translation
systems for Romance languages typically target another Romance language (and not
other Indo-European languages), and the same is true of Germanic into Germanic
and even South Slavic into South Slavic, West Slavic into West Slavic, and East
Slavic into East Slavic. There is a heavier density of translation pairs between
Romance languages (19 for 12 languages), between Slavic languages (6 for 9
languages), and between Scandinavian languages (5 for 5 languages or language
varieties). Two languages tend to break the close-proximity rule: English and
Esperanto, which have a significant number of connections with languages outside
their sub-family. (footnote: We consider Esperanto within a specific constructed
subfamily of Indo-European languages.) Despite this, there is no central
language in Apertium: there are 9 translators into both English and Spanish, 8
into Catalan, 4 into both Norwegian (Bokmål) and Esperanto, 3 into both French
and Portuguese, etc.

The initial objective of Apertium was to create free and open-source resources
for the languages of Spain. In light of the increasing breadth of the published
pairs and ongoing work leveraging the Apertium platform (see
Table [(see: tab:NmRB)](#tab:NmRB)), particularly thanks to funding from the Google Summer of
Code programme, it may be stated that Apertium has since become a major venue
for creating resources for minoritised and low-resource languages in Europe and
has shown potential as a language technology platform supporting languages all
around the world.

Eleven of the forty-four languages with released translators are considered
vulnerable or endangered [(cites: moseley2010atlas)](#moseley2010atlas): Aragonese, Arpitan, Asturian,
Basque, Belarusian, Breton, gCrimean Tatar, North Sámi, Occitan, Sardinian, and
Welsh. Other languages hold minority status in their states, like Afrikaans,
Catalan, Galician, Silesian, and Tatar. Recent work on other under-resourced
and/or minoritised languages includes Bashqort [(cites: tyers2012prototype)](#tyers2012prototype),
Bengali [(cites: faridee2009development)](#faridee2009development),
Chukchi (footnote: <https://summerofcode.withgoogle.com/archive/2017/projects/4736366453719040/>),
Gagauz [(cites: bayatli2018finite)](#bayatli2018finite),
Guarani (footnote: <https://summerofcode.withgoogle.com/archive/2018/projects/5434804640153600/>),
Qaraqalpaq (footnote: <https://www.google-melange.com/archive/gsoc/2014/orgs/apertium/projects/beknazar.html>,
<https://summerofcode.withgoogle.com/archive/2019/projects/6137485212516352/>,
<https://summerofcode.withgoogle.com/archive/2020/projects/4815970624864256/>),
Karelian [(cites: pirinen2019workflows)](#pirinen2019workflows), Kurmanji
Kurdish (footnote: <https://summerofcode.withgoogle.com/archive/2016/projects/5069737520267264/>),
Sorani Kurdish [(cites: TranslatorsWithoutBorders2016)](#TranslatorsWithoutBorders2016),
Lingala (footnote: <https://summerofcode.withgoogle.com/archive/2019/projects/4582884889853952/>),
Malayalam (footnote: <https://www.google-melange.com/archive/gsoc/2014/orgs/apertium/projects/aboobacker.html>),
Marathi [(cites: ravishankar2017finite)](#ravishankar2017finite),
Punjabi (footnote: <https://summerofcode.withgoogle.com/archive/2020/projects/6209442061746176/>),
Cuzco
Quechua (footnote: <https://www.google-melange.com/archive/gsoc/2012/orgs/apertium/projects/pato_yap.html>),
Lule-Saami [(cites: tyers2009developing)](#tyers2009developing), South-Saami [(cites: antonsen2017northsaami,
tyers2009developing)](#antonsen2017northsaami,
tyers2009developing),
Sakha (footnote: <https://summerofcode.withgoogle.com/archive/2018/projects/4877442304966656/>),
Sicilian (footnote: <https://summerofcode.withgoogle.com/archive/2016/projects/5883995808071680/>),
Iraqi Türkman (footnote:  <https://github.com/apertium/apertium-tki>,
<https://wiki.apertium.org/wiki/Apertium-tki>), and
Uyghur (footnote: <https://summerofcode.withgoogle.com/archive/2018/projects/5988796768190464/>,
<https://summerofcode.withgoogle.com/archive/2019/projects/5106764196872192/>).
In some cases, coordinated efforts are under way to develop resources for entire
language families, such as for Turkic languages [(cites: washington2020free)](#washington2020free).

### Other languages and work ahead<a id="OtherLanguages">(¶ OtherLanguages)</a>


**Table:**[t]
<!-- centering -->
(Caption: A selection of unreleased translation pairs with published results.
Coverage is the percentage of tokens which receive at least one analysis
from the morphological analyser. WER (Word Error Rate), PER
    (Position-independent Word Error Rate), and BLEU scores are computed against
a reference translation. A relatively low WER/PER score or a relatively high
BLEU score generally denotes better translation quality.)
<a id="tab:WER&PER&OOV">(¶ tab:WER&PER&OOV)</a>
<!-- scalebox 0.93  -->

\begin{threeparttable


|
| ---- | ---- | ---- | ---- | ---- |
| **Systems** | **Coverage (%)** | **WER (%)**  | \textbf {PER (%)} |  **BLEU (0–1)** |
| **Kazakh–Turkish**\tnote{x} | 83.42 | 45.77   | 41.69  | 0.17  |
| **North Sámi—Finnish**\tnote{y} | 76.81 | 34.24 |  -  |  - |
| **North-Saami–South-Saami**\tnote{z} | 87.4 | 54.84 |  30.94   |  |
| **Tatar–Bashkir**\tnote{aa} | 70.19 | 8.97 |  -  |  -|

\begin{tablenotes}
* [x] [(cites: bayatli2018rule)](#bayatli2018rule) 

* [y] [(cites: johnson2017north)](#johnson2017north) 

* [z] [(cites: antonsen2017northsaami)](#antonsen2017northsaami) 

* [aa] [(cites: tyers2012prototype)](#tyers2012prototype) 

\end{tablenotes}
\end{threeparttable}
}
<!-- end table* -->


In Table [(see: tab:WER&PER&OOV)](#tab:WER&PER&OOV), we show the performance of some unreleased
machine-translation systems from previous reports or publications.

An improvement in performance could be possible for these systems with time by
improving morphological disambiguation, adding more stems into the dictionaries,
and adding or refining lexical and structural transfer rules.

In addition to the languages pairs which have been mentioned in
Table [(see: tab:WER&PER&OOV)](#tab:WER&PER&OOV), there are many other pairs that are in various
stages of development but have not been systematically evaluated yet, such as
Basque–English, Cuzco Quechua–Spa\-nish, Guaraní–Spa\-nish,
Karelian–Finnish, Kazakh–Kyrgyz, Kazakh–Russian, Lingala–English,
Marathi–Hin\-di, Sorani Kurdish–Kurmanji Kurdish, Turkish–Uzbek, and
Uzbek–Qaraqalpaq, among others.

## Supplementary tools<a id="sec:OtherValuableTools">(¶ sec:OtherValuableTools)</a>

This section highlights supplementary tools maintained by Apertium that are
useful for developers as well as end-users. Apertium-viewer
(Section [(see: sec:ApertiumViewer)](#sec:ApertiumViewer)) is particularly useful for developers
interacting with Apertium resources.  The Apertium website software
(Section [(see: sec:website)](#sec:website)) provides access to free and unlimited translation,
morphological analysis, and several under-development features like dictionary
lookup and a spell-checking interface, each of which can prove very useful for
end-users who do not wish to install any software locally.

### Apertium-viewer<a id="sec:ApertiumViewer">(¶ sec:ApertiumViewer)</a>
Apertium-viewer is a tool that makes it straightforward for users to view and
edit the output of the various stages of an Apertium translation. It reads a
translation pair’s “mode” configuration file, where the specific pipeline for
the translator is defined. It displays how a text changes as it cascades through
the modules, from the source to the target language. The user can change the
text string at every stage for debugging purposes. This tool can be useful for
understanding translation pairs and debugging translations.

### Website software<a id="sec:website">(¶ sec:website)</a>
Apertium offers an open-source web API and customisable website
front-end (footnote: <https://apertium.org>) [(cites: cherivirala2018apertium)](#cherivirala2018apertium).
Apart from translating text, users can provide a URL to a webpage, which will be
translated with the formatting preserved. Note that the Apertium API and website
software can also be deployed by anyone for any purpose. The software also
provides a front-end to morphological transducers, and there are a number of
beta features under development.

One of these features is multi-step translation, where a user can use the
interface to translate from one language to another for which there isn’t an
Apertium translation pair via one or more pivot languages. (footnote: This feature
is enabled and available at <https://beta.apertium.org/>.)

Another feature under development is dictionary lookup, where a user may use the
Apertium website as an online dictionary.  That is, a word is not simply
translated, but all possible translations of the word are provided.  The
community hopes to include some additional features with dictionary lookup,
including automatic reverse lookups (so that a user has a better understanding
of the results), grammatical information (such as the gender of nouns or the
conjugation paradigms of verbs), and information about MWEs.

A suggestions feature allows users to suggest corrections to translations. This
is especially helpful as developers can incorporate these corrections back into
the systems.

One last feature under development is a spell-checking interface.  This feature
provides users with a simple interface to check the spelling of words in a text,
and to be offered suggestions for misspelled words. It is noteworthy that there
are no known spell checkers available for some of the languages with
dictionaries in Apertium, such as Arpitan.

## Conclusion<a id="sec:Conclusion">(¶ sec:Conclusion)</a>
We have presented the latest updates to Apertium, a free and open-source
platform for machine translation, with a focus on MT for low-resource languages.
These updates include approaches to hybridisation of Apertium modules with
corpus-based approaches, new modules that are available for the Apertium RBMT
pipeline, and newly released languages pairs.

The new modules in the pipeline are all optional since they may be useful for
some specific languages pairs, but would not significantly improve others.  With
an increasing number of released language pairs, Apertium becomes a preferred
vehicle for translation to and from low-resource languages, which are not as
easily implemented using widely advocated neural approaches to MT due to
sparsity of available text, and are also not considered economical for corporate
work.  In addition, the different sub-components of translation pairs can be and
are used independently to produce other types of resources for these languages,
such as electronic dictionaries, a tool for searches in electronic corpora
[(cites: Saykhunov2019[e.g.,])](#Saykhunov2019), spell
checkers, (footnote: Including, for example,
<http://grammar.corpus.tatar/index_en.php?of=search/spellchecker.php>) and
tools supporting language learning and revitalisation
[(cites: katinskaia2018revita,ivanova2019tools[e.g.,])](#katinskaia2018revita,ivanova2019tools).


# References

* <a id="forcada2011apertium">**forcada2011apertium**</a>:
    * Author: Mikel L. Forcada and Mireia Ginestí  Rosell  and Jacob Nordf...
    * Journal: Machine Translation
    * Title: Apertium: a free/open-source platform for rule-based machine
    * Year: 2011
* <a id="linden2011hfst">**linden2011hfst**</a>:
    * author: Lindén, Krister and Axelson, Erik and Hardwick, Sam and Piri...
    * journal: Systems and Frameworks for Computational Morphology
    * pages: 67–85
    * publisher: Springer
    * title: Hfst—framework for compiling and applying morphologies
    * year: 2011
* <a id="bick2015cg">**bick2015cg**</a>:
    * author: Eckhard Bick and Tino Didriksen
    * booktitle: Proceedings of the 20th Nordic Conference of Computational
    * issn: 1650-3740
    * pages: 31-39
    * publisher: Linköping University Electronic Press, Linköpings
    * title: CG-3 – Beyond Classical Constraint Grammar
    * year: 2015
* <a id="tyers2012flexible">**tyers2012flexible**</a>:
    * author: Tyers, Francis M and Sánchez-Martínez, Felipe and
    * publisher: European Association for Machine Translation
    * title: Flexible finite-state lexical selection for rule-based machi...
    * year: 2012
* <a id="marting2014fst">**marting2014fst**</a>:
    * author: Matthew Marting and Kevin Brubeck Unhammer
    * booktitle: Proceedings of the 9th Conference on Language Resources and
    * pages: 19–24
    * title: FST Trimming: Ending Dictionary Redundancy in {Apertium}
    * year: 2014
* <a id="sanchez2006speeding">**sanchez2006speeding**</a>:
    * author: Felipe Sánchez-Martínez and Juan Antonio Pérez-Ortiz and Mik...
    * booktitle: Proceedings of the 5th Mexican International Conference on
    * pages: 844–854
    * title: Speeding up target language driven part-of-speech tagger tra...
    * year: 2006
* <a id=" sanchez2007training">** sanchez2007training**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="karlsson1995constraint">**karlsson1995constraint**</a>:
    * address: Berlin
    * author: Fred Karlsson and Atro Voutilainen and Juha Heikkilä and Art...
    * publisher: Mouton de Gruyter
    * title: Constraint Grammar: A Language-Independent System for Parsin...
    * year: 1995
* <a id="zhang2011syntactic">**zhang2011syntactic**</a>:
    * author: Zhang, Yue  and Clark, Stephen
    * doi: 10.1162/coli_a_00037
    * journal: Computational Linguistics
    * number: 1
    * pages: 105–151
    * title: Syntactic Processing Using the Generalized Perceptron and Be...
    * url: https://www.aclweb.org/anthology/J11-1005
    * volume: 37
    * year: 2011
* <a id="tyers2014unsupervised">**tyers2014unsupervised**</a>:
    * author: F. M Tyers and F. Sánchez-Martínez and M. L. Forcada
    * booktitle: Proceedings of the 18th Annual Conference of the European
    * pages: 145–153
    * title: Unsupervised training of maximum-entropy models for lexical
    * year: 2014
* <a id="hutchison2006using">**hutchison2006using**</a>:
    * author: Sánchez-Martínez, Felipe and Ney, Hermann
    * booktitle: Advances in Natural Language Processing
    * doi: 10.1007/11816508_75
    * editor: Salakoski, Tapio and Ginter, Filip and Pyysalo, Sampo and
    * editorb: Hutchison, David and Kanade, Takeo and Kittler, Josef andKle...
    * editorbtype: redactor
    * isbn: 978-3-540-37334-6 978-3-540-37336-0
    * langid: english
    * location: Berlin, Heidelberg
    * pages: 756–767
    * publisher: Springer Berlin Heidelberg
    * title: Using Alignment Templates to Infer Shallow-Transfer Machine
    * url: http://link.springer.com/10.1007/11816508_75
    * urldate: 2021-02-01
    * volume: 4139
    * year: 2006
* <a id="sanchez2007automatic">**sanchez2007automatic**</a>:
    * author: Sánchez-Martínez, Felipe and Forcada, Mikel L.
    * booktitle: Proceedings of the 11th Conference on Theoretical and
    * editor: Way, Andy and Gawronska, Barbara
    * isbn: 978-91-977095-0-7
    * pages: 181–190
    * publisher: Skövde University Studies in Informatics
    * title: Automatic induction of shallow-transfer rules for open-sourc...
    * volume: 2007:1
    * year: 2007
* <a id="
martinez2008using">**
martinez2008using**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="sanchez2009inferring">**sanchez2009inferring**</a>:
    * author: Felipe Sánchez-Martínez and Mikel L. Forcada
    * journal: Journal of Artificial Intelligence Research
    * pages: 605–635
    * title: Inferring shallow-transfer machine translation rules from sm...
    * volume: 34
    * year: 2009
* <a id=" sanchez-cartagena2015generalised">** sanchez-cartagena2015generalised**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="bayatli2019unsupervised">**bayatli2019unsupervised**</a>:
    * author: Bayatli, Sevilay and Kurnaz, Sefer and Ali, Aboelhamd and
    * doi: 10.6688/JISE.202003_36(2).0010
    * journal: Journal of Information Science and Engineering
    * number: 2
    * pages: 309–322
    * title: Unsupervised weighting of transfer rules in rule-based machi...
    * volume: 36
    * year: 2020
* <a id="swanson2020tree">**swanson2020tree**</a>:
    * author: Daniel G. Swanson and Jonathan N. Washington and Francis M. ...
    * journal: Machine Translation
    * note: to appear
    * pubstate: to appear
    * title: A Tree-Based Structural Transfer Module for the Apertium Mac...
    * year: 2021
* <a id="constant2017multiword">**constant2017multiword**</a>:
    * author: Constant, Mathieu and Eryiğit, Gülşen and Monti, Johanna and...
    * doi: 10.1162/COLI_a_00302
    * journal: Computational Linguistics
    * number: 4
    * pages: 837-892
    * title: Multiword Expression Processing: A Survey
    * volume: 43
    * year: 2017
* <a id="lappin1994algorithm">**lappin1994algorithm**</a>:
    * author: Lappin, Shalom  and Leass, Herbert J.
    * journal: Computational Linguistics
    * number: 4
    * pages: 535–561
    * title: An Algorithm for Pronominal Anaphora Resolution
    * url: https://www.aclweb.org/anthology/J94-4002
    * volume: 20
    * year: 1994
* <a id="baldwin1997cogniac">**baldwin1997cogniac**</a>:
    * author: Baldwin, Breck
    * booktitle: Proceedings of a Workshop on Operational Factors in Practica...
    * doi: 10.3115/1598819.1598825
    * eventtitle: a Workshop
    * langid: english
    * location: Madrid, Spain
    * pages: 38–45
    * publisher: Association for Computational Linguistics
    * shorttitle: CogNIAC
    * title: {CogNIAC}: high precision coreference with limited knowledge...
    * url: http://portal.acm.org/citation.cfm?doid
    * urldate: 2020-10-07
    * year: 1997
* <a id="trouilleux2002rule">**trouilleux2002rule**</a>:
    * author: Trouilleux, François
    * journal: 4th Discourse Anaphora and Anaphor Resolution Colloquium
    * langid: english
    * pages: 7
    * title: A Rule-based Pronoun Resolution System for French
    * year: 2002
* <a id="lee2013deterministic">**lee2013deterministic**</a>:
    * author: Heeyoung Lee and Angel Chang and Yves Peirsman and Nathanael
    * journal: Computational Linguistics
    * number: 4
    * title: Deterministic coreference resolution based on entity-centric...
    * volume: 39
    * year: 2013
* <a id="loaiciga2015rule">**loaiciga2015rule**</a>:
    * author: Loáiciga, Sharid and Wehrli, Eric
    * booktitle: Proceedings of the Second Workshop on Discourse in Machine
    * doi: 10.18653/v1/W15-2512
    * eventtitle: Proceedings of the Second Workshop on Discourse in Machine
    * langid: english
    * location: Lisbon, Portugal
    * pages: 86–93
    * publisher: Association for Computational Linguistics
    * title: Rule-Based Pronominal Anaphora Treatment for Machine Transla...
    * url: http://aclweb.org/anthology/W15-2512
    * urldate: 2020-10-07
    * year: 2015
* <a id="zeldes2016when">**zeldes2016when**</a>:
    * author: Amir Zeldes and Shuo Zhang
    * booktitle: Proceedings of the NAACL2016 Workshop on Coreference
    * location: San Diego, USA
    * pages: 92–101
    * title: When Annotation Schemes Change Rules Help: A Configurable Ap...
    * year: 2016
* <a id="mitkov1999multilingual">**mitkov1999multilingual**</a>:
    * author: Ruslan Mitkov’s
    * journal: Machine Translation
    * pages: 281-299
    * title: Multilingual Anaphora Resolution
    * volume: 14
    * year: 1999
* <a id="kornai2013digital">**kornai2013digital**</a>:
    * NOmonth: 10
    * NOurl: https://doi.org/10.1371/journal.pone.0077056
    * author: Kornai, András
    * doi: 10.1371/journal.pone.0077056
    * journal: PLOS ONE
    * number: 10
    * pages: 1–11
    * publisher: Public Library of Science
    * title: Digital Language Death
    * volume: 8
    * year: 2013
* <a id="martín-mor2017technologies">**martín-mor2017technologies**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="martinez2012free">**martinez2012free**</a>:
    * author: Juan Pablo {Martínez Cortés} and Jim O’Regan and Francis Tye...
    * booktitle: Proceedings of the Eight International Conference on Languag...
    * publisher: European Language Resources Association (ELRA)
    * title: Free/Open Source Shallow-Transfer Based Machine Translation ...
    * year: 2012
* <a id="tyers2009rule">**tyers2009rule**</a>:
    * author: Francis M. Tyers
    * booktitle: Proceedings of the 13th Annual Conference of the European
    * pages: 213-218
    * title: Rule-based augmentation of training data in {Breton–French
    * year: 2009
* <a id=" tyers2010rule">** tyers2010rule**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="fronteddu2017eina">**fronteddu2017eina**</a>:
    * author: Gianfranco Fronteddu and Hèctor {Alòs i Font} and Francis M.
    * doi: 10.21814/lm.9.2.255
    * journal: Linguamática
    * number: 3
    * pages: 3–20
    * title: Una eina per a una llengua en procés d’estandardització: el
    * volume: 9
    * year: 2017
* <a id="tyers2017rule">**tyers2017rule**</a>:
    * author: Francis M. Tyers and Gianfranco Fronteddu and Hèctor {Alòs i
    * doi: 10.1515/pralin-2017-0022
    * issue: 108
    * journal: The Prague Bulletin of Mathematical Linguistics
    * pages: 221–232
    * title: Rule-based machine translation for the {Italian–Sardinian
    * year: 2017
* <a id="trosterud2012evaluating">**trosterud2012evaluating**</a>:
    * author: Trond Trosterud and Kevin Brubeck Unhammer
    * booktitle: Third International Workshop on Free/Open-Source Rule-Based
    * pages: 13–25
    * title: Evaluating North Sámi to Norwegian assimilation RBMT
    * year: 2012
* <a id="peradin2012rule">**peradin2012rule**</a>:
    * author: Hrvoje Peradin and F. M. Tyers
    * booktitle: Third International Workshop on Free/Open-Source Rule-Based
    * pages: 55–63
    * title: A rule-based machine translation system from Serbo-Croatian ...
    * year: 2012
* <a id="tyers2009apertiumcy">**tyers2009apertiumcy**</a>:
    * author: Francis M. Tyers and Kevin Donnelly
    * journal: The Prague Bulletin of Mathematical Linguistics
    * pages: 57–66
    * title: apertium-cy – a collaboratively-developed free RBMT system ...
    * volume: 91
    * year: 2009
* <a id="otte2011rapid">**otte2011rapid**</a>:
    * author: Pim Otte and Francis M. Tyers
    * booktitle: EAMT 2011: proceedings of the 15th conference of the Europea...
    * title: Rapid rule-based machine translation between {Dutch} and
    * year: 2011
* <a id="gokirmak2017dependency">**gokirmak2017dependency**</a>:
    * author: M. Gökırmak and F. M Tyers
    * booktitle: Proceedings of the the International Conference on Dependenc...
    * title: A dependency treebank for {Kurmanji Kurdish}
    * year: 2017
* <a id="salimzyanov2013free">**salimzyanov2013free**</a>:
    * AUTHOR: Ilnar Salimzyanov and Jonathan North Washington and Francis
    * EDITOR: K. Sima’an and M.L. Forcada and D. Grasmick and H. Depraeter...
    * NOmonth: 09
    * PAGES: 175-182
    * PUBLISHER: European Association for Machine Translation
    * TITLE: A free/open-source Kazakh-Tatar machine translation system
    * URL: http://www.mt-archive.info/10/MTS-2013-Salimzyanov.pdf
    * YEAR: 2013
    * booktitle: Proceedings of the XIV Machine Translation Summit
* <a id="moseley2010atlas">**moseley2010atlas**</a>:
    * edition: 3rd
    * editor: Moseley, Christopher
    * note: Online version: http://www.unesco.org/languages-atlas/
    * place: Paris
    * publisher: UNESCO Publishing
    * title: Atlas of the World’s Languages in Danger
    * year: 2010
* <a id="tyers2012prototype">**tyers2012prototype**</a>:
    * author: Tyers, Francis M and Washington, Jonathan N and Salimzyanov,
    * booktitle: First Workshop on Language Resources and Technologies for
    * pages: 11
    * title: A prototype machine translation system for Tatar and Bashkir
    * year: 2012
* <a id="faridee2009development">**faridee2009development**</a>:
    * address: Alicante, Spain
    * author: Abu Zaher Md. Faridee and Francis M. Tyers
    * booktitle: Proceedings of the First International Workshop on
    * editor: J.A. Pérez-Ortiz and F. Sánchez-Martínez and F.M. Tyers
    * pages: 43–50
    * publisher: Universidad de Alicante. Departamento de Lenguajes y Sistema...
    * title: Development of a morphological analyser for {Bengali}
    * year: 2009
* <a id="bayatli2018finite">**bayatli2018finite**</a>:
    * address: Miyazaki, Japan
    * author: Bayatli, Sevilay and Karanfil, Güllü  and
    * booktitle: Proceedings of the Eleventh International Conference on
    * month: may
    * publisher: European Language Resources Association (ELRA)
    * title: Finite-state morphological analysis for Gagauz
    * url: https://www.aclweb.org/anthology/L18-1411
    * year: 2018
* <a id="pirinen2019workflows">**pirinen2019workflows**</a>:
    * address: Dublin, Ireland
    * author: Pirinen, Flammie A
    * booktitle: Proceedings of The 2nd Workshop on Technologies for MT of Lo...
    * title: Workflows for kickstarting RBMT in virtually No-Resource Sit...
    * year: 2019
* <a id="TranslatorsWithoutBorders2016">**TranslatorsWithoutBorders2016**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="ravishankar2017finite">**ravishankar2017finite**</a>:
    * author: V. Ravishankar and Francis M. Tyers
    * booktitle: Proceedings of The 13th International Conference on Finite
    * howpublished: (to appear)
    * title: Finite-state morphological analysis for {Marathi}
    * year: 2017
* <a id="tyers2009developing">**tyers2009developing**</a>:
    * author: Francis M. Tyers and L. Wiechetek and Trond Trosterud
    * booktitle: Proceedings of the 13th Annual Conference of the European
    * pages: 120–128
    * title: Developing prototypes for machine translation between two {S...
    * year: 2009
* <a id="antonsen2017northsaami">**antonsen2017northsaami**</a>:
    * author: Lene Antonsen and Trond Trosterud and Francis M. Tyers
    * doi: 10.3384/nejlt.2000-1533.1642
    * journal: Lecture Notes in Artificial Intelligence
    * pages: 11–27
    * title: A {North Saami} to {South Saami} Machine Translation Prototy...
    * volume: 4
    * year: 2017
* <a id="
tyers2009developing">**
tyers2009developing**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="washington2020free">**washington2020free**</a>:
    * NOyear: 2021
    * author: Jonathan N. Washington and Ilnar Salimzianov and Francis M. ...
    * booktitle: Proceedings of the Seventh International Conference on
    * location: Simferopol, Republic of Crimea
    * pubstate: to appear
    * title: Free/Open-Source technologies for Turkic languages developed...
    * year: to appear
* <a id="bayatli2018rule">**bayatli2018rule**</a>:
    * author: Bayatli, Sevilay and Kurnaz, Sefer and Salimzianov, Ilnar an...
    * booktitle: European Association for Machine Translation (EAMT)
    * pages: 49–58
    * title: Rule-based machine translation from Kazakh to Turkish
    * year: 2018
* <a id="johnson2017north">**johnson2017north**</a>:
    * author: Johnson, Ryan and Pirinen, Tommi A and Puolakainen, Tiina an...
    * booktitle: Proceedings of the 21st Nordic Conference on Computational
    * number: 131
    * organization: Linköping University Electronic Press
    * pages: 115–122
    * title: North-Sámi to Finnish rule-based machine translation system
    * year: 2017
* <a id="cherivirala2018apertium">**cherivirala2018apertium**</a>:
    * author: Cherivirala, Sushain and Chiplunkar, Shardul and Washington,
    * booktitle: Proceedings of the AMTA 2018 Workshop on Technologies for MT
    * pages: 53–62
    * title: Apertium’s Web Toolchain for Low-Resource Language Technolog...
    * url: https://www.aclweb.org/anthology/W18-2207/
    * year: 2018
* <a id="Saykhunov2019">**Saykhunov2019**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="katinskaia2018revita">**katinskaia2018revita**</a>:
    * address: Miyazaki, Japan
    * author: Katinskaia, Anisia and Nouri, Javad and Yangarber, Roman
    * booktitle: Proceedings of LREC: 11th International Conference on Langua...
    * title: Revita: a language-learning platform at the intersection of ...
    * year: 2018
* <a id="ivanova2019tools">**ivanova2019tools**</a>:
    * address: Turku, Finland
    * author: Ivanova, Sardana  and Katinskaia, Anisia  and Yangarber, Rom...
    * booktitle: Proceedings of the 22nd Nordic Conference on Computational
    * month: sep # "{–}" # oct
    * pages: 155–163
    * publisher: Linköping University Electronic Press
    * title: Tools for supporting language learning for Sakha
    * url: https://www.aclweb.org/anthology/W19-6117
    * year: 2019


\clearpage
* * *

# Appendix


## List of released languages and translation pairs<a id="app:translationPairs">(¶ app:translationPairs)</a>

The released languages are: (footnote: An asterisk (*) indicates that the language
has been released since the previous publication [(cites: forcada2011apertium)](#forcada2011apertium).
Norwegian Bokmål and Norwegian Nynorsk are considered two different languages in
Apertium since there is a translator from one to the other, which is not the
case between different varieties of Catalan, Occitan and Portuguese that are
supported in Apertium.)

<!-- multicols 3 -->

*  Afrikaans*
*  Arabic*
*  Aragonese*
*  Arpitan*
*  Asturian
*  Basque
*  Belarusian*
*  Breton
*  Bulgarian
*  Catalan
*  Danish
*  Dutch*
*  English
*  Esperanto
*  French
*  Galician
*  Hindi*
*  Icelandic
*  Indonesian*
*  Italian
*  Kazakh*
*  Macedonian
*  Malaysian*
*  Maltese*
*  Norwegian Bokmål
*  Norwegian Nynorsk
*  Occitan
*  Polish*
*  Portuguese
*  Romanian
*  Russian*
*  North Sámi*
*  Sardinian*
*  Serbo-Croatian*
*  Silesian*
*  Slovenian*
*  Spanish
*  Swedish
*  Tatar*
*  Crimean Tatar*
*  Turkish*
*  Ukrainian*
*  Urdu*
*  Welsh

<!-- /multicols -->


<!-- noindent --> The released language pairs (with indication of the translation directions and novelty) are:
<!-- multicols 2 -->

    *  Afrikaans {⇆} Dutch*
    *  Aragonese {⇆} Catalan*
    *  Aragonese {⇆} Spanish*
    *  Basque {→} English*
    *  Basque {→} Spanish
    *  Belarusian {⇆} Russian*
    *  Breton {→} French
    *  Bulgarian {⇆} Macedonian
    *  Catalan {⇆} English
    *  Catalan {→} Esperanto
    *  Catalan {⇆} French
    *  Catalan {⇆} Italian
    *  Catalan {⇆} Occitan
    *  Catalan {⇆} Portuguese
    *  Catalan {⇆} Romanian*
    *  Catalan {→} Sardinian*
    *  Catalan {⇆} Spanish
    *  Danish {⇆} Norwegian*
    *  Danish {⇆} Swedish
    *  English {⇆} Esperanto
    *  English {⇆} Galician
    *  English {⇆} Spanish
    *  French {→} Arpitan*
    *  French {→} Esperanto
    *  French {→} Occitan*
    *  French {⇆} Spanish
    *  Galician {⇆} Portuguese
    *  Galician {⇆} Spanish
    *  Hindi {⇆} Urdu*
    *  Icelandic {→} English
    *  Icelandic {⇆} Swedish*
    *  Indonesian {⇆} Malaysian*
    *  Italian {→} Sardinian*
    *  Kazakh {⇆} Tatar*
    *  Macedonian {→} English
    *  Maltese {→} Arabic*
    *  Norwegian {⇆} Swedish*
    *  Norwegian Bokmål {⇆} Nynorsk
    *  Occitan {⇆} Spanish
    *  Polish {→} Silesian*
    *  Portuguese {⇆} Spanish
    *  Romanian {→} Spanish
    *  Russian {⇆} Ukrainian*
    *  North Sámi {→} Norwegian*
    *  Serbo-Croatian {→} English*
    *  Serbo-Croatian {→} Macedonian*
    *  Serbo-Croatian {⇆} Slovenian*
    *  Spanish {→} Asturian
    *  Spanish {→} Esperanto
    *  Crimean Tatar {→} Turkish*
    *  Welsh {→} English

<!-- /multicols -->

It should be noted that many of the pairs already released in the last
publication [(cites: forcada2011apertium)](#forcada2011apertium) have been updated. For example, the
Catalan-French pair previously had a bilingual dictionary of 10,554 entries,
while in December 2020 it has 71,537.

<!-- bib style: unsrt -->

<!-- end document -->


* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

