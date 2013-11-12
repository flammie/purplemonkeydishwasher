#include "SequenceWeighter.h"

SequenceWeighter::SequenceWeighter
(const SequenceCounter &input_counter,
 const SequenceCounter &abstracted_input_counter,
 const StringTransformer * abstracter):
  is_valid(true)
{
  size_t maximum_divisor = 1;

  for (SequenceCounter::const_iterator it = input_counter.begin();
       it != input_counter.end();
       ++it)
    {
      const std::string &symbol = it->first;
      std::string abstracted_symbol = abstracter->transform(symbol);

      if (abstracted_input_counter.count(abstracted_symbol) == 0)
	{ 
	  is_valid = false;
	  throw LogicError(); 
	}

      size_t input_counter_weight = it->second;
      size_t abstracted_input_counter_weight = 
	abstracted_input_counter[abstracted_symbol];

      map_[symbol] = 
	input_counter_weight * 1.0 / abstracted_input_counter_weight;

      maximum_divisor = 
	(maximum_divisor < abstracted_input_counter_weight ?
	 abstracted_input_counter_weight : maximum_divisor);
    }
  
  penalty_weight = 1.0 / (maximum_divisor + 1.0);
}

SequenceWeighter::const_iterator SequenceWeighter::begin(void) const
{
  if (not is_valid)
    { throw InvalidObject(); }
  return map_.begin();
}

SequenceWeighter::const_iterator SequenceWeighter::end(void) const
{
  if (not is_valid)
    { throw InvalidObject(); }
  return map_.end();
}

void SequenceWeighter::transform_weights(const WeightTransformer &transformer)
{
  for (StringWeighter_::iterator it = map_.begin();
       it != map_.end();
       ++it)
    { it->second = transformer(it->second); }
  
  penalty_weight = transformer(penalty_weight);
}

size_t SequenceWeighter::get_sequence_length(void) const
{
  if (map_.empty())
    { return 0; }

  std::string first_sequence = map_.begin()->first;

  size_t pos = std::string::npos;
  size_t tab_count = 0;

  while ((pos = first_sequence.find('\t',pos+1)) != std::string::npos)
    { ++tab_count; }

  return tab_count + 1;
}

float SequenceWeighter::get_penalty_weight(void) const
{ return penalty_weight; }

#ifdef HFST_TAGGER_TEST_SequenceWeighter

#include <cassert>
#include <iostream>

class TestTransformer : public StringTransformer
{
public:
  std::string transform(const std::string &symbol) const
  {
    if (symbol == "a")
      { return "a"; }
    return "";
  }
};

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  TestTransformer abstracter;
  SequenceCounter input_counter;
  SequenceCounter abstracted_input_counter;

  input_counter["a"] += 2;
  input_counter["b"] += 1;
  input_counter["c"] += 3;
  
  abstracted_input_counter[abstracter.transform("a")] += 2;
  abstracted_input_counter[abstracter.transform("b")] += 1;
  abstracted_input_counter[abstracter.transform("c")] += 3;

  SequenceWeighter sequence_weighter(input_counter,
				     abstracted_input_counter,
				     &abstracter);

  SequenceWeighter::const_iterator it = sequence_weighter.begin();
  assert(it != sequence_weighter.end());
  // "a"
  assert(it->second == 1.0);

  ++it;
  assert(it != sequence_weighter.end());
  // "b"
  assert(static_cast<double>(it->second) == 0.25);

  ++it;
  assert(it != sequence_weighter.end());
  // "c"
  assert(static_cast<double>(it->second) == 0.75);

  ++it;
  assert(it == sequence_weighter.end());

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_SequenceWeighter
