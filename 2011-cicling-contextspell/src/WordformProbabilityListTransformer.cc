#include "WordformProbabilityListTransformer.h"

#include <iostream>

WordformProbabilityListTransformer::WordformProbabilityListTransformer
(std::istream &in):
  StreamTransformer(in)
{
  WfTagger wf_tagger;
  transform_input_data(wf_tagger);
}

void WordformProbabilityListTransformer::WfTagger::input_line
(const std::string &line)
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
	WF_TAG +
	"\t" +
	DUMMY_TAG;

      transformed_line += "\n"; 

    } while (tab_pos < last_tab_pos);

  transformed_line +=
    std::string(WF_TAG) +
    "\t" +
    DUMMY_TAG; 
  
}

#ifdef HFST_TAGGER_TEST_WordformProbabilityListTransformer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_data = "a\tb\tc\tNN";

  std::istringstream input_stream(input_data);

  WordformProbabilityListTransformer 
    wordform_probability_list_transformer(input_stream);

  std::istream &in = wordform_probability_list_transformer.get_stream();

  char line[1000];
  in.getline(line,1000);
  assert(std::string(line) == "a\t<wf>\t<tag>");
  
  in.getline(line,1000);
  assert(std::string(line) == "a\tb\t<wf>\t<tag>");

  in.getline(line,1000);
  assert(std::string(line) == "a\tb\tc\t<wf>\t<tag>");

  in.getline(line,1000);
  assert(std::string(line) == "<wf>\t<tag>");

  (void)in.peek();
  assert(in.eof());

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_WordformProbabilityListTransformer
