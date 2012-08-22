#ifndef HFST_TAGGER_HEADER_STRING_TRANSFORMER_H
#define HFST_TAGGER_HEADER_STRING_TRANSFORMER_H

#include <string>

// Default symbol used when input is abstracted. E.g. used to signify an
// abstract wordform or tag.
#define DEFAULT_SYMBOL "<DEFAULT>"

// Abstract super-class for string transformers, which rewrite strings to 
// other strings.
class StringTransformer
{

 public:

  class MalformedInputData
  {};

  // Return the string @a symbol transformed.
  virtual std::string transform(const std::string &symbol) const = 0;

};

#endif // HFST_TAGGER_HEADER_STRING_TRANSFORMER_H
