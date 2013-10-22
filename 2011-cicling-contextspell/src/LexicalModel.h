#ifndef HFST_TAGGER_HEADER_LEXICAL_MODEL_H
#define HFST_TAGGER_HEADER_LEXICAL_MODEL_H

#include <utility>
#include <vector>
#include <map>

#include "LanguageModel.h"
#include "StreamReinitializer.h"

#define LEXICAL_MODEL_NAME_PREFIX "LEXICAL-MODEL:"

using hfst::HfstOneLevelPaths;
using hfst::StringVector;
using hfst::HfstTokenizer;

class LexicalModel : public LanguageModel
{
 public:

  class NotALexicalModel
  {};

  typedef std::pair<float,std::string> WeightString;
  typedef std::vector<WeightString> WeightStringVector;
  typedef std::vector<WeightStringVector> WeightStringVectorVector;

  // This constructor that takes as input a stream of wordform tag pairs 
  // separated by newlines. A wordform and tag on the same line need to be
  // separated by a tabulator. The lexical model receives a name @a name, which
  // is stored with the binary, if the lexical model is written to file.
  LexicalModel(std::istream &in,std::string name);

  // This constructor reads a lexical model from the file @a filename.
  LexicalModel(const std::string filename,bool init_tag_probabilities=true);

  // Write the lexical model to file @a filename.
  void store(const std::string &filename);

  WeightStringVector operator[](std::string wordform);

  HfstTransducer get_model(void);

 protected:
  typedef std::map<std::string,float> StringWeightMap;

  HfstTokenizer    tokenizer;
  HfstTransducer   model;
  bool             corrupted;
  StringWeightMap  tag_probabilities;

  LexicalModel(HfstInputStream &in);
  void store(HfstOutputStream &out);
  void strip_prefix(void);
  void extract_tags_and_weights(HfstOneLevelPaths * paths,
				WeightStringVector &res,
				bool convert_to_tropical_weight);
  void guess(std::string wordform,WeightStringVector &results);
  std::string invert(const std::string &wordform);
  virtual void smoothe_tag_probabilities
    (const WeightStringVectorVector &prefix_tag_probabilities,
     WeightStringVector &tag_probabilities) = 0;
  void bayesian_invert(const std::string &suffix,WeightStringVector &results);
  void convert_probabilities_to_tropical_weights(WeightStringVector &results);
  float convert_tropical_weight_to_probability(float w);
  float get_tag_probability(const std::string &symbol);
  void initialize_tag_probabilities(void);
};


#endif // HFST_TAGGER_HEADER_LEXICAL_MODEL_H
