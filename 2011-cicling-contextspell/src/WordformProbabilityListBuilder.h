#ifndef HFST_TAGGER_HEADER_WORDFORM_PROBABILITY_LIST_BUILDER_H
#define HFST_TAGGER_HEADER_WORDFORM_PROBABILITY_LIST_BUILDER_H

#include "TrieBuilder.h"
#include "WordformProbabilityListTransformer.h"

class WordformProbabilityListBuilder : public TrieBuilder
{
 public:
  WordformProbabilityListBuilder(std::istream &in);
};

#endif // HFST_TAGGER_HEADER_WORDFORM_PROBABILITY_LIST_BUILDER_H
