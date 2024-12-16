
LATEX=lualatex
BIBTEX=bibtex
AUTHOR=Pirinen
YEAR=2024
CONFERENCE=iwclul
LATEXML=latexml
LATEXMLPOST=latexmlpost

.PHONY: all

PREFIX=$(AUTHOR)-$(YEAR)-$(CONFERENCE)
PAPER=$(PREFIX).pdf
#BEAMER=$(PREFIX)-beamer.pdf
## bibtexes cannot always handle hyphens
BIB=$(CONFERENCE)$(YEAR).bib
HTML=$(PREFIX).html

all: $(PAPER) $(BEAMER) $(BOASTER) $(HTML)

$(BOASTER): $(POSTER)

%.pdf: %.tex $(BIB)
	$(LATEX) $<
	-$(BIBTEX) $*
	$(LATEX) $<
	$(LATEX) $<
	$(LATEX) $<

clean:
	-rm -f *.log *.bbl *.aux $(PAPER) $(BEAMER) $(BOASTER)

LATEXML=latexml
LATEXMLPOST=latexmlpost


%.html: %.tex
	$(LATEXML) --inputencoding=utf-8 $< | $(LATEXMLPOST) --dest=$@ -
	sed -i -e 's:"LaTeXML.css":"../latexml/LaTeXML.css":'\
		-e 's:"ltx-article.css":"../latexml/ltx-article.css":' $@
