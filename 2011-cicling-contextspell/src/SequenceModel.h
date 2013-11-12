#ifndef HFST_TAGGER_HEADER_SEQUENCE_MODEL_H
#define HFST_TAGGER_HEADER_SEQUENCE_MODEL_H

#include <vector>
#include <string>
#include <utility>

typedef std::pair<std::string,std::string> ConfigStringPair;
typedef std::vector<ConfigStringPair> ConfigStringPairVector;
typedef std::vector<float> FloatVector;

#include "ComposeIntersectNGramModelPair.h"

#define SEQUENCE_MODEL_NAME_PREFIX "SEQUENCE-MODEL:"
#define N_PREFIX                    "N="

using hfst::HfstTransducer;

class WrongCoefficientVectorSize
{};

class LogicError
{};

class CorruptedModel
{};

class SequenceModel
{
 public:

  SequenceModel(const ConfigStringPairVector &config_string_vector,
		std::istream &in,
		FloatVector coefficients=FloatVector());
  SequenceModel(const std::string filename);

  ~SequenceModel(void);
  HfstBasicTransducer tag_input(HfstBasicTransducer &fst);
  void store(const std::string &filename);  

 protected:
  typedef std::vector<size_t> SizeTVector;
  typedef std::vector<HfstTransducer> TransducerVector;

  SizeTVector n_vector;
  TransducerVector fst_vector;

  ComposeIntersectNGramModelPair * sequence_model;
  bool corrupted;

  void strip_prefix(HfstTransducer &fst);
  void read_fst(const std::string &filename);
  size_t get_n(HfstTransducer &fst);
};

#endif // HFST_TAGGER_HEADER_SEQUENCE_MODEL_H
