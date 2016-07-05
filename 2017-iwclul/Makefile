
.PHONY: all

all: 2017-iwclul-template.pdf 2017-iwclul-template.zip \
	2017-iwclul-template.tar.xz \
	2017-iwclul-template.tar.bz2 \
	2017-iwclul-template.tar.gz

%.pdf: %.tex
	xelatex $<
	-bibtex $*
	xelatex $<
	xelatex $<
	xelatex $<

2017-iwclul-template.zip: 2017-iwclul-template.tex iwclul2017.bib Makefile
	zip $@ $^

2017-iwclul-template.tar.gz: 2017-iwclul-template.tex iwclul2017.bib Makefile
	tar zcvf $@ $^

2017-iwclul-template.tar.bz2: 2017-iwclul-template.tex iwclul2017.bib Makefile
	tar jcvf $@ $^

2017-iwclul-template.tar.xz: 2017-iwclul-template.tex iwclul2017.bib Makefile
	tar Jcvf $@ $^

clean:
	-rm -f *.log *.bbl *.aux 2017-iwclul-template.pdf
