#include "StreamTransformer.h"
#include <iostream>

StreamTransformer::StreamTransformer(std::istream &in):
  transformed_in(0)
{ input_data = read_input(in); }

StreamTransformer::StreamTransformer(void):
  transformed_in(0)
{}

StreamTransformer::~StreamTransformer(void)
{ delete transformed_in; }

std::istringstream &StreamTransformer::get_stream(void)
{
  if (transformed_in == 0)
    { throw MalformedInputData(); }
  return *transformed_in;
}

std::string StreamTransformer::read_input(std::istream &in)
{
  (void)in.peek();
  if (in.bad() or in.eof())
    { throw FileNotReadable(); }

  std::string input;
  input.reserve(in.tellg());

  in.seekg(0);

  int c;
  while ((c = in.get()) != -1)
    { input.push_back(static_cast<char>(c)); }
  
  return input;
}

void StreamTransformer::set_transformed_stream(void)
{
  input_data.resize(0);
  transformed_in = new std::istringstream(transformed_input_data);
}

void StreamTransformer::transform_input_data
(StreamTransformer::LineTransformer &line_transformer)
{
  size_t begin_pos = std::string::npos;
  size_t newline_pos = std::string::npos;

  do
    {
      begin_pos = newline_pos + 1;

      // Skip empty final lines.
      if (begin_pos == input_data.size())
	{ break; }

      newline_pos = input_data.find('\n',begin_pos);

      // Skip empty lines.
      if (newline_pos == begin_pos)
	{ continue; }

      std::string line = input_data.substr(begin_pos,
					   newline_pos - begin_pos);
      
      line_transformer.input_line(line);
      if (line_transformer.output_exists())
	{ 
	  std::string transformed_line = line_transformer.output_line();
	  transformed_input_data += transformed_line + "\n";	  
	}
    } 
  while (newline_pos != std::string::npos);
  
  set_transformed_stream();
}

bool StreamTransformer::LineTransformer::output_exists(void)
{ return not transformed_line.empty(); }

std::string StreamTransformer::LineTransformer::output_line(void)
{ return transformed_line; }

#ifdef HFST_TAGGER_TEST_StreamTransformer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.



  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_StreamTransformer
