

<!-- usepackage booktabs  -->
<!-- usepackage microtype  -->
<!-- usepackage color  --> 
# Abu-MaTran at WMT 2015 Translation Task:
Morphological Segmentation and Web Crawling ¹ 

<span style='font-size:8pt'>(¹ Authors' archival version: The official publication was in WMT 2015 workshop, in EMNLP 2015, and published version can be found in  <http://statmt.org/wmt15/papers.html>  or ACL anthology.)</span>


**Authors:** Raphael Rubino<span class='math'>^{★</span>, Tommi Pirinen<span class='math'>^{†}</span>, 
Miquel Esplà-Gomis<span class='math'>^{‡}</span>, Nikola Ljubešić<span class='math'>^{γ}</span>,

Sergio Ortiz-Rojas<span class='math'>^{★}</span>, Vassilis Papavassiliou<span class='math'>^</span>,
Prokopis Prokopidis<span class='math'>^</span>, Antonio Toral<span class='math'>^{†}</span>\vspace*{.2cm}

<span class='math'>^{★}</span> Prompsit Language Engineering, S.L., Elche, Spain

<!-- small -->{`\{rrubino,sortiz\`@prompsit.com}}

<span class='math'>^†</span> NCLT, School of Computing, Dublin City University, Ireland

<!-- small -->{`\{atoral,tpirinen\`@computing.dcu.ie}}

<span class='math'>^‡</span> Dep. Llenguatges i Sistemes Informàtics, Universitat d’Alacant, Spain

<!-- small -->{`mespla@dlsi.ua.es`}

<span class='math'>^γ</span> Department of Information and Communication Sciences, University of Zagreb, Croatia

<!-- small -->{`nljubesi@ffzg.hr`}

<span class='math'>^</span> Institute for Language and Speech Processing, Athena Research and Innovation Center, Greece

<!-- small -->{`\{vpapa, prokopis\`@ilsp.gr}}}
**Date:** 

<!-- begin document -->

<!-- make title -->


**Abstract:**
This paper presents the machine translation systems submitted by the Abu-MaTran project for the Finnish–English language pair at the WMT 2015 translation task.
We tackle the lack of resources and complex morphology of the Finnish language by (i) crawling parallel and monolingual data from the Web and (ii) applying rule-based and unsupervised methods for morphological segmentation.
Several statistical machine translation approaches are evaluated and then combined to obtain our final submissions <span style='color: green'>which are ranked amongst the top systems on both automatic and manual evaluation.</span>
<!-- end abstract -->


## Introduction
<a id="section:introduction">(¶ section:introduction)</a>
This paper presents the statistical machine translation (SMT) systems submitted by the Abu-MaTran project for the WMT 2015 translation task. The language pair concerned is Finnish–English with a strong focus on the English-to-Finnish direction. The Finnish language is newly introduced this year as a particular translation challenge due to its rich morphology and to the lack of resources available, compared to e.g. English or French. 

Morphologically rich languages, and especially Finnish, are known to be difficult to translate using phrase-based SMT systems mainly because of the large diversity of word forms leading to data scarcity [(cites: koehn2005europarl)](#koehn2005europarl). We assume that data acquisition and morphological segmentation should contribute to decrease the out-of-vocabulary rate and thus improve the performance of SMT. To gather additional data, we decide to build on previous work conducted in the Abu-MaTran project and crawl the Web looking for monolingual and parallel corpora [(cites: toral2014extrinsic)](#toral2014extrinsic). In addition, morphological segmentation of Finnish is used in our systems as pre- and post-processing steps. Four segmentation methods are proposed in this paper, two unsupervised and two rule-based.

Both constrained and unconstrained translation systems are submitted for the shared task. The former ones are trained on the data provided by the shared task, while the latter ones benefit from crawled data. For both settings, we evaluate the impact of the different SMT approaches and morphological segmentation methods. Finally, the outputs of individually trained systems are combined to obtain our primary submissions for the translation tasks.

This paper is structured as follows: the methods for data acquisition from the Web are described in Section [(see: section:web_crawling)](#section:web_crawling). Morphological segmentation is presented in Section [(see: section:morphological_segmentation)](#section:morphological_segmentation). The data and tools used in our experiments are detailed in Section [(see: section:datasets_and_tools)](#section:datasets_and_tools). Finally, the results of our experiments are shown in Section [(see: section:results)](#section:results), followed by a conclusion in Section [(see: section:conclusion)](#section:conclusion).
## Web Crawling
<a id="section:web_crawling">(¶ section:web_crawling)</a>

In this section we describe the process we followed to collect monolingual and parallel data through Web crawling. Both types of corpora are gathered through one web crawl of the Finnish *.fi* top-level domain (TLD) with the <span style='font-variant: small-caps'>SpiderLing</span> crawler (footnote: <http://nlp.fi.muni.cz/trac/spiderling>) [(cites: suchomel2012efficient)](#suchomel2012efficient). Since the <span style='font-variant: small-caps'>SpiderLing</span> crawler performs language identification during the crawling process, it allows simultaneous multilingual crawling. The whole unconstrained dataset gathered from the Web is built in 40 days using 16 threads. Documents written in Finnish and English are collected during the crawl.

### Monolingual Data
<a id="subsection:monolingual_data">(¶ subsection:monolingual_data)</a>
The amount of Finnish and English data collected during the crawl amounts to, after processing (which includes removing near-duplicates), <span class='math'>5.6M</span> and <span class='math'>3.9M</span> documents, containing <span class='math'>1.7B</span> and <span class='math'>2.0B</span> words for Finnish and English respectively. Interestingly, the amount of Finnish and English data on the Finnish TLD is quite similar. For comparison, on the Croatian domain only 10% of the data is written in English [(cites: ljubesic14-bs)](#ljubesic14-bs). While the Finnish data is used in further steps for building the target-language model, both datasets are used in the task of searching for parallel data described in the next subsection.
### Parallel Data
<a id="subsection:parallel_data">(¶ subsection:parallel_data)</a>
The process of searching for parallel segments among the English and Finnish crawled data is performed by adapting the <span style='font-variant: small-caps'>Bitextor</span> (footnote: <http://sf.net/p/bitextor/>) tool to process already crawled data. <span style='font-variant: small-caps'>Bitextor</span> is a free/open-source tool for harvesting bitexts from multilingual websites. This tool downloads a complete website, processes it, extracts parallel documents and aligns their sentences. In this paper <span style='font-variant: small-caps'>Bitextor</span> is used to detect parallel documents from a collection of downloaded and pre-processed websites. The pre-processing performed by <span style='font-variant: small-caps'>SpiderLing</span> includes language detection, boilerplate removal, and HTML format cleaning. Therefore, the only modules of <span style='font-variant: small-caps'>Bitextor</span> used for this task are those performing document and segment alignment, relying on <span style='font-variant: small-caps'>hunalign</span> (footnote: <http://mokk.bme.hu/resources/hunalign>) [(cites: varga2007parallel)](#varga2007parallel) and an English–Finnish bilingual lexicon. (footnote: <http://sf.net/p/bitextor/files/bitextor/bitextor-4.1/dictionaries/>) Confidence scores for aligned segments are computed thanks to these two resources.

From the <span class='math'>12,183</span> web domains containing both Finnish and English documents, <span style='font-variant: small-caps'>Bitextor</span> is able to identify potentially parallel data on <span class='math'>10,656</span> domains, i.e. <span class='math'>87.5%</span>. From these domains, <span class='math'>2.1M</span> segment pairs are extracted without any additional restrictions, and <span class='math'>1.2M</span> when additional restrictions on the document pairing are set. Namely, these restrictions discard (i) document pairs where less than 5 segments are aligned; and (ii) those with an alignment score lower than <span class='math'>0.2</span> according to <span style='font-variant: small-caps'>hunalign</span>. The first collection can be considered recall-oriented and the second one precision-oriented.

In this first step, a large amount of potentially parallel data is obtained by post-processing data collected with a TLD crawl, which is not primarily aimed at finding parallel data. To make use of this resource in a more efficient way, we re-crawl some of the most promising web sites (we call them *multilingual hotspots*) with the <span style='font-variant: small-caps'>ILSP-FC</span> crawler specialised in locating parallel documents during crawling. According to [(cites: espla14-comparing)](#espla14-comparing), <span style='font-variant: small-caps'>Bitextor</span> and <span style='font-variant: small-caps'>ILSP-FC</span> have shown to be complementary, and combining both tools leads to a larger amount of parallel data.

<span style='font-variant: small-caps'>ILSP-FC</span> [(cites: papavassiliou-prokopidis-thurmair:2013:BUCC)](#papavassiliou-prokopidis-thurmair:2013:BUCC) is an open-source modular crawling system allowing to easily acquire domain-specific and generic corpora from the Web. (footnote: <http://nlp.ilsp.gr/redmine/projects/ilsp-fc>)
The modules integrated in <span style='font-variant: small-caps'>ILSP-FC</span> include a de-duplicator that checks each document against all others and identifies near-duplicates by comparing the quantised word frequencies and the paragraphs of each pair of candidate duplicate documents and a pair detector that examines each document against all others and identifies pairs of documents that could be considered parallel. The main methods used by the pair detector are URL similarity, co-occurrences of images with the same filename in two documents, and the documents’ structural similarity.

In order to identify the *multilingual hotspots*, we process the output of the Finnish TLD and generate a list containing the websites which have already been crawled and the number of stored English and Finnish webpages for each website. Assuming that a website with comparable numbers of webpages for each language is likely to contain bitexts of good quality, we keep the websites with Finnish to English ratio over 0.9. Then, <span style='font-variant: small-caps'>ILSP-FC</span> processes the <span class='math'>1,000</span> largest such websites, considered the most bitext-productive multilingual websites, in order to detect parallel documents. We identify a total of <span class='math'>58,839</span> document pairs (<span class='math'>8,936</span>, <span class='math'>17,288</span> and <span class='math'>32,615</span> based on URL similarity, co-occurrences of images and structural similarity, respectively). Finally, <span style='font-variant: small-caps'>Hunalign</span> is applied on these document pairs, resulting in <span class='math'>1.2M</span> segment pairs after duplicate removal.

The parallel corpus used in our experiments is the result of joining the biggest corpora acquired by <span style='font-variant: small-caps'>Bitextor</span> and <span style='font-variant: small-caps'>ILSP-FC</span> and removing duplicates.
This amounts to <span class='math'>2.8M</span> segment pairs.



## Morphological Segmentation
<a id="section:morphological_segmentation">(¶ section:morphological_segmentation)</a>

Morphological segmentation is a method of analysis of word-forms in order to reduce morphological complexity. There are few variations on how to define morphological segmentation, we use the most simple definition: a morphological segmentation of a word is defined by 0 or more segmentation points from where the word can be split into segments. The letter sequences between segmentation points are not modified, i.e. no lemmatisation or segment analysis is performed (or retained) in the actual SMT data.
An example of a linguistically derived morphological segmentation of an English word-form *cats* would be `cat<span class='math'>→</span> <span class='math'>←</span>s`, where <span class='math'>→</span> <span class='math'>←</span> denotes the segmentation point, (footnote: we follow this arrow notation throughout the paper as well as in the actual implementation) and `cat` and `s` are the segments.


We use four segmentation approaches that can be divided in two categories: (i) rule-based, based on morphological dictionaries and weighted finite-state technology <span style='font-variant: small-caps'>HFST</span> [(cites: hfst)](#hfst) (footnote: <http://hfst.sf.net>), further detailed in subsection [(see: subsection:rule_based)](#subsection:rule_based), and (ii) statistical, based on unsupervised learning of morphologies, further detailed in subsection [(see: subsection:unsupervised)](#subsection:unsupervised). All segments are used as described in subsection [(see: subsection:segments_pipeline)](#subsection:segments_pipeline).

### Rule-based Segmentation
<a id="subsection:rule_based">(¶ subsection:rule_based)</a>
Rule-based morphological segmentation is based on linguistically motivated computational descriptions of the morphology by dividing the word-forms into *morphs* (minimal segments carrying semantic or syntactic meaning). The rule-based approach to morphological segmentation uses a morphological dictionary of words and an implementation of the morphological grammar to analyse word-forms. In our case, we use <span style='font-variant: small-caps'>omorfi</span> [(cites: pirinen2015omorfi)](#pirinen2015omorfi), an open-source implementation of the Finnish morphology. (footnote: <http://github.com/flammie/omorfi/>) <span style='font-variant: small-caps'>omorfi</span>’s segmentation produces named segment boundaries: stem, inflection, derivation, compound-word and other etymological. The two variants of rule-based segmentation we use are based on selection of the boundary points: *compound segmentation* uses compound segments and discards the rest (referred in tables and figures to as `HFST Comp`), and *morph segmentation* uses compound and inflectional morph segments (`HFST Morph` in tables and figures). In cases of ambiguous segments, the weighted finite-state automata 1-best search is used with default weights. (footnote: For details of implementation and reproducibility, the code is available in form of automake scriptlets at <http://github.com/flammie/autostuff-moses-smt/>.) For example, the words *kuntaliitoksen selvitt\"amisess\"a* (“examining annexation”) is segmented by `hfst-comp` as ‘kunta<span class='math'>→ ←</span>liitoksen selvitt\"amisess\"a’ and `hfst-morph` as ‘kunta<span class='math'>→ ←</span>liitokse<span class='math'>→ ←</span>n selvitt\"amise<span class='math'>→ ←</span>ss\"a’.

### Unsupervised Segmentation
<a id="subsection:unsupervised">(¶ subsection:unsupervised)</a>
Unsupervised morphological segmentation is based on a statistical model trained by minimising the number of different character sequences observed in a training corpus. We use two different algorithms: <span style='font-variant: small-caps'>Morfessor</span> Baseline 2.0 [(cites: morfessor)](#morfessor) and <span style='font-variant: small-caps'>Flatcat</span> [(cites: flatcat)](#flatcat).
The segmentation models are trained using the Europarl v8 corpus. Both systems are used with default settings. However, with <span style='font-variant: small-caps'>Flatcat</span> we discard the non-morph boundaries and we have not used semi-supervised features.
For example, the phrase given in previous sub-section:  `morfessor` produces 1-best segmentation: and ‘Kun<span class='math'>→ ←</span>ta<span class='math'>→ ←</span>liito<span class='math'>→ ←</span>ksen selvitt\"a<span class='math'>→ ←</span>misess\"a’ and `flatcat` ‘Kun<span class='math'>→ ←</span>tali<span class='math'>→ ←</span>itoksen selvitt\"amis<span class='math'>→ ←</span>ess\"a’

### Segments in the SMT Pipeline
<a id="subsection:segments_pipeline">(¶ subsection:segments_pipeline)</a>
The segmented data is used exactly as the word-form-based data during training, tuning and testing of the SMT systems, (footnote: The parameters of the word alignment, phrase extraction and decoding algorithms have not been modified to take into account the nature of the segmented data.) except during the pre-processing and post-processing steps.
For pre-processing, the Finnish side is segmented prior to use. 
In segmented-Finnish-to-English the post-processing was performed by removing the boundary markers. In English-to-segmented-Finnish translation, there are basically two types of tokens with boundary markers: *matching* arrows `a<span class='math'>→</span> <span class='math'>←</span>b` and *stray* arrows `a<span class='math'>→</span> x` or `x <span class='math'>←</span>b`. In the former case, we replace `<span class='math'>→</span> <span class='math'>←</span>` with an empty string to join the morphs. In the latter case, we delete the morphs with the stray arrows.

## Datasets and Tools
<a id="section:datasets_and_tools">(¶ section:datasets_and_tools)</a>
This section presents the tools and the monolingual and parallel data used to train our SMT systems. All the corpora are pre-processed prior to training the language and translation models. We rely on the scripts included in the <span style='font-variant: small-caps'>Moses</span> toolkit [(cites: koehn2007moses)](#koehn2007moses) and perform the following operations: punctuation normalisation, tokenisation, true-casing and escaping of problematic characters. The truecaser is lexicon-based, trained on all the monolingual and parallel data. In addition, we remove sentence pairs from the parallel corpora where either side is longer than <span class='math'>80</span> tokens.

### Translation Models
<a id="subsection:translation_model">(¶ subsection:translation_model)</a>
Previous studies in MT involving Finnish do not show a clear advantage of one particular approach compared to another, and thus we decide to empirically evaluate several types of SMT systems: phrase-based SMT [(cites: och2004alignment)](#och2004alignment) trained on word forms or morphs as described in Section [(see: section:morphological_segmentation)](#section:morphological_segmentation), Factored Models [(cites: koehn2007factored)](#koehn2007factored) including morphological and suffix information as provided by <span style='font-variant: small-caps'>omorfi</span>, (footnote: using the script `omorfi-factorise.py`) in addition to surface forms, and finally hierarchical phrase-based SMT [(cites: chiang2005hierarchical)](#chiang2005hierarchical) as an unsupervised tree-based model. All the systems are trained with <span style='font-variant: small-caps'>Moses</span>, relying on <span style='font-variant: small-caps'>MGIZA</span> [(cites: gao2008parallel)](#gao2008parallel) for word alignment
and MIRA [(cites: watanabe-EtAl:2007:EMNLP-CoNLL2007)](#watanabe-EtAl:2007:EMNLP-CoNLL2007) for tuning. This tuning algorithm was shown to be faster and as efficient as MERT for model core features, as well as a better stability with larger numbers of features [(cites: hasler2011margin)](#hasler2011margin).

In order to compare the individually trained SMT systems, we use the same parallel data for each model, as well as the provided development set to tune the systems. The phrase-based SMT system is augmented with additional features: an Operation Sequence Model (OSM) [(cites: durrani2011joint)](#durrani2011joint) and a Bilingual Neural Language Model (BiNLM) [(cites: devlin2014binlm)](#devlin2014binlm), both trained on the parallel data used to learn the phrase-table. All the translation systems also benefit from two additional reordering models, namely a phrase-based model with three different orientations (monotone, swap and discontinuous) and a hierarchical model with four orientations (non merged discontinuous left and right orientations), both trained in a bidirectional way [(cites: koehn2005edinburgh,galley2008simple)](#koehn2005edinburgh,galley2008simple).


**Figure:**
<!-- centering -->
![figures/uniqtokens.pdf](figures/uniqtokens.pdf)
(Caption: Effects of segmentation to unique token counts in Finnish data.
	<a id="figure:segmentation_effects">(¶ figure:segmentation_effects)</a>
	)
<!-- end figure -->

Our constrained systems are trained on the data available for the shared task, while unconstrained systems are trained with two additional sets of parallel data, the <span style='font-variant: small-caps'>FiEnWaC</span> crawled dataset (cf. Section  [(see: subsection:parallel_data)](#subsection:parallel_data))
and Open Subtitles, henceforth <span style='font-variant: small-caps'>osubs</span>. (footnote: <http://opus.lingfil.uu.se/>) The details about the corpora used to train the translation models are presented in Table [(see: table:data_tm)](#table:data_tm).  Figure [(see: figure:segmentation_effects)](#figure:segmentation_effects) shows how different segmentation methods affect the vocabulary size; given that linguistic segmentation have larger vocabularies as statistical their contribution to translation models may be at least partially complementary.


**Table:**
	\center{
<!-- small -->{
	

|  |   |  | <!-- FIXME: multicolumn 2 c -->{Words (M)} |
| Corpus  |  Sentences (k)  |  Finnish  |  English|
| ---- | ---- | ---- | ---- |
|  |  | <!-- FIXME: multicolumn 3 c -->{*Constrained System*} |
| Europarl v8  |  1,901.1  |  36.5  |  50.9 |
|  |  | <!-- FIXME: multicolumn 3 c -->{*Unconstrained System*} |
| fienwac.in   |  640.1  |  9.2  |  13.6 |
| fienwac.outt  |  838.9  |  12.5  |  18.1 |
| fienwac.outb  |  838.9  |  13.9  |  18.1 |
| osubs.in  |  492.2  |  3.6  |  5.6 |
| osubs.outt  |  1,169.6  |  8.8  |  14.4 |
| osubs.outb  |  1,169.6  |  7.8  |  13.0 |

(Caption: Parallel data used to train the translation models, after pre-processing.)
	<a id="table:data_tm">(¶ table:data_tm)</a>
	}}
<!-- end table -->

The two unconstrained parallel datasets are split into three subsets: pseudo in-domain, pseudo out-of-domain top and pseudo out-of-domain bottom, henceforth `in`, `outt` and `outb`.
We rank the sentence pairs according to bilingual cross-entropy difference on the devset [(cites: axelrod2011domain)](#axelrod2011domain) and calculate the perplexity on the devset of LMs trained on different portions of the top ranked sentences (the top 1/64, 1/32 and so on).
The subset for which we obtain the lowest perplexities is kept as `in` (this was 1/4 for `fienwac` (403.89 and 3610.95 for English and Finnish, respectively), and 1/16 for `osubs` (702.45 and 7032.2).
The remaining part of each dataset is split in two sequential parts in ranking order of same number of lines, which are kept as `outt` and `outb`.

The out-of-domain part of `osubs` is further processed with vocabulary saturation [(cites: lewis2013dramatically)](#lewis2013dramatically) in order to have a more efficient and compact system [(cites: rubino-EtAl:2014:W14-33)](#rubino-EtAl:2014:W14-33).
We traverse the sentence pairs in the order they are ranked and filter out those for which we have seen already each 1-gram at least 10 times.
This results in a reduction of 3.2x on the number of sentence pairs (from <span class='math'>7.3M</span> to <span class='math'>2.3M</span>) and 2.6x on the number of words (from <span class='math'>114M</span> to <span class='math'>44M</span>).

The resulting parallel datasets (<span class='math'>7</span> in total: Europarl and 3 sets for each `fienwac` and `osubs`) are used individually to train translation and reordering models before being combined by linear interpolation based on perplexity minimisation on the development set. [(cites: sennrich2012perplexity)](#sennrich2012perplexity)
### Language Models
<a id="subsection:language_model">(¶ subsection:language_model)</a>
All the Language Models (LM) used in our experiments are <span class='math'>5</span>-grams modified Kneser-Ney smoothed LMs trained using KenLM [(cites: heafield2013estimate)](#heafield2013estimate). For the constrained setup, the Finnish and the English LMs are trained following two different approaches. The English LM is trained on the concatenation of all available corpora while the Finnish LM is obtained by linearly interpolating individually trained LMs based on each corpus. The weights given to each individual LM is calculated by minimising the perplexity obtained on the development set. For the unconstrained setup, the Finnish LM is trained on the concatenation of all constrained data plus the additional monolingual crawled corpora (noted *FiWaC*). The data used to train the English and Finnish LMs are presented in Table [(see: table:data_en_lm)](#table:data_en_lm) and Table [(see: table:data_fi_lm)](#table:data_fi_lm) respectively.


**Table:**
	\center{
<!-- small -->{
	

| Corpus  |  Sentences (k)  |  Words (M) |
| ---- | ---- | ---- |
| Europarl v8  |  2,218.2  |  59.9 | 		News Commentary v10  |  344.9  |  8.6 |
| <!-- FIXME: multicolumn 3 l -->{News Shuffled} |
| 2007  |  3\,782.5  |  90.2 |
| 2008  |  12\,954.5  |  308.1 |
| 2009  |  14\,680.0  |  347.0 |
| 2010  |  6\,797.2  |  157.8 |
| 2011  |  15\,437.7  |  358.1 |
| 2012  |  14\,869.7  |  345.5 |
| 2013  |  21\,688.4  |  495.2 |
| 2014  |  28\,221.3  |  636.6 |
| Gigaword 5th  |  28,178.1  |  4,831.5 |

(Caption: English monolingual data, after pre-processing, used to train the constrained language model.)
	<a id="table:data_en_lm">(¶ table:data_en_lm)</a>
	}}
<!-- end table -->


**Table:**
	\center{
<!-- small -->{
	

| Corpus  |  Sentences (k)  |  Words (M) |
| ---- | ---- | ---- |
| | <!-- FIXME: multicolumn 3 c -->{*Constrained System*} | 		News Shuffle 2014  |  1,378.8  |  16.5 |
| <!-- FIXME: multicolumn 3 c -->{*Unconstrained System*} |
| FiWaC  |  146,557.4  |  1,996.3 |

(Caption: Finnish monolingual data, after pre-processing, used to train the language models.)
	<a id="table:data_fi_lm">(¶ table:data_fi_lm)</a>
	}}
<!-- end table -->







## Results
<a id="section:results">(¶ section:results)</a>
In this section we present the results obtained for the constrained and unconstrained tasks.
We tackled the English-to-Finnish direction in the unconstrained task, while both directions are presented for the constrained task. The diversity of the translation systems and morphological segmentation approaches motivates the combination of the individual translation outputs. We assume that they have complementary strengths and we perform system combination using MEMT [(cites: heafield2010combining)](#heafield2010combining). Default settings are used, except for the beam size (set to <span class='math'>1,500</span>) and radius (5 for Finnish and 7 for English), following empirical results obtained on the development set.
### Constrained Results
<a id="section:constrained_results">(¶ section:constrained_results)</a>

Individual systems trained on the provided data are evaluated before being combined. The results obtained for the English-to-Finnish direction are presented in Table [(see: table:constrained_results_enfi)](#table:constrained_results_enfi). (footnote: We use NIST mteval v13 and TERp v0.1, both with default parameters.) The <span style='font-variant: small-caps'>BLEU</span> [(cites: papineni2002bleu)](#papineni2002bleu) and <span style='font-variant: small-caps'>TER</span> [(cites: snover2006study)](#snover2006study) scores obtained by the system trained on compound-segmented data (*HFST Comp*) show a positive impact of this method on SMT according to the development set, compared to the other individual systems. The unsupervised segmentation methods do not improve over phrase-based SMT, while the hierarchical model shows an interesting reduction of the <span style='font-variant: small-caps'>TER</span> score compared to a classic phrase-based approach. On the test set, the use of inflectional morph segments as well as compounds (*HFST Morph*) leads to the best results for the individual systems on both evaluation metrics. The combination of these <span class='math'>7</span> systems improves substantially over the best individual system for the development and the test sets. 

**Table:**
	\center{
<!-- small -->{
	

|  |  | <!-- FIXME: multicolumn 2 c -->{Dev}  |  | <!-- FIXME: multicolumn 2 c -->{Test} |
| System  |  BLEU  |  TER  |  BLEU  |  TER |
| ---- | ---- | ---- | ---- | ---- |
| Phrase-Based  |  13.51  |  0.827  |  12.33  |  0.843 |
| Factored Model  |  13.08  |  0.827  |  11.89  |  0.847 |
| Hierarchical  |  13.05  |  0.822  |  12.11 |  0.830 |
| HFST Comp  |  {<!-- bf -->13.57}  |  {\bf0.814}  |  12.66  |  0.828 |
| HFST Morph  |  13.19  |  0.818  |  {\bf12.77}  |  {\bf0.819} |
| Morfessor  |  12.21  |  0.860  |  11.58  |  0.864 |
| Flatcat  |  12.67  |  0.844  |  12.05  |  0.849 |
| Combination  |  14.61  |  0.786  |  13.54  |  0.801 |

(Caption: Results obtained on the development and test sets for the constrained English-to-Finnish translation task. Best individual system in bold.)
	<a id="table:constrained_results_enfi">(¶ table:constrained_results_enfi)</a>
	}}
<!-- end table -->

The results for the other translation direction (Finnish to English) are shown in Table [(see: table:constrained_results_fien)](#table:constrained_results_fien) and follow the same trend as observed with Finnish as target: the morphologically segmented data helps improving over classic SMT approaches. The two metrics indicate better performances of *HFST Morph* on the development set, while *Flatcat* reaches the best scores on the test set. The results obtained with the segmented data on the two translation directions and the different segmentation approaches are fluctuating and do not indicate which method is the best.
Again, the combination of all the systems results in a substantial improvement over the best individual system across both evaluation metrics.


**Table:**
	\center{
<!-- small -->{
	

|  |  | <!-- FIXME: multicolumn 2 c -->{Dev}  |  | <!-- FIXME: multicolumn 2 c -->{Test} |
| System  |  BLEU  |  TER  |  BLEU  |  TER |
| ---- | ---- | ---- | ---- | ---- |
| Phrase-Based  |  17.19  |  0.762  |  16.90  |  0.759 |
| Hierarchical  |  16.98  |  0.768  |  15.93  |  0.773 |
| HFST Comp  |  17.87  |  0.748  |  16.68  |  0.753 |
| HFST Morph  |  {\bf18.64}  |  {\bf0.735}  |  17.22  |  0.752 |
| Morfessor  |  16.83  |  0.769  |  15.96  |  0.756 |
| Flatcat  |  16.78  |  0.766  |  {\bf17.33}  |  {\bf0.741} |
| Combination  |  19.66  |  0.719  |  18.77  |  0.726 |

(Caption: Results obtained on the development and test sets for the constrained Finnish-to-English translation task.  Best individual system in bold.)
	<a id="table:constrained_results_fien">(¶ table:constrained_results_fien)</a>
	}}
<!-- end table -->
### Unconstrained Results
<a id="section:constrained_results_fien">(¶ section:constrained_results_fien)</a>

We present the results obtained on the unconstrained English-to-Finnish translation task in Table [(see: table:unconstrained_results_enfi)](#table:unconstrained_results_enfi). Two individual systems are evaluated, using word-forms and compound-based data, and show that the segmented data leads to lower TER scores, while higher BLEU are reached by the word-based system.
The combination of these two systems in addition to the constrained outputs of the remaining systems (hierarchical, factored model, HFST Morph, Morfessor and Flatcat) is evaluated in the last row of the table, and shows <span class='math'>.3</span>pt BLEU gain on the test set over the phrase-based approach using word forms.


**Table:**
	\center{
<!-- small -->{
	

|  |  | <!-- FIXME: multicolumn 2 c -->{Dev}  |  | <!-- FIXME: multicolumn 2 c -->{Test} |
| System  |  BLEU  |  TER  |  BLEU  |  TER |
| ---- | ---- | ---- | ---- | ---- |
| Phrase-Based  |  {\bf16.16}  |  0.804  |  {\bf16.07}  |  0.801 |
| HFST Comp  |  15.80  |  {\bf0.796}  |  15.06  |  {\bf0.800} |
| Combination  |  17.25  |  0.776  |  16.38  |  0.779 |

(Caption: Results obtained on the development and test sets for the unconstrained English-to-Finnish translation task. Best individual system in bold.)
	<a id="table:unconstrained_results_enfi">(¶ table:unconstrained_results_enfi)</a>
	}}
<!-- end table -->
## Conclusion
<a id="section:conclusion">(¶ section:conclusion)</a>
Our participation in WMT15’s translation task has focused on investigating the use of several morphological segmentation methods and Web data acquisition in order to handle the data scarcity and the rich morphology of Finnish. In addition, we have evaluated several SMT approaches.
Our submission is based on the system combination of SMT systems following different approaches and using different types of morphological segmentation.

Automatic evaluation metrics show the usefulness of morphological segmentation, especially of the rule-based methods, <span style='color: blue'>which lead to a reduction of the vocabulary size and, in most cases, also to better performance, compared to an equivalent SMT system that operates on word forms</span>.
The best results are obtained with the system combination approach. The acquisition of additional training data improves over the constrained systems and is a successful example of the Abu-MaTran crawling pipeline.

## Acknowledgments
The research leading to these results has received funding from the European Union Seventh Framework Programme FP7/2007-2013 under grant agreement PIAP-GA-2012-324414 (Abu-MaTran).
We would like to thank Kenneth Heafield for his help to our questions re MEMT.
<!-- bib style: unsrt -->
# References

* <a id="koehn2005europarl">**koehn2005europarl**</a>:
    * title: {Europarl: A Parallel Corpus for Statistical Machine Transla...
    * author: Koehn, Philipp
    * booktitle: MT summit
    * volume: 5
    * pages: 79–86
    * year: 2005
* <a id="toral2014extrinsic">**toral2014extrinsic**</a>:
    * title: Extrinsic Evaluation of Web-Crawlers in Machine Translation:...
    * author: Toral, Antonio and Rubino, Raphael and Esplà-Gomis, Miquel a...
    * booktitle: Proceedings of EAMT
    * pages: 221–224
    * year: 2014
* <a id="suchomel2012efficient">**suchomel2012efficient**</a>:
    * title: Efficient web crawling for large text corpora
    * author: Suchomel, Vít and Pomikálek, Jan
    * booktitle: Proceedings of the 7th Web as Corpus Workshop
    * series: {WAC7}
    * pages: 39–43
    * address: Lyon, France
    * year: 2012
* <a id="ljubesic14-bs">**ljubesic14-bs**</a>:
    * Address: Gothenburg, Sweden
    * Author: Nikola Ljubešić and Filip Klubička
    * Booktitle: Proceedings of the 9th Web as Corpus Workshop (WaC-9)
    * Pages: 29–35
    * Publisher: Association for Computational Linguistics
    * Title: 
{bs,hr,sr
}{WaC} – Web corpora of Bosnian, Croatian and ...
    * Year: 2014
* <a id="varga2007parallel">**varga2007parallel**</a>:
    * title: Parallel corpora for medium density languages
    * author: Varga, Dániel and Németh, László and Halácsy, Péter and Korn...
    * booktitle: Recent Advances in Natural Language Processing
    * address: Borovets, Bulgaria
    * pages: 590–596
    * year: 2005
* <a id="espla14-comparing">**espla14-comparing**</a>:
    * Address: Reykjavik, Iceland
    * Author: Miquel Esplà-Gomis and Filip Klubička and Nikola Ljubešić an...
    * Booktitle: Proceedings of the 9th International Conference on Language ...
    * series: LREC’14
    * Title: Comparing Two Acquisition Systems for Automatically Building...
    * Year: 2014
* <a id="papavassiliou-prokopidis-thurmair:2013:BUCC">**papavassiliou-prokopidis-thurmair:2013:BUCC**</a>:
    * author: Papavassiliou, Vassilis and Prokopidis, Prokopis and Gregor ...
    * address: Sofia, Bulgaria
    * booktitle: Proceedings of the Sixth Workshop on Building and Using Comp...
    * month: August
    * pages: 43–51
    * publisher: Association for Computational Linguistics
    * title: A modular open-source focused crawler for mining monolingual...
    * url: http://www.aclweb.org/anthology/W13-2506.pdf
    * year: 2013
* <a id="hfst">**hfst**</a>:
    * title: HFST tools for morphology–an efficient open-source package ...
    * author: Lindén, Krister and Silfverberg, Miikka and Pirinen, Tommi
    * booktitle: State of the Art in Computational Morphology
    * pages: 28–47
    * year: 2009
    * publisher: Springer
* <a id="pirinen2015omorfi">**pirinen2015omorfi**</a>:
    * title: Omorfi—Free and open source morphological lexical database f...
    * author: Pirinen, Tommi A
    * booktitle: Nordic Conference of Computational Linguistics NODALIDA 2015
    * pages: 313–317
    * year: 2015
* <a id="morfessor">**morfessor**</a>:
    * crossref: virpioja2013morfessor
* <a id="flatcat">**flatcat**</a>:
    * crossref: gronroos2014morfessor
* <a id="koehn2007moses">**koehn2007moses**</a>:
    * title: {Moses: Open Source Toolkit for Statistical Machine Translat...
    * author: Koehn, Philipp and Hoang, Hieu and Birch, Alexandra and Call...
    * booktitle: Proceedings of ACL
    * pages: 177–180
    * year: 2007
* <a id="och2004alignment">**och2004alignment**</a>:
    * title: {The Alignment Template Approach to Statistical Machine Tran...
    * author: Och, Franz Josef and Ney, Hermann
    * journal: Computational linguistics
    * volume: 30
    * number: 4
    * pages: 417–449
    * year: 2004
    * publisher: MIT press
* <a id="koehn2007factored">**koehn2007factored**</a>:
    * title: {Factored Translation Models}
    * author: Koehn, Philipp and Hoang, Hieu
    * booktitle: Proceedings of EMNLP-CoNLL
    * pages: 868–876
    * year: 2007
* <a id="chiang2005hierarchical">**chiang2005hierarchical**</a>:
    * title: {A Hierarchical Phrase-based Model for Statistical Machine T...
    * author: Chiang, David
    * booktitle: Proceedings of ACL
    * pages: 263–270
    * year: 2005
* <a id="gao2008parallel">**gao2008parallel**</a>:
    * title: {Parallel Implementations of Word Alignment Tool}
    * author: Gao, Qin and Vogel, Stephan
    * booktitle: Software Engineering, Testing, and Quality Assurance for Nat...
    * pages: 49–57
    * year: 2008
* <a id="watanabe-EtAl:2007:EMNLP-CoNLL2007">**watanabe-EtAl:2007:EMNLP-CoNLL2007**</a>:
    * author: Watanabe, Taro and Suzuki, Jun and Tsukada, Hajime and Isoza...
    * title: Online Large-Margin Training for Statistical Machine Transla...
    * booktitle: Proceedings of the 2007 Joint Conference on Empirical Method...
    * month: June
    * year: 2007
    * address: Prague, Czech Republic
    * publisher: Association for Computational Linguistics
    * pages: 764–773
    * url: http://www.aclweb.org/anthology/D07-1080
* <a id="hasler2011margin">**hasler2011margin**</a>:
    * title: {Margin Infused Relaxed Algorithm for Moses}
    * author: Hasler, Eva and Haddow, Barry and Koehn, Philipp
    * journal: The Prague Bulletin of Mathematical Linguistics
    * volume: 96
    * pages: 69–78
    * year: 2011
* <a id="durrani2011joint">**durrani2011joint**</a>:
    * title: {A Joint Sequence Translation Model with Integrated Reorderi...
    * author: Durrani, Nadir and Schmid, Helmut and Fraser, Alexander
    * booktitle: Proceedings of ACL/HLT
    * pages: 1045–1054
    * year: 2011
* <a id="devlin2014binlm">**devlin2014binlm**</a>:
    * author: Devlin, Jacob  and  Zbib, Rabih  and  Huang, Zhongqiang  and...
    * title: {Fast and Robust Neural Network Joint Models for Statistical...
    * booktitle: Proceedings of ACL
    * year: 2014
    * pages: 1370–1380
* <a id="koehn2005edinburgh">**koehn2005edinburgh**</a>:
    * title: Edinburgh system description for the 2005 IWSLT speech trans...
    * author: Koehn, Philipp and Axelrod, Amittai and Birch, Alexandra and...
    * booktitle: IWSLT
    * pages: 68–75
    * year: 2005
* <a id="galley2008simple">**galley2008simple**</a>:
    * title: A simple and effective hierarchical phrase reordering model
    * author: Galley, Michel and Manning, Christopher D
    * booktitle: Proceedings of the Conference on Empirical Methods in Natura...
    * pages: 848–856
    * year: 2008
    * organization: Association for Computational Linguistics
* <a id="axelrod2011domain">**axelrod2011domain**</a>:
    * title: Domain adaptation via pseudo in-domain data selection
    * author: Axelrod, Amittai and He, Xiaodong and Gao, Jianfeng
    * booktitle: Proceedings of the Conference on Empirical Methods in Natura...
    * pages: 355–362
    * year: 2011
    * organization: Association for Computational Linguistics
* <a id="lewis2013dramatically">**lewis2013dramatically**</a>:
    * title: Dramatically reducing training data size through vocabulary ...
    * author: Lewis, William D and Eetemadi, Sauleh
    * booktitle: Proceedings of the Eighth Workshop on Statistical Machine Tr...
    * pages: 281–291
    * year: 2013
* <a id="rubino-EtAl:2014:W14-33">**rubino-EtAl:2014:W14-33**</a>:
    * author: Rubino, Raphael  and  Toral, Antonio  and  S
’{a}nchez-Cart...
    * title: Abu-MaTran at WMT 2014 Translation Task: Two-step Data Selec...
    * booktitle: Proceedings of the Ninth Workshop on Statistical Machine Tra...
    * month: June
    * year: 2014
    * address: Baltimore, Maryland, USA
    * publisher: Association for Computational Linguistics
    * pages: 171–177
    * url: http://www.aclweb.org/anthology/W/W14/W14-3319
* <a id="sennrich2012perplexity">**sennrich2012perplexity**</a>:
    * title: Perplexity minimization for translation model domain adaptat...
    * author: Sennrich, Rico
    * booktitle: Proceedings of the 13th Conference of the European Chapter o...
    * pages: 539–549
    * year: 2012
    * organization: Association for Computational Linguistics
* <a id="heafield2013estimate">**heafield2013estimate**</a>:
    * title: {Scalable Modified Kneser-Ney Language Model Estimation}
    * author: Kenneth Heafield and Ivan Pouzyrevsky and Jonathan H. Clark ...
    * year: 2013
    * booktitle: Proceedings of ACL
    * pages: 690–696
* <a id="heafield2010combining">**heafield2010combining**</a>:
    * title: Combining Machine Translation Output with Open Source: The C...
    * author: Heafield, Kenneth and Lavie, Alon
    * journal: The Prague Bulletin of Mathematical Linguistics
    * volume: 93
    * pages: 27–36
    * year: 2010
* <a id="papineni2002bleu">**papineni2002bleu**</a>:
    * author: Papineni, Kishore and Roukos, Salim and Ward, Todd and Zhu, ...
    * title: {BLEU: A Method for Automatic Evaluation of Machine Translat...
    * booktitle: Proceedings of ACL
    * year: 2002
    * pages: 311–318
* <a id="snover2006study">**snover2006study**</a>:
    * title: {A Study of Translation Edit Rate with Targeted Human Annota...
    * author: Snover, Matthew and Dorr, Bonnie and Schwartz, Richard and M...
    * booktitle: Proceedings of AMTA
    * pages: 223–231
    * year: 2006

<!-- end document -->




* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

