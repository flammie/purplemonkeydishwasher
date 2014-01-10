LATEX=xelatex
BIBTEX=bibtex

all: Pirinen-nodalida-2011-omorfi.pdf

%.pdf: %.tex
	$(LATEX) $<
	$(BIBTEX) $*
	$(LATEX) $<
	$(LATEX) $<
	$(LATEX) $<

