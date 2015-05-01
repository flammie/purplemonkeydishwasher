
.PHONY: all

all: 2015-nodalida-omorfi.pdf 2015-nodalida-cg-reweight.pdf \
	Pirinen-2015-nodalida-cg-reweight.pdf

%.pdf: %.tex nodalida2015.bib
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 
