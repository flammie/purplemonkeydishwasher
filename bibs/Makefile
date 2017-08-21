## run make to convert stuff

BIB2XML=bib2xml
XML2END=xml2end

all: pirinen.xml pirinen.enw

%.xml: %.bib
	$(BIB2XML) $< > $@

%.enw: %.xml
	$(XML2END) $< > $@
