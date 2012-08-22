#include "HMMTagger.h"

using hfst::TROPICAL_OPENFST_TYPE;
using hfst::HfstTwoLevelPaths;
using hfst::HfstTwoLevelPath;

ConfigStringPair hmm_config_string_pair0("01010101","01010100");
ConfigStringPair hmm_config_string_pair1("010101","010100");
ConfigStringPair hmm_config_string_pair2("0101","0100");
ConfigStringPair hmm_config_string_pair3("01","00");

ConfigStringPair config_string_pairs[3] =
  {hmm_config_string_pair1, hmm_config_string_pair2, hmm_config_string_pair3};

ConfigStringPairVector hmm_config_string_pair_vector(config_string_pairs,
						     config_string_pairs + 3);

float k = 1.4;
//float coeffs[3] = {k*0.28,k*0.34,k*0.38};
float coeffs[3] = {k*0.48,k*0.24,k*0.28};

FloatVector coefficients(coeffs,coeffs+3);

HMMTagger::HMMTagger(std::istream &in,const std::string &name):
  Tagger(in,name,hmm_config_string_pair_vector,coefficients)
{}

HMMTagger::HMMTagger(const std::string &lexical_model_file_name,
		     const std::string &sequence_model_file_name):
  Tagger(lexical_model_file_name,sequence_model_file_name)
{}

#ifdef HFST_TAGGER_TEST_HMMTagger
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_file =
    "W	Y\n"
    "W	X\n"
    "W	X\n"
    "V	X\n"
    "V	Y"
    ;

  std::istringstream input_stream(input_file);
  
  HMMTagger hmm_tagger(input_stream,"HMM");

  StringVector input;
  input.push_back("W");
  input.push_back("W");
  input.push_back("W");

  StringPairVector result = hmm_tagger[input];
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_HMMTagger
