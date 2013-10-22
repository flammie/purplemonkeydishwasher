#ifndef HFST_TAGGER_HEADER_IDENTITY_TRANSFORMER_H
#define HFST_TAGGER_HEADER_IDENTITY_TRANSFORMER_H

#include "StringTransformer.h"

class IdentityTransformer : public StringTransformer
{
 public:
  std::string transform(const std::string &symbol) const;
};

#endif // HFST_TAGGER_HEADER_IDENTITY_TRANSFORMER_H
