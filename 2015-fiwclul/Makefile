
.PHONY: all

all: 2015-fiwclul-template.pdf

%.pdf: %.tex
	xelatex $<
	bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<


