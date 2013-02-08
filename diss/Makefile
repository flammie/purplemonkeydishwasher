# Use this makefile to create the phd pdf's of the great
#  ”Finite-State Methods in Spell-Checking”
# by Tommi A Pirinen

TEX=xelatex
BIB=bibtex

all: Pirinen-2012-dissertation.pdf diss-seminar-2013-02-14.pdf

Pirinen-2012-dissertation.pdf: Pirinen-2012-dissertation.tex diss.bib
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<

diss-seminar-2013-02-14.pdf: diss-seminar-2013-02-14.tex
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<

clean:
	-rm -f Pirinen-2012-dissertation.aux Pirinen-2012-dissertation.bbl Pirinen-2012-dissertation.blg Pirinen-2012-dissertation.log Pirinen-2012-dissertation.toc Pirinen-2012-dissertation.out Pirinen-2012-dissertation.pdf
	-rm -f diss-seminar-2013-02-14.aux diss-seminar-2013-02-14.bbl diss-seminar-2013-02-14.blg diss-seminar-2013-02-14.log diss-seminar-2013-02-14.toc diss-seminar-2013-02-14.out diss-seminar-2013-02-14.pdf
