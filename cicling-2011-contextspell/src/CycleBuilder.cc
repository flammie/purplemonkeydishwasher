#include "CycleBuilder.h"

using hfst::TROPICAL_OPENFST_TYPE;

CycleBuilder::CycleBuilder(const SequenceWeightTable &model_weights):
  ModelBuilder(TROPICAL_OPENFST_TYPE,0.0)
{
  model_fst.set_final_weight(START_STATE,0.0);

  for (SequenceWeightTable::const_iterator it = model_weights.begin();
       it != model_weights.end();
       ++it)
    { add_sequence(it->first,it->second); }
}

void CycleBuilder::add_sequence(const std::string &sequence,float weight)
{
  StringVector split_sequence = split_at_tabs(sequence);
  
  StringVector::const_iterator first_symbol_it = split_sequence.begin();
  StringVector::const_iterator last_symbol_it = split_sequence.end() - 1;

  // Construct a path labelled with the symbols in range
  // [first_symbol_it, last_symbol_it) from START_STATE to 
  // last_transition_initial_state.
  HfstState last_transition_initial_state = 
    ModelBuilder::add_sequence(first_symbol_it,last_symbol_it);

  HfstState last_transition_target_state = START_STATE;

  std::string last_symbol = *last_symbol_it;

  add_transition(last_transition_initial_state,
		 last_transition_target_state,
		 last_symbol,
		 weight);		 
}

#ifdef HFST_TAGGER_TEST_CycleBuilder
#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>

#include "LogSequenceWeightTable.h"
#include "WordformRemover.h"
#include "LastEntryRemover.h"

using hfst::HfstTransducer;

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t\t";

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
  
  CycleBuilder cycle_builder(sequence_weight_table);

  HfstTransducer default_wf(DEFAULT_SYMBOL,TROPICAL_OPENFST_TYPE);
  HfstTransducer dt("DT",TROPICAL_OPENFST_TYPE);
  HfstTransducer nn("NN",TROPICAL_OPENFST_TYPE);
  HfstTransducer jj("JJ",TROPICAL_OPENFST_TYPE);

  // @_DEFAULT_@
  HfstTransducer default_path = default_wf;

  // @_DEFAULT_@ DT
  HfstTransducer default_dt_path = default_path;
  default_dt_path.concatenate(dt);

  // @_DEFAULT_@ DT @_DEFAULT_@
  HfstTransducer default_dt_default_path = default_dt_path;
  default_dt_default_path.concatenate(default_wf);

  // @_DEFAULT_@ DT @_DEFAULT_@ NN <-log(0.75)>
  HfstTransducer default_dt_default_nn_path = default_dt_default_path;
  default_dt_default_nn_path.concatenate(nn);
  default_dt_default_nn_path.set_final_weights(-1.0 * log(0.75));

  // @_DEFAULT_@ DT @_DEFAULT_@ JJ <-log(0.25)>
  HfstTransducer default_dt_default_jj_path = default_dt_default_path;
  default_dt_default_jj_path.concatenate(jj);
  default_dt_default_jj_path.set_final_weights(-1.0 * log(0.25));

  // (@_DEFAULT_@ DT @_DEFAULT_@ NN <-log(0.75)>) |
  //  @_DEFAULT_@ DT @_DEFAULT_@ JJ <-log(0.25)>)*
  HfstTransducer main_cycle(default_dt_default_nn_path);
  main_cycle.disjunct(default_dt_default_jj_path).repeat_star();

  // (@_DEFAULT_@ | @_DEFAULT_@ DT | @_DEFAULT_@ DT @_DEFAULT_@)?
  HfstTransducer cycle_tail(default_path);
  cycle_tail.disjunct(default_dt_path).disjunct(default_dt_default_path);
  cycle_tail.optionalize();

  // (@_DEFAULT_@ DT @_DEFAULT_@ NN <-log(0.75)>) |
  //  @_DEFAULT_@ DT @_DEFAULT_@ JJ <-log(0.25)>)*
  // (@_DEFAULT_@ | @_DEFAULT_@ DT | @_DEFAULT_@ DT @_DEFAULT_@)?
  HfstTransducer comparison_model(main_cycle);
  comparison_model.concatenate(cycle_tail).minimize();

  HfstTransducer result_cycle_fst = cycle_builder.get_model();
  result_cycle_fst.minimize();

  // comparison_model and result_cycle_fst should be equivalent.
  assert(result_cycle_fst.compare(comparison_model));

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_CycleBuilder
