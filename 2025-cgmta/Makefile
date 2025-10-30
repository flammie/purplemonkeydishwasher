
LATEX=lualatex
BIBTEX=bibtex
AUTHOR=Pirinen
YEAR=2025
TITLE=
CONFERENCE=cgmta
LATEXML=latexml
LATEXMLPOST=latexmlpost
SED=gsed

.PHONY: all

PREFIX=$(AUTHOR)-$(YEAR)-$(CONFERENCE)
PAPER=$(PREFIX).pdf
ONLINE=$(PREFIX).html
## bibtexes cannot always handle hyphens
BIB=$(CONFERENCE)$(YEAR).bib

all: $(PAPER) $(ONLINE) $(BEAMER) $(BOASTER)

$(BOASTER): $(POSTER)

%.pdf: %.tex $(BIB)
	-$(LATEX) $<
	-$(BIBTEX) $*
	$(LATEX) $<
	$(LATEX) $<
	$(LATEX) $<

clean:
	-rm -f *.log *.bbl *.aux $(PAPER) $(BEAMER) $(BOASTER)

%.html: %.tex
	$(LATEXML) --inputencoding=utf-8 $< | $(LATEXMLPOST) --dest=$@ -
	$(SED) -i -e 's:"LaTeXML.css":"../latexml/LaTeXML.css":'\
		-e 's:"ltx-article.css":"../latexml/ltx-article.css":' $@
