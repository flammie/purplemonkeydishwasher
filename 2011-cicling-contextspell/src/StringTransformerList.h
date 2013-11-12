#ifndef HFST_TAGGER_HEADER_STRING_TRANSFORMER_LIST_H
#define HFST_TAGGER_HEADER_STRING_TRANSFORMER_LIST_H

#include "StringTransformer.h"

class StringTransformerList : public StringTransformer
{
 public:
  StringTransformerList(void);
  StringTransformerList(const StringTransformer &head,
			const StringTransformerList &tail);
  std::string transform(const std::string &symbol) const;

 protected:
  const StringTransformer * headp;
  const StringTransformerList * tailp;
};

#endif // HFST_TAGGER_HEADER_STRING_TRANSFORMER_LIST_H
