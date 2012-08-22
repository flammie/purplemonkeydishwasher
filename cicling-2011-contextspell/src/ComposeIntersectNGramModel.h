#ifndef HFST_TAGGER_HEADER_COMPOSE_INTERSECT_N_GRAM_MODEL_H
#define HFST_TAGGER_HEADER_COMPOSE_INTERSECT_N_GRAM_MODEL_H

#include <hfst/HfstTransducer.h>
#include <hfst/implementations/compose_intersect/ComposeIntersectRule.h>
#include <hfst/implementations/compose_intersect/ComposeIntersectFst.h>

using hfst::implementations::HfstBasicTransducer;
using hfst::implementations::ComposeIntersectRule;
using hfst::implementations::HfstState;
typedef hfst::implementations::ComposeIntersectFst::Transition Transition;
typedef hfst::implementations::ComposeIntersectFst::TransitionSet 
TransitionSet;
using hfst::implementations::HfstTropicalTransducerTransitionData;
using hfst::implementations::HfstBasicTransition;

#include "StringTransformer.h"

class ComposeIntersectNGramModel : public ComposeIntersectRule
{
 public:

  ComposeIntersectNGramModel(size_t delay,const HfstBasicTransducer &t);
  const TransitionSet &get_transitions(HfstState s,size_t symbol);

 protected:
  
  size_t default_label;

  static HfstBasicTransducer add_delay(size_t delay,
				       const HfstBasicTransducer &t);
  
};

#endif // HFST_TAGGER_HEADER_COMPOSE_INTERSECT_N_GRAM_MODEL_H
