## Use make to create article pdfs or recreate test results

TEX=xelatex
BIB=bibtex
SCP=scp
SCPHOST=ruuvi
SCPDIR=public_html/tmp/
PAPER_SOURCES=cicling-2011-contextspell.tex cicling2011.bib
PAPER_PDF=cicling-2011-contextspell.pdf

ERROR_CORPORA=en-US.autogen.contextspell en-US.birkbeck.contextspell fi-FI.autogen.contextspell fi-FI.fiwiki-gutenberg.contextspell norvig1.contextspell norvig2.contextspell
DOCS=README LICENCE

cicling-2011-contextspell.pdf: cicling-2011-contextspell.tex cicling2011.bib
	$(TEX) cicling-2011-contextspell.tex
	$(BIB) cicling-2011-contextspell
	$(TEX) cicling-2011-contextspell.tex
	$(TEX) cicling-2011-contextspell.tex
	$(TEX) cicling-2011-contextspell.tex

# dictionary and edit distance targets
OMORFI=hfst/fi
NORVIG=hfst/en

# locally installed dictionarise
prefix=/usr/local
sharedir=$(prefix)/share

# context model targets
CONTEXT_SPELLER=bin/context_speller 
EN_TAGGER=taggers/en/hmm_model.lex taggers/en/hmm_model.seq
FI_TAGGER=taggers/fin/hmm_model.lex taggers/fin/hmm_model.seq

# parameters
UNIGRAM_BACKOFF=5.2667
# 6.90878 = -log(1/1000) i.e. one typo per 1000 words
ERROR_PROBABILITY=6.9078
FI_SCALE=10
EN_SCALE=0.85

$(OMORFI):
	mkdir -p $@

$(NORVIG):
	mkdir -p $@

.PHONY: automata automata-fi automata-en results results-fi results-en textables textables-fi textables-en context_speller context-results upload

# rulem amiking stuff
context_speller: bin/context_speller
bin/context_speller:
	$(MAKE) -C src/ install

automata: automata-fi automata-en

automata-fi: $(OMORFI)/dictionary.limited.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/error.edit-distance-2-huge.hfst

automata-en: $(NORVIG)/dictionary.default.hfst $(NORVIG)/edit-distance-2.hfst

# finnish automata; gather dictionares from omorfi


$(OMORFI)/dictionary.limited.hfst: $(sharedir)/hfst/fi/dictionary.filtered.hfst $(OMORFI)/dictionary.fiwiki.hfst
	hfst-fst2fst $(sharedir)/hfst/fi/dictionary.filtered.hfst -f openfst-tropical |\
		hfst-reweight -e -a $(UNIGRAM_BACKOFF) |\
		hfst-union $(OMORFI)/dictionary.fiwiki.hfst |\
		hfst-minimize |\
		hfst-fst2fst -f  olw -o $@

# ensure current svn revision with boundary weighting
$(OMORFI)/dictionary.default-boundaryweight-medium.hfst: $(sharedir)/hfst/fi/dictionary.default.hfst $(OMORFI)/dictionary.fiwiki.hfst
	hfst-fst2fst $(sharedir)/hfst/fi/dictionary.default.hfst -f openfst-tropical |\
		hfst-reweight -e -a $(UNIGRAM_BACKOFF) |\
		hfst-union $(OMORFI)/dictionary.fiwiki.hfst |\
		hfst-minimize |\
		hfst-fst2fst -f  olw -o $@

$(OMORFI)/dictionary.default-boundaryweight-small.hfst: $(sharedir)/hfst/fi/dictionary.default.hfst $(OMORFI)/dictionary.fiwiki.hfst
	hfst-fst2fst $(sharedir)/hfst/fi/dictionary.default.hfst -f openfst-tropical |\
		hfst-reweight -b 0.01 |\
		hfst-reweight -e -a $(UNIGRAM_BACKOFF) |\
		hfst-union $(OMORFI)/dictionary.fiwiki.hfst |\
		hfst-minimize |\
		hfst-fst2fst -f  olw -o $@

$(OMORFI)/dictionary.default-boundaryweight-huge.hfst: $(sharedir)/hfst/fi/dictionary.default.hfst $(OMORFI)/dictionary.fiwiki.hfst
	hfst-fst2fst $(sharedir)/hfst/fi/dictionary.default.hfst -f openfst-tropical |\
		hfst-reweight -b 100 |\
		hfst-reweight -e -a $(UNIGRAM_BACKOFF) |\
		hfst-union $(OMORFI)/dictionary.fiwiki.hfst |\
		hfst-minimize |\
		hfst-fst2fst -f  olw -o $@

$(OMORFI)/dictionary.default-boundaryweight-none.hfst: $(sharedir)/hfst/fi/dictionary.default.hfst $(OMORFI)/dictionary.fiwiki.hfst
	hfst-fst2fst $(sharedir)/hfst/fi/dictionary.default.hfst -f openfst-tropical |\
		hfst-reweight -b 0 |\
		hfst-reweight -e -a $(UNIGRAM_BACKOFF) |\
		hfst-union $(OMORFI)/dictionary.fiwiki.hfst |\
		hfst-minimize |\
		hfst-fst2fst -f  olw -o $@

$(OMORFI)/dictionary.fiwiki.hfst: fiwiki.strings
	sort < fiwiki.strings | uniq -c | sort -nr > train
	awk -f tropicalize-uniq-c.awk --assign CS=`wc -l < fiwiki.strings` < train > tropical
	hfst-strings2fst -j -f openfst-tropical tropical -v |\
		hfst-minimize -v -o $@


$(OMORFI)/error.edit-distance-2-medium.hfst:  edit-distance.bash
	./edit-distance.bash 2 $(ERROR_PROBABILITY) a b c d e f g h i j k l m n o p q r s š t u v w x y z ž å ä ö |\
		hfst-txt2fst -v -f openfst-tropical |\
		hfst-minimize -v |\
		hfst-fst2fst -v -f olw -o $@

$(OMORFI)/error.edit-distance-2-small.hfst:  edit-distance.bash
	./edit-distance.bash 2 0.69078 a b c d e f g h i j k l m n o p q r s š t u v w x y z ž å ä ö |\
		hfst-txt2fst -v -f openfst-tropical |\
		hfst-minimize -v |\
		hfst-fst2fst -v -f olw -o $@

$(OMORFI)/error.edit-distance-2-none.hfst:  edit-distance.bash
	./edit-distance.bash 2 0.0 a b c d e f g h i j k l m n o p q r s š t u v w x y z ž å ä ö |\
		hfst-txt2fst -v -f openfst-tropical |\
		hfst-minimize -v |\
		hfst-fst2fst -v -f olw -o $@

$(OMORFI)/error.edit-distance-2-huge.hfst: edit-distance.bash
	./edit-distance.bash 2 690.78 a b c d e f g h i j k l m n o p q r s š t u v w x y z ž å ä ö |\
		hfst-txt2fst -v -f openfst-tropical |\
		hfst-minimize -v |\
		hfst-fst2fst -v -f olw -o $@

# english automata
# norvig's statistic dictionary
big.txt:
	wget http://norvig.com/big.txt

$(NORVIG)/dictionary.default-none.hfst: big.txt tropicalize-uniq-c.awk
	tr -s '[:punct:][:digit:]' ' ' < $< | tr -s '[:space:]' '\n' | tr '[:upper:]' '[:lower:]' > words
	sort < words | uniq -c | sort -nr > train
	awk -f tropicalize-uniq-c.awk --assign CS=`wc -l < words` < train > tropical
	hfst-strings2fst -j -f openfst-tropical tropical -v |\
		hfst-reweight -a 0 -b 0 |\
		hfst-minimize -v |\
		hfst-fst2fst -v -f olw -o $@

$(NORVIG)/error.edit-distance-2-none.hfst: edit-distance.bash 
	./edit-distance.bash 2 0 a b c d e f g h i j k l m n o p q r s t u v w x y z |\
		hfst-txt2fst -v -f openfst-tropical |\
		hfst-minimize -v  |\
		hfst-fst2fst -v -f olw -o $@

$(NORVIG)/dictionary.default-medium.hfst: big.txt tropicalize-uniq-c.awk
	tr -s '[:punct:][:digit:]' ' ' < $< | tr -s '[:space:]' '\n' | tr '[:upper:]' '[:lower:]' > words
	sort < words | uniq -c | sort -nr > train
	awk -f tropicalize-uniq-c.awk --assign CS=`wc -l < words` < train > tropical
	hfst-strings2fst -j -f openfst-tropical tropical -v |\
		hfst-minimize -v |\
		hfst-fst2fst -v -f olw -o $@

$(NORVIG)/error.edit-distance-2-medium.hfst: edit-distance.bash 
	./edit-distance.bash 2 $(ERROR_PROBABILITY) a b c d e f g h i j k l m n o p q r s t u v w x y z |\
		hfst-txt2fst -v -f openfst-tropical |\
		hfst-minimize -v  |\
		hfst-fst2fst -v -f olw -o $@

# automata testing rules
results: results-fi results-en

RESULTS_FI=\
		   results/fi-FI.fiwiki.dictionary-full-boundaries-none.edit-distance-2-none.unigrams\
		   results/fi-FI.fiwiki.dictionary-full-boundaries-none.edit-distance-2-huge.unigrams\
		   results/fi-FI.fiwiki.dictionary-full-boundaries-medium.edit-distance-2-huge.unigrams\
		   results/fi-FI.autogen.dictionary-full-boundaries-none.edit-distance-2-none.unigrams\
		   results/fi-FI.autogen.dictionary-full-boundaries-none.edit-distance-2-medium.unigrams\
		   results/fi-FI.autogen.dictionary-full-boundaries-medium.edit-distance-2-huge.unigrams

ADJUSTMENT_RESULTS_FI=results/juha_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-none.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-none.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-none.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-none.unigrams  results/juha_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-small.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-small.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-small.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-small.unigrams  results/juha_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-medium.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-medium.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-medium.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-medium.unigrams  results/juha_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-huge.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-huge.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-huge.unigrams results/juha_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-huge.unigrams 

ADJUSTMENT_RESULTS_EN=results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.unigrams

results-fi: $(RESULTS_FI)

RESULTS_EN=\
		   results/en-US.norvig1.dictionary-norvig-none.edit-distance-2-none.unigrams\
		   results/en-US.norvig1.dictionary-norvig-none.edit-distance-2-medium.unigrams\
		   results/en-US.norvig1.dictionary-norvig-medium.edit-distance-2-medium.unigrams\
		   results/en-US.norvig2.dictionary-norvig-none.edit-distance-2-none.unigrams \
		   results/en-US.norvig2.dictionary-norvig-none.edit-distance-2-medium.unigrams \
		   results/en-US.norvig2.dictionary-norvig-medium.edit-distance-2-medium.unigrams \
		   results/en-US.autogen.dictionary-norvig-none.edit-distance-2-none.unigrams\
		   results/en-US.autogen.dictionary-norvig-none.edit-distance-2-medium.unigrams\
		   results/en-US.autogen.dictionary-norvig-medium.edit-distance-2-medium.unigrams\

results-en: $(RESULTS_EN)

# context speller result files
context-results: context-results-fi context-results-en

context-results-fi:results-fi $(RESULTS_FI:%.unigrams=%.ngrams.10)

context-results-en:results-en $(RESULTS_EN:%.unigrams=%.ngrams.0.85)

results-en:$(RESULTS_EN) 

context-adjustment-results:context-adjustment-results-fi juha_excerpt_with_errors.txt context-results-fi alice_excerpt_with_errors.txt context-adjustment-results-en

context-adjustment-results-fi:adjustment-results-fi $(ADJUSTMENT_RESULTS_FI:%.unigrams=%.ngrams) 

context-adjustment-results-en:adjustment-results-en alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams

adjustment-results-fi:$(ADJUSTMENT_RESULTS_FI)

adjustment-results-en:$(ADJUSTMENT_RESULTS_EN)

fi%.ngrams: fi%.ngrams.1 fi%.ngrams.2 fi%.ngrams.3 fi%.ngrams.4 fi%.ngrams.5 fi%.ngrams.6 fi%.ngrams.7 fi%.ngrams.8 fi%.ngrams.9 fi%.ngrams.10

fi%.ngrams.1: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 1.0 > $@

fi%.ngrams.2: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 2.0 > $@

fi%.ngrams.3: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 3.0 > $@

fi%.ngrams.4: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 4.0 > $@

fi%.ngrams.5: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 5.0 > $@

fi%.ngrams.6: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 6.0 > $@

fi%.ngrams.7: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 7.0 > $@

fi%.ngrams.8: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 8.0 > $@

fi%.ngrams.9: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 9.0 > $@

fi%.ngrams.10: fi%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 10.0 > $@

juha%.ngrams: juha%.ngrams.1 juha%.ngrams.2 juha%.ngrams.3 juha%.ngrams.4 juha%.ngrams.5 juha%.ngrams.6 juha%.ngrams.7 juha%.ngrams.8 juha%.ngrams.9 juha%.ngrams.10

alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams: results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.05 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.1 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.15 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.2 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.25 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.3 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.35 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.4 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.45 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.5 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.55 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.6 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.65 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.7 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.75 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.8 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.85 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.9 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.0.95 results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.ngrams.1.0

juha%.ngrams.1: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 1 > $@

alice%.ngrams.0.05: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.05 > $@

alice%.ngrams.0.1: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.1 > $@

alice%.ngrams.0.15: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.15 > $@

juha%.ngrams.2: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 2 > $@

alice%.ngrams.0.2: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.2 > $@

alice%.ngrams.0.25: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.25 > $@

juha%.ngrams.3: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 3 > $@

alice%.ngrams.0.3: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.3 > $@

alice%.ngrams.0.35: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.35 > $@

juha%.ngrams.4: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 4 > $@

alice%.ngrams.0.4: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.4 > $@

alice%.ngrams.0.45: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.45 > $@

juha%.ngrams.5: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 5 > $@

alice%.ngrams.0.5: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.5 > $@

alice%.ngrams.0.55: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.55 > $@

juha%.ngrams.6: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 6 > $@

alice%.ngrams.0.6: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.6 > $@

alice%.ngrams.0.65: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.65 > $@

juha%.ngrams.7: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 7 > $@

alice%.ngrams.0.7: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.7 > $@

alice%.ngrams.0.75: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.75 > $@

juha%.ngrams.8: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 8 > $@

alice%.ngrams.0.8: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.8 > $@

alice%.ngrams.0.85: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.85 > $@

juha%.ngrams.9: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 9 > $@

alice%.ngrams.0.9: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.9 > $@

alice%.ngrams.0.95: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.95 > $@

juha%.ngrams.10: juha%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(FI_TAGGER) 10 > $@

alice%.ngrams.1.0: alice%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 1.0 > $@

alice%.ngrams: alice%.ngrams.0.05 alice%.ngrams.0.1 alice%.ngrams.0.15 alice%.ngrams.0.2 alice%.ngrams.0.25 alice%.ngrams.0.3 alice%.ngrams.0.35 alice%.ngrams.0.4 alice%.ngrams.0.45 alice%.ngrams.0.5 alice%.ngrams.0.55 alice%.ngrams.0.6 alice%.ngrams.0.65 alice%.ngrams.0.7 alice%.ngrams.0.75 alice%.ngrams.0.8 alice%.ngrams.0.85 alice%.ngrams.0.9 alice%.ngrams.0.95 alice%.ngrams.1.0

en%.ngrams: en%.ngrams.0.05 en%.ngrams.0.1 en%.ngrams.0.15 en%.ngrams.0.2 en%.ngrams.0.25 en%.ngrams.0.3 en%.ngrams.0.35 en%.ngrams.0.4 en%.ngrams.0.45 en%.ngrams.0.5 en%.ngrams.0.55 en%.ngrams.0.6 en%.ngrams.0.65 en%.ngrams.0.7 en%.ngrams.0.75 en%.ngrams.0.8 en%.ngrams.0.85 en%.ngrams.0.9 en%.ngrams.0.95 en%.ngrams.1.0

en%.ngrams.0.05: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.05 > $@

en%.ngrams.0.1: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.1 > $@

en%.ngrams.0.15: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.15 > $@

en%.ngrams.0.2: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.2 > $@

en%.ngrams.0.25: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.25 > $@

en%.ngrams.0.3: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.3 > $@

en%.ngrams.0.35: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.35 > $@

en%.ngrams.0.4: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.4 > $@

en%.ngrams.0.45: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.45 > $@

en%.ngrams.0.5: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.5 > $@

en%.ngrams.0.55: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.55 > $@

en%.ngrams.0.6: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.6 > $@

en%.ngrams.0.65: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.65 > $@

en%.ngrams.0.7: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.7 > $@

en%.ngrams.0.75: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.75 > $@

en%.ngrams.0.8: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.8 > $@

en%.ngrams.0.85: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.85 > $@

en%.ngrams.0.9: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.9 > $@

en%.ngrams.0.95: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 0.95 > $@

en%.ngrams.1.0: en%.unigrams
	cat $< | $(CONTEXT_SPELLER) $(EN_TAGGER) 1.0 > $@


textables: textables-fi textables-en

textables-fi: \
	results/fi-FI.fiwiki.dictionary-full-boundaries-none.edit-distance-2-none.tex\
	results/fi-FI.fiwiki.dictionary-full-boundaries-none.edit-distance-2-huge.tex\
	results/fi-FI.fiwiki.dictionary-full-boundaries-medium.edit-distance-2-huge.tex\
	results/fi-FI.autogen.dictionary-full-boundaries-none.edit-distance-2-none.tex\
	results/fi-FI.autogen.dictionary-full-boundaries-none.edit-distance-2-huge.tex\
	results/fi-FI.autogen.dictionary-full-boundaries-medium.edit-distance-2-huge.tex

textables-en: \
	results/en-US.norvig1.dictionary-norvig-none.edit-distance-2-medium.tex \
	results/en-US.norvig2.dictionary-norvig-medium.edit-distance-2-medium.tex \
	results/en-US.autogen.dictionary-norvig-none.edit-distance-2-medium.tex \
	results/en-US.autogen.dictionary-norvig-medium.edit-distance-2-medium.tex

results/fi-FI%.tex: results/fi-FI%.unigrams results/fi-FI%.ngrams.$(FI_SCALE)
	sed -e 's/\[[^]]*\]//g' < results/fi-FI$*.unigrams | awk -f results2tex.awk > $@
	sed -e 's/\[[^]]*\]//g' < results/fi-FI$*.ngrams.$(FI_SCALE) | awk -f results2tex.awk >> $@
results/en-US%.tex: results/en-US%.unigrams results/en-US%.ngrams.$(EN_SCALE)
	sed -e 's/\[[^]]*\]//g' < results/en-US$*.unigrams | awk -f results2tex.awk > $@
	sed -e 's/\[[^]]*\]//g' < results/en-US$*.ngrams.$(EN_SCALE) | awk -f results2tex.awk >> $@

results/fi-FI.autogen.dictionary-full-boundaries-none.edit-distance-2-none.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-small.edit-distance-2-none.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-medium.edit-distance-2-none.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-huge.edit-distance-2-none.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-none.edit-distance-2-small.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-small.edit-distance-2-small.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-medium.edit-distance-2-small.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-huge.edit-distance-2-small.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-none.edit-distance-2-medium.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-small.edit-distance-2-medium.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-medium.edit-distance-2-medium.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-huge.edit-distance-2-medium.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-none.edit-distance-2-huge.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-small.edit-distance-2-huge.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-medium.edit-distance-2-huge.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.autogen.dictionary-full-boundaries-huge.edit-distance-2-huge.unigrams: fi-FI.autogen.contextspell $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < fi-FI.autogen.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-none.edit-distance-2-none.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-small.edit-distance-2-none.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-medium.edit-distance-2-none.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-huge.edit-distance-2-none.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-none.edit-distance-2-small.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-small.edit-distance-2-small.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-medium.edit-distance-2-small.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-huge.edit-distance-2-small.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-none.edit-distance-2-medium.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-small.edit-distance-2-medium.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-medium.edit-distance-2-medium.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-huge.edit-distance-2-medium.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-none.edit-distance-2-huge.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-small.edit-distance-2-huge.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-medium.edit-distance-2-huge.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/fi-FI.fiwiki.dictionary-full-boundaries-huge.edit-distance-2-huge.unigrams: fi-FI.fiwiki-gutenberg.contextspell $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < fi-FI.fiwiki-gutenberg.contextspell > $@

results/en-US.autogen.dictionary-norvig-none.edit-distance-2-medium.unigrams: en-US.autogen.contextspell $(NORVIG)/dictionary.default-none.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-none.hfst < en-US.autogen.contextspell > $@

results/en-US.norvig1.dictionary-norvig-none.edit-distance-2-medium.unigrams: norvig1.contextspell $(NORVIG)/dictionary.default-none.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-none.hfst < norvig1.contextspell > $@

results/en-US.norvig2.dictionary-norvig-none.edit-distance-2-medium.unigrams: norvig2.contextspell $(NORVIG)/dictionary.default-none.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-none.hfst < norvig2.contextspell > $@

results/en-US.autogen.dictionary-norvig-medium.edit-distance-2-medium.unigrams: en-US.autogen.contextspell $(NORVIG)/dictionary.default-medium.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-medium.hfst < en-US.autogen.contextspell > $@

results/en-US.norvig1.dictionary-norvig-medium.edit-distance-2-medium.unigrams: norvig1.contextspell $(NORVIG)/dictionary.default-medium.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-medium.hfst < norvig1.contextspell > $@

results/en-US.norvig2.dictionary-norvig-medium.edit-distance-2-medium.unigrams: norvig2.contextspell $(NORVIG)/dictionary.default-medium.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-none.hfst $(NORVIG)/dictionary.default-none.hfst < norvig2.contextspell > $@

results/en-US.autogen.dictionary-norvig-none.edit-distance-2-none.unigrams: en-US.autogen.contextspell $(NORVIG)/dictionary.default-none.hfst $(NORVIG)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-none.hfst $(NORVIG)/dictionary.default-none.hfst < en-US.autogen.contextspell > $@

results/en-US.norvig1.dictionary-norvig-none.edit-distance-2-none.unigrams: norvig1.contextspell $(NORVIG)/dictionary.default-none.hfst $(NORVIG)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-none.hfst $(NORVIG)/dictionary.default-none.hfst < norvig1.contextspell > $@

results/en-US.norvig2.dictionary-norvig-none.edit-distance-2-none.unigrams: norvig2.contextspell $(NORVIG)/dictionary.default-none.hfst $(NORVIG)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-none.hfst $(NORVIG)/dictionary.default-none.hfst < norvig2.contextspell > $@


results/juha_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-huge.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-medium.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-none.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-small.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-huge.hfst $(OMORFI)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-huge.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-medium.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-none.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-small.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-medium.hfst $(OMORFI)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-huge.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-medium.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-none.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-small.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-none.hfst $(OMORFI)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-huge.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-huge.hfst $(OMORFI)/dictionary.default-boundaryweight-huge.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-medium.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-medium.hfst $(OMORFI)/dictionary.default-boundaryweight-medium.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-none.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-none.hfst $(OMORFI)/dictionary.default-boundaryweight-none.hfst < juha_excerpt_with_errors.txt > $@
results/juha_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-small.unigrams: juha_excerpt_with_errors.txt  $(OMORFI)/dictionary.default-boundaryweight-small.hfst $(OMORFI)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(OMORFI)/error.edit-distance-2-small.hfst $(OMORFI)/dictionary.default-boundaryweight-small.hfst < juha_excerpt_with_errors.txt > $@


results/alice_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-huge.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-huge.hfst $(NORVIG)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-huge.hfst $(NORVIG)/dictionary.default-boundaryweight-huge.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-medium.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-huge.hfst $(NORVIG)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-boundaryweight-medium.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-none.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-huge.hfst $(NORVIG)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-none.hfst $(NORVIG)/dictionary.default-boundaryweight-none.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-huge.edit-distance-2-small.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-huge.hfst $(NORVIG)/error.edit-distance-2-huge.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-small.hfst $(NORVIG)/dictionary.default-boundaryweight-small.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-huge.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-medium.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-huge.hfst $(NORVIG)/dictionary.default-boundaryweight-huge.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-medium.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-medium.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-boundaryweight-medium.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-none.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-medium.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-none.hfst $(NORVIG)/dictionary.default-boundaryweight-none.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-medium.edit-distance-2-small.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-medium.hfst $(NORVIG)/error.edit-distance-2-medium.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-small.hfst $(NORVIG)/dictionary.default-boundaryweight-small.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-huge.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-none.hfst $(NORVIG)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-huge.hfst $(NORVIG)/dictionary.default-boundaryweight-huge.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-medium.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-none.hfst $(NORVIG)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-boundaryweight-medium.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-none.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-none.hfst $(NORVIG)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-none.hfst $(NORVIG)/dictionary.default-boundaryweight-none.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-none.edit-distance-2-small.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-none.hfst $(NORVIG)/error.edit-distance-2-none.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-small.hfst $(NORVIG)/dictionary.default-boundaryweight-small.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-huge.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-small.hfst $(NORVIG)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-huge.hfst $(NORVIG)/dictionary.default-boundaryweight-huge.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-medium.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-small.hfst $(NORVIG)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-medium.hfst $(NORVIG)/dictionary.default-boundaryweight-medium.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-none.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-small.hfst $(NORVIG)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-none.hfst $(NORVIG)/dictionary.default-boundaryweight-none.hfst < alice_excerpt_with_errors.txt > $@
results/alice_excerpt_with_errors.dictionary-full-boundaries-small.edit-distance-2-small.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default-boundaryweight-small.hfst $(NORVIG)/error.edit-distance-2-small.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2-small.hfst $(NORVIG)/dictionary.default-boundaryweight-small.hfst < alice_excerpt_with_errors.txt > $@

results/alice_excerpt_with_errors.dictionary-default.edit-distance-2.unigrams: alice_excerpt_with_errors.txt  $(NORVIG)/dictionary.default.hfst $(NORVIG)/error.edit-distance-2.hfst
	hfst-ospell-cicling $(NORVIG)/error.edit-distance-2.hfst $(NORVIG)/dictionary.default.hfst < alice_excerpt_with_errors.txt > $@

juha.txt:
	wget http://www.gutenberg.org/cache/epub/10863/pg10863.txt
	cat pg10863.txt | tail -n +150 | dos2unix > $@

juha_excerpt.txt:juha.txt
	cat $< | egrep -v "^$$" | tr -s '.?!\n' '\n' | tr -cd 'A-Za-z \n' |  sed 's/^ //' | egrep "[^ ]* [^ ]* [^ ]* [^ ]* [^ ]*" | sed 's/\([^ ]* [^ ]* [^ ]* [^ ]* [^ ]*\) .*/\1/' | head -150 > $@

juha_excerpt_with_errors.txt:juha_excerpt.txt
	cat $< | bin/induce_errors.pl > $@

alice.txt:
	wget http://www.gutenberg.org/cache/epub/11/pg11.txt
	cat pg11.txt | tail -n +150 | dos2unix > $@

alice_excerpt.txt:alice.txt
	cat alice.txt | egrep -v "^$$" | tr -s '.?!\n' '\n' | tr -cd 'A-Za-z \n' |  sed 's/^ //' | egrep "[^ ]* [^ ]* [^ ]* [^ ]* [^ ]*" | sed 's/\([^ ]* [^ ]* [^ ]* [^ ]* [^ ]*\) .*/\1/' | head -150 > $@

alice_excerpt_with_errors.txt:alice_excerpt.txt
	cat $< | bin/induce_errors.pl | egrep -v "		" > $@

clean:
	-rm -f cicling-2011-contextspell.aux cicling-2011-contextspell.bbl cicling-2011-contextspell.pdf words train tropical
	-rm -f juha* alice* results/juha* results/alice*

upload: $(PAPER_PDF)
	$(SCP) $< $(SCPHOST):$(SCPDIR)

SOFTWARE=hfst-3.3.0.tar.gz openfst-1.2.7.tar.gz hfstospell-0.2.0.tar.gz

openfst-1.2.7.tar.gz:
	wget http://www.openfst.org/twiki/pub/FST/FstDownload/openfst-1.2.7.tar.gz

hfst-3.3.0.tar.gz:
	wget -O $@ http://sourceforge.net/projects/hfst/files/hfst/hfst-3.3.0.tar.gz/download

hfst-ospell-0.2.0.tar.gz:
	wget -O $@ http://sourceforge.net/projects/hfst/files/hfst/hfst-ospell-0.2.0.tar.gz/download

cicling-2011-contextspell.zip: $(PAPER_PDF) $(PAPER_SOURCES) $(SOFTWARE) $(SPELLING_CORPORA) $(DOCS) $(ERROR_CORPORA) edit-distance.bash
	zip -x .svn -x \*.svn-base -r -v -9 $@ $^ Makefile bin results hfst taggers word_context_speller

cicling-2011-contextspell-small.zip:  $(PAPER_PDF) $(PAPER_SOURCES) $(SOFTWARE) $(SPELLING_CORPORA) $(DOCS) $(ERROR_CORPORA) edit-distance.bash $(RESULTS_FI) $(RESULTS_EN)
	zip -x .svn -x \*.svn-base -x \*autogen\* -r -v -9 $@ $^ Makefile  bin



