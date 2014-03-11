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

GRAPHICS=anystar.pdf cat.pdf catses.pdf cta2cat.pdf \
				  cta.pdf demo-lm.pdf edit1-ab10.pdf \
				  edit1+en-orth.pdf edit1swap-ab10.pdf \
				  en-confusables.pdf en-orth.pdf \
				  errm-ed1.pdf errm.edit1+en-orth.pdf
.PHONY: all

all: abumatran-weighted-fst.pdf

%.pdf: %.dot
	dot -Tpdf -o$@ $<

%.dot: %.hfst
	hfst-fst2txt -f dot $< -o $@

%.hfst: %.strings
	hfst-strings2fst -j $< -o $@

%.hfst: %.txt
	hfst-txt2fst $< -o $@

edit1+en-orth.hfst: edit1-ab10.hfst en-orth.hfst
	hfst-disjunct edit1-ab10.hfst en-orth.hfst -o $@

errm-ed1.hfst: edit1-ab10.hfst anystar.hfst
	hfst-concatenate anystar.hfst edit1-ab10.hfst |\
		hfst-concatenate - anystar.hfst |\
		hfst-minimize -o $@

errm.edit1+en-orth.hfst: edit1+en-orth.hfst anystar.hfst
	hfst-concatenate anystar.hfst edit1+en-orth.hfst |\
		hfst-concatenate - anystar.hfst |\
		hfst-minimize -o $@

abumatran-weighted-fst.pdf: abumatran-weighted-fst.tex $(GRAPHICS)
	$(XELATEX) $<
	$(XELATEX) $<
	$(XELATEX) $<

