#include "WordformRemover.h"

std::string WordformRemover::transform(const std::string &symbol) const
{
  StringVector tokenized_symbol = split_at_tabs(symbol);
  
  if (tokenized_symbol.size() % 2 != 0)
    { throw IncorrectFieldCount(); }

  for (StringVector::iterator it = tokenized_symbol.begin();
       it != tokenized_symbol.end();
       ++it)
    {
      *it = DEFAULT_SYMBOL;
      ++it;
    }

  return join(tokenized_symbol);
}

WordformRemover::StringVector WordformRemover::split_at_tabs 
(const std::string &symbol) const
{
  StringVector result;

  size_t beg_pos = 0;
  size_t end_pos = std::string::npos;

  do
    {
      beg_pos = end_pos + 1;
      end_pos = symbol.find('\t',beg_pos);
      std::string token = symbol.substr(beg_pos,end_pos - beg_pos);
      result.push_back(token);
    } 
  while (end_pos != std::string::npos);
  
  return result;
}

std::string WordformRemover::join(const StringVector &string_vector) const
{
  std::string result;

  for (StringVector::const_iterator it = string_vector.begin();
       it != string_vector.end();
       ++it)
    { 
      result += *it; 
      if (it + 1 != string_vector.end())
	{ result += "\t"; }
    }
  
  return result;
}

#ifdef HFST_TAGGER_TEST_WordformRemover
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  std::string entry = 
    "the	DT	cat	NN	sat	VBD";

  WordformRemover wordform_remover;

  assert(wordform_remover.transform(entry) ==
	 DEFAULT_SYMBOL "	DT	" DEFAULT_SYMBOL "	NN	"
	 DEFAULT_SYMBOL "	VBD");
	 
  try
    {
      (void)wordform_remover.transform
	("the	DT	cat	NN	sat");
      assert(0);
    }
  catch (const WordformRemover::IncorrectFieldCount & e)
    {};

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_WordformRemover
