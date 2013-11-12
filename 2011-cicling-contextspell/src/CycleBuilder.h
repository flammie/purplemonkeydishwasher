#ifndef HFST_TAGGER_HEADER_CYCLE_BUILDER_H
#define HFST_TAGGER_HEADER_CYCLE_BUILDER_H

#include <string>
#include <vector>
#include <map>
#include <climits>

#include "ModelBuilder.h"
#include "SequenceWeightTable.h"
#include "StringTransformer.h"

class CycleBuilder : public ModelBuilder
{
 public:

  CycleBuilder(const SequenceWeightTable &model_weights);

 protected:

  void add_sequence(const std::string &sequence,float weight);
};

#endif // HFST_TAGGER_HEADER_CYCLE_BUILDER_H
