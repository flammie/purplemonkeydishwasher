#include "SequenceWeightTable.h"

#include "StringTransformerList.h"

SequenceWeightTable::SequenceWeightTable
(const StringTransformer &dividend_abstractor,
 const StringTransformer &divisor_abstractor,
 std::istream &input_file):
  sequence_weighter(0)
{
  
  StringTransformerList empty;
  StringTransformerList abstract_once(dividend_abstractor,empty);
  StringTransformerList abstract_twice(divisor_abstractor,abstract_once);

  (void)input_file.peek();
  if (input_file.fail())
    { throw FileNotReadable(); }

  SequenceCounter dividend_counter;
  SequenceCounter divisor_counter;

  while (input_file)
    {
      char line[MAX_BUFFER];
      input_file.getline(line,MAX_BUFFER);

      std::string input_line(line);

      if (input_line == "")
	{ continue; }
      
      if (input_file.fail())
	{ throw MaxLineLengthExceeded(); }

      ++dividend_counter[dividend_abstractor.transform(input_line)];
      ++divisor_counter[abstract_twice.transform(input_line)];
    }

  sequence_weighter = new SequenceWeighter(dividend_counter,
					   divisor_counter,
					   &abstract_twice); 
}

SequenceWeightTable::~SequenceWeightTable(void)
{ delete sequence_weighter; }

SequenceWeightTable::const_iterator SequenceWeightTable::begin(void) const
{
  if (sequence_weighter == 0)
    { throw ObjectNotProperlyInitialized(); }
  return sequence_weighter->begin(); 
}

SequenceWeightTable::const_iterator SequenceWeightTable::end(void) const
{
  if (sequence_weighter == 0)
    { throw ObjectNotProperlyInitialized(); }
  return sequence_weighter->end(); 
}

void SequenceWeightTable::transform_weights
(const SequenceWeighter::WeightTransformer &transformer)
{ 
  if (sequence_weighter == 0)
    { throw ObjectNotProperlyInitialized(); }
  sequence_weighter->transform_weights(transformer); 
}

size_t SequenceWeightTable::get_sequence_length(void) const
{ 
  if (sequence_weighter == 0)
    { throw ObjectNotProperlyInitialized(); }
  return sequence_weighter->get_sequence_length(); 
}

float SequenceWeightTable::get_penalty_weight(void) const
{
  if (sequence_weighter == 0)
    { throw ObjectNotProperlyInitialized(); }
  return sequence_weighter->get_penalty_weight();
}

#ifdef HFST_TAGGER_TEST_SequenceWeightTable
#include <cassert>
#include <iostream>
#include <sstream>

#include "WordformRemover.h"
#include "LastEntryRemover.h"

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  const char * input_file =
    "the	DT	cat	NN\n"
    "the	DT	big	JJ\n"
    "this	DT	guy	NN\n"
    "this	DT	guy	NN"
    ;

  std::istringstream input_stream(input_file);

  WordformRemover wordform_remover;
  LastEntryRemover last_entry_remover;

  SequenceWeightTable sequence_weight_table(wordform_remover,
					    last_entry_remover,
					    input_stream);

  SequenceWeightTable::const_iterator it = sequence_weight_table.begin();
  assert(it != sequence_weight_table.end());
  assert(it->first == DEFAULT_SYMBOL "\tDT\t" DEFAULT_SYMBOL "\tJJ");
  assert(static_cast<float>(it->second) == 0.25);

  ++it;
  assert(it != sequence_weight_table.end());
  assert(it->first == DEFAULT_SYMBOL "\tDT\t" DEFAULT_SYMBOL "\tNN");
  assert(static_cast<float>(it->second) == 0.75);

  ++it;
  assert(it == sequence_weight_table.end());

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_SequenceWeightTable
