#ifndef HFST_TAGGER_HEADER_LAST_ENTRY_REMOVER_H
#define HFST_TAGGER_HEADER_LAST_ENTRY_REMOVER_H

#include "StringTransformer.h"

class LastEntryRemover : public StringTransformer
{
 public:
  class IncorrectFieldCount
  {};

  std::string transform(const std::string &symbol) const;
};

#endif // HFST_TAGGER_HEADER_LAST_ENTRY_REMOVER_H
