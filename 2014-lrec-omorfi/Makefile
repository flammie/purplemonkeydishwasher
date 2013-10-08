# Make the pdfs of omorfi article
# by Tommi A Pirinen

TEX=xelatex
BIB=bibtex

all: 2014-lrec-omorfi.pdf

%.pdf: %.tex lrec2014.bib
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<

clean:
	-rm -f *.pdf *.aux *.bbl *.log

