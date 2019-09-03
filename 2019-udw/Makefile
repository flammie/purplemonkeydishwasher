
LATEXML=latexml
LATEXMLPOST=latexmlpost

.PHONY: all

all: Pirinen-2019-udw-karelians.pdf Pirinen-2019-udw-karelians-beamer.pdf \
	 Pirinen-2019-udw-karelians.html

%.pdf: %.tex
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

%.html: %.tex
	$(LATEXML) $< | $(LATEXMLPOST) --dest=$@ -
	sed -i -e 's:"LaTeXML.css":"../latexml/LaTeXML.css":'\
		-e 's:"ltx-article.css":"../latexml/ltx-article.css":' $@

clean:
	-rm -f *.log *.bbl *.aux 2016-finnish-mt.pdf
