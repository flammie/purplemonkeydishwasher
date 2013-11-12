#include "SequenceModel.h"

#include "StreamReinitializer.h"
#include "NGramModelConstructor.h"

#include <hfst/implementations/compose_intersect/ComposeIntersectLexicon.h>

using hfst::implementations::ComposeIntersectLexicon;
using hfst::TROPICAL_OPENFST_TYPE;
using hfst::HfstInputStream;
using hfst::HfstOutputStream;

SequenceModel::SequenceModel
(const ConfigStringPairVector &config_string_pair_vector,
 std::istream &in,
 FloatVector coefficients):
  sequence_model(0),
  corrupted(0)
{
  StreamReinitializer stream_reinitializer(in);

  if (coefficients.empty())
    { coefficients = FloatVector(config_string_pair_vector.size(),1.0); }

  if (coefficients.size() != config_string_pair_vector.size())
    { throw WrongCoefficientVectorSize(); }

  for (ConfigStringPairVector::const_iterator it = 
	 config_string_pair_vector.begin();
       it != config_string_pair_vector.end();
       ++it)
    {
      NGramModelConstructor n_gram_model_constructor
	(it->first,
	 it->second,
	 stream_reinitializer.get_stream(),
	 coefficients[it - config_string_pair_vector.begin()]);

      stream_reinitializer.reinitialize();
  
      size_t n = it->first.size() / 2;

      n_vector.push_back(n);
      fst_vector.push_back(n_gram_model_constructor.get_model());

      for (size_t i = 0; i < n; ++i)
	{
	  if (sequence_model == 0)
	    {
	      ComposeIntersectNGramModel * model1 = 
		new ComposeIntersectNGramModel
		(i,n_gram_model_constructor.get_model());

	      ComposeIntersectNGramModel * model2 = 
		new ComposeIntersectNGramModel
		(++i,n_gram_model_constructor.get_model());

	      sequence_model = 
		new ComposeIntersectNGramModelPair(model1,model2); 
	    }
	  else
	    { 
	      ComposeIntersectNGramModel * model = 
		new ComposeIntersectNGramModel
		(i,n_gram_model_constructor.get_model());

	      sequence_model = 
		new ComposeIntersectNGramModelPair(model,sequence_model); 
	    }
	}
    }
}

SequenceModel::SequenceModel(const std::string filename):
  sequence_model(0),
  corrupted(0)
{ 
  try
    { read_fst(filename); }
  catch (const TransducerHasWrongTypeException &)
    { std::cerr << "Too old hfst version!" << std::endl; }

}

void SequenceModel::strip_prefix(HfstTransducer &model)
{
  std::string name = model.get_name();

  if (name.find(SEQUENCE_MODEL_NAME_PREFIX) != 0)
    {  corrupted = true;  }

  size_t prefix_length = std::string(SEQUENCE_MODEL_NAME_PREFIX).size();
  name = name.substr(prefix_length);

  model.set_name(name);
}

void SequenceModel::read_fst(const std::string &filename)
{
  HfstInputStream in(filename);

  while (in.is_good())
    {
      HfstTransducer fst(in);

      strip_prefix(fst);
      size_t n = get_n(fst);
      
      n_vector.push_back(n);
      fst_vector.push_back(fst);

      for (size_t i = 0; i < n; ++i)
	{
	  if (sequence_model == 0)
	    {
	      if (n < 2)
		{ throw LogicError(); }

	      ComposeIntersectNGramModel * model1 = 
		new ComposeIntersectNGramModel(i,fst);
	      
	      ++i;

	      ComposeIntersectNGramModel * model2 = 
		new ComposeIntersectNGramModel(i,fst);

	      sequence_model = 
		new ComposeIntersectNGramModelPair(model1,model2); 	     
	    }
	  else
	    {
	      ComposeIntersectNGramModel * model = 
		new ComposeIntersectNGramModel(i,fst);

	      sequence_model = 
		new ComposeIntersectNGramModelPair(model,sequence_model); 
	    }
	}
    }
}

void SequenceModel::store(const std::string &filename)
{
  HfstOutputStream fst_out(filename,TROPICAL_OPENFST_TYPE);
  
  if (n_vector.size() != fst_vector.size())
    { throw LogicError(); }

  for (size_t i = 0; i < fst_vector.size(); ++i)
    {       
      std::ostringstream out;

      out << SEQUENCE_MODEL_NAME_PREFIX 
	  << N_PREFIX 
	  << n_vector[i] 
	  << fst_vector[i].get_name();

      std::string name = out.str();
      std::string old_name = fst_vector[i].get_name();
      fst_vector[i].set_name(name);

      std::cerr << "Writing: " << fst_vector[i].get_name() << " in " 
		<< filename << std::endl;

      fst_out << fst_vector[i];
      fst_vector[i].set_name(old_name);
    }
}

size_t SequenceModel::get_n(HfstTransducer &fst)
{
  std::string name = fst.get_name();

  if (name.find(N_PREFIX) != 0)
    { corrupted = true; }

  size_t prefix_length = std::string(N_PREFIX).size();
  name = name.substr(prefix_length);

  std::istringstream in(name);
  size_t n;
  in >> n;
  
  size_t n_length = 0;
  while ('0' <= name[n_length] and name[n_length] <= '9')
    { ++n_length; }
  name = name.substr(n_length);

  fst.set_name(name);  

  return n;
}

SequenceModel::~SequenceModel(void)
{ delete sequence_model; }

HfstBasicTransducer SequenceModel::tag_input(HfstBasicTransducer &fst)
{
  if (corrupted)
    { throw CorruptedModel(); }
  ComposeIntersectLexicon unigram_tagged_sentence(fst);
  return unigram_tagged_sentence.compose_with_rules(sequence_model);
}

#ifdef HFST_TAGGER_TEST_SequenceModel
#include <cmath>
#include <cassert>
#include <iostream>

using hfst::HfstTokenizer;
using hfst::TROPICAL_OPENFST_TYPE;

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_file =
    "W	Y\n"
    "W	X\n"
    "W	X\n"
    "W	X\n"
    "W	X"
    ;
  
  float y_x_weight = -1 * log(1.0/4.0);
  float x_x_weight = -1 * log(3.0/4.0);
  float z_x_weight = -1 * log(1.0/5.0);
  float penalty_weight = -1 * log(1.0/5.0);

  (void)y_x_weight;
  (void)x_x_weight;
  (void)z_x_weight;
  (void)penalty_weight;

  std::istringstream input_stream(input_file);
  
  ConfigStringPair config_string_pair1("0101","0001");

  ConfigStringPairVector config_string_pair_vector(1,config_string_pair1);
  SequenceModel sequence_model(config_string_pair_vector,input_stream);

  HfstTokenizer tokenizer;
  HfstTransducer input1("WXWX",tokenizer,TROPICAL_OPENFST_TYPE);
  HfstTransducer input2("WYWX",tokenizer,TROPICAL_OPENFST_TYPE);
  HfstTransducer input3("WZWX",tokenizer,TROPICAL_OPENFST_TYPE);

  HfstTransducer input(input1);

  input.disjunct(input2).disjunct(input3).minimize();

  HfstBasicTransducer basic(input);

  HfstBasicTransducer tagged_basic = sequence_model.tag_input(basic);

  HfstTransducer tagged_fst(tagged_basic,TROPICAL_OPENFST_TYPE);

  //std::cerr << tagged_fst.minimize() << std::endl;
  
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_SequenceModel
