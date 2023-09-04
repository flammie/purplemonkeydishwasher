
LATEX=xelatex
BIBTEX=bibtex
AUTHOR=Wiechetek
YEAR=2023
CONFERENCE=ranlp
LATEXML=latexml
LATEXMLPOST=latexmlpost

.PHONY: all

PREFIX=$(AUTHOR)-$(YEAR)-$(CONFERENCE)
PAPER=$(PREFIX).pdf
## bibtexes cannot always handle hyphens
BIB=$(CONFERENCE)$(YEAR).bib

all: $(PAPER) $(BEAMER) $(BOASTER)

$(BOASTER): $(POSTER)

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
