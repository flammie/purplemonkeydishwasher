#include "LexiconDivisorTransformer.h"

#include <iostream>

std::string LexiconDivisorTransformer::transform(const std::string &symbol) 
const
{
  size_t tab_pos;
  if ((tab_pos = symbol.find_last_of('\t')) == std::string::npos)
    { throw MalformedInputData(); }

  return symbol.substr(tab_pos+1);
}

#ifdef HFST_TAGGER_TEST_LexiconDivisorTransformer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  LexiconDivisorTransformer lexicon_divisor_transformer;

  assert(lexicon_divisor_transformer.transform("a\tDT") == "DT");
  assert(lexicon_divisor_transformer.transform("t\th\e\tDT") == "DT");
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_LexiconDivisorTransformer
