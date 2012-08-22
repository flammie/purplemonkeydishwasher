#ifndef HFST_TAGGER_HEADER_N_GRAM_MODEL_CONSTRUCTOR_H
#define HFST_TAGGER_HEADER_N_GRAM_MODEL_CONSTRUCTOR_H

#include "CompletedCycleBuilder.h"
#include "StreamReinitializer.h"

class NGramModelConstructor
{
 public:

  class UnEqualConfigStringSizes {};

  NGramModelConstructor(const std::string &dividend_abstracter_config_string,
			const std::string &divisor_abstracter_config_string,
			std::istream &in,
			float coefficient = 1.0);
  HfstTransducer get_model(void);

 protected:
  static float * c;
  HfstTransducer model;

  friend float multiply(float w);
};

#endif // HFST_TAGGER_HEADER_N_GRAM_MODEL_CONSTRUCTOR_H
