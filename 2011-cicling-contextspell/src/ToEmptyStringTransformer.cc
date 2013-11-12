#include "ToEmptyStringTransformer.h"

std::string ToEmptyStringTransformer::transform
(const std::string &symbol) const
{ 
  (void)symbol;
  return ""; 
}

#ifdef HFST_TAGGER_TEST_ToEmptyStringTransformer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.



  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_ToEmptyStringTransformer
