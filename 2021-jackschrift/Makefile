
LATEXML=latexml
LATEXMLPOST=latexmlpost

.PHONY: all

all: Pirinen-2021-jack-festschrift.pdf \
	 Pirinen-2021-jack-festschrift.html \
	 infra-diagram.pdf

%.pdf: %.tex infra-diagram.pdf
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

%.html: %.tex
	$(LATEXML) $< | $(LATEXMLPOST) --dest=$@ -
	sed -i -e 's:"LaTeXML.css":"../latexml/LaTeXML.css":'\
		-e 's:"ltx-article.css":"../latexml/ltx-article.css":' $@

%.pdf: %.dia
	dia -e $@ -t pdf $< 

%.svg: %.dia
	dia -e $@ -t svg $< 

clean:
	-rm -f *.log *.bbl *.aux 2016-finnish-mt.pdf
