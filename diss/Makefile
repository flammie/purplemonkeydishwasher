# Use this makefile to create the phd pdf's of the great
#  ”Finite-State Methods in Spell-Checking”
# by Tommi A Pirinen

TEX=xelatex
BIB=bibtex
MAKEGLOSSARIES=makeglossaries
HT2F=hfst-fst2txt

DISS=Pirinen-2014-dissertation.pdf
PRESENTATIONS=diss-seminar-2013-02-14.pdf
GRAPHIX=edit1-ab-unw.pdf edit-weighted.pdf diss-structure-uml-ish.pdf
LICENCES=cc-by-nc-nd-unported-3.tex cc-by-nc-nd-unported-3-deed.tex

all: $(DISS)

presentations: $(PRESENTATIONS)

# edit1-ab-unw.pdf edit-weighted.pdf

$(DISS): Pirinen-2014-dissertation.tex diss.bib $(LICENCES) $(GRAPHIX)
	$(TEX) $<
	$(BIB) Pirinen-2014-dissertation
	$(MAKEGLOSSARIES) Pirinen-2014-dissertation
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
	-rm -f Pirinen-2014-dissertation.aux Pirinen-2014-dissertation.bbl Pirinen-2014-dissertation.blg Pirinen-2014-dissertation.log Pirinen-2014-dissertation.toc Pirinen-2014-dissertation.out Pirinen-2014-dissertation.pdf edit-weighted.pdf edit1-ab-unw.pdf
	-rm -f diss-seminar-2013-02-14.aux diss-seminar-2013-02-14.bbl diss-seminar-2013-02-14.blg diss-seminar-2013-02-14.log diss-seminar-2013-02-14.toc diss-seminar-2013-02-14.out diss-seminar-2013-02-14.pdf
