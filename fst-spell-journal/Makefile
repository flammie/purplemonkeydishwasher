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

# dictionaries
DICT_EN_CORP=hfst/en/acceptor.corpuswg.hfst
DICT_EN_NO1S=hfst/en/acceptor.corpnosg.hfst

DICT_FI_CORP=hfst/fi/acceptor.corpuswg.hfst
DICT_FI_NOPD=hfst/fi/acceptor.gtklnopd.hfst
DICT_FI_PROD=hfst/fi/acceptor.gtklprod.hfst

DICT_SE_CORP=hfst/se/acceptor.corpuswg.hfst
DICT_SE_NOPD=hfst/se/acceptor.gtsenopd.hfst
DICT_SE_PROD=hfst/se/acceptor.gtseprod.hfst

DICT_KL_NOPD=hfst/kl/acceptor.gtklnopd.hfst

$(DICT_EN_CORP): corp/en/wikipedia.txt

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
	$(WGET) http://dumps.wikimedia.org/fiwiki/$(FIWIKI_DATE)/fiwiki-$(FIWIKI_DATE)-pages-articles.xml.bz2

corp/fi/fiwiki-pages-articles.lines: fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2
	$(BZ2CAT) $< | wc -l > $@

corp/fi/fiwiki-pages-articles-train.xml: fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2 corp/fi/fiwiki-pages-articles.lines
	$(BZ2CAT) $< | head -n `cat corp/fi/fiwiki-pages-articles.lines | sed -e 's/$/ * 0.8/' | bc | sed -e 's/[.,].*//'` > $@

corp/fi/fiwiki-pages-articles-test.xml: fiwiki-pages-articles-$(FIWIKI_DATE).xml.bz2 corp/fi/fiwiki-pages-articles.lines
	$(BC2CAT) $< | tail -n +`cat corp/fi/fiwiki-pages-articles.lines | sed -e 's/$/ * 0.8/' | bc | sed -e 's/[.,].*//'` > $@

corpora:

# corpus to analysers

corp/en/wikipedia.tropical: corp/en/wikipedia.txt
	tr -s '[:space:].-?!,;:/' '\n' < $< | sort | uniq -c |\
		awk -f tropicalize-uniq-c.awk > $@

hfst/en/%.hfst: corp/en/%.tropical
	hfst-strings2fst -v -j $< |\
		hfst-minimize -o $@

hfst/fi/%.hfst: corp/fi/%.tropical
	hfst-strings2fst -v -j $< |\
		hfst-minimize -o $@

hfst/se/%.hfst: corp/se/%.tropical
	hfst-strings2fst -v -j $< |\
		hfst-minimize -o $@

hfst/kl/%.hfst: corp/kl/%.tropical
	hfst-strings2fst -v -j $< |\
		hfst-minimize -o $@

