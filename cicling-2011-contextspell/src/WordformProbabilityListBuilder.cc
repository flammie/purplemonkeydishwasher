#include "WordformProbabilityListBuilder.h"

#include "IdentityTransformer.h"
#include "ToEmptyStringTransformer.h"
#include "LogSequenceWeightTable.h"

WordformProbabilityListBuilder::WordformProbabilityListBuilder
(std::istream &in):
  TrieBuilder
  (LogSequenceWeightTable
   (IdentityTransformer(),
    ToEmptyStringTransformer(),
    WordformProbabilityListTransformer(in).get_stream()))
{}

#ifdef HFST_TAGGER_TEST_WordformProbabilityListBuilder
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.



  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_WordformProbabilityListBuilder
