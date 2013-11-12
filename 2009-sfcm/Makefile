<<<<<<< Makefile
HLEXC=hfst-lexc
HLEXC_FLAGS=-t
HTWOLC=hfst-twolc
=======
HLEXC=/usr/local/bin/hfst-lexc-sfcm-2009
HLEXC_FLAGS=-O multichar-parser-none -t
HTWOLC=~mpsilfve/bin/hfst-twolc-static
>>>>>>> 1.10
HTWOLC_FLAGS = --resolve --no-report
HIC=hfst-compose-intersect
CSV2HLEXC = python csv2lexc.py
SAXON=saxon-xslt

LATEX		= latex
LATEXFLAGS	= 
PDFLATEX	= pdflatex
PDFLATEXFLAGS	= 
DVIPS		= dvips
DVIPSFLAGS	= -Pps -Ptype1 
DVIPDF		= dvipdfm
DVIPDFFLAGS	= 
BIBTEX		= bibtex
BIBTEXFLAGS	= 
SPELL		= tmispell
SPELLFLAGS	= -d finnish -T tex
CONVERT		= convert
CONVERTFLAGS	= 
#RECODE		= recode -d
SCP			= scp
SCPFLAGS	= 
REMOTE_DIR	= tapirine@ruuvi.helsinki.fi:public_html/paperit/

BINSOURCES = Makefile \
	omorfi.hlexc kotus-sanalista-1a.hlexc inflection.hlexc derivations.hlexc \
	stemparts.hlexc exceptions.hlexc \
	omorfi.twolc northern-sami.hlexc sami.twolc
BINTARGETS = omorfi.lexc.hfst omorfi.twolc.hfst omorfi.hfst northern-sami.lexc.hfst northern-sami.twolc.hfst northern-sami.hfst french.hfst

DOCSOURCES = hfst-sfcm.tex
DOCTARGETS = hfst-sfcm.pdf hfst-sfcm.ps

DISTBALLS = sfcm-2009-data.tar.bz2 sfcm-2009-article.tar.bz2

all: docs bins dist

docs: $(DOCTARGETS)

bins: $(BINTARGETS)

clean: 
	-rm -f $(DOCTARGETS) $(BINTARGETS) $(DISTBALLS)

omorfi.lexc.hfst: omorfi.hlexc kotus-sanalista-1a.hlexc stemparts.hlexc inflection.hlexc derivations.hlexc exceptions.hlexc
	$(HLEXC) $(HLEXC_FLAGS) -o $@ $^

omorfi.lexc.hwfst: omorfi.hlexc kotus-sanalista-1a.hlexc stemparts.hlexc inflection.hlexc derivations.hlexc exceptions.hlexc
	$(HLEXC) $(HLEXC_FLAGS) -w -o $@ $^

omorfi.twolc.hfst: omorfi.twolc
	$(HTWOLC) $(HTWOLC_FLAGS) --input $< > $@

omorfi.hfst: omorfi.twolc.hfst omorfi.lexc.hfst
	cat omorfi.twolc.hfst | $(HIC) -l omorfi.lexc.hfst > $@

northern-sami.lexc.hfst: northern-sami.hlexc
	$(HLEXC) $(HLEXC_FLAGS) -o $@ $^

northern-sami.lexc.hwfst: northern-sami.hlexc
	$(HLEXC) $(HLEXC_FLAGS) -w -o $@ $^

northern-sami.twolc.hfst: sami.twolc
	$(HTWOLC) $(HTWOLC_FLAGS) --input $< > $@

northern-sami.hfst: northern-sami.lexc.hfst northern-sami.twolc.hfst
	cat northern-sami.lexc.hfst northern-sami.twolc.hfst | $(HIC) > $@

french.hfst: french.hlexc
	$(HLEXC) $(HLEXC_FLAGS) -o $@ $^

french.hwfst: french.hlexc
	$(HLEXC) $(HLEXC_FLAGS) -w -o $@ $^

dist: dist-bzip2

dist-bzip2: $(BINSOURCES) $(BINTARGETS) $(DOCSOURCES) $(DOCTARGETS)
	-rm -rf dist/sfcm-2009
	mkdir -p dist/sfcm-2009/
	cp $(BINSOURCES) $(BINTARGETS) dist/sfcm-2009
	tar -C dist -cjvf sfcm-2009-data.tar.bz2 sfcm-2009
	-rm -rf dist/sfcm-2009
	mkdir -p dist/sfcm-2009
	cp $(DOCSOURCES) $(DOCTARGETS) dist/sfcm-2009/
	tar -C dist -cjvf sfcm-2009-article.tar.bz2 sfcm-2009

upload:
	scp $(DISTBALLS) $(DOCTARGETS) ruuvi:public_html/paperit/

kotus-sanalista-1a.hlexc: kotus-sanalista-1a.csv
	$(CSV2HLEXC) --input=$< --output=$@

kotus-sanalista-1a.csv: kotus-sanalista-1a.xml
	$(SAXON) -o $@ $< kotus2csv.xslt


%.dvi : %.tex
	$(LATEX) $(LATEXFLAGS) $<
	if grep 'undefined citations' $*.log > /dev/null || \
			grep 'Citation.*undefined' $*.log > /dev/null ; then \
		$(BIBTEX) $(BIBTEXFLAGS) $* ;\
		$(LATEX) $(LATEXFLAGS) $< ;\
	fi
	if grep 'Warning: Label(s) may' $*.log > /dev/null || \
			grep 'Rerun' $*.log > /dev/null || \
			grep 'Warning: Citation' $*.log > /dev/null; then \
		$(LATEX) $(LATEXFLAGS) $< ;\
	fi
	if grep 'Warning: Label(s) may' $*.log > /dev/null || \
			grep 'Rerun' $*.log > /dev/null || \
			grep 'Warning: Citation' $*.log > /dev/null; then \
		$(LATEX) $(LATEXFLAGS) $< ;\
	fi
	if grep 'Warning: Label(s) may' $*.log > /dev/null || \
			grep 'Rerun' $*.log > /dev/null || \
			grep 'Warning: Citation' $*.log > /dev/null; then \
		$(LATEX) $(LATEXFLAGS) $< ;\
	fi

# using pdflatex
%.pdf: %.tex
	$(PDFLATEX) $(PDFLATEXFLAGS) $<
	if grep 'undefined citations' $*.log > /dev/null || \
			grep 'Citation.*undefined' $*.log > /dev/null ; then \
		$(BIBTEX) $(BIBTEXFLAGS) $* ;\
		$(PDFLATEX) $(PDFLATEXFLAGS) $< ;\
	fi
	if grep 'Warning: Label(s) may' $*.log > /dev/null || \
			grep 'Rerun' $*.log > /dev/null || \
			grep 'Warning: Citation' $*.log > /dev/null; then \
		$(PDFLATEX) $(PDFLATEXFLAGS) $< ;\
	fi
	if grep 'Warning: Label(s) may' $*.log > /dev/null || \
			grep 'Rerun' $*.log > /dev/null || \
			grep 'Warning: Citation' $*.log > /dev/null; then \
		$(PDFLATEX) $(PDFLATEXFLAGS) $< ;\
	fi
	if grep 'Warning: Label(s) may' $*.log > /dev/null || \
			grep 'Rerun' $*.log > /dev/null || \
			grep 'Warning: Citation' $*.log > /dev/null; then \
		$(PDFLATEX) $(PDFLATEXFLAGS) $< ;\
	fi

%.ps: %.dvi
	$(DVIPS) $(DVIPSFLAGS) -o $@ $<

# using pdfm
#%.pdf: %.dvi
#	$(DVIPDF) $(DVIPDFFLAGS) $<

# graphics for latex dvips
%.eps: %.png
	$(CONVERT) $< $(CONVERTFLAGS) $@
