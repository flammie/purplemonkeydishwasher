# Use this makefile to create the phd pdf's of the great
#  ”Finite-State Methods in Spell-Checking”
# by Tommi A Pirinen

TEX=xelatex
BIB=bibtex
MAKEGLOSSARIES=makeglossaries
HT2F=hfst-fst2txt

DISS=Pirinen-2013-dissertation.pdf
PRESENTATIONS=diss-seminar-2013-02-14.pdf
GRAPHIX=edit1-ab-unw.pdf edit-weighted.pdf diss-structure-uml-ish.pdf

all: $(DISS)

presentations: $(PRESENTATIONS)

# edit1-ab-unw.pdf edit-weighted.pdf

$(DISS): Pirinen-2013-dissertation.tex diss.bib $(GRAPHIX)
	$(TEX) $<
	$(BIB) Pirinen-2013-dissertation
	$(MAKEGLOSSARIES) Pirinen-2013-dissertation
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<

%.pdf: %.dia
	dia -e $*.eps -t eps $<
	epstopdf $*.eps

%.pdf: %.tsv
	hfst-txt2fst -f openfst $< | $(HT2F) -f dot -o $*.dot
	dot -Tpdf $*.dot -o$@

clean:
	-rm -f Pirinen-2013-dissertation.aux Pirinen-2013-dissertation.bbl Pirinen-2013-dissertation.blg Pirinen-2013-dissertation.log Pirinen-2013-dissertation.toc Pirinen-2013-dissertation.out Pirinen-2013-dissertation.pdf edit-weighted.pdf edit1-ab-unw.pdf
	-rm -f diss-seminar-2013-02-14.aux diss-seminar-2013-02-14.bbl diss-seminar-2013-02-14.blg diss-seminar-2013-02-14.log diss-seminar-2013-02-14.toc diss-seminar-2013-02-14.out diss-seminar-2013-02-14.pdf
