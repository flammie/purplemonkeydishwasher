
.PHONY: all

all: 2015-naacl-smt-morph-segments.pdf

%.pdf: %.tex naacl2015.bib
	xelatex $<
	bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 2015-fiwclul-template.pdf
