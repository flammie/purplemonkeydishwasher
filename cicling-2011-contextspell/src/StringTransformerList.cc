#include <cassert>

#include "StringTransformerList.h"

StringTransformerList::StringTransformerList(void):
  headp(0), tailp(0)
{}

StringTransformerList::StringTransformerList
(const StringTransformer &head,
 const StringTransformerList &tail):
  headp(&head), tailp(&tail)
{}

std::string StringTransformerList::transform(const std::string &symbol) const
{
  if (headp == 0)
    { return symbol; }

  assert(tailp != 0);

  return tailp->transform(headp->transform(symbol));
}

#ifdef HFST_TAGGER_TEST_StringTransformerList
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_StringTransformerList
