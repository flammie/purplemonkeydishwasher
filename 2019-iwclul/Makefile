
FILES=Pirinen-2019-iwclul-neural-finnish.tex iwclul.bib Makefile acl_natbib.bst

.PHONY: all

all: Pirinen-2019-iwclul-neural-finnish.pdf Pirinen-2019-iwclul-neural-finnish-poster.pdf Pirinen-2019-iwclul-neural-finnish-beamer-boaster.pdf

%.pdf: %.tex
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux iwclul-template.pdf
