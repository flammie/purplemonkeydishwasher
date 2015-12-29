
TEX=xelatex
BIB=bibtex

all: Pirinen-2015-wmt.pdf

%.pdf: %.tex
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<
