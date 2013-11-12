#include "TrieBuilder.h"

using hfst::internal_epsilon;

using hfst::TROPICAL_OPENFST_TYPE;

TrieBuilder::TrieBuilder(const SequenceWeightTable &model_weights):
  ModelBuilder(TROPICAL_OPENFST_TYPE,std::numeric_limits<float>::infinity())
{
  for (SequenceWeightTable::const_iterator it = model_weights.begin();
       it != model_weights.end();
       ++it)
    { add_sequence(it->first,it->second); }
}

void TrieBuilder::add_sequence(const std::string &sequence,float weight)
{
  StringVector split_sequence = split_at_tabs(sequence);

  HfstState target_state =
   ModelBuilder::add_sequence(split_sequence.begin(),split_sequence.end() - 1);
  
  std::string tag = *(split_sequence.end() - 1);
  
  HfstState final_state = model_fst.add_state();

  ModelBuilder::add_transition(target_state,
			       final_state,
			       internal_epsilon,
			       tag,
			       0.0);

  model_fst.set_final_weight(final_state,weight);
}

#ifdef HFST_TAGGER_TEST_TrieBuilder
#include <cassert>
#include <iostream>
#include <cmath>

#include "LexiconDivisorTransformer.h"
#include "IdentityTransformer.h"
#include "StreamTokenizer.h"
#include "LogSequenceWeightTable.h"

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

    const char * input_file =
      "man\tNN\n"
      "meal\tNN"
    ;

  std::istringstream input_stream(input_file);

  StreamTokenizer stream_tokenizer(input_stream);

  std::istream &in = stream_tokenizer.get_stream();

  LexiconDivisorTransformer lexicon_divisor_transformer;
  IdentityTransformer identity_transformer;

  LogSequenceWeightTable sequence_weight_table(identity_transformer,
					       lexicon_divisor_transformer,
					       in);

  TrieBuilder trie_builder(sequence_weight_table);

  HfstTransducer model_fst = trie_builder.get_model();

  HfstTokenizer tokenizer;
  tokenizer.add_multichar_symbol("NN");

  HfstTransducer man("man","manNN",tokenizer,TROPICAL_OPENFST_TYPE);
  HfstTransducer meal("meal","mealNN",tokenizer,TROPICAL_OPENFST_TYPE);

  man.set_final_weights(-1.0 * log(0.5));
  meal.set_final_weights(-1.0 * log(0.5));

  HfstTransducer trie(man);
  trie.disjunct(meal);
  
  assert(model_fst.compare(trie));

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_TrieBuilder
