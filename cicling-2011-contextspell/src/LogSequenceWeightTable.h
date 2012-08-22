#ifndef HFST_TAGGER_HEADER_LOG_SEQUENCE_WEIGHT_TABLE_H
#define HFST_TAGGER_HEADER_LOG_SEQUENCE_WEIGHT_TABLE_H

#include "SequenceWeightTable.h"
#include "SequenceWeighter.h"

class LogSequenceWeightTable : public SequenceWeightTable
{
 public:
  
  LogSequenceWeightTable(const StringTransformer &dividend_abstractor,
			 const StringTransformer &divisor_abstractor,
			 std::istream &input_file);

 protected:
  
  struct LogWeightTransformer : public SequenceWeighter::WeightTransformer
    {
      float operator() (float f) const;
    };

};


#endif // HFST_TAGGER_HEADER_LOG_SEQUENCE_WEIGHT_TABLE_H
