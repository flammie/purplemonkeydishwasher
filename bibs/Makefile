## run make to convert stuff

LATEXML=latexml
BIB2XML=bib2xml
XML2END=xml2end
SAXON=saxon9-transform

all: pirinen.xml pirinen.enw pirinen.html

%.xml: %.bib
	$(BIB2XML) $< > $@

%.enw: %.xml
	$(XML2END) $< > $@

%.html: %.xml
	$(SAXON) -s:$< mods2html.xsl > $@

check:
	$(LATEXML) --bibtex pirinen.bib > /dev/null
