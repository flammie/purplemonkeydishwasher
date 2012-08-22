#ifndef HFST_TAGGER_HEADER_STREAM_MARKOVIZER_H
#define HFST_TAGGER_HEADER_STREAM_MARKOVIZER_H

#include <sstream>
#include <iostream>
#include <queue>

#include "StreamTransformer.h"

class StreamMarkovizer : public StreamTransformer
{
 public:

  StreamMarkovizer(size_t n,std::istream &in);

 protected:

  class LineJoiner : public StreamTransformer::LineTransformer
    {
    public:
      
      LineJoiner(size_t n);
      void input_line(const std::string &line);

    protected:

      typedef std::queue<std::string> StringQueue;

      StringQueue string_queue;
      size_t n;

      void push(const std::string &s);
      std::string get_string(void);
    };
};

#endif // HFST_TAGGER_HEADER_STREAM_MARKOVIZER_H
