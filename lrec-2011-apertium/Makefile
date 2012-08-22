# Execute this Makefile with GNU compatible make to recreate the test results
# and paper for article titled
# `blah' in Proceedings of LREC 2012

# point programs to right binaries
PYTHON=python3
LTCOMP=lt-comp
LTPROC=lt-proc
HFST_APERTIUM2FST=hfst-apertium2fst
HFST_MINIMIZE=hfst-minimize
HFST_INVERT=hfst-invert
XELATEX=xelatex
BIBTEX=bibtex
UPLOAD=ruuvi:public_html/tmp
ARTICLE=lrec-2011-apertium.pdf
BEAMER=lrec-2011-apertium-beamer.pdf
WIKISIZE=102400
SPELLWORDS=1000

paper: $(ARTICLE) $(BEAMER)

# article
$(ARTICLE): lrec-2011-apertium.tex lrec2011.bib
	$(XELATEX) lrec-2011-apertium.tex
	$(BIBTEX) lrec-2011-apertium
	$(XELATEX) lrec-2011-apertium.tex
	$(XELATEX) lrec-2011-apertium.tex
	$(XELATEX) lrec-2011-apertium.tex

$(BEAMER): lrec-2011-apertium-beamer.tex
	$(XELATEX) $<
	$(XELATEX) $<
	$(XELATEX) $<


upload:
	scp $(BEAMER) $(ARTICLE) $(UPLOAD)

#  apertium-cy-kw.kw.dix:9: parser error : XML declaration allowed only at the start of the document
#  apertium-sw-en.sw.dix: empty <alphabet>
#
BROKEN_HFST=apertium-cy-kw.kw.dix \
	   apertium-sw-en.sw.dix
# Error (17501): Undefined paradigm 'Septemb/er__n'.
BROKEN_APERTIUM=apertium-la-es.la.dix

# point to directory holding SVN repository:
# <https://apertium.svn.sourceforge.net/svnroot/apertium>
APERTIUM_SVNROOT=apertium
# these are the files we _can_ compile
DIX_SOURCES=$(APERTIUM_SVNROOT)/nursery/apertium-en-af/apertium-en-af.af.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-es-an/apertium-es-an.an.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-ay-es.ay.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-be-ru.be.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-mk-bg/apertium-mk-bg.bg.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-bn-en/apertium-bn-en.bn.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-br-fr/apertium-br-fr.br.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-es-ca/apertium-es-ca.ca.dix\
			$(APERTIUM_SVNROOT)/staging/apertium-pl-cs/apertium-pl-cs.cs.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-cy-en/apertium-cy-en.cy.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-sv-da/apertium-sv-da.da.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-de-nl/apertium-de-nl.de.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-el-en/apertium-el-en.el.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-mk-en/apertium-mk-en.en.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-eo-fr/apertium-eo-fr.eo.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-es-ca/apertium-es-ca.es.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-eu-es/apertium-eu-es.eu.dix\
			$(APERTIUM_SVNROOT)/nursery/apertium-fo-is/apertium-fo-is.fo.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-eo-fr/apertium-eo-fr.fr.dix\
			$(APERTIUM_SVNROOT)/nursery/apertium-ga-gd/apertium-ga-gd.ga.dix\
			$(APERTIUM_SVNROOT)/nursery/apertium-ga-gd/apertium-ga-gd.gd.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-es-gl/apertium-es-gl.gl.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-ga-gv/apertium-ga-gv.gv.dix\
			$(APERTIUM_SVNROOT)/staging/apertium-mt-he/apertium-mt-he.he.dix\
			$(APERTIUM_SVNROOT)/nursery/apertium-ur-hi/apertium-ur-hi.hi.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-ht-en/apertium-ht-en.ht.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-hy-en.hy.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-es-ia/apertium-es-ia.ia.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-is-en/apertium-is-en.is.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-es-it/apertium-es-it.it.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-ku-fa/apertium-ku-fa.ku.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-lt-lv/apertium-lt-lv.lt.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-en-lv/apertium-en-lv.lv.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-mk-bg/apertium-mk-bg.mk.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-sh-mk/apertium-sh-mk.mk.dix\
			$(APERTIUM_SVNROOT)/staging/apertium-mt-he/apertium-mt-he.mt.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-nn-nb/apertium-nn-nb.nb.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-ne-en/apertium-ne-en.ne.dix\
			$(APERTIUM_SVNROOT)/staging/apertium-af-nl/apertium-af-nl.nl.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-nn-nb/apertium-nn-nb.nn.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-os-fa.os.dix\
			$(APERTIUM_SVNROOT)/staging/apertium-pl-cs/apertium-pl-cs.pl.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-es-pt/apertium-es-pt.pt.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-qu-es.qu.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-es-ro/apertium-es-ro.ro.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-kv-ru/apertium-kv-ru.ru.dix\
			$(APERTIUM_SVNROOT)/staging/apertium-ca-sc/apertium-ca-sc.sc.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-si-en/apertium-si-en.si.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-cs-sk/apertium-cs-sk.sk.dix\
			$(APERTIUM_SVNROOT)/nursery/apertium-sl-es/apertium-sl-es.sl.dix\
			$(APERTIUM_SVNROOT)/trunk/apertium-sv-da/apertium-sv-da.sv.dix\
			$(APERTIUM_SVNROOT)/nursery/apertium-tg-fa/apertium-tg-fa.tg.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-ru-uk/apertium-ru-uk.uk.dix\
			$(APERTIUM_SVNROOT)/nursery/apertium-ur-hi/apertium-ur-hi.ur.dix\
			$(APERTIUM_SVNROOT)/incubator/apertium-vi-en/apertium-vi-en.vi.dix

# we link them to current directory to help % rules
DIX_LINKS=apertium-en-af.af.dix\
			apertium-es-an.an.dix\
			apertium-ay-es.ay.dix\
			apertium-be-ru.be.dix\
			apertium-mk-bg.bg.dix\
			apertium-bn-en.bn.dix\
			apertium-br-fr.br.dix\
			apertium-es-ca.ca.dix\
			apertium-pl-cs.cs.dix\
			apertium-cy-en.cy.dix\
			apertium-sv-da.da.dix\
			apertium-de-nl.de.dix\
			apertium-el-en.el.dix\
			apertium-mk-en.en.dix\
			apertium-eo-fr.eo.dix\
			apertium-es-ca.es.dix\
			apertium-eu-es.eu.dix\
			apertium-fo-is.fo.dix\
			apertium-eo-fr.fr.dix\
			apertium-ga-gd.ga.dix\
			apertium-ga-gd.gd.dix\
			apertium-es-gl.gl.dix\
			apertium-ga-gv.gv.dix\
			apertium-mt-he.he.dix\
			apertium-ur-hi.hi.dix\
			apertium-ht-en.ht.dix\
			apertium-hy-en.hy.dix\
			apertium-es-ia.ia.dix\
			apertium-is-en.is.dix\
			apertium-es-it.it.dix\
			apertium-ku-fa.ku.dix\
			apertium-lt-lv.lt.dix\
			apertium-en-lv.lv.dix\
			apertium-mk-bg.mk.dix\
			apertium-sh-mk.mk.dix\
			apertium-mt-he.mt.dix\
			apertium-nn-nb.nb.dix\
			apertium-ne-en.ne.dix\
			apertium-af-nl.nl.dix\
			apertium-nn-nb.nn.dix\
			apertium-os-fa.os.dix\
			apertium-pl-cs.pl.dix\
			apertium-es-pt.pt.dix\
			apertium-qu-es.qu.dix\
			apertium-es-ro.ro.dix\
			apertium-kv-ru.ru.dix\
			apertium-ca-sc.sc.dix\
			apertium-si-en.si.dix\
			apertium-cs-sk.sk.dix\
			apertium-sl-es.sl.dix\
			apertium-sv-da.sv.dix\
			apertium-tg-fa.tg.dix\
			apertium-ru-uk.uk.dix\
			apertium-ur-hi.ur.dix\
			apertium-vi-en.vi.dix

# these are corresponding hfst automata
HFST_TARGETS=apertium-en-af.af.hfst\
			apertium-es-an.an.hfst\
			apertium-ay-es.ay.hfst\
			apertium-be-ru.be.hfst\
			apertium-mk-bg.bg.hfst\
			apertium-bn-en.bn.hfst\
			apertium-br-fr.br.hfst\
			apertium-es-ca.ca.hfst\
			apertium-pl-cs.cs.hfst\
			apertium-cy-en.cy.hfst\
			apertium-sv-da.da.hfst\
			apertium-de-nl.de.hfst\
			apertium-el-en.el.hfst\
			apertium-mk-en.en.hfst\
			apertium-eo-fr.eo.hfst\
			apertium-es-ca.es.hfst\
			apertium-eu-es.eu.hfst\
			apertium-fo-is.fo.hfst\
			apertium-eo-fr.fr.hfst\
			apertium-ga-gd.ga.hfst\
			apertium-ga-gd.gd.hfst\
			apertium-es-gl.gl.hfst\
			apertium-ga-gv.gv.hfst\
			apertium-mt-he.he.hfst\
			apertium-ur-hi.hi.hfst\
			apertium-ht-en.ht.hfst\
			apertium-hy-en.hy.hfst\
			apertium-es-ia.ia.hfst\
			apertium-is-en.is.hfst\
			apertium-es-it.it.hfst\
			apertium-ku-fa.ku.hfst\
			apertium-lt-lv.lt.hfst\
			apertium-en-lv.lv.hfst\
			apertium-mk-bg.mk.hfst\
			apertium-sh-mk.mk.hfst\
			apertium-mt-he.mt.hfst\
			apertium-nn-nb.nb.hfst\
			apertium-ne-en.ne.hfst\
			apertium-af-nl.nl.hfst\
			apertium-nn-nb.nn.hfst\
			apertium-os-fa.os.hfst\
			apertium-pl-cs.pl.hfst\
			apertium-es-pt.pt.hfst\
			apertium-qu-es.qu.hfst\
			apertium-es-ro.ro.hfst\
			apertium-kv-ru.ru.hfst\
			apertium-ca-sc.sc.hfst\
			apertium-si-en.si.hfst\
			apertium-cs-sk.sk.hfst\
			apertium-sl-es.sl.hfst\
			apertium-sv-da.sv.hfst\
			apertium-tg-fa.tg.hfst\
			apertium-ru-uk.uk.hfst\
			apertium-ur-hi.ur.hfst\
			apertium-vi-en.vi.hfst

# these are corresponding apertium automata
APERTIUM_TARGETS=apertium-en-af.af.apertium\
			apertium-es-an.an.apertium\
			apertium-ay-es.ay.apertium\
			apertium-be-ru.be.apertium\
			apertium-mk-bg.bg.apertium\
			apertium-bn-en.bn.apertium\
			apertium-br-fr.br.apertium\
			apertium-es-ca.ca.apertium\
			apertium-pl-cs.cs.apertium\
			apertium-cy-en.cy.apertium\
			apertium-sv-da.da.apertium\
			apertium-de-nl.de.apertium\
			apertium-el-en.el.apertium\
			apertium-mk-en.en.apertium\
			apertium-eo-fr.eo.apertium\
			apertium-es-ca.es.apertium\
			apertium-eu-es.eu.apertium\
			apertium-fo-is.fo.apertium\
			apertium-eo-fr.fr.apertium\
			apertium-ga-gd.ga.apertium\
			apertium-ga-gd.gd.apertium\
			apertium-es-gl.gl.apertium\
			apertium-ga-gv.gv.apertium\
			apertium-mt-he.he.apertium\
			apertium-ur-hi.hi.apertium\
			apertium-ht-en.ht.apertium\
			apertium-hy-en.hy.apertium\
			apertium-es-ia.ia.apertium\
			apertium-is-en.is.apertium\
			apertium-es-it.it.apertium\
			apertium-ku-fa.ku.apertium\
			apertium-lt-lv.lt.apertium\
			apertium-en-lv.lv.apertium\
			apertium-mk-bg.mk.apertium\
			apertium-sh-mk.mk.apertium\
			apertium-mt-he.mt.apertium\
			apertium-nn-nb.nb.apertium\
			apertium-ne-en.ne.apertium\
			apertium-af-nl.nl.apertium\
			apertium-nn-nb.nn.apertium\
			apertium-os-fa.os.apertium\
			apertium-pl-cs.pl.apertium\
			apertium-es-pt.pt.apertium\
			apertium-qu-es.qu.apertium\
			apertium-es-ro.ro.apertium\
			apertium-kv-ru.ru.apertium\
			apertium-ca-sc.sc.apertium\
			apertium-si-en.si.apertium\
			apertium-cs-sk.sk.apertium\
			apertium-sl-es.sl.apertium\
			apertium-sv-da.sv.apertium\
			apertium-tg-fa.tg.apertium\
			apertium-ru-uk.uk.apertium\
			apertium-ur-hi.ur.apertium\
			apertium-vi-en.vi.apertium

# build automata 
all: $(HFST_TARGETS) $(APERTIUM_TARGETS)

# link data to local dir for simpler build rules
dix-links: $(DIX_SOURCES)
	for f in $^ ; do \
		ln -sf $$f . ; \
	done

%.dix: dix-links

# the targets that are not files
.PHONY: compile texts \
	results results1 results2 results3 results4 results5 results6 results7 \
	times1 times2 \
	analyses1 analyses2

# fetch or create corpora (handpicked)
texts: apertium-eu-es.eu.text apertium-nn-nb.nn.text apertium-ga-gv.gv.text

euwiki-20120219-pages-articles.xml.bz2:
	wget 'http://dumps.wikimedia.org/euwiki/20120219/euwiki-20120219-pages-articles.xml.bz2'

apertium-eu-es.eu.text: euwiki-20120219-pages-articles.xml.bz2
	bzcat $< |\
		awk '/<text/,/<\/text/ {print}' |\
		./wikipedia-deform.sh |\
		head -n $(WIKISIZE) > $@

nnwiki-20120215-pages-articles.xml.bz2:
	wget 'http://dumps.wikimedia.org/nnwiki/20120215/nnwiki-20120215-pages-articles.xml.bz2'

apertium-nn-nb.nn.text: nnwiki-20120215-pages-articles.xml.bz2
	bzcat $< |\
		awk '/<text/,/<\/text/ {print}' |\
		./wikipedia-deform.sh |\
		head -n $(WIKISIZE) > $@

gvwiki-20120215-pages-articles.xml.bz2:
	wget 'http://dumps.wikimedia.org/gvwiki/20120215/gvwiki-20120215-pages-articles.xml.bz2'

apertium-ga-gv.gv.text: gvwiki-20120215-pages-articles.xml.bz2
	bzcat $< |\
		awk '/<text/,/<\/text/ {print}' |\
		./wikipedia-deform.sh |\
		head -n $(WIKISIZE) > $@


# spectie says:
## The dictionaries I think we could use are:
##
## * apertium-eu-es.eu.dix (this is the biggest _released_ dictionary I
## know of)
## * apertium-nn-nb.nb.dix (it's well developed, and we can test how word
## compounding differs)
## * ... plus one dictionary for a language that doesn't yet have a
## hunspell speller ...
# -> apertium-ga-gv.gv.dix

# (1) analyse corpora and compare
analyses1: apertium-eu-es.eu.hfst.analyses1 apertium-eu-es.eu.apertium.analyses1 \
	apertium-nn-nb.nn.hfst.analyses1 apertium-nn-nb.nn.apertium.analyses1 \
	apertium-ga-gv.gv.hfst.analyses1 apertium-ga-gv.gv.apertium.analyses1
results1: apertium-eu-es.eu.results1 apertium-nn-nb.nn.results1 \
	apertium-ga-gv.gv.results1

%.hfst.analyses1: %.hfst %.text
	hfst-proc $< < $*.text > $@

apertium-nn-nb.nn.apertium.analyses1: apertium-nn-nb.nn.apertium apertium-nn-nb.nn.text
	lt-proc -e $< < apertium-nn-nb.nn.text > $@

%.apertium.analyses1: %.apertium %.text
	lt-proc $< < $*.text > $@

%.results1: %.hfst.analyses1 %.apertium.analyses1
	$(PYTHON) compare-analysis-sets.py -1 $*.apertium.analyses1 -2 $< -o $@

# (2) generate dictionary with apertium and analyse both and compare
results2: apertium-eu-es.eu.results2 apertium-nn-nb.nn.results2 \
	apertium-ga-gv.gv.results2

%.expand: %.dix
	lt-expand $< | cut -f 1 -d : | fgrep --invert-match '__REGEXP__' > $@

%.hfst.analyses2: %.hfst %.expand
	apertium-destxt $*.expand | hfst-proc $< > $@

%.apertium.analyses2: %.apertium %.expand
	apertium-destxt $*.expand | lt-proc $< > $@

%.results2: %.hfst.analyses2 %.apertium.analyses2
	$(PYTHON) compare-analysis-sets.py -1 $*.apertium.analyses2 -2 $< -o $@

# (3) analysis speed tests
results3: times1
times1: apertium-eu-es.eu.times1 apertium-nn-nb.nn.times1 \
	apertium-ga-gv.gv.times1

%.times1: %.hfst %.apertium %.text
	echo hfst-proc thrice analyzing $*.text > $@
	time hfst-proc $*.hfst --profile=$*.profile1  $*.text > /dev/null
	time hfst-proc $*.hfst --profile=$*.profile1  $*.text > /dev/null
	time hfst-proc $*.hfst --profile=$*.profile1 $*.text  > /dev/null
	echo lt-proc thrice analyzing $*.text >> $@
	time lt-proc $*.apertium $*.text /dev/null >> $@
	time lt-proc $*.apertium $*.text /dev/null >> $@
	time lt-proc $*.apertium $*.text /dev/null >> $@

# (4) sizes
results4: sizes
sizes: apertium-eu-es.eu.hfst-sizes apertium-nn-nb.nn.hfst-sizes \
	apertium-ga-gv.gv.hfst-sizes apertium-eu-es.eu.apertium-sizes \
	apertium-nn-nb.nn.apertium-sizes apertium-ga-gv.gv.apertium-sizes


%.hfst-sizes: %.hfst
	ls -lh $< > $@
	hfst-summarize $< >> $@

%.apertium-sizes: %.dix
	lt-comp lr $< $*.apertium.lr > $@
	lt-comp rl $< $*.apertium.rl >> $@
	ls -lh $*.apertium.lr $*.apertium.rl >> $@

# (5) look at compilation speed
results5: times2
times2: apertium-eu-es.eu.times2 apertium-nn-nb.nn.times2 \
	apertium-ga-gv.gv.times2

%.times2: %.dix
	echo hfst-apertium2fst thrice compiling $< > $@
	time hfst-apertium2fst $< --profile=$*.profile2 -o /tmp/tmp >> $@ 
	time hfst-apertium2fst $< --profile=$*.profile2 -o /tmp/tmp >> $@
	time hfst-apertium2fst $< --profile=$*.profile2 -o /tmp/tmp >> $@
	echo lt-comp thrice compiling $< > $@
	time lt-comp lr $< /tmp/tmp >> $@
	time lt-comp lr $< /tmp/tmp >> $@
	time lt-comp lr $< /tmp/tmp >> $@

# (6) compile spellers
results6: spellertimes
spellers: apertium-eu-es.eu.zhfst apertium-nn-nb.nn.zhfst \
	apertium-ga-gv.gv.zhfst
spellertimes: apertium-eu-es.eu.times3 apertium-nn-nb.nn.times3 \
	apertium-ga-gv.gv.times3

%.misspelt: %.text
	hfst-proc $*.hfst < $< | egrep -o '\^[^*#/]*/[^*#]' | tr -d '^/' > $*.words
	python lines2misspell.py --input=$*.words --output=$@

%.times3: %.zhfst %.misspelt
	awk 'NR < $(SPELLWORDS) {print $$1}' < $*.misspelt | time hfst-ospell-fsmnlp-2012 --profile=$*.profile3 $< > $*.spells
	awk 'NR < $(SPELLWORDS) {print $$1}' < $*.misspelt | time hfst-ospell-fsmnlp-2012 --profile=$*.profile3 $< > $*.spells
	awk 'NR < $(SPELLWORDS) {print $$1}' < $*.misspelt | time hfst-ospell-fsmnlp-2012 --profile=$*.profile3 $< > $*.spells


%.zhfst: %.dix
	hfst-apertium2fst -v $< -o $@.tmp
	hfst-project -v -p input $@.tmp |\
		hfst-minimize -v |\
		hfst-fst2fst -v -f olw -o acceptor.default.hfst
	python editdist.py --no-elim -d 2 -a acceptor.default.hfst |\
		hfst-txt2fst -v |\
		hfst-minimize -v |\
		hfst-fst2fst -f olw -o errmodel.default.hfst
	sed -e "s/@APERTIUM_NAME@/$*/" index.xml.template > index.xml
	zip -9 $@ errmodel.default.hfst acceptor.default.hfst index.xml
	rm -f $@.tmp $*.errmodel.tmp acceptor.default.hfst index.xml

# here the actual compilation for other tests
%.hfst: %.dix
	hfst-apertium2fst -v $< -o $@.tmp
	hfst-minimize -v $@.tmp |\
		hfst-fst2fst -v -f olw -o $@
	hfst-invert -v $@.tmp |\
		hfst-minimize -v |\
		hfst-fst2fst -f olw -o $@.inv
	rm -f $@.tmp

%.apertium: %.dix
	lt-comp lr $< $@



