
TEX=xelatex
BIB=bibtex
LATEXML=latexml
LATEXMLPOST=latexmlpost

all: Pirinen-2008-masters-thesis.pdf Pirinen-2008-masters-thesis.html

%.pdf: %.tex
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<

%.html: %.tex
	$(LATEXML) $< | $(LATEXMLPOST) --dest=$@ -
	sed -i -e 's:"LaTeXML.css":"../latexml/LaTeXML.css":'\
		-e 's:"ltx-article.css":"../latexml/ltx-article.css":' $@
