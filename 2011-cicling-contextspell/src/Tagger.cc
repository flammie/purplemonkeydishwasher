#include "Tagger.h"

using hfst::TROPICAL_OPENFST_TYPE;
using hfst::HfstTwoLevelPaths;
using hfst::HfstTwoLevelPath;

Tagger::Tagger(std::istream &in,
	       const std::string &name,
	       ConfigStringPairVector &config_vector,
	       FloatVector coefficients):
  stream_reinitializer(in),
  lexical_model(stream_reinitializer.get_stream(),name),
  sequence_model(config_vector,
		 stream_reinitializer.reinitialize().get_stream(),
		 coefficients)
{}

Tagger::Tagger(const std::string &lexical_model_file_name,
	       const std::string &sequence_model_file_name):
  lexical_model(lexical_model_file_name),
  sequence_model(sequence_model_file_name)
{}

StringPairVector Tagger::operator[]
(const StringVector &input_sentence)
{
  LexicalModel::WeightStringVectorVector results;
  for (StringVector::const_iterator it = input_sentence.begin();
       it != input_sentence.end();
       ++it)
    { results.push_back(lexical_model[*it]); }

  HfstBasicTransducer sentence_with_lexical_weights = 
    get_fst(input_sentence,results);
  
 
  HfstBasicTransducer sentence_with_weights = 
    sequence_model.tag_input(sentence_with_lexical_weights);

  StringPairVector result = get_vector(sentence_with_weights);

  return result;
}

HfstBasicTransducer 
Tagger::get_all_taggings(const StringVector &input_sentence)
{
  LexicalModel::WeightStringVectorVector results;
  for (StringVector::const_iterator it = input_sentence.begin();
       it != input_sentence.end();
       ++it)
    { results.push_back(lexical_model[*it]); }

  HfstBasicTransducer sentence_with_lexical_weights = 
    get_fst(input_sentence,results);
  
  HfstBasicTransducer sentence_with_weights = 
    sequence_model.tag_input(sentence_with_lexical_weights);

  return sentence_with_weights;
}

HfstBasicTransducer Tagger::get_fst
(const StringVector &s,const LexicalModel::WeightStringVectorVector &v)
{
  HfstBasicTransducer fst;
  HfstState initial_state = 0;
  HfstState target_state  = 0;

  for (size_t i = 0; i < v.size(); ++i)
    {
      initial_state = target_state;
      target_state = fst.add_state();
      
      fst.add_transition(initial_state,
			 HfstBasicTransition
			 (target_state,s[i],s[i],0.0));

      initial_state = target_state;
      target_state = fst.add_state();

      for (LexicalModel::WeightStringVector::const_iterator jt = v[i].begin();
	   jt != v[i].end();
	   ++jt)
	{
	  fst.add_transition(initial_state,
			     HfstBasicTransition
			     (target_state,jt->second,jt->second,jt->first));
	}
    }

  fst.set_final_weight(target_state,0.0);

  return fst;
}

StringPairVector Tagger::get_vector(const HfstBasicTransducer &tagged_fst)
{
  HfstTransducer tagged(tagged_fst,TROPICAL_OPENFST_TYPE);
  tagged.n_best(1).minimize();

  HfstTwoLevelPaths hfst_two_level_paths;
  tagged.extract_paths(hfst_two_level_paths);

  StringPairVector result_path = hfst_two_level_paths.begin()->second;
  StringPairVector result;
  
  for (StringPairVector::const_iterator it = result_path.begin();
       it != result_path.end();
       ++it)
    { 
      std::string word = it->first;
      ++it;
      std::string tag = it->first;

      StringPair p(word,tag);
      result.push_back(p);
    }

  assert(result.size() != 0);

  return result;
}

void Tagger::store(const std::string &lexical_model_file_name,
		   const std::string &sequence_model_file_name)
{
  lexical_model.store(lexical_model_file_name);
  sequence_model.store(sequence_model_file_name);
}

std::ostream &operator<<(std::ostream &out,const StringPairVector &v)
{
  for (StringPairVector::const_iterator it = v.begin() + 1;
       it != v.end() - 1;
       ++it)
    {
      out << it->first << "\t" << it->second;

      if (it + 1 != v.end() - 1)
	{ out << std::endl; }
    }
  return out;
}

#ifdef HFST_TAGGER_TEST_Tagger
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_file =
    "W	Y\n"
    "W	X\n"
    "W	X\n"
    "V	X\n"
    "V	Y"
    ;

  std::istringstream input_stream(input_file);
  
  ConfigStringPair hmm_config_string_pair1("010101","000101");
  ConfigStringPair hmm_config_string_pair2("0101","0001");
  ConfigStringPair hmm_config_string_pair3("01","00");
  
  ConfigStringPair config_string_pairs[3] =
    {hmm_config_string_pair1, hmm_config_string_pair2, 
     hmm_config_string_pair1};
  
  ConfigStringPairVector hmm_config_string_pair_vector
    (config_string_pairs,
     config_string_pairs + 2);



  Tagger hmm_tagger(input_stream,"HMM",hmm_config_string_pair_vector);

  StringVector input;
  input.push_back("W");
  input.push_back("W");
  input.push_back("W");

  StringPairVector result = hmm_tagger[input];
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_Tagger
