#include "LexicalModel.h"

#include <iostream>
#include <algorithm>
#include <cmath>

#include "LexiconBuilder.h"
#include "GuesserBuilder.h"
#include "WordformProbabilityListBuilder.h"
#include "StreamFieldInverter.h"
#include "StreamTokenizer.h"
#include "LexicalStreamTransformer.h"

using hfst::HFST_OLW_TYPE;
using hfst::TROPICAL_OPENFST_TYPE;

LexicalModel::LexicalModel(std::istream &in,
			   std::string name):
  LanguageModel(),
  model(TROPICAL_OPENFST_TYPE),
  corrupted(false)
{
  StreamReinitializer stream_reinitializer
    (LexicalStreamTransformer(in).get_stream());
  LexiconBuilder lexicon_builder
    (stream_reinitializer.get_stream());
  GuesserBuilder guesser_builder
    (stream_reinitializer.reinitialize().get_stream());
  WordformProbabilityListBuilder wordform_probability_list_builder
    (stream_reinitializer.reinitialize().get_stream());

  HfstTransducer lexicon = lexicon_builder.get_model();
  HfstTransducer guesser = guesser_builder.get_model();
  HfstTransducer wordform_probability_list = 
    wordform_probability_list_builder.get_model();

  model = 
    lexicon.
    disjunct(guesser).
    disjunct(wordform_probability_list).
    minimize();

  model.convert(HFST_OLW_TYPE);

  name = (name == "" ? "<unnamed>" : name);
  model.set_name(name);

  initialize_tag_probabilities();
}

LexicalModel::LexicalModel(const std::string filename,
			   bool init_tag_probabilities):
  LanguageModel(),
  model(read_fst(filename)),
  corrupted(false)
{ 
  // This can't be done before the library is fixed.
  // strip_prefix(); 

  if (init_tag_probabilities)
    { initialize_tag_probabilities(); }
}

float LexicalModel::convert_tropical_weight_to_probability(float w)
{ return exp(-1.0 * w); }

void LexicalModel::strip_prefix(void)
{
  std::string name = model.get_name();

  if (name.find(LEXICAL_MODEL_NAME_PREFIX) != 0)
    { 
      corrupted = true; 
      return;
    }

  size_t prefix_length = std::string(LEXICAL_MODEL_NAME_PREFIX).size();
  name = name.substr(prefix_length);

  model.set_name(name);
}

void LexicalModel::store(const std::string &filename)
{ 
  std::string original_name = model.get_name();

  std::string name = 
    std::string("") + 
    LEXICAL_MODEL_NAME_PREFIX + 
    original_name;

  model.set_name(name);

  write_fst(model,filename);

  model.set_name(original_name);
}

LexicalModel::LexicalModel(HfstInputStream &in):
  model(in)
{ strip_prefix(); }

LexicalModel::WeightStringVector LexicalModel::operator[](std::string wordform)
{
  if (corrupted)
    { throw NotALexicalModel(); }

  WeightStringVector results;

  std::string inverted_wordform = invert(wordform);

  HfstOneLevelPaths * lexicon_result = model.lookup(inverted_wordform);
  
  if (lexicon_result->size() == 0)
    { guess(inverted_wordform,results); }
  else
    { extract_tags_and_weights(lexicon_result,results,false); }

  delete lexicon_result;

  return results;
}

std::string LexicalModel::invert(const std::string &wordform)
{
  StringVector tokenized_wordform = tokenizer.tokenize_one_level(wordform);
  std::string inverted_wordform;
  for (StringVector::const_reverse_iterator it = tokenized_wordform.rbegin();
       it != tokenized_wordform.rend();
       ++it)
    { inverted_wordform += *it; }
  return inverted_wordform;
}

void LexicalModel::extract_tags_and_weights(HfstOneLevelPaths * paths,
					    WeightStringVector &res,
					    bool convert_to_tropical_weight)
{
  for (HfstOneLevelPaths::const_iterator it = paths->begin();
       it != paths->end();
       ++it)
    {
      
      float weight = 
	(convert_to_tropical_weight ? 
	 convert_tropical_weight_to_probability(it->first) :
	 it->first);

      std::string tag = it->second.back();
      res.push_back(WeightString(weight,tag));
    }
}

void LexicalModel::guess(std::string inverted_wordform,
			 LexicalModel::WeightStringVector &results)
{
  assert(not inverted_wordform.empty());

  StringVector tokenized_inverted_wordform = 
    tokenizer.tokenize_one_level(inverted_wordform);

  std::string previous_wordform_suffix;
  std::string wordform_suffix;

  WeightStringVectorVector suffix_results;

  for (StringVector::const_iterator it = tokenized_inverted_wordform.begin();
       it != tokenized_inverted_wordform.end();
       ++it)
    {
      HfstOneLevelPaths * suffix_result_paths =
	model.lookup(wordform_suffix + GUESS_TAG);

      WeightStringVector suffix_result; 

      if (not suffix_result_paths->empty())
	{ extract_tags_and_weights(suffix_result_paths,suffix_result,true); }

      delete suffix_result_paths;

      if (suffix_result.empty())
	{ break; }
	  
      suffix_results.push_back(suffix_result);

      previous_wordform_suffix = wordform_suffix;
      wordform_suffix += *it;
    }

  smoothe_tag_probabilities(suffix_results,results);

  // FIXME: need to tokenize when dealing with multibyte characters. FIXED
  std::string last_found_suffix = 
    previous_wordform_suffix.substr(0,previous_wordform_suffix.size());

  bayesian_invert(last_found_suffix,results);
  
  convert_probabilities_to_tropical_weights(results);

  std::sort(results.begin(),results.end());
}

void LexicalModel::bayesian_invert(const std::string &suffix,
				   WeightStringVector &results)
{
  HfstOneLevelPaths * suffix_result = model.lookup(suffix + WF_TAG);

  if (suffix_result->size() != 1)
    {
      std::cerr << "\""<< suffix << "\"" << suffix_result->size() 
		<< std::endl; 
    }
  assert(suffix_result->size() == 1);

  float suffix_probability = 
    convert_tropical_weight_to_probability(suffix_result->begin()->first);

  delete suffix_result;

  for (WeightStringVector::iterator it = results.begin();
       it != results.end();
       ++it)
    {  
      float tag_probability = get_tag_probability(it->second);

      if (tag_probability == 0)
	{
	  it->first = 1.0/1000000.0; 
	}
      else
	{
	  it->first = it->first * suffix_probability / tag_probability;
	}
    }
  
}

void LexicalModel::convert_probabilities_to_tropical_weights
(WeightStringVector &results)
{
    for (WeightStringVector::iterator it = results.begin();
       it != results.end();
       ++it)
      { it->first = -1.0 * log(it->first); }
}

float LexicalModel::get_tag_probability(const std::string &symbol)
{ return tag_probabilities[symbol]; }

void LexicalModel::initialize_tag_probabilities(void)
{
  HfstOneLevelPaths * tag_probability_paths = model.lookup(GUESS_TAG);
  WeightStringVector tag_probability_vector;
  extract_tags_and_weights(tag_probability_paths,tag_probability_vector,true);
  delete tag_probability_paths;

  for (WeightStringVector::const_iterator it = tag_probability_vector.begin();
       it != tag_probability_vector.end();
       ++it)
    { 
      tag_probabilities[it->second] = it->first; 
    }
}

HfstTransducer LexicalModel::get_model(void)
{ return model; }

#ifdef HFST_TAGGER_TEST_LexicalModel
#include <cassert>
#include <iostream>

#include <cmath>

using hfst::TROPICAL_OPENFST_TYPE; 

#include <map>

class SummingGuesserLexicalModel : public LexicalModel
{
public:
  typedef std::map<float,std::string> WeightStringMap;
  typedef std::map<std::string,float> StringWeightMap;

  SummingGuesserLexicalModel(std::istream &in,std::string name):
    LexicalModel(in,name) {}
protected:
  void smoothe_tag_probabilities
  (const WeightStringVectorVector &prefix_tag_probabilities,
   WeightStringVector &tag_probabilities)
  {
    StringWeightMap m;
    for (WeightStringVectorVector::const_iterator it = 
	   prefix_tag_probabilities.begin();
	 it != prefix_tag_probabilities.end();
	 ++it)
      {
	for (WeightStringVector::const_iterator jt = it->begin();
	     jt != it->end();
	     ++jt)
	  { m[jt->second] += jt->first; }
      }
    
    WeightStringMap mm;
    for (StringWeightMap::const_iterator it = m.begin();
	 it != m.end();
	 ++it)
      { mm[it->second] = it->first; }

    for (WeightStringMap::const_iterator it = mm.begin();
	 it != mm.end();
	 ++it)
      { tag_probabilities.push_back(WeightString(it->first,it->second)); }
  }
};

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_data =
    "man\tNN\n"
    "man\tVB\n"
    "can\tVB\n";

  std::istringstream in(input_data);

  SummingGuesserLexicalModel lexical_model_constructor(in,"");

  HfstTransducer lexical_model = lexical_model_constructor.get_model();
  lexical_model.convert(TROPICAL_OPENFST_TYPE);

  HfstTokenizer tokenizer;
  tokenizer.add_multichar_symbol("NN");
  tokenizer.add_multichar_symbol("VB");
  tokenizer.add_multichar_symbol("<guess>");
  tokenizer.add_multichar_symbol("<wf>");
  tokenizer.add_multichar_symbol("<tag>");

  HfstTransducer man_NN("nam","namNN",tokenizer,TROPICAL_OPENFST_TYPE);
  man_NN.set_final_weights(-1.0 * log(1.0));

  HfstTransducer man_VB("nam","namVB",tokenizer,TROPICAL_OPENFST_TYPE);
  man_VB.set_final_weights(-1.0 * log(1.0/2.0));

  HfstTransducer can_VB("nac","nacVB",tokenizer,TROPICAL_OPENFST_TYPE);
  can_VB.set_final_weights(-1.0 * log(1.0/2.0));

  HfstTransducer NN("<guess>","<guess>NN",tokenizer,TROPICAL_OPENFST_TYPE);
  NN.set_final_weights(-1 * log(1.0/3.0));

  HfstTransducer VB("<guess>","<guess>VB",tokenizer,TROPICAL_OPENFST_TYPE);
  VB.set_final_weights(-1 * log(2.0/3.0));

  HfstTransducer n_NN("n<guess>","n<guess>NN",tokenizer,TROPICAL_OPENFST_TYPE);
  n_NN.set_final_weights(-1 * log(1.0/3.0));

  HfstTransducer n_VB("n<guess>","n<guess>VB",tokenizer,TROPICAL_OPENFST_TYPE);
  n_VB.set_final_weights(-1 * log(2.0/3.0));

  HfstTransducer an_NN("na<guess>","na<guess>NN",tokenizer,
		       TROPICAL_OPENFST_TYPE);
  an_NN.set_final_weights(-1*log(1.0/3.0));

  HfstTransducer an_VB("na<guess>","na<guess>VB",tokenizer,
		       TROPICAL_OPENFST_TYPE);
  an_VB.set_final_weights(-1*log(2.0/3.0));

  HfstTransducer can_VB_guess("nac<guess>","nac<guess>VB",tokenizer,
			      TROPICAL_OPENFST_TYPE);
  can_VB_guess.set_final_weights(-1*log(1.0));

  HfstTransducer man_NN_guess("nam<guess>","nam<guess>NN",tokenizer,
			      TROPICAL_OPENFST_TYPE);
  man_NN_guess.set_final_weights(-1*log(1.0/2.0));

  HfstTransducer man_VB_guess("nam<guess>","nam<guess>VB",tokenizer,
			      TROPICAL_OPENFST_TYPE);
  man_VB_guess.set_final_weights(-1*log(1.0/2.0));

  HfstTransducer empty_wf("<wf>","<wf><tag>",
			tokenizer,TROPICAL_OPENFST_TYPE);
  empty_wf.set_final_weights(-1*log(3.0/12.0));

  HfstTransducer n_wf("n<wf>","n<wf><tag>",
			tokenizer,TROPICAL_OPENFST_TYPE);
  n_wf.set_final_weights(-1*log(3.0/12.0));

  HfstTransducer an_wf("na<wf>","na<wf><tag>",
			tokenizer,TROPICAL_OPENFST_TYPE);
  an_wf.set_final_weights(-1*log(3.0/12.0));

  HfstTransducer man_wf("nam<wf>","nam<wf><tag>",
			tokenizer,TROPICAL_OPENFST_TYPE);
  man_wf.set_final_weights(-1*log(2.0/12.0));

  HfstTransducer can_wf("nac<wf>","nac<wf><tag>",
			tokenizer,TROPICAL_OPENFST_TYPE);
  can_wf.set_final_weights(-1*log(1.0/12.0));

  HfstTransducer comparison_model(man_NN);
  comparison_model.
    disjunct(man_NN).
    disjunct(man_VB).
    disjunct(can_VB).
    disjunct(NN).
    disjunct(VB).
    disjunct(n_NN).
    disjunct(n_VB).
    disjunct(an_NN).
    disjunct(an_VB).
    disjunct(man_NN_guess).
    disjunct(man_VB_guess).
    disjunct(can_VB_guess).
    disjunct(empty_wf).
    disjunct(n_wf).
    disjunct(an_wf).
    disjunct(man_wf).
    disjunct(can_wf).
    minimize();

  assert(lexical_model.compare(comparison_model));

  SummingGuesserLexicalModel::WeightStringVector man_lookup_result = 
    lexical_model_constructor["man"];
  assert(man_lookup_result.size() == 2);

  assert(man_lookup_result[0].first == (-1.0 * log(1.0)));
  assert(man_lookup_result[0].second == "NN");

  assert(abs((man_lookup_result[1].first - (-1.0 * log(1.0/2.0)))) < 0.01);
  assert(man_lookup_result[1].second == "VB");

  SummingGuesserLexicalModel::WeightStringVector woman_lookup_result = 
    lexical_model_constructor["woman"];

  assert(woman_lookup_result.size() == 2);

  float woman_NN_tropical_weight = 
    (1.0/3.0 + 1.0/3.0 + 1.0/3.0 + 1.0/2.0) * (2.0 / 12.0) / (1.0/3.0);

  float woman_VB_tropical_weight = 
    (2.0/3.0 + 2.0/3.0 + 2.0/3.0 + 1.0/2.0) * (2.0 / 12.0) / (2.0/3.0);

  assert
    (abs(woman_lookup_result[0].first - woman_NN_tropical_weight) < 0.0005);
  assert(woman_lookup_result[0].second == "NN");

  assert
    (abs(woman_lookup_result[1].first - woman_VB_tropical_weight) < 0.0005);
  assert(woman_lookup_result[1].second == "VB");
  
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_LexicalModel
