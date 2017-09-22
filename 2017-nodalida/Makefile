
LATEX=xelatex
BIBTEX=bibtex
AUTHOR=Pirinen
YEAR=2017
TITLE=fin-sme
CONFERENCE=nodalida

.PHONY: all

PREFIX=$(AUTHOR)-$(YEAR)-$(CONFERENCE)-$(TITLE)
PAPER=$(PREFIX).pdf
BEAMER=$(PREFIX)-beamer.pdf
#POSTER=$(PREFIX)-poster.pdf
#BOASTER=$(PREFIX)-beamer-boaster.pdf
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
