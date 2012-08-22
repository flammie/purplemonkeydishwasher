#include "LexiconBuilder.h"

#include "IdentityTransformer.h"
#include "LexiconDivisorTransformer.h"
#include "LogSequenceWeightTable.h"

LexiconBuilder::LexiconBuilder(std::istream &in):
  TrieBuilder(LogSequenceWeightTable(IdentityTransformer(),
				     LexiconDivisorTransformer(),
				     in))
{}

#ifdef HFST_TAGGER_TEST_LexiconBuilder
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.



  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_LexiconBuilder
