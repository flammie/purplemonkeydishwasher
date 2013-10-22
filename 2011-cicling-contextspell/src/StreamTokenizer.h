#ifndef HFST_TAGGER_HEADER_STREAM_TOKENIZER_H
#define HFST_TAGGER_HEADER_STREAM_TOKENIZER_H

#include <hfst/HfstTokenizer.h>

using hfst::HfstTokenizer;

#include "StreamTransformer.h"

class StreamTokenizer : public StreamTransformer
{
 public:

  StreamTokenizer(std::istream &in);

 protected:

  class FirstFieldTokenizer : public StreamTransformer::LineTransformer
    {
    public:
      void input_line(const std::string &line);
    protected:
      HfstTokenizer tokenizer;
    };
};

#endif // HFST_TAGGER_HEADER_STREAM_TOKENIZER_H
