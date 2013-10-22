#include "GuesserBuilder.h"

#include "IdentityTransformer.h"
#include "GuesserDivisorTransformer.h"
#include "LogSequenceWeightTable.h"
#include "GuesserStreamTransformer.h"

GuesserBuilder::GuesserBuilder(std::istream &in):
  TrieBuilder(LogSequenceWeightTable
	      (IdentityTransformer(),
	       GuesserDivisorTransformer(),
	       GuesserStreamTransformer(in).get_stream()))
{}

#ifdef HFST_TAGGER_TEST_GuesserBuilder
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.



  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_GuesserBuilder
