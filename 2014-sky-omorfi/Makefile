# Make the pdfs of omorfi article
# by Tommi A Pirinen

TEX=xelatex
BIB=bibtex

all: 2015-sky-omorfi.pdf

%.pdf: %.tex skyomorfi2015.bib
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<

clean:
	-rm -f 2015-sky-omorfi.pdf 2015-sky-omorfi.aux 2015-sky-omorfi.bbl 2015-sky-omorfi.log

# fetch and clean texts
undhr.fi.html:
	wget -O $@ 'http://www.ohchr.org/EN/UDHR/Pages/Language.aspx?LangID=fin'

undhr.fi.text: undhr.fi.html
	awk  '/<h3>/,/<\/div>/ {print}' < undhr.fi.html | sed -e 's/<br\/>/\n/' -e 's/<\/\?h.>/\n/g' -e 's/<\/\?p>/\n/g' -e 's/<li>/\n/' -e 's/<[^>]*>//g' > $@

FIWIKIDATE=20130811

fiwiki-$(FIWIKIDATE)-pages-articles.xml.bz2:
	wget http://dumps.wikimedia.org/fiwiki/$(FIWIKIDATE)/fiwiki-$(FIWIKIDATE)-pages-articles.xml.bz2

%.text: %.xml.bz2
	if ! test -f unpack-wikimedia.bash ; then \
		wget https://raw.github.com/flammie/bash-corpora/master/unpack-wikimedia.bash ; \
	fi
	bash unpack-wikimedia.bash fiwiki $(FIWIKIDATE) > $@

# tests of omorfi article
%.fintwols: %.text
	iconv -c -f utf8 -t latin1//IGNORE < $< | fintwol | iconv -f latin1 -t utf8 > $@

%.omors: %.text
	apertium-destxt < $< | hfst-proc morphology.omor.hfst --xerox > $@


%.pdf: %.dia
	dia $< -e $@

%-crop.pdf: %.pdf
	pdfcrop --margins "0 0 0 300" -clip $< $@

