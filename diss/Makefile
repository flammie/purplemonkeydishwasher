# Use this makefile to create the phd pdf's of the great
#  ”Finite-State Methods in Spell-Checking”
# by Tommi A Pirinen

TEX=xelatex
BIB=bibtex

all: Pirinen-2012-dissertation.pdf

%.pdf: %.tex diss.bib
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<


clean:
	-rm -f Pirinen-2012-dissertation.aux Pirinen-2012-dissertation.bbl Pirinen-2012-dissertation.blg Pirinen-2012-dissertation.log Pirinen-2012-dissertation.toc Pirinen-2012-dissertation.out Pirinen-2012-dissertation.pdf
