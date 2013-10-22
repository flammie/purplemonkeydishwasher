#include "ComposeIntersectNGramModel.h"

ComposeIntersectNGramModel::ComposeIntersectNGramModel
(size_t delay,const HfstBasicTransducer &t):
  ComposeIntersectRule(add_delay(delay,t)),
  default_label(get_symbol_number(DEFAULT_SYMBOL))
{}

HfstBasicTransducer ComposeIntersectNGramModel::add_delay
(size_t delay,const HfstBasicTransducer &t)
{
  HfstBasicTransducer new_t;

  HfstState initial_state = 0;
  HfstState target_state = 1;

  // Add sufficiently many new states, so that new_t has number of state of t 
  // + 2*delay states.
  (void)new_t.add_state(t.get_max_state() - 1 + 2*delay);

  // After the for loop, initial_state == delay.
  for (size_t i = 0; i < 2*delay; ++i)
    {
      new_t.set_final_weight(initial_state,0.0);

      new_t.add_transition(initial_state,
			   HfstBasicTransition(target_state,
					       DEFAULT_SYMBOL,
					       DEFAULT_SYMBOL,
					       0.0));
      initial_state = target_state;
      target_state = initial_state + 1;
    }

  HfstState s = 0;

  for (HfstBasicTransducer::const_iterator it = t.begin();
       it != t.end();
       ++it)
    {
      if (t.is_final_state(s))
	{ new_t.set_final_weight(initial_state,t.get_final_weight(s)); }

      for (HfstBasicTransducer::HfstTransitions::const_iterator jt = 
	     it->begin();
	   jt != it->end();
	   ++jt)
	{
	  new_t.add_transition
	    (initial_state,
	     HfstBasicTransition(jt->get_target_state() + 2*delay,
				 jt->get_input_symbol(),
				 jt->get_output_symbol(),
				 jt->get_weight()));
	}
      ++s;
      ++initial_state;
    }

  return new_t;
}

const TransitionSet &ComposeIntersectNGramModel::get_transitions
(HfstState s,size_t symbol)
{
  const TransitionSet &transitions = 
    ComposeIntersectRule::get_transitions(s,symbol);
  
  if ((symbol != 0) and (transitions.size() == 0))
    { return ComposeIntersectRule::get_transitions(s,default_label); }

  return transitions;
}

#ifdef HFST_TAGGER_TEST_ComposeIntersectNGramModel
#include <cassert>
#include <iostream>

#include <hfst/implementations/compose_intersect/ComposeIntersectLexicon.h>

using hfst::HfstTokenizer;
using hfst::HfstTransducer;
using hfst::TROPICAL_OPENFST_TYPE;
using hfst::implementations::ComposeIntersectLexicon;

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  HfstTokenizer tokenizer;
  HfstTransducer t("abc",tokenizer,TROPICAL_OPENFST_TYPE);
  HfstBasicTransducer b(t);
  ComposeIntersectNGramModel compose_intersect_n_gram_model(2,b);

  TransitionSet transition_set = 
    compose_intersect_n_gram_model.get_transitions(0,10);

  assert(transition_set.size() == 1);

  transition_set = 
    compose_intersect_n_gram_model.get_transitions(1,10);
  assert(transition_set.size() == 1);

  transition_set = 
    compose_intersect_n_gram_model.get_transitions(2,10);
  assert(transition_set.size() == 1);

  transition_set = 
    compose_intersect_n_gram_model.get_transitions(3,10);
  assert(transition_set.size() == 1);

  transition_set = 
    compose_intersect_n_gram_model.get_transitions(4,3);
  assert(transition_set.size() == 1);

  transition_set = 
    compose_intersect_n_gram_model.get_transitions(4,4);
  assert(transition_set.size() == 0);

  transition_set = 
    compose_intersect_n_gram_model.get_transitions(5,4);
  assert(transition_set.size() == 1);

  transition_set = 
    compose_intersect_n_gram_model.get_transitions(6,5);
  assert(transition_set.size() == 1);

  transition_set = 
    compose_intersect_n_gram_model.get_transitions(7,6);
  assert(transition_set.size() == 0);

  HfstTransducer lex("ddddabc",tokenizer,TROPICAL_OPENFST_TYPE);
  HfstBasicTransducer basic_lex(lex);
  ComposeIntersectLexicon lexicon(basic_lex);

  HfstBasicTransducer res = 
    lexicon.compose_with_rules(&compose_intersect_n_gram_model);

  HfstTransducer res_fst(res,TROPICAL_OPENFST_TYPE);
  res_fst.minimize();


  tokenizer.add_multichar_symbol(DEFAULT_SYMBOL);

  HfstTransducer 
    comparison_model("ddddabc",DEFAULT_SYMBOL DEFAULT_SYMBOL DEFAULT_SYMBOL DEFAULT_SYMBOL "abc",
		     tokenizer,TROPICAL_OPENFST_TYPE);

  assert(res_fst.compare(comparison_model));

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_ComposeIntersectNGramModel
