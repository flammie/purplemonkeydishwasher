#ifndef HFST_TAGGER_HEADER_COMPOSE_INTERSECT_N_GRAM_MODEL_PAIR_H
#define HFST_TAGGER_HEADER_COMPOSE_INTERSECT_N_GRAM_MODEL_PAIR_H

#include <hfst/implementations/compose_intersect/ComposeIntersectRulePair.h>

using hfst::implementations::ComposeIntersectRulePair;

#include "ComposeIntersectNGramModel.h"

class ComposeIntersectNGramModelPair : public ComposeIntersectRulePair
{
 public:
  ComposeIntersectNGramModelPair(ComposeIntersectNGramModel * model1,
				 ComposeIntersectNGramModel * model2);

  ComposeIntersectNGramModelPair(ComposeIntersectNGramModel * model1,
				 ComposeIntersectNGramModelPair * model2);
  
  const TransitionSet &get_transitions(HfstState s,size_t symbol);

 protected:

  size_t default_label;
};

#endif // HFST_TAGGER_HEADER_COMPOSE_INTERSECT_N_GRAM_MODEL_PAIR_H
