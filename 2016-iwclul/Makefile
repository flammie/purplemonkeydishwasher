
.PHONY: all

all: 2016-sigur-meeting-beamer.pdf Pirinen-2016-abumatran-poster-boaster.pdf UD_tutorial.pdf Pirinen-2016-smt-morph-segments.pdf Pirinen-2016-iwclul-rbmt-representations.pdf

%.pdf: %.tex
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 2016-finnish-mt.pdf
