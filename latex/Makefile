# use make to install my tex classes or stuffs

TEXMFHOME=${HOME}/texmf
INSTALL=install
TEXHASH=texhash

.PHONY: install

install:
	@echo installing flammie.cls to $(TEXMFHOME)
	$(INSTALL) -d $(TEXMFHOME)/tex/latex/flammie/
	$(INSTALL) flammie.cls $(TEXMFHOME)/tex/latex/flammie/
	$(TEXHASH) --verbose $(TEXMFHOME)


