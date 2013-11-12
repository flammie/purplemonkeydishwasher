SRC=src
DATA=data
BIN=bin
MODELS=models
RESULTS=results

speller-results:
	$(MAKE) -C $(SRC) install

	# Generate English results.
	cat $(DATA)/en_test_data | $(BIN)/word_context_speller \
        $(MODELS)/en_speller 0.99 | sed 's/\[[^	]*\]//g' | \
	$(BIN)/measure_accuracy.pl > $(RESULTS)/en_results

	# Generate Finnish results.
	cat $(DATA)/fi_test_data | $(BIN)/word_context_speller \
        $(MODELS)/fi_speller -710.25 --penalty | sed 's/\[[^	]*\]//g' | \
	$(BIN)/measure_accuracy.pl > $(RESULTS)/fi_results

