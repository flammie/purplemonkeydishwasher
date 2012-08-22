#ifndef HFST_TAGGER_HEADER_STREAM_TRANSFORMER_H
#define HFST_TAGGER_HEADER_STREAM_TRANSFORMER_H

#include <sstream>
#include <string>

class StreamTransformer
{
 public:

  class MaxLineLengthExceeded
  {};

  class FileNotReadable
  {};
  
  class ObjectNotProperlyInitialized
  {};

  class MalformedInputData
  {};

  StreamTransformer(std::istream &in);
  StreamTransformer(void);
  ~StreamTransformer(void);
  std::istringstream &get_stream(void);
  
 protected:

  class LineTransformer
  {
  public:

    virtual void input_line(const std::string &line) = 0;
    bool output_exists(void);
    std::string output_line(void);

  protected:

    std::string transformed_line;
  };
  
  std::string input_data;
  std::string transformed_input_data;
  std::istringstream * transformed_in;

  std::string read_input(std::istream &in);
  void set_transformed_stream(void);
  void transform_input_data(LineTransformer &line_transformer);
};


#endif // HFST_TAGGER_HEADER_STREAM_TRANSFORMER_H
