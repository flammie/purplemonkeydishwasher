#include "NGramAbstracter.h"

NGramAbstracter::NGramAbstracter
(const EntryAbstracterVector &entry_abstracter_vector):
  entry_abstracter_vector(entry_abstracter_vector)
{}

NGramAbstracter::NGramAbstracter(const std::string &abstracter_string)
{
  if ((abstracter_string.size() % 2) != 0)
    { throw MalformedConfigurationString(); }
  
  for (size_t i = 0; i < abstracter_string.size(); ++i)
    {
      char c1 = abstracter_string[i];
      char c2 = abstracter_string[++i];

      if (c1 != '0' and c1 != '1')
	{ throw MalformedConfigurationString(); }
      
      if (c2 != '0' and c2 != '1')
	{ throw MalformedConfigurationString(); }

      bool concrete_wordform = (c1 == '1');
      bool concrete_tag = (c2 == '1');
      
      entry_abstracter_vector.push_back(EntryAbstracter(concrete_wordform,
							concrete_tag));
    }
}

std::string NGramAbstracter::transform(const std::string &symbol) const
{
  std::string result = "";
  
  size_t old_tab_pos = std::string::npos;
  size_t new_tab_pos = old_tab_pos;

  std::string separator = "";

  for (EntryAbstracterVector::const_iterator it = 
	 entry_abstracter_vector.begin();
       it != entry_abstracter_vector.end();
       ++it)
    {
      if ((new_tab_pos = symbol.find('\t',old_tab_pos+1)) 
	  == 
	  std::string::npos) 
	{ throw IncorrectFieldCount(); }


      if (it->first)
	{ 
	  std::string field = symbol.substr(old_tab_pos + 1,
					    new_tab_pos -(old_tab_pos + 1));
	  result += separator + field;
	}
      else
	{ result += separator + DEFAULT_SYMBOL; }

      separator = "\t";

      old_tab_pos = new_tab_pos;

      if ((new_tab_pos = symbol.find('\t',old_tab_pos+1)) 
	  == 
	  std::string::npos) 
	{ 
	  if (it + 1 != entry_abstracter_vector.end())
	    { throw IncorrectFieldCount(); }
	}

      if (it->second)
	{ 
	  std::string field = symbol.substr(old_tab_pos + 1,
					    new_tab_pos -(old_tab_pos + 1));
	  result += separator + field;
	}
      else
	{ result += separator + DEFAULT_SYMBOL; }
      
      old_tab_pos = new_tab_pos;
    }
  return result;
}

#ifdef HFST_TAGGER_TEST_NGramAbstracter
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  EntryAbstracter abstracter1(false,false);
  EntryAbstracter abstracter2(false,true);
  EntryAbstracter abstracter3(false,true);

  EntryAbstracterVector entry_abstracter_vector;
  entry_abstracter_vector.push_back(abstracter1);
  entry_abstracter_vector.push_back(abstracter2);
  entry_abstracter_vector.push_back(abstracter3);

  NGramAbstracter n_gram_abstracter1(entry_abstracter_vector);

  std::string result = n_gram_abstracter1.transform
    ("the\tDT\tcat\tNN\tsat\tVB");
  
  assert(result == 
	 (std::string() + 
	  DEFAULT_SYMBOL + "\t" + DEFAULT_SYMBOL + "\t" +
	  DEFAULT_SYMBOL + "\t" + "NN" + "\t" +
	  DEFAULT_SYMBOL + "\t" + "VB"));

  try
    {
      (void)n_gram_abstracter1.transform("the\tDT\tcat\tNN\tsat");
      assert(false);
    }
  catch (const NGramAbstracter::IncorrectFieldCount &)
    {}

  NGramAbstracter n_gram_abstracter2("000101");

  result = n_gram_abstracter1.transform
    ("the\tDT\tcat\tNN\tsat\tVB");
  
  assert(result == 
	 (std::string() + 
	  DEFAULT_SYMBOL + "\t" + DEFAULT_SYMBOL + "\t" +
	  DEFAULT_SYMBOL + "\t" + "NN" + "\t" +
	  DEFAULT_SYMBOL + "\t" + "VB"));

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_NGramAbstracter
