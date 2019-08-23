
LATEXML=latexml
LATEXMLPOST=latexmlpost

.PHONY: all

all: Pirinen-2019-loresmt-karelian-workflow.pdf \
	Pirinen-2019-loresmt-karelian-workflow-beamer.pdf \
	Pirinen-2019-loresmt-karelian-workflow.html

Map_of_Karelian_dialects.png:
	wget https://upload.wikimedia.org/wikipedia/commons/a/a7/Map_of_Karelian_dialects.png

%.pdf: %.png
	convert $< $@

%.svg: %.dia
	dia --export=$@ $<

%.pdf: %.svg
	convert $< $@

%.pdf: %.tex Map_of_Karelian_dialects.pdf process-uml.pdf
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
