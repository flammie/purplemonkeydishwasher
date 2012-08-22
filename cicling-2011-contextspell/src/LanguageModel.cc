#include "LanguageModel.h"

using hfst::TROPICAL_OPENFST_TYPE;

HfstTransducer LanguageModel::read_fst(const std::string &filename)
{
  try
    {
      HfstInputStream in(filename);
      HfstTransducer result(in);
  
      in.close();
      
      std::string name = result.get_name();
      if (name.find(TAGGER_NAME_PREFIX) != 0)
	{ throw NotTaggerStream(); }
      size_t name_rest_pos = std::string(TAGGER_NAME_PREFIX).size();
      result.set_name(name.substr(name_rest_pos));
      return result;
    }
  catch (const TransducerHasWrongTypeException &)
    { 
      std::cerr << "Too old hfst version!" << std::endl; 
      exit(1);
    }
  return HfstTransducer(TROPICAL_OPENFST_TYPE);
}

void LanguageModel::write_fst(HfstTransducer &fst,const std::string &filename)
{
  fst.set_name(std::string(TAGGER_NAME_PREFIX) + fst.get_name());

  HfstOutputStream out(filename,fst.get_type());

  std::cerr << "Writing: " << fst.get_name() << " in " << filename 
	    << std::endl;

  out << fst;

  out.close();
}

#ifdef HFST_TAGGER_TEST_LanguageModel
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.



  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_LanguageModel
