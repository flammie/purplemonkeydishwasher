
.PHONY: all

all: Pirinen-2015-cifu-omorfi-beamer.pdf 

%.pdf: %.tex 
	xelatex $<
	xelatex $<

clean:
	-rm -f *.log *.bbl *.aux 
