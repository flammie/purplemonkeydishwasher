all: Pirinen-cla-2010.pdf

%.pdf: %.tex
	$(LATEX) $<
	$(BIBTEX) $*
	$(LATEX) $<
	$(LATEX) $<
	$(LATEX) $<

