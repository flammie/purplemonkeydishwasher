#ifndef HFST_TAGGER_HEADER_LEXICON_DIVISOR_TRANSFORMER_H
#define HFST_TAGGER_HEADER_LEXICON_DIVISOR_TRANSFORMER_H

#include "StringTransformer.h"

class LexiconDivisorTransformer : public StringTransformer
{
 public:
  std::string transform(const std::string &symbol) const;
};

#endif // HFST_TAGGER_HEADER_LEXICON_DIVISOR_TRANSFORMER_H
