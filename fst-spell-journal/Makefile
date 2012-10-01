## Use make to create article pdfs or recreate test results

TEX=xelatex
BIB=bibtex
SCP=scp
SCPHOST=ruuvi
SCPDIR=public_html/tmp/
WGET=wget
BZ2CAT=bzcat
SED=sed
AWK=awk
WIKICLEAN=./wikipedia-deform.sh
HFST_COMPOSE=hfst-compose
HFST_CONCATENATE=hfst-concatenate
HFST_FST2FST=hfst-fst2fst
HFST_INVERT=hfst-invert
HFST_MINIMIZE=hfst-minimize
HFST_REGEXP2FST=hfst-regexp2fst
HFST_REPEAT=hfst-repeat
HFST_REWEIGHT=hfst-reweight
HFST_STRINGS2FST=hfst-strings2fst
HFST_TXT2FST=hfst-txt2fst
HFST_UNION=hfst-disjunct
HFST_PROC=hfst-proc
HFST_OSPELL=hfst-ospell-survey
HFST_LOOKUP=hfst-lookup
PYTHON2=python2
PYTHON3=python3
EDITDIST=editdist.py
ASPELL=aspell
HUNSPELL=hunspell
# use GNU time rather than bash builtin
TIME=/usr/bin/time

PAPER_SOURCES=fst-spell-2012.tex
PAPER_AUXES=fst-spell-2012.aux fst-spell-2012.bbl fst-spell-2012.log fst-spell-2012.blg
PAPER_PDF=fst-spell-2012.pdf
GRAPHICX=graphicx/xy-edit1.pdf graphicx/soundex.pdf
DOTS=dots/xy-edit1.dot dots/soundex.dot

DOCS=README LICENCE

fst-spell-2012.pdf: fst-spell-2012.tex fstspell2012.bib $(GRAPHICX)
	$(TEX) fst-spell-2012.tex
	$(BIB) fst-spell-2012
	$(TEX) fst-spell-2012.tex
	$(TEX) fst-spell-2012.tex
	$(TEX) fst-spell-2012.tex

clean-article:
	-rm -f $(PAPER_PDF) $(PAPER_AUXES)

clean: clean-article

dots/%.dot: hfst/und/%.hfst
	hfst-fst2txt -v -f dot -i $< -o $@

graphicx/%.pdf: dots/%.dot
	dot -Tpdf -o$@ $<

# language settings
PROFILE_FOR_EXPR=1 2 3 4 5

TEST_CORPUS_HUGE=20000000
TEST_CORPUS_LARGE=1000000
TEST_CORPUS_TINY=10000

EN_ALPHABET=abcdefghijklmnopqrstuvwxzyABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\'-
FI_ALPHABET=abcdefghijklmnopqršstuwvxyzžåäöABCDEFGHIJKLMNOPQRSŠTUWVXYZŽÅÄÖ0123456789\'-

HUNSPELL_EN_AFF=en_US.aff
EN_TEST_CORPUS=corp/en/wikipedia-test.txt


EN_TEST_SORTS_HUGE=corp/en/wikipedia-test.$(TEST_CORPUS_HUGE).sorted
EN_TEST_SORTS_LARGE=corp/en/wikipedia-test.$(TEST_CORPUS_LARGE).sorted
EN_TEST_SORTS_TINY=corp/en/wikipedia-test.$(TEST_CORPUS_TINY).sorted
EN_TEST_SORTS_ONE=corp/en/wikipedia-test.1.sorted
EN_TEST_WORDS_HUGE=corp/en/wikipedia-test.$(TEST_CORPUS_HUGE).words
EN_TEST_WORDS_LARGE=corp/en/wikipedia-test.$(TEST_CORPUS_LARGE).words
EN_TEST_WORDS_TINY=corp/en/wikipedia-test.$(TEST_CORPUS_TINY).words
EN_TEST_WORDS_ONE=corp/en/wikipedia-test.1.words
EN_TEST_NONWORDS_LARGE=corp/en/wikipedia-test.$(TEST_CORPUS_LARGE).nonwords
EN_TEST_NONWORDS_TINY=corp/en/wikipedia-test.$(TEST_CORPUS_TINY).nonwords
EN_TEST_NONWORDS_ONE=corp/en/wikipedia-test.1.nonwords
EN_TEST_WORDS_REAL=corp/en/wikispells.tsv

DICT_EN_CORP=hfst/en/acceptor.corpuswg.hfst
DICT_EN_NORV=hfst/en/acceptor.norvigxx.hfst

DICT_FI_CORP=hfst/fi/acceptor.corpuswg.hfst
DICT_FI_NOPD=hfst/fi/acceptor.gtfinopd.hfst
DICT_FI_PROD=hfst/fi/acceptor.gtfiprod.hfst

DICT_SE_CORP=hfst/se/acceptor.corpuswg.hfst
DICT_SE_NOPD=hfst/se/acceptor.gtsenopd.hfst
DICT_SE_PROD=hfst/se/acceptor.gtseprod.hfst

DICT_KL_NOPD=hfst/kl/acceptor.gtklnopd.hfst

DICTIONARIES=$(DICT_EN_CORP) $(DICT_EN_NO1S) $(DICT_EN_NORV) \
			 $(DICT_FI_CORP) $(DICT_FI_NOPD) $(DICT_FI_PROD) \
			 $(DICT_SE_CORP) $(DICT_SE_NOPD) $(DICT_SE_PROD) \
			 $(DICT_KL_NOPD)

ERRM_EN_0UNW=hfst/en/errmodel.ed0unwe.hfst
ERRM_EN_1UNW=hfst/en/errmodel.ed1unwe.hfst
ERRM_EN_1NOF=hfst/en/errmodel.ed1nofi.hfst
ERRM_EN_1HUN=hfst/en/errmodel.ed1huns.hfst
ERRM_EN_2UNW=hfst/en/errmodel.ed2unwe.hfst
ERRM_EN_2NOF=hfst/en/errmodel.ed2nofi.hfst
ERRM_EN_2HUN=hfst/en/errmodel.ed2huns.hfst
ERRM_EN_3UNW=hfst/en/errmodel.ed3unwe.hfst
ERRM_EN_3NOF=hfst/en/errmodel.ed3nofi.hfst
ERRM_EN_3HUN=hfst/en/errmodel.ed3huns.hfst

ERRM_EN_1QWE=hfst/en/errmodel.ed1qwer.hfst
ERRM_EN_2QWE=hfst/en/errmodel.ed2qwer.hfst

ERRM_EN_4UNW=hfst/en/errmodel.ed4unwe.hfst
ERRM_EN_5UNW=hfst/en/errmodel.ed5unwe.hfst
ERRM_EN_6UNW=hfst/en/errmodel.ed6unwe.hfst
ERRM_EN_7UNW=hfst/en/errmodel.ed7unwe.hfst
ERRM_EN_8UNW=hfst/en/errmodel.ed8unwe.hfst

ERRM_FI_0UNW=hfst/fi/errmodel.ed0unew.hfst
ERRM_FI_1UNW=hfst/fi/errmodel.ed1unwe.hfst
ERRM_FI_2UNW=hfst/fi/errmodel.ed2unwe.hfst
ERRM_FI_2QWE=hfst/fi/errmodel.ed2qwer.hfst
ERRM_FI_CORP=hfst/fi/errmodel.ed2corp.hfst
ERRM_FI_3UNW=hfst/fi/errmodel.ed3unwe.hfst

ERRM_SE_1UNW=hfst/se/errmodel.ed1unwe.hfst
ERRM_SE_2UNW=hfst/se/errmodel.ed2unwe.hfst
ERRM_SE_2QWE=hfst/se/errmodel.ed2qwer.hfst
ERRM_SE_CORP=hfst/se/errmodel.ed2corp.hfst

ERRM_KL_2UNW=hfst/kl/errmodel.ed2unew.hfst
ERRM_KL_2QWE=hfst/kl/errmodel.ed2qwer.hfst
ERRM_KL_CORP=hfst/kl/errmodel.ed2corp.hfst

ENWIKI_DATE=20120802
FIWIKI_DATE=20120827
SEWIKI_DATE=20120825
KLWIKI_DATE=20120902

CORP_EN_NORV=corp/en/big.txt
CORP_EN_WPLM=corp/en/wikipedia.txt
CORP_FI_WPLM=corp/fi/wikipedia.txt
CORP_SE_WPLM=corp/se/wikipedia.txt
CORP_KL_WPLM=corp/kl/wikipedia.txt

# The article table data
RESULTS_EN_RUNNING=\
				   results/en/rung.spells.dict-corpuswg.errm-ed0.tsv \
				   results/en/rung.spells.dict-corpuswg.errm-ed1.tsv \
				   results/en/rung.spells.dict-corpuswg.errm-ed2.tsv \
				   results/en/rung.spells.dict-corpuswg.errm-ed3.tsv \
				   results/en/rung.spells.dict-norvigxx.errm-ed0.tsv \
				   results/en/rung.spells.dict-norvigxx.errm-ed1.tsv \
				   results/en/rung.spells.dict-norvigxx.errm-ed2.tsv \
				   results/en/rung.spells.dict-norvigxx.errm-ed3.tsv
RESULTS_EN_REAL=\
				   results/en/real.spells.dict-corpuswg.errm-ed0.tsv \
				   results/en/real.spells.dict-corpuswg.errm-ed1.tsv \
				   results/en/real.spells.dict-corpuswg.errm-ed2.tsv \
				   results/en/real.spells.dict-corpuswg.errm-ed3.tsv \
				   results/en/real.spells.dict-norvigxx.errm-ed0.tsv \
				   results/en/real.spells.dict-norvigxx.errm-ed1.tsv \
				   results/en/real.spells.dict-norvigxx.errm-ed2.tsv \
				   results/en/real.spells.dict-norvigxx.errm-ed3.tsv \
				   results/en/real.spells.dict-corpuswg.errm-nf1.tsv \
				   results/en/real.spells.dict-corpuswg.errm-nf2.tsv \
				   results/en/real.spells.dict-corpuswg.errm-nf3.tsv \
				   results/en/real.spells.dict-norvigxx.errm-nf1.tsv \
				   results/en/real.spells.dict-norvigxx.errm-nf2.tsv \
				   results/en/real.spells.dict-norvigxx.errm-nf3.tsv \
				   results/en/real.spells.dict-corpuswg.errm-hs1.tsv \
				   results/en/real.spells.dict-corpuswg.errm-hs2.tsv \
				   results/en/real.spells.dict-corpuswg.errm-hs3.tsv \
				   results/en/real.spells.dict-norvigxx.errm-hs1.tsv \
				   results/en/real.spells.dict-norvigxx.errm-hs2.tsv \
				   results/en/real.spells.dict-norvigxx.errm-hs3.tsv \
				   results/en/real.spells.dict-aspell.errm-aspell.tsv \
				   results/en/real.spells.dict-hunspell.errm-hunspell.tsv

results-en: $(RESULTS_EN_RUNNING) $(RESULTS_EN_REAL)

# spelling results for running
results/en/rung.spells.dict-norvigxx.errm-ed5.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_5UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed5.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed5.tsv $(ERRM_EN_5UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > $@

results/en/rung.spells.dict-corpuswg.errm-ed5.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_CORP) $(ERRM_EN_5UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed5.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed5.tsv $(ERRM_EN_5UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_TINY) > $@

results/en/rung.spells.dict-norvigxx.errm-ed4.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_4UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed4.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed4.tsv $(ERRM_EN_4UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > $@

results/en/rung.spells.dict-corpuswg.errm-ed4.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_CORP) $(ERRM_EN_4UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed4.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed4.tsv $(ERRM_EN_4UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_TINY) > $@

results/en/rung.spells.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed3.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed3.tsv $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > $@

results/en/rung.spells.dict-corpuswg.errm-ed3.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_CORP) $(ERRM_EN_3UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed3.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed3.tsv $(ERRM_EN_3UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_TINY) > $@

results/en/rung.spells.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed2.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed2.tsv $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > $@

results/en/rung.spells.dict-corpuswg.errm-ed2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_CORP) $(ERRM_EN_2UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed2.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed2.tsv $(ERRM_EN_2UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_LARGE) > $@

results/en/rung.spells.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed1.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed1.tsv $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > $@

results/en/rung.spells.dict-corpuswg.errm-ed1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_CORP) $(ERRM_EN_1UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed1.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed1.tsv $(ERRM_EN_1UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_LARGE) > $@

results/en/rung.spells.dict-norvigxx.errm-ed0.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_0UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed0.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed0.tsv $(ERRM_EN_0UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > $@

results/en/rung.spells.dict-corpuswg.errm-ed0.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_CORP) $(ERRM_EN_0UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed0.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed0.tsv $(ERRM_EN_0UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_LARGE) > $@

# for reals

results/en/real.spells.dict-norvigxx.errm-ed5.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_5UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-ed5.tsv -H results/en/real.hist.dict-norvigxx.errm-ed5.tsv $(ERRM_EN_5UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-ed5.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_5UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-ed5.tsv -H results/en/real.hist.dict-corpuswg.errm-ed5.tsv $(ERRM_EN_5UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-ed4.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_4UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-ed4.tsv -H results/en/real.hist.dict-norvigxx.errm-ed4.tsv $(ERRM_EN_4UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-ed4.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_4UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-ed4.tsv -H results/en/real.hist.dict-corpuswg.errm-ed4.tsv $(ERRM_EN_4UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-ed3.tsv -H results/en/real.hist.dict-norvigxx.errm-ed3.tsv $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-ed3.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_3UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-ed3.tsv -H results/en/real.hist.dict-corpuswg.errm-ed3.tsv $(ERRM_EN_3UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-ed2.tsv -H results/en/real.hist.dict-norvigxx.errm-ed2.tsv $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-ed2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_2UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-ed2.tsv -H results/en/real.hist.dict-corpuswg.errm-ed2.tsv $(ERRM_EN_2UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-ed1.tsv -H results/en/real.hist.dict-norvigxx.errm-ed1.tsv $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-ed1.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_1UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-ed1.tsv -H results/en/real.hist.dict-corpuswg.errm-ed1.tsv $(ERRM_EN_1UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-ed0.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_0UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-ed0.tsv -H results/en/real.hist.dict-norvigxx.errm-ed0.tsv $(ERRM_EN_0UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-ed0.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_0UNW)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-ed0.tsv -H results/en/real.hist.dict-corpuswg.errm-ed0.tsv $(ERRM_EN_0UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@


results/en/real.spells.dict-norvigxx.errm-nf5.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_5NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-nf5.tsv -H results/en/real.hist.dict-norvigxx.errm-nf5.tsv $(ERRM_EN_5NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-nf5.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_5NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-nf5.tsv -H results/en/real.hist.dict-corpuswg.errm-nf5.tsv $(ERRM_EN_5NOF) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-nf4.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_4NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-nf4.tsv -H results/en/real.hist.dict-norvigxx.errm-nf4.tsv $(ERRM_EN_4NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-nf4.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_4NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-nf4.tsv -H results/en/real.hist.dict-corpuswg.errm-nf4.tsv $(ERRM_EN_4NOF) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-nf3.tsv -H results/en/real.hist.dict-norvigxx.errm-nf3.tsv $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-nf3.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_3NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-nf3.tsv -H results/en/real.hist.dict-corpuswg.errm-nf3.tsv $(ERRM_EN_3NOF) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-nf2.tsv -H results/en/real.hist.dict-norvigxx.errm-nf2.tsv $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-nf2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_2NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-nf2.tsv -H results/en/real.hist.dict-corpuswg.errm-nf2.tsv $(ERRM_EN_2NOF) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-nf1.tsv -H results/en/real.hist.dict-norvigxx.errm-nf1.tsv $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-nf1.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_1NOF)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-nf1.tsv -H results/en/real.hist.dict-corpuswg.errm-nf1.tsv $(ERRM_EN_1NOF) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-al2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_2ALL)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-al2.tsv -H results/en/real.hist.dict-norvigxx.errm-al2.tsv $(ERRM_EN_2ALL) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-al2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_2ALL)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-al2.tsv -H results/en/real.hist.dict-corpuswg.errm-al2.tsv $(ERRM_EN_2ALL) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-sx2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_2SEX)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-sx2.tsv -H results/en/real.hist.dict-norvigxx.errm-sx2.tsv $(ERRM_EN_2SEX) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-sx2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_2SEX)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-sx2.tsv -H results/en/real.hist.dict-corpuswg.errm-sx2.tsv $(ERRM_EN_2SEX) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-hs3.tsv -H results/en/real.hist.dict-norvigxx.errm-hs3.tsv $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-hs3.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_3HUN)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-hs3.tsv -H results/en/real.hist.dict-corpuswg.errm-hs3.tsv $(ERRM_EN_3HUN) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-hs2.tsv -H results/en/real.hist.dict-norvigxx.errm-hs2.tsv $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-hs2.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_2HUN)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-hs2.tsv -H results/en/real.hist.dict-corpuswg.errm-hs2.tsv $(ERRM_EN_2HUN) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	$(HFST_OSPELL) -X results/en/real.stats.dict-norvigxx.errm-hs1.tsv -H results/en/real.hist.dict-norvigxx.errm-hs1.tsv $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_REAL) > $@

results/en/real.spells.dict-corpuswg.errm-hs1.tsv: $(EN_TEST_WORDS_REAL) $(DICT_EN_CORP) $(ERRM_EN_1HUN)
	$(HFST_OSPELL) -X results/en/real.stats.dict-corpuswg.errm-hs1.tsv -H results/en/real.hist.dict-corpuswg.errm-hs1.tsv $(ERRM_EN_1HUN) $(DICT_EN_CORP) < $(EN_TEST_WORDS_REAL) > $@

# hunspell measures

results/en/%.tsv: results/en/%.aspells
	$(PYTHON3) ./hunspells2stats.py -i $< -c corp/en/wikispells.tsv -o $@

results/en/real.spells.dict-aspell.errm-aspell.aspells: corp/en/wikispells.tsv
	cut -f 1 $< |\
		$(ASPELL) -a -d en_US |\
		tr -s '\n' | tail -n +2 > $@

results/en/%.tsv: results/en/%.hunspells
	$(PYTHON3) ./hunspells2stats.py -i $< -c corp/en/wikispells.hunnable.tsv -o $@

results/en/real.spells.dict-hunspell.errm-hunspell.hunspells: corp/en/wikispells.hunnable.tsv
	$(HUNSPELL) -1 -d en_US -i UTF-8 < $< |\
		tr -s '\n' | tail -n +2 > $@

corp/en/wikispells.hunnable.tsv: corp/en/wikispells.tsv
	cut -f 2 $< | hunspell -d en_US -G > corp/en/hunnables
	fgrep -f corp/en/hunnables $< > $@
	-rm -f corp/en/hunnables

# profiling results

PROFILES_EN=\
			 results/en/profiles.1-nonwords.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.1-nonwords.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-ed3.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-hs3.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-nf3.tsv \
			 results/en/profiles.1-words.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.1-words.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-ed3.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-hs3.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-nf3.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-nf3.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-hs3.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-ed3.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-nf3.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-hs3.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-ed3.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-aspell.errm-aspell.tsv


profiles-en: $(PROFILES_EN)

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_WORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_NONWORDS_TINY) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done



# huns
results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_WORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_WORDS_TINY)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_WORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_NONWORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_NONWORDS_TINY)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_NONWORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

# as
results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-aspell.errm-aspell.tsv: $(EN_TEST_WORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-words.dict-aspell.errm-aspell.tsv: $(EN_TEST_WORDS_TINY)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_WORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-words.dict-aspell.errm-aspell.tsv: $(EN_TEST_WORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-aspell.errm-aspell.tsv: $(EN_TEST_NONWORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-aspell.errm-aspell.tsv: $(EN_TEST_NONWORDS_TINY)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-aspell.errm-aspell.tsv: $(EN_TEST_NONWORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

# dictionaries

$(DICT_EN_CORP): hfst/en/wikipedia.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

$(DICT_EN_NORV): hfst/en/big.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

$(DICT_FI_CORP): hfst/fi/wikipedia.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

$(DICT_FI_NOPD): hfst/fi/dictionary.filtered.hfst hfst/fi/wikipedia.addone.hfst corp/fi/wikipedia.addone.unseenweight
	$(HFST_COMPOSE) -F -v hfst/fi/dictionary.filtered.hfst hfst/fi/wikipedia.addone.hfst -o hfst/fi/dictionary.wpweights.hfst
	$(HFST_REWEIGHT) -v hfst/fi/dictionary.filtered.hfst -e -a `cat corp/fi/wikipedia.addone.unseenweight` -o hfst/fi/dictionary.addone-unseen.hfst
	$(HFST_UNION) -v hfst/fi/dictionary.wpweights.hfst hfst/fi/dictionary.addone-unseen.hfst -o $@

$(DICT_FI_PROD): hfst/fi/dictionary.default.hfst hfst/fi/wikipedia.addone.hfst corp/fi/wikipedia.addone.unseenweight
	$(HFST_COMPOSE) -F -v hfst/fi/dictionary.default.hfst hfst/fi/wikipedia.addone.hfst -o hfst/fi/dictionary.wpweights.hfst
	$(HFST_REWEIGHT) -v hfst/fi/dictionary.default.hfst -e -a `cat corp/fi/wikipedia.addone.unseenweight` -o hfst/fi/dictionary.addone-unseen.hfst
	$(HFST_UNION) -v hfst/fi/dictionary.wpweights.hfst hfst/fi/dictionary.addone-unseen.hfst -o $@

dictionaries:

# error models

errmodels:

$(ERRM_EN_8ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 8 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_7ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 7 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_6ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 6 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_5UNW): hfst/en/edit-1.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 5 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_5ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 5 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_4UNW): hfst/en/edit-1.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 4 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_4ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 4 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_3ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 3 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_3HUN): hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst hfst/en/hunspell-trys.hfst hfst/en/sigmastar.hfst
	$(HFST_UNION) -v hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/en/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/en/sigmastar.hfst |\
		$(HFST_REPEAT) -v -f 1 -t 3 |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_3NOF): hfst/en/no-edits-1.hfst hfst/en/edit-1.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v hfst/en/edit-1.hfst -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 3 -v |\
		$(HFST_CONCATENATE) -v hfst/en/no-edits-1.hfst - |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_3UNW): hfst/en/edit-1.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 3 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2SEX): hfst/en/edit-1.hfst hfst/en/soundex-full.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v hfst/en/edit-1.hfst -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2UNW): hfst/en/edit-1.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2NOF): hfst/en/no-edits-1.hfst hfst/en/edit-1.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v hfst/en/edit-1.hfst -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_CONCATENATE) -v hfst/en/no-edits-1.hfst - |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2HUN): hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst hfst/en/hunspell-trys.hfst hfst/en/sigmastar.hfst
	$(HFST_UNION) -v hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/en/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/en/sigmastar.hfst |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2QWE): hfst/en/edit-1-qwerty-halved.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v $< -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1NOF): hfst/en/edit-1-nonfirst.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1HUN): hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst hfst/en/hunspell-trys.hfst hfst/en/sigmastar.hfst
	$(HFST_UNION) -v hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/en/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/en/sigmastar.hfst |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1QWE): hfst/en/edit-1-qwerty-halved.hfst corp/en/wikipedia.unseenweight
	$(HFST_REWEIGHT) -v $< -b "`cat corp/en/wikipedia.unseenweight`" |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1UNW): hfst/en/edit-1.hfst
	$(HFST_MINIMIZE) -v $< |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_0UNW): hfst/en/edit-0.hfst
	$(HFST_MINIMIZE) -v $< |\
		$(HFST_FST2FST) -v -f olw -o $@

hfst/en/sigmastar.hfst:
	echo '?*' | $(HFST_REGEXP2FST) -v -o $@

hfst/en/soundex-full.hfst: hfst/en/soundex.hfst
	$(HFST_INVERT) $< -o $<.inv -v
	$(HFST_COMPOSE) -v -1 hfst/en/soundex.hfst -2 hfst/en/soundex.hfst.inv |\
		$(HFST_MINIMIZE) -v -o $@

hfst/en/%.hfst: manual/en/%.txt
	$(HFST_TXT2FST) -v $< -o $@

hfst/en/%.hfst: manual/en/%.strings
	$(HFST_STRINGS2FST) -j $< -o $@

# corpora
corp/en/wikipedia-test.txt: corp/en/enwiki-pages-articles-test.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -f utf8 -t utf8//IGNORE > $@

corp/en/wikipedia.txt: corp/en/enwiki-pages-articles-train.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -f utf8 -t utf8//IGNORE > $@

corp/fi/wikipedia.txt: corp/fi/fiwiki-pages-articles-train.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -f utf8 -t utf8//IGNORE > $@

corp/en/big.txt:
	$(WGET) http://norvig.com/big.txt -O $@

corp/en/enwiki-pages-articles-train.xml:
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles1.xml-p000000010p000010000.bz2 -O enwiki-pages-articles1.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles2.xml-p000010002p000024999.bz2 -O enwiki-pages-articles2.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles3.xml-p000025001p000055000.bz2 -O enwiki-pages-articles3.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles4.xml-p000055002p000104998.bz2 -O enwiki-pages-articles4.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles5.xml-p000105002p000184999.bz2 -O enwiki-pages-articles5.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles6.xml-p000185003p000305000.bz2 -O enwiki-pages-articles6.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles7.xml-p000305002p000464996.bz2 -O enwiki-pages-articles7.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles8.xml-p000465001p000665000.bz2 -O enwiki-pages-articles8.xml.bz2
	$(BZ2CAT) enwiki-pages-articles[12345678].xml.bz2 > $@

enwiki-pages-articles9.xml.bz2: enwiki-pages-articles10.xml.bz2
enwiki-pages-articles10.xml.bz2:
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles9.xml-p000665001p000925000.bz2 -O enwiki-pages-articles9.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles10.xml-p000925001p001325000.bz2 -O enwiki-pages-articles10.xml.bz2

corp/en/enwiki-pages-articles-test.xml: enwiki-pages-articles9.xml.bz2 enwiki-pages-articles10.xml.bz2
	$(BZ2CAT) enwiki-pages-articles9.xml.bz2 enwiki-pages-articles10.xml.bz2 > $@

corp/fi/fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2:
	$(WGET) http://dumps.wikimedia.org/fiwiki/$(FIWIKI_DATE)/fiwiki-$(FIWIKI_DATE)-pages-articles.xml.bz2 -O $@

corp/fi/fiwiki-pages-articles.lines: corp/fi/fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2
	$(BZ2CAT) $< | wc -l > $@

corp/fi/fiwiki-pages-articles-train.xml: corp/fi/fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2 corp/fi/fiwiki-pages-articles.lines
	$(BZ2CAT) $< | head -n `cat corp/fi/fiwiki-pages-articles.lines | sed -e 's/$$/ * 0.8/' | bc | sed -e 's/[.,].*//'` > $@

corp/fi/fiwiki-pages-articles-test.xml: corp/fi/fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2 corp/fi/fiwiki-pages-articles.lines
	$(BC2CAT) $< | tail -n +`cat corp/fi/fiwiki-pages-articles.lines | sed -e 's/$$/ * 0.8/' | bc | sed -e 's/[.,].*//'` > $@

corpora:

# corpus to weighted word-form lists

corp/en/%.words: corp/en/%.sorted
	sort < $< > $@

corp/en/%.$(TEST_CORPUS_HUGE).nonwords: corp/en/%.txt hfst/en/acceptor.norvigxx.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/en/acceptor.norvigxx.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_HUGE) > $@

corp/en/%.$(TEST_CORPUS_LARGE).nonwords: corp/en/%.txt hfst/en/acceptor.norvigxx.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/en/acceptor.norvigxx.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_LARGE) > $@

corp/en/%.$(TEST_CORPUS_TINY).nonwords: corp/en/%.txt hfst/en/acceptor.norvigxx.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/en/acceptor.norvigxx.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_TINY) > $@

corp/en/%.1.nonwords: corp/en/%.txt hfst/en/acceptor.norvigxx.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/en/acceptor.norvigxx.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n 1 > $@

corp/en/%.nonwords: corp/en/%.txt hfst/en/acceptor.norvigxx.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/en/acceptor.norvigxx.hfst |\
		fgrep '+?' |\
		cut -f 1 > $@

corp/en/%.$(TEST_CORPUS_HUGE).words: corp/en/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_HUGE) > $@

corp/en/%.$(TEST_CORPUS_LARGE).words: corp/en/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_LARGE) > $@

corp/en/%.$(TEST_CORPUS_TINY).words: corp/en/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_TINY) > $@

corp/en/%.1.words: corp/en/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n 1 > $@

corp/en/%.words: corp/en/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' > $@

corp/en/%.uniqc: corp/en/%.sorted
	uniq -c < $< > $@

corp/en/%.unseenweight: corp/en/%.sorted
	echo | $(AWK) "{print (-log(1 / (`wc -l < corp/en/$*.sorted` + 1)));}" > $@

corp/en/%.addone.unseenweight: corp/en/%.sorted corp/en/%.uniqc
	echo | $(AWK) "{print (-log(1 / (`wc -l < corp/en/$*.sorted` + `wc -l < corp/en/$*.uniqc`)));}" > $@

corp/en/%.addhalf.unseenweight: corp/en/%.sorted corp/en/%.uniqc
	echo | $(AWK) "{print (-log(0.5 / (`wc -l < corp/en/$*.sorted` + 0.5 * `wc -l < corp/en/$*.uniqc`)));}" > $@

corp/en/%.tropical: corp/en/%.uniqc
	$(AWK) -f tropicalize-uniq-c.awk --assign=CS=`wc -l < corp/en/$*.sorted` < $< > $@

corp/en/%.addone.tropical: corp/en/%.uniqc
	$(AWK) -f tropicalize-uniq-c-add-smoothing.awk --assign=CS=`wc -l < corp/en/$*.sorted` --assign=LS=`wc -l < corp/en/$*.uniqc` --assign=ALPHA=1 < $< > $@

corp/en/%.addhalf.tropical: corp/en/%.uniqc
	$(AWK) -f tropicalize-uniq-c-add-smoothing.awk --assign=CS=`wc -l < corp/en/$*.sorted` --assign=LS=`wc -l < corp/en/$*.uniqc` --assign=ALPHA=0.5 < $< > $@

corp/fi/%.sorted: corp/fi/%.txt
	tr -s '[:space:].-?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		sort > $@

corp/fi/%.uniqc: corp/fi/%.sorted
	uniq -c < $< > $@

corp/fi/%.unseenweight: corp/fi/%.sorted
	echo | $(AWK) "{print (-log(1 / (`wc -l < corp/fi/$*.sorted` + 1)));}" > $@

corp/fi/%.addone.unseenweight: corp/fi/%.sorted corp/fi/%.uniqc
	echo | $(AWK) "{print (-log(1 / (`wc -l < corp/fi/$*.sorted` + `wc -l < corp/fi/$*.uniqc`)));}" > $@

corp/fi/%.addhalf.unseenweight: corp/fi/%.sorted corp/fi/%.uniqc
	echo | $(AWK) "{print (-log(0.5 / (`wc -l < corp/fi/$*.sorted` + 0.5 * `wc -l < corp/fi/$*.uniqc`)));}" > $@

corp/fi/%.tropical: corp/fi/%.uniqc
	$(AWK) -f tropicalize-uniq-c.awk --assign=CS=`wc -l < corp/fi/$*.sorted` < $< > $@

corp/fi/%.addone.tropical: corp/fi/%.uniqc
	$(AWK) -f tropicalize-uniq-c-add-smoothing.awk --assign=CS=`wc -l < corp/fi/$*.sorted` --assign=LS=`wc -l < corp/fi/$*.uniqc` --assign=ALPHA=1 < $< > $@

corp/fi/%.addhalf.tropical: corp/fi/%.uniqc
	$(AWK) -f tropicalize-uniq-c-add-smoothing.awk --assign=CS=`wc -l < corp/fi/$*.sorted` --assign=LS=`wc -l < corp/fi/$*.uniqc` --assign=ALPHA=0.5 < $< > $@

# from weighted lists to automata
hfst/en/%.hfst: corp/en/%.tropical
	$(HFST_STRINGS2FST) -j $< |\
		$(HFST_MINIMIZE) -v -o $@

hfst/fi/%.hfst: corp/fi/%.tropical
	$(HFST_STRINGS2FST) -j $< |\
		$(HFST_MINIMIZE) -v -o $@

hfst/se/%.hfst: corp/se/%.tropical
	$(HFST_STRINGS2FST)  -j $< |\
		$(HFST_MINIMIZE) -v -o $@

hfst/kl/%.hfst: corp/kl/%.tropical
	$(HFST_STRINGS2FST) -j $< |\
		$(HFST_MINIMIZE) -v -o $@

# the error models
manual/en/edit-0.txt:
	$(PYTHON2) editdist.py -d 0 -s --no-elim "$(EN_ALPHABET)" |\
		fgrep -v "\\" > $@

manual/en/edit-1.txt:
	$(PYTHON2) editdist.py -s --no-elim "$(EN_ALPHABET)" |\
		fgrep -v "\\" > $@

manual/en/edit-1-nonfirst.txt:
	$(PYTHON2) editdist.py --no-string-initial-correction -s --no-elim "$(EN_ALPHABET)" |\
		fgrep -v "\\" > $@

manual/en/edit-1-qwerty-halved.txt: manual/en/qwerty.tsv
	$(PYTHON2) editdist.py -s --no-elim "$(EN_ALPHABET)" -i manual/en/qwerty.tsv |\
		fgrep -v "\\" > $@

# if lexicon'd contain spaces we'd need not filter them
manual/en/hunspell-reps.strings: $(HUNSPELL_EN_AFF)
	grep '^REP' $(HUNSPELL_EN_AFF) |\
		tail -n +2 |\
		sed -e 's/REP[[:space:]]*//' -e 's/[[:space:]]\+/:/' -e 's/_/ /g' |\
		fgrep -v ' ' > $@

manual/en/hunspell-keys.txt: $(HUNSPELL_EN_AFF)
	grep '^KEY' $(HUNSPELL_EN_AFF) |\
		sed -e 's/KEY[[:space:]]*//' -e 's/\(.\)\(.\)/0	1	\1	\2\n0	1	\2	\1\n/g' |\
		head -n -1 |\
		fgrep -v '|' > $@
	echo 1 >> $@

manual/en/hunspell-trys.txt: $(HUNSPELL_EN_AFF)
	grep '^TRY' $(HUNSPELL_EN_AFF) |\
		sed -e 's/TRY[[:space:]]*//' -e 's/\(.\)/0	1	\1	@_EPSILON_SYMBOL_@\n0	1	@_EPSILON_SYMBOL_@	\1\n/g' |\
		head -n -1 |\
		fgrep -v "'" > $@
	echo 1 >> $@


# a bit of error corpus collecting
corp/en/speling-candidates.tsv: corp/en/enwiki-pages-meta-history.xml.bz2
	$(BZ2CAT) $< |\
		$(AWK) -f dump-wiki-revisions-for-speling-wdiffs.awk --assign=CORPDIR=corp/en
	chmod +x ./print-wdiffs.sh
	./print-wdiffs.sh | grep '\[-.*+}' |\
		sed -e 's/\[-//' -e 's/-] {+/	/' -e 's/+}//' > $@
	chmod +x ./remove-junk.sh
	./remove-junk.sh

corp/fi/speling-candidates.tsv: corp/fi/fiwiki-pages-meta-history.xml.bz2
	$(BZ2CAT) $< |\
		$(AWK) -f dump-wiki-revisions-for-speling-wdiffs-fi.awk --assign=CORPDIR=corp/fi
	chmod +x ./print-wdiffs.sh
	./print-wdiffs.sh | grep '\[-.*+}' |\
		sed -e 's/\[-//' -e 's/-] *{+/	/' -e 's/+}//' > $@
	chmod +x ./remove-junk.sh
	./remove-junk.sh

corp/se/speling-candidates.tsv: corp/se/sewiki-pages-meta-history.xml.bz2
	$(BZ2CAT) $< |\
		$(AWK) -f dump-wiki-revisions-for-speling-wdiffs-se.awk --assign=CORPDIR=corp/se
	chmod +x ./print-wdiffs.sh
	./print-wdiffs.sh | grep '\[-.*+}' |\
		sed -e 's/\[-//' -e 's/-] *{+/	/' -e 's/+}//' > $@
	chmod +x ./remove-junk.sh
	./remove-junk.sh

