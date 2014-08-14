
XELATEX=xelatex
GRAPHICS=lattice.pdf alignments.pdf 
#formspertokens.pdf

.PHONY: all

all: abumatran-workshop.pdf

%.pdf: %.dia
	dia $< -e $@

%.pdf: %.dot
	dot -Tpdf -o$@ $<

%.dot: %.hfst
	hfst-fst2txt -f dot $< -o $@

%.hfst: %.strings
	hfst-strings2fst -j $< |\
		hfst-minimize -o $@

%.hfst: %.txt
	hfst-txt2fst $< |\
		hfst-minimize -o $@

%.pdf: %.tex $(GRAPHICS)
	$(XELATEX) $<
	$(XELATEX) $<
	$(XELATEX) $<

