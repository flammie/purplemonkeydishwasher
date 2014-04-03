# Execute this Makefile with GNU compatible make to recreate the test results
# and paper for article titled
# `blah' in Proceedings of CICLING 2014
#
# point programs to right binaries
XELATEX=xelatex
BIBTEX=bibtex

# article
articles: Pirinen-2014-cicling-beamer.pdf

TUTORIAL_GRAPHICS=anystar.pdf cat.pdf catses.pdf cta2cat.pdf \
				  cta.pdf demo-lm.pdf edit1-ab10.pdf \
				  edit1+en-orth.pdf edit1swap-ab10.pdf \
				  en-confusables.pdf en-orth.pdf \
				  errm-ed1.pdf errm.edit1+en-orth.pdf \
				  errm-ed2.pdf errm-ed7.pdf

%.dot: %.hfst
	hfst-fst2txt -f dot $< -o $@

%.hfst: %.strings
	hfst-strings2fst -j $< |\
		hfst-minimize -o $@

%.hfst: %.txt
	hfst-txt2fst $< |\
		hfst-minimize -o $@

errm-ed7.hfst: errm-ed1.hfst
	hfst-repeat -f 1 -t 7 $< |\
		hfst-minimize -o $@

errm-ed2.hfst: errm-ed1.hfst
	hfst-repeat -f 1 -t 2 $< |\
		hfst-minimize -o $@

edit1+en-orth.hfst: edit1-ab10.hfst en-orth.hfst
	hfst-disjunct edit1-ab10.hfst en-orth.hfst -o $@

errm.edit1+en-orth.hfst: edit1+en-orth.hfst anystar.hfst
	hfst-concatenate anystar.hfst edit1+en-orth.hfst |\
		hfst-concatenate - anystar.hfst |\
		hfst-minimize -o $@


%.pdf: %.dot
	dot -Tpdf -o$@ $<

Pirinen-2014-cicling-beamer.pdf: Pirinen-2014-cicling-beamer.tex $(TUTORIAL_GRAPHICS)
	$(XELATEX) $<
	$(XELATEX) $<
	$(XELATEX) $<

# generic target
all: results articles

