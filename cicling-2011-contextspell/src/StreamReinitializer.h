#ifndef HFST_TAGGER_HEADER_STREAM_REINITIALIZER_H
#define HFST_TAGGER_HEADER_STREAM_REINITIALIZER_H

#include <sstream>
#include <string>
#include <iostream>

#include "StreamTransformer.h"

class StreamReinitializer : public StreamTransformer
{
 public:
  StreamReinitializer(std::istream &in);
  StreamReinitializer(void);
  StreamReinitializer &reinitialize(void);

 protected:
  
  class IdentityTransformer : public StreamTransformer::LineTransformer
  {
  public:
    void input_line(const std::string &line);
  };

};

#endif // HFST_TAGGER_HEADER_STREAM_REINITIALIZER_H
