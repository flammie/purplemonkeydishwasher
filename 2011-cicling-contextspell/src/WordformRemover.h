#ifndef HFST_TAGGER_HEADER_WORDFORM_REMOVER_H
#define HFST_TAGGER_HEADER_WORDFORM_REMOVER_H

#include <vector>

#include "StringTransformer.h"

class WordformRemover : public StringTransformer
{

 public:
  
  class IncorrectFieldCount
  {};

  std::string transform(const std::string &symbol) const;

 protected:

  typedef std::vector<std::string> StringVector;
  
  StringVector split_at_tabs(const std::string &symbol) const;
  std::string join(const StringVector &string_vector) const;
};

#endif // HFST_TAGGER_HEADER_WORDFORM_REMOVER_H
