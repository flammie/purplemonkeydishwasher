
.PHONY: all

all: 2015-fiwclul-template.pdf 2015-fiwclul-proceedings.pdf \
	2015-fiwclul-business-meating-beamer.pdf

%.pdf: %.tex
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 2015-fiwclul-template.pdf
