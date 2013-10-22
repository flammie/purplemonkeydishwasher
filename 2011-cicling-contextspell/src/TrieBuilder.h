#ifndef HFST_TAGGER_HEADER_TRIE_BUILDER_H
#define HFST_TAGGER_HEADER_TRIE_BUILDER_H

#include <limits>

#include "ModelBuilder.h"
#include "SequenceWeightTable.h"

class TrieBuilder : public ModelBuilder
{
 public:

  TrieBuilder(const SequenceWeightTable &model_weights);

 protected:

  void add_sequence(const std::string &sequence,float weight);
};

#endif // HFST_TAGGER_HEADER_TRIE_BUILDER_H
