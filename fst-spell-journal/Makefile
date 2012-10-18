## Use make to create article pdfs or recreate test results

# {{{ program path settings
TEX=xelatex
BIB=bibtex
SCP=scp
SCPHOST=ruuvi
SCPDIR=public_html/tmp/
WGET=wget
BZCAT=bzcat
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
CONTEXT_SPELL1=hfst-ospell-cicling
CONTEXT_SPELL2=${HOME}/src/hfst-svn-trunk/articles/cicling-2011-contextspell/bin/context_speller
EN_TAGGER=${HOME}/src/hfst-svn-trunk/articles/cicling-2011-contextspell/taggers/en/hmm_model.lex ${HOME}/src/hfst-svn-trunk/articles/cicling-2011-contextspell/taggers/en/hmm_model.seq
# use GNU time rather than bash builtin
TIME=/usr/bin/time

# }}}
#
# {{{ latex building stuff
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

# }}}
#
# {{{ language settings all
PROFILE_FOR_EXPR=1 2 3 4 5

TEST_CORPUS_HUGE=100000000
TEST_CORPUS_LARGE=1000000
TEST_CORPUS_SMALL=10000
TEST_CORPUS_TINY=100
CONTEXT_CORPUS_HUGE=100000000
CONTEXT_CORPUS_LARGE=1000000
CONTEXT_CORPUS_SMALL=10000
CONTEXT_CORPUS_TINY=100

# }}}

# {{{ English settings
EN_ALPHABET=abcdefghijklmnopqrstuvwxzyABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\'-

HUNSPELL_EN_AFF=en_US.aff
EN_TEST_CORPUS=corp/en/wikipedia-test.txt


EN_TEST_SORTS_HUGE=corp/en/wikipedia-test.$(TEST_CORPUS_HUGE).sorted
EN_TEST_SORTS_LARGE=corp/en/wikipedia-test.$(TEST_CORPUS_LARGE).sorted
EN_TEST_SORTS_SMALL=corp/en/wikipedia-test.$(TEST_CORPUS_SMALL).sorted
EN_TEST_SORTS_ONE=corp/en/wikipedia-test.1.sorted
EN_TEST_WORDS_HUGE=corp/en/wikipedia-test.$(TEST_CORPUS_HUGE).words
EN_TEST_WORDS_LARGE=corp/en/wikipedia-test.$(TEST_CORPUS_LARGE).words
EN_TEST_WORDS_SMALL=corp/en/wikipedia-test.$(TEST_CORPUS_SMALL).words
EN_TEST_WORDS_ONE=corp/en/wikipedia-test.1.words
EN_TEST_NONWORDS_LARGE=corp/en/wikipedia-test.$(TEST_CORPUS_LARGE).nonwords
EN_TEST_NONWORDS_SMALL=corp/en/wikipedia-test.$(TEST_CORPUS_SMALL).nonwords
EN_TEST_NONWORDS_ONE=corp/en/wikipedia-test.1.nonwords
EN_TEST_WORDS_REAL=corp/en/wikispells.tsv
EN_TEST_WORDS_HUGE=corp/en/wikipedia-test.$(TEST_CORPUS_HUGE).contexts
EN_CONTEXT_WORDS_LARGE=corp/en/wikipedia-test.$(TEST_CORPUS_LARGE).contexts
EN_CONTEXT_WORDS_SMALL=corp/en/wikipedia-test.$(TEST_CORPUS_SMALL).contexts
EN_CONTEXT_WORDS_ONE=corp/en/wikipedia-test.1.contexts
EN_CONTEXT_NONWORDS_LARGE=corp/en/wikipedia-test.$(TEST_CORPUS_LARGE).noncontexts
EN_CONTEXT_NONWORDS_SMALL=corp/en/wikipedia-test.$(TEST_CORPUS_SMALL).noncontexts
EN_CONTEXT_NONWORDS_ONE=corp/en/wikipedia-test.1.noncontexts

ERRM_EN_0UNW=hfst/en/errmodel.ed0unwe.hfst
ERRM_EN_1UNW=hfst/en/errmodel.ed1unwe.hfst
ERRM_EN_2UNW=hfst/en/errmodel.ed2unwe.hfst
ERRM_EN_3UNW=hfst/en/errmodel.ed3unwe.hfst
ERRM_EN_4UNW=hfst/en/errmodel.ed4unwe.hfst
ERRM_EN_5UNW=hfst/en/errmodel.ed5unwe.hfst
ERRM_EN_6UNW=hfst/en/errmodel.ed6unwe.hfst
ERRM_EN_7UNW=hfst/en/errmodel.ed7unwe.hfst
ERRM_EN_8UNW=hfst/en/errmodel.ed8unwe.hfst
ERRM_EN_1NOF=hfst/en/errmodel.ed1nofi.hfst
ERRM_EN_2NOF=hfst/en/errmodel.ed2nofi.hfst
ERRM_EN_3NOF=hfst/en/errmodel.ed3nofi.hfst
ERRM_EN_1HUN=hfst/en/errmodel.ed1huns.hfst
ERRM_EN_2HUN=hfst/en/errmodel.ed2huns.hfst
ERRM_EN_3HUN=hfst/en/errmodel.ed3huns.hfst
ERRM_EN_1QWE=hfst/en/errmodel.ed1qwer.hfst
ERRM_EN_2QWE=hfst/en/errmodel.ed2qwer.hfst

DICT_EN_CORP=hfst/en/acceptor.corpuswg.hfst
DICT_EN_NORV=hfst/en/acceptor.norvigxx.hfst
ENWIKI_DATE=20120802
CORP_EN_NORV=corp/en/big.txt
CORP_EN_WPLM=corp/en/wikipedia-train.txt

# }}}
#
# {{{ Finnish settings
FI_ALPHABET=abcdefghijklmnopqršstuwvxyzžåäöABCDEFGHIJKLMNOPQRSŠTUWVXYZŽÅÄÖ0123456789\'-

FI_ALPHABET_SHORT=abcdefghijklmnopqrsštuvwxyzåäö-

FI_TEST_SORTS_HUGE=corp/fi/wikipedia-test.$(TEST_CORPUS_HUGE).sorted
FI_TEST_SORTS_LARGE=corp/fi/wikipedia-test.$(TEST_CORPUS_LARGE).sorted
FI_TEST_SORTS_SMALL=corp/fi/wikipedia-test.$(TEST_CORPUS_SMALL).sorted
FI_TEST_SORTS_TINY=corp/fi/wikipedia-test.$(TEST_CORPUS_TINY).sorted
FI_TEST_SORTS_ONE=corp/fi/wikipedia-test.1.sorted
FI_TEST_WORDS_HUGE=corp/fi/wikipedia-test.$(TEST_CORPUS_HUGE).words
FI_TEST_WORDS_LARGE=corp/fi/wikipedia-test.$(TEST_CORPUS_LARGE).words
FI_TEST_WORDS_SMALL=corp/fi/wikipedia-test.$(TEST_CORPUS_SMALL).words
FI_TEST_WORDS_TINY=corp/fi/wikipedia-test.$(TEST_CORPUS_TINY).words
FI_TEST_WORDS_ONE=corp/fi/wikipedia-test.1.words
FI_TEST_NONWORDS_LARGE=corp/fi/wikipedia-test.$(TEST_CORPUS_LARGE).nonwords
FI_TEST_NONWORDS_SMALL=corp/fi/wikipedia-test.$(TEST_CORPUS_SMALL).nonwords
FI_TEST_NONWORDS_TINY=corp/fi/wikipedia-test.$(TEST_CORPUS_TINY).nonwords
FI_TEST_NONWORDS_ONE=corp/fi/wikipedia-test.1.nonwords
FI_TEST_WORDS_REAL=corp/fi/wikispells.tsv
FI_TEST_WORDS_HUGE=corp/fi/wikipedia-test.$(TEST_CORPUS_HUGE).contexts
FI_CONTEXT_WORDS_LARGE=corp/fi/wikipedia-test.$(TEST_CORPUS_LARGE).contexts
FI_CONTEXT_WORDS_SMALL=corp/fi/wikipedia-test.$(TEST_CORPUS_SMALL).contexts
FI_CONTEXT_WORDS_TINY=corp/fi/wikipedia-test.$(TEST_CORPUS_TINY).contexts
FI_CONTEXT_WORDS_ONE=corp/fi/wikipedia-test.1.contexts
FI_CONTEXT_NONWORDS_LARGE=corp/fi/wikipedia-test.$(TEST_CORPUS_LARGE).noncontexts
FI_CONTEXT_NONWORDS_SMALL=corp/fi/wikipedia-test.$(TEST_CORPUS_SMALL).noncontexts
FI_CONTEXT_NONWORDS_TINY=corp/fi/wikipedia-test.$(TEST_CORPUS_TINY).noncontexts
FI_CONTEXT_NONWORDS_ONE=corp/fi/wikipedia-test.1.noncontexts

DICT_FI_CORP=hfst/fi/acceptor.corpuswg.hfst
DICT_FI_NOPD=hfst/fi/acceptor.gtfinopd.hfst
DICT_FI_PROD=hfst/fi/acceptor.gtfiprod.hfst

ERRM_FI_0UNW=hfst/fi/errmodel.ed0unwe.hfst
ERRM_FI_1UNW=hfst/fi/errmodel.ed1unwe.hfst
ERRM_FI_2UNW=hfst/fi/errmodel.ed2unwe.hfst
ERRM_FI_3UNW=hfst/fi/errmodel.ed3unwe.hfst
ERRM_FI_1NOF=hfst/fi/errmodel.ed1nofi.hfst
ERRM_FI_2NOF=hfst/fi/errmodel.ed2nofi.hfst
ERRM_FI_3NOF=hfst/fi/errmodel.ed3nofi.hfst
ERRM_FI_2QWE=hfst/fi/errmodel.ed2qwer.hfst
ERRM_FI_CORP=hfst/fi/errmodel.ed2corp.hfst

FIWIKI_DATE=20120827
CORP_FI_WPLM=corp/fi/wikipedia-train.txt
FIWIKI_LEGO_CUTOFF=10

# }}}

# {{{ North Sámi settings
SE_ALPHABET=abcčdefghijklmnŋopqršstŧuwvxyzžåäöABCČDĐEFGHIJKLMNŊOPQRSŠTŦUWVXYZŽÅÄÖ0123456789\'-

SE_ALPHABET_SHORT=abcdefghijklmnŋopqrsštŧuvwxyzžåäö-

SE_TEST_SORTS_HUGE=corp/se/wikipedia-test.$(TEST_CORPUS_HUGE).sorted
SE_TEST_SORTS_LARGE=corp/se/wikipedia-test.$(TEST_CORPUS_LARGE).sorted
SE_TEST_SORTS_SMALL=corp/se/wikipedia-test.$(TEST_CORPUS_SMALL).sorted
SE_TEST_SORTS_TINY=corp/se/wikipedia-test.$(TEST_CORPUS_TINY).sorted
SE_TEST_SORTS_ONE=corp/se/wikipedia-test.1.sorted
SE_TEST_WORDS_HUGE=corp/se/wikipedia-test.$(TEST_CORPUS_HUGE).words
SE_TEST_WORDS_LARGE=corp/se/wikipedia-test.$(TEST_CORPUS_LARGE).words
SE_TEST_WORDS_SMALL=corp/se/wikipedia-test.$(TEST_CORPUS_SMALL).words
SE_TEST_WORDS_TINY=corp/se/wikipedia-test.$(TEST_CORPUS_TINY).words
SE_TEST_WORDS_ONE=corp/se/wikipedia-test.1.words
SE_TEST_NONWORDS_LARGE=corp/se/wikipedia-test.$(TEST_CORPUS_LARGE).nonwords
SE_TEST_NONWORDS_SMALL=corp/se/wikipedia-test.$(TEST_CORPUS_SMALL).nonwords
SE_TEST_NONWORDS_TINY=corp/se/wikipedia-test.$(TEST_CORPUS_TINY).nonwords
SE_TEST_NONWORDS_ONE=corp/se/wikipedia-test.1.nonwords
SE_TEST_WORDS_REAL=corp/se/wikispells.tsv
SE_TEST_WORDS_HUGE=corp/se/wikipedia-test.$(TEST_CORPUS_HUGE).contexts
SE_CONTEXT_WORDS_LARGE=corp/se/wikipedia-test.$(TEST_CORPUS_LARGE).contexts
SE_CONTEXT_WORDS_SMALL=corp/se/wikipedia-test.$(TEST_CORPUS_SMALL).contexts
SE_CONTEXT_WORDS_TINY=corp/se/wikipedia-test.$(TEST_CORPUS_TINY).contexts
SE_CONTEXT_WORDS_ONE=corp/se/wikipedia-test.1.contexts
SE_CONTEXT_NONWORDS_LARGE=corp/se/wikipedia-test.$(TEST_CORPUS_LARGE).noncontexts
SE_CONTEXT_NONWORDS_SMALL=corp/se/wikipedia-test.$(TEST_CORPUS_SMALL).noncontexts
SE_CONTEXT_NONWORDS_TINY=corp/se/wikipedia-test.$(TEST_CORPUS_TINY).noncontexts
SE_CONTEXT_NONWORDS_ONE=corp/se/wikipedia-test.1.noncontexts

DICT_SE_CORP=hfst/se/acceptor.corpuswg.hfst
DICT_SE_NOPD=hfst/se/acceptor.gtsenopd.hfst
DICT_SE_PROD=hfst/se/acceptor.gtseprod.hfst


ERRM_SE_0UNW=hfst/se/errmodel.ed0unwe.hfst
ERRM_SE_1UNW=hfst/se/errmodel.ed1unwe.hfst
ERRM_SE_2UNW=hfst/se/errmodel.ed2unwe.hfst
ERRM_SE_3UNW=hfst/se/errmodel.ed3unwe.hfst
ERRM_SE_1NOF=hfst/se/errmodel.ed1nofi.hfst
ERRM_SE_2NOF=hfst/se/errmodel.ed2nofi.hfst
ERRM_SE_3NOF=hfst/se/errmodel.ed3nofi.hfst
ERRM_SE_2QWE=hfst/se/errmodel.ed2qwer.hfst
ERRM_SE_CORP=hfst/se/errmodel.ed2corp.hfst

SEWIKI_DATE=20120827
CORP_SE_WPLM=corp/se/wikipedia-train.txt
SEWIKI_LEGO_CUTOFF=2
SEWIKI_DATE=20120825
CORP_SE_WPLM=corp/se/wikipedia-train.txt

# }}}

# {{{ Greenlandic settings
ERRM_KL_2UNW=hfst/kl/errmodel.ed2unwe.hfst
ERRM_KL_2QWE=hfst/kl/errmodel.ed2qwer.hfst
ERRM_KL_CORP=hfst/kl/errmodel.ed2corp.hfst

KLWIKI_DATE=20120902
CORP_KL_WPLM=corp/kl/wikipedia-train.txt

# }}}

DICTIONARIES=$(DICT_EN_CORP) $(DICT_EN_NO1S) $(DICT_EN_NORV) \
			 $(DICT_FI_CORP) $(DICT_FI_NOPD) $(DICT_FI_PROD) \
			 $(DICT_SE_CORP) $(DICT_SE_NOPD) $(DICT_SE_PROD) \
			 $(DICT_KL_NOPD)

# coverage and quality tables
results: results-fi results-en

# {{{ English coverage and quality settings
RESULTS_EN_RUNNING=\
				   results/en/rung.spells.dict-corpuswg.errm-ed0.tsv \
				   results/en/rung.spells.dict-corpuswg.errm-ed1.tsv \
				   results/en/rung.spells.dict-corpuswg.errm-ed2.tsv \
				   results/en/rung.spells.dict-norvigxx.errm-ed0.tsv \
				   results/en/rung.spells.dict-norvigxx.errm-ed1.tsv \
				   results/en/rung.spells.dict-norvigxx.errm-ed2.tsv \
RESULTS_EN_REAL=\
				   results/en/real.spells.dict-corpuswg.errm-ed0.tsv \
				   results/en/real.spells.dict-corpuswg.errm-ed1.tsv \
				   results/en/real.spells.dict-corpuswg.errm-ed2.tsv \
				   results/en/real.spells.dict-norvigxx.errm-ed0.tsv \
				   results/en/real.spells.dict-norvigxx.errm-ed1.tsv \
				   results/en/real.spells.dict-norvigxx.errm-ed2.tsv \
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
# }}}
#
# {{{ English running text quality tests
results/en/rung.spells.dict-norvigxx.errm-ed5.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_5UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed5.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed5.tsv $(ERRM_EN_5UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > $@

results/en/rung.spells.dict-corpuswg.errm-ed5.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_CORP) $(ERRM_EN_5UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed5.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed5.tsv $(ERRM_EN_5UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_SMALL) > $@

results/en/rung.spells.dict-norvigxx.errm-ed4.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_4UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed4.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed4.tsv $(ERRM_EN_4UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > $@

results/en/rung.spells.dict-corpuswg.errm-ed4.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_CORP) $(ERRM_EN_4UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed4.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed4.tsv $(ERRM_EN_4UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_SMALL) > $@

results/en/rung.spells.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-norvigxx.errm-ed3.tsv -H results/en/rung.hist.dict-norvigxx.errm-ed3.tsv $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > $@

results/en/rung.spells.dict-corpuswg.errm-ed3.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_CORP) $(ERRM_EN_3UNW)
	$(HFST_OSPELL) -X results/en/rung.stats.dict-corpuswg.errm-ed3.tsv -H results/en/rung.hist.dict-corpuswg.errm-ed3.tsv $(ERRM_EN_3UNW) $(DICT_EN_CORP) < $(EN_TEST_WORDS_SMALL) > $@

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

# }}}
# 
# {{{ Engish real errors quality tests

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

# }}}
#
# {{{ English other spellers qualities

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

# }}}
#
# {{{ Finnish quality and coverage path settings
RESULTS_FI_RUNNING=\
				   results/fi/rung.spells.dict-aspell.errm-aspell.tsv \
				   results/fi/rung.spells.dict-corpuswg.errm-ed0.tsv \
				   results/fi/rung.spells.dict-corpuswg.errm-ed1.tsv \
				   results/fi/rung.spells.dict-corpuswg.errm-ed2.tsv \
				   results/fi/rung.spells.dict-divvunpd.errm-ed0.tsv \
				   results/fi/rung.spells.dict-divvunpd.errm-ed1.tsv \
				   results/fi/rung.spells.dict-divvunac.errm-ed0.tsv \
				   results/fi/rung.spells.dict-divvunac.errm-ed1.tsv \
				   results/fi/rung.spells.dict-divvunac.errm-ed2.tsv
RESULTS_FI_REAL=\
				   results/fi/real.spells.dict-corpuswg.errm-ed0.tsv \
				   results/fi/real.spells.dict-corpuswg.errm-ed1.tsv \
				   results/fi/real.spells.dict-corpuswg.errm-ed2.tsv \
				   results/fi/real.spells.dict-divvunpd.errm-ed0.tsv \
				   results/fi/real.spells.dict-divvunpd.errm-ed1.tsv \
				   results/fi/real.spells.dict-divvunpd.errm-ed2.tsv \
				   results/fi/real.spells.dict-corpuswg.errm-nf1.tsv \
				   results/fi/real.spells.dict-corpuswg.errm-nf2.tsv \
				   results/fi/real.spells.dict-divvunpd.errm-nf1.tsv \
				   results/fi/real.spells.dict-divvunpd.errm-nf2.tsv \
				   results/fi/real.spells.dict-aspell.errm-aspell.tsv
#				   results/fi/real.spells.dict-corpuswg.errm-hs1.tsv \
				   results/fi/real.spells.dict-corpuswg.errm-hs2.tsv \
				   results/fi/real.spells.dict-divvunpd.errm-hs1.tsv \
				   results/fi/real.spells.dict-divvunpd.errm-hs2.tsv \

results-fi: $(RESULTS_FI_RUNNING) $(RESULTS_FI_REAL)

# }}}
# 
# {{{ Finnish tests for running texts
results/fi/rung.spells.dict-divvunac.errm-ed5.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_NOPD) $(ERRM_FI_5UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunac.errm-ed5.tsv -H results/fi/rung.hist.dict-divvunac.errm-ed5.tsv $(ERRM_FI_5UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-divvunpd.errm-ed5.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_5UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunpd.errm-ed5.tsv -H results/fi/rung.hist.dict-divvunpd.errm-ed5.tsv $(ERRM_FI_5UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-corpuswg.errm-ed5.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_CORP) $(ERRM_FI_5UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-corpuswg.errm-ed5.tsv -H results/fi/rung.hist.dict-corpuswg.errm-ed5.tsv $(ERRM_FI_5UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-divvunac.errm-ed4.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_NOPD) $(ERRM_FI_4UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunac.errm-ed4.tsv -H results/fi/rung.hist.dict-divvunac.errm-ed4.tsv $(ERRM_FI_4UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-divvunpd.errm-ed4.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_4UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunpd.errm-ed4.tsv -H results/fi/rung.hist.dict-divvunpd.errm-ed4.tsv $(ERRM_FI_4UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-corpuswg.errm-ed4.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_CORP) $(ERRM_FI_4UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-corpuswg.errm-ed4.tsv -H results/fi/rung.hist.dict-corpuswg.errm-ed4.tsv $(ERRM_FI_4UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-divvunac.errm-ed3.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_NOPD) $(ERRM_FI_3UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunac.errm-ed3.tsv -H results/fi/rung.hist.dict-divvunac.errm-ed3.tsv $(ERRM_FI_3UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunpd.errm-ed3.tsv -H results/fi/rung.hist.dict-divvunpd.errm-ed3.tsv $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-corpuswg.errm-ed3.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_CORP) $(ERRM_FI_3UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-corpuswg.errm-ed3.tsv -H results/fi/rung.hist.dict-corpuswg.errm-ed3.tsv $(ERRM_FI_3UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-divvunac.errm-ed2.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_NOPD) $(ERRM_FI_2UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunac.errm-ed2.tsv -H results/fi/rung.hist.dict-divvunac.errm-ed2.tsv $(ERRM_FI_2UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunpd.errm-ed2.tsv -H results/fi/rung.hist.dict-divvunpd.errm-ed2.tsv $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-corpuswg.errm-ed2.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_CORP) $(ERRM_FI_2UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-corpuswg.errm-ed2.tsv -H results/fi/rung.hist.dict-corpuswg.errm-ed2.tsv $(ERRM_FI_2UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_TINY) > $@

results/fi/rung.spells.dict-divvunac.errm-ed1.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_NOPD) $(ERRM_FI_1UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunac.errm-ed1.tsv -H results/fi/rung.hist.dict-divvunac.errm-ed1.tsv $(ERRM_FI_1UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_LARGE) > $@

results/fi/rung.spells.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunpd.errm-ed1.tsv -H results/fi/rung.hist.dict-divvunpd.errm-ed1.tsv $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > $@

results/fi/rung.spells.dict-corpuswg.errm-ed1.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_CORP) $(ERRM_FI_1UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-corpuswg.errm-ed1.tsv -H results/fi/rung.hist.dict-corpuswg.errm-ed1.tsv $(ERRM_FI_1UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_LARGE) > $@

results/fi/rung.spells.dict-divvunac.errm-ed0.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_NOPD) $(ERRM_FI_0UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunac.errm-ed0.tsv -H results/fi/rung.hist.dict-divvunac.errm-ed0.tsv $(ERRM_FI_0UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_LARGE) > $@

results/fi/rung.spells.dict-divvunpd.errm-ed0.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_0UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-divvunpd.errm-ed0.tsv -H results/fi/rung.hist.dict-divvunpd.errm-ed0.tsv $(ERRM_FI_0UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > $@

results/fi/rung.spells.dict-corpuswg.errm-ed0.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_CORP) $(ERRM_FI_0UNW)
	$(HFST_OSPELL) -X results/fi/rung.stats.dict-corpuswg.errm-ed0.tsv -H results/fi/rung.hist.dict-corpuswg.errm-ed0.tsv $(ERRM_FI_0UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_LARGE) > $@

# }}}
#
# {{{ Finnish quality tests for real errors

results/fi/real.spells.dict-divvunac.errm-ed5.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_5UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-ed5.tsv -H results/fi/real.hist.dict-divvunac.errm-ed5.tsv $(ERRM_FI_5UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-ed5.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_5UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-ed5.tsv -H results/fi/real.hist.dict-divvunpd.errm-ed5.tsv $(ERRM_FI_5UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-ed5.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_5UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-ed5.tsv -H results/fi/real.hist.dict-corpuswg.errm-ed5.tsv $(ERRM_FI_5UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-ed4.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_4UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-ed4.tsv -H results/fi/real.hist.dict-divvunac.errm-ed4.tsv $(ERRM_FI_4UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-ed4.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_4UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-ed4.tsv -H results/fi/real.hist.dict-divvunpd.errm-ed4.tsv $(ERRM_FI_4UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-ed4.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_4UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-ed4.tsv -H results/fi/real.hist.dict-corpuswg.errm-ed4.tsv $(ERRM_FI_4UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-ed3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_3UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-ed3.tsv -H results/fi/real.hist.dict-divvunac.errm-ed3.tsv $(ERRM_FI_3UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-ed3.tsv -H results/fi/real.hist.dict-divvunpd.errm-ed3.tsv $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-ed3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_3UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-ed3.tsv -H results/fi/real.hist.dict-corpuswg.errm-ed3.tsv $(ERRM_FI_3UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-ed2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_2UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-ed2.tsv -H results/fi/real.hist.dict-divvunac.errm-ed2.tsv $(ERRM_FI_2UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-ed2.tsv -H results/fi/real.hist.dict-divvunpd.errm-ed2.tsv $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-ed2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_2UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-ed2.tsv -H results/fi/real.hist.dict-corpuswg.errm-ed2.tsv $(ERRM_FI_2UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-ed1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_1UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-ed1.tsv -H results/fi/real.hist.dict-divvunac.errm-ed1.tsv $(ERRM_FI_1UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-ed1.tsv -H results/fi/real.hist.dict-divvunpd.errm-ed1.tsv $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-ed1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_1UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-ed1.tsv -H results/fi/real.hist.dict-corpuswg.errm-ed1.tsv $(ERRM_FI_1UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-ed0.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_0UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-ed0.tsv -H results/fi/real.hist.dict-divvunac.errm-ed0.tsv $(ERRM_FI_0UNW) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-ed0.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_0UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-ed0.tsv -H results/fi/real.hist.dict-divvunpd.errm-ed0.tsv $(ERRM_FI_0UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-ed0.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_0UNW)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-ed0.tsv -H results/fi/real.hist.dict-corpuswg.errm-ed0.tsv $(ERRM_FI_0UNW) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@


results/fi/real.spells.dict-divvunac.errm-nf5.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_5NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-nf5.tsv -H results/fi/real.hist.dict-divvunac.errm-nf5.tsv $(ERRM_FI_5NOF) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-nf5.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_5NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-nf5.tsv -H results/fi/real.hist.dict-divvunpd.errm-nf5.tsv $(ERRM_FI_5NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-nf5.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_5NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-nf5.tsv -H results/fi/real.hist.dict-corpuswg.errm-nf5.tsv $(ERRM_FI_5NOF) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-nf4.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_4NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-nf4.tsv -H results/fi/real.hist.dict-divvunac.errm-nf4.tsv $(ERRM_FI_4NOF) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-nf4.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_4NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-nf4.tsv -H results/fi/real.hist.dict-divvunpd.errm-nf4.tsv $(ERRM_FI_4NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-nf4.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_4NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-nf4.tsv -H results/fi/real.hist.dict-corpuswg.errm-nf4.tsv $(ERRM_FI_4NOF) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-nf3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_3NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-nf3.tsv -H results/fi/real.hist.dict-divvunac.errm-nf3.tsv $(ERRM_FI_3NOF) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-nf3.tsv -H results/fi/real.hist.dict-divvunpd.errm-nf3.tsv $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-nf3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_3NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-nf3.tsv -H results/fi/real.hist.dict-corpuswg.errm-nf3.tsv $(ERRM_FI_3NOF) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-nf2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_2NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-nf2.tsv -H results/fi/real.hist.dict-divvunac.errm-nf2.tsv $(ERRM_FI_2NOF) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-nf2.tsv -H results/fi/real.hist.dict-divvunpd.errm-nf2.tsv $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-nf2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_2NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-nf2.tsv -H results/fi/real.hist.dict-corpuswg.errm-nf2.tsv $(ERRM_FI_2NOF) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-nf1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_1NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-nf1.tsv -H results/fi/real.hist.dict-divvunac.errm-nf1.tsv $(ERRM_FI_1NOF) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-nf1.tsv -H results/fi/real.hist.dict-divvunpd.errm-nf1.tsv $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-nf1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_1NOF)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-nf1.tsv -H results/fi/real.hist.dict-corpuswg.errm-nf1.tsv $(ERRM_FI_1NOF) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-hs3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_3HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-hs3.tsv -H results/fi/real.hist.dict-divvunac.errm-hs3.tsv $(ERRM_FI_3HUN) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-hs3.tsv -H results/fi/real.hist.dict-divvunpd.errm-hs3.tsv $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-hs3.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_3HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-hs3.tsv -H results/fi/real.hist.dict-corpuswg.errm-hs3.tsv $(ERRM_FI_3HUN) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-hs2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_2HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-hs2.tsv -H results/fi/real.hist.dict-divvunac.errm-hs2.tsv $(ERRM_FI_2HUN) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-hs2.tsv -H results/fi/real.hist.dict-divvunpd.errm-hs2.tsv $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-hs2.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_2HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-hs2.tsv -H results/fi/real.hist.dict-corpuswg.errm-hs2.tsv $(ERRM_FI_2HUN) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunac.errm-hs1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_NOPD) $(ERRM_FI_1HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunac.errm-hs1.tsv -H results/fi/real.hist.dict-divvunac.errm-hs1.tsv $(ERRM_FI_1HUN) $(DICT_FI_NOPD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-divvunpd.errm-hs1.tsv -H results/fi/real.hist.dict-divvunpd.errm-hs1.tsv $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_REAL) > $@

results/fi/real.spells.dict-corpuswg.errm-hs1.tsv: $(FI_TEST_WORDS_REAL) $(DICT_FI_CORP) $(ERRM_FI_1HUN)
	$(HFST_OSPELL) -X results/fi/real.stats.dict-corpuswg.errm-hs1.tsv -H results/fi/real.hist.dict-corpuswg.errm-hs1.tsv $(ERRM_FI_1HUN) $(DICT_FI_CORP) < $(FI_TEST_WORDS_REAL) > $@

# }}}
#
# {{{ Finnish qualite tests for other spellers

results/fi/%.tsv: results/fi/%.aspells
	$(PYTHON3) ./hunspells2stats.py -i $< -c corp/fi/wikispells.tsv -o $@

results/fi/real.spells.dict-aspell.errm-aspell.aspells: corp/fi/wikispells.tsv
	cut -f 1 $< |\
		$(ASPELL) -a -d fi |\
		tr -s '\n' | tail -n +2 > $@

results/fi/%.tsv: results/fi/%.hunspells
	$(PYTHON3) ./hunspells2stats.py -i $< -c corp/fi/wikispells.hunnable.tsv -o $@

results/fi/real.spells.dict-hunspell.errm-hunspell.hunspells: corp/fi/wikispells.hunnable.tsv
	$(HUNSPELL) -1 -d fi_FI -i UTF-8 < $< |\
		tr -s '\n' | tail -n +2 > $@

corp/fi/wikispells.hunnable.tsv: corp/fi/wikispells.tsv
	cut -f 2 $< | hunspell -d fi_FI -G > corp/fi/hunnables
	fgrep -f corp/fi/hunnables $< > $@
	-rm -f corp/fi/hunnables

# }}}
#
# {{{ North Sámi quality and coverage path settings
RESULTS_SE_RUNNING=\
				   results/se/rung.spells.dict-corpuswg.errm-ed0.tsv \
				   results/se/rung.spells.dict-corpuswg.errm-ed1.tsv \
				   results/se/rung.spells.dict-corpuswg.errm-ed2.tsv \
				   results/se/rung.spells.dict-divvunpd.errm-ed0.tsv \
				   results/se/rung.spells.dict-divvunpd.errm-ed1.tsv \
				   results/se/rung.spells.dict-divvunpd.errm-ed2.tsv \
				   results/se/rung.spells.dict-divvunac.errm-ed0.tsv \
				   results/se/rung.spells.dict-divvunac.errm-ed1.tsv \
				   results/se/rung.spells.dict-divvunac.errm-ed2.tsv
RESULTS_SE_REAL=\
				   results/se/real.spells.dict-corpuswg.errm-ed0.tsv \
				   results/se/real.spells.dict-corpuswg.errm-ed1.tsv \
				   results/se/real.spells.dict-corpuswg.errm-ed2.tsv \
				   results/se/real.spells.dict-divvunpd.errm-ed0.tsv \
				   results/se/real.spells.dict-divvunpd.errm-ed1.tsv \
				   results/se/real.spells.dict-divvunpd.errm-ed2.tsv \
				   results/se/real.spells.dict-corpuswg.errm-nf1.tsv \
				   results/se/real.spells.dict-corpuswg.errm-nf2.tsv \
				   results/se/real.spells.dict-divvunpd.errm-nf1.tsv \
				   results/se/real.spells.dict-divvunpd.errm-nf2.tsv
#				   results/se/real.spells.dict-corpuswg.errm-hs1.tsv \
				   results/se/real.spells.dict-corpuswg.errm-hs2.tsv \
				   results/se/real.spells.dict-divvunpd.errm-hs1.tsv \
				   results/se/real.spells.dict-divvunpd.errm-hs2.tsv \

results-se: $(RESULTS_SE_RUNNING) $(RESULTS_SE_REAL)

# }}}
# 
# {{{ North Sámi tests for running texts
results/se/rung.spells.dict-divvunac.errm-ed5.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_NOPD) $(ERRM_SE_5UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunac.errm-ed5.tsv -H results/se/rung.hist.dict-divvunac.errm-ed5.tsv $(ERRM_SE_5UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-divvunpd.errm-ed5.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_5UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunpd.errm-ed5.tsv -H results/se/rung.hist.dict-divvunpd.errm-ed5.tsv $(ERRM_SE_5UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-corpuswg.errm-ed5.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_CORP) $(ERRM_SE_5UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-corpuswg.errm-ed5.tsv -H results/se/rung.hist.dict-corpuswg.errm-ed5.tsv $(ERRM_SE_5UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-divvunac.errm-ed4.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_NOPD) $(ERRM_SE_4UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunac.errm-ed4.tsv -H results/se/rung.hist.dict-divvunac.errm-ed4.tsv $(ERRM_SE_4UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-divvunpd.errm-ed4.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_4UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunpd.errm-ed4.tsv -H results/se/rung.hist.dict-divvunpd.errm-ed4.tsv $(ERRM_SE_4UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-corpuswg.errm-ed4.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_CORP) $(ERRM_SE_4UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-corpuswg.errm-ed4.tsv -H results/se/rung.hist.dict-corpuswg.errm-ed4.tsv $(ERRM_SE_4UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-divvunac.errm-ed3.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_NOPD) $(ERRM_SE_3UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunac.errm-ed3.tsv -H results/se/rung.hist.dict-divvunac.errm-ed3.tsv $(ERRM_SE_3UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunpd.errm-ed3.tsv -H results/se/rung.hist.dict-divvunpd.errm-ed3.tsv $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-corpuswg.errm-ed3.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_CORP) $(ERRM_SE_3UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-corpuswg.errm-ed3.tsv -H results/se/rung.hist.dict-corpuswg.errm-ed3.tsv $(ERRM_SE_3UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-divvunac.errm-ed2.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_NOPD) $(ERRM_SE_2UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunac.errm-ed2.tsv -H results/se/rung.hist.dict-divvunac.errm-ed2.tsv $(ERRM_SE_2UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunpd.errm-ed2.tsv -H results/se/rung.hist.dict-divvunpd.errm-ed2.tsv $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-corpuswg.errm-ed2.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_CORP) $(ERRM_SE_2UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-corpuswg.errm-ed2.tsv -H results/se/rung.hist.dict-corpuswg.errm-ed2.tsv $(ERRM_SE_2UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_TINY) > $@

results/se/rung.spells.dict-divvunac.errm-ed1.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_NOPD) $(ERRM_SE_1UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunac.errm-ed1.tsv -H results/se/rung.hist.dict-divvunac.errm-ed1.tsv $(ERRM_SE_1UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_LARGE) > $@

results/se/rung.spells.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunpd.errm-ed1.tsv -H results/se/rung.hist.dict-divvunpd.errm-ed1.tsv $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > $@

results/se/rung.spells.dict-corpuswg.errm-ed1.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_CORP) $(ERRM_SE_1UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-corpuswg.errm-ed1.tsv -H results/se/rung.hist.dict-corpuswg.errm-ed1.tsv $(ERRM_SE_1UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_LARGE) > $@

results/se/rung.spells.dict-divvunac.errm-ed0.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_NOPD) $(ERRM_SE_0UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunac.errm-ed0.tsv -H results/se/rung.hist.dict-divvunac.errm-ed0.tsv $(ERRM_SE_0UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_LARGE) > $@

results/se/rung.spells.dict-divvunpd.errm-ed0.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_0UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-divvunpd.errm-ed0.tsv -H results/se/rung.hist.dict-divvunpd.errm-ed0.tsv $(ERRM_SE_0UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > $@

results/se/rung.spells.dict-corpuswg.errm-ed0.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_CORP) $(ERRM_SE_0UNW)
	$(HFST_OSPELL) -X results/se/rung.stats.dict-corpuswg.errm-ed0.tsv -H results/se/rung.hist.dict-corpuswg.errm-ed0.tsv $(ERRM_SE_0UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_LARGE) > $@

# }}}
#
# {{{ North Sámi quality tests for real errors

results/se/real.spells.dict-divvunac.errm-ed5.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_5UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-ed5.tsv -H results/se/real.hist.dict-divvunac.errm-ed5.tsv $(ERRM_SE_5UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-ed5.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_5UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-ed5.tsv -H results/se/real.hist.dict-divvunpd.errm-ed5.tsv $(ERRM_SE_5UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-ed5.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_5UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-ed5.tsv -H results/se/real.hist.dict-corpuswg.errm-ed5.tsv $(ERRM_SE_5UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-ed4.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_4UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-ed4.tsv -H results/se/real.hist.dict-divvunac.errm-ed4.tsv $(ERRM_SE_4UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-ed4.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_4UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-ed4.tsv -H results/se/real.hist.dict-divvunpd.errm-ed4.tsv $(ERRM_SE_4UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-ed4.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_4UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-ed4.tsv -H results/se/real.hist.dict-corpuswg.errm-ed4.tsv $(ERRM_SE_4UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-ed3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_3UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-ed3.tsv -H results/se/real.hist.dict-divvunac.errm-ed3.tsv $(ERRM_SE_3UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-ed3.tsv -H results/se/real.hist.dict-divvunpd.errm-ed3.tsv $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-ed3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_3UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-ed3.tsv -H results/se/real.hist.dict-corpuswg.errm-ed3.tsv $(ERRM_SE_3UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-ed2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_2UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-ed2.tsv -H results/se/real.hist.dict-divvunac.errm-ed2.tsv $(ERRM_SE_2UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-ed2.tsv -H results/se/real.hist.dict-divvunpd.errm-ed2.tsv $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-ed2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_2UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-ed2.tsv -H results/se/real.hist.dict-corpuswg.errm-ed2.tsv $(ERRM_SE_2UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-ed1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_1UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-ed1.tsv -H results/se/real.hist.dict-divvunac.errm-ed1.tsv $(ERRM_SE_1UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-ed1.tsv -H results/se/real.hist.dict-divvunpd.errm-ed1.tsv $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-ed1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_1UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-ed1.tsv -H results/se/real.hist.dict-corpuswg.errm-ed1.tsv $(ERRM_SE_1UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-ed0.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_0UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-ed0.tsv -H results/se/real.hist.dict-divvunac.errm-ed0.tsv $(ERRM_SE_0UNW) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-ed0.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_0UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-ed0.tsv -H results/se/real.hist.dict-divvunpd.errm-ed0.tsv $(ERRM_SE_0UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-ed0.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_0UNW)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-ed0.tsv -H results/se/real.hist.dict-corpuswg.errm-ed0.tsv $(ERRM_SE_0UNW) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@


results/se/real.spells.dict-divvunac.errm-nf5.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_5NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-nf5.tsv -H results/se/real.hist.dict-divvunac.errm-nf5.tsv $(ERRM_SE_5NOF) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-nf5.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_5NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-nf5.tsv -H results/se/real.hist.dict-divvunpd.errm-nf5.tsv $(ERRM_SE_5NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-nf5.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_5NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-nf5.tsv -H results/se/real.hist.dict-corpuswg.errm-nf5.tsv $(ERRM_SE_5NOF) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-nf4.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_4NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-nf4.tsv -H results/se/real.hist.dict-divvunac.errm-nf4.tsv $(ERRM_SE_4NOF) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-nf4.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_4NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-nf4.tsv -H results/se/real.hist.dict-divvunpd.errm-nf4.tsv $(ERRM_SE_4NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-nf4.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_4NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-nf4.tsv -H results/se/real.hist.dict-corpuswg.errm-nf4.tsv $(ERRM_SE_4NOF) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-nf3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_3NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-nf3.tsv -H results/se/real.hist.dict-divvunac.errm-nf3.tsv $(ERRM_SE_3NOF) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-nf3.tsv -H results/se/real.hist.dict-divvunpd.errm-nf3.tsv $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-nf3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_3NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-nf3.tsv -H results/se/real.hist.dict-corpuswg.errm-nf3.tsv $(ERRM_SE_3NOF) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-nf2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_2NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-nf2.tsv -H results/se/real.hist.dict-divvunac.errm-nf2.tsv $(ERRM_SE_2NOF) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-nf2.tsv -H results/se/real.hist.dict-divvunpd.errm-nf2.tsv $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-nf2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_2NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-nf2.tsv -H results/se/real.hist.dict-corpuswg.errm-nf2.tsv $(ERRM_SE_2NOF) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-nf1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_1NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-nf1.tsv -H results/se/real.hist.dict-divvunac.errm-nf1.tsv $(ERRM_SE_1NOF) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-nf1.tsv -H results/se/real.hist.dict-divvunpd.errm-nf1.tsv $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-nf1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_1NOF)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-nf1.tsv -H results/se/real.hist.dict-corpuswg.errm-nf1.tsv $(ERRM_SE_1NOF) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-hs3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_3HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-hs3.tsv -H results/se/real.hist.dict-divvunac.errm-hs3.tsv $(ERRM_SE_3HUN) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-hs3.tsv -H results/se/real.hist.dict-divvunpd.errm-hs3.tsv $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-hs3.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_3HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-hs3.tsv -H results/se/real.hist.dict-corpuswg.errm-hs3.tsv $(ERRM_SE_3HUN) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-hs2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_2HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-hs2.tsv -H results/se/real.hist.dict-divvunac.errm-hs2.tsv $(ERRM_SE_2HUN) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-hs2.tsv -H results/se/real.hist.dict-divvunpd.errm-hs2.tsv $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-hs2.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_2HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-hs2.tsv -H results/se/real.hist.dict-corpuswg.errm-hs2.tsv $(ERRM_SE_2HUN) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunac.errm-hs1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_NOPD) $(ERRM_SE_1HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunac.errm-hs1.tsv -H results/se/real.hist.dict-divvunac.errm-hs1.tsv $(ERRM_SE_1HUN) $(DICT_SE_NOPD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-divvunpd.errm-hs1.tsv -H results/se/real.hist.dict-divvunpd.errm-hs1.tsv $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_REAL) > $@

results/se/real.spells.dict-corpuswg.errm-hs1.tsv: $(SE_TEST_WORDS_REAL) $(DICT_SE_CORP) $(ERRM_SE_1HUN)
	$(HFST_OSPELL) -X results/se/real.stats.dict-corpuswg.errm-hs1.tsv -H results/se/real.hist.dict-corpuswg.errm-hs1.tsv $(ERRM_SE_1HUN) $(DICT_SE_CORP) < $(SE_TEST_WORDS_REAL) > $@

# }}}
#
# {{{ North Sámi qualite tests for other spellers

results/se/%.tsv: results/se/%.aspells
	$(PYTHON3) ./hunspells2stats.py -i $< -c corp/se/wikispells.tsv -o $@

results/se/real.spells.dict-aspell.errm-aspell.aspells: corp/se/wikispells.tsv
	cut -f 1 $< |\
		$(ASPELL) -a -d fi |\
		tr -s '\n' | tail -n +2 > $@

results/se/%.tsv: results/se/%.hunspells
	$(PYTHON3) ./hunspells2stats.py -i $< -c corp/se/wikispells.hunnable.tsv -o $@

results/se/real.spells.dict-hunspell.errm-hunspell.hunspells: corp/se/wikispells.hunnable.tsv
	$(HUNSPELL) -1 -d se -i UTF-8 < $< |\
		tr -s '\n' | tail -n +2 > $@

corp/se/wikispells.hunnable.tsv: corp/se/wikispells.tsv
	cut -f 2 $< | hunspell -d se -G > corp/se/hunnables
	fgrep -f corp/se/hunnables $< > $@
	-rm -f corp/se/hunnables

# }}}

# {{{ English profiling test path settings

PROFILES_EN=\
			 results/en/profiles.1-nonwords.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.1-nonwords.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-hs3.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-nf3.tsv \
			 results/en/profiles.1-nonwords.dict-norvigxx.errm-3gr.tsv \
			 results/en/profiles.1-words.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.1-words.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-hs3.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-nf3.tsv \
			 results/en/profiles.1-words.dict-norvigxx.errm-3gr.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-nf3.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-hs3.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-3gr.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-nf3.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-hs3.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-3gr.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-3gr.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-aspell.errm-aspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed2.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed1.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-3gr.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-hunspell.errm-hunspell.tsv \
			 results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-aspell.errm-aspell.tsv


profiles-en: $(PROFILES_EN)

# }}}
#
# {{{ English profiling tests
results/en/profiles.$(CONTEXT_CORPUS_LARGE)-words.dict-norvigxx.errm-3gr.tsv: $(EN_CONTEXT_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_CONTEXT_WORDS_LARGE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(EN_TAGGER) 0.85 > /dev/null ;\
	done

results/en/profiles.$(CONTEXT_CORPUS_SMALL)-words.dict-norvigxx.errm-3gr.tsv: $(EN_CONTEXT_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_CONTEXT_WORDS_SMALL) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(EN_TAGGER) 0.85 > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-3gr.tsv: $(EN_CONTEXT_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_CONTEXT_WORDS_ONE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(EN_TAGGER) 0.85 > /dev/null ;\
	done

results/en/profiles.$(CONTEXT_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-3gr.tsv: $(EN_CONTEXT_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_CONTEXT_NONWORDS_LARGE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(EN_TAGGER) 0.85 > /dev/null ;\
	done

results/en/profiles.$(CONTEXT_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-3gr.tsv: $(EN_CONTEXT_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_CONTEXT_NONWORDS_SMALL) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(EN_TAGGER) 0.85 > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-3gr.tsv: $(EN_CONTEXT_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_CONTEXT_NONWORDS_ONE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(EN_TAGGER) 0.85 > /dev/null ;\
	done


results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-5c3.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-5c3.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-5c3.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-5c3.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-5c3.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-5c3.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-5c2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-5c2.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-5c2.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-5c2.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-5c2.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-5c2.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-5c1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-5c1.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-5c1.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-5c1.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-5c1.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-5c1.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-ed3.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-ed2.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-ed1.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1UNW) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-nf3.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-nf2.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-nf1.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1NOF) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-hs3.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_3HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-hs2.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_2HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_WORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_WORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_WORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_NONWORDS_LARGE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_NONWORDS_SMALL) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-norvigxx.errm-hs1.tsv: $(EN_TEST_NONWORDS_ONE) $(DICT_EN_NORV) $(ERRM_EN_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_EN_1HUN) $(DICT_EN_NORV) < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

# }}}

# {{{ English profilng tests for other spellers
results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_WORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_WORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_WORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_NONWORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_NONWORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-hunspell.errm-hunspell.tsv: $(EN_TEST_NONWORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d en_US -i UTF-8 < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done

# aspell
results/en/profiles.$(TEST_CORPUS_LARGE)-words.dict-aspell.errm-aspell.tsv: $(EN_TEST_WORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-words.dict-aspell.errm-aspell.tsv: $(EN_TEST_WORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-words.dict-aspell.errm-aspell.tsv: $(EN_TEST_WORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_WORDS_ONE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-aspell.errm-aspell.tsv: $(EN_TEST_NONWORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/en/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-aspell.errm-aspell.tsv: $(EN_TEST_NONWORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/en/profiles.1-nonwords.dict-aspell.errm-aspell.tsv: $(EN_TEST_NONWORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d en_US -a < $(EN_TEST_NONWORDS_ONE) > /dev/null ;\
	done
# }}}

# {{{ Finnish profiling test path settings

PROFILES_FI=\
			 results/fi/profiles.1-nonwords.dict-aspell.errm-aspell.tsv \
			 results/fi/profiles.1-nonwords.dict-divvunpd.errm-ed1.tsv \
			 results/fi/profiles.1-nonwords.dict-divvunpd.errm-ed2.tsv \
			 results/fi/profiles.1-nonwords.dict-divvunpd.errm-nf1.tsv \
			 results/fi/profiles.1-nonwords.dict-divvunpd.errm-nf2.tsv \
			 results/fi/profiles.1-words.dict-aspell.errm-aspell.tsv \
			 results/fi/profiles.1-words.dict-divvunpd.errm-ed1.tsv \
			 results/fi/profiles.1-words.dict-divvunpd.errm-ed2.tsv \
			 results/fi/profiles.1-words.dict-divvunpd.errm-nf1.tsv \
			 results/fi/profiles.1-words.dict-divvunpd.errm-nf2.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf2.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed2.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf2.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed2.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-aspell.errm-aspell.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-aspell.errm-aspell.tsv \
			 results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-aspell.errm-aspell.tsv \
			 results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-aspell.errm-aspell.tsv \
			 results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-nf1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-ed1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-aspell.errm-aspell.tsv \
			 results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-nf1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-ed1.tsv \
			 results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-aspell.errm-aspell.tsv


profiles-fi: $(PROFILES_FI)

# }}}

# {{{ Finnish profiling tests
results/fi/profiles.$(CONTEXT_CORPUS_LARGE)-words.dict-divvunpd.errm-3gr.tsv: $(FI_CONTEXT_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_CONTEXT_WORDS_LARGE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(FI_TAGGER) 0.85 > /dev/null ;\
	done

results/fi/profiles.$(CONTEXT_CORPUS_SMALL)-words.dict-divvunpd.errm-3gr.tsv: $(FI_CONTEXT_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_CONTEXT_WORDS_SMALL) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(FI_TAGGER) 0.85 > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-3gr.tsv: $(FI_CONTEXT_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_CONTEXT_WORDS_ONE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(FI_TAGGER) 0.85 > /dev/null ;\
	done

results/fi/profiles.$(CONTEXT_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-3gr.tsv: $(FI_CONTEXT_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_CONTEXT_NONWORDS_LARGE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(FI_TAGGER) 0.85 > /dev/null ;\
	done

results/fi/profiles.$(CONTEXT_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-3gr.tsv: $(FI_CONTEXT_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_CONTEXT_NONWORDS_SMALL) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(FI_TAGGER) 0.85 > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-3gr.tsv: $(FI_CONTEXT_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_CONTEXT_NONWORDS_ONE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(FI_TAGGER) 0.85 > /dev/null ;\
	done


results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-5c3.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-5c3.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-5c3.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-5c3.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-5c3.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-5c3.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-5c3.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-5c3.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-5c2.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-5c2.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-5c2.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-5c2.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-5c2.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-5c2.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-5c2.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-5c2.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-5c1.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-5c1.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-5c1.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-5c1.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-5c1.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-5c1.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-5c1.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-5c1.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-ed3.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-ed2.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-ed1.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1UNW) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-nf3.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-nf2.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-nf1.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1NOF) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done


results/fi/profiles.1-words.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-hs3.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_3HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-hs2.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_2HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_WORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_WORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_WORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_WORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_NONWORDS_LARGE) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_NONWORDS_SMALL) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_NONWORDS_TINY) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-divvunpd.errm-hs1.tsv: $(FI_TEST_NONWORDS_ONE) $(DICT_FI_PROD) $(ERRM_FI_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_FI_1HUN) $(DICT_FI_PROD) < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

# }}}

# {{{ Finnish profilng tests for other spellers
results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-hunspell.errm-hunspell.tsv: $(FI_TEST_WORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d fi -i UTF-8 < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-hunspell.errm-hunspell.tsv: $(FI_TEST_WORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d fi -i UTF-8 < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-hunspell.errm-hunspell.tsv: $(FI_TEST_WORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d fi -i UTF-8 < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-hunspell.errm-hunspell.tsv: $(FI_TEST_NONWORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d fi -i UTF-8 < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-hunspell.errm-hunspell.tsv: $(FI_TEST_NONWORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d fi -i UTF-8 < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-hunspell.errm-hunspell.tsv: $(FI_TEST_NONWORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d fi -i UTF-8 < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done

# aspell
results/fi/profiles.$(TEST_CORPUS_LARGE)-words.dict-aspell.errm-aspell.tsv: $(FI_TEST_WORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d fi -a < $(FI_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-words.dict-aspell.errm-aspell.tsv: $(FI_TEST_WORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d fi -a < $(FI_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-words.dict-aspell.errm-aspell.tsv: $(FI_TEST_WORDS_TINY)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d fi -a < $(FI_TEST_WORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-words.dict-aspell.errm-aspell.tsv: $(FI_TEST_WORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d fi -a < $(FI_TEST_WORDS_ONE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-aspell.errm-aspell.tsv: $(FI_TEST_NONWORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d fi -a < $(FI_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-aspell.errm-aspell.tsv: $(FI_TEST_NONWORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d fi -a < $(FI_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/fi/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-aspell.errm-aspell.tsv: $(FI_TEST_NONWORDS_TINY)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d fi -a < $(FI_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/fi/profiles.1-nonwords.dict-aspell.errm-aspell.tsv: $(FI_TEST_NONWORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d fi -a < $(FI_TEST_NONWORDS_ONE) > /dev/null ;\
	done
# }}}

# {{{ North Sámi profiling test path settings

PROFILES_SE=\
			 results/se/profiles.1-nonwords.dict-divvunpd.errm-ed1.tsv \
			 results/se/profiles.1-nonwords.dict-divvunpd.errm-ed2.tsv \
			 results/se/profiles.1-nonwords.dict-divvunpd.errm-nf1.tsv \
			 results/se/profiles.1-nonwords.dict-divvunpd.errm-nf2.tsv \
			 results/se/profiles.1-words.dict-divvunpd.errm-ed1.tsv \
			 results/se/profiles.1-words.dict-divvunpd.errm-ed2.tsv \
			 results/se/profiles.1-words.dict-divvunpd.errm-nf1.tsv \
			 results/se/profiles.1-words.dict-divvunpd.errm-nf2.tsv \
			 results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf2.tsv \
			 results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed2.tsv \
			 results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf2.tsv \
			 results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed2.tsv \
			 results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf1.tsv \
			 results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed1.tsv \
			 results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf1.tsv \
			 results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed1.tsv \
			 results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf2.tsv \
			 results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed2.tsv \
			 results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf2.tsv \
			 results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed2.tsv \
			 results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf1.tsv \
			 results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed1.tsv \
			 results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf1.tsv \
			 results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed1.tsv \
			 results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-nf1.tsv \
			 results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-ed1.tsv \
			 results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-nf1.tsv \
			 results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-ed1.tsv


profiles-se: $(PROFILES_SE)

# }}}

# {{{ North Sámi profiling tests
results/se/profiles.$(CONTEXT_CORPUS_LARGE)-words.dict-divvunpd.errm-3gr.tsv: $(SE_CONTEXT_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_CONTEXT_WORDS_LARGE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(SE_TAGGER) 0.85 > /dev/null ;\
	done

results/se/profiles.$(CONTEXT_CORPUS_SMALL)-words.dict-divvunpd.errm-3gr.tsv: $(SE_CONTEXT_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_CONTEXT_WORDS_SMALL) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(SE_TAGGER) 0.85 > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-3gr.tsv: $(SE_CONTEXT_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_CONTEXT_WORDS_ONE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(SE_TAGGER) 0.85 > /dev/null ;\
	done

results/se/profiles.$(CONTEXT_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-3gr.tsv: $(SE_CONTEXT_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_CONTEXT_NONWORDS_LARGE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(SE_TAGGER) 0.85 > /dev/null ;\
	done

results/se/profiles.$(CONTEXT_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-3gr.tsv: $(SE_CONTEXT_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_CONTEXT_NONWORDS_SMALL) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(SE_TAGGER) 0.85 > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-3gr.tsv: $(SE_CONTEXT_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(CONTEXT_SPELL1)   $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_CONTEXT_NONWORDS_ONE) |fgrep '['|fgrep -v '[inf]'| $(TIME) -a -o $@ $(CONTEXT_SPELL2) $(SE_TAGGER) 0.85 > /dev/null ;\
	done


results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-5c3.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-5c3.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-5c3.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-5c3.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-5c3.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-5c3.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-5c3.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-5c3.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-5c2.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-5c2.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-5c2.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-5c2.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-5c2.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-5c2.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-5c2.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-5c2.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-5c1.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-5c1.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-5c1.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-5c1.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-5c1.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-5c1.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-5c1.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-5c1.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ -n 5 $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-ed3.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-ed2.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_2UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-ed1.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_1UNW)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1UNW) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-nf3.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-nf2.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_2NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-nf1.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_1NOF)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1NOF) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done


results/se/profiles.1-words.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-hs3.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_3HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_3HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-hs2.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_2HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_2HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_WORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_WORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_WORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_WORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_NONWORDS_LARGE) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_NONWORDS_SMALL) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_NONWORDS_TINY) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-divvunpd.errm-hs1.tsv: $(SE_TEST_NONWORDS_ONE) $(DICT_SE_PROD) $(ERRM_SE_1HUN)
	for i in $(PROFILE_FOR_EXPR); do \
		$(HFST_OSPELL) -P $@ $(ERRM_SE_1HUN) $(DICT_SE_PROD) < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

# }}}

# {{{ North Sámi profilng tests for other spellers
results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-hunspell.errm-hunspell.tsv: $(SE_TEST_WORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d se -i UTF-8 < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-hunspell.errm-hunspell.tsv: $(SE_TEST_WORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d se -i UTF-8 < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.1-words.dict-hunspell.errm-hunspell.tsv: $(SE_TEST_WORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d se -i UTF-8 < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-hunspell.errm-hunspell.tsv: $(SE_TEST_NONWORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d se -i UTF-8 < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-hunspell.errm-hunspell.tsv: $(SE_TEST_NONWORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d se -i UTF-8 < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-hunspell.errm-hunspell.tsv: $(SE_TEST_NONWORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(HUNSPELL) -d se -i UTF-8 < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done

# aspell
results/se/profiles.$(TEST_CORPUS_LARGE)-words.dict-aspell.errm-aspell.tsv: $(SE_TEST_WORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d se -a < $(SE_TEST_WORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-words.dict-aspell.errm-aspell.tsv: $(SE_TEST_WORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d se -a < $(SE_TEST_WORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-words.dict-aspell.errm-aspell.tsv: $(SE_TEST_WORDS_TINY)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d se -a < $(SE_TEST_WORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-words.dict-aspell.errm-aspell.tsv: $(SE_TEST_WORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d se -a < $(SE_TEST_WORDS_ONE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_LARGE)-nonwords.dict-aspell.errm-aspell.tsv: $(SE_TEST_NONWORDS_LARGE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d se -a < $(SE_TEST_NONWORDS_LARGE) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_SMALL)-nonwords.dict-aspell.errm-aspell.tsv: $(SE_TEST_NONWORDS_SMALL)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d se -a < $(SE_TEST_NONWORDS_SMALL) > /dev/null ;\
	done

results/se/profiles.$(TEST_CORPUS_TINY)-nonwords.dict-aspell.errm-aspell.tsv: $(SE_TEST_NONWORDS_TINY)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d se -a < $(SE_TEST_NONWORDS_TINY) > /dev/null ;\
	done

results/se/profiles.1-nonwords.dict-aspell.errm-aspell.tsv: $(SE_TEST_NONWORDS_ONE)
	for i in $(PROFILE_FOR_EXPR); do \
		$(TIME) -a -o $@ $(ASPELL) -d se -a < $(SE_TEST_NONWORDS_ONE) > /dev/null ;\
	done
# }}}


# dictionaries
dictionaries: dictionaries-en dictionaries-fi dictionaries-se

# {{{ English dictionary building
dictionaries-en: $(DICT_EN_CORP) $(DICT_EN_NORV)

$(DICT_EN_CORP): hfst/en/wikipedia-train.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

$(DICT_EN_NORV): hfst/en/big.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

# }}}
#
# {{{ Finnish dictionary building
dictionaries-fi: $(DICT_FI_CORP) $(DICT_FI_NOPD) $(DICT_FI_PROD)

$(DICT_FI_CORP): hfst/fi/wikipedia-train.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

$(DICT_FI_NOPD): hfst/fi/giellatekno-filtered-weighted.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

# N.B: minimize fail for 2012-10-09
$(DICT_FI_PROD): hfst/fi/giellatekno-weighted.hfst
	$(HFST_FST2FST) -v -f olw -o $@ $<

hfst/fi/giellatekno-filtered-weighted.hfst: hfst/fi/dictionary.filtered.hfst hfst/fi/wikipedia-train.addone.hfst corp/fi/wikipedia-train.addone.unseenweight
	$(HFST_COMPOSE) -F -v hfst/fi/dictionary.filtered.hfst hfst/fi/wikipedia-train.addone.hfst -o hfst/fi/dictionary.wpweights.hfst
	$(HFST_REWEIGHT) -v hfst/fi/dictionary.filtered.hfst -e -a `cat corp/fi/wikipedia-train.addone.unseenweight` -o hfst/fi/dictionary.filtered.addone-unseen.hfst
	$(HFST_UNION) -v hfst/fi/dictionary.wpweights.hfst hfst/fi/dictionary.filtered.addone-unseen.hfst -o $@


hfst/fi/giellatekno-weighted.hfst: hfst/fi/dictionary.default.hfst hfst/fi/wikipedia-train.addone.hfst corp/fi/wikipedia-train.addone.unseenweight
	$(HFST_COMPOSE) -F -v hfst/fi/dictionary.default.hfst hfst/fi/wikipedia-train.addone.hfst -o hfst/fi/dictionary.wpweights.hfst
	$(HFST_REWEIGHT) -v hfst/fi/dictionary.default.hfst -e -a `cat corp/fi/wikipedia-train.addone.unseenweight` -o hfst/fi/dictionary.addone-unseen.hfst
	$(HFST_UNION) -v hfst/fi/dictionary.wpweights.hfst hfst/fi/dictionary.addone-unseen.hfst -o $@

# }}}
#
# {{{ North Sámi dictionary building
dictionaries-se: $(DICT_SE_CORP) $(DICT_SE_NOPD) $(DICT_SE_PROD)

$(DICT_SE_CORP): hfst/se/wikipedia-train.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

$(DICT_SE_NOPD): hfst/se/giellatekno-filtered-weighted.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

$(DICT_SE_PROD): hfst/se/giellatekno-weighted.hfst
	$(HFST_MINIMIZE) -v $< | $(HFST_FST2FST) -v -f olw -o $@

hfst/se/giellatekno-filtered-weighted.hfst: hfst/se/dictionary.filtered.hfst hfst/se/wikipedia-train.addone.hfst corp/se/wikipedia-train.addone.unseenweight
	$(HFST_COMPOSE) -F -v hfst/se/dictionary.filtered.hfst hfst/se/wikipedia-train.addone.hfst -o hfst/se/dictionary.wpweights.hfst
	$(HFST_REWEIGHT) -v hfst/se/dictionary.filtered.hfst -e -a `cat corp/se/wikipedia-train.addone.unseenweight` -o hfst/se/dictionary.filtered.addone-unseen.hfst
	$(HFST_UNION) -v hfst/se/dictionary.wpweights.hfst hfst/se/dictionary.filtered.addone-unseen.hfst -o $@


hfst/se/giellatekno-weighted.hfst: hfst/se/dictionary.default.hfst hfst/se/wikipedia-train.addone.hfst corp/se/wikipedia-train.addone.unseenweight
	$(HFST_COMPOSE) -F -v hfst/se/dictionary.default.hfst hfst/se/wikipedia-train.addone.hfst -o hfst/se/dictionary.wpweights.hfst
	$(HFST_REWEIGHT) -v hfst/se/dictionary.default.hfst -e -a `cat corp/se/wikipedia-train.addone.unseenweight` -o hfst/se/dictionary.addone-unseen.hfst
	$(HFST_UNION) -v hfst/se/dictionary.wpweights.hfst hfst/se/dictionary.addone-unseen.hfst -o $@

# }}}
#
# error models

errmodels: errmodels-en errmodels-fi errmodels-se

# {{{ English error model building
errmodels-en: $(ERRM_EN_8ALL) $(ERRM_EN_7ALL)

$(ERRM_EN_8ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 8 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_7ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 7 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_6ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 6 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_5UNW): hfst/en/edit-1.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 5 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_5ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 5 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_4UNW): hfst/en/edit-1.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 4 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_4ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 4 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_3ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 3 |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_3HUN): hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst hfst/en/hunspell-trys.hfst hfst/en/sigmastar.hfst
	$(HFST_UNION) -v hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/en/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/en/sigmastar.hfst |\
		$(HFST_REPEAT) -v -f 1 -t 3 |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_3NOF): hfst/en/no-edits-1.hfst hfst/en/edit-1.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v hfst/en/edit-1.hfst -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 3 -v |\
		$(HFST_CONCATENATE) -v hfst/en/no-edits-1.hfst - |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_3UNW): hfst/en/edit-1.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 3 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2SEX): hfst/en/edit-1.hfst hfst/en/soundex-full.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v hfst/en/edit-1.hfst -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_UNION) -v - hfst/en/soundex-full.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2UNW): hfst/en/edit-1.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2NOF): hfst/en/no-edits-1.hfst hfst/en/edit-1.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v hfst/en/edit-1.hfst -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_CONCATENATE) -v hfst/en/no-edits-1.hfst - |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2HUN): hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst hfst/en/hunspell-trys.hfst hfst/en/sigmastar.hfst
	$(HFST_UNION) -v hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/en/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/en/sigmastar.hfst |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_2QWE): hfst/en/edit-1-qwerty-halved.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1NOF): hfst/en/edit-1-nonfirst.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1ALL): hfst/en/soundex-full.hfst hfst/en/hunspell-reps+context.hfst hfst/en/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/en/edit-1-qwerty-halved.hfst -b "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_UNION) -v - hfst/en/hunspell-reps+context.hfst |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1HUN): hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst hfst/en/hunspell-trys.hfst hfst/en/sigmastar.hfst
	$(HFST_UNION) -v hfst/en/hunspell-reps.hfst hfst/en/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/en/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/en/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/en/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/en/sigmastar.hfst |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_EN_1QWE): hfst/en/edit-1-qwerty-halved.hfst corp/en/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -b "`cat corp/en/wikipedia-train.unseenweight`" |\
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

# }}}

# {{{ Finnish error model building
errmodels-fi: $(ERRM_FI_0UNW) $(ERRM_FI_1UNW) $(ERRM_FI_2UNW) $(ERRM_FI_3UNW) \
			  $(ERRM_FI_1QWE) $(ERRM_FI_2QWE) $(ERRM_FI_3QWE) \
			  $(ERRM_FI_1NOF) $(ERRM_FI_2NOF) $(ERRM_FI_3NOF)

$(ERRM_FI_8ALL):  hfst/fi/hunspell-reps+context.hfst hfst/fi/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/fi/edit-1-qwerty-halved.hfst -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 8 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/fi/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_7ALL):  hfst/fi/hunspell-reps+context.hfst hfst/fi/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/fi/edit-1-qwerty-halved.hfst -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 7 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/fi/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_6ALL):  hfst/fi/hunspell-reps+context.hfst hfst/fi/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/fi/edit-1-qwerty-halved.hfst -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 6 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/fi/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_5UNW): hfst/fi/edit-1.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 5 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_5ALL):  hfst/fi/hunspell-reps+context.hfst hfst/fi/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/fi/edit-1-qwerty-halved.hfst -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 5 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/fi/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_4UNW): hfst/fi/edit-1.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 4 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_4ALL):  hfst/fi/hunspell-reps+context.hfst hfst/fi/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/fi/edit-1-qwerty-halved.hfst -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 4 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/fi/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_3ALL):  hfst/fi/hunspell-reps+context.hfst hfst/fi/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/fi/edit-1-qwerty-halved.hfst -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 3 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/fi/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_3HUN): hfst/fi/hunspell-reps.hfst hfst/fi/hunspell-keys.hfst hfst/fi/hunspell-trys.hfst hfst/fi/sigmastar.hfst
	$(HFST_UNION) -v hfst/fi/hunspell-reps.hfst hfst/fi/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/fi/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/fi/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/fi/sigmastar.hfst |\
		$(HFST_REPEAT) -v -f 1 -t 3 |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_3NOF): hfst/fi/no-edits-1.hfst hfst/fi/edit-1.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v hfst/fi/edit-1.hfst -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 3 -v |\
		$(HFST_CONCATENATE) -v hfst/fi/no-edits-1.hfst - |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_3UNW): hfst/fi/edit-1.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 3 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_2UNW): hfst/fi/edit-1.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_2NOF): hfst/fi/no-edits-1.hfst hfst/fi/edit-1.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v hfst/fi/edit-1.hfst -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_CONCATENATE) -v hfst/fi/no-edits-1.hfst - |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_2ALL):  hfst/fi/hunspell-reps+context.hfst hfst/fi/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/fi/edit-1-qwerty-halved.hfst -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_UNION) -v - hfst/fi/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_2HUN): hfst/fi/hunspell-reps.hfst hfst/fi/hunspell-keys.hfst hfst/fi/hunspell-trys.hfst hfst/fi/sigmastar.hfst
	$(HFST_UNION) -v hfst/fi/hunspell-reps.hfst hfst/fi/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/fi/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/fi/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/fi/sigmastar.hfst |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_2QWE): hfst/fi/edit-1-qwerty-halved.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_1NOF): hfst/fi/edit-1-nonfirst.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_1ALL):  hfst/fi/hunspell-reps+context.hfst hfst/fi/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/fi/edit-1-qwerty-halved.hfst -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_UNION) -v - hfst/fi/hunspell-reps+context.hfst |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_1HUN): hfst/fi/hunspell-reps.hfst hfst/fi/hunspell-keys.hfst hfst/fi/hunspell-trys.hfst hfst/fi/sigmastar.hfst
	$(HFST_UNION) -v hfst/fi/hunspell-reps.hfst hfst/fi/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/fi/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/fi/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/fi/sigmastar.hfst |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_1QWE): hfst/fi/edit-1-qwerty-halved.hfst corp/fi/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -b "`cat corp/fi/wikipedia-train.unseenweight`" |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_1UNW): hfst/fi/edit-1.hfst
	$(HFST_MINIMIZE) -v $< |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_FI_0UNW): hfst/fi/edit-0.hfst
	$(HFST_MINIMIZE) -v $< |\
		$(HFST_FST2FST) -v -f olw -o $@

hfst/fi/sigmastar.hfst:
	echo '?*' | $(HFST_REGEXP2FST) -v -o $@

hfst/fi/%.hfst: manual/fi/%.txt
	$(HFST_TXT2FST) -v $< -o $@

hfst/fi/%.hfst: manual/fi/%.strings
	$(HFST_STRINGS2FST) -j $< | $(HFST_MINIMIZE) -o $@

# }}}
#
# {{{ North Sámi error model building
errmodels-se: $(ERRM_SE_0UNW) $(ERRM_SE_1UNW) $(ERRM_SE_2UNW) $(ERRM_SE_3UNW) \
			  $(ERRM_SE_1QWE) $(ERRM_SE_2QWE) $(ERRM_SE_3QWE) \
			  $(ERRM_SE_1NOF) $(ERRM_SE_2NOF) $(ERRM_SE_3NOF)

$(ERRM_SE_8ALL):  hfst/se/hunspell-reps+context.hfst hfst/se/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/se/edit-1-qwerty-halved.hfst -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 8 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/se/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_7ALL):  hfst/se/hunspell-reps+context.hfst hfst/se/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/se/edit-1-qwerty-halved.hfst -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 7 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/se/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_6ALL):  hfst/se/hunspell-reps+context.hfst hfst/se/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/se/edit-1-qwerty-halved.hfst -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 6 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/se/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_5UNW): hfst/se/edit-1.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 5 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_5ALL):  hfst/se/hunspell-reps+context.hfst hfst/se/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/se/edit-1-qwerty-halved.hfst -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 5 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/se/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_4UNW): hfst/se/edit-1.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 4 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_4ALL):  hfst/se/hunspell-reps+context.hfst hfst/se/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/se/edit-1-qwerty-halved.hfst -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 4 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/se/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_3ALL):  hfst/se/hunspell-reps+context.hfst hfst/se/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/se/edit-1-qwerty-halved.hfst -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 3 |\
		$(HFST_UNION) -v -  |\
		$(HFST_UNION) -v - hfst/se/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_3HUN): hfst/se/hunspell-reps.hfst hfst/se/hunspell-keys.hfst hfst/se/hunspell-trys.hfst hfst/se/sigmastar.hfst
	$(HFST_UNION) -v hfst/se/hunspell-reps.hfst hfst/se/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/se/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/se/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/se/sigmastar.hfst |\
		$(HFST_REPEAT) -v -f 1 -t 3 |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_3NOF): hfst/se/no-edits-1.hfst hfst/se/edit-1.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v hfst/se/edit-1.hfst -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 3 -v |\
		$(HFST_CONCATENATE) -v hfst/se/no-edits-1.hfst - |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_3UNW): hfst/se/edit-1.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 3 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_2UNW): hfst/se/edit-1.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_2NOF): hfst/se/no-edits-1.hfst hfst/se/edit-1.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v hfst/se/edit-1.hfst -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -f 1 -t 2 -v |\
		$(HFST_CONCATENATE) -v hfst/se/no-edits-1.hfst - |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_2ALL):  hfst/se/hunspell-reps+context.hfst hfst/se/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/se/edit-1-qwerty-halved.hfst -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_UNION) -v - hfst/se/hunspell-reps+context.hfst |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_2HUN): hfst/se/hunspell-reps.hfst hfst/se/hunspell-keys.hfst hfst/se/hunspell-trys.hfst hfst/se/sigmastar.hfst
	$(HFST_UNION) -v hfst/se/hunspell-reps.hfst hfst/se/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/se/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/se/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/se/sigmastar.hfst |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_2QWE): hfst/se/edit-1-qwerty-halved.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_REPEAT) -v -f 1 -t 2 |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_1NOF): hfst/se/edit-1-nonfirst.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_1ALL):  hfst/se/hunspell-reps+context.hfst hfst/se/edit-1-qwerty-halved.hfst
	$(HFST_REWEIGHT) -v hfst/se/edit-1-qwerty-halved.hfst -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_UNION) -v - hfst/se/hunspell-reps+context.hfst |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_1HUN): hfst/se/hunspell-reps.hfst hfst/se/hunspell-keys.hfst hfst/se/hunspell-trys.hfst hfst/se/sigmastar.hfst
	$(HFST_UNION) -v hfst/se/hunspell-reps.hfst hfst/se/hunspell-keys.hfst |\
		$(HFST_UNION) -v - hfst/se/hunspell-trys.hfst |\
		$(HFST_REWEIGHT) -v -e -a "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_CONCATENATE) -v hfst/se/sigmastar.hfst - |\
		$(HFST_CONCATENATE) -v - hfst/se/sigmastar.hfst |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_1QWE): hfst/se/edit-1-qwerty-halved.hfst corp/se/wikipedia-train.unseenweight
	$(HFST_REWEIGHT) -v $< -b "`cat corp/se/wikipedia-train.unseenweight`" |\
		$(HFST_MINIMIZE) -v |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_1UNW): hfst/se/edit-1.hfst
	$(HFST_MINIMIZE) -v $< |\
		$(HFST_FST2FST) -v -f olw -o $@

$(ERRM_SE_0UNW): hfst/se/edit-0.hfst
	$(HFST_MINIMIZE) -v $< |\
		$(HFST_FST2FST) -v -f olw -o $@

hfst/se/sigmastar.hfst:
	echo '?*' | $(HFST_REGEXP2FST) -v -o $@

hfst/se/%.hfst: manual/se/%.txt
	$(HFST_TXT2FST) -v $< -o $@

hfst/se/%.hfst: manual/se/%.strings
	$(HFST_STRINGS2FST) -j $< | $(HFST_MINIMIZE) -o $@

# }}}
#
# corpora
corpora: corpora-en corpora-fi corpora-se

# {{{ English corpora herding
corpora-en: corp/en/wikipedia-test.txt corp/en/wikipedia-train.txt corp/en/big.txt

corp/en/wikipedia-test.txt: corp/en/enwiki-pages-articles-test.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -c -f utf8 -t utf8//IGNORE > $@

corp/en/wikipedia-train.txt: corp/en/enwiki-pages-articles-train.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -c -f utf8 -t utf8//IGNORE > $@

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
	$(BZCAT) enwiki-pages-articles[12345678].xml.bz2 > $@

enwiki-pages-articles9.xml.bz2: enwiki-pages-articles10.xml.bz2
enwiki-pages-articles10.xml.bz2:
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles9.xml-p000665001p000925000.bz2 -O enwiki-pages-articles9.xml.bz2
	$(WGET) http://dumps.wikimedia.org/enwiki/$(ENWIKI_DATE)/enwiki-$(ENWIKI_DATE)-pages-articles10.xml-p000925001p001325000.bz2 -O enwiki-pages-articles10.xml.bz2

corp/en/enwiki-pages-articles-test.xml: enwiki-pages-articles9.xml.bz2 enwiki-pages-articles10.xml.bz2
	$(BZCAT) enwiki-pages-articles9.xml.bz2 enwiki-pages-articles10.xml.bz2 > $@
# }}}
#
# {{{ Finnish corpora herding
corpora-fi: corp/fi/wikipedia-train.txt corp/fi/wikipedia-test.txt

corp/fi/wikipedia-test.txt: corp/fi/fiwiki-pages-articles-test.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -c -f utf8 -t utf8//IGNORE > $@

corp/fi/wikipedia-train.txt: corp/fi/fiwiki-pages-articles-train.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -c -f utf8 -t utf8//IGNORE > $@

corp/fi/fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2:
	$(WGET) http://dumps.wikimedia.org/fiwiki/$(FIWIKI_DATE)/fiwiki-$(FIWIKI_DATE)-pages-articles.xml.bz2 -O $@

corp/fi/fiwiki-pages-articles.lines: corp/fi/fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2
	$(BZCAT) $< | wc -l > $@

corp/fi/fiwiki-pages-articles-train.xml: corp/fi/fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2 corp/fi/fiwiki-pages-articles.lines
	$(BZCAT) $< | head -n `cat corp/fi/fiwiki-pages-articles.lines | sed -e 's/$$/ * 0.1/' | bc | sed -e 's/[.,].*//'` > $@

corp/fi/fiwiki-pages-articles-test.xml: corp/fi/fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2 corp/fi/fiwiki-pages-articles.lines
	$(BZCAT) $< | tail -n +`cat corp/fi/fiwiki-pages-articles.lines | sed -e 's/$$/ * 0.9/' | bc | sed -e 's/[.,].*//'` > $@


# }}}
#
# {{{ North Sámi corpora herding
corpora-se: corp/se/wikipedia-train.txt corp/se/wikipedia-test.txt

corp/se/wikipedia-test.txt: corp/se/sewiki-pages-articles-test.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -c -f utf8 -t utf8//IGNORE > $@

corp/se/wikipedia-train.txt: corp/se/sewiki-pages-articles-train.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) |\
		iconv -c -f utf8 -t utf8//IGNORE > $@

corp/se/sewiki-pages-articles-$(SEWIKI_DATE).xml.bz2:
	$(WGET) http://dumps.wikimedia.org/sewiki/$(SEWIKI_DATE)/sewiki-$(SEWIKI_DATE)-pages-articles.xml.bz2 -O $@

corp/se/sewiki-pages-articles.lines: corp/se/sewiki-pages-articles-$(SEWIKI_DATE).xml.bz2
	$(BZCAT) $< | wc -l > $@

corp/se/sewiki-pages-articles-train.xml: corp/se/sewiki-pages-articles-$(SEWIKI_DATE).xml.bz2 corp/se/sewiki-pages-articles.lines
	$(BZCAT) $< | head -n `cat corp/se/sewiki-pages-articles.lines | sed -e 's/$$/ * 0.9/' | bc | sed -e 's/[.,].*//'` > $@

corp/se/sewiki-pages-articles-test.xml: corp/se/sewiki-pages-articles-$(SEWIKI_DATE).xml.bz2 corp/se/sewiki-pages-articles.lines
	$(BZCAT) $< | tail -n +`cat corp/se/sewiki-pages-articles.lines | sed -e 's/$$/ * 0.9/' | bc | sed -e 's/[.,].*//'` > $@


# }}}
#
# corpus to weighted word-form lists

# {{{ English corpora building
corp/en/%.sorted: corp/en/%.words
	sort < $< > $@

corp/en/%.$(CONTEXT_CORPUS_HUGE).contexts: corp/en/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_HUGE) > $@

corp/en/%.$(CONTEXT_CORPUS_LARGE).contexts: corp/en/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_LARGE) > $@

corp/en/%.$(CONTEXT_CORPUS_SMALL).contexts: corp/en/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_SMALL) > $@

corp/en/%.1.contexts: corp/en/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n 1 > $@

corp/en/%.contexts: corp/en/%.txt
	$(AWK) -f text2contexts.awk < $< > $@

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

corp/en/%.$(TEST_CORPUS_SMALL).nonwords: corp/en/%.txt hfst/en/acceptor.norvigxx.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/en/acceptor.norvigxx.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_SMALL) > $@

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

corp/en/%.$(TEST_CORPUS_SMALL).words: corp/en/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_SMALL) > $@

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

# }}}
#
# {{{ Finnish corpora building
corp/fi/%.sorted: corp/fi/%.words
	sort < $< > $@

corp/fi/%.$(CONTEXT_CORPUS_HUGE).contexts: corp/fi/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_HUGE) > $@

corp/fi/%.$(CONTEXT_CORPUS_LARGE).contexts: corp/fi/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_LARGE) > $@

corp/fi/%.$(CONTEXT_CORPUS_SMALL).contexts: corp/fi/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_SMALL) > $@

corp/fi/%.1.contexts: corp/fi/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n 1 > $@

corp/fi/%.contexts: corp/fi/%.txt
	$(AWK) -f text2contexts.awk < $< > $@

corp/fi/%.$(TEST_CORPUS_HUGE).nonwords: corp/fi/%.txt hfst/fi/acceptor.gtfiprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/fi/acceptor.gtfiprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_HUGE) > $@

corp/fi/%.$(TEST_CORPUS_LARGE).nonwords: corp/fi/%.txt hfst/fi/acceptor.gtfiprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/fi/acceptor.gtfiprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_LARGE) > $@

corp/fi/%.$(TEST_CORPUS_SMALL).nonwords: corp/fi/%.txt hfst/fi/acceptor.gtfiprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/fi/acceptor.gtfiprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_SMALL) > $@

corp/fi/%.$(TEST_CORPUS_TINY).nonwords: corp/fi/%.txt hfst/fi/acceptor.gtfiprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/fi/acceptor.gtfiprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_TINY) > $@

corp/fi/%.1.nonwords: corp/fi/%.txt hfst/fi/acceptor.gtfiprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/fi/acceptor.gtfiprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n 1 > $@

corp/fi/%.nonwords: corp/fi/%.txt hfst/fi/acceptor.gtfiprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/fi/acceptor.gtfiprod.hfst |\
		fgrep '+?' |\
		cut -f 1 > $@

corp/fi/%.$(TEST_CORPUS_HUGE).words: corp/fi/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_HUGE) > $@

corp/fi/%.$(TEST_CORPUS_LARGE).words: corp/fi/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_LARGE) > $@

corp/fi/%.$(TEST_CORPUS_SMALL).words: corp/fi/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_SMALL) > $@

corp/fi/%.$(TEST_CORPUS_TINY).words: corp/fi/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_TINY) > $@

corp/fi/%.1.words: corp/fi/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n 1 > $@

corp/fi/%.words: corp/fi/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(FI_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' > $@

corp/fi/%.uniqc: corp/fi/%.sorted
	uniq -c < $< | awk '$$1 > $(FIWIKI_LEGO_CUTOFF) {print}' > $@

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


# }}}
#
# {{{ North Sámi corpora building
corp/se/%.sorted: corp/se/%.words
	sort < $< > $@

corp/se/%.$(CONTEXT_CORPUS_HUGE).contexts: corp/se/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_HUGE) > $@

corp/se/%.$(CONTEXT_CORPUS_LARGE).contexts: corp/se/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_LARGE) > $@

corp/se/%.$(CONTEXT_CORPUS_SMALL).contexts: corp/se/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n $(CONTEXT_CORPUS_SMALL) > $@

corp/se/%.1.contexts: corp/se/%.txt
	$(AWK) -f text2contexts.awk < $< |\
		head -n 1 > $@

corp/se/%.contexts: corp/se/%.txt
	$(AWK) -f text2contexts.awk < $< > $@

corp/se/%.$(TEST_CORPUS_HUGE).nonwords: corp/se/%.txt hfst/se/acceptor.gtseprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/se/acceptor.gtseprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_HUGE) > $@

corp/se/%.$(TEST_CORPUS_LARGE).nonwords: corp/se/%.txt hfst/se/acceptor.gtseprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/se/acceptor.gtseprod.hfst |\
		fgrep '+?' |\
		cut -f 1 > corp/se/$*.nonwords
	cat corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords corp/se/$*.nonwords |\
		head -n $(TEST_CORPUS_LARGE) > $@

corp/se/%.$(TEST_CORPUS_SMALL).nonwords: corp/se/%.txt hfst/se/acceptor.gtseprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/se/acceptor.gtseprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_SMALL) > $@

corp/se/%.$(TEST_CORPUS_TINY).nonwords: corp/se/%.txt hfst/se/acceptor.gtseprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/se/acceptor.gtseprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n $(TEST_CORPUS_TINY) > $@

corp/se/%.1.nonwords: corp/se/%.txt hfst/se/acceptor.gtseprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/se/acceptor.gtseprod.hfst |\
		fgrep '+?' |\
		cut -f 1 |\
		head -n 1 > $@

corp/se/%.nonwords: corp/se/%.txt hfst/se/acceptor.gtseprod.hfst
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		$(HFST_LOOKUP) hfst/se/acceptor.gtseprod.hfst |\
		fgrep '+?' |\
		cut -f 1 > $@

corp/se/%.$(TEST_CORPUS_HUGE).words: corp/se/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_HUGE) > $@

corp/se/%.$(TEST_CORPUS_LARGE).words: corp/se/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' > corp/se/$*.words
	cat corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words corp/se/$*.words |\
		head -n $(TEST_CORPUS_LARGE) > $@

corp/se/%.$(TEST_CORPUS_SMALL).words: corp/se/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_SMALL) > $@

corp/se/%.$(TEST_CORPUS_TINY).words: corp/se/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n $(TEST_CORPUS_TINY) > $@

corp/se/%.1.words: corp/se/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' |\
		head -n 1 > $@

corp/se/%.words: corp/se/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(SE_ALPHABET)]*$$" |\
		grep '[[:alpha:]]' > $@

corp/se/%.uniqc: corp/se/%.sorted
	uniq -c < $< | awk '$$1 > $(SEWIKI_LEGO_CUTOFF) {print}' > $@

corp/se/%.unseenweight: corp/se/%.sorted
	echo | $(AWK) "{print (-log(1 / (`wc -l < corp/se/$*.sorted` + 1)));}" > $@

corp/se/%.addone.unseenweight: corp/se/%.sorted corp/se/%.uniqc
	echo | $(AWK) "{print (-log(1 / (`wc -l < corp/se/$*.sorted` + `wc -l < corp/se/$*.uniqc`)));}" > $@

corp/se/%.addhalf.unseenweight: corp/se/%.sorted corp/se/%.uniqc
	echo | $(AWK) "{print (-log(0.5 / (`wc -l < corp/se/$*.sorted` + 0.5 * `wc -l < corp/se/$*.uniqc`)));}" > $@

corp/se/%.tropical: corp/se/%.uniqc
	$(AWK) -f tropicalize-uniq-c.awk --assign=CS=`wc -l < corp/se/$*.sorted` < $< > $@

corp/se/%.addone.tropical: corp/se/%.uniqc
	$(AWK) -f tropicalize-uniq-c-add-smoothing.awk --assign=CS=`wc -l < corp/se/$*.sorted` --assign=LS=`wc -l < corp/se/$*.uniqc` --assign=ALPHA=1 < $< > $@

corp/se/%.addhalf.tropical: corp/se/%.uniqc
	$(AWK) -f tropicalize-uniq-c-add-smoothing.awk --assign=CS=`wc -l < corp/se/$*.sorted` --assign=LS=`wc -l < corp/se/$*.uniqc` --assign=ALPHA=0.5 < $< > $@


# }}}
#
#
# from weighted lists to automata
# EN
hfst/en/%.hfst: corp/en/%.tropical
	$(HFST_STRINGS2FST) -j $< |\
		$(HFST_MINIMIZE) -v -o $@

# FI
hfst/fi/%.hfst: corp/fi/%.tropical
	$(HFST_STRINGS2FST) -j $< |\
		$(HFST_MINIMIZE) -v -o $@

# SE
hfst/se/%.hfst: corp/se/%.tropical
	$(HFST_STRINGS2FST)  -j $< |\
		$(HFST_MINIMIZE) -v -o $@
# KL
hfst/kl/%.hfst: corp/kl/%.tropical
	$(HFST_STRINGS2FST) -j $< |\
		$(HFST_MINIMIZE) -v -o $@

# the error models
# {{{ English error models
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

# }}}

# {{{ Finnish error models
manual/fi/no-edits-1.txt: manual/fi/edit-0.txt
	$(AWK)  'BEGIN {OFS = "\t";} NF == 5 {$$2 = 1; print;} NF == 2 {$$1 =1; print;}' < manual/fi/edit-0.txt > $@

manual/fi/edit-0.txt:
	$(PYTHON2) editdist.py -d 0 -s --no-elim "$(FI_ALPHABET_SHORT)" |\
		fgrep -v "\\" > $@

manual/fi/edit-1.txt:
	$(PYTHON2) editdist.py -s --no-elim "$(FI_ALPHABET_SHORT)" |\
		fgrep -v "\\" > $@

manual/fi/edit-1-nonfirst.txt:
	$(PYTHON2) editdist.py --no-string-initial-correction -s --no-elim "$(FI_ALPHABET_SHORT)" |\
		fgrep -v "\\" > $@

manual/fi/edit-1-qwerty-halved.txt: manual/fi/qwerty.tsv
	$(PYTHON2) editdist.py -s --no-elim "$(FI_ALPHABET_SHORT)" -i manual/fi/qwerty.tsv |\
		fgrep -v "\\" > $@

# if lexicon'd contain spaces we'd need not filter them
manual/fi/hunspell-reps.strings: $(HUNSPELL_FI_AFF)
	grep '^REP' $(HUNSPELL_FI_AFF) |\
		tail -n +2 |\
		sed -e 's/REP[[:space:]]*//' -e 's/[[:space:]]\+/:/' -e 's/_/ /g' |\
		fgrep -v ' ' > $@

manual/fi/hunspell-keys.txt: $(HUNSPELL_FI_AFF)
	grep '^KEY' $(HUNSPELL_FI_AFF) |\
		sed -e 's/KEY[[:space:]]*//' -e 's/\(.\)\(.\)/0	1	\1	\2\n0	1	\2	\1\n/g' |\
		head -n -1 |\
		fgrep -v '|' > $@
	echo 1 >> $@

manual/fi/hunspell-trys.txt: $(HUNSPELL_FI_AFF)
	grep '^TRY' $(HUNSPELL_FI_AFF) |\
		sed -e 's/TRY[[:space:]]*//' -e 's/\(.\)/0	1	\1	@_EPSILON_SYMBOL_@\n0	1	@_EPSILON_SYMBOL_@	\1\n/g' |\
		head -n -1 |\
		fgrep -v "'" > $@
	echo 1 >> $@

# }}}

# {{{ North Sámi error models
manual/se/no-edits-1.txt: manual/se/edit-0.txt
	$(AWK)  'BEGIN {OFS = "\t";} NF == 5 {$$2 = 1; print;} NF == 2 {$$1 =1; print;}' < manual/se/edit-0.txt > $@

manual/se/edit-0.txt:
	$(PYTHON2) editdist.py -d 0 -s --no-elim "$(SE_ALPHABET_SHORT)" |\
		fgrep -v "\\" > $@

manual/se/edit-1.txt:
	$(PYTHON2) editdist.py -s --no-elim "$(SE_ALPHABET_SHORT)" |\
		fgrep -v "\\" > $@

manual/se/edit-1-nonfirst.txt:
	$(PYTHON2) editdist.py --no-string-initial-correction -s --no-elim "$(SE_ALPHABET_SHORT)" |\
		fgrep -v "\\" > $@

manual/se/edit-1-qwerty-halved.txt: manual/se/qwerty.tsv
	$(PYTHON2) editdist.py -s --no-elim "$(SE_ALPHABET_SHORT)" -i manual/se/qwerty.tsv |\
		fgrep -v "\\" > $@

# if lexicon'd contain spaces we'd need not filter them
manual/se/hunspell-reps.strings: $(HUNSPELL_SE_AFF)
	grep '^REP' $(HUNSPELL_SE_AFF) |\
		tail -n +2 |\
		sed -e 's/REP[[:space:]]*//' -e 's/[[:space:]]\+/:/' -e 's/_/ /g' |\
		fgrep -v ' ' > $@

manual/se/hunspell-keys.txt: $(HUNSPELL_SE_AFF)
	grep '^KEY' $(HUNSPELL_SE_AFF) |\
		sed -e 's/KEY[[:space:]]*//' -e 's/\(.\)\(.\)/0	1	\1	\2\n0	1	\2	\1\n/g' |\
		head -n -1 |\
		fgrep -v '|' > $@
	echo 1 >> $@

manual/se/hunspell-trys.txt: $(HUNSPELL_SE_AFF)
	grep '^TRY' $(HUNSPELL_SE_AFF) |\
		sed -e 's/TRY[[:space:]]*//' -e 's/\(.\)/0	1	\1	@_EPSILON_SYMBOL_@\n0	1	@_EPSILON_SYMBOL_@	\1\n/g' |\
		head -n -1 |\
		fgrep -v "'" > $@
	echo 1 >> $@

# }}}

#
# a bit of error corpus collecting
# EN
corp/en/speling-candidates.tsv: corp/en/enwiki-pages-meta-history.xml.bz2
	$(BZCAT) $< |\
		$(AWK) -f dump-wiki-revisions-for-speling-wdiffs.awk --assign=CORPDIR=corp/en
	chmod +x ./print-wdiffs.sh
	./print-wdiffs.sh | grep '\[-.*+}' |\
		sed -e 's/\[-//' -e 's/-] {+/	/' -e 's/+}//' > $@
	chmod +x ./remove-junk.sh
	./remove-junk.sh

# FI
corp/fi/speling-candidates.tsv: corp/fi/fiwiki-pages-meta-history.xml.bz2
	$(BZCAT) $< |\
		$(AWK) -f dump-wiki-revisions-for-speling-wdiffs-fi.awk --assign=CORPDIR=corp/fi
	chmod +x ./print-wdiffs.sh
	./print-wdiffs.sh | grep '\[-.*+}' |\
		sed -e 's/\[-//' -e 's/-] *{+/	/' -e 's/+}//' > $@
	chmod +x ./remove-junk.sh
	./remove-junk.sh

# SE
corp/se/speling-candidates.tsv: corp/se/sewiki-pages-meta-history.xml.bz2
	$(BZCAT) $< |\
		$(AWK) -f dump-wiki-revisions-for-speling-wdiffs-se.awk --assign=CORPDIR=corp/se
	chmod +x ./print-wdiffs.sh
	./print-wdiffs.sh | grep '\[-.*+}' |\
		sed -e 's/\[-//' -e 's/-] *{+/	/' -e 's/+}//' > $@
	chmod +x ./remove-junk.sh
	./remove-junk.sh

# KL
#

# vim: set foldmethod=marker:
