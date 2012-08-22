#include "LexicalStreamTransformer.h"

#include "StreamFieldInverter.h"

LexicalStreamTransformer::LexicalStreamTransformer(std::istream &in):
  StreamTokenizer(StreamFieldInverter(in).get_stream())
{}

#ifdef HFST_TAGGER_TEST_LexicalStreamTransformer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.



  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_LexicalStreamTransformer
