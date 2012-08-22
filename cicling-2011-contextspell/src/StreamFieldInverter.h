#ifndef HFST_TAGGER_HEADER_STREAM_FILED_INVERTER_H
#define HFST_TAGGER_HEADER_STREAM_FILED_INVERTER_H

#include <string>
#include <sstream>

#include <hfst/HfstTransducer.h>

using hfst::HfstTokenizer;

#include "StreamTransformer.h"

class StreamFieldInverter : public StreamTransformer
{
 public:

  StreamFieldInverter(std::istream &in);

 protected:

  class LineInverter : public StreamTransformer::LineTransformer
    {
    public:

      void input_line(const std::string &line);

    protected:

      HfstTokenizer tokenizer;

      std::string inverted_line;
      std::string invert_string(const std::string &str);
    };
};

#endif // HFST_TAGGER_HEADER_STREAM_FILED_INVERTER_H
