#include "StreamReinitializer.h"

StreamReinitializer::StreamReinitializer(std::istream &in):
  StreamTransformer(in)
{
  IdentityTransformer id;
  transform_input_data(id);
}

StreamReinitializer::StreamReinitializer(void)
{}

StreamReinitializer &StreamReinitializer::reinitialize(void)
{
  // Test for non-initialized stream.
  (void)get_stream();

  delete transformed_in;
  transformed_in = new std::istringstream(transformed_input_data);

  return *this;
}

void StreamReinitializer::IdentityTransformer::input_line
(const std::string &line)
{ transformed_line = line; }

#ifdef HFST_TAGGER_TEST_StreamReinitializer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const std::string file_content = 
    "a\n"
    "b";

  std::istringstream file_stream(file_content);

  StreamReinitializer stream_reinitializer(file_stream);

  for (size_t i = 0; i < 2; ++i)
    {
      std::istream &in = stream_reinitializer.get_stream();
      
      char line[1000];
      in.getline(line,1000);
      assert(std::string(line) == "a");
      
      in.getline(line,1000);
      assert(std::string(line) == "b");
      
      in.peek();
      assert(in.eof());
      
      stream_reinitializer.reinitialize();
    }
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_StreamReinitializer
