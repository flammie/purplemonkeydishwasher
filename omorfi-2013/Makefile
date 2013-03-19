# Make the pdfs of omorfi article
# by Tommi A Pirinen

TEX=xelatex
BIB=bibtex

all: omorfi-2013.pdf

%.pdf: %.tex omorfi2013.bib
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<
