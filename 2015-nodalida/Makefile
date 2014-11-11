
.PHONY: all

all: 2015-nodalida-mt-comp.pdf

%.pdf: %.tex nodalida2015.bib
	xelatex $<
	bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 
