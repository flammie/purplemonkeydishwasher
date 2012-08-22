#include "LastEntryRemover.h"

std::string LastEntryRemover::transform(const std::string &symbol) const
{
  size_t last_tab_pos = symbol.find_last_of('\t');
  size_t second_last_tab_pos = symbol.find_last_of('\t',last_tab_pos - 1);
  
  if (last_tab_pos == std::string::npos or
      second_last_tab_pos == std::string::npos)
    { throw IncorrectFieldCount(); }
  
  return symbol.substr(0,second_last_tab_pos) + 
    "\t" DEFAULT_SYMBOL "\t" DEFAULT_SYMBOL;
}

#ifdef HFST_TAGGER_TEST_LastEntryRemover
#include <cassert>
#include <iostream>

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ "\t";

  LastEntryRemover last_entry_remover;
  assert(last_entry_remover.transform("the	DT	cat	NN	sat")
	 == "the	DT	cat	" DEFAULT_SYMBOL "\t" DEFAULT_SYMBOL);
	 
  try
    {
      (void)last_entry_remover.transform("a	a");
      assert(0);
    }
  catch (const LastEntryRemover::IncorrectFieldCount &)
    {};

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_LastEntryRemover
