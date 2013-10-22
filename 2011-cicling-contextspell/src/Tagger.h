#ifndef HFST_TAGGER_HEADER_TAGGER_H
#define HFST_TAGGER_HEADER_TAGGER_H

#include <vector>

#include "StandardHMMLexicalModel.h"
#include "SequenceModel.h"

typedef std::pair<std::string,std::string> StringPair;
typedef std::vector<StringPair> StringPairVector;
typedef std::vector<std::string> StringVector;

using hfst::HfstBasicTransducer;

class Tagger
{
 public:

  Tagger(std::istream &in,
	 const std::string &name,
	 ConfigStringPairVector &config_vector,
	 FloatVector coefficients=FloatVector());
  Tagger(const std::string &lexical_model_file_name,
	 const std::string &sequence_model_file_name);
  StringPairVector operator[](const StringVector &input_sentence);
  HfstBasicTransducer get_all_taggings(const StringVector &input_sentence);
  void store(const std::string &lexical_model_file_name,
	     const std::string &sequence_model_file_name);
 protected:
  StreamReinitializer     stream_reinitializer;
  StandardHMMLexicalModel lexical_model;
  SequenceModel           sequence_model;

  HfstBasicTransducer get_fst(const StringVector &s,
			      const LexicalModel::WeightStringVectorVector &v);
  StringPairVector    get_vector(const HfstBasicTransducer &tagged_fst); 
};

std::ostream &operator<<(std::ostream &out,const StringPairVector &v);

#endif // HFST_TAGGER_HEADER_TAGGER_H
