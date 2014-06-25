## Process this file with automake to create Makefile.in

## This is Makefile for mt marathon 2014 experiments by Flammie and all.
## run make to reproduce.

all: 2014-mtm-fin-eng.pdf

%.pdf: %.tex
	$(XELATEX) $<
	$(BIBTEX) $*
	$(XELATEX) $<
	$(XELATEX) $<
	$(XELATEX) $<

clean-local:
	-rm 2014-mtm-fin-eng.pdf 2014-mtm-fin-eng.aux 2014-mtm-fin-eng.log \
		2014-mtm-fin-eng.bbl 2014-mtm-fin-eng.blg
