
.PHONY: all

all: 2015-why-linguistics-in-smt.pdf Pirinen-2015-why-linguistics-in-smt.pdf

%.pdf: %.tex why2015.bib
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 
