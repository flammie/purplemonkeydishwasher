#ifndef HFST_TAGGER_HEADER_SEQUENCE_WEIGHT_TABLE_H
#define HFST_TAGGER_HEADER_SEQUENCE_WEIGHT_TABLE_H

#include <iostream>

#include "SequenceWeighter.h"
#include "SequenceCounter.h"
#include "StringTransformer.h"

#define MAX_BUFFER 10000

class SequenceWeightTable
{
 public:

  typedef SequenceWeighter::const_iterator const_iterator;

  class MaxLineLengthExceeded
  {};

  class FileNotReadable
  {};

  class ObjectNotProperlyInitialized
  {};

  SequenceWeightTable(const StringTransformer &dividend_abstractor,
		      const StringTransformer &divisor_abstractor,
		      std::istream &input_file);
  ~SequenceWeightTable(void);
  const_iterator begin(void) const;
  const_iterator end(void) const;
  size_t get_sequence_length(void) const;
  float get_penalty_weight(void) const;

 protected:

  SequenceWeighter * sequence_weighter;

  void transform_weights
    (const SequenceWeighter::WeightTransformer &transformer);

};

#endif // HFST_TAGGER_HEADER_SEQUENCE_WEIGHT_TABLE_H
