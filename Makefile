
.PHONY: all

all: Pirinen-2019-loresmt-karelian-workflow.pdf \
	Pirinen-2019-loresmt-karelian-workflow-beamer.pdf

%.pdf: %.tex
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 2016-finnish-mt.pdf
