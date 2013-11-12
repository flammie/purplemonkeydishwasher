# Rebuild nodalida papers and beamers

LATEX=xelatex
BIBTEX=bibtex

PAPER=Pirinen-nodalida-2009.pdf
BEAMER=Pirinen-nodalida-2009-beamer.pdf

all: $(PAPER)

%.pdf: %.tex
	$(LATEX) $<
	$(BIBTEX) $*
	$(LATEX) $<
	$(LATEX) $<
