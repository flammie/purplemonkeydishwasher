#ifndef HFST_TAGGER_HEADER_GUESSER_STREAM_TRANSFORMER_H
#define HFST_TAGGER_HEADER_GUESSER_STREAM_TRANSFORMER_H

#include "StreamTransformer.h"

#define GUESS_TAG "<guess>"

class GuesserStreamTransformer : public StreamTransformer
{
 public:

  GuesserStreamTransformer(std::istream &in);
  
 protected:

  class GuessTagger : public StreamTransformer::LineTransformer
    {
    public:
      void input_line(const std::string &line);
    };

};

#endif // HFST_TAGGER_HEADER_GUESSER_STREAM_TRANSFORMER_H
