
LATEX=xelatex
BIBTEX=bibtex
YEAR=2023
TITLE=rblt
LATEXML=latexml
LATEXMLPOST=latexmlpost

.PHONY: all

## bibtexes cannot always handle hyphens
BIB=$(TITLE)$(YEAR).bib

PDFS=foreword.pdf introduction.pdf fsa.pdf giellalt.pdf
HTMLS=foreword.html introduction.html fsa.html giellalt.html

all: $(PDFS) $(HTMLS)

fsa.pdf: catses.pdf catses2.pdf edit-1.pdf

%.pdf: %.dot
	dot -Tpdf $< > $@

%.pdf: %.tex $(BIB)
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux $(PDFS) $(HTMLS)

%.html: %.tex
	$(LATEXML) --inputencoding=utf-8 $< | $(LATEXMLPOST) --dest=$@ -
	sed -i -e 's:"LaTeXML.css":"../latexml/LaTeXML.css":'\
		-e 's:"ltx-article.css":"../latexml/ltx-article.css":' $@
