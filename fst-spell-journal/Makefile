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
HFST_REWEIGHT=hfst-reweight
HFST_UNION=hfst-disjunct
HFST_STRINGS2FST=hfst-strings2fst
HFST_MINIMIZE=hfst-minimize
HFST_FST2FST=hfst-fst2fst

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
EN_ALPHABET=abcdefghijklmnopqrstuvwxzyABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\'’-
FI_ALPHABET=abcdefghijklmnopqršstuwvxyzžåäöABCDEFGHIJKLMNOPQRSŠTUWVXYZŽÅÄÖ0123456789\'’-

# dictionaries
DICT_EN_CORP=hfst/en/acceptor.corpuswg.hfst
DICT_EN_NO1S=hfst/en/acceptor.corpnosg.hfst
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

$(DICT_EN_CORP): hfst/en/wikipedia.hfst
	cp -v $< $@

$(DICT_EN_NORV): hfst/en/big.hfst
	cp -v $< $@

$(DICT_FI_CORP): hfst/fi/wikipedia.hfst
	cp -v $< $@

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
ERRM_EN_1ALL=hfst/en/errmodel.ed1alls.hfst
ERRM_EN_2UNW=hfst/en/errmodel.ed2unwe.hfst
ERRM_EN_2QWE=hfst/en/errmodel.ed2qwer.hfst
ERRM_EN_CORP=hfst/en/errmodel.ed2corp.hfst
ERRM_EN_2ALL=hfst/en/errmodel.ed2alls.hfst
ERRM_EN_3ALL=hfst/en/errmodel.ed3alls.hfst
ERRM_EN_4ALL=hfst/en/errmodel.ed4alls.hfst

ERRM_FI_2UNW=hfst/fi/errmodel.ed2unwe.hfst
ERRM_FI_2QWE=hfst/fi/errmodel.ed2qwer.hfst
ERRM_FI_CORP=hfst/fi/errmodel.ed2corp.hfst

ERRM_SE_2UNW=hfst/se/errmodel.ed2unwe.hfst
ERRM_SE_2QWE=hfst/se/errmodel.ed2qwer.hfst
ERRM_SE_CORP=hfst/se/errmodel.ed2corp.hfst

ERRM_KL_2UNW=hfst/kl/errmodel.ed2unew.hfst
ERRM_KL_2QWE=hfst/kl/errmodel.ed2qwer.hfst
ERRM_KL_CORP=hfst/kl/errmodel.ed2corp.hfst

errmodels:

# corpora
ENWIKI_DATE=20120802
FIWIKI_DATE=20120827
SEWIKI_DATE=20120825
KLWIKI_DATE=20120902

CORP_EN_NORV=corp/en/big.txt
CORP_EN_WPLM=corp/en/wikipedia.txt
CORP_FI_WPLM=corp/fi/wikipedia.txt
CORP_SE_WPLM=corp/se/wikipedia.txt
CORP_KL_WPLM=corp/kl/wikipedia.txt

corp/en/wikipedia.txt: corp/en/enwiki-pages-articles-train.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) > $@

corp/fi/wikipedia.txt: corp/fi/fiwiki-pages-articles-train.xml
	$(AWK) '/<text/,/<\/text/ {print}' < $<|\
		$(SED) -e 's_</\?text[^>]*>__g' |\
		$(WIKICLEAN) > $@

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

corp/en/%.sorted: corp/en/%.txt
	tr -s '[:space:].?!,;:/' '\n' < $< |\
		grep "^[$(EN_ALPHABET)]*$$" |\
		sort > $@

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
manual/en/edit-1.txt:
	$(PYTHON2) editdist.py -a "$(EN_ALPHABET)"

manual/en/edit-1-nonfirst.txt:
	$(PYTHON2) editdist.py -a "$(EN_ALPHABET)"

manual/en/edit-1-qwerty-halved.txt: manual/en/qwerty.tsv
	$(PYTHON2) editdist.py -a "$(EN_ALPHABET)" -i manual/en/qwerty.tsv

manual/en/hunspell-reps.strings:
	grep '^REP' $(HUNSPELL_EN_AFF) |\
		tail -n +2 |\
		sed -e 's/REP[[:space:]]*//' -e 's/[[:space:]]\+/:/' > $@

