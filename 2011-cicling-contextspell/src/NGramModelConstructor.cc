#include "NGramModelConstructor.h"
#include "NGramAbstracter.h"
#include "LogSequenceWeightTable.h"
#include "StreamMarkovizer.h"

using hfst::TROPICAL_OPENFST_TYPE;

float * NGramModelConstructor::c = 0;

float multiply(float w)
{ return w * (*NGramModelConstructor::c); }

NGramModelConstructor::NGramModelConstructor
(const std::string &dividend_abstracter_config_string,
 const std::string &divisor_abstracter_config_string,
 std::istream &in,
 float coefficient):
  model(TROPICAL_OPENFST_TYPE)
{
  c = &coefficient;

  if (dividend_abstracter_config_string.size() !=
      divisor_abstracter_config_string.size())
    { throw UnEqualConfigStringSizes(); }

  size_t n = dividend_abstracter_config_string.size() / 2;
  
  model =
    CompletedCycleBuilder
    (LogSequenceWeightTable
     (NGramAbstracter(dividend_abstracter_config_string),
      NGramAbstracter(divisor_abstracter_config_string),
      StreamMarkovizer(n,in).get_stream())).get_model();

  model.transform_weights(multiply);
}

HfstTransducer NGramModelConstructor::get_model(void)
{ return model; }

#ifdef HFST_TAGGER_TEST_NGramModelConstructor
#include <cassert>
#include <iostream>
using hfst::HfstOutputStream;
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_file =
    "W	Y\n"
    "W	X\n"
    "W	X\n"
    "W	X\n"
    "W	X"
    ;

  std::istringstream input_stream(input_file);

  NGramModelConstructor n_gram_model_constructor("010101",
						 "000101",
						 input_stream);

  HfstTransducer n_gram_model = n_gram_model_constructor.get_model();

  HfstOutputStream out(TROPICAL_OPENFST_TYPE);
  //out << n_gram_model;

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_NGramModelConstructor
