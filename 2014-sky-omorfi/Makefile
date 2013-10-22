# Make the pdfs of omorfi article
# by Tommi A Pirinen

TEX=xelatex
BIB=bibtex

all: omorfi-2013.pdf

%.pdf: %.tex omorfi2013.bib
	$(TEX) $<
	$(BIB) $*
	$(TEX) $<
	$(TEX) $<
	$(TEX) $<

clean:
	-rm -f omorfi-2013.pdf omorfi-2013.aux omorfi-2013.bbl omorfi-2013.log

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
