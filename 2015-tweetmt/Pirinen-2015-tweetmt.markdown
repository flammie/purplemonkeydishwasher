

<!-- usepackage url,multirow,scrextend  -->

<!-- usepackage cleveref  -->


# Dublin City University at the TweetMT 2015 Shared Task¹ 

<span style='font-size:8pt'>(¹ Authors' archival version:  The real publication is in TweetMT 2015. in SEPLN 2015. The version you see here does not include the Spanish translations.)</span>

\author {
Antonio Toral, Xiaofeng Wu, Tommi Pirinen,

Zhengwei Qiu, Ergun Bicici, Jinhua Du

ADAPT Centre, School of Computing, Dublin City University, Ireland

\{atoral, xwu, tpirinen, zhengwei.qiu2, ebicici, jdu\}@computing.dcu.ie}









<!-- begin document -->




<a id="firstpage">(¶ firstpage)</a> <!-- make title -->



**Abstract:**
We describe our participation in TweetMT for three language pairs in both directions: Spanish from/to Catalan, Basque and Portuguese.
We used a range of techniques: statistical and rule-based MT, morph segmentation, data selection with ParFDA and system combination.
As for resources, our focus was on crawling vast amounts of tweets to perform monolingual domain adaptation.
Our system was the best of all systems submitted for five out of the six language directions.
<!-- end abstract -->




## Introduction and Objectives

While statistical machine translation (SMT) can be considered a mature technology nowadays, one of its requirements is the availability of considerable amounts of parallel text for the language pair of interest.
Ideally, the parallel text to train an SMT system should come from the same domain and genre as the text the system is going to be applied to.
Thus, using MT to translate types of text for which no parallel data is available constitutes a challenge.
This is the case for tweets and social media in general, the target text of the TweetMT shared task.

The main objective of our participation in the TweetMT 2015 shared task was to build the best MT systems for tweets we could with a clear constraint, i.e. it had to be done in a very short period and, to a large extent, be limited to available resources.
We have taken part for three language pairs in both directions: Spanish (ES) from/to Catalan (CA), Basque (EU) and Portuguese (PT).

We decided to focus on making the best possible use of available techniques, tools and resources.
Regarding techniques and tools, we rely on state-of-the-art SMT, morph segmentation for morphologically rich languages (EU), data selection with ParFDA for fast development of accurate SMT systems [(cites: Bicici:FDA54FDA:WMT15)](#Bicici:FDA54FDA:WMT15) and domain adaptation [(cites: BiciciPBML2015)](#BiciciPBML2015), the use of available open-source rule-based systems and, finally, system combination to take advantage of the strengths of the different systems we built.
As for resources, we crawl vast amounts of tweets to perform monolingual domain adaptation and complement this with publicly available general-domain monolingual and parallel corpora.

The rest of the paper is organised as follows.
Sections [(see: s:architecture)](#s:architecture) and [(see: sec:resources)](#sec:resources) detail the systems built and the resources used, respectively.
Section [(see: s:eval)](#s:eval) presents the evaluation and, finally, Section [(see: s:conclusion)](#s:conclusion) outlines conclusions and lines of future work.


## Architecture and Components of the System<a id="s:architecture">(¶ s:architecture)</a>

Here we describe the components used in our translation pipeline.
First, we pre-process the datasets (Section [(see: sec:data_preprocessing)](#sec:data_preprocessing)), then we use a set of MT systems (Section [(see: sec:mt_systems)](#sec:mt_systems)) that can incorporate additional functionality (Sections [(see: sec:morph_seg)](#sec:morph_seg) and [(see: sec:fda)](#sec:fda)).
Finally, we combine MT systems (Section [(see: sec:sys_combo)](#sec:sys_combo)).

### Data Preprocessing<a id="sec:data_preprocessing">(¶ sec:data_preprocessing)</a>

Prior to be used, all the datasets used in our systems are preprocessed, as follows:


*  Punctuation normalisation, with Moses’ [(cites: Koehn:2007:MOS:1557769.1557821)](#Koehn:2007:MOS:1557769.1557821) script.
*  Sentence splitting and tokenisation, with Freeling [(cites: padro12)](#padro12).
*  Normalisation (only for tweets). We sort the vocabulary of a tweet corpus by word frequency and inspect the words that occur in at least 0.5% of the tweets, creating rules to convert informal words to their formal equivalent.
This leads to just a handful of rules. E.g. in Spanish, “q”, occurring in 2.62% of the tweets, is converted to its formal equivalent “que”.*  Truecasing, with a modified version of Moses’ script. We added a set of start-of-sentence characters commonly used in Spanish: "-", "—", "¿", "“" and "‘".


### MT Systems<a id="sec:mt_systems">(¶ sec:mt_systems)</a>
We build SMT systems using two paradigms: phrase-based with Moses [(cites: Koehn:2007:MOS:1557769.1557821)](#Koehn:2007:MOS:1557769.1557821) and hierarchical with cdec [(cites: cdec)](#cdec).
In both cases we use default settings.
We also use off-the-shelf open-source rule-based MT (RBMT) systems.
Namely, Apertium [(cites: forcada11a)](#forcada11a) for ES<span class='math'>\leftrightarrow</span>CA, ES<span class='math'>\leftrightarrow</span>PT and EU<span class='math'>→</span>ES, (footnote: Revisions 60356, 60384, and 60356, respectively.) and Matxin [(cites: DBLP:journals/mt/MayorASLLS11)](#DBLP:journals/mt/MayorASLLS11) for ES<span class='math'>→</span>EU. (footnote: API at <http://ixa2.si.ehu.es/glabaka/Matxin.xml>)

The SMT systems use 5-gram LMs with Knesser-Ney smoothing [(cites: kneser1995improved)](#kneser1995improved) except for ParFDA Moses SMT systems, which use LMs of order 8 to 10.
We build LMs on individual monolingual corpora (cf. Section [(see: monolingualcorpora)](#monolingualcorpora)) and interpolate them with SRILM [(cites: stolcke2002srilm)](#stolcke2002srilm) to minimise the perplexity on the dev set.
Each target language and its corpora used to build LMs together with their interpolation weights are shown in Table [(see: t:mono)](#t:mono).
We observe that tweets are given very high weights even if they are not the biggest corpora in the mixes.










### Morphological Segmentation<a id="sec:morph_seg">(¶ sec:morph_seg)</a>
Morphological segmentation is a popular method to deal with SMT for morphologically differing languages by simply splitting words into sub-word units.
The main benefits of morphological segmentation are to reduce the out-of-vocabulary (OOV) rate and to increase the percentage of 1 to 1 word alignments between morphosyntactically different languages; e.g. in our case, by matching inflectional suffixes in EU to syntactic prepositions in ES, we expect to improve the MT quality for the EU–ES language pair. The segmentation and de-segmentation is able to create word-forms not present in the training data by matching a translated stem with a correct suffix.

In our participation, morphological segmentation was only used for EU–ES on the EU side, since EU’s morphology is significantly more complex than that of ES. For the remaining languages of the shared task, there is no such big difference in morphology complexity (all of them are closely-related as they belong to the same family) so the expected gains do not outweigh the added complexity of segmentation.

We use unsupervised statistical segmentation as provided by Morfessor 2.0 Baseline [(cites: morfessor)](#morfessor). (footnote: <http://www.cis.hut.fi/projects/morpho/morfessor2.shtml>) The basic setup for segmentation is the same as in the Abu-MaTran project submission to the WMT 2015 translation task [(cites: abumatran2015wmt)](#abumatran2015wmt).
However, some minor Twitter-related pre-processing has been added in order to keep URLs and hashtags intact. The parameters used for Morfessor training are the default of version 2.0.2-alpha and the data for training is the EU side of the ES–EU parallel training data (cf. Section [(see: ss:parallel_corpora)](#ss:parallel_corpora)).

To gauge the effects of our method as well as the morphological complexity of EU as compared to ES we show in Table [(see: table:morphs)](#table:morphs) the OOV rates and vocabulary sizes of the ES and EU sides of the ES–EU training corpus, and EU corpora after morphological segmentation.
Segmentation reduces the type-to-token ratio by a factor of 6 and the OOV rate by almost a factor of 10.

{<!-- small -->

**Table:**[t]


| ---- | ---- | ---- | ---- |\rule{-2pt}{15pt}
| <!-- bf -->Corpora  |  <!-- bf -->Tokens  |  <!-- bf -->Types  |  <!-- bf -->OOV |
\rule{-4pt}{10pt}
| ES  |  30,532,489  |  296,612  |  14.5 % |
| EU  |  24,966,862  |  605,207  |  25.4 % |
| EU morphs  |  35,293,220  |  100,990  |  2.6 % |

(Caption: Size of ES–EU training corpus in word tokens (ES and EU sides) and in morph tokens (EU).
<a id="table:morphs">(¶ table:morphs)</a>)
<!-- end table -->
}










**Table:**[t]
<!-- centering -->
<!-- minipage \linewidth -->
{<!-- footnotesize -->


}l@{<!-- hspace 0.075cm -->}|@{<!-- hspace 0.075cm -->}c@{<!-- hspace 0.15cm -->}
c@{<!-- hspace 0.15cm -->}c@{<!-- hspace 0.15cm -->}l@{<!-- hspace 0.075cm -->}|@{<!-- hspace 0.075cm -->}l@{<!-- hspace 0.15cm -->}l@{<!-- hspace 0.15cm -->}l@{
<!-- hspace 0.15cm -->}l@{<!-- hspace 0.0cm -->}}
| ---- | ---- | ---- |
| <span class='math'>5</span>-gram  |  | <!-- FIXME: multicolumn 4 c|@{<!-- hspace 0.075cm --> -->}{OOV}  |  | <!-- FIXME: multicolumn 4 c -->{perplexity} |
| <span class='math'>S</span><span class='math'>→</span><span class='math'>T</span>  |  <span class='math'>\stackrel{\mbox{C}}{\mbox{train}}</span>  |  <span class='math'>\stackrel{\mbox{FDA}}{\mbox{train}}</span>  |  
| <span class='math'>\stackrel{\mbox{FDA}}{\mbox{LM}}</span>  |  %red  |  <span class='math'>\stackrel{\mbox{C}}{\mbox{train}}</span>  |  
| <span class='math'>\stackrel{\mbox{FDA}}{\mbox{train}}</span>  |  <span class='math'>\stackrel{\mbox{FDA}}{\mbox{LM}}</span>  |  %red |
| CA–ES  |  2948  |  2957  |  2324  |  .21  |  332  |  336  |  294  |  .11 |
| EU–ES  |  3021  |  3046  |  2443  |  .19  |  462  |  483  |  546  |  -.18 |
| PT–ES  |  2871  |  2896  |  1951  |  **.32**  |  633  |  623  |  486  |  .23 |
| ES–CA  |  3338  |  3345  |  2890  |  .13  |  325  |  330  |  338  |  -.04 | 
| ES–EU  |  4110  |  4129  |  3349  |  .19  |  745  |  761  |  637 (footnote: <a id="es-eu_LM">(¶ es-eu_LM)</a>ES–EU LM is recomputed after the task, 
| removing duplicates, which slightly decrease BLEU, increase NIST.)  |  .15\footref{es-eu_LM} |
| ES–PT  |  3087  |  3117  |  2216  |  .28  |  993  |  941  |  746  |  **.25** |

} (Caption: LM comparison built from training corpus (C train), ParFDA
selected training data (FDA train), ParFDA selected LM data (FDA LM). <span class='math'>%</span>red is reduction proportion.
)
<a id="LMPerplexityComparison">(¶ LMPerplexityComparison)</a>
<!-- /minipage -->
<!-- end table -->

### ParFDA<a id="sec:fda">(¶ sec:fda)</a>

ParFDA parallelizes instance selection with an optimized parallel implementation of FDA5 and significantly reduces the 
time to deploy accurate SMT systems especially in the presence of large training data and still achieve state-of-the-art SMT performance [(cites: Bicici:FDA54FDA:WMT15,BiciciYuret:FDA5:TASLP)](#Bicici:FDA54FDA:WMT15,BiciciYuret:FDA5:TASLP).
Detailed composition of the available corpora, which is referred to as constrained (C), are provided in \Cref{sec:resources}.
For ES, we also included LDC Gigaword corpora [(cites: LDCGigawordSpanish)](#LDCGigawordSpanish).
The size of the LM corpora includes both the LDC and the monolingual LM corpora provided.
ParFDA selected training and LM data obtains accurate
translation outputs with the selected LM data reducing the number of OOV tokens by up to <span class='math'>32%</span> and the perplexity by up to <span class='math'>25%</span> and allows us to model higher order dependencies (\Cref{LMPerplexityComparison}).

### System Combination<a id="sec:sys_combo">(¶ sec:sys_combo)</a>

For each language direction we have built up to five systems, as detailed in Sections [(see: sec:mt_systems)](#sec:mt_systems) to [(see: sec:fda)](#sec:fda):
(i) phrase-based and (ii) hierarchical SMT, (iii) phrase-based with morph segmentation, (iv) phrase-based with ParFDA and (v) RBMT.
We hypothesise these systems to have complementary strengths, and thus we decide to perform system combination.
To that end we use MEMT [(cites: heafield2010combining)](#heafield2010combining), with default settings, except for the parameter `length`, for which we use its default (7) for all directions except for ES<span class='math'>→</span>EU, for which we use 5 according to empirical results on the development set.



## Resources Employed
<a id="sec:resources">(¶ sec:resources)</a>

### Parallel Corpora<a id="ss:parallel_corpora">(¶ ss:parallel_corpora)</a>

Ideally, we would use data in the same domain and genre as the test set, i.e. tweets.
We have access to parallel tweets provided by the task for ES–CA and ES–EU (4,000 parallel tweets for each language pair, we use 1,000 for dev and the remaining 3,000 for training).
For ES–PT we have access to 999 parallel tweets (we use them for dev) from Brazilator, (footnote: <http://www.cngl.ie/brazilator>) a recent project by DCU and Microsoft to translate tweets from the 2014 soccer World Cup across 24 language directions.

As the availability of parallel tweets for the language pairs of TweetMT 2015 is rather limited (at most we have 4,000 per language pair), we use additional sources of parallel data.
For ES–CA we use elPeriodico (eP) (footnote: <http://catalog.elra.info/product_info.php?products_id=1122>) and a selection of contemporary novels.
For ES–EU, translation memories (TMs) provided by the shared task (footnote: <http://komunitatea.elhuyar.org/tweetmt/resources/>)
and two corpora from Opus [(cites: TIEDEMANN12.463)](#TIEDEMANN12.463): (footnote: <http://opus.lingfil.uu.se/>) Open subtitles 2013 and Tatoeba.
Finally, for ES–PT we use Europarl v7 (footnote: <http://www.statmt.org/europarl/>) and two corpora from Opus: news-commentary and Tatoeba.
Table [(see: t:parallel_data)](#t:parallel_data) provides details on these corpora.



    



{<!-- small -->

**Table:** [t]
<!-- centering -->


{clrr}
|\rule{-2pt}{15pt}
| <!-- bf -->Pair  |  <!-- bf -->Corpus  |  <!-- bf -->\# s.  |  <!-- bf -->\# tokens|
| \multirow{3}{*}{ES–CA}  |  tweets  |  3K |  48k, 48k|
|  |  eP  |  0.6M  |  13.5M, 14M |
|  |  novels  |  47K  |  .78M, .86M|
| \multirow{4}{*}{ES–EU}  |  tweets  |  3K |  42K, 38K|
|  |  TMs  |  1.1M  |  28.9M, 23.5M|
|  |  OpenSubs  |  0.16M  | 1.2M, 1.0M|
|  |  Tatoeba  |  902  | 6.7K, 5.5K|
| \multirow{3}{*}{ES–PT}  |  EU  |  1.9M |  54M, 53M|
|  |  NC  |  9K  |  .26M, .25M|
|  |  Tatoeba  |  53K |  .42M, .41M|

(Caption: <a id="t:parallel_data">(¶ t:parallel_data)</a>Parallel corpora used for training.
For each corpus we provide its number of sentence pairs (\# s.) and tokens on both sides (\# tokens).)
<!-- end table -->
}





### <a id="monolingualcorpora">(¶ monolingualcorpora)</a>Monolingual Corpora


Our main source of monolingual data is in-domain and comes from crawled tweets.
We use TweetCat [(cites: ljubesic14-tweetcat)](#ljubesic14-tweetcat) and crawl tweets for all the target languages (CA, ES, EU and PT) during March and April 2015.

For each language we create two lists of words as required by the crawler:
(i) most common discriminating words (up to 100), these are words that are unique to the language and they are used to seed the crawler so that it can find candidate tweets;
and (ii) most common words of the language (200), these are used to determine the language of crawled tweets.
These two lists are derived from a list of the most common words found in a corpus of subtitles. (footnote: <https://onedrive.live.com/?cid=3732e80b128d016f&id=3732E80B128D016F!3584>)

The tweets crawled are post-processed with langid (footnote: <https://github.com/saffsd/langid.py>) to identify their language.
We keep the tweets whose langid’s confidence score is above a certain threshold, which is set empirically at 0.7 by inspecting tweets.

In addition to crawled tweets, we use the target sides of the parallel corpora (cf. Section [(see: ss:parallel_corpora)](#ss:parallel_corpora) and a set of monolingual corpora as follows.
For CA we use caWaC [(cites: LJUBEI14.841)](#LJUBEI14.841), a corpus crawled from the `.cat` top level domain.
For ES, news crawl and news-commentary from WMT’13. (footnote: <http://www.statmt.org/wmt13/>)
For EU, a dump from Wikipedia (20150407).
For PT, the news sources CETEMPublico, (footnote: <http://www.linguateca.pt/cetempublico/>) and CETENFolha, (footnote: <http://www.linguateca.pt/cetenfolha/>) and a dump from Wikipedia (20150510).

Table [(see: t:mono)](#t:mono) shows details on these corpora including their interpolation weights (cf. Section [(see: sec:mt_systems)](#sec:mt_systems)).




{<!-- small -->

**Table:** [t]
<!-- centering -->


{clrrr}
|\rule{-2pt}{15pt}
| <!-- bf -->Lang  |  <!-- bf -->Corpus   |  <!-- bf -->\# tokens  |  <!-- bf -->Weights |
| \multirow{3}{*}{CA}  |  tweets  |  29M  |  0.60 |
|  |  caWaC  |  0.5G  |  0.33 |
|  |  eP  |  14M  |  0.07 |
| \multirow{3}{*}{ES}  |  tweets  |  129.2M  |  0.75 |
|  |  news  |  0.4G  |  0.21|
|  |  europarl  |  60M  |  0.04  |  |
| \multirow{3}{*}{EU}  |  tweets  |  11.3M  |  0.97 |
|  |  Wikipedia  |  11.5M  | 0.01|
|  |  TMs  |  23M  |  0.02 |
| \multirow{3}{*}{PT}  |  tweets  |  33M |  0.93 |
|  |  Wikipedia  | 166M  |  0.02|
|  |  Others  |  286M  |  0.05 |
\rule{-4pt}{10pt}

(Caption: <a id="t:mono">(¶ t:mono)</a>Monolingual corpora used for training.
For each corpus we show its number of tokens (\# tokens) and its weight in LM interpolation.)
<!-- end table -->
}












## Evaluation<a id="s:eval">(¶ s:eval)</a>


We report our results on the development set (all systems built) and then on the test set (systems submitted).


### Evaluation on Development Data

Table [(see: t:res_dev)](#t:res_dev) presents the results obtained on the devset by the individual systems and a set of combinations
for the three language pairs we covered: ES–CA, ES–EU and ES–PT.
The scores were obtained on raw MT output (i.e. tokenised and truecased) as calculated by us with BLEU [(cites: papineni2002bleu)](#papineni2002bleu) (multibleu cased as included in Moses version 3) and TER [(cites: snover2006study)](#snover2006study) (as implemented in TERp version 0.1). Due to time constraints not all the possible combinations were tried.
The scores of the best individual system and combination are shown in bold.


{<!-- small -->

**Table:** [hbtp]
<!-- centering -->


{llrr}
|\rule{-2pt}{15pt}
|  |  <!-- bf -->System  |  <!-- bf -->BLEU  |  <!-- bf -->TER|
| \multirow{7}{*}{\rotatebox[origin=c]{90}{ES<span class='math'>→</span>CA}}  |  Moses (1)  | 	82.21	 | 0.1102|
|  | cdec (2)   | 	81.45	 | 0.1128|
|  | ParFDA (3) | 		<!-- bf -->82.37	 | <!-- bf -->0.1062|
|  | Apertium (4) | 	78.17	 | 0.1310|
\cline{2-4}
|  | 1+2		 | 81.71	 | 0.1102|
|  | 1+4		 | <!-- bf -->82.37	 | <!-- bf -->0.1057|
|  | 1+2+4	 | 81.93	 | 0.1085|
| \multirow{8}{*}{\rotatebox[origin=c]{90}{CA<span class='math'>→</span>ES}}  |  Moses (1)	 | <!-- bf -->82.52	 | 0.1086|
|  |  cdec (2)	 | 81.76	 | 0.1118|
|  |  ParFDA (3)	 | 82.16	 | <!-- bf -->0.1063|
|  |  Apertium (4)  | 77.96	 | 0.1329|
\cline{2-4}
|  |  1+2		 | 82.38	 | 0.1088|
|  |  1+4		 | <!-- bf -->82.58	 | 0.1077|
|  |  1+2+4		 | 82.38	 | 0.1083|
|  |  1+3+4		 | 82.45	 | <!-- bf -->0.1074|
\multirow{10}{*}{\rotatebox[origin=c]{90}{ES<span class='math'>→</span>EU}}
|  |   Moses (1)  | 	22.57 | 	0.6116|
|  | cdec (2)  | 	<!-- bf -->23.7 | 	<!-- bf -->0.5863|
|  | ParFDA (3) | 	21.59 | 	0.6181|
|  | Matxin (4) | 	12.66 | 	0.7436|
|  | Morph (5) |  5.20 | 	0.8812|   \cline{2-4}
|  | 1+2	 | 23.18	 | 0.5796|
|  | 1+4	 | 18.36	 | 0.6112|
|  | 1+2+4  | 23.58	 | 0.5771|
|  | 1+2+4+5 | 24.07	 | <!-- bf -->0.5741|
|  | 1+2+3+4+5 | <!-- bf -->24.42	 | 0.5777|
\multirow{9}{*}{\rotatebox[origin=c]{90}{EU<span class='math'>→</span>ES}}
|  | Moses (1)		 | 24.21	 | 0.6228|
|  | cdec (2)  	 | <!-- bf -->24.65	 | <!-- bf -->0.5911|
|  | ParFDA (3)	 | 22.25	 | 0.6346|
|  | Apertium (4)	 | 18.36	 | 0.6918|
|  | Morph (5)		 | 11.25	 | 0.9655|
\cline{2-4}
|  | 1+2			 | 24.18	 | 0.5883|
|  | 1+4			 | 24.33	 | 0.6076|
|  | 1+2+4			 | 24.94	 | 0.5831|
|  | 1+2+4+5		 | <!-- bf -->25.21	 | <!-- bf -->0.5792|
\multirow{7}{*}{\rotatebox[origin=c]{90}{ES<span class='math'>→</span>PT}}
|  | Moses (1)		 | <!-- bf -->29.21	 | 0.6052|
|  | cdec (2)		 | 28.14	 | <!-- bf -->0.5962|
|  | ParFDA (3)	 | 27.74	 | 0.6164|
|  | Apertium (4)	 | 24.96	 | 0.6272|
\cline{2-4}
|  | 1+2			 | <!-- bf -->28.76	 | 0.5891|
|  | 1+4			 | 26.58	 | 0.6082|
|  | 1+2+4			 | 27.00		 | <!-- bf -->0.5878|
\multirow{7}{*}{\rotatebox[origin=c]{90}{PT<span class='math'>→</span>ES}}
|  | Moses (1) 	 | <!-- bf -->30.47	 | 0.5267|
|  | cdec (2)		 | 29.42	 | <!-- bf -->0.5254|
|  | ParFDA (3)	 | 29.63	 | 0.5338|
|  | Apertium (4)	 | 27.52	 | 0.5335|
\cline{2-4}
|  | 1+2			 | <!-- bf -->29.9	 | 0.5230|
|  | 1+4			 | 30.01	 | 0.5131|
|  | 1+2+4			 | 29.89	 | <!-- bf -->0.5089|

(Caption: <a id="t:res_dev">(¶ t:res_dev)</a>Results on the dev set.)
<!-- end table -->
}





At least one of the combinations obtains better scores (both in terms of BLEU and TER) than the best individual system (except for ES<span class='math'>\leftrightarrow</span>PT with BLEU and for CA<span class='math'>→</span>ES with TER), supporting our hypothesis that the individual systems built are complementary.
Although SMT systems outperform RBMT systems for all directions, (footnote: When interpreting the results, it should be taken into account that automatic metrics are known to be biased towards statistical MT approaches [(cites: E06-1032)](#E06-1032).) the addition of RBMT in system combinations has a positive impact (except for ES<span class='math'>\leftrightarrow</span>PT).
Phrase-based SMT outperforms hierarchical SMT for related language pairs (ES–CA and ES–PT), but the opposite is true for the unrelated language pair ES–EU. We hypothesise this is due to the fact that ES and EU follow different word orders (SVO and SOV, respectively), and this leads to pervasive long reorderings in translation, that are better modelled with a hierarchical approach.

### Evaluation on Test Data

Table [(see: t:res_test)](#t:res_test) presents the results on the test set of the systems we submitted.
The scores shown are the ones reported by the organisers (case-insensitive BLEU and TER) on post-processed MT outputs (detokenised and detruecased).
For each language direction we submitted the three systems that obtained the best performance on the dev set.
The scores of the best submitted system are shown in bold.



{<!-- small -->

**Table:**[t]
<!-- centering -->


{llll}
|\rule{-2pt}{15pt}
|  |  <!-- bf -->System  |  <!-- bf -->BLEU  |  <!-- bf -->TER|
\multirow{3}{*}{\rotatebox[origin=c]{90}{{<!-- footnotesize --> ES<span class='math'>→</span>CA}}}
|  | DCU1 (1+4)	 | 0.7669		 | 0.1740|
|  | DCU2 (1)		 | <!-- bf -->0.7899<span class='math'>^\dagger</span>		 | <!-- bf -->0.1626<span class='math'>^\dagger</span>|
|  | DCU3 (1+2+4)	 | 0.7630		 | 0.1738|
\multirow{3}{*}{\rotatebox[origin=c]{90}{{<!-- footnotesize --> CA<span class='math'>→</span>ES}}}
|  | DCU1 (1+4)	 | 0.7826		 | 0.1506|
|  | DCU2 (1+2+4)	 | 0.7816		 | 0.1500|
|  | DCU3 (1+3+4)	 | <!-- bf -->0.7943<span class='math'>^\dagger</span>	 | <!-- bf -->0.1431<span class='math'>^\dagger</span>|
\multirow{3}{*}{\rotatebox[origin=c]{90}{{<!-- footnotesize --> ES<span class='math'>→</span>EU}}}
|  | DCU1 (1+2+4)		 | 0.2455					 | 0.6533|
|  | DCU2 (1+2+3+4+5)	 | <!-- bf -->0.2636<span class='math'>^\dagger</span>	 | <!-- bf -->0.6469<span class='math'>^\dagger</span>|
|  | DCU3 (1+2+4+5)	 | 0.2493					 | 0.6553|
\multirow{3}{*}{\rotatebox[origin=c]{90}{{<!-- footnotesize --> EU<span class='math'>→</span>ES}}}
|  | DCU1 (2)			 | 0.2687	 | 0.6512|
|  | DCU2 (1+2+4)		 | 0.2698	 | 0.6406|
|  | DCU3 (1+2+4+5)	 | <!-- bf -->0.2728	 | <!-- bf -->0.6363|
\multirow{3}{*}{\rotatebox[origin=c]{90}{{<!-- footnotesize --> ES<span class='math'>→</span>PT}}}
|  | DCU1 (1)		 | 0.3595					 | 0.5290|
|  | DCU2 (1+2)	 | <!-- bf -->0.3711<span class='math'>^\dagger</span>	 | <!-- bf -->0.5157<span class='math'>^\dagger</span>|
|  | DCU3 (1+2+4)	 | 0.3687					 | 0.5163|
\multirow{3}{*}{\rotatebox[origin=c]{90}{{<!-- footnotesize --> PT<span class='math'>→</span>ES}}}
|  | DCU1 (1)		 | 0.4465					 | 0.5767|
|  | DCU2 (1+2)	 | 0.4467					 | 0.5627|
|  | DCU3 (1+2+4)	 | <!-- bf -->0.4524<span class='math'>^\dagger</span>	 | <!-- bf -->0.5403<span class='math'>^\dagger</span>|

(Caption: <a id="t:res_test">(¶ t:res_test)</a>Results on the test set.)
<!-- end table -->
}


Out of six directions, our best submission is the top performing system for five of them (indicated with <span class='math'>\dagger</span>).
For most directions, the addition of a RBMT system leads to better performance.
Similarly, for the directions where we have used segmentation (ES<span class='math'>\leftrightarrow</span>EU) and ParFDA (CA<span class='math'>→</span>ES and ES<span class='math'>→</span>EU), the addition of systems based on these techniques had a positive impact on the results.

We now delve deeper into the results obtained by SMT systems based on ParFDA (cf. Section [(see: sec:fda)](#sec:fda)).
Although ParFDA systems were submitted to the shared task only as part of system combinations, we have evaluated *a posteriori* the performance of this technique by means of standalone systems on the test set.
ParFDA Moses SMT system obtains top results in CA<span class='math'>→</span>ES and ES<span class='math'>→</span>CA and close to top results in other language pairs with  <span class='math'>1.21</span> BLEU points average difference to the top (\Cref{ParFDA_TranslationResults}).
An interesting feature of ParFDA regards its ability to build and deploy SMT systems in a quick manner. In the specific case of TweetMT,
ParFDA took about 8 hours to build for ES<span class='math'>→</span>CA and 28 hours for PT<span class='math'>→</span>ES taking about 11 GB and 27 GB disk space in total, respectively. 



**Table:**[t]
<!-- centering -->
{

}l|lll@{<!-- hspace 0.0cm -->}}
| ---- | ---- | ---- |
| TweetMT  |  CA–ES  |  EU–ES  |  PT–ES |
| ParFDA  |  **.8012**  |  .2713  |  .4374 |
| Top  |  .7942  |  .3109  |  .4519 |
| diff  |  -.007  |  .0396  |  .0145 |
| LM order  |  8  |  8  |  8 |
|  |  ES–CA  |  ES–EU  |  ES–PT |
\cline{2-4}
| ParFDA  |  **.7926**  |  .2482  |  .3589 |
| Top  |  .7907  |  .2636  |  .3711 |
| diff  |  -.0019  |  .0154  |  .0122 |
| LM order  |  8  |  10  |  8 |

} (Caption: BLEU results for ParFDA standalone systems on the test set, their difference to the top, and ParFDA LM order used. 
ParFDA obtains top results in CA<span class='math'>→</span>ES and ES<span class='math'>→</span>CA and <span class='math'>1.21</span> BLEU points average difference.)
<a id="ParFDA_TranslationResults">(¶ ParFDA_TranslationResults)</a>
<!-- end table -->



## Conclusions and Future Work<a id="s:conclusion">(¶ s:conclusion)</a>

This paper has described our participation in the TweetMT 2015 shared task.
Our focus has been on rapid development of MT systems adapted to tweets by making the best possible use of available techniques, tools and resources.
Our best submissions have been the ones that combine different MT systems (except for ES<span class='math'>→</span>CA), supporting our hypothesis that the techniques we have used are complementary.

As for future work, we consider several possible avenues.
First, we would like to analyse in detail the translations produced by our systems in order to derive findings beyond the ones we can extract from the automatic evaluation metrics used in the task.
Second, most of the tweets in the test set use formal language, (footnote: This is due to the fact that they are extracted from twitter accounts that publish tweets in multiple languages, and such accounts belong, to a large extent, to institutions that use formal language.) and thus we would like to test our systems in a more representative set of tweets where informal language would be expected to be more pervasive.

## Acknowledgments

This research is supported by the EU 7th Framework Programme FP7/2007-2013 under grant agreement PIAP-GA-2012-324414 (Abu-MaTran),
by SFI as part of the
ADAPT research center (07/CE/I1142) at Dublin City University and
the project “Monolingual and Bilingual Text Quality Judgments with Translation Performance Prediction” (13/TIDA/I2740).
We also thank the SFI/HEA Irish Centre for High-End Computing (ICHEC) for the
provision of computational facilities and support.
Finally, we would like to thank Mikel L. Forcada and Iacer Calixto for their advice on normalising tweets for Basque and Portuguese, respectively, and Gorka Labaka for his help with Matxin’s API.

<!-- bib style: unsrt -->
# References

* <a id="Bicici:FDA54FDA:WMT15">**Bicici:FDA54FDA:WMT15**</a>:
    * author: Ergun Bi
c{c}ici and Qun Liu and Andy Way
    * title: {ParFDA} for Fast Deployment of Accurate Statistical Machine...
    * booktitle: Proceedings of the EMNLP 2015 Tenth Workshop on Statistical ...
    * month: September
    * year: 2015
    * address: Lisbon, Portugal
    * publisher: Association for Computational Linguistics
* <a id="BiciciPBML2015">**BiciciPBML2015**</a>:
    * author: Ergun Bi
c{c}ici
    * title: Domain Adaptation for Machine Translation with Instance Sele...
    * journal: The Prague Bulletin of Mathematical Linguistics
    * year: 2015
    * volume: 103
    * pages: 5–20
    * issn: 1804-0462
    * doi: 10.1515/pralin-2015-0001
    * keywords: Machine Translation, Machine Learning, Domain Adaptation
* <a id="Koehn:2007:MOS:1557769.1557821">**Koehn:2007:MOS:1557769.1557821**</a>:
    * author: Koehn, Philipp and Hoang, Hieu and Birch, Alexandra and Call...
    * title: Moses: Open Source Toolkit for Statistical Machine Translati...
    * booktitle: Proceedings of the 45th Annual Meeting of the ACL on Interac...
    * series: ACL ’07
    * year: 2007
    * location: Prague, Czech Republic
    * pages: 177–180
    * numpages: 4
    * url: http://dl.acm.org/citation.cfm?id
    * acmid: 1557821
    * publisher: Association for Computational Linguistics
    * address: Stroudsburg, PA, USA
* <a id="padro12">**padro12**</a>:
    * author: Lluís Padró and Evgeny Stanilovsky
    * title: FreeLing 3.0: Towards Wider Multilinguality
    * booktitle: Proceedings of the Language Resources and Evaluation Confere...
    * organization: ELRA
    * address: Istanbul, Turkey
    * year: 2012
* <a id="cdec">**cdec**</a>:
    * author: Chris Dyer and Adam Lopez and Juri Ganitkevitch and Johnatha...
    * title: cdec: A Decoder, Alignment, and Learning Framework for Finit...
    * booktitle: Proceedings of the Association for Computational Linguistics...
    * year: 2010
* <a id="forcada11a">**forcada11a**</a>:
    * author: Mikel L. Forcada and Mireia Ginest
’i-Rosell andJacob Nordf...
    * title: Apertium: a free/open-source platform for rule-based
    * journal: Machine Translation
    * note: Special Issue: Free/Open-Source Machine Translation
    * year: 2011,
    * volume: 25,
    * number: 2,
    * pages: 127–144
* <a id="DBLP:journals/mt/MayorASLLS11">**DBLP:journals/mt/MayorASLLS11**</a>:
    * author: Aingeru Mayor and
    * title: 
emph{Matxin}, an open-source rule-based machine translatio...
    * journal: Machine Translation
    * volume: 25
    * number: 1
    * pages: 53–82
    * year: 2011
    * url: http://dx.doi.org/10.1007/s10590-011-9092-y
    * doi: 10.1007/s10590-011-9092-y
    * timestamp: Thu, 18 Aug 2011 14:33:00 +0200
    * biburl: http://dblp.uni-trier.de/rec/bib/journals/mt/MayorASLLS11
    * bibsource: dblp computer science bibliography, http://dblp.org
* <a id="kneser1995improved">**kneser1995improved**</a>:
    * title: Improved backing-off for m-gram language modeling
    * author: Kneser, Reinhard and Ney, Hermann
    * booktitle: Acoustics, Speech, and Signal Processing, 1995. ICASSP-95., ...
    * volume: 1
    * pages: 181–184
    * year: 1995
    * organization: IEEE
* <a id="stolcke2002srilm">**stolcke2002srilm**</a>:
    * title: SRILM-an extensible language modeling toolkit.
    * author: Stolcke, Andreas and others
    * booktitle: INTERSPEECH
    * year: 2002
* <a id="morfessor">**morfessor**</a>:
    * title: Morfessor 2.0: Python implementation and extensions for morf...
    * author: Virpioja, Sami and Smit, Peter and Grönroos, Stig-Arne and K...
    * year: 2013
    * publisher: Aalto University
* <a id="abumatran2015wmt">**abumatran2015wmt**</a>:
    * title: {Abu-MaTran at WMT 2015 Translation Task: Morphological Segm...
    * year: 2015
    * author: Raphael Rubino and Tommi Pirinen and Miquel Esplà-Gomis and ...
    * booktitle: Proceedings of the Tenth Workshop on Statistical Machine Tra...
* <a id="BiciciYuret:FDA5:TASLP">**BiciciYuret:FDA5:TASLP**</a>:
    * author: Ergun Bi
c{c}ici and Deniz Yuret
    * journal: {IEEE/ACM} Transactions On Audio, Speech, and Language Proce...
    * title: Optimizing Instance Selection for Statistical Machine Transl...
    * year: 2015
    * pages: 339-350
    * volume: 23
    * doi: 10.1109/TASLP.2014.2381882
* <a id="LDCGigawordSpanish">**LDCGigawordSpanish**</a>:
    * author: 
^Angelo Mendon
c{c}a and Daniel Jaquette and David Graff ...
    * title: Spanish Gigaword Third edition, Linguistic Data Consortium
    * address: Philadelphia, USA
    * year: 2011
* <a id="heafield2010combining">**heafield2010combining**</a>:
    * title: Combining Machine Translation Output with Open Source: The C...
    * author: Heafield, Kenneth and Lavie, Alon
    * journal: The Prague Bulletin of Mathematical Linguistics
    * volume: 93
    * pages: 27–36
    * year: 2010
* <a id="TIEDEMANN12.463">**TIEDEMANN12.463**</a>:
    * author: Jörg Tiedemann
    * title: Parallel Data, Tools and Interfaces in OPUS
    * booktitle: Proceedings of the Eight International Conference on Languag...
    * year: 2012
    * month: may
    * date: 23-25
    * address: Istanbul, Turkey
    * editor: Nicoletta Calzolari (Conference Chair) and Khalid Choukri an...
    * publisher: European Language Resources Association (ELRA)
    * isbn: 978-2-9517408-7-7
    * language: english
* <a id="ljubesic14-tweetcat">**ljubesic14-tweetcat**</a>:
    * Address: Reykjavik, Iceland
    * Author: Nikola Ljubešić and Darja Fišer and Toma{
v z} Erjavec
    * Booktitle: Proceedings of the Ninth International Conference on Languag...
    * Title: {TweetCaT: a Tool for Building Twitter Corpora of Smaller La...
    * Year: 2014
* <a id="LJUBEI14.841">**LJUBEI14.841**</a>:
    * author: Nikola Ljubešić and Antonio Toral
    * title: caWaC - a Web Corpus of Catalan and its Application to Langu...
    * booktitle: Proceedings of the Ninth International Conference on Languag...
    * year: 2014
    * month: may
    * date: 26-31
    * address: Reykjavik, Iceland
* <a id="papineni2002bleu">**papineni2002bleu**</a>:
    * title: BLEU: a method for automatic evaluation of machine translati...
    * author: Papineni, Kishore and Roukos, Salim and Ward, Todd and Zhu, ...
    * booktitle: Proceedings of the 40th annual meeting on association for co...
    * pages: 311–318
    * year: 2002
* <a id="snover2006study">**snover2006study**</a>:
    * title: A study of translation edit rate with targeted human annotat...
    * author: Snover, Matthew and Dorr, Bonnie and Schwartz, Richard and M...
    * booktitle: Proceedings of Association for machine translation in the Am...
    * pages: 223–231
    * year: 2006
* <a id="E06-1032">**E06-1032**</a>:
    * author: Chris Callison-Burch and Miles Osborne and Philipp Koehn
    * booktitle: 11th Conference of the European Chapter of the Association f...
    * title: Re-evaluation the Role of Bleu in Machine Translation Resear...
    * url: http://www.aclweb.org/anthology/E06-1032
    * year: 2006
    * pages: 249–256



<!-- end document -->














* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

