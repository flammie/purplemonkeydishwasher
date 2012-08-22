#include "GuesserDivisorTransformer.h"

std::string GuesserDivisorTransformer::transform(const std::string &symbol) 
const
{
  size_t final_tab_pos;
  if ((final_tab_pos = symbol.find_last_of('\t')) == std::string::npos)
    { throw MalformedInputData(); }

  return symbol.substr(0,final_tab_pos);
}

#ifdef HFST_TAGGER_TEST_GuesserDivisorTransformer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  GuesserDivisorTransformer guesser_divisor_transformer;
  
  assert(guesser_divisor_transformer.transform("c\ta\tn\tDT") == "c\ta\tn");
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_GuesserDivisorTransformer
