#ifndef HFST_TAGGER_HEADER_TO_EMPTY_STRING_TRANSFORMER_H
#define HFST_TAGGER_HEADER_TO_EMPTY_STRING_TRANSFORMER_H

#include "StringTransformer.h"

class ToEmptyStringTransformer : public StringTransformer
{
 public:
  std::string transform(const std::string &symbol) const;
};

#endif // HFST_TAGGER_HEADER_TO_EMPTY_STRING_TRANSFORMER_H
