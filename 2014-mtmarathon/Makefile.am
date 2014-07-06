## Process this file with automake to create Makefile.in

## This is Makefile for mt marathon 2014 experiments by Flammie and all.
## run make to reproduce.

# to make official PDF version you need to fetch PBML zip from MTM 2014 site

# all secondary
.SECONDARY:
.PHONY: corpora segments translations evaluations

# {{{ SETTINGS

# English - Finnish
MOSES_BASELINE_FI=europarl-v7.fi-en.blm.fi
MOSES_BASELINE_EN_FI=europarl-v7.fi-en.btm.en-fi
MOSES_BASELINE_EN_FI_DIR=europarl-v7.fi-en.en-fi

MOSES_FST1BEST_FI=europarl-v7.fi-en.fst.1best.blm.fi
MOSES_FST1BEST_EN_FI=europarl-v7.fi-en.fst.1best.btm.en-fi
MOSES_FST1BEST_EN_FI_DIR=europarl-v7.fi-en.fst.1best.en-fi

# truecasing
TRUECASE_BASELINE_FI=europarl-v7.fi-en.truecaser.fi
TRUECASE_BASELINE_EN=europarl-v7.fi-en.truecaser.en

# segment Finnish
MORFESSOR_FI=europarl-v7.fi-en.fi.train.morfessor
FST_FI_UNWEIGHTED=compounds.hfst
FST_FI=europarl-v7.fi-en.fi.weighted.hfst

# join (as postproc?)
TEDDYBEARS_FI=

MODELS=$(TRUECASE_BASELINE_FI) $(TRUECASE_BASELINE_EN) \
	   $(MOSES_BASELINE_FI) $(MOSES_BASELINE_EN_FI) \
	   $(MOSES_FST1BEST_FI) $(MOSES_FST1BEST_EN_FI)

# translations
TRANSLATIONS=undhr.baseline-moses.en-fi.translated.fi \
			 undhr.baseline-apertium.en-fi.translated.fi 

# evaluations
EVALUATIONS=undhr.baseline-moses.en-fi.bleu.fi \
			undhr.baseline-apertium.en-fi.bleu.fi

PAPER=2014-mtm-fin-eng.pdf
# }}}

noinst_DATA=$(MODELS) $(SEGMENTS) $(TRANSLATIONS) $(EVALUATIONS) \
			$(PAPER)

# {{{ CORPORA
corpora: fi-en.tgz de-en.tgz

fi-en.tgz:
	$(WGET) http://www.statmt.org/europarl/v7/fi-en.tgz

de-en.tgz:
	$(WGET) http://www.statmt.org/europarl/v7/de-en.tgz

europarl-v7.fi-en.fi.text: fi-en.tgz
	$(TAR) zxvf $<
	mv europarl-v7.fi-en.fi $@
	touch $@

europarl-v7.fi-en.en.text: fi-en.tgz
	$(TAR) zxvf $<
	mv europarl-v7.fi-en.en $@
	touch $@

# }}}
#
# {{{TRAINING
models: $(MODELS)

# Baseline from http://www.statmt.org/moses/?n=moses.baseline
# europarl for en-fi

%.tok.fi: %.fi.text
	$(MOSES_TOKENIZER) -l fi < $< > $@

%.tok.en: %.en.text
	$(MOSES_TOKENIZER) -l en < $< > $@

%.truecaser.fi: %.tok.fi
	$(MOSES_TRAIN_TRUECASER) --model $@ --corpus $<

%.truecaser.en: %.tok.en
	$(MOSES_TRAIN_TRUECASER) --model $@ --corpus $<

%.true.fi: %.tok.fi $(TRUECASE_BASELINE_FI)
	$(MOSES_TRUECASE) --model $(TRUECASE_BASELINE_FI) < $< > $@

%.true.en: %.tok.en $(TRUECASE_BASELINE_EN)
	$(MOSES_TRUECASE) --model $(TRUECASE_BASELINE_EN) < $< > $@

%.clean.fi: %.true.fi %.true.en
	$(MOSES_CLEAN_CORPUS_N) $*.true fi en $*.clean 1 80

%.clean.en: %.true.fi %.true.en
	$(MOSES_CLEAN_CORPUS_N) $*.true en fi $*.clean 1 80

%.sb.fi: %.clean.fi
	$(IRSTLM_ADD_START_END) < $< > $@

%.sb.en: %.clean.en
	$(IRSTLM_ADD_START_END) < $< > $@

%.lm.fi.gz: %.sb.fi
	IRSTLM=$(IRSTLM_DIR) $(IRSTLM_BUILD_LM) -i $*.sb.fi -t /tmp/$* -p -s improved-kneser-ney -o $@

%.lm.en.gz: %.sb.en
	IRSTLM=$(IRSTLM_DIR) $(IRSTLM_BUILD_LM) -i $*.sb.en -t /tmp/$* -p -s improved-kneser-ney -o $@

%.arpa.fi: %.lm.fi.gz
	$(IRSTLM_COMPILE_LM) --text $<
	mv $*.lm.fi.lm $@

%.arpa.en: %.lm.en.gz
	$(IRSTLM_COMPILE_LM) --text $<
	mv $*.lm.en.lm $@

%.blm.fi: %.arpa.fi
	$(MOSES_BUILD_BINARY) -i $< $@

%.blm.en: %.arpa.en
	$(MOSES_BUILD_BINARY) -i $< $@

%.tm.en-fi: %.clean.en %.clean.fi %.blm.fi
	$(MOSES_TRAIN_MODEL) -root-dir $*.en-fi -corpus $*.clean -f en -e fi \
		-alignment grow-diag-final-and -reordering msd-bidirectional-fe \
		-lm 0:3:`pwd`/$*.blm.fi:8  $(MGIZA_FLAGS) \
		$(PARALLEL_FLAGS) \
		-sort-batch-size 253 -sort-compress gzip \
		-external-bin-dir $(GIZA_TOOLDIR) $(SNT2COOC_FLAG) 
	touch $@

### FIXME: tuning

%.btm.en-fi: %.tm.en-fi
	if test ! -d $*.binarised.en-fi ; then \
		$(MKDIR_P) $*.binarised.en-fi ;\
	fi
	$(MOSES_PROCESS_PHRASE_TABLE) -ttable 0 0 $*.en-fi/model/phrase-table.gz \
		-nscores 5 -out $*.binarised.en-fi/phrase-table
	$(MOSES_PROCESS_LEXICAL_TABLE) -in $*.en-fi/model/reordering-table.wbe-msd-bidirectional-fe.gz -out $*.binarised.en-fi/reordering-table
	sed -i -e 's/PhraseDictionaryMemory/PhraseDictionaryBinary/' \
		-e "s:$*.en-fi/model/phrase-table.gz:$*.binarised.en-fi/phrase-table:"\
		-e "s:$*.en-fi/model/reordering-table.wbe-msd-bidirectional-fe.gz:$*.binarised.en-fi/reordering-table:"\
		$*.en-fi/model/moses.ini 
	touch $@

# morfessor train
%.morfessor: %.text
	morfessor-train $< -s $@

%.fi.words: %.tok.fi
	tr -s ' ' '\n' < $< > $@

%.freqs: %.words
	sort < $< | uniq -c | sort -nr > $@

# FST train
%.tropical: %.freqs %.words tropicalize-uniq-c-add-smoothing.awk
	awk -f tropicalize-uniq-c-add-smoothing.awk \
		--assign=CS=`wc -l < $*.words` --assign=LS=`wc -l < $*.freqs` \
		< $*.freqs > $@

%.hfst: %.tropical
	hfst-strings2fst -j -f openfst $< -o $@

# FIXME: ideal would be to calc weight from training data e.g.
# alpha / |CORPUS| + alpha * |DICTIONARY|
%.wordseparator.hfst: %.freqs %.words
	echo -e " \t17.09" | hfst-strings2fst -f openfst -o $@

%.compoundloop.hfst: %.hfst %.wordseparator.hfst
	hfst-concatenate $*.wordseparator.hfst $*.hfst |\
		hfst-minimize |\
		hfst-repeat -f 0 |\
		hfst-minimize -o $@

%.weights.hfst: %.hfst %.compoundloop.hfst
	hfst-concatenate $*.hfst $*.compoundloop.hfst |\
		hfst-minimize -o $@

# FIXME replace this with real calculation too
%.fi.unseen.hfst: %.fi.freqs %.fi.words $(FST_FI_UNWEIGHTED)
	hfst-reweight -S " " -a 34.18 $(FST_FI_UNWEIGHTED) |\
		hfst-reweight -e -a 17.09 - |\
		hfst-minimize -o $@

%.fi.weighted.hfst: %.fi.weights.hfst %.fi.unseen.hfst $(FST_FI_UNWEIGHTED)
	hfst-compose -F $(FST_FI_UNWEIGHTED) $*.fi.weights.hfst|\
		hfst-minimize |\
		hfst-disjunct $*.fi.unseen.hfst |\
		hfst-fst2fst -f olw -o $@

# from omorfi repo
$(FST_FI_UNWEIGHTED): morphology.segments.hfst omorfi-segments.relabel
	hfst-fst2fst -f openfst < $< | hfst-substitute -F omorfi-segments.relabel |\
		hfst-minimize -o $@

morphology.segments.hfst: $(OMORFI_PREFIX)/share/hfst/fi/morphology.segments.hfst
	cp -v $< $@

# }}}
#
# {{{SEGMENTing
segments: $(SEGMENTS)

%.fi.morfessed.text: %.text.fi $(MORFESSOR_FI)
	morfessor-segment $< -l $(MORFESSOR) > $@

%.fst.1best.tok.fi: %.tok.fi $(FST_FI)
	$(IRSTLM_ADD_START_END) < $< | tr ' ' '\n' |\
		$(HFST_LOOKUP) -q $(FST_FI) | tr '\n' '@' | $(SED) -e 's/\@@/\n/g' |\
		cut -f 2 | tr '\n' ' ' | sed -e 's/+?//g' -e 's:</s>:\0\n:g' |\
		$(IRSTLM_RM_START_END) > $@

# for translation model: copy en - en for tokenising

%.fst.1best.tok.en: %.tok.en
	cp -v $< $@

# }}}

# {{{TRANSLATEing
translations:  $(TRANSLATIONS)


%.baseline-moses.en-fi.translated.fi: %.true.en $(MOSES_BASELINE_EN_FI)
	$(MOSES) -f $(MOSES_BASELINE_EN_FI_DIR)/model/moses.ini < $< |\
		$(MOSES_DETRUECASE) |\
		$(MOSES_DETOKENIZER) > $@

%.baseline-moses.en-fi.5best.fi: %.true.en $(MOSES_BASELINE_EN_FI)
	$(MOSES) -f $(MOSES_BASELINE_EN_FI_DIR)/model/moses.ini -n-best-list - 5 < $< > $@

%.baseline-apertium.en-fi.translated.fi: %.en.text 
	$(APERTIUM_DESTXT) < $< |\
		$(APERTIUM) eng-fin |\
		$(APERTIUM_RETXT) > $@


%.fst-moses.en-fi.translated.fi: %.true.en $(MOSES_FST1BEST_EN_FI)
	$(MOSES) -f $(MOSES_FST1BEST_EN_FI_DIR)/model/moses.ini < $< |\
		$(MOSES_DETRUECASE) |\
		$(MOSES_DETOKENIZER) > $@

%.fst-moses.en-fi.5best.fi: %.true.en $(MOSES_FST2BEST_EN_FI)
	$(MOSES) -f $(MOSES_FST1BEST_EN_FI_DIR)/model/moses.ini -n-best-list 5 < $< > $@
# }}}

# {{{EVALUATIONS
evaluations: $(EVALUATIONS)

%.baseline-moses.en-fi.bleu.fi: %.baseline-moses.en-fi.translated.fi %.fi.text
	$(MOSES_MULTI_BLEU) -lc $*.fi.text < $*.baseline-moses.en-fi.translated.fi > $@

%.baseline-apertium.en-fi.bleu.fi: %.baseline-apertium.en-fi.translated.fi %.fi.text
	$(MOSES_MULTI_BLEU) -lc $*.fi.text < $*.baseline-apertium.en-fi.translated.fi > $@
# }}}


# {{{ paper
pbml.cls:
	$(WGET) http://ufal.mff.cuni.cz/pbml/pbml-4_0-flat.zip
	unzip pbml-4_0-flat.zip
	@echo you also need to install gyre pagella font and some texliverecommended

2014-mtm-fin-eng.pdf: 2014-mtm-fin-eng.tex pbml.cls

%.pdf: %.tex
	$(XELATEX) $<
	$(BIBTEX) $*
	$(XELATEX) $<
	$(XELATEX) $<
	$(XELATEX) $<

CLEANFILES=2014-mtm-fin-eng.pdf 2014-mtm-fin-eng.aux 2014-mtm-fin-eng.log \
			2014-mtm-fin-eng.bbl 2014-mtm-fin-eng.blg
# }}}

