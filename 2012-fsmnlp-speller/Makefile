# Execute this Makefile with GNU compatible make to recreate the test results
# and paper for article titled
# `blah' in Proceedings of FSMLNP 2012

# point programs to right binaries
PYTHON=python3
HFST_EDIT_DISTANCE=hfst-edit-distance
HFST_OSPELL=hfst-ospell
HFST_FST2FST=hfst-fst2fst
XELATEX=xelatex
BIBTEX=bibtex
WGET=wget
BZCAT=bzcat

FOMA=foma
HUNSPELL=hunspell -1 -a
VOIKKOSPELL=voikkospell -s

# dictionaries to build or fetch
EN_DICT=hfst/en/norvig.hfst
FI_DICT=hfst/fi/omorfi-20110505.hfst
KL_DICT=hfst/kl/kl.hfst

# test settings
# this expression is used in sh for loop
TESTS=1 2 3 4 5
# this is the amount of words to test for typical tests
WORDS=10000
# very slow / large tests with this many words
LESSWORDS=100
# scale time results then by (should be approx. WORDS/LESSWORDS)
SCALE=100

# build target lists
DICTIONARIES=$(EN_DICT) \
			 $(FI_DICT) \
			 $(KL_DICT)

# word list corpora
CORPORA=corp/fi/fiwiki-20120213-pages-articles.2000000.xml \
		corp/en/enwiki-20120211-pages-articles.2000000.xml \
		corp/kl/klwiki-20120214-pages-articles.xml \
		corp/en/enwiki.$(WORDS).words \
		corp/fi/fiwiki.$(WORDS).words \
		corp/kl/klwiki.$(WORDS).words \
		corp/en/enwiki.$(LESSWORDS).words \
		corp/fi/fiwiki.$(LESSWORDS).words \
		corp/kl/klwiki.$(LESSWORDS).words \
		corp/en/automisp.words \
		corp/fi/automisp.words \
		corp/kl/automisp.words

# the error models!
MODELS=hfst/fi/errmodel.edit-distance-1.hfst \
		hfst/en/errmodel.edit-distance-1.hfst \
		hfst/kl/errmodel.edit-distance-1.hfst \
		hfst/en/errmodel.edit-distance-2.hfst \
		hfst/fi/errmodel.edit-distance-2.hfst \
		hfst/kl/errmodel.edit-distance-2.hfst \
		hfst/en/errmodel.edit-distance-3.hfst \
		hfst/fi/errmodel.edit-distance-3.hfst \
		hfst/kl/errmodel.edit-distance-3.hfst \
		hfst/en/errmodel.edit-distance-2-no-redundant.hfst \
		hfst/fi/errmodel.edit-distance-2-no-redundant.hfst \
		hfst/kl/errmodel.edit-distance-2-no-redundant.hfst \
		hfst/en/errmodel.edit-distance-3-no-redundant.hfst \
		hfst/fi/errmodel.edit-distance-3-no-redundant.hfst \
		hfst/kl/errmodel.edit-distance-3-no-redundant.hfst \
		hfst/fi/errmodel.edit-distance-1-no-initial.hfst \
		hfst/en/errmodel.edit-distance-1-no-initial.hfst \
		hfst/kl/errmodel.edit-distance-1-no-initial.hfst \
		hfst/en/errmodel.edit-distance-2-no-initial.hfst \
		hfst/fi/errmodel.edit-distance-2-no-initial.hfst \
		hfst/kl/errmodel.edit-distance-2-no-initial.hfst \
		hfst/en/errmodel.edit-distance-3-no-initial.hfst \
		hfst/fi/errmodel.edit-distance-3-no-initial.hfst \
		hfst/kl/errmodel.edit-distance-3-no-initial.hfst \
		hfst/en/errmodel.edit-distance-2-no-initial-no-redundant.hfst \
		hfst/fi/errmodel.edit-distance-2-no-initial-no-redundant.hfst \
		hfst/kl/errmodel.edit-distance-2-no-initial-no-redundant.hfst \
		hfst/en/errmodel.edit-distance-3-no-initial-no-redundant.hfst \
		hfst/fi/errmodel.edit-distance-3-no-initial-no-redundant.hfst \
		hfst/kl/errmodel.edit-distance-3-no-initial-no-redundant.hfst

# final tex tables
TABLES=results/table1.tex results/table2.tex \
	   results/table3.tex results/table4.tex results/table5.tex \
	   results/table6.tex

# generic targets
.PHONY: all results dictionaries models corpora tables clean-results clean-corpora clean-models clean-tables


# article
articles: fsmnlp-2012-speedspelling.pdf fsmnlp-2012-spelling-tutorial.pdf

TUTORIAL_GRAPHICS=anystar.pdf cat.pdf catses.pdf cta2cat.pdf \
				  cta.pdf demo-lm.pdf edit1-ab10.pdf \
				  edit1+en-orth.pdf edit1swap-ab10.pdf \
				  en-confusables.pdf en-orth.pdf \
				  errm-ed1.pdf errm.edit1+en-orth.pdf

%.pdf: %.dot
	dot -Tpdf -o$@ $<

fsmnlp-2012-spelling-tutorial.pdf: fsmnlp-2012-spelling-tutorial.tex $(TUTORIAL_GRAPHICS)
	$(XELATEX) $<
	$(XELATEX) $<
	$(XELATEX) $<

fsmnlp-2012-speedspelling.pdf: fsmnlp-2012-speedspelling.tex fsmnlp2012.bib
	$(XELATEX) fsmnlp-2012-speedspelling.tex
	$(BIBTEX)  fsmnlp-2012-speedspelling
	$(XELATEX) fsmnlp-2012-speedspelling.tex
	$(XELATEX) fsmnlp-2012-speedspelling.tex
	$(XELATEX) fsmnlp-2012-speedspelling.tex

# generic target
all: results articles

# test results
results: corpora dictionaries models tables

dictionaries: $(DICTIONARIES)
models: $(MODELS)
corpora: $(CORPORA)
tables: $(TABLES)

clean-results: clean-tables clean-corpora clean-models

clean-corpora:
	-rm -rf $(CORPORA)

clean-tables:
	-rm -rf $(TABLES)

clean-models:
	-rm -rf $(MODELS)

# corpora acquisition
fiwiki-20120213-pages-articles.xml.bz2:
	$(WGET) 'http://dumps.wikimedia.org/fiwiki/20120213/fiwiki-20120213-pages-articles.xml.bz2'

corp/fi/fiwiki-20120213-pages-articles.2000000.xml: fiwiki-20120213-pages-articles.xml.bz2
	$(BZCAT) $< | head -n 2000000 > $@

enwiki-20120211-pages-articles.xml.bz2:
	$(WGET) 'http://dumps.wikimedia.org/enwiki/20120211/enwiki-20120211-pages-articles.xml.bz2'

corp/en/enwiki-20120211-pages-articles.2000000.xml: enwiki-20120211-pages-articles.xml.bz2
	$(BZCAT) $< | head -n 2000000 > $@

klwiki-20120214-pages-articles.xml.bz2:
	$(WGET) 'http://dumps.wikimedia.org/klwiki/20120214/klwiki-20120214-pages-articles.xml.bz2'

corp/kl/klwiki-20120214-pages-articles.xml: klwiki-20120214-pages-articles.xml.bz2
	$(BZCAT) $< > $@

# corpora preprocessing (ugly fixme plz)
corp/en/enwiki.$(WORDS).words: corp/en/enwiki-20120211-pages-articles.2000000.xml wikipedia-deform.sh
	awk '/<text/,/<\/text/ {print}' < $< |\
		./wikipedia-deform.sh |\
		tr -s ' ' '\n' |\
		head -n $(WORDS) > $@

corp/fi/fiwiki.$(WORDS).words: corp/fi/fiwiki-20120213-pages-articles.2000000.xml
	awk '/<text/,/<\/text/ {print}' < $< |\
		./wikipedia-deform.sh |\
		tr -s ' ' '\n' |\
		head -n $(WORDS) > $@

corp/kl/klwiki.$(WORDS).words: corp/kl/klwiki-20120214-pages-articles.xml
	awk '/<text/,/<\/text/ {print}' < $< |\
		./wikipedia-deform.sh |\
		tr -s ' ' '\n' |\
		head -n $(WORDS) > $@

corp/en/enwiki.$(LESSWORDS).words: corp/en/enwiki-20120211-pages-articles.2000000.xml wikipedia-deform.sh
	awk '/<text/,/<\/text/ {print}' < $< |\
		./wikipedia-deform.sh |\
		tr -s ' ' '\n' |\
		head -n $(LESSWORDS) > $@

corp/fi/fiwiki.$(LESSWORDS).words: corp/fi/fiwiki-20120213-pages-articles.2000000.xml
	awk '/<text/,/<\/text/ {print}' < $< |\
		./wikipedia-deform.sh |\
		tr -s ' ' '\n' |\
		head -n $(LESSWORDS) > $@

corp/kl/klwiki.$(LESSWORDS).words: corp/kl/klwiki-20120214-pages-articles.xml
	awk '/<text/,/<\/text/ {print}' < $< |\
		./wikipedia-deform.sh |\
		tr -s ' ' '\n' |\
		head -n $(LESSWORDS) > $@

# to 1:1 recreate article results please be using --seed=15632753
corp/en/automisp.words: corp/en/enwiki.$(WORDS).words
	python lines2misspell.py --seed=15632753 --input=$< --output=$@

corp/fi/automisp.words: corp/fi/fiwiki.$(WORDS).words
	python lines2misspell.py --seed=15632753 --input=$< --output=$@

corp/kl/automisp.words: corp/kl/klwiki.$(WORDS).words
	python lines2misspell.py --seed=15632753 --input=$< --output=$@

# fetching / concocting dictionary automata from external sources
big.txt:
	wget http://norvig.com/big.txt

hfst/en/norvig.hfst: big.txt
	tr -s '[.:?!;:-][:digit:]' ' ' < big.txt | tr -s '[:space:]' '\n' | tr '[:upper:]' '[:lower:]' > words
	sort < words | uniq -c | sort -nr > train
	awk -f tropicalize-uniq-c.awk --assign CS=`wc -l < words` < train > tropical
	hfst-strings2fst -j -f openfst-tropical -v < tropical |\
		hfst-minimize -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/fi/omorfi-20110505.hfst:
	$(WGET) 'http://download.gna.org/omorfi/omorfi-20110505-transducers.tar.xz'
	tar Jxvf omorfi-20110505-transducers.tar.xz
	mv omorfi-transducers-20110505/dictionary.default.hfstol $@

hfst/kl/kl.hfst:
	wget 'http://sourceforge.net/projects/hfst/files/spell-transducers/voikko-kl-linux-x86_64-static.oxt/download' -O voikko-kl-linux-x86_64-static.oxt
	unzip voikko-kl-linux-x86_64-static.oxt
	unzip 2/mor-hfst-kl/speller.zhfst
	mv acceptor.default.hfst $@

hfst/kl/kl.foma: hfst/kl/kl.hfst
	hfst-fst2fst -i $< -o $@.unzipped -f foma -b -v
	gzip $@.unzipped
	mv -v $@.unzipped.gz $@
	
# create all error models here

# Basic ED 1
hfst/fi/errmodel.edit-distance-1.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s --no-elim -d 1 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-1.hfst: hfst/en/norvig.hfst
	python editdist.py -s --no-elim -d 1 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-1.hfst: hfst/kl/kl.hfst
	python editdist.py -s --no-elim -d 1 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@
# Basic ED 2
hfst/fi/errmodel.edit-distance-2.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s --no-elim -d 2 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-2.hfst: hfst/en/norvig.hfst
	python editdist.py -s --no-elim -d 2 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-2.hfst: hfst/kl/kl.hfst
	python editdist.py -s --no-elim -d 2 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@
# Basic ED 3
hfst/fi/errmodel.edit-distance-3.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s --no-elim -d 3 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-3.hfst: hfst/en/norvig.hfst
	python editdist.py -s --no-elim -d 3 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-3.hfst: hfst/kl/kl.hfst
	python editdist.py -s --no-elim -d 3 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

# ED 2, eliminate redundancies
hfst/fi/errmodel.edit-distance-2-no-redundant.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s -d 2 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-2-no-redundant.hfst: hfst/en/norvig.hfst
	python editdist.py -s -d 2 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-2-no-redundant.hfst: hfst/kl/kl.hfst
	python editdist.py -s -d 2 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

# ED 3, eliminate redundancies
hfst/fi/errmodel.edit-distance-3-no-redundant.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s -d 3 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-3-no-redundant.hfst: hfst/en/norvig.hfst
	python editdist.py -s -d 3 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-3-no-redundant.hfst: hfst/kl/kl.hfst
	python editdist.py -s -d 3 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

# ED 1, no initial edit
hfst/fi/errmodel.edit-distance-1-no-initial.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 1 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-1-no-initial.hfst: hfst/en/norvig.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 1 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-1-no-initial.hfst: hfst/kl/kl.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 1 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

# ED 2, no initial edit
hfst/fi/errmodel.edit-distance-2-no-initial.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 2 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-2-no-initial.hfst: hfst/en/norvig.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 2 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-2-no-initial.hfst: hfst/kl/kl.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 2 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

# ED 3, no initial edit
hfst/fi/errmodel.edit-distance-3-no-initial.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 3 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-3-no-initial.hfst: hfst/en/norvig.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 3 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-3-no-initial.hfst: hfst/kl/kl.hfst
	python editdist.py -s --no-elim --no-string-initial-correction -d 3 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

# ED 2, no initial edit, eliminate redundancies
hfst/fi/errmodel.edit-distance-2-no-initial-no-redundant.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s --no-string-initial-correction -d 2 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-2-no-initial-no-redundant.hfst: hfst/en/norvig.hfst
	python editdist.py -s --no-string-initial-correction -d 2 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-2-no-initial-no-redundant.hfst: hfst/kl/kl.hfst
	python editdist.py -s --no-string-initial-correction -d 2 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

# ED 3, no initial edit
hfst/fi/errmodel.edit-distance-3-no-initial-no-redundant.hfst: hfst/fi/omorfi-20110505.hfst
	python editdist.py -s --no-string-initial-correction -d 3 abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/en/errmodel.edit-distance-3-no-initial-no-redundant.hfst: hfst/en/norvig.hfst
	python editdist.py -s --no-string-initial-correction -d 3 abcdefghijklmnopqrstuvwxyz |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

hfst/kl/errmodel.edit-distance-3-no-initial-no-redundant.hfst: hfst/kl/kl.hfst
	python editdist.py -s --no-string-initial-correction -d 3 abcdefghijklmnopqrstuvwxyzåäæøöABCDEFGHIJKLMNOPQRSTUVWXYZÅÆØÄÖ |\
		hfst-txt2fst -v |\
		hfst-fst2fst -v -f olw -o $@

# create profiling data for tables 1 and 2 and ...

# ED 1

results/en/table1.dict-hunspell.errm-hunspell.corp-wiki.times: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		/usr/bin/time -f %U -a -o $@ \
			$(HUNSPELL) -d en_US corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/en/table1.dict-norvig.errm-ed1.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-1.hfst $(EN_DICT) < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-voikko.errm-voikko.corp-wiki.times: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		/usr/bin/time -f %U -a -o $@ \
			$(VOIKKOSPELL) -d fi_FI < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed1.corp-wiki.profile: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-1.hfst $(FI_DICT) < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed1.corp-wiki.profile: corp/kl/klwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-1.hfst $(KL_DICT) < corp/kl/klwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-foma.corp-wiki.times: corp/kl/klwiki.$(WORDS).words hfst/kl/kl.foma
	echo > $@
	printf "load stack hfst/kl/kl.foma\napply med\n" > fomascript
	cat corp/kl/klwiki.$(WORDS).words >> fomascript
	echo "quit" >> fomascript
	for i in $(TESTS) ; do \
		/usr/bin/time -f %U -a -o $@ \
			$(FOMA) -f fomascript > /dev/null ;\
	done
	-rm -f fomascript

# Table 1, ED 2

results/en/table1.dict-norvig.errm-ed2.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-2.hfst $(EN_DICT) < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed2.corp-wiki.profile: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-2.hfst $(FI_DICT) < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed2.corp-wiki.profile: corp/kl/klwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-2.hfst $(KL_DICT) < corp/kl/klwiki.$(WORDS).words > /dev/null ;\
	done

# Table 1, ED 3

results/en/table1.dict-norvig.errm-ed3.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-3.hfst $(EN_DICT) < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed3.corp-wiki.lessprofile: corp/fi/fiwiki.$(LESSWORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-3.hfst $(FI_DICT) < corp/fi/fiwiki.$(LESSWORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed3.corp-wiki.lessprofile: corp/kl/klwiki.$(LESSWORDS).words
	echo > $@
	#for i in $(TESTS) ; do \
	#	hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-3.hfst $(KL_DICT) < corp/kl/klwiki.$(LESSWORDS).words > /dev/null ;\
	#done 

# Table 1, ED 1, no initial

results/en/table1.dict-norvig.errm-ed1-no-initial.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-1-no-initial.hfst $(EN_DICT) < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed1-no-initial.corp-wiki.profile: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-1-no-initial.hfst $(FI_DICT) < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed1-no-initial.corp-wiki.profile: corp/kl/klwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-1-no-initial.hfst $(KL_DICT) < corp/kl/klwiki.$(WORDS).words > /dev/null ;\
	done

# Table 1, ED 2, no initial

results/en/table1.dict-norvig.errm-ed2-no-initial.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-2-no-initial.hfst $(EN_DICT) < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed2-no-initial.corp-wiki.profile: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-2-no-initial.hfst $(FI_DICT) < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed2-no-initial.corp-wiki.profile: corp/kl/klwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-2-no-initial.hfst $(KL_DICT) < corp/kl/klwiki.$(WORDS).words > /dev/null ;\
	done

# Table 1, ED 3, no initial

results/en/table1.dict-norvig.errm-ed3-no-initial.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-3-no-initial.hfst $(EN_DICT) < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed3-no-initial.corp-wiki.lessprofile: corp/fi/fiwiki.$(LESSWORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-3-no-initial.hfst $(FI_DICT) < corp/fi/fiwiki.$(LESSWORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed3-no-initial.corp-wiki.lessprofile: corp/kl/klwiki.$(LESSWORDS).words
	echo > $@
	#for i in $(TESTS) ; do \
	#	hfst-ospell-fsmnlp-2012 --profile $@.tsv hfst/kl/errmodel.edit-distance-3-no-initial.hfst $(KL_DICT) < corp/kl/klwiki.$(LESSWORDS).words > /dev/null ;\
	#done

# Table 1, ED 2, eliminate redundancies

results/en/table1.dict-norvig.errm-ed2-no-redundant.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-2.hfst hfst/en/norvig.hfst < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed2-no-redundant.corp-wiki.profile: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-2-no-redundant.hfst $(FI_DICT) < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed2-no-redundant.corp-wiki.profile: corp/kl/klwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-2-no-redundant.hfst $(KL_DICT) < corp/kl/klwiki.$(WORDS).words > /dev/null ;\
	done

# Table 1, ED 3, eliminate redundancies

results/en/table1.dict-norvig.errm-ed3-no-redundant.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-3.hfst $(EN_DICT) < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed3-no-redundant.corp-wiki.lessprofile: corp/fi/fiwiki.$(LESSWORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-3-no-redundant.hfst $(FI_DICT) < corp/fi/fiwiki.$(LESSWORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed3-no-redundant.corp-wiki.lessprofile: corp/kl/klwiki.$(LESSWORDS).words
	echo > $@
	#for i in $(TESTS) ; do \
	#	hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-3-no-redundant.hfst $(KL_DICT) < corp/kl/klwiki.$(LESSWORDS).words > /dev/null ;\
	#done

# Table 1, ED 2, no first and no redundancies

results/en/table1.dict-norvig.errm-ed2-no-initial-no-redundant.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-2-no-initial-no-redundant.hfst hfst/en/norvig.hfst < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed2-no-initial-no-redundant.corp-wiki.profile: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-2-no-initial-no-redundant.hfst $(FI_DICT) < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed2-no-initial-no-redundant.corp-wiki.profile: corp/kl/klwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-2-no-initial-no-redundant.hfst $(KL_DICT) < corp/kl/klwiki.$(WORDS).words > /dev/null ;\
	done

# Table 1, ED 3, no first and no redundancies

results/en/table1.dict-norvig.errm-ed3-no-initial-no-redundant.corp-wiki.lessprofile: corp/en/enwiki.$(LESSWORDS).words
	echo > $@
	#for i in $(TESTS) ; do \
	#	hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-3-no-initial-no-redundant.hfst $(EN_DICT) < corp/en/enwiki.$(LESSWORDS).words > /dev/null ;\
	#done

results/fi/table1.dict-omorfi.errm-ed3-no-initial-no-redundant.corp-wiki.lessprofile: corp/fi/fiwiki.$(LESSWORDS).words
	echo > $@
	#for i in $(TESTS) ; do \
	#	hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-3-no-initial-no-redundant.hfst $(FI_DICT) < corp/fi/fiwiki.$(LESSWORDS).words > /dev/null ;\
	#done

results/kl/table1.dict-kl.errm-ed3-no-initial-no-redundant.corp-wiki.lessprofile: corp/kl/klwiki.$(LESSWORDS).words
	echo > $@
	#for i in $(TESTS) ; do \
	#	hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-3-no-initial-no-redundant.hfst $(KL_DICT) < corp/kl/klwiki.$(LESSWORDS).words > /dev/null ;\
	#done

# Table 1, ED 2, fallback from ED 1 to ED 2 (no redundancies)

results/en/table1.dict-norvig.errm-fallback.corp-wiki.profile: corp/en/enwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-1.hfst hfst/en/errmodel.edit-distance-2.hfst $(EN_DICT) < corp/en/enwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-fallback.corp-wiki.profile: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-1.hfst hfst/fi/errmodel.edit-distance-2.hfst $(FI_DICT) < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-fallback.corp-wiki.profile: corp/kl/klwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-1.hfst hfst/kl/errmodel.edit-distance-2.hfst $(KL_DICT) < corp/kl/klwiki.$(WORDS).words > /dev/null ;\
	done

# Table 1, generate all edits first for ED2

results/en/table1.dict-norvig.errm-ed2.corp-wiki.generate-all.2times: corp/en/enwiki.$(LESSWORDS).words
	echo > $@.time
	for i in $(TESTS) ; do \
		cat corp/en/enwiki.$(LESSWORDS).words |\
		/usr/bin/time -f %U -a -o $@ \
		hfst-optimized-lookup hfst/en/errmodel.edit-distance-2.hfst \
		| cut -f 2  |\
		/usr/bin/time -f %U -a -o $@ \
		hfst-optimized-lookup hfst/en/norvig.hfst > /dev/null ;\
	done

results/fi/table1.dict-omorfi.errm-ed2.corp-wiki.generate-all.2times: corp/fi/fiwiki.$(LESSWORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		cat corp/fi/fiwiki.$(LESSWORDS).words |\
		/usr/bin/time -f %U -a -o $@ \
		hfst-optimized-lookup hfst/fi/errmodel.edit-distance-2.hfst \
		| cut -f 2  |\
		/usr/bin/time -f %U -a -o $@ \
		hfst-optimized-lookup $(FI_DICT) > /dev/null ;\
	done

results/kl/table1.dict-kl.errm-ed2.corp-wiki.generate-all.2times: corp/kl/klwiki.$(LESSWORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		cat corp/kl/klwiki.$(LESSWORDS).words |\
		/usr/bin/time -f %U -a -o $@ \
		hfst-optimized-lookup hfst/kl/errmodel.edit-distance-2.hfst \
		| cut -f 2  |\
		/usr/bin/time -f %U -a -o $@ \
		hfst-optimized-lookup $(KL_DICT) > /dev/null ;\
	done


# (re)generate results in neat tables
# combine all bits and pieces for table 1:
TABLE1_DATA=\
			results/en/table1.dict-hunspell.errm-hunspell.corp-wiki.tex \
			results/fi/table1.dict-voikko.errm-voikko.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed1.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed1.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed1.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed2.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed2.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed2.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed3.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed3.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed3.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed1-no-initial.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed1-no-initial.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed1-no-initial.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed2-no-initial.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed2-no-initial.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed2-no-initial.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed3-no-initial.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed3-no-initial.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed3-no-initial.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed2-no-redundant.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed2-no-redundant.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed2-no-redundant.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed3-no-redundant.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed3-no-redundant.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed3-no-redundant.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-fallback.corp-wiki.tex \
			results/fi/table1.dict-omorfi.errm-fallback.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-fallback.corp-wiki.tex \
			results/en/table1.dict-norvig.errm-ed2.corp-wiki.generate-all.tex \
			results/fi/table1.dict-omorfi.errm-ed2.corp-wiki.generate-all.tex \
			results/kl/table1.dict-kl.errm-ed2.corp-wiki.generate-all.tex \
 			results/en/table1.dict-norvig.errm-ed3-no-redundant.corp-wiki.tex \
 			results/fi/table1.dict-omorfi.errm-ed3-no-redundant.corp-wiki.tex \
 			results/kl/table1.dict-kl.errm-ed3-no-redundant.corp-wiki.tex \
 			results/en/table1.dict-norvig.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
 			results/fi/table1.dict-omorfi.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
 			results/kl/table1.dict-kl.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
			results/kl/table1.dict-kl.errm-foma.corp-wiki.tex



results/table1.tex: $(TABLE1_DATA)
	echo "Reference impl. &" > $@
	paste -d '&' results/en/table1.dict-hunspell.errm-hunspell.corp-wiki.tex \
		results/fi/table1.dict-voikko.errm-voikko.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-foma.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Generate all edits 2 & " >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed2.corp-wiki.generate-all.tex \
		results/fi/table1.dict-omorfi.errm-ed2.corp-wiki.generate-all.tex \
		results/kl/table1.dict-kl.errm-ed2.corp-wiki.generate-all.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "\\hline" >> $@
	echo "Edit distance 1 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed1.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed1.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed1.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 2 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed2.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed2.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed2.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 3 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed3.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed3.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed3.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 1 & " >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed1-no-initial.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed1-no-initial.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed1-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 2 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed2-no-initial.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed2-no-initial.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed2-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 3 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed3-no-initial.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed3-no-initial.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed3-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No redundancy ed 2 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed2-no-redundant.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed2-no-redundant.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed2-no-redundant.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No redundancy ed 3 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed3-no-redundant.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed3-no-redundant.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed3-no-redundant.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No redundancy and firsts ed 2 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed2-no-initial-no-redundant.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No redundancy and firsts ed 3 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed3-no-initial-no-redundant.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Lower order first ed 1 to 2 &" >> $@
	paste -d '&' results/en/table1.dict-norvig.errm-fallback.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-fallback.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-fallback.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@


results/en/table1.%.tex: results/en/table1.%.lessprofile
	awk --assign SCALE=100 -f profile-times2tex.awk < $< > $@

results/en/table1.%.tex: results/en/table1.%.profile
	awk --assign SCALE=1 -f profile-times2tex.awk < $< > $@

results/en/table1.%.tex: results/en/table1.%.times
	awk -f timelist2tex.awk < $< > $@

results/en/table1.%.tex: results/en/table1.%.2times
	awk --assign SCALE=100 -f 2timeslist2tex.awk < $< > $@

results/fi/table1.%.tex: results/fi/table1.%.lessprofile
	awk --assign SCALE=100 -f profile-times2tex.awk < $< > $@

results/fi/table1.%.tex: results/fi/table1.%.profile
	awk --assign SCALE=1 -f profile-times2tex.awk < $< > $@

results/fi/table1.%.tex: results/fi/table1.%.times
	awk -f timelist2tex.awk < $< > $@

results/fi/table1.%.tex: results/fi/table1.%.2times
	awk --assign SCALE=100 -f 2timeslist2tex.awk < $< > $@

results/kl/table1.%.tex: results/kl/table1.%.lessprofile
	awk --assign SCALE=100 -f profile-times2tex.awk < $< > $@

results/kl/table1.%.tex: results/kl/table1.%.profile
	awk --assign SCALE=1 -f profile-times2tex.awk < $< > $@

results/kl/table1.%.tex: results/kl/table1.%.times
	awk -f timelist2tex.awk < $< > $@

results/kl/table1.%.tex: results/kl/table1.%.2times
	awk --assign SCALE=100 -f 2timeslist2tex.awk < $< > $@

# Table 2 (memory)

TABLE2_DATA=\
			results/en/table2.dict-norvig.errm-ed1.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed1.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed1.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed2.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed2.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed2.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed3.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed3.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed3.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed1-no-initial.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed1-no-initial.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed1-no-initial.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed2-no-initial.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed2-no-initial.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed2-no-initial.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed3-no-initial.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed3-no-initial.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed3-no-initial.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed2-no-redundant.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed2-no-redundant.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed2-no-redundant.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed3-no-redundant.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed3-no-redundant.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed3-no-redundant.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
			results/en/table2.dict-norvig.errm-fallback.corp-wiki.tex \
			results/fi/table2.dict-omorfi.errm-fallback.corp-wiki.tex \
			results/kl/table2.dict-kl.errm-fallback.corp-wiki.tex

results/table2.tex: $(TABLE2_DATA)
	#echo "Reference impl. &" > $@
	#paste -d '&' results/en/table2.dict-hunspell.errm-hunspell.corp-wiki.tex \
	#	results/fi/table2.dict-voikko.errm-voikko.corp-wiki.tex >> $@
	#echo "? & ? & --- \\\\\\\\" >> $@
	#echo "Generate all edits 2 & " >> $@
	#paste -d '&' results/en/table2.dict-norvig.errm-ed2.corp-wiki.generate-all.tex \
	#	results/fi/table2.dict-omorfi.errm-ed2.corp-wiki.generate-all.tex \
	#	results/kl/table2.dict-kl.errm-ed2.corp-wiki.generate-all.tex >> $@
	#echo "\\\\\\\\" >> $@
	echo "\\hline" >> $@
	echo "Edit distance 1 &" >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-ed1.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-ed1.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-ed1.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 2 &" >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-ed2.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-ed2.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-ed2.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 3 &" >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-ed3.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-ed3.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-ed3.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 1 & " >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-ed1-no-initial.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-ed1-no-initial.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-ed1-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 2 &" >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-ed2-no-initial.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-ed2-no-initial.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-ed2-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 3 &" >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-ed3-no-initial.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-ed3-no-initial.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-ed3-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No redundancy or firsts ed 2 &" >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-ed2-no-initial-no-redundant.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-ed2-no-initial-no-redundant.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No redundancy or firsts ed 3 &" >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-ed3-no-initial-no-redundant.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-ed3-no-initial-no-redundant.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Lower order first ed 1 to 2 &" >> $@
	paste -d '&' results/en/table2.dict-norvig.errm-fallback.corp-wiki.tex \
		results/fi/table2.dict-omorfi.errm-fallback.corp-wiki.tex \
		results/kl/table2.dict-kl.errm-fallback.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@

# copy results from first table runs
results/en/table2.%.profile: results/en/table1.%.profile
	-rm -f $@
	ln -sf `pwd`/$< $@

results/en/table2.%.lessprofile: results/en/table1.%.lessprofile
	-rm -f $@
	ln -sf `pwd`/$< $@

results/fi/table2.%.profile: results/fi/table1.%.profile
	-rm -f $@
	ln -sf `pwd`/$< $@

results/fi/table2.%.lessprofile: results/fi/table1.%.lessprofile
	-rm -f $@
	ln -sf `pwd`/$< $@

results/kl/table2.%.profile: results/kl/table1.%.profile
	-rm -f $@
	ln -sf `pwd`/$< $@

results/kl/table2.%.lessprofile: results/kl/table1.%.lessprofile
	-rm -f $@
	ln -sf `pwd`/$< $@

# process profiles
results/en/table2.%.tex: results/en/table2.%.profile
	awk -f profile-mems2tex.awk < $< > $@

results/en/table2.%.tex: %.lessprofile
	awk -f profile-mems2tex.awk < $< > $@

results/fi/table2.%.tex: results/fi/table2.%.profile
	awk -f profile-mems2tex.awk < $< > $@

results/fi/table2.%.tex: results/fi/table2.%.lessprofile
	awk -f profile-mems2tex.awk < $< > $@

results/kl/table2.%.tex: results/kl/table2.%.profile
	awk -f profile-mems2tex.awk < $< > $@

results/kl/table2.%.tex: results/kl/table2.%.lessprofile
	awk -f profile-mems2tex.awk < $< > $@


# Table 3 (quality)

TABLE3_DATA=\
			results/en/table3.dict-norvig.errm-ed1.corp-wiki.tex\
			results/fi/table3.dict-omorfi.errm-ed1.corp-wiki.tex\
			results/kl/table3.dict-kl.errm-ed1.corp-wiki.tex \
			results/en/table3.dict-norvig.errm-ed2.corp-wiki.tex \
			results/fi/table3.dict-omorfi.errm-ed2.corp-wiki.tex \
			results/kl/table3.dict-kl.errm-ed2.corp-wiki.tex \
			results/en/table3.dict-norvig.errm-ed3.corp-wiki.tex \
			results/fi/table3.dict-omorfi.errm-ed3.corp-wiki.tex \
			results/kl/table3.dict-kl.errm-ed3.corp-wiki.tex \
			results/en/table3.dict-norvig.errm-ed1-no-initial.corp-wiki.tex \
			results/fi/table3.dict-omorfi.errm-ed1-no-initial.corp-wiki.tex \
			results/kl/table3.dict-kl.errm-ed1-no-initial.corp-wiki.tex \
			results/en/table3.dict-norvig.errm-ed2-no-initial.corp-wiki.tex \
			results/fi/table3.dict-omorfi.errm-ed2-no-initial.corp-wiki.tex \
			results/kl/table3.dict-kl.errm-ed2-no-initial.corp-wiki.tex \
			results/en/table3.dict-norvig.errm-ed3-no-initial.corp-wiki.tex \
			results/fi/table3.dict-omorfi.errm-ed3-no-initial.corp-wiki.tex \
			results/kl/table3.dict-kl.errm-ed3-no-initial.corp-wiki.tex

results/table3.tex: $(TABLE3_DATA)
	#echo "Reference impl. &" > $@
	#paste -d '&' results/en/table1.dict-hunspell.errm-hunspell.corp-wiki.tex \
	#	results/fi/table1.dict-voikko.errm-voikko.corp-wiki.tex >> $@
	#echo "& ---  \\\\\\\\" >> $@
	#echo "Generate all edits 2 & " >> $@
	#paste -d '&' results/en/table3.dict-norvig.errm-ed2.corp-wiki.generate-all.tex \
	#	results/fi/table3.dict-omorfi.errm-ed2.corp-wiki.generate-all.tex \
	#	results/kl/table3.dict-kl.errm-ed2.corp-wiki.generate-all.tex >> $@
	#echo "\\\\\\\\" >> $@
	echo "\\hline" >> $@
	echo "Edit distance 1 &" >> $@
	paste -d '&' results/en/table3.dict-norvig.errm-ed1.corp-wiki.tex \
		results/fi/table3.dict-omorfi.errm-ed1.corp-wiki.tex \
		results/kl/table3.dict-kl.errm-ed1.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 2 &" >> $@
	paste -d '&' results/en/table3.dict-norvig.errm-ed2.corp-wiki.tex \
		results/fi/table3.dict-omorfi.errm-ed2.corp-wiki.tex \
		results/kl/table3.dict-kl.errm-ed2.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 3 &" >> $@
	paste -d '&' results/en/table3.dict-norvig.errm-ed3.corp-wiki.tex \
		results/fi/table3.dict-omorfi.errm-ed3.corp-wiki.tex \
		results/kl/table3.dict-kl.errm-ed3.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 1 & " >> $@
	paste -d '&' results/en/table3.dict-norvig.errm-ed1-no-initial.corp-wiki.tex \
		results/fi/table3.dict-omorfi.errm-ed1-no-initial.corp-wiki.tex \
		results/kl/table3.dict-kl.errm-ed1-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 2 &" >> $@
	paste -d '&' results/en/table3.dict-norvig.errm-ed2-no-initial.corp-wiki.tex \
		results/fi/table3.dict-omorfi.errm-ed2-no-initial.corp-wiki.tex \
		results/kl/table3.dict-kl.errm-ed2-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 3 &" >> $@
	paste -d '&' results/en/table3.dict-norvig.errm-ed3-no-initial.corp-wiki.tex \
		results/fi/table3.dict-omorfi.errm-ed3-no-initial.corp-wiki.tex \
		results/kl/table3.dict-kl.errm-ed3-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@



# Table 3, ED 1

results/en/table3.dict-norvig.errm-ed1.corp-wiki.tex: corp/en/automisp.words
	cut -f 1 corp/en/automisp.words | hfst-ospell-fsmnlp-2012 hfst/en/errmodel.edit-distance-1.hfst hfst/en/norvig.hfst > corp/en/temp_mispell_corrections
	cut -f 2 corp/en/automisp.words | hfst-optimized-lookup hfst/en/norvig.hfst > corp/en/temp_correct_corrections
	cut -f 2 corp/en/automisp.words > corp/en/temp_original_correct_words
	python tally_corrections.py corp/en/temp_mispell_corrections corp/en/temp_correct_corrections corp/en/temp_original_correct_words > $@

results/fi/table3.dict-omorfi.errm-ed1.corp-wiki.tex: corp/fi/automisp.words
	cut -f 1 corp/fi/automisp.words | hfst-ospell-fsmnlp-2012 hfst/fi/errmodel.edit-distance-1.hfst $(FI_DICT) > corp/fi/temp_mispell_corrections
	cut -f 2 corp/fi/automisp.words | hfst-optimized-lookup $(FI_DICT) > corp/fi/temp_correct_corrections
	cut -f 2 corp/fi/automisp.words > corp/fi/temp_original_correct_words
	python tally_corrections.py corp/fi/temp_mispell_corrections corp/fi/temp_correct_corrections corp/fi/temp_original_correct_words > $@

results/kl/table3.dict-kl.errm-ed1.corp-wiki.tex: corp/kl/automisp.words
	cut -f 1 corp/kl/automisp.words | hfst-ospell-fsmnlp-2012 hfst/kl/errmodel.edit-distance-1.hfst $(KL_DICT) > corp/kl/temp_mispell_corrections
	cut -f 2 corp/kl/automisp.words | hfst-optimized-lookup $(KL_DICT) > corp/kl/temp_correct_corrections
	cut -f 2 corp/kl/automisp.words > corp/kl/temp_original_correct_words
	python tally_corrections.py corp/kl/temp_mispell_corrections corp/kl/temp_correct_corrections corp/kl/temp_original_correct_words > $@

# Table 3, ED 2

results/en/table3.dict-norvig.errm-ed2.corp-wiki.tex: corp/en/automisp.words
	cut -f 1 corp/en/automisp.words | hfst-ospell-fsmnlp-2012 hfst/en/errmodel.edit-distance-2.hfst hfst/en/norvig.hfst > corp/en/temp_mispell_corrections
	cut -f 2 corp/en/automisp.words | hfst-optimized-lookup hfst/en/norvig.hfst > corp/en/temp_correct_corrections
	cut -f 2 corp/en/automisp.words > corp/en/temp_original_correct_words
	python tally_corrections.py corp/en/temp_mispell_corrections corp/en/temp_correct_corrections corp/en/temp_original_correct_words > $@

results/fi/table3.dict-omorfi.errm-ed2.corp-wiki.tex: corp/fi/automisp.words
	cut -f 1 corp/fi/automisp.words | hfst-ospell-fsmnlp-2012 hfst/fi/errmodel.edit-distance-2.hfst $(FI_DICT) > corp/fi/temp_mispell_corrections
	cut -f 2 corp/fi/automisp.words | hfst-optimized-lookup $(FI_DICT) > corp/fi/temp_correct_corrections
	cut -f 2 corp/fi/automisp.words > corp/fi/temp_original_correct_words
	python tally_corrections.py corp/fi/temp_mispell_corrections corp/fi/temp_correct_corrections corp/fi/temp_original_correct_words > $@

results/kl/table3.dict-kl.errm-ed2.corp-wiki.tex: corp/kl/automisp.words
	cut -f 1 corp/kl/automisp.words | hfst-ospell-fsmnlp-2012 hfst/kl/errmodel.edit-distance-2.hfst $(KL_DICT) > corp/kl/temp_mispell_corrections
	cut -f 2 corp/kl/automisp.words | hfst-optimized-lookup $(KL_DICT) > corp/kl/temp_correct_corrections
	cut -f 2 corp/kl/automisp.words > corp/kl/temp_original_correct_words
	python tally_corrections.py corp/kl/temp_mispell_corrections corp/kl/temp_correct_corrections corp/kl/temp_original_correct_words > $@

# Table 3, ED 3

results/en/table3.dict-norvig.errm-ed3.corp-wiki.tex: corp/en/automisp.words
	cut -f 1 corp/en/automisp.words | hfst-ospell-fsmnlp-2012 hfst/en/errmodel.edit-distance-3.hfst hfst/en/norvig.hfst > corp/en/temp_mispell_corrections
	cut -f 2 corp/en/automisp.words | hfst-optimized-lookup hfst/en/norvig.hfst > corp/en/temp_correct_corrections
	cut -f 2 corp/en/automisp.words > corp/en/temp_original_correct_words
	python tally_corrections.py corp/en/temp_mispell_corrections corp/en/temp_correct_corrections corp/en/temp_original_correct_words > $@

results/fi/table3.dict-omorfi.errm-ed3.corp-wiki.tex: corp/fi/automisp.words
	echo --- > $@
	#cut -f 1 corp/fi/automisp.words | hfst-ospell-fsmnlp-2012 hfst/fi/errmodel.edit-distance-3.hfst $(FI_DICT) > corp/fi/temp_mispell_corrections
	#cut -f 2 corp/fi/automisp.words | hfst-optimized-lookup $(FI_DICT) > corp/fi/temp_correct_corrections
	#cut -f 2 corp/fi/automisp.words > corp/fi/temp_original_correct_words
	python tally_corrections.py corp/fi/temp_mispell_corrections corp/fi/temp_correct_corrections corp/fi/temp_original_correct_words > $@

results/kl/table3.dict-kl.errm-ed3.corp-wiki.tex: corp/kl/automisp.words
	echo "---" > $@
	#cut -f 1 corp/kl/automisp.words | hfst-ospell-fsmnlp-2012 hfst/kl/errmodel.edit-distance-3.hfst $(KL_DICT) > corp/kl/temp_mispell_corrections
	# cut -f 2 corp/kl/automisp.words | hfst-optimized-lookup $(KL_DICT) > corp/kl/temp_correct_corrections
	#cut -f 2 corp/kl/automisp.words > corp/kl/temp_original_correct_words
	#python tally_corrections.py corp/kl/temp_mispell_corrections corp/kl/temp_correct_corrections corp/kl/temp_original_correct_words > $@

# Table 3, ED 1, no initial

results/en/table3.dict-norvig.errm-ed1-no-initial.corp-wiki.tex: corp/en/automisp.words
	cut -f 1 corp/en/automisp.words | hfst-ospell-fsmnlp-2012 hfst/en/errmodel.edit-distance-1-no-initial.hfst hfst/en/norvig.hfst > corp/en/temp_mispell_corrections
	cut -f 2 corp/en/automisp.words | hfst-optimized-lookup hfst/en/norvig.hfst > corp/en/temp_correct_corrections
	cut -f 2 corp/en/automisp.words > corp/en/temp_original_correct_words
	python tally_corrections.py corp/en/temp_mispell_corrections corp/en/temp_correct_corrections corp/en/temp_original_correct_words > $@

results/fi/table3.dict-omorfi.errm-ed1-no-initial.corp-wiki.tex: corp/fi/automisp.words
	cut -f 1 corp/fi/automisp.words | hfst-ospell-fsmnlp-2012 hfst/fi/errmodel.edit-distance-1-no-initial.hfst $(FI_DICT) > corp/fi/temp_mispell_corrections
	cut -f 2 corp/fi/automisp.words | hfst-optimized-lookup $(FI_DICT) > corp/fi/temp_correct_corrections
	cut -f 2 corp/fi/automisp.words > corp/fi/temp_original_correct_words
	python tally_corrections.py corp/fi/temp_mispell_corrections corp/fi/temp_correct_corrections corp/fi/temp_original_correct_words > $@

results/kl/table3.dict-kl.errm-ed1-no-initial.corp-wiki.tex: corp/kl/automisp.words
	cut -f 1 corp/kl/automisp.words | hfst-ospell-fsmnlp-2012 hfst/kl/errmodel.edit-distance-1-no-initial.hfst $(KL_DICT) > corp/kl/temp_mispell_corrections
	cut -f 2 corp/kl/automisp.words | hfst-optimized-lookup $(KL_DICT) > corp/kl/temp_correct_corrections
	cut -f 2 corp/kl/automisp.words > corp/kl/temp_original_correct_words
	python tally_corrections.py corp/kl/temp_mispell_corrections corp/kl/temp_correct_corrections corp/kl/temp_original_correct_words > $@

# Table 3, ED 2, no initial

results/en/table3.dict-norvig.errm-ed2-no-initial.corp-wiki.tex: corp/en/automisp.words
	cut -f 1 corp/en/automisp.words | hfst-ospell-fsmnlp-2012 hfst/en/errmodel.edit-distance-2-no-initial.hfst hfst/en/norvig.hfst > corp/en/temp_mispell_corrections
	cut -f 2 corp/en/automisp.words | hfst-optimized-lookup hfst/en/norvig.hfst > corp/en/temp_correct_corrections
	cut -f 2 corp/en/automisp.words > corp/en/temp_original_correct_words
	python tally_corrections.py corp/en/temp_mispell_corrections corp/en/temp_correct_corrections corp/en/temp_original_correct_words > $@

results/fi/table3.dict-omorfi.errm-ed2-no-initial.corp-wiki.tex: corp/fi/automisp.words
	cut -f 1 corp/fi/automisp.words | hfst-ospell-fsmnlp-2012 hfst/fi/errmodel.edit-distance-2-no-initial.hfst $(FI_DICT) > corp/fi/temp_mispell_corrections
	cut -f 2 corp/fi/automisp.words | hfst-optimized-lookup $(FI_DICT) > corp/fi/temp_correct_corrections
	cut -f 2 corp/fi/automisp.words > corp/fi/temp_original_correct_words
	python tally_corrections.py corp/fi/temp_mispell_corrections corp/fi/temp_correct_corrections corp/fi/temp_original_correct_words > $@

results/kl/table3.dict-kl.errm-ed2-no-initial.corp-wiki.tex: corp/kl/automisp.words
	cut -f 1 corp/kl/automisp.words | hfst-ospell-fsmnlp-2012 hfst/kl/errmodel.edit-distance-2-no-initial.hfst $(KL_DICT) > corp/kl/temp_mispell_corrections
	cut -f 2 corp/kl/automisp.words | hfst-optimized-lookup $(KL_DICT) > corp/kl/temp_correct_corrections
	cut -f 2 corp/kl/automisp.words > corp/kl/temp_original_correct_words
	python tally_corrections.py corp/kl/temp_mispell_corrections corp/kl/temp_correct_corrections corp/kl/temp_original_correct_words > $@

# Table 3, ED 3, no initial

results/en/table3.dict-norvig.errm-ed3-no-initial.corp-wiki.tex: corp/en/automisp.words
	cut -f 1 corp/en/automisp.words | hfst-ospell-fsmnlp-2012 hfst/en/errmodel.edit-distance-3-no-initial.hfst hfst/en/norvig.hfst > corp/en/temp_mispell_corrections
	cut -f 2 corp/en/automisp.words | hfst-optimized-lookup hfst/en/norvig.hfst > corp/en/temp_correct_corrections
	cut -f 2 corp/en/automisp.words > corp/en/temp_original_correct_words
	python tally_corrections.py corp/en/temp_mispell_corrections corp/en/temp_correct_corrections corp/en/temp_original_correct_words > $@

results/fi/table3.dict-omorfi.errm-ed3-no-initial.corp-wiki.tex: corp/fi/automisp.words
	echo --- > $@
	#cut -f 1 corp/fi/automisp.words | hfst-ospell-fsmnlp-2012 hfst/fi/errmodel.edit-distance-3-no-initial.hfst $(FI_DICT) > corp/fi/temp_mispell_corrections
	#cut -f 2 corp/fi/automisp.words | hfst-optimized-lookup $(FI_DICT) > corp/fi/temp_correct_corrections
	#cut -f 2 corp/fi/automisp.words > corp/fi/temp_original_correct_words
	#python tally_corrections.py corp/fi/temp_mispell_corrections corp/fi/temp_correct_corrections corp/fi/temp_original_correct_words > $@

results/kl/table3.dict-kl.errm-ed3-no-initial.corp-wiki.tex: corp/kl/automisp.words
	echo "---" > $@
	#cut -f 1 corp/kl/automisp.words | hfst-ospell-fsmnlp-2012 hfst/kl/errmodel.edit-distance-3-no-initial.hfst $(KL_DICT) > corp/kl/temp_mispell_corrections
	#cut -f 2 corp/kl/automisp.words | hfst-optimized-lookup $(KL_DICT) > corp/kl/temp_correct_corrections
	#cut -f 2 corp/kl/automisp.words > corp/kl/temp_original_correct_words
	#python tally_corrections.py corp/kl/temp_mispell_corrections corp/kl/temp_correct_corrections corp/kl/temp_original_correct_words > $@

# Table 4 (text type vs. speed)

TABLE4_DATA=\
			results/en/table4.dict-norvig.errm-ed2-no-initial.corp-wiki-automispelled.tex\
			results/fi/table4.dict-omorfi.errm-ed2-no-initial.corp-wiki-automispelled.tex\
			results/kl/table4.dict-kl.errm-ed2-no-initial.corp-wiki-automispelled.tex \
			results/en/table4.dict-norvig.errm-ed2-no-initial.corp-wiki-wronglang.tex\
			results/fi/table4.dict-omorfi.errm-ed2-no-initial.corp-wiki-wronglang.tex\
			results/kl/table4.dict-kl.errm-ed2-no-initial.corp-wiki-wronglang.tex

results/table4.tex: $(TABLE1_DATA) $(TABLE4_DATA)
	# this baseline is from test table 1
	echo "Native Lang. Corpus &" > $@
	paste -d '&' results/en/table1.dict-norvig.errm-ed2-no-initial.corp-wiki.tex \
		results/fi/table1.dict-omorfi.errm-ed2-no-initial.corp-wiki.tex \
		results/kl/table1.dict-kl.errm-ed2-no-initial.corp-wiki.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Added automatic errors &" >> $@
	paste -d '&' results/en/table4.dict-norvig.errm-ed2-no-initial.corp-wiki-automispelled.tex \
		results/fi/table4.dict-omorfi.errm-ed2-no-initial.corp-wiki-automispelled.tex \
		results/kl/table4.dict-kl.errm-ed2-no-initial.corp-wiki-automispelled.tex >> $@
	echo "\\\\\\\\" >> $@
	echo "Text in another language &" >> $@
	paste -d '&' results/en/table4.dict-norvig.errm-ed2-no-initial.corp-wiki-wronglang.tex \
		results/fi/table4.dict-omorfi.errm-ed2-no-initial.corp-wiki-wronglang.tex \
		results/kl/table4.dict-kl.errm-ed2-no-initial.corp-wiki-wronglang.tex >> $@
	echo "\\\\\\\\" >> $@

# Automispelled

results/en/table4.dict-norvig.errm-ed2-no-initial.corp-wiki-automispelled.profile: corp/en/automisp.words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-2-no-initial.hfst hfst/en/norvig.hfst < corp/en/automisp.words > /dev/null ;\
	done

results/fi/table4.dict-omorfi.errm-ed2-no-initial.corp-wiki-automispelled.profile: corp/fi/automisp.words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-2-no-initial.hfst $(FI_DICT) < corp/fi/automisp.words > /dev/null ;\
	done

results/kl/table4.dict-kl.errm-ed2-no-initial.corp-wiki-automispelled.profile: corp/kl/automisp.words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-2-no-initial.hfst $(KL_DICT) < corp/kl/automisp.words > /dev/null ;\
	done

# Wrong language

results/en/table4.dict-norvig.errm-ed2-no-initial.corp-wiki-wronglang.profile: corp/fi/fiwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/en/errmodel.edit-distance-2.hfst hfst/en/norvig.hfst < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/fi/table4.dict-omorfi.errm-ed2-no-initial.corp-wiki-wronglang.profile: corp/kl/klwiki.$(WORDS).words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/fi/errmodel.edit-distance-2-no-initial.hfst $(FI_DICT) < corp/kl/klwiki.$(WORDS).words > /dev/null ;\
	done

results/kl/table4.dict-kl.errm-ed2-no-initial.corp-wiki-wronglang.profile: corp/fi/automisp.words
	echo > $@
	for i in $(TESTS) ; do \
		hfst-ospell-fsmnlp-2012 --profile $@ hfst/kl/errmodel.edit-distance-2-no-initial.hfst $(KL_DICT) < corp/fi/fiwiki.$(WORDS).words > /dev/null ;\
	done

results/en/table4.%.tex: results/en/table4.%.lessprofile
	awk --assign SCALE=100 -f profile-times2tex.awk < $< > $@

results/en/table4.%.tex: results/en/table4.%.profile
	awk --assign SCALE=1 -f profile-times2tex.awk < $< > $@

results/en/table4.%.tex: results/en/table4.%.times
	awk -f timelist2tex.awk < $< > $@

results/en/table4.%.tex: results/en/table4.%.2times
	awk --assign SCALE=100 -f 2timeslist2tex.awk < $< > $@

results/fi/table4.%.tex: results/fi/table4.%.lessprofile
	awk --assign SCALE=100 -f profile-times2tex.awk < $< > $@

results/fi/table4.%.tex: results/fi/table4.%.profile
	awk --assign SCALE=1 -f profile-times2tex.awk < $< > $@

results/fi/table4.%.tex: results/fi/table4.%.times
	awk -f timelist2tex.awk < $< > $@

results/fi/table4.%.tex: results/fi/table4.%.2times
	awk --assign SCALE=100 -f 2timeslist2tex.awk < $< > $@

results/kl/table4.%.tex: results/kl/table4.%.lessprofile
	awk --assign SCALE=100 -f profile-times2tex.awk < $< > $@

results/kl/table4.%.tex: results/kl/table4.%.profile
	awk --assign SCALE=1 -f profile-times2tex.awk < $< > $@

results/kl/table4.%.tex: results/kl/table4.%.times
	awk -f timelist2tex.awk < $< > $@

results/kl/table4.%.tex: results/kl/table4.%.2times
	awk --assign SCALE=100 -f 2timeslist2tex.awk < $< > $@

# table 5 and such
TABLE5_DATA=\
			results/en/table5.norvig.sigmasetsize \
			results/fi/table5.omorfi-20110505.sigmasetsize \
			results/kl/table5.kl.sigmasetsize  \
			results/en/table5.norvig.states \
			results/fi/table5.omorfi-20110505.states \
			results/kl/table5.kl.states \
			results/en/table5.norvig.arcs \
			results/fi/table5.omorfi-20110505.arcs \
			results/kl/table5.kl.arcs

TABLE6_DATA=results/en/table6.errmodel.edit-distance-1.sigmasetsize\
			results/fi/table6.errmodel.edit-distance-1.sigmasetsize\
			results/kl/table6.errmodel.edit-distance-1.sigmasetsize\
			results/en/table6.errmodel.edit-distance-1.states \
			results/en/table6.errmodel.edit-distance-1-no-initial.states \
			results/en/table6.errmodel.edit-distance-2.states \
			results/en/table6.errmodel.edit-distance-2-no-initial.states \
			results/en/table6.errmodel.edit-distance-2-no-initial-no-redundant.states \
			results/en/table6.errmodel.edit-distance-2-no-redundant.states \
			results/en/table6.errmodel.edit-distance-3.states \
			results/en/table6.errmodel.edit-distance-3-no-initial.states \
			results/en/table6.errmodel.edit-distance-3-no-initial-no-redundant.states \
			results/en/table6.errmodel.edit-distance-3-no-redundant.states \
			results/fi/table6.errmodel.edit-distance-1.states \
			results/fi/table6.errmodel.edit-distance-1-no-initial.states \
			results/fi/table6.errmodel.edit-distance-2.states \
			results/fi/table6.errmodel.edit-distance-2-no-initial.states \
			results/fi/table6.errmodel.edit-distance-2-no-initial-no-redundant.states \
			results/fi/table6.errmodel.edit-distance-2-no-redundant.states \
			results/fi/table6.errmodel.edit-distance-3.states \
			results/fi/table6.errmodel.edit-distance-3-no-initial.states \
			results/fi/table6.errmodel.edit-distance-3-no-initial-no-redundant.states \
			results/fi/table6.errmodel.edit-distance-3-no-redundant.states \
			results/kl/table6.errmodel.edit-distance-1.states \
			results/kl/table6.errmodel.edit-distance-1-no-initial.states \
			results/kl/table6.errmodel.edit-distance-2.states \
			results/kl/table6.errmodel.edit-distance-2-no-initial.states \
			results/kl/table6.errmodel.edit-distance-2-no-initial-no-redundant.states \
			results/kl/table6.errmodel.edit-distance-2-no-redundant.states \
			results/kl/table6.errmodel.edit-distance-3.states \
			results/kl/table6.errmodel.edit-distance-3-no-initial.states \
			results/kl/table6.errmodel.edit-distance-3-no-initial-no-redundant.states \
			results/kl/table6.errmodel.edit-distance-3-no-redundant.states \
			results/en/table6.errmodel.edit-distance-1.arcs \
			results/en/table6.errmodel.edit-distance-1-no-initial.arcs \
			results/en/table6.errmodel.edit-distance-2.arcs \
			results/en/table6.errmodel.edit-distance-2-no-initial.arcs \
			results/en/table6.errmodel.edit-distance-2-no-initial-no-redundant.arcs \
			results/en/table6.errmodel.edit-distance-2-no-redundant.arcs \
			results/en/table6.errmodel.edit-distance-3.arcs \
			results/en/table6.errmodel.edit-distance-3-no-initial.arcs \
			results/en/table6.errmodel.edit-distance-3-no-initial-no-redundant.arcs \
			results/en/table6.errmodel.edit-distance-3-no-redundant.arcs \
			results/fi/table6.errmodel.edit-distance-1.arcs \
			results/fi/table6.errmodel.edit-distance-1-no-initial.arcs \
			results/fi/table6.errmodel.edit-distance-2.arcs \
			results/fi/table6.errmodel.edit-distance-2-no-initial.arcs \
			results/fi/table6.errmodel.edit-distance-2-no-initial-no-redundant.arcs \
			results/fi/table6.errmodel.edit-distance-2-no-redundant.arcs \
			results/fi/table6.errmodel.edit-distance-3.arcs \
			results/fi/table6.errmodel.edit-distance-3-no-initial.arcs \
			results/fi/table6.errmodel.edit-distance-3-no-initial-no-redundant.arcs \
			results/fi/table6.errmodel.edit-distance-3-no-redundant.arcs \
			results/kl/table6.errmodel.edit-distance-1.arcs \
			results/kl/table6.errmodel.edit-distance-1-no-initial.arcs \
			results/kl/table6.errmodel.edit-distance-2.arcs \
			results/kl/table6.errmodel.edit-distance-2-no-initial.arcs \
			results/kl/table6.errmodel.edit-distance-2-no-initial-no-redundant.arcs \
			results/kl/table6.errmodel.edit-distance-2-no-redundant.arcs \
			results/kl/table6.errmodel.edit-distance-3.arcs \
			results/kl/table6.errmodel.edit-distance-3-no-initial.arcs \
			results/kl/table6.errmodel.edit-distance-3-no-initial-no-redundant.arcs \
			results/kl/table6.errmodel.edit-distance-3-no-redundant.arcs


results/table5.tex: $(TABLE5_DATA)
	echo "$$\\\\Sigma$$ set size &" > $@
	paste -d '&' results/en/table5.norvig.sigmasetsize \
		results/fi/table5.omorfi-20110505.sigmasetsize \
		results/kl/table5.kl.sigmasetsize >> $@
	echo "\\\\\\\\" >> $@
	echo "Dictionary FSM nodes &" >> $@
	paste -d '&' results/en/table5.norvig.states \
		results/fi/table5.omorfi-20110505.states \
		results/kl/table5.kl.states >> $@
	echo "\\\\\\\\" >> $@
	echo "Dictionary FSM arcs &" >> $@
	paste -d '&' results/en/table5.norvig.arcs \
		results/fi/table5.omorfi-20110505.arcs \
		results/kl/table5.kl.arcs >> $@
	echo "\\\\\\\\" >> $@
	echo "Dictionary FSM on HDD & " >> $@
	ls -sh $(EN_DICT) | cut -d ' ' -f 1 | sed -e 's/$$/iB \\&/' >> $@
	ls -sh $(FI_DICT) | cut -d ' ' -f 1 | sed -e 's/$$/iB \\&/' >> $@
	ls -sh $(KL_DICT) | cut -d ' ' -f 1 | sed -e 's/$$/iB \\&/' >> $@
	echo "\\\\\\\\" >> $@


results/table6.tex: $(TABLE6_DATA)
	echo "$$\\\\Sigma$$ set size &" > $@
	paste -d '&' results/en/table6.errmodel.edit-distance-1.sigmasetsize \
		results/fi/table6.errmodel.edit-distance-1.sigmasetsize \
		results/kl/table6.errmodel.edit-distance-1.sigmasetsize >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 1 nodes &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-1.states \
		results/fi/table6.errmodel.edit-distance-1.states \
		results/kl/table6.errmodel.edit-distance-1.states >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 1 arcs &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-1.arcs \
		results/fi/table6.errmodel.edit-distance-1.arcs \
		results/kl/table6.errmodel.edit-distance-1.arcs >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 2 nodes &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-2.states \
		results/fi/table6.errmodel.edit-distance-2.states \
		results/kl/table6.errmodel.edit-distance-2.states >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 2 arcs &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-2.arcs \
		results/fi/table6.errmodel.edit-distance-2.arcs \
		results/kl/table6.errmodel.edit-distance-2.arcs >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 3 nodes &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-3.states \
		results/fi/table6.errmodel.edit-distance-3.states \
		results/kl/table6.errmodel.edit-distance-3.states >> $@
	echo "\\\\\\\\" >> $@
	echo "Edit distance 3 arcs &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-3.arcs \
		results/fi/table6.errmodel.edit-distance-3.arcs \
		results/kl/table6.errmodel.edit-distance-3.arcs >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 1 nodes & " >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-1-no-initial.states \
		results/fi/table6.errmodel.edit-distance-1-no-initial.states \
		results/kl/table6.errmodel.edit-distance-1-no-initial.states >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 1 arcs & " >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-1-no-initial.arcs \
		results/fi/table6.errmodel.edit-distance-1-no-initial.arcs \
		results/kl/table6.errmodel.edit-distance-1-no-initial.arcs >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 2 nodes &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-2-no-initial.states \
		results/fi/table6.errmodel.edit-distance-2-no-initial.states \
		results/kl/table6.errmodel.edit-distance-2-no-initial.states >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 2 arcs &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-2-no-initial.arcs \
		results/fi/table6.errmodel.edit-distance-2-no-initial.arcs \
		results/kl/table6.errmodel.edit-distance-2-no-initial.arcs >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 3 nodes &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-3-no-initial.states \
		results/fi/table6.errmodel.edit-distance-3-no-initial.states \
		results/kl/table6.errmodel.edit-distance-3-no-initial.states >> $@
	echo "\\\\\\\\" >> $@
	echo "No firsts ed 3 arcs &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-3-no-initial.arcs \
		results/fi/table6.errmodel.edit-distance-3-no-initial.arcs \
		results/kl/table6.errmodel.edit-distance-3-no-initial.arcs >> $@
	echo "\\\\\\\\" >> $@
	echo "No redundancy and firsts ed 2 nodes &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-2-no-initial-no-redundant.states \
		results/fi/table6.errmodel.edit-distance-2-no-initial-no-redundant.states \
		results/kl/table6.errmodel.edit-distance-2-no-initial-no-redundant.states >> $@
	echo "\\\\\\\\" >> $@
	echo "No redundancy and firsts ed 2 arcs &" >> $@
	paste -d '&' results/en/table6.errmodel.edit-distance-2-no-initial-no-redundant.arcs \
		results/fi/table6.errmodel.edit-distance-2-no-initial-no-redundant.arcs \
		results/kl/table6.errmodel.edit-distance-2-no-initial-no-redundant.arcs >> $@
	echo "\\\\\\\\" >> $@
	#echo "No redundancy and firsts ed 3 nodes &" >> $@
	#paste -d '&' results/en/table6.errmodel.edit-distance-3-no-initial-no-redundant.states \
	#	results/fi/table6.errmodel.edit-distance-3-no-initial-no-redundant.states \
	#	results/kl/table6.errmodel.edit-distance-3-no-initial-no-redundant.states >> $@
	#echo "\\\\\\\\" >> $@
	#echo "No redundancy and firsts ed 3 arcs &" >> $@
	#paste -d '&' results/en/table6.errmodel.edit-distance-3-no-initial-no-redundant.arcs \
	#	results/fi/table6.errmodel.edit-distance-3-no-initial-no-redundant.arcs \
	#	results/kl/table6.errmodel.edit-distance-3-no-initial-no-redundant.arcs >> $@
	#echo "\\\\\\\\" >> $@
	echo "Lower order first ed 1 to 2 arcs &" >> $@
	echo "add & above & rows" >> $@
	echo "\\\\\\\\" >> $@
	echo "Lower order first ed 1 to 2 nodes &" >> $@
	echo "add & above & rows" >> $@
	echo "\\\\\\\\" >> $@

results/en/table6.%.sigmasetsize: hfst/en/%.hfst
	hfst-summarize -v $< |\
		fgrep 'sigma set size' |\
		sed -e 's/^.*://' > $@

results/fi/table6.%.sigmasetsize: hfst/fi/%.hfst
	hfst-summarize -v $< |\
		fgrep 'sigma set size' |\
		sed -e 's/^.*://' > $@

results/kl/table6.%.sigmasetsize: hfst/kl/%.hfst
	hfst-summarize -v $< |\
		fgrep 'sigma set size' |\
		sed -e 's/^.*://' > $@


results/en/table6.%.states: hfst/en/%.hfst
	hfst-summarize $< |\
		fgrep '# of states' |\
		sed -e 's/^.*://' > $@

results/fi/table6.%.states: hfst/fi/%.hfst
	hfst-summarize $< |\
		fgrep '# of states' |\
		sed -e 's/^.*://' > $@

results/kl/table6.%.states: hfst/kl/%.hfst
	hfst-summarize $< |\
		fgrep '# of states' |\
		sed -e 's/^.*://' > $@


results/en/table6.%.arcs: hfst/en/%.hfst
	hfst-summarize $< |\
		fgrep '# of arcs' |\
		sed -e 's/^.*://' > $@

results/fi/table6.%.arcs: hfst/fi/%.hfst
	hfst-summarize $< |\
		fgrep '# of arcs' |\
		sed -e 's/^.*://' > $@

results/kl/table6.%.arcs: hfst/kl/%.hfst
	hfst-summarize $< |\
		fgrep '# of arcs' |\
		sed -e 's/^.*://' > $@




results/en/table5.%.sigmasetsize: hfst/en/%.hfst
	hfst-summarize -v $< |\
		fgrep 'sigma set size' |\
		sed -e 's/^.*://' > $@

results/fi/table5.%.sigmasetsize: hfst/fi/%.hfst
	hfst-summarize -v $< |\
		fgrep 'sigma set size' |\
		sed -e 's/^.*://' > $@

results/kl/table5.%.sigmasetsize: hfst/kl/%.hfst
	hfst-summarize -v $< |\
		fgrep 'sigma set size' |\
		sed -e 's/^.*://' > $@

results/en/table5.%.states: hfst/en/%.hfst
	hfst-summarize $< |\
		fgrep '# of states' |\
		sed -e 's/^.*://' > $@

results/fi/table5.%.states: hfst/fi/%.hfst
	hfst-summarize $< |\
		fgrep '# of states' |\
		sed -e 's/^.*://' > $@

results/kl/table5.%.states: hfst/kl/%.hfst
	hfst-summarize $< |\
		fgrep '# of states' |\
		sed -e 's/^.*://' > $@


results/en/table5.%.arcs: hfst/en/%.hfst
	hfst-summarize $< |\
		fgrep '# of arcs' |\
		sed -e 's/^.*://' > $@

results/fi/table5.%.arcs: hfst/fi/%.hfst
	hfst-summarize $< |\
		fgrep '# of arcs' |\
		sed -e 's/^.*://' > $@

results/kl/table5.%.arcs: hfst/kl/%.hfst
	hfst-summarize $< |\
		fgrep '# of arcs' |\
		sed -e 's/^.*://' > $@



## misc: proof of morphological complexity

UNDHR_EN=undhr.txt.en
UNDHR_FI=undhr.txt.fi
UNDHR_KL=undhr.txt.kl
UNDHR_TARGETS=undhr.wordforms.fi undhr.wordforms.en undhr.wordforms.kl\
			  undhr.tokencounts.fi undhr.tokencounts.en undhr.tokencounts.kl\
			  undhr.wordlengths.fi undhr.wordlengths.en undhr.wordlengths.kl

morphological-complexity: $(UNDHR_TARGETS)

undhr.norm.%: undhr.txt.%
	tr [:upper:] [:lower:] < $< |\
		tr -s [:space:] '\n' > $@

undhr.wordforms.%: undhr.norm.%
	wc -l < $< > $@

undhr.wordlengths.%: undhr.norm.%
	python3 countwordlengths.py $< $@

undhr.tokencounts.%: undhr.norm.%
	sort < $< | uniq -c | sort -nr > $@

undhr.morphcount.fi: undhr.txt.fi
	omorfi-analyse.sh $< > $@
