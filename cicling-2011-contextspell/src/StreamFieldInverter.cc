#include "StreamFieldInverter.h"

StreamFieldInverter::StreamFieldInverter(std::istream &in):
  StreamTransformer(in)
{
  LineInverter line_inverter;
  transform_input_data(line_inverter);
}

using hfst::StringVector;

void StreamFieldInverter::LineInverter::input_line(const std::string &line)
{
  transformed_line = "";
  
  if (line.find('\t') == std::string::npos)
    { throw MalformedInputData(); }

  size_t begin_pos = std::string::npos;
  size_t tab_pos = std::string::npos;

  do
    {
      begin_pos = tab_pos + 1;
      tab_pos = line.find('\t',begin_pos);

      if (tab_pos == begin_pos)
	{ 
	  std::cerr << "\"" << line << "\"" << std::endl;
	  throw MalformedInputData(); 
	}

      std::string field = line.substr(begin_pos,
				      tab_pos - begin_pos);

      std::string transformed_field;

      if (tab_pos == std::string::npos)
	{ transformed_field = field; } 
      else
	{ transformed_field = invert_string(field) + "\t"; }

      transformed_line += transformed_field;
    } 
  while (tab_pos != std::string::npos);

}

std::string StreamFieldInverter::LineInverter::invert_string
(const std::string &str)
{
  StringVector utf_8_tokens = tokenizer.tokenize_one_level(str);
  
  std::string result;
  
  for (StringVector::const_reverse_iterator it = utf_8_tokens.rbegin();
       it != utf_8_tokens.rend();
       ++it)
    { result += *it; }
 
  return result;  
}

#ifdef HFST_TAGGER_TEST_StreamFieldInverter
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.
  
  const char * input_data =
    "the	DT\n"
    "Böll	NNP\n"      
    "wordform	lemma	tag"
    ;
  
  std::istringstream in(input_data);
  
  StreamFieldInverter stream_field_inverter(in);

  std::istream &inverted_in = stream_field_inverter.get_stream();

  char line[1000];
  inverted_in.getline(line,1000);
  assert(std::string(line) == "eht\tDT");

  inverted_in.getline(line,1000);
  assert(std::string(line) == "llöB\tNNP");

  inverted_in.getline(line,1000);
  assert(std::string(line) == "mrofdrow\tammel\ttag");

  (void)inverted_in.peek();
  assert(inverted_in.eof());

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_StreamFieldInverter
