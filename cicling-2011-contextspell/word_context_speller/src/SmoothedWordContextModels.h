#ifndef SMOOTHED_WORD_CONTEXT_MODELS_H
#define SMOOTHED_WORD_CONTEXT_MODELS_H

#include <string>

#include "WordContextModel.h"

class SmoothedWordContextModels
{
 public:
  SmoothedWordContextModels(std::string training_data,
			    double unigram_coefficient,
			    double bigram_coefficient,
			    double trigram_coefficient,
			    char list_separator='\n');
  SmoothedWordContextModels(std::istream &in);			    
  double operator[] (const std::string &sentence_fragment);
  void store (std::ostream &out);
 private:
  double unigram_coefficient;
  double bigram_coefficient;
  double trigram_coefficient;

  WordContextModel unigram_model;
  WordContextModel bigram_model;
  WordContextModel trigram_model;

  void read_coefficients(std::istream &in);
};


#endif // SMOOTHED_WORD_CONTEXT_MODELS_H
