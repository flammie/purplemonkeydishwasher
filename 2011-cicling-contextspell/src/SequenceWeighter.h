#ifndef HFST_TAGGER_HEADER_SEQUENCE_WEIGHTER_H
#define HFST_TAGGER_HEADER_SEQUENCE_WEIGHTER_H

#include <map>
#include <string>

#include "SequenceCounter.h"
#include "StringTransformer.h"

class SequenceWeighter
{
 public:

  struct WeightTransformer
  {
    virtual float operator() (float f) const = 0;
  };
  
  class LogicError
  {};

  class InvalidObject
  {};

  typedef std::map<std::string,float> StringWeighter_;
  typedef StringWeighter_::const_iterator const_iterator;

  // For each symbol X found in input_counter, SequenceWeighter stores
  // the weight 
  // input_counter[X] / abstracted_input_counter[abstracter->transform(X)]
  //
  // If input_counter contains a symbol X s.t. abstracter->transform(X) is not
  // in abstracted_input_counter a SequenceWeighter::LogicError is thrown.
  SequenceWeighter(const SequenceCounter &input_counter,
		   const SequenceCounter &abstracted_input_counter,
		   const StringTransformer * abstracter);
  
  // Iterator to the start of the range of pairs <std::string,float>.
  // If the constructor threw a LogiError, this funcion will throw 
  // InvalidObject.
  const_iterator begin(void) const;

  // Iterator to the end of the range of pairs <std::string,float>
  // If the constructor threw a LogiError, this funcion will throw 
  // InvalidObject.
  const_iterator end(void) const;

  size_t get_sequence_length(void) const;

  float get_penalty_weight(void) const;

 protected:

  bool is_valid;
  StringWeighter_ map_;
  float penalty_weight;

  void transform_weights(const WeightTransformer &transformer);

  friend class SequenceWeightTable;

};

#endif // HFST_TAGGER_HEADER_SEQUENCE_WEIGHTER_H
