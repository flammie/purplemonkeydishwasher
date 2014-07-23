## Process this file with automake to create Makefile.in

## This is Makefile for mt marathon 2014 experiments by Flammie and all.
## run make to reproduce.

# to make official PDF version you need to fetch PBML zip from MTM 2014 site

# all secondary
.SECONDARY:
.PHONY: corpora segments translations evaluations

# {{{ SETTINGS

# English - Finnish
MOSES_BASELINE_FI=europarl-v7.fi-en.train.blm.fi
MOSES_BASELINE_EN_FI=europarl-v7.fi-en.train.btm.en-fi
MOSES_BASELINE_EN_FI_DIR=europarl-v7.fi-en.train.en-fi

MOSES_FST1BEST_FI=europarl-v7.fi-en.train.fst.1best.blm.fi
MOSES_FST1BEST_EN_FI=europarl-v7.fi-en.train.fst.1best.btm.en-fi
MOSES_FST1BEST_EN_FI_DIR=europarl-v7.fi-en.train.fst.1best.en-fi

MOSES_FST1BESTMORPHS_FI=europarl-v7.fi-en.train.fst.1best-mor.blm.fi
MOSES_FST1BESTMORPHS_EN_FI=europarl-v7.fi-en.train.fst.1best-mor.btm.en-fi
MOSES_FST1BESTMORPHS_EN_FI_DIR=europarl-v7.fi-en.train.fst.1best-mor.en-fi

# truecasing
TRUECASE_BASELINE_FI=europarl-v7.fi-en.truecaser.fi
TRUECASE_BASELINE_EN=europarl-v7.fi-en.truecaser.en

# segment Finnish
MORFESSOR_FI=europarl-v7.fi-en.fi.morfessor
MORFESSOR_HALF_FI=europarl-v7.fi-en.half.fi.morfessor
MORFESSOR_QUARTER_FI=europarl-v7.fi-en.quarter.fi.morfessor
MORFESSOR_EIGHTH_FI=europarl-v7.fi-en.eighth.fi.morfessor

FST_FI_MORPHS_UNWEIGHTED=morphs-unweighted.hfst
FST_FI_MORPHS=europarl-v7.fi-en.fi.morphweighted.hfst

FST_FI_UNWEIGHTED=compounds.hfst
FST_FI=europarl-v7.fi-en.fi.weighted.hfst

# join (as postproc?)
TEDDYBEARS_FI=

MODELS=$(TRUECASE_BASELINE_FI) $(TRUECASE_BASELINE_EN) \
	   $(MORFESSOR_FI) $(MORFESSOR_HALF_FI) \
	   $(MORFESSOR_QUARTER_FI) $(MORFESSOR_EIGHTH_FI) \
	   $(MOSES_BASELINE_FI) $(MOSES_BASELINE_EN_FI) \
	   $(MOSES_FST1BEST_FI) $(MOSES_FST1BEST_EN_FI) \
	   $(MOSES_FST1BESTMORPHS_FI) $(MOSES_FST1BESTMORPHS_EN_FI)

# translations
TRANSLATIONS=undhr.baseline-moses.en-fi.translated.fi \
			 undhr.baseline-apertium.en-fi.translated.fi \
			 undhr.fst-moses.en-fi.translated.fi \
			 undhr.fst-morphses.en-fi.translated.fi \
			 europarl-v7.fi-en.test.baseline-apertium.en-fi.translated.fi \
			 europarl-v7.fi-en.test.baseline-moses.en-fi.translated.fi \
			 europarl-v7.fi-en.test.fst-moses.en-fi.translated.fi \
			 europarl-v7.fi-en.test.fst-morphses.en-fi.translated.fi

# evaluations
EVALUATIONS=undhr.baseline-moses.en-fi.bleu.fi \
			undhr.baseline-apertium.en-fi.bleu.fi \
			undhr.fst-moses.en-fi.bleu.fi \
			undhr.fst-morphses.en-fi.bleu.fi \
			undhr.baseline-moses.en-fi.nistbleu.fi \
			undhr.baseline-apertium.en-fi.nistbleu.fi \
			undhr.fst-moses.en-fi.nistbleu.fi \
			undhr.fst-morphses.en-fi.nistbleu.fi \
			europarl-v7.fi-en.test.baseline-apertium.en-fi.nistbleu.fi \
			europarl-v7.fi-en.test.baseline-moses.en-fi.nistbleu.fi \
			europarl-v7.fi-en.test.fst-moses.en-fi.nistbleu.fi \
			europarl-v7.fi-en.test.fst-morphses.en-fi.nistbleu.fi

if CAN_TER
EVALUATIONS+=undhr.baseline-moses.en-fi.ter.fi\
			 undhr.baseline-apertium.en-fi.ter.fi \
			 undhr.fst-moses.en-fi.ter.fi \
			 undhr.fst-morphses.en-fi.ter.fi \
			 europarl-v7.fi-en.test.baseline-apertium.en-fi.ter.fi \
			 europarl-v7.fi-en.test.baseline-moses.en-fi.ter.fi \
			 europarl-v7.fi-en.test.fst-moses.en-fi.ter.fi \
			 europarl-v7.fi-en.test.fst-morphses.en-fi.ter.fi

endif

PAPER=2014-mtm-fin-eng.pdf
# }}}

noinst_DATA=$(MODELS) $(SEGMENTS) $(TRANSLATIONS) $(EVALUATIONS) \
			$(PAPER)

# {{{ CORPORA
corpora: fi-en.tgz de-en.tgz

fi-en.tgz:
	$(WGET) http://www.statmt.org/europarl/v7/fi-en.tgz

europarl-v7.fi-en.dupes.fi.text: fi-en.tgz
	$(TAR) zxvf $<
	mv europarl-v7.fi-en.fi $@
	touch $@

europarl-v7.fi-en.dupes.en.text: fi-en.tgz
	$(TAR) zxvf $<
	mv europarl-v7.fi-en.en $@
	touch $@

%.fi.text: %.dupes.en.text %.dupes.fi.text
	paste $* dupes.en.text $*.dupes.fi.text |\
		sort |\
		uniq |\
		cut -f 1 > $@

%.en.text: %.dupes.fi.text %.dupes.en.text
	paste $*.dupes.fi.text $*.dupes.en.text |\
		sort |\
		uniq |\
		cut -f 1 > $@

# split to train / dev / test in 8 / 1 / 1 if no tuning corpora
%.train.en.text: %.en.text
	split -d -l `wc -l < $< | $(SED) -e 's/$$/\/10/' | bc`  $< $*.split.en.
	cat $*.split.en.00 $*.split.en.01 $*.split.en.02 $*.split.en.03 \
		$*.split.en.04 $*.split.en.05 $*.split.en.06 $*.split.en.07 \
		>> $@

%.dev.en.text: %.train.en.text
	cp -v $*.split.en.08 $@

%.test.en.text: %.train.en.text
	cp -v $*.split.en.09 $@

%.train.fi.text: %.fi.text
	split -d -l `wc -l < $< | $(SED) -e 's/$$/\/10/' | bc` $< $*.split.fi.
	cat $*.split.fi.00 $*.split.fi.01 $*.split.fi.02 $*.split.fi.03 \
		$*.split.fi.04 $*.split.fi.05 $*.split.fi.06 $*.split.fi.07 \
		>> $@

%.dev.fi.text: %.train.fi.text
	cp -v $*.split.fi.08 $@

%.test.fi.text: %.train.fi.text
	cp -v $*.split.fi.09 $@

%.half.en.text: %.en.text
	split -d -l `wc -l < $< | $(SED) -e 's/$$/\/2/' | bc`  $< $*.halves.en.
	cp -v $*.halves.en.00 $@

%.quarter.en.text: %.en.text
	split -d -l `wc -l < $< | $(SED) -e 's/$$/\/4/' | bc`  $< $*.quarters.en.
	cp -v $*.quarters.en.00 $@

%.eighth.en.text: %.en.text
	split -d -l `wc -l < $< | $(SED) -e 's/$$/\/4/' | bc`  $< $*.eighths.en.
	cp -v $*.eighths.en.00 $@


%.half.fi.text: %.fi.text
	split -d -l `wc -l < $< | $(SED) -e 's/$$/\/2/' | bc`  $< $*.halves.fi.
	cp -v $*.halves.fi.00 $@

%.quarter.fi.text: %.fi.text
	split -d -l `wc -l < $< | $(SED) -e 's/$$/\/4/' | bc`  $< $*.quarters.fi.
	cp -v $*.quarters.fi.00 $@

%.eighth.fi.text: %.fi.text
	split -d -l `wc -l < $< | $(SED) -e 's/$$/\/4/' | bc`  $< $*.eighths.fi.
	cp -v $*.eighths.fi.00 $@
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

%.tuned.en-fi: %.train.tm.en-fi %.dev.true.en %.dev.true.fi
	$(MOSES_MERT) $*.dev.true.en $*.dev.true.fi \
		--working-dir $*.en-fi.tuning \
		$(MOSES) $*.train.en-fi/model/moses.ini \
		--mertdir `dirname $(MOSES)` $(MOSES_MERT_FLAGS)
	touch $@

%.btm.en-fi: %.tm.en-fi
	if test ! -d $*.binarised.en-fi ; then \
		$(MKDIR_P) $*.binarised.en-fi ;\
	fi
	$(MOSES_PROCESS_PHRASE_TABLE) -ttable 0 0 $*.en-fi/model/phrase-table.gz \
		-nscores 5 -out $*.binarised.en-fi/phrase-table
	$(MOSES_PROCESS_LEXICAL_TABLE) -in $*.en-fi/model/reordering-table.wbe-msd-bidirectional-fe.gz -out $*.binarised.en-fi/reordering-table
	$(SED) -i -e 's/PhraseDictionaryMemory/PhraseDictionaryBinary/' \
		-e "s:$*.en-fi/model/phrase-table.gz:$*.binarised.en-fi/phrase-table:"\
		-e "s:$*.en-fi/model/reordering-table.wbe-msd-bidirectional-fe.gz:$*.binarised.en-fi/reordering-table:"\
		$*.en-fi/model/moses.ini 
	touch $@

# morfessor train
%.morfessor: %.text
	$(MORFESSOR_TRAIN)  $< -s $@

# word counts for word segment model
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
		hfst-substitute -f ' ' -t '→ ←' |\
		hfst-fst2fst -f olw -o $@

# morph count for morph segment model
%.fi.morphs: %.morfessed.text.fi
	tr -s ' ' '\n' < $< > $@

%.morphfreqs: %.morphs
	sort < $< | uniq -c | sort -nr > $@

%.morphtropical: %.morphfreqs %.morphs  tropicalize-uniq-c-add-smoothing.awk
	awk -f tropicalize-uniq-c-add-smoothing.awk \
		--assign=CS=`wc -l < $*.words` --assign=LS=`wc -l < $*.freqs` \
		< $*.freqs > $@

%.morphfst: %.morphtropical
	hfst-strings2fst -j -f openfst $< -o $@

# FIXME: ideal would be to calc weight from training data e.g.
# alpha / |CORPUS| + alpha * |DICTIONARY|
%.morphseparator.hfst: %.morphfreqs %.morphs
	echo -e " \t17.09" | hfst-strings2fst -f openfst -o $@

%.morphloop.hfst: %.morphfst %.morphseparator.hfst
	hfst-concatenate $*.morphseparator.hfst $*.hfst |\
		hfst-minimize |\
		hfst-repeat -f 0 |\
		hfst-minimize -o $@

%.morphweights.hfst: %.hfst %.morphloop.hfst
	hfst-concatenate $*.hfst $*.morphloop.hfst |\
		hfst-minimize -o $@

# FIXME replace this with real calculation too
%.fi.unseenmorphs.hfst: %.fi.morphfreqs %.fi.morphs $(FST_FI_MORPHS_UNWEIGHTED)
	hfst-reweight -S " " -a 54.18 $(FST_FI_MORPHS_UNWEIGHTED) |\
		hfst-reweight -e -a 27.09 - |\
		hfst-minimize -o $@

%.fi.morphweighted.hfst: %.fi.morphweights.hfst %.fi.unseenmorphs.hfst $(FST_FI_MORPHS_UNWEIGHTED)
	hfst-compose -F $(FST_FI_MORPHS_UNWEIGHTED) $*.fi.morphweights.hfst|\
		hfst-minimize |\
		hfst-disjunct $*.fi.unseenmorphs.hfst |\
		hfst-substitute -f ' ' -t '→ ←' |\
		hfst-fst2fst -f olw -o $@


# originals with segmentation added

$(FST_FI_UNWEIGHTED): morphology.segments.hfst omorfi-segments.relabel
	hfst-fst2fst -f openfst < $< | hfst-substitute -F omorfi-segments.relabel |\
		hfst-minimize -o $@

$(FST_FI_MORPHS_UNWEIGHTED): morphology.segments.hfst omorfi-morphs.relabel
	hfst-fst2fst -f openfst < $< | hfst-substitute -F omorfi-morphs.relabel |\
		hfst-minimize -o $@

# from omorfi repo
morphology.segments.hfst: $(OMORFI_PREFIX)/share/hfst/fi/morphology.segments.hfst
	cp -v $< $@



# }}}
#
# {{{SEGMENTing
segments: $(SEGMENTS)

%.morfessed.text.fi: %.fi.text $(MORFESSOR_FI)
	$(MORFESSOR_SEGMENT) -l $(MORFESSOR_FI)  $<  > $@

%.fst.1best.tok.fi: %.tok.fi $(FST_FI)
	$(IRSTLM_ADD_START_END) < $< | tr ' ' '\n' |\
		$(HFST_LOOKUP) -q -P $(FST_FI) | $(SED) -e 's/^$$//' | tr '\n' '@' |\
		tr  '\n' |\
		cut -f 2 | tr '\n' ' ' | $(SED) -e 's/+?//g' -e 's:</s>:\0\n:g' |\
		head -n -1 |\
		$(IRSTLM_RM_START_END) > $@

%.fst.1best-mor.tok.fi: %.tok.fi $(FST_FI_MORPHS)
	$(IRSTLM_ADD_START_END) < $< | tr ' ' '\n' |\
		$(HFST_LOOKUP) -q -P $(FST_FI_MORPHS) | $(SED) -e 's/^$$//' | tr '\n' '@' |\
		tr  '\n' |\
		cut -f 2 | tr '\n' ' ' | $(SED) -e 's/+?//g' -e 's:</s>:\0\n:g' |\
		head -n -1 |\
		$(IRSTLM_RM_START_END) > $@

# for translation model: copy en - en for tokenising

%.fst.1best.tok.en: %.tok.en
	cp -v $< $@

%.fst.1best-mor.tok.en: %.tok.en
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
		tr -d '*#@' |\
		$(APERTIUM_RETXT) > $@


%.fst-moses.en-fi.translated-segments.fi: %.true.en $(MOSES_FST1BEST_EN_FI)
	$(MOSES) -f $(MOSES_FST1BEST_EN_FI_DIR)/model/moses.ini < $< |\
		$(MOSES_DETRUECASE) |\
		$(MOSES_DETOKENIZER) > $@

# baseline desegmentation
%.translated.fi: %.translated-segments.fi
	$(SED) -e 's/→ ←//g' \
		-e 's/←[^[:space:].,?!()"]*//g' \
		-e 's/[^[:space:].,?!()"]*→//g' < $< > $@

%.fst-moses.en-fi.5best.fi: %.true.en $(MOSES_FST1BEST_EN_FI)
	$(MOSES) -f $(MOSES_FST1BEST_EN_FI_DIR)/model/moses.ini -n-best-list - 5 < $< > $@

%.fst-morphses.en-fi.translated-segments.fi: %.true.en $(MOSES_FST1BESTMORPHS_EN_FI)
	$(MOSES) -f $(MOSES_FST1BESTMORPHS_EN_FI_DIR)/model/moses.ini < $< |\
		$(MOSES_DETRUECASE) |\
		$(MOSES_DETOKENIZER) > $@

# }}}

# {{{EVALUATIONS
evaluations: $(EVALUATIONS)

%.baseline-moses.en-fi.bleu.fi: %.baseline-moses.en-fi.translated.fi %.fi.text
	$(MOSES_MULTI_BLEU) -lc $*.fi.text < $*.baseline-moses.en-fi.translated.fi > $@

%.fst-moses.en-fi.bleu.fi: %.fst-moses.en-fi.translated.fi %.fi.text
	$(MOSES_MULTI_BLEU) -lc $*.fi.text < $*.fst-moses.en-fi.translated.fi > $@

%.fst-morphses.en-fi.bleu.fi: %.fst-morphses.en-fi.translated.fi %.fi.text
	$(MOSES_MULTI_BLEU) -lc $*.fi.text < $*.fst-morphses.en-fi.translated.fi > $@

%.baseline-apertium.en-fi.bleu.fi: %.baseline-apertium.en-fi.translated.fi %.fi.text
	$(MOSES_MULTI_BLEU) -lc $*.fi.text < $*.baseline-apertium.en-fi.translated.fi > $@

%.en.sgml: %.en.text
	$(WRAP_XML) src en fi $< | grep -v "<seg id[^>]*></seg>" > $@

%.fi.sgml: %.fi.text
	$(WRAP_XML) ref en fi $< | grep -v "<seg id[^>]*></seg>" > $@

%.translated.fi.sgml: %.translated.fi
	$(WRAP_XML) tst en fi $< | grep -v "<seg id[^>]*></seg>" > $@

%.baseline-moses.en-fi.nistbleu.fi: %.baseline-moses.en-fi.translated.fi.sgml %.fi.sgml %.en.sgml
	$(NIST_BLEU13A) -s $*.en.sgml -r $*.fi.sgml -t $*.baseline-moses.en-fi.translated.fi.sgml > $@

%.fst-moses.en-fi.nistbleu.fi: %.fst-moses.en-fi.translated.fi.sgml %.fi.sgml %.en.sgml
	$(NIST_BLEU13A) -s $*.en.sgml -r $*.fi.sgml -t $*.fst-moses.en-fi.translated.fi.sgml > $@

%.fst-morphses.en-fi.nistbleu.fi: %.fst-morphses.en-fi.translated.fi.sgml %.fi.sgml %.en.sgml
	$(NIST_BLEU13A) -s $*.en.sgml -r $*.fi.sgml -t $*.fst-morphses.en-fi.translated.fi.sgml > $@

%.baseline-apertium.en-fi.nistbleu.fi: %.baseline-apertium.en-fi.translated.fi.sgml %.fi.sgml %.en.sgml
	$(NIST_BLEU13A) -s $*.en.sgml -r $*.fi.sgml -t $*.baseline-apertium.en-fi.translated.fi.sgml > $@

if CAN_TER
%.baseline-moses.en-fi.ter.fi: %.baseline-moses.en-fi.translated.fi.sgml %.fi.sgml %.en.sgml
	$(JAVA) -jar $(TERJAR) -r $*.fi.sgml -h $*.baseline-moses.en-fi.translated.fi.sgml > $@

%.fst-moses.en-fi.ter.fi: %.fst-moses.en-fi.translated.fi.sgml %.fi.sgml %.en.sgml
	$(JAVA) -jar $(TERJAR) -r $*.fi.sgml -h $*.fst-moses.en-fi.translated.fi.sgml > $@

%.fst-morphses.en-fi.ter.fi: %.fst-morphses.en-fi.translated.fi.sgml %.fi.sgml %.en.sgml
	$(JAVA) -jar $(TERJAR) -r $*.fi.sgml -h $*.fst-morphses.en-fi.translated.fi.sgml > $@

%.baseline-apertium.en-fi.ter.fi: %.baseline-apertium.en-fi.translated.fi.sgml %.fi.sgml %.en.sgml
	$(JAVA) -jar $(TERJAR) -r $*.fi.sgml -h $*.baseline-apertium.en-fi.translated.fi.sgml > $@
endif

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
# vim: set foldmethod=marker:
