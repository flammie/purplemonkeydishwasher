#include "IdentityTransformer.h"

std::string IdentityTransformer::transform(const std::string &symbol) const
{ return symbol; }

#ifdef HFST_TAGGER_TEST_IdentityTransformer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.



  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_IdentityTransformer
