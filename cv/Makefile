
.PHONY: all

all: Pirinen-Curriculum-Vitae.pdf 

%.pdf: %.tex
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 2016-finnish-mt.pdf
