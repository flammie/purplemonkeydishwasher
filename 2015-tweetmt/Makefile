
TEX=xelatex
BIB=bibtex

all: Pirinen-2015-tweetmt.pdf

%.pdf: %.tex
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<
