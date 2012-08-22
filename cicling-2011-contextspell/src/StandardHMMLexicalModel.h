#ifndef HFST_TAGGER_HEADER_STANDARD_H_M_M_LEXICAL_MODEL_H
#define HFST_TAGGER_HEADER_STANDARD_H_M_M_LEXICAL_MODEL_H

#include <vector>

#include "LexicalModel.h"

class StandardHMMLexicalModel : public LexicalModel
{
 public:
  typedef std::map<float,std::string> WeightStringMap;
  typedef std::map<std::string,float> StringWeightMap;
  
  StandardHMMLexicalModel(std::istream &in,std::string name);
  StandardHMMLexicalModel(const std::string filename);

#ifdef HFST_TAGGER_TEST_StandardHMMLexicalModel  
  HfstTransducer get_model(void);
#endif // HFST_TAGGER_TEST_StandardHMMLexicalModel  

 protected:
  typedef std::vector<float> FloatVector;

  double standard_deviation;
  
  void init_coefficient(void);
  void smoothe_tag_probabilities
    (const WeightStringVectorVector &prefix_tag_probabilities,
     WeightStringVector &tag_probabilities);
  float get_std_dev(const FloatVector &tag_probabilities);
  FloatVector get_tag_probabilities(void);
};

#endif // HFST_TAGGER_HEADER_STANDARD_H_M_M_LEXICAL_MODEL_H
