
.PHONY: all

all: Pirinen-2019-wmt-finnish-english.pdf Pirinen-2019-wmt-finnish-english-poster.pdf

%.pdf: %.tex
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 2016-finnish-mt.pdf
