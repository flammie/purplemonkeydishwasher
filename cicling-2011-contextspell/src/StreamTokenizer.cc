#include "StreamTokenizer.h"

StreamTokenizer::StreamTokenizer(std::istream &in):
  StreamTransformer(in)
{
  FirstFieldTokenizer first_field_tokenizer;
  transform_input_data(first_field_tokenizer);
}

using hfst::StringVector;

void StreamTokenizer::FirstFieldTokenizer::input_line(const std::string &line)
{
  size_t tab_pos = line.find('\t');
  
  if (tab_pos == std::string::npos)
    { throw MalformedInputData(); }

  std::string first_field = line.substr(0,tab_pos);
  std::string rest        = line.substr(tab_pos + 1,std::string::npos);

  StringVector tokenized_field = tokenizer.tokenize_one_level(first_field);

  std::string tokenized_field_string;
  for (StringVector::const_iterator it = tokenized_field.begin();
       it != tokenized_field.end();
       ++it)
    { tokenized_field_string += *it + "\t"; }
    
  transformed_line = tokenized_field_string + rest;
}

#ifdef HFST_TAGGER_TEST_StreamTokenizer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_data =
    "the	DT\n"
    "cat	NN\n"
    ;

  std::istringstream in(input_data);

  StreamTokenizer stream_tokenizer(in);

  std::istream &tokenized_in = stream_tokenizer.get_stream();

  char line[1000];

  tokenized_in.getline(line,1000);
  assert(std::string(line) == "t\th\te\tDT");

  tokenized_in.getline(line,1000);
  assert(std::string(line) == "c\ta\tt\tNN");
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_StreamTokenizer
