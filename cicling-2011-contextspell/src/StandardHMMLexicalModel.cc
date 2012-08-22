#include <cmath>

#include "StandardHMMLexicalModel.h"
#include "GuesserBuilder.h"

#define GUESSER_COEFFICIENT 0.02

bool gt(const StandardHMMLexicalModel::WeightString &w1,
	const StandardHMMLexicalModel::WeightString &w2)
{
  return 
    (w1.first > w2.first) or 
    ((w1.first == w2.first) and (w1.second > w2.second));
}

StandardHMMLexicalModel::StandardHMMLexicalModel
(std::istream &in,std::string name):
  LexicalModel(in,name)
{ init_coefficient(); }

StandardHMMLexicalModel::StandardHMMLexicalModel(const std::string filename):
  LexicalModel(filename)
{ init_coefficient(); }

void StandardHMMLexicalModel::init_coefficient(void)
{
  FloatVector tag_probabilities = get_tag_probabilities();
  standard_deviation = get_std_dev(tag_probabilities);
}

StandardHMMLexicalModel::FloatVector 
StandardHMMLexicalModel::get_tag_probabilities(void)
{
  HfstOneLevelPaths * tag_paths =
    model.lookup(GUESS_TAG);

  WeightStringVector tag_result;
  extract_tags_and_weights(tag_paths,tag_result,true);
  
  FloatVector result;

  for (WeightStringVector::const_iterator it = tag_result.begin();
       it != tag_result.end();
       ++it)
    { result.push_back(it->first); }
  
  return result;
}

float StandardHMMLexicalModel::get_std_dev
(const FloatVector &probabilities)
{
  assert(probabilities.size() > 1);

  double average_probability = 1.0 / probabilities.size();

  double square_difference_sum = 0;

  for (FloatVector::const_iterator it = probabilities.begin();
       it != probabilities.end();
       ++it)
    { 
      square_difference_sum += 
	(*it - average_probability)*(*it - average_probability);
    }
  
  double std_dev = square_difference_sum / (probabilities.size() - 1);
  
  return std_dev;
}

void StandardHMMLexicalModel::smoothe_tag_probabilities
(const WeightStringVectorVector &prefix_tag_probabilities,
 WeightStringVector &tag_probabilities)
{
  WeightStringVectorVector::const_iterator it = 
    prefix_tag_probabilities.begin();
  while (prefix_tag_probabilities.end() - it > 10)
    { ++it; }
  
  StringWeightMap m;

  for( ; it != prefix_tag_probabilities.end(); ++it)
    {
      StringWeightMap symbols_found;
      for (WeightStringVector::const_iterator jt = it->begin();
	   jt != it->end();
	   ++jt)
	{ 

	  symbols_found[jt->second] = 1;

	  if (jt == it->begin())
	    { m[jt->second] = jt->first; }
	  else
	    {
	      m[jt->second] = 
		((standard_deviation * m[jt->second]) + jt->first)
		/ (standard_deviation + 1); 
	    }
	}

      for (StringWeightMap::iterator jt = m.begin();
	   jt != m.end();
	   ++jt)
	{ 
	  if (symbols_found[jt->first] == 0)
	    { jt->second = 
		standard_deviation*jt->second / (standard_deviation + 1); }
	}
    }

  for (StringWeightMap::const_iterator it = m.begin();
	 it != m.end();
	 ++it)
      { 
	tag_probabilities.push_back
	  (WeightString
	   (it->second*GUESSER_COEFFICIENT,it->first)); 
      }

  std::sort(tag_probabilities.begin(),tag_probabilities.end(),gt);

  if (tag_probabilities.size() > 5)
    {
      tag_probabilities.erase(tag_probabilities.begin() + 5,
			      tag_probabilities.end());
    }
}

#ifdef HFST_TAGGER_TEST_StandardHMMLexicalModel  
HfstTransducer StandardHMMLexicalModel::get_model(void)
{ return model; }
#endif // HFST_TAGGER_TEST_StandardHMMLexicalModel  

using hfst::TROPICAL_OPENFST_TYPE;

#ifdef HFST_TAGGER_TEST_StandardHMMLexicalModel
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_data =
    "man\tNN\n"
    "man\tVB\n"
    "can\tVB\n";

  std::istringstream in(input_data);

  StandardHMMLexicalModel lexical_model_constructor(in,"");

  LexicalModel::WeightStringVector v = lexical_model_constructor["acan"];

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_StandardHMMLexicalModel
