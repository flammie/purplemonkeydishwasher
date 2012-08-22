CXXFLAGS=-Wall -Wextra -Wfatal-errors -O3
LDFLAGS=-lhfst
TARGETS=context_speller

all:$(TARGETS)

install:all
	cp $(TARGETS) ../bin/

clean:
	rm -f $(TARGETS)

context_speller:context_speller.cc Speller.cc HMMTagger.cc \
                SuggestionsInContext.cc Tagger.cc NGramAbstracter.cc \
		CompletedCycleBuilder.cc CycleBuilder.cc ModelBuilder.cc\
		LogSequenceWeightTable.cc SequenceWeightTable.cc \
		StringTransformerList.cc SequenceCounter.cc \
                SequenceWeighter.cc WordformRemover.cc \
                LastEntryRemover.cc StreamMarkovizer.cc \
		StreamTransformer.cc NGramModelConstructor.cc \
	        ComposeIntersectNGramModelPair.cc \
                ComposeIntersectNGramModel.cc \
                StreamReinitializer.cc SequenceModel.cc \
                StandardHMMLexicalModel.cc LexicalModel.cc \
                LexiconBuilder.cc GuesserBuilder.cc \
                WordformProbabilityListBuilder.cc LanguageModel.cc \
                IdentityTransformer.cc LexicalStreamTransformer.cc \
                GuesserDivisorTransformer.cc \
                LexiconDivisorTransformer.cc TrieBuilder.cc \
                ToEmptyStringTransformer.cc GuesserStreamTransformer.cc \
                StreamFieldInverter.cc \
                WordformProbabilityListTransformer.cc \
                StreamTokenizer.cc

