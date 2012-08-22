#ifndef HFST_TAGGER_HEADER_LEXICAL_STREAM_TANSFORMER_H
#define HFST_TAGGER_HEADER_LEXICAL_STREAM_TANSFORMER_H

#include "StreamTokenizer.h"

class LexicalStreamTransformer : public StreamTokenizer
{
 public:
  LexicalStreamTransformer(std::istream &in);
};

#endif // HFST_TAGGER_HEADER_LEXICAL_STREAM_TANSFORMER_H
