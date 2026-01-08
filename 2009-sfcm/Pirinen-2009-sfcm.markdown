
<!-- usepackage latexsym  -->
<!-- usepackage amsmath  -->
<!-- usepackage amssymb  -->

<!-- begin document -->

<!-- if pdf -->
<!--\pdfinfo{
  /Author (Krister Linden and Miikka Silfverberg and Tommi Pirinen)
  /Title (HFST Tools for Morphology - An Efficient Open-Source Package for Consttruction of Morphological Analyzers)
  /CreationDate (D:20090501123456)
  /Subject (Finite-State Morphology)
  /Keywords (FSM;FST;Morphology)
}-->
<!-- fi -->
# <span style='font-variant: small-caps'>HFST</span> Tools for Morphology – An Efficient Open-Source Package for Construction of Morphological Analyzers ¹

<span style='font-size:8pt'>(¹ Authors' archival version: This article was published in Proceedings of SFCM 2009 in Zürich <http://sfcm2009.org>. Publisher’s version available at [Springer via doi: 10.1007/978-3-642-04131-0_3](https://dx.doi.org/10.1007/978-3-642-04131-0_3). For more information, see [Springers self archiving policy](http://www.springer.com/gp/open-access/authors-rights/self-archiving-policy/2124).)</span>

**Authors:**  Krister Lindén
and

Miikka Silfverberg
and

Tommi Pirinen

University of Helsinki

firstname.lastname@helsinki.fi



**Date:** Last modification: (date of conversion: 2026-01-02)

<!-- make title -->


**Abstract:**
Morphological analysis of a wide range of languages can be implemented
efficiently using finite-state transducer technologies. Over the last
30 years, a number of attempts have been made to create tools for
computational morphologies. The two main competing approaches have
been parallel vs. cascaded rule application. The parallel rule
application was originally introduced by Koskenniemi
[(cites: Koskenniemi83)](#Koskenniemi83) and implemented in tools like <span style='font-variant: small-caps'>TwolC</span> and
<span style='font-variant: small-caps'>LexC</span>. Currently many applications of morphologies could use
dictionaries encoding the a priori likelihoods of words and
expressions as well as the likelihood of relations to other
representations or languages. We have made the choice to create
open-source tools and language descriptions in order to let as many as
possible participate in the effort. The current article presents some
of the main tools that we have created such as <span style='font-variant: small-caps'>HFST-LexC</span>,
<span style='font-variant: small-caps'>HFST-TwolC</span> and <span style='font-variant: small-caps'>HFST-Compose-Intersect</span>.  We evaluate
their efficiency in comparison to some similar tools and libraries. In
particular, we evaluate them using several full-fledged morphological
descriptions. Our tools compare well with similar open source tools,
even if we still have some challenges ahead before we can catch up
with the commercial tools. We demonstrate that for various reasons a
parallel rule approach still seems to be more efficient than a
cascaded rule approach when developing finite-state morphologies.
<!-- end abstract -->

## Introduction

Morphological analysis of a wide range of languages can be implemented
efficiently using finite-state technologies based on finite-state
transducers. Our goal is to implement efficient tools for creating and
manipulating finite-state transducer morphologies for different uses
and purposes. The task is daunting and we cannot do it alone.

Over the last 30 years, a number of attempts have been made to create
tools for computational morphologies and some of them have withstood
the test of time better than others. A major effort that has shaped
the landscape and incorporated many lasting ideas is the morphological
development tools created by Xerox. It started with the insight that
we can use transducers to describe or encode phonological processes
and relate various levels of linguistic abstraction using tools like
<span style='font-variant: small-caps'>TwolC</span> introduced by Koskenniemi and Karttunen
[(cites: Koskenniemi83,Karttunen87,Karttunen92)](#Koskenniemi83,Karttunen87,Karttunen92). To efficiently compile
large-scale lexicons into transducers, we need special lexicon
compilers like <span style='font-variant: small-caps'>LexC</span> described by Karttunen
[(cites: Karttunen93,Karttunen94)](#Karttunen93,Karttunen94).

Such tools do not solve all the problems. Writing full-scale
dictionaries in <span style='font-variant: small-caps'>LexC</span> may well be compared to having
programmers write sophisticated applications in C without access to
any of the modern high-level libraries. It is possible, but unless it
is done in some principled way, one may easily end up with
spaghetti-code that is difficult to maintain. This is not the fault of
the lexicon compiler, but the general programming solution is to
create several descriptions that are small and independent,
i.e. modular.  With this insight and as computers became more
powerful, the initial calculus that was conceived for abstract objects
like automata and transducers in <span style='font-variant: small-caps'>TwolC</span> and <span style='font-variant: small-caps'>LexC</span> was
expanded and migrated into the lexical programming environment
<span style='font-variant: small-caps'>xfst</span> documented by Beesly and Karttunen [(cites: beesley03)](#beesley03),
where smaller lexical modules for various purposes can be tailored and
combined using finite-state calculus operations.

The previous effort is well-worth studying, but currently additional
ideas have established themselves such as weighted transducers for
modeling aspects of language that deal with preferences or trends
rather than strict rules or on/off phenomena. Many applications of
morphologies could use dictionaries encoding the a priori likelihoods
of words and expressions as well as the likelihood of their relations
to phonetic representations or their lexical relations to other words
in the same language or in different languages. The efforts to explore
weighted finite-state transducers for natural language processing are
ongoing in information retrieval, speech processing and machine
translation to name a few of the main application areas involved.

Since we do not pretend that we could develop all the morphologies for
all the languages ourselves, or even all the aspects of the tools
needed to develop these morphologies, we have made the choice to
create open-source tools and language descriptions. We hope as many as
possible will participate in the effort by developing the tools
further for common needs and special purposes.

In addition to the open source tools, we also encourage the commercial
use of the final transducers created by the tools by providing runtime
software (footnote: <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstRuntimeInterface>)
that is free for commercial purposes. Eventually this will allow
software applications simply to select the appropriate transducer in
order to process a language correctly allowing the programmer to
ignore special characteristics of individual languages.

Recently, a number of open-source finite-state processing environments
have emerged, e.g.  for unweighted transducers there are the
*SFST–Stuttgart Finite-State Transducer
Tools* (footnote: <http://www.ims.uni-stuttgart.de/projekte/gramotron/SOFTWARE/SFST.html>)
by Schmid [(cites: sfst)](#sfst), *foma: a finite-state machine toolkit and
library* (footnote: <http://foma.sourceforge.net/>) by Huld\’en,
etc., and for weighted transducers there are
*Vaucanson* (footnote: <http://www.lrde.epita.fr/cgi-bin/twiki/view/Projects/Vaucanson>)
by Lombardy et al. [(cites: vaucanson)](#vaucanson), *OpenFST
Library* (footnote: <http://www.openfst.org/>) by Allauzen et
al. [(cites: openfst)](#openfst), etc. These are valuable contributions to the open
source software that we can build on.

Our particular goal currently is in providing the basic facilities for
efficiently developing, compiling and running morphologies with or
without weights. To achieve our goal, we decided to create a unified
API (footnote: <http://www.ling.helsinki.fi/kieliteknologia/tutkimus/hfst/documentation.shtml>),
which is capable of interfacing various weighted and unweighted
finite-state transducer libraries allowing us to incorporate new
libraries as needed.  Currently, we have interfaces to <span style='font-variant: small-caps'>SFST</span>
and <span style='font-variant: small-caps'>OpenFST</span>. On top of the unified API, we created a set of
basic
tools (footnote: <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstHome>),
e.g. <span style='font-variant: small-caps'>HFST-TwolC, HFST-LexC, HFST-Compose-Inter\-sect,
HFST-Test, HFST-Lookup</span>, etc. With these tools, we created or used
real full-fledged morphological descriptions of different languages
from different
language-families (footnote: <http://www.ling.helsinki.fi/kieliteknologia/tutkimus/omor/index.shtml>),
e.g.  *English, Finnish, French, Northern S\’ami* and
*Swedish*. We used the morphological descriptions for testing the
functionality of the tools and for evaluating the performance of the
different libraries through a unified interface on the full-fledged
morphological development and compilation tasks.

The current article presents some of the main tools that we have
created: <span style='font-variant: small-caps'>HFST-LexC</span> in Sect. 2, <span style='font-variant: small-caps'>HFST-TwolC</span> in Sect. 3
and <span style='font-variant: small-caps'>HFST-Compose-Inter\-sect</span> in Sect. 4. For each tool, we
present the main theoretical underpinnings of the implementation and
illustrate them with some examples.  We highlight the main design
decisions that influenced the efficiency of the implementation and
how, if at all, our implementations differ from their namesakes. In
Sect. 5, we briefly present the morphological descriptions that we use
for demonstrating and comparing the efficiency of the
implementation. In Sect. 6, we evaluate the performance of our tools
for parallel-rule application and compare them with the performance of
the *foma* <span style='font-variant: small-caps'>LexC</span> compiler and the *Xerox* tools,
as well as the cascaded rule compiler of <span style='font-variant: small-caps'>SFST</span>. In Sect. 7, we
discuss the test results and present some aspects of future research
and development. In Sect. 8, we draw the conclusions.

## <span style='font-variant: small-caps'>HFST-LexC</span>
<a id="sec:HFST-LexC">(¶ sec:HFST-LexC)</a>

A lexicon compiler is a program that reads sets of morphemes and their
morphotactic combinations in order to create a finite-state transducer
of a lexicon.  This finite state transducer is called a *lexical
transducer*[(cites: Karttunen94)](#Karttunen94).  The lexical transducer may be further
adjusted with e.g. phonological rules. The example for our lexicon
compiler is set by <span style='font-variant: small-caps'>LexC</span> of Xerox [(cites: beesley03)](#beesley03).  In
<span style='font-variant: small-caps'>LexC</span>, morphemes are arranged into named sets called
sub-lexicons. Each entry of a sub-lexicon is a pair of finite
strings (footnote: Entries of regular expression form are not covered
here to simplify the presentation, but a full definition of an entry
in this formalism allows an entry to be a regular language.)
associated with the name of a sub-lexicon called a *continuation
class*.

Below, we highlight the main design decisions that influenced the
efficiency of the implementation and some of the we present the main
theory for compiling a <span style='font-variant: small-caps'>LexC</span> description into a finite-state
transducer. Our morphology example outlines the nominal inflection of
four Finnish nouns as shown in Table [(see: fig:finnish-lexc)](#fig:finnish-lexc).  This
example is a highly simplified version of the actual morphology.


**Table:**[!h]

```

Multichar_Symbols

+noun +1 +a +d +h +m +AV+ +AV- +AVA +AVD +AVH +AVM
+all +gen +ptv +sg  A  K  P

LEXICON Root
akku+noun+1+a:ak Ku+AVA   N1b "battery";
alku+noun+1+d:al Ku+AVD   N1b "beginning";
kumpu+noun+1+h:kum Pu+AVH N1b "heap";
kyky+noun+1+m:ky Ky+AVM   N1b "capability";

LEXICON N1b
NounSg ;
NounPtvA ;


LEXICON NounPtvA
    +sg+ptv: A+AV+  Ennd ;

LEXICON NounSg
    +sg+gen:n+AV-   Ennd ;
    +sg+all:l+AV-le Ennd ;
    :n+AV-          Compounding ;

LEXICON Compounding
Root ;

LEXICON Ennd
    # ;

```

(Caption: A simplified <span style='font-variant: small-caps'>HFST-LexC</span> lexicon for some Finnish
nouns.)<a id="fig:finnish-lexc">(¶ fig:finnish-lexc)</a>
<!-- end table -->

There are at least three time consuming parts of the <span style='font-variant: small-caps'>HFST-LexC</span> compilation
process.  First the compiler needs to parse the strings representing
the entry morphemes. Traditionally <span style='font-variant: small-caps'>LexC</span> allows multiple
characters in a single symbol. The problem of finding the optimal
partition of a string when compiling it into a finite-state transducer
is optimizing the *tokenization* algorithm. The tokenization is
discussed in Sect. [(see: subsec:lexc-tokenisation)](#subsec:lexc-tokenisation).  The set of entries
in each sub-lexicon form a *union*. There are a few alternative
strategies for creating unions, which are briefly outlined in
Sect. [(see: subsec:lexc-union)](#subsec:lexc-union). The combining of sub-lexicons is
described in Sect. [(see: subsec:lexc-morphotax)](#subsec:lexc-morphotax) on morphotax.

### Efficient Tokenizing of a Sub-Lexicon Entry
<a id="subsec:lexc-tokenisation">(¶ subsec:lexc-tokenisation)</a>

Lexicon entries are tokenized using a simple left-to-right longest
match algorithm. The entry can be tokenized by going through the entry
string, position by position, and looking up the longest symbols
available using a very simple greedy algorithm. An alternative, but
less efficient, strategy is to compose the entry string with a
tokenizer-transducer, implementing greedy left-to-right matching, to
achieve the correct partition.

### Efficient Union of Sub-Lexicon Entries
<a id="subsec:lexc-union">(¶ subsec:lexc-union)</a>

The finite-state form of a sub-lexicon is a union of entry
transducers.  Building a union of entry transducers is a relatively
straight-forward process. However, iteratively taking the union of n
entries with the n+1<span class='math'>^{th}</span> entry is not ideal. A faster approach,
given that all our entries are simple finite strings is to build the
sub-lexicon transducer as a prefix tree, *trie*.

### Efficient Implementation of Morphotax over Sublexicons
<a id="subsec:lexc-morphotax">(¶ subsec:lexc-morphotax)</a>

There are two strategies for making the sub-lexicon combinations. A
trivial, and fast, strategy is to connect the entries using
continuation classes to sub-lexicons of the same name with an epsilon
arc. An alternative method, which we implemented, is to use named
auxiliary symbols and the finite-state algebra to create
overgenerating combinations which are filtered by composition to
achieve legal combinations. This is further described in the next
subsection.

#### Combining sublexicons using standard finite-state transducer algebra.
We assume all standard finite state operations to be known. For an
introduction, see Beesly and Karttunen [(cites: beesley03)](#beesley03). We use the
following notation: <span class='math'>\cup</span> is union, <span class='math'>\cap</span> is intersection, <span class='math'>•</span>
is composition, juxtaposition is concatenation. Latin characters
represent symbols of language and the <span class='math'>ε</span> symbol is used for
a zero-length string.  Capital Greek letters <span class='math'>Σ, Γ</span>
represent subsets of an alphabet.  We define <span class='math'>Σ = \{a, b,
...}</span> as a subset of the alphabet used for representing the
morphophonology of the language in <span style='font-variant: small-caps'>LexC</span> definitions. <span class='math'>Γ</span>
is the alphabet of the *auxiliary* symbols used in our rules in
the morphotax implementation. We assume that <span class='math'>Σ ∪Γ =
∅</span>.  We use the symbol <span class='math'>J ∈ Σ</span> for *joiners* to
delimit and combine morphemes in our morphotax.  A joiner for an entry
with a continuation class named <span class='math'>x</span> is denoted as <span class='math'>Jₓ</span> and a joiner
for a sub-lexicon named <span class='math'>y</span> is denoted as <span class='math'>J_{y}</span>.

We introduce the compilation of lexicons using the example-lexicon in
Table [(see: fig:finnish-lexc)](#fig:finnish-lexc).

A single entry in a sub-lexicon, i.e., a line of code in a
<span style='font-variant: small-caps'>LexC</span> file, is referred to as a morpheme denoted by
<span class='math'>𝓜</span>. A morpheme can be a subset of the language
<span class='math'>Σ^{★}</span> appended with the joiner of a continuation class
([(see: eqn1)](#eqn1)).

<div class='math'>
  <a id="eqn1">(¶ eqn1)</a>
𝓜 = Σ^{★} J
</div>

E.g. the <span style='font-variant: small-caps'>LexC</span> string entry *akku\text:ak<span class='math'>~</span>Ku+AVA*
with a continuation class *N1b* becomes
*a k k:<span class='math'>~</span>K u:+AVA <span class='math'>ε</span>:<span class='math'>J_{N1b*</span>}.

A sub-lexicon <span class='math'>𝓛</span> defined by ([(see: eqn2)](#eqn2)) is a union of
morphemes as specified in Sect. [(see: subsec:lexc-union)](#subsec:lexc-union).

<div class='math'>
  <a id="eqn2">(¶ eqn2)</a>
𝓛 = J ⋃_{𝓜ₓ ∈ 𝓜} ( 𝓜ₓ )
</div>

E.g. the lexicon named *Root* consisting of *akku* and
*alku* with continuation class *N1b* becomes
<span class='math'>J_{Root} ( a k k u J_{N1b} | a l k u J_{N1b} )</span>.

We create a filter <span class='math'>𝓕</span> defined by ([(see: eqn3)](#eqn3)) for legal
morpheme combinations by pairing up adjacent joiners.

<div class='math'>
  <a id="eqn3">(¶ eqn3)</a>
𝓕 = ⋃_{Jₓ ∈ J} ( Jₓ Jₓ )
</div>

To account for the special starting lexicon and the special ending
lexicon, we define <span class='math'>J_{Root} ∈ J</span> and <span class='math'>J_{\#} ∉ J</span>. The root
lexicon can be used in continuation classes as a target, e.g. for the
compounding mechanism, but the end lexicon is not available as a
lexicon name, so it is not part of the regular morphotax. To
accommodate this, we extend the filter definition to
<span class='math'>𝓕^{′}</span> as in ([(see: eqn4)](#eqn4)).

<div class='math'>
  <a id="eqn4">(¶ eqn4)</a>
𝓕^{′} = J_{Root} ( Σ^{★} 𝓕 )^{★} Σ^{★} J_{\#}
</div>

This allows us to create the final transducer <span class='math'>𝓡</span> with only
legal combinations of sub-lexicons by composition ([(see: eqn5)](#eqn5)).

<div class='math'>
  <a id="eqn5">(¶ eqn5)</a>
𝓡 = ⋃_{𝓛ₓ ∈ 𝓛} ( 𝓛ₓ )^{★} • 𝓕^{′}
</div>

E.g., for the sublexicons *Root*, *N1b*, *NounSg*, and
*Ennd* in Table [(see: fig:finnish-lexc)](#fig:finnish-lexc), and their entries
*akku* and *+sg+all:lle*, we get the disjunction of lexicons
<span class='math'>L^{★}</span>, which we filter using <span class='math'>L^{★} • F^{′}</span> as
shown in Table [(see: filter-example)](#filter-example).


**Table:**[!h]


| <span class='math'>L^{★} =</span>  |  <span class='math'>(  J_{Root} a k k u J_{N1b}  `|`  J_{N1b} J_{NounSg}  |</span> |
| ---- | ---- |
|      |  <span class='math'>J_{NounSg} +sg:l +all:l ε:e J_{Ennd}  `|`  J_{Ennd} J_{\#}  )^{★}</span> |
| <span class='math'>F =</span>          |  <span class='math'>J_{Root} J_{Root} `|` J_{N1b} J_{N1b} `|` J_{NounSg} J_{NounSg} `|` J_{Ennd} J_{Ennd}</span> |
| <span class='math'>L^{★} • F^{′} =</span>  |  <span class='math'>J_{Root} a k k u J_{N1b}  J_{N1b} J_{NounSg}</span> |
|  |  <span class='math'>J_{NounSg} +sg:l +all:l ε:e J_{Ennd}  J_{Ennd} J_{\#}</span>|

(Caption: Filtering a single path in <span style='font-variant: small-caps'>HFST-LexC</span> with a
morphotax filter.)  <a id="filter-example">(¶ filter-example)</a>
<!-- end table -->

Finally, all the symbols in <span class='math'>Γ</span> are removed. While this is
trivial, it introduces some indeterminism in the final transducer,
which would otherwise have been introduced by building direct epsilon
arcs. Its influence on the performance is further detailed in
Sect. [(see: sec:performance)](#sec:performance).

According to our experiments, attaching weights to each entry works
without modification of the lexicon compilation method.

## <span style='font-variant: small-caps'>HFST-TwolC</span>

*Two-level rules* are parallel constraints on symbol-pair
strings governing the realizations of lexical word-forms as
corresponding surface-strings. They were introduced by Koskenniemi
[(cites: Koskenniemi83)](#Koskenniemi83) and have been used for modeling the phonology of
numerous natural languages. <span style='font-variant: small-caps'>HFST-TwolC</span> is an accurate and
efficient open-source two-level rule compiler. It compiles grammars of
two-level rules into sets of finite-state transducers. The rules are
represented as regular-expression operations closely resembling
familiar phonological re-write rules both to appearance and semantics.

The most widely known two-level rule-compiler existing at the moment
is the *Xerox Two-Level Rule Compiler* (later <span style='font-variant: small-caps'>TwolC</span>)
presented by Karttunen el al. [(cites: Karttunen92)](#Karttunen92).  It is proprietary
software, which imposes some limitations upon its use. The
<span style='font-variant: small-caps'>HFST-TwolC</span> compiler has been designed to be an open-source
substitute for the <span style='font-variant: small-caps'>TwolC</span> compiler and has a syntax and
semantics very similar to those of the <span style='font-variant: small-caps'>TwolC</span> compiler. Hence
existing two-level grammars, designed to compile under the
<span style='font-variant: small-caps'>TwolC</span> compiler, require very few modifications to compile
correctly under <span style='font-variant: small-caps'>HFST-TwolC</span>.

Besides being an open-source program, <span style='font-variant: small-caps'>HFST-TwolC</span> also has
other benefits compared with the <span style='font-variant: small-caps'>TwolC</span> compiler. Resolution
of rule-conflicts is an important part of compiling two-level
grammars. We know of at least one instance, where the <span style='font-variant: small-caps'>TwolC</span>
compiler resolves rule-conflicts in an incorrect way (see
Sect. [(see: twolc-conflict-resolution)](#twolc-conflict-resolution)). It also compiles epenthesis
rules in a way, which denies the grammar-writer the full expressive
power of two-level rules (see Sect. [(see: twolc-rules)](#twolc-rules)). In
<span style='font-variant: small-caps'>HFST-TwolC</span> we have been able to remedy these shortcomings by
compiling the rules with the *generalized
restriction-operation* (later *GR-operation*), presented by
Yli-Jyr\"a and Koskenniemi [(cites: Yli-Jyra06)](#Yli-Jyra06). It allows compilation of
two-level rules in a uniform way and makes conflict-resolution easy to
tackle, while still permitting efficient compilation.

In Sect. [(see: twolc-example)](#twolc-example), we demonstrate the syntax and semantics
of a two-level grammar-file using a small example from Finnish
morphology. The example grammar maps the lexical forms given by the
example lexicon in Table [(see: fig:finnish-lexc)](#fig:finnish-lexc), presented in
Sect. [(see: sec:HFST-LexC)](#sec:HFST-LexC), into surface-forms.

It is not possible to demonstrate all features of <span style='font-variant: small-caps'>HFST-TwolC</span>
in this article, but we try to highlight the few most important
differences to show that it is easy to migrate from the <span style='font-variant: small-caps'>TwolC</span>
compiler to <span style='font-variant: small-caps'>HFST-TwolC</span>.

We use the GR-operation to compile the grammar-rules in
<span style='font-variant: small-caps'>HFST-TwolC</span>. In Sect. [(see: twolc-rules)](#twolc-rules), we explain how the
different types of two-level rules are compiled. Rule-conflicts and
their resolution are covered in Sect. [(see: twolc-conflict-resolution)](#twolc-conflict-resolution).

### An Example Grammar<a id="twolc-example">(¶ twolc-example)</a>

An input-file for <span style='font-variant: small-caps'>HFST-TwolC</span> consists of five parts:
*the Alphabet*, *the Rule-variables*, *the Sets*,
*the Definitions* and *the Rules*. The file-format has
been modeled on the format used by the <span style='font-variant: small-caps'>TwolC</span> compiler, and
all parts of the grammar are present also in the <span style='font-variant: small-caps'>TwolC</span>
compiler except for the part declaring rule-variables. There are a few
other differences, as well, most of which we will mention below. A
complete list of known differences can be found in the
<span style='font-variant: small-caps'>HFST-TwolC</span>
documentation (footnote: <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstTwolC>).


**Table:**[!h]

```

Alphabet

A B C D E F G H I J K L M N O P Q R S T U V W X Y Z Å Ä Ö
a b c d e f g h i j k l m n o p q r s t u v w x y z å ä ö

Rule-variables

Cm Cs Cw ;

Sets

Gradations =    BackVowels = a o u A O U ;
UpperCaseVowels   = A E I O U Y Å Ä Ö ;
LowerCaseVowels = a e i o u y å ä ö ;

Vowels = UpperCaseVowels LowerCaseVowels ;

Definitions

AlphaSeq    = [ \Gradations: ]* ;
NonVowelSeq = [ \:Vowels ]* ;

Rules

   " K:0 Gradation"

   "   Cs:Cw &lt;=&gt; _ AlphaSeq Cm:0 AlphaSeq       where Cs in (               Cw in (     v     m )
Cm in (
   "Vowel Harmony"


```

(Caption: An example <span style='font-variant: small-caps'>HFST-TwolC</span> grammar governing the surface
realizations of the forms presented in the example lexicon in
Table [(see: fig:finnish-lexc)](#fig:finnish-lexc).)<a id="figure:finnish-morphology-rules">(¶ figure:finnish-morphology-rules)</a>
<!-- end table -->

#### The Alphabet.

The alphabet of a two-level grammar contains all lexical symbols
specified in the <span style='font-variant: small-caps'>HFST-LexC</span> grammar together with their
possible surface realizations. In the example grammar in
Table [(see: figure:finnish-morphology-rules)](#figure:finnish-morphology-rules), the alphabet contains all
letters used in Finnish words together with the vowel-harmony
archphoneme ` A`, the gradation morphophonemes ` K` and
` P`, as well as, the gradation-markers `+AV+`, `+AV-`,
`+AVA`, `+AVD`, `+AVH`, `+AVM`.

All symbols in the grammar may be arbitrary strings of UTF-8
characters, but characters like `+`, ` ` or white-space,
which bear special meanings for the compiler need to be escaped using
the escape-character `
The letters in the example-grammar of
Table [(see: figure:finnish-morphology-rules)](#figure:finnish-morphology-rules) always correspond to
themselves on the surface. The gradation-markers always correspond to
zero and the archphoneme \verb` A| and the morphophonemes ` K`
and ` P` have various surface-realizations. E.g. ` A` is
always realized as either `a` or `\"a`.

Each valid pair of a lexical symbol and its surface-correspondence has
to be listed in the alphabet. This differs from the <span style='font-variant: small-caps'>TwolC</span>
compiler, where pairs may be omitted from the alphabet, if they are
identity-pairs or are already constrained by some rule. Forcing the
grammar-writer to declare all symbol-pairs, may result in some extra
work, but it also prevents the creation of inadvertent pairs.

Declaring all symbol-pairs in <span style='font-variant: small-caps'>HFST-TwolC</span> is mandatory, as we
have not yet implemented an *other-symbol* like the one in
Xerox <span style='font-variant: small-caps'>TwolC</span> [(cites: Karttunen92)](#Karttunen92) using the <span style='font-variant: small-caps'>HFST</span>
interface. Besides the grammar-formalism, this also affects the
compile-time for rules, which becomes more dependent on the number of
symbol-pairs in the grammar.

#### The Rule-variables.

Like the <span style='font-variant: small-caps'>Xerox</span> compiler, <span style='font-variant: small-caps'>HFST-TwolC</span> supports
defining a set of similar two-level rules using a rule-schema with
variables. During the compilation of the grammar, each schema is
compiled into actual two-level rules, by substituting the variables
with the values specified for them. All rule-variables, which are used
in the grammar, need to be declared in the Rule-variables section.

#### The Sets.

It is often convenient to name some classes of symbols, which are used
in many rules. E.g. the class `BackVowels` in the example-grammar
in Table [(see: figure:finnish-morphology-rules)](#figure:finnish-morphology-rules), which contains all
vowel-segments used in the grammar. The sets in <span style='font-variant: small-caps'>HFST-TwolC</span>
and <span style='font-variant: small-caps'>TwolC</span> are very similar constructs.

In <span style='font-variant: small-caps'>HFST-TwolC</span>, the Cartesian product of sets, or a set and a
symbol, is always limited to the set of symbol-pairs declared in the
alphabet. E.g. the equivalent expressions `BackVowel:BackVowel`
and `BackVowel` will only accept the pairs `a:a`,
`o:o`, `u:u`, `A:A`, `O:O` and
`U:U`. Although it is conceivable, that they would accept
e.g. the pairs `a:U` and `A:O`, they will not, since the
pairs have not been declared.

All sets have to be declared in the sets section of the grammar. Of
the five sets we have defined in the example grammar, the first four
are defined directly using a symbol sequence. The fifth set
`Vowels` is defined as the union of the sets `SmallVowels`
and `BigVowels`.

#### The Definitions.

Like character-sets, also regular expressions may be stored under a
name and accessed later using that name. Named regular expressions are
called definitions and may be used freely in the rules. Sets and
previous definitions can be used in the definition of a new
definition. The definitions in <span style='font-variant: small-caps'>HFST-TwolC</span> and <span style='font-variant: small-caps'>TwolC</span>
are identical.

#### The Rules.

A two-level grammar constrains the surface-realizations of lexical
forms. The constraints are given as two-level rules, whose joint
effect determines the set of valid correspondences for each lexical
form. Each of the rules governs one realization of a lexical symbol in
a context given by a regular expression of pairs of a lexical and
surface symbol.

The syntax and semantics of rules in <span style='font-variant: small-caps'>HFST-TwolC</span> and
<span style='font-variant: small-caps'>TwolC</span> are very
similar (footnote: <http://www.xrce.xerox.com/competencies/content-analysis/fsCompiler/fssyntax.html>).
Except for *surface-restrictions* concerning epsilon,
i.e. epenthesis rules, the rules also work the same way.

An example of a rule is the rule governing vowel-harmony in our example grammar

```

   "Vowel Harmony"

```

It states that the archphoneme ` A` has to be realized as
`a`, if the surface-vowel immediately preceding it is a
back-vowel. It also disallows the pair ` A:a` in all other
contexts.

The rule accepts the first correspondence in Table [(see: cor:1)](#cor:1) since
the vowel preceding ` A` is `y`, which is not a
back-vowel. It disallows both of the latter correspondences. In the
second correspondence ` A` is realized as `a`, even though
the preceding surface-vowel is not a back-vowel. This violates the
`=&gt;` direction of the rule. In the third correspondence,
` A` is realized as `\"a`, but the preceding
surface-vowel is `u`, which is a back-vowel. This violates the
`&lt;=` direction of the rule.


**Table:**
  <div style='text-align: center'>


| `k`  |  `y`  |  ` K`  |  `y`  |  ` A `  |
| ` k`  |  `y`  |  ` K`  |  `y`  |  ` A `  |
| ` k`  |  `u`  |  `m`  |  ` P`  |  `u`  | ` A`|
| `k`  |  `y`  |  `k`  |  `y`  |  `\"a` |
|  ` k`  |  `y`  |  `k`  |  `y`  |  `a `  |
| ` k`  |  `u`  |  `m`  |  `p`  |  `u`  | `\"a`` `|

  </div>
(Caption: Symbol-pair correspondences for demonstrating the
vowel-harmony rules.)<a id="cor:1">(¶ cor:1)</a>
<!-- end table -->

<span style='font-variant: small-caps'>HFST-TwolC</span> allows a set of rules to be defined using
variables or by giving a set of rule-centers. E.g. the rule which
defines the basic constraint of gradation in our example grammar is a
rule with three variables: `Cs`, `Cv` and `Cm`.

```

   "   Cs:Cw &lt;=&gt; _ AlphaSeq Cm:0 AlphaSeq       where Cs in (               Cw in (     v     m )
Cm in (
```

Like ordinary alphabet-symbols, variables may be used both in the
center of a rule and in its contexts.

When a rule with variables is compiled, it is split into
sub-rules. These are obtained by substituting real alphabet symbols
for the variables. The possible values of variables are listed in the
where-clause following the rule.

### Compiling the Rules and Resolving Rule-Conflicts

<span style='font-variant: small-caps'>HFST-TwolC</span> compiles two-level rules, given as regular
expressions of pairs, into finite-state transducers. All two-level
rules may be constructed from simple surface-requirements,
context-restrictions and surface-prohibitions. The compilation reduces
the two-sided rules and rules with variables into combinations of such
simple constructions, or subrules.

After compilation, the subrules are intersected, so that finally
equally many rule-transducers are produced as there were original
two-level rules. Intersecting the subrules of the two-level grammar
rules takes up a considerable portion of the compile-time of the
grammar.

Compilation of the rules is preceded by a phase called
conflict-resolution, which modifies rule-contexts in order to prevent
harmful interactions between the rules. After conflict-resolution the
modified rule-set may be compiled as usual.

We use the GR-operation of Yli-Jyr\"a and Koskenniemi
[(cites: Yli-Jyra06)](#Yli-Jyra06) to compile rules. Both compiling rules and
conflict-resolution is simplified using the operation.

The compilation in <span style='font-variant: small-caps'>HFST-TwolC</span> differs from <span style='font-variant: small-caps'>TwolC</span>
when epenthesis rules are compiled. As Yli-Jyr\"a and Koskenniemi
[(cites: Yli-Jyra06)](#Yli-Jyra06) point out, epenthesis rules may be compiled as any
other surface-requirement rules using the GR-operation. This increases
the expressive power of the two-level grammar as explained below.

A general restriction of the pair-alphabet <span class='math'>Σ</span> is an expression
<span class='math'>W \overset{n♢}{→}W’</span>, where the precondition <span class='math'>W</span> and
postcondition <span class='math'>W’</span> are unions of expressions of the form <span class='math'>V_1 ♢
V_2 ♢ \text{ ... }♢ V_n ⊂ Σ^* (♢\
Σ^*)^n</span>, where <span class='math'>♢ ∉ Σ</span> is a special
marker-symbol and each <span class='math'>V_i</span> is a regular language of the alphabet
<span class='math'>Σ</span>. Such an expression is compiled into a regular expression
using the GR-operation as in ([(see: gr)](#gr)).

<div class='math'>
  <a id="gr">(¶ gr)</a>
Σ^* - \text{delete}_{♢}(W - W’)
</div>

The operation <span class='math'>\text{delete}_♢</span> in ([(see: gr)](#gr)) rewrites each
marker-symbol <span class='math'>♢</span> into epsilon and leaves all other symbols
intact.

We do not need the full expressive power of the GR-operation. Instead
we use a restricted version <span class='math'>W \overset{2♢}{→}W’</span>,
which is limited to compiling rules with one center and a number of
contexts with a right and a left part. Hence we operate on
preconditions and postconditions with two diamonds,
i.e. <span class='math'>W,W’⊆ Σ^* ♢ Σ^* ♢ Σ^*</span>.

We discuss compiling one rule first and then conflict-resolution,
although logically conflict-resolution is done first and then the
rules are compiled. This is easier to explain, because
conflict-resolution is highly dependent on the way the rules are
compiled.

#### Compiling one rule.
<a id="twolc-rules">(¶ twolc-rules)</a>
Yli-Jyr\"a and Koskenniemi [(cites: Yli-Jyra06)](#Yli-Jyra06) explain how ordinary
two-level rules can be compiled using the GR-operation. We use slight
variations of the same methods.

Surface-requirement rules and context-restriction rules need to be
compiled in different ways. Surface-prohibition rules can be compiled
in a similar manner as surface-requirement rules and double-sided
rules are compiled, by intersecting the two directions of the rule.

The general restriction corresponding to the context-restriction rule
<span class='math'>a\text{:}b → ⋃_{i=0}^n L_i \_ R_i</span> is given by
([(see: right-rule)](#right-rule)).

<div class='math'>
  <a id="right-rule">(¶ right-rule)</a>
Σ^* ♢ a\text{:}b♢Σ^*
  \overset{2♢}{→} ⋃_{i=0}^n
L_i♢Σ^*♢ R_i
</div>

The surface-requirement rule requires an auxiliary definition. We
define the inverse projection <span class='math'>[x\text{:}]</span> of the input-symbol <span class='math'>x</span>
using ([(see: inverse-projection)](#inverse-projection)). Here <span class='math'>x</span> may be any of the
input-symbols of pairs in <span class='math'>Σ</span>, including epsilon.

<div class='math'>
  <a id="inverse-projection">(¶ inverse-projection)</a>
	[x\text{:}] = \{ x\text{:}y | x\text{:}y ∈ Σ \}
</div>

The general restriction corresponding to the surface-requirement rule
<span class='math'>a\text{:}b ← ⋃_{i=0}^n L_i \_ R_i</span> is given by
([(see: left-rule)](#left-rule)).

<div class='math'>
  <a id="left-rule">(¶ left-rule)</a>
  \Big( Σ^* ♢ [a\text{:}] - a\text{:}b ♢Σ^*
  ∩⋃_{i=0}^n L_i♢Σ^*♢ R_i \Big)
  \overset{2♢}{→} ∅
</div>

The general restriction corresponding to the surface-prohibition rule
<span class='math'>a\text{:}b \/← ⋃_{i=0}^n L_i \_ R_i</span> is similar. It
is given by ([(see: prohibition-rule)](#prohibition-rule)).

<div class='math'>
  <a id="prohibition-rule">(¶ prohibition-rule)</a>
  \Big( Σ^* ♢ a\text{:}b ♢Σ^* \cap
  ⋃_{i=0}^n L_i♢Σ^*♢ R_i \Big)
  \overset{2♢}{→} ∅
</div>

Using the GR-operation, epenthesis rules have the same semantics as
other surface-requirement rules. The rule <span class='math'>0\text{:}a ← b\
\_ b</span> rejects the correspondences <span class='math'>bb</span> and <span class='math'>b0\text{:}cb</span>, but accepts
<span class='math'>b0\text{:}ab</span>.

The <span style='font-variant: small-caps'>TwolC</span> compiler compiles epenthesis rules in a different
way than <span style='font-variant: small-caps'>HFST-TwolC</span>. In <span style='font-variant: small-caps'>TwolC</span>, the rule <span class='math'>0\text{:}a
← b \_ b</span> becomes equivalent to the expression <span class='math'>Σ^* -
( Σ^* b bΣ^*)</span>, which means that <span class='math'>bb</span> is rejected, but
<span class='math'>b0\text{:}cb</span> is accepted, provided that the pair <span class='math'>0\text{:}c</span> is
declared in the alphabet <span class='math'>Σ</span>. This makes it impossible to
interpret one epenthesis rule a special case of another epenthesis
rule.

E.g. we might want the pair <span class='math'>0\text{:}v</span> between two vowels, but the pair
<span class='math'>0\text{:}w</span> between two like vowels. This can be expressed by the rules

<span class='math'></span>0\text{:}v ← \text{Vowel} \_ \text{Vowel} ;\text{ and
}0\text{:}w ← V_x \_ V_x\text{, }V_x ∈ \text{Vowel} ;<span class='math'></span>

In <span style='font-variant: small-caps'>HFST-TwolC</span> conflict resolution modifies the context of the
more general rule. A correspondence with <span class='math'>0\text{:}t</span> between like
vowels becomes disallowed, but a correspondence with <span class='math'>0\text{:}s</span>
between like vowels is allowed. In the <span style='font-variant: small-caps'>TwolC</span> compiler this is
not possible.

#### Resolving rule-conflicts.
<a id="twolc-conflict-resolution">(¶ twolc-conflict-resolution)</a>

Rule-conflicts are situations where different rules require a lexical
string to be realized in different ways. Since each correspondence of
a lexical string and surface string needs to be accepted by all rules
in a two-level grammar, such lexical strings are filtered by the
grammar. Using the GR-operation to compile the rules allows separating
the processes of conflict-resolution and rule-compilation. Previously,
these may have been more entangled, which would explain, why the
conflict resolution of the <span style='font-variant: small-caps'>Xerox</span> compiler sometimes works in
an unexpected way (see example below).

Like <span style='font-variant: small-caps'>TwolC</span>, <span style='font-variant: small-caps'>HFST-TwolC</span> only handles two kinds of
conflicts: right-arrow conflicts and left-arrow conflicts. Right-arrow
conflicts occur between context-restrictions with the same
center-pair. Left-arrow conflicts occur between surface-requirements
with centers having the same lexical symbol, but different
surface-symbols.

Consider the rules
<span class='math'></span>a\text{:}b → x  \_ ;\text{ and }a\text{:}b →
y \_ ;<span class='math'></span>

These are in right-arrow conflict with each other. Like Xerox
<span style='font-variant: small-caps'>TwolC</span>, <span style='font-variant: small-caps'>HFST-TwolC</span> interprets both rules as
permissions and replaces them with one rule, whose context is the
union of the contexts of the conflicting rules. Joining the contexts
is easy when the rules are compiled using the GR-operation.

A left-arrow conflict is resolvable exactly when one of the
rule-contexts is a sub-context of the other. A trivial example of a
resolvable left-arrow conflict is given by the rules
<span class='math'></span>a\text{:}b ← \{d\text{, }e\} \_ ;\text{ and }a\text{:}c
← d \_ ;<span class='math'></span>

Here the alphabet <span class='math'>Σ</span> consists of the pairs <span class='math'>a\text{:}b</span>,
<span class='math'>a\text{:}c</span>, <span class='math'>d</span> and <span class='math'>e</span>. This is resolved by replacing the more
general context with the difference of that context and the more
specific context as given by ([(see: modified-context)](#modified-context)), where we have
written the contexts as generalized restriction contexts.

<div class='math'>
  <a id="modified-context">(¶ modified-context)</a>
  (Σ^* \{d\text{, }e\}♢ Σ^* ♢ Σ^*) -
  (Σ^* d ♢ Σ^* ♢ Σ^*) = Σ^*
e♢ Σ^* ♢ Σ^*
</div>

This example does not compile as expected under
<span style='font-variant: small-caps'>TwolC</span>. Conflict-resolution results in a grammar, which
rejects all lexical strings containing <span class='math'>a</span> or <span class='math'>e</span>.

Right-arrow conflict-resolution may result in large rule-contexts
which may be time-consuming to determinize. Left-arrow conflict
resolution requires testing all pairs of surface-restriction rules
concerning the same lexical symbol. This means that the worst-case
time-requirement is quadratic w.r.t. to the number of rules in the
grammar.

## <span style='font-variant: small-caps'>HFST-Compose-Intersect</span>

A lexicon compiled using <span style='font-variant: small-caps'>HFST-LexC</span> and a grammar of two-level
rules compiled using <span style='font-variant: small-caps'>HFST-TwolC</span> are combined using the
program <span style='font-variant: small-caps'>HFST-Compose-Intersect</span>. It is an implementation of
the *intersecting composition* algorithm presented by Karttunen
[(cites: Karttunen94)](#Karttunen94). The result of the operation is equivalent to the
composition of the lexicon-transducer with the intersection of the
rule-transducers.

Karttunen [(cites: Karttunen94)](#Karttunen94) observed that the intersection of the
rule-transducers alone may be extremely large and computing it may
take a long time, whereas intersecting composition allows the lexicon
to restrict the intersection of the rule-transducers. This reduces
compilation time significantly.

Although computers have become considerably faster since 1994 and they
have more memory, computing the intersection of the rule-transducers
can still be very space-consuming. We intersected the rule-transducers
of the two-level implementation of
<span style='font-variant: small-caps'>OMorFi</span> (footnote: <http://kitwiki.csc.fi/kitwiki/Main/OMorFiHome>),
i.e. Pirinen’s [(cites: pirinen2008)](#pirinen2008) morphological analyzer for
Finnish. Without the intersecting composition, the rule intersection
took eleven hours using the same machine we used for conducting our
other performance-tests. Hence we believe that intersecting
composition is still a necessary operation when developing full-scale
two-level morphological analyzers.

## Full-Scale Morphological Analyzers using <span style='font-variant: small-caps'>HFST</span> Morphological
Tools

We test the performance of the <span style='font-variant: small-caps'>HFST</span> tools by building three
full-scale morphological analyzers of varying complexities for French,
Finnish, and Northern S\’{a}mi. All of them highlight different
aspects of the compilation process. To verify the correctness of the
compilation results, we analyzed corpora using the lexical
transducers.

The French analyzer was built from the existing morphological
full-form lexicon
Morphalou (footnote: <http://www.cnrtl.fr/lexiques/morphalou/>). The
lexicon was translated into the <span style='font-variant: small-caps'>LexC</span> format and it contains
some 550,000 entries in a single lexicon. Each entry represents a word
form and its analysis. We chose this lexicon for testing
<span style='font-variant: small-caps'>HFST-LexC</span> with a large number of real entries.

The Finnish analyzer has two implementations, i.e. the version using
the <span style='font-variant: small-caps'>SFST</span> compiler format of <span style='font-variant: small-caps'>OMorFi</span> which is
Pirinen’s [(cites: pirinen2008)](#pirinen2008) original analyzer for Finnish, and a
reformulated version using a <span style='font-variant: small-caps'>LexC</span> lexicon and a
<span style='font-variant: small-caps'>TwolC</span> grammar format. The reformulation was done manually by
converting the morpheme sets of the original code into <span style='font-variant: small-caps'>LexC</span>
sublexicons and rewriting the phonological rules from replace cascades
into <span style='font-variant: small-caps'>TwolC</span> rule sets.  While care has been taken to ensure
the similarity of the implementations, it should be noted that the
versions are not totally equivalent.  We still think they are close
enough for a meaningful comparison of the two approaches.

The Northern S\’{a}mi analyzer is an original <span style='font-variant: small-caps'>LexC</span> and
<span style='font-variant: small-caps'>TwolC</span> based morphological analyzer developed in the Divvun
Project (footnote: <http://www.divvun.no>). It is a full-fledged
analyzer developed totally independently of the <span style='font-variant: small-caps'>HFST</span> project
and it has both a large number of sublexicons and a large number of
rules.

The characteristics of the analyzers of the three languages are
summarized in Table [(see: fig:lexicon-sizes)](#fig:lexicon-sizes). The first three of the
columns summarize the <span style='font-variant: small-caps'>HFST-LexC</span> lexicons stating the numbers
of sublexicons, lexicon-entries and symbols used in the lexicons. The
remaining three columns summarize the <span style='font-variant: small-caps'>HFST-TwolC</span> grammars.
They state the numbers of symbol-pairs, rules and subrules in the
double-sided rules and rules with variables. The example for French
has no entries in the last three columns, since it has no two-level
grammar.


**Table:**[!h]
  <div style='text-align: center'>


|  | <span style='font-variant: small-caps'>HFST-LexC</span>}  |  | {<span style='font-variant: small-caps'>HFST-TwolC</span>} | | | |
| Language  |    Sublexicons    |    Entries    |    Symbols    |    Pairs    |    Rules    |    Subrules  |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| French  |  1    |  553,158    |  87    |  —    |  —    |  —   |
| Finnish  |  213    |  94,278    |  301    |  169    |  12    |  76   |
| Northern S\’ami    |  870    |  105,503    |  428    |  313    |  105    |  555   |

    \vskip0.5cm
  </div>
(Caption: Some numbers characterizing the lexicons and two-level
grammars we used for testing.)<a id="fig:lexicon-sizes">(¶ fig:lexicon-sizes)</a>
<!-- end table -->

## Performance Evaluation
<a id="sec:performance">(¶ sec:performance)</a>

The goal of the performance evaluation is is to see how far we still
have to go before we reach industrial-strength performance.
Additionally, we wish to see how the performance of the <span style='font-variant: small-caps'>LexC</span>
and <span style='font-variant: small-caps'>TwolC</span> approach with parallel-rules compares to the
approach with cascaded-rules. To achieve these goals, we compare
<span style='font-variant: small-caps'>HFST</span> with some other open source tools and an industrial
strength implementation by Xerox.  By compiling the analyzers
mentioned in the previous section, we can also collect performance
figures on real full-fledged morphologies for identifying the most
significant remaining bottle-necks in our tools.

The <span style='font-variant: small-caps'>HFST-LexC</span> and <span style='font-variant: small-caps'>HFST-TwolC</span> tools mimic many of the
Xerox <span style='font-variant: small-caps'>LexC</span> and <span style='font-variant: small-caps'>TwolC</span> functionalities, so the
input-files for the <span style='font-variant: small-caps'>HFST</span> tools require very small
modifications in order to compile using the Xerox tools, and vice
versa. This makes it is easy to compare the performance of the
<span style='font-variant: small-caps'>HFST</span> tools with the Xerox versions.

As the Finnish <span style='font-variant: small-caps'>OMorFi</span> analyzer has two almost identical
versions: one using replace-rules for the <span style='font-variant: small-caps'>SFST</span> compiler and
one using two-level rules for the <span style='font-variant: small-caps'>LexC</span> and <span style='font-variant: small-caps'>TwolC</span>
tools, we are able to compare the efficiency of the two approaches to
building morphological analyzers.

Below, we have five tables summarizing the results of the performance
tests. The first Table [(see: fig:lexicon-compilation-comparisons)](#fig:lexicon-compilation-comparisons)
compares the total compile times of the analyzers using the
<span style='font-variant: small-caps'>HFST</span> tools, the Xerox tools, the foma <span style='font-variant: small-caps'>LexC</span> tool and
the <span style='font-variant: small-caps'>SFST</span> compiler.  For foma, only the compile-time for the
analyzer of French is given, as foma only comes with a
<span style='font-variant: small-caps'>LexC</span> (footnote: foma also has an <span style='font-variant: small-caps'>xfst</span> interface.)
interface.  For the <span style='font-variant: small-caps'>SFST</span> compiler, only the compile-time for
the Finnish lexicon is given, as our only implementation with cascaded
rules is for Finnish.


**Table:**[!h]
  <div style='text-align: center'>


| Language  |    <span style='font-variant: small-caps'>HFST</span> tools    |    foma <span style='font-variant: small-caps'>LexC</span>    |    <span style='font-variant: small-caps'>SFST</span> compiler    |    Xerox tools   |
| ---- | ---- | ---- | ---- | ---- |
| French           |  45.92 s    |    16.87 s    |  —           |  5.46 s  |
| Finnish          |  25.42 s    |  —         |    1682.04 s    |  1.83 s  |
| Northern S\’ami    |    287.21 s    |  —         |  —           |    24.61 s  |

    \vskip0.5cm
(Caption: Total compile-times using <span style='font-variant: small-caps'>HFST</span> tools, foma
    <span style='font-variant: small-caps'>LexC</span>, <span style='font-variant: small-caps'>SFST</span> compiler and Xerox tools to compile
lexical transducers. Times are in
seconds.)<a id="fig:lexicon-compilation-comparisons">(¶ fig:lexicon-compilation-comparisons)</a>
  </div>
<!-- end table -->

The following three Tables [(see: fig:lexicon-compilation-phases)](#fig:lexicon-compilation-phases),
[(see: fig:grammar-compilation-phases)](#fig:grammar-compilation-phases) and [(see: fig:ci-phases)](#fig:ci-phases) give the
\text{HFST} compile-times for the analyzers of Finnish, French and
Northern S\’ami. The times have been broken down into sub-phases of the
compilation in order to see where the bottle-necks are. The phases are
explained below the tables.


**Table:**[!h]
  <div style='text-align: center'>


| Language         |  1          |  2          |  3          |  4          |  Total    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| French           |    19.27 s    |    1.18 s    |  0.08 s    |    25.40 s    |    45.92 s   |
| Finnish          |  3.59  s    |  0.19 s    |  0.29 s    |  17.99 s    |  22.05 s   |
| Northern S\’ami    |  3.74  s    |  0.23 s    |    2.00 s    |  78.84 s    |  84.81 s   |

    \vskip0.5cm

    *  The entry parsing and compilation
    (cf. Sect [(see: subsec:lexc-tokenisation)](#subsec:lexc-tokenisation))
    *  Union of entries (cf. Sect [(see: subsec:lexc-union)](#subsec:lexc-union))
    *  Morphotactic filtering
    (cf. Sect [(see: subsec:lexc-morphotax)](#subsec:lexc-morphotax))
    *  Other phases (Alphabet discovery, minimizing results, etc.)

(Caption: <span style='font-variant: small-caps'>HFST-LexC</span> performance broken into the different
phases of the compilation process. Times are in
seconds.)<a id="fig:lexicon-compilation-phases">(¶ fig:lexicon-compilation-phases)</a>
  </div>
<!-- end table -->


**Table:**[!h]
  <div style='text-align: center'>


| Language  |  1      |  2      |  3      |  Total    |
| ---- | ---- | ---- | ---- | ---- |
| Finnish  |    0.10 s    |    0.04 s    |  1.27 s    |  1.41 s   |
| Northern S\’ami    |  2.11 s    |  1.35 s    |    24.77 s    |    28.23 s   |

    \vskip0.5cm

    *  Reading the input-file and creating auxiliary
data-structures. Compiling rule-contexts into transducers.
    *  Identifying and resolving rule-conflicts.
    *  Combining contexts and centers of single
surface-requirements and context-restrictions. Intersecting subrules
of rules with variables and double-sided rules, in order to form
the final rule-transducers. Minimizing and storing the
rule-transducers.

(Caption: <span style='font-variant: small-caps'>HFST-TwolC</span> performance broken into the different
phases of the compilation process. Times are in
seconds.)<a id="fig:grammar-compilation-phases">(¶ fig:grammar-compilation-phases)</a>
  </div>
<!-- end table -->


**Table:**[!h]
  <div style='text-align: center'>


| Language  |  1      |  2      |  3      |  4      |  Total    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| Finnish  |  0.10 s    |  1.44 s    |  0.36 s    |  0.07 s    |  1.97 s   |
| Northern S\’ami    |    0.90 s    |    154.60 s    |    18.26 s    |    0.41 s    |    174.17 s   |

    \vskip0.5cm

    *  Reading lexicon-transducer and rule-transducers.
    *  Computing intersecting composition.
    *  Determinizing and minimizing the result of the operation.
    *  Storing the minimized result of the operation.

(Caption: <span style='font-variant: small-caps'>HFST-Compose-Intersect</span> performance broken down
into the different phases of the compilation process. Times are in
seconds.)<a id="fig:ci-phases">(¶ fig:ci-phases)</a>
  </div>
<!-- end table -->

Finally, Table [(see: fig:memory-consumption)](#fig:memory-consumption) gives an indication of the
maximal memory consumption during the lexicon compilations using the
<span style='font-variant: small-caps'>HFST</span> tools and the Xerox tools.


**Table:**[!h]
  <div style='text-align: center'>


| Language  |    <span style='font-variant: small-caps'>HFST-LexC</span>    |    <span style='font-variant: small-caps'>HFST-TwolC</span>    |    <span style='font-variant: small-caps'>HFST-Compose-Intersect</span>   |
| ---- | ---- | ---- | ---- |
| French  |  596 MB    |  —    |  —   |
| Finish  |  181 MB    |  13 MB    |  48 MB   |
| Northern S\’ami    |    180 MB    |    291 MB    |    1090 MB (1.1 GB)   |
| Language  |    Xerox <span style='font-variant: small-caps'>LexC</span>    |    Xerox <span style='font-variant: small-caps'>TwolC</span>    |  |
| ---- | ---- | ---- | ---- |
| French  |    85 MB    |    —    |    —   |
| Finnish  |    28 MB    |    3 MB    |    —   |
| Northern S\’ami    |    13 MB    |    12 MB    |    —   |

    \vskip0.5cm
(Caption: Maximum space required using <span style='font-variant: small-caps'>HFST</span> and Xerox
utilities to compile the transducers. Space indications are in
megabytes (MB).)<a id="fig:memory-consumption">(¶ fig:memory-consumption)</a>
  </div>
<!-- end table -->

All tests were conducted on an Intel computer with a Xeon E5450 64 bit
3.00 GHz CPU and 64 GB of memory. For the <span style='font-variant: small-caps'>HFST</span> tools, the
times were extracted using the C language `clock` function. For
other tools, the GNU `time` command was used. In order to monitor
the memory consumption, we used the GNU `top` command.

<span style='font-variant: small-caps'>HFST</span> has both a weighted and an unweighted implementation,
but the current tests were performed using only the unweighted
implementation of <span style='font-variant: small-caps'>HFST</span>, i.e. in practice we used the
unweighted <span style='font-variant: small-caps'>SFST</span> library implementation of the <span style='font-variant: small-caps'>HFST</span>
tools.

## Discussion and Future Research

In this section we discuss the evaluation results and suggest some
further lines of research and development of the tools that the
evaluation figures seem to indicate. Comparing the total compilation
times for <span style='font-variant: small-caps'>HFST</span> tools, Xerox tools, foma <span style='font-variant: small-caps'>LexC</span> and
<span style='font-variant: small-caps'>SFST</span> compiler, shows that <span style='font-variant: small-caps'>HFST</span> is still a magnitude
slower than the Xerox tools. However, <span style='font-variant: small-caps'>HFST</span> compares well with
the other open-source tools. The decrease in compile-time for the
Finnish lexicon, when parallel-rules are used, is considerable by
improving performance with almost two magnitudes. Most importantly,
using the <span style='font-variant: small-caps'>HFST</span> tools is sufficiently quick not to slow down
the development of full-scale morphological analyzers. Even large
morphological analyzers like the analyzers for French and Northern
S\’ami already compile in less than ten minutes.

### HFST-LexC Performance

Comparing the <span style='font-variant: small-caps'>HFST-LexC</span> compilation times for French and
Northern S\’ami given in Table [(see: fig:lexicon-compilation-phases)](#fig:lexicon-compilation-phases),
we see that the entry parsing is almost linear. The lexicon for French
has about five times as many entries as the lexicon for Northern
S\’ami. This is a result of the trie-union described in
Sect. [(see: sec:HFST-LexC)](#sec:HFST-LexC), which speeds up the building of
sublexicons.

We also see that the number of sublexicons is currently very
influential on the <span style='font-variant: small-caps'>HFST-LexC</span> compile-time. The lexicon for
French only has one sub-lexicon, whereas the lexicon for Northern
S\’ami has 870 sub-lexicons. This indicates that the current
implementation of the morphotax filtering still slows down the
compilation with some unnecessary copying.

There are two main parts that dominate the time consumption of the
fourth column of Table [(see: fig:lexicon-compilation-phases)](#fig:lexicon-compilation-phases),
i.e. alphabet discovery and final determinization and minimization.
Since the <span style='font-variant: small-caps'>HFST</span> API and underlying libraries need the full
alphabet to be known prior to the compilation of the entries and the
<span style='font-variant: small-caps'>LexC</span> file format provides no declaration of the alphabet,
<span style='font-variant: small-caps'>HFST-LexC</span> needs to make an initial pass through the entries
before the actual compilation phase to gather the alphabet.  In
addition, the determinization and minimization of the final result
consumes well over half of the compile-time of the Northern S\’ami
lexicon (46,85 seconds), which we estimate is caused by a large number
of lexicons containing epsilon entries giving rise to indeterminism.

### HFST-TwolC Performance

Examining the <span style='font-variant: small-caps'>HFST-TwolC</span> compile-times for Finnish and
Northern S\’ami shows, that the last phase, i.e. combining contexts
and intersecting subrules, takes up approximately 90 % of the
compile-time. The compile-time for this phase depends heavily on the
intersection, subtraction and determinization algorithms used when
implementing the <span style='font-variant: small-caps'>HFST</span> API.

In <span style='font-variant: small-caps'>HFST</span>, we have not yet implemented an *other-symbol*
like the one in the Xerox <span style='font-variant: small-caps'>TwolC</span> presented by Karttunen
[(cites: Karttunen92)](#Karttunen92), the rule-transducers encode a number of
unnecessary transitions.  This slows down intersection, difference and
determinization among other operations. It is probably the single most
important factor slowing down <span style='font-variant: small-caps'>HFST-TwolC</span>. Like intersection,
intersecting composition is also affected by the lack of an
*other-symbol*, since intersecting composition is sensitive to
the number of transitions in the rule-transducers.

### Parallel Rules vs. Cascaded Rules

It is interesting to see, that the two-level <span style='font-variant: small-caps'>HFST-LexC</span> and
<span style='font-variant: small-caps'>HFST-TwolC</span> approach to compiling the <span style='font-variant: small-caps'>OMorFi</span> analyzer
for Finnish is so much more efficient than the cascade of
replace-rules, which constitutes the <span style='font-variant: small-caps'>SFST</span> implementation of
<span style='font-variant: small-caps'>OMorFi</span>. We know, that the difference lies in the approach to
compiling the lexicon and the rules, as the unweighted <span style='font-variant: small-caps'>HFST</span>
morphology tools ultimately perform their transducer operations using
the <span style='font-variant: small-caps'>SFST</span> library, even if this happens through the
<span style='font-variant: small-caps'>HFST</span> API.

One possible reason for the speed-up is that <span style='font-variant: small-caps'>HFST-LexC</span> and
<span style='font-variant: small-caps'>HFST-TwolC</span> are more constrained environments than the
<span style='font-variant: small-caps'>SFST</span> utility `fst-compiler` by Schmid [(cites: sfst)](#sfst),
which is used for compiling the <span style='font-variant: small-caps'>SFST</span> version of the
<span style='font-variant: small-caps'>OMorFi</span> analyzer. We suspect that the great liberty in
constructing rules using <span style='font-variant: small-caps'>SFST</span> may tempt the user to indulge
in unnecessarily unconstrained ways of expressing replacements with a
very local area of application. This manifests itself among other
things as an increased compile-time.

Converting the <span style='font-variant: small-caps'>LexC</span> and <span style='font-variant: small-caps'>TwolC</span> version of the Finnish
lexicon from the <span style='font-variant: small-caps'>SFST</span> lexicon compiler files took
approximately a week of manual work. While doing this, we were able to
slightly modify and improve the rules in order to remove some of the
incorrect readings that were coming through as analyses of the Finnish
cascaded rule analyzer, which had not been corrected before. This
indicates that the parallel rule set may be easier to test and debug
than the cascaded rules, but first and foremost it confirms the
well-known effect that a reduced compile-time is very significant for
the development process as it allows an increased number of test
cycles during a fixed time-span.

### The *Other-symbol*

We have demonstrated, that the morphology tools <span style='font-variant: small-caps'>HFST-LexC</span>,
<span style='font-variant: small-caps'>HFST-TwolC</span> and <span style='font-variant: small-caps'>HFST-Intersect-Compose</span> provide a
realistic open-source alternative for constructing morphological
analyzers in the two-level framework. Still, there is room for
improvement, as the performance of the Xerox tools show.

Currently the performance of both <span style='font-variant: small-caps'>HFST-TwolC</span> and
<span style='font-variant: small-caps'>HFST-Intersect-Compose</span> correlates strongly with the number of
symbol pairs in the alphabet of the two-level grammar. A significant
optimization for these <span style='font-variant: small-caps'>HFST</span> tools would be the introduction
of an *other-symbol*, which can represent the class of pairs
bearing no special meaning to a rule. Such a symbol would decrease the
number of transitions in rule-transducers. In case the number of
symbol-pairs of the alphabet is large, this has a significant impact
on the performance of both <span style='font-variant: small-caps'>HFST-TwolC</span> and
<span style='font-variant: small-caps'>HFST-Intersect-Compose</span>. In practice, the introduction of the
*other-symbol* makes both tools insensitive to the number of
symbols in the alphabet of the grammar. We believe, that this may help
us achieve rule compile-times closer to those of Xerox.

### Future Directions

In our future research, we intend to look at various aspects of and
methods for integrating the creation and use of weighted transducers
in morphologies. It is already possible to compile both weighted
two-level lexicons and grammars using <span style='font-variant: small-caps'>HFST</span> tools. These can
be combined into weighted lexical transducers using the weighted
version of <span style='font-variant: small-caps'>HFST-Intersect-Compose</span>. It is also possible to
adjoin meaningful weights to lexicon-entries in <span style='font-variant: small-caps'>HFST-LexC</span>.
Currently <span style='font-variant: small-caps'>HFST-TwolC</span> only provides a way to compile weighted
rules with zero-weights. However, even this small beginning allows us
to combine weighted lexicons and two-level grammars using weighted
intersecting composition. We are currently working on useful ways to
attach weights to two-level rules with applications for weighted
two-level grammars.

We were able to compare the performance of a cascaded rule approach
with a parallel rule approach using the same underlying finite-state
library. However, using our full-fledged morphologies, we could also
compare different underlying finite-state libraries on real
compilation tasks in order to compare different algorithms and their
implementations. A future task, would be to compare the performance of
e.g. the <span style='font-variant: small-caps'>SFST</span> library with that of <span style='font-variant: small-caps'>OpenFST</span>.  Our
preliminary evaluation results show that efficient and well-suited
determinization and minimization algorithms have a significant impact
on the real-world morphology compilation task.

## Conclusions

We have chosen to create open-source tools and language descriptions
in order to let as many as possible participate in the effort of
providing morphological analyzers for the languages of the world. The
current article present some of the main tools that we have created
based on our unified API for finite-state libraries. The tools include
<span style='font-variant: small-caps'>HFST-LexC</span>, <span style='font-variant: small-caps'>HFST-TwolC</span> and
<span style='font-variant: small-caps'>HFST-Compose-Intersect</span>. We have evaluated the efficiency of
the current implementations in comparison with some of the similar
tools and libraries available using several full-fledged morphological
descriptions. Our tools compare well with other similar open source
tools, even if we still have some challenges ahead before we can catch
up with the commercial tools. We demonstrate that for various reasons
a parallel rule approach seems to be more efficient than the cascaded
rule approach when developing finite-state morphologies.

## Acknowledgments

<span class='math'>...</span>

# References

* [1983]{Koskenniemi83}
Koskenniemi, K.:
Two-Level Morphology: A General Computational Model for Word-Form Recognition and Production.
University of Helsinki, Department of General Linguistics (1983).

* [1987]{Karttunen87}
Karttunen, L., Koskenniemi, K., Kaplan, R.:
A Compiler for Two-Level Phonological Rules.
CSLI Publications (1987)
<http://www2.parc.com/istl/members/karttune/publications/archive/twolcomp.pdf>.

* [1992]{Karttunen92}
Karttunen, L.:
Two-Level Rule Compiler, Technical Report ISTL-92-2, Xerox Palo Alto Research Center (1992).
<http://www.xrce.xerox.com/competencies/content-analysis/fssoft/docs/twolc-92/twolc92.html>.

* [1993]{Karttunen93}
Karttunen, L.:
Finite-State Lexicon Compiler.
Technical Report, ISTL-NLTT2993-04-02, Xerox Palo Alto Research Center (1993)
Palo Alto, California.

* [1994]{Karttunen94}
Karttunen, L.:
Constructing Lexical Transducers.
The Proceedings of the 15th International Conference on Computational Linguistics COLING 94, I, 406–411 (1994)

* [1997]{mohri1997}
Mohri, M.:
Finite-state transducers in language and speech processing.
Computational Linguistics 23(2), (1997)

* [2002]{mohri2002}
Mohri, M., Riley. M.:
An efficient algorithm for the n-best-strings problem.
Proceedings of the International Conference on Spoken Language Processing 2002, ICSLP ’02 (2002)

* [2003]{beesley03}
Beesley, K., Karttunen, L.:
Finite State Morphology.
CSLI Publications (2003).
<http://www.fsmbook.com>.

* [2004]{vaucanson}
Lombardy, S., R\’egis-Gianas, Y., Sakharovitch, J.:
Introducing Vaucanson.
Theoretical Computer Science 328, 77–96 (2004)

* [2005]{sfst}
Schmid, H.:
A programming language for finite state transducers.
Proceedings of the 5th International Workshop on Finite State Methods in Natural Language Processing, FSMNLP 2005, (2005).
Helsinki, Finland.

* [2006]{Yli-Jyra06}
Yli-Jyr\"a, A., Koskenniemi, K.:
Compiling Generalized Two-Level Rules and Grammars.
Advances in Natural Language Processing, LNCS, 174–185 (2006)

* [2007]{openfst}
Allauzen, C., Riley, M., Schalkwyk, J., Skut, W., Mohri, M.:
Open{F}st: A general and efficient weighted finite-state transducer library.
Proceedings of the Ninth International Conference on Implementation and Application of Automata, CIAA 2007, vol. 4783 LNCS, 11–23 (2007)
<http://www.openfst.org>.

* [2008]{pirinen2008}
Pirinen, T.:
Suomen kielen äärellistilainen automaattinen morfologia avoimen lähdekoodin menetelmin.
Master’s thesis, Helsingin yliopisto (2008)

\end{thebibliography}
\clearpage

<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

