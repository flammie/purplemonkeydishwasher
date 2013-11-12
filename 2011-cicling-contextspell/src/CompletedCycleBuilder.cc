#include "CompletedCycleBuilder.h"

CompletedCycleBuilder::CompletedCycleBuilder
(const SequenceWeightTable &model_weights):
  CycleBuilder(model_weights),
  cycle_length(model_weights.get_sequence_length()),
  penalty_weight(model_weights.get_penalty_weight())
{ complete_cycle(); }

void CompletedCycleBuilder::complete_cycle(void)
{
  if (cycle_length == 0)
    { return; }

  // We create cycle_length - 1 final states and add them to the fallback path.
  // Finally we complete the fallback path by adding START_STATE to it.
  StateVector fallback_path;

  for (size_t i = 0; i < cycle_length - 1; ++i)
    { 
      fallback_path.push_back(model_fst.add_state()); 
      model_fst.set_final_weight(fallback_path.back(),penalty_weight);
    }
  fallback_path.push_back(START_STATE);

  // We add transitions with DEFAULT_SYMBOL between the consectutive
  // states in fallback_path. The last transition carries a penalty weight.
  for (StateVector::iterator it = fallback_path.begin();
       it != fallback_path.end();
       ++it)
    {
      if (it + 1 == fallback_path.end())
	{ break; }

      HfstState initial_state = *it;     
      HfstState target_state = *(it+1);
      float weight = (target_state == START_STATE ? penalty_weight : 0.0);

      add_transition(initial_state,target_state,DEFAULT_SYMBOL,weight);
    }

  add_default_transition
    (START_STATE,fallback_path.begin(),fallback_path.end());
}

void CompletedCycleBuilder::add_default_transition
(HfstState s,
 StateVector::const_iterator it,
 StateVector::const_iterator end)
{
  float weight = (*it == START_STATE ? penalty_weight : 0.0);

  bool found_default_transition = false;

  const HfstBasicTransducer::HfstTransitions &transitions = model_fst[s];
  
  for (HfstBasicTransducer::HfstTransitions::const_iterator transition_it = 
	 transitions.begin();
       transition_it != transitions.end();
       ++transition_it)
    {
      if (transition_it->get_input_symbol() == DEFAULT_SYMBOL)
	{ found_default_transition = true; }
      
      if (it + 1 != end)
	{ add_default_transition(transition_it->get_target_state(),
				 it + 1,
				 end); }
    }
  
  if (not found_default_transition)
    { add_transition(s,*it,DEFAULT_SYMBOL,weight); }
}

#ifdef HFST_TAGGER_TEST_CompletedCycleBuilder
#include <cassert>
#include <iostream>

#include "LogSequenceWeightTable.h"
#include "WordformRemover.h"
#include "LastEntryRemover.h"

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_file =
    "the	DT	cat	NN\n"
    "the	DT	big	JJ\n"
    "this	DT	guy	NN\n"
    "this	DT	guy	NN"
    ;

  std::istringstream input_stream(input_file);

  WordformRemover wordform_remover;
  LastEntryRemover last_entry_remover;

  LogSequenceWeightTable sequence_weight_table(wordform_remover,
					       last_entry_remover,
					       input_stream);
  
  CompletedCycleBuilder completed_cycle_builder(sequence_weight_table);

  HfstTransducer model_fst = completed_cycle_builder.get_model();

  /* And we should actually test stuff here...!!.. */

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_CompletedCycleBuilder
