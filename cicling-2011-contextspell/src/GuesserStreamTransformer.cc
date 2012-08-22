#include "GuesserStreamTransformer.h"

#include <iostream>

GuesserStreamTransformer::GuesserStreamTransformer(std::istream &in):
  StreamTransformer(in)
{
  GuessTagger guess_tagger;
  transform_input_data(guess_tagger);
}

void GuesserStreamTransformer::GuessTagger::input_line(const std::string &line)
{
  transformed_line = "";

  size_t last_tab_pos = line.find_last_of('\t');
  
  size_t begin_pos = std::string::npos;
  size_t tab_pos   = std::string::npos;


  do 
    {
      begin_pos = tab_pos + 1;
      tab_pos   = line.find('\t',begin_pos);

      transformed_line += 
	line.substr(0,tab_pos) + 
	"\t" + 
	GUESS_TAG +
	line.substr(last_tab_pos);

      transformed_line += "\n"; 

    } while (tab_pos < last_tab_pos);

  transformed_line += 
    GUESS_TAG +
    line.substr(last_tab_pos);  
}

#ifdef HFST_TAGGER_TEST_GuesserStreamTransformer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_data = "a\tb\tc\tNN";

  std::istringstream input_stream(input_data);

  GuesserStreamTransformer guesser_stream_transformer(input_stream);

  std::istream &in = guesser_stream_transformer.get_stream();

  char line[1000];
  in.getline(line,1000);
  assert(std::string(line) == "a\t<guess>\tNN");
  
  in.getline(line,1000);
  assert(std::string(line) == "a\tb\t<guess>\tNN");

  in.getline(line,1000);
  assert(std::string(line) == "a\tb\tc\t<guess>\tNN");

  in.getline(line,1000);
  assert(std::string(line) == "<guess>\tNN");

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_GuesserStreamTransformer
