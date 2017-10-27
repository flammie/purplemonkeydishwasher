
LATEX=xelatex
BIBTEX=bibtex
AUTHOR=Pirinen
YEAR=2017
TITLE=apefindeu
CONFERENCE=finmt

.PHONY: all

PREFIX=$(AUTHOR)-$(YEAR)-$(CONFERENCE)-$(TITLE)
#PAPER=$(PREFIX).pdf
BEAMER=$(PREFIX)-beamer.pdf
#POSTER=$(PREFIX)-poster.pdf
#BOASTER=$(PREFIX)-beamer-boaster.pdf
## bibtexes cannot always handle hyphens
BIB=$(CONFERENCE)$(YEAR).bib

all: $(PAPER) $(BEAMER) $(BOASTER)

$(BOASTER): $(POSTER)

%.pdf: %.tex $(BIB)
	$(LATEX) $<
	-$(BIBTEX) $*
	$(LATEX) $<
	$(LATEX) $<
	$(LATEX) $<

clean:
	-rm -f *.log *.bbl *.aux $(PAPER) $(BEAMER) $(BOASTER)
