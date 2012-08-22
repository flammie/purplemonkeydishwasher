#ifndef HFST_TAGGER_HEADER_COMPLETED_CYCLE_BUILDER_H
#define HFST_TAGGER_HEADER_COMPLETED_CYCLE_BUILDER_H


#include <vector>

#include <hfst/HfstTransducer.h>

using hfst::implementations::HfstState;

#include "CycleBuilder.h"

class CompletedCycleBuilder : public CycleBuilder
{
 public:

  CompletedCycleBuilder(const SequenceWeightTable &model_weights);

 protected:
  
  typedef std::vector<HfstState> StateVector;

  size_t cycle_length;
  float penalty_weight;

  void complete_cycle(void);
  void add_default_transition(HfstState s,
			      StateVector::const_iterator it,
			      StateVector::const_iterator end);
};
 
#endif // HFST_TAGGER_HEADER_COMPLETED_CYCLE_BUILDER_H
