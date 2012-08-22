#ifndef HFST_TAGGER_HEADER_N_GRAM_ABSTRACTER_H
#define HFST_TAGGER_HEADER_N_GRAM_ABSTRACTER_H

#include <utility>
#include <vector>

typedef std::pair<bool,bool> EntryAbstracter;
typedef std::vector<EntryAbstracter> EntryAbstracterVector;

#include "StringTransformer.h"


class NGramAbstracter : public StringTransformer
{
 public:
  class IncorrectFieldCount {};

  class MalformedConfigurationString {};

  NGramAbstracter(const EntryAbstracterVector &entry_abstracter_vector);
  NGramAbstracter(const std::string &abstracter_string);
  std::string transform(const std::string &symbol) const;  

 protected:
  EntryAbstracterVector entry_abstracter_vector;
};

#endif // HFST_TAGGER_HEADER_N_GRAM_ABSTRACTER_H
