#ifndef WORD_CONTEXT_SPELLER_H
#define WORD_CONTEXT_SPELLER_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "SmoothedWordContextModels.h"

typedef std::pair<double,std::string> WeightedString;
typedef std::vector<WeightedString> WeightedStringVector;

class WordContextSpeller
{
 public:
  WordContextSpeller(std::istream &training_data_in,
		     double unigram_coefficient,
		     double bigram_coefficient,
		     double trigram_coefficientg,
		     double context_coefficient);
  WordContextSpeller(std::string speller_binary_filename);
  WordContextSpeller(std::istream &speller_binary_in);
  ~WordContextSpeller(void);
  void reorder_suggestions(WeightedStringVector &suggestions,
			   const std::string &left_context,
			   const std::string &right_context);
  void store(const std::string &filename);
  void store(std::ostream &out);
  void set_context_coefficient(double coefficient);
 protected:
  SmoothedWordContextModels * model;
  double context_coefficient;

  double reweight_suggestion(const std::string &left_context,
			    WeightedString &suggestion,
			    const std::string &right_context);
  std::string read_data(std::istream &in);
  void get_context_coefficient(std::istream &in);
};

#endif // WORD_CONTEXT_SPELLER_H
