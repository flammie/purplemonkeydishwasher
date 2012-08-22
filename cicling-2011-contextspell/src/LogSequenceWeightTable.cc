#include <cmath>

#include "LogSequenceWeightTable.h"

LogSequenceWeightTable::LogSequenceWeightTable
(const StringTransformer &dividend_abstractor,
 const StringTransformer &divisor_abstractor,
 std::istream &input_file):
  SequenceWeightTable(dividend_abstractor,divisor_abstractor,input_file)
{ transform_weights(LogWeightTransformer()); }

float LogSequenceWeightTable::LogWeightTransformer::operator() (float f) const
{ return -1.0 * log(f); }

#ifdef HFST_TAGGER_TEST_LogSequenceWeightTable
#include <cassert>
#include <iostream>
#include <sstream>

#include "WordformRemover.h"
#include "LastEntryRemover.h"

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_file =
    "the	DT	cat	NN\n"
    "the	DT	big	JJ\n"
    "this	DT	guy	NN\n"
    "this	DT	guy	NN"
    ;

  std::istringstream input_stream(input_file);

  WordformRemover wordform_remover;
  LastEntryRemover last_entry_remover;

  SequenceWeightTable sequence_weight_table(wordform_remover,
					    last_entry_remover,
					    input_stream);


  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_LogSequenceWeightTable
