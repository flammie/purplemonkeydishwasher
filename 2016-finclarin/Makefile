
LATEX=xelatex
BIBTEX=bibtex
AUTHOR=Pirinen
YEAR=2016
TITLE=sigur
TITLE2=inel
CONFERENCE=finclarin

.PHONY: all

PREFIX=$(AUTHOR)-$(YEAR)-$(CONFERENCE)-$(TITLE)
PREFIX2=$(AUTHOR)-$(YEAR)-$(CONFERENCE)-$(TITLE2)
BEAMER=$(PREFIX)-beamer.pdf $(PREFIX2)-beamer.pdf
## bibtexes cannot always handle hyphens
BIB=$(CONFERENCE)$(YEAR).bib

all: $(BEAMER)

%.pdf: %.tex $(BIB)
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux $(PAPER) $(BEAMER) $(BOASTER)
