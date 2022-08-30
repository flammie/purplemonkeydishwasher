
LATEX=xelatex
BIBTEX=bibtex
AUTHOR1=Wiechetek
AUTHOR2=Kaalep
YEAR=2022
CONFERENCE=trondschrift
LATEXML=latexml
LATEXMLPOST=latexmlpost

.PHONY: all

PREFIX=$(AUTHOR2)-$(YEAR)-$(CONFERENCE)
PAPER=$(PREFIX).pdf
WEB=$(PREFIX).html
## bibtexes cannot always handle hyphens
BIB=$(CONFERENCE).bib

all: $(PAPER) $(WEB)

%.pdf: %.tex $(BIB)
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux $(PAPER) $(BEAMER) $(BOASTER)

TEX=xelatex
BIB=bibtex
LATEXML=latexml
LATEXMLPOST=latexmlpost


%.html: %.tex
	$(LATEXML) --inputencoding=utf-8 $< | $(LATEXMLPOST) --dest=$@ -
	sed -i -e 's:"LaTeXML.css":"../latexml/LaTeXML.css":'\
		-e 's:"ltx-article.css":"../latexml/ltx-article.css":' $@
