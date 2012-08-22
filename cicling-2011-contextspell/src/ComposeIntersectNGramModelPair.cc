#include "ComposeIntersectNGramModelPair.h"

ComposeIntersectNGramModelPair::ComposeIntersectNGramModelPair
(ComposeIntersectNGramModel * model1,
 ComposeIntersectNGramModel * model2):
  ComposeIntersectRulePair(model1,model2),
    default_label(get_symbol_number(DEFAULT_SYMBOL))
{}

ComposeIntersectNGramModelPair::ComposeIntersectNGramModelPair
(ComposeIntersectNGramModel * model1,
 ComposeIntersectNGramModelPair * model2):
  ComposeIntersectRulePair(model1,model2),
    default_label(get_symbol_number(DEFAULT_SYMBOL))
{}

const TransitionSet &ComposeIntersectNGramModelPair::get_transitions
(HfstState s,size_t symbol)
{

  if (symbol == default_label)
    { return ComposeIntersectRulePair::get_transitions(s,symbol); }

  if (symbol == 0)
    { return ComposeIntersectRulePair::get_transitions(s,symbol); }

  if (not transitions_computed(s,symbol))
    {
      const TransitionSet &result = 
	ComposeIntersectRulePair::get_transitions(s,symbol);

      if (result.size() != 0)
	{ return result; }

      StatePair state_pair = state_pair_vector[s];
      const TransitionSet model1_transitions = 
	fst1->get_transitions(state_pair.first,symbol);
      const TransitionSet model2_transitions = 
	fst2->get_transitions(state_pair.second,symbol);

      if ((model1_transitions.size() == 0) or (model2_transitions.size() == 0))
	{ return result; }


      const Transition &model1_transition = *(model1_transitions.begin()); 
      const Transition &model2_transition = *(model2_transitions.begin()); 

      HfstState model1_s = model1_transition.target;
      HfstState model2_s = model2_transition.target;
      StatePair s_pair(model1_s,model2_s);
      
      float weight = model1_transition.weight + model2_transition.weight;
      
      TransitionSet transitions;
      add_transition(transitions,get_state(s_pair),symbol,symbol,weight);
      state_transition_vector[s][symbol] = transitions;
      return state_transition_vector[s][symbol];
    }

  const TransitionSet &transitions = 
    ComposeIntersectRulePair::get_transitions(s,symbol);

  if (transitions.size() == 0)
    { return get_transitions(s,default_label); }

  return transitions;
}

#ifdef HFST_TAGGER_TEST_ComposeIntersectNGramModelPair
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
  tokenizer.add_multichar_symbol(DEFAULT_SYMBOL);

  HfstTransducer lex("aXbXcX",tokenizer,TROPICAL_OPENFST_TYPE);
  HfstBasicTransducer basic_lex(lex);

  ComposeIntersectLexicon lexicon(basic_lex);

  HfstTransducer t1("a" "X" DEFAULT_SYMBOL DEFAULT_SYMBOL DEFAULT_SYMBOL DEFAULT_SYMBOL,tokenizer,TROPICAL_OPENFST_TYPE);
  t1.set_final_weights(3.0);

  HfstTransducer t2("b" "X" DEFAULT_SYMBOL DEFAULT_SYMBOL,tokenizer,TROPICAL_OPENFST_TYPE);

  HfstTransducer t3("c" "X",tokenizer,TROPICAL_OPENFST_TYPE);
  t3.set_final_weights(4.0);

  HfstBasicTransducer b1(t1);
  HfstBasicTransducer b2(t2);
  HfstBasicTransducer b3(t3);

  ComposeIntersectNGramModel * m1 =
    new ComposeIntersectNGramModel(0,b1);
  ComposeIntersectNGramModel * m2 =
    new ComposeIntersectNGramModel(1,b2);
  ComposeIntersectNGramModel * m3 =
    new ComposeIntersectNGramModel(2,b3);


  ComposeIntersectNGramModelPair * p1 =
    new ComposeIntersectNGramModelPair(m1,m2);

  ComposeIntersectNGramModelPair * p2 =
    new ComposeIntersectNGramModelPair(m3,p1);

  HfstBasicTransducer res = 
    lexicon.compose_with_rules(p2);

  HfstTransducer lex_copy(res,TROPICAL_OPENFST_TYPE);
  lex_copy.input_project().minimize();

  lex.set_final_weights(7.0);

  assert(lex.compare(lex_copy));

  delete p2;

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_ComposeIntersectNGramModelPair
