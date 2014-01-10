LATEX=xelatex
BIBTEX=bibtex

all: Pirinen-il-2010.pdf

%.pdf: %.tex
	$(LATEX) $<
	$(BIBTEX) $*
	$(LATEX) $<
	$(LATEX) $<
	$(LATEX) $<

