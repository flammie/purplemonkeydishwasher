#include "SmoothedWordContextModels.h"
#include <sstream>

SmoothedWordContextModels::SmoothedWordContextModels(std::string training_data,
						     double unigram_coefficient,
						     double bigram_coefficient,
						     double trigram_coefficient,
						     char list_separator):
  unigram_coefficient(unigram_coefficient),
  bigram_coefficient(bigram_coefficient),
  trigram_coefficient(trigram_coefficient),
  unigram_model(0,training_data,list_separator),
  bigram_model(1,training_data,list_separator),
  trigram_model(2,training_data,list_separator)
{}

double SmoothedWordContextModels::operator[] 
(const std::string &sentence_fragment)
{
  return 
    unigram_coefficient*unigram_model[sentence_fragment] +
    bigram_coefficient*bigram_model[sentence_fragment] +
    trigram_coefficient*trigram_model[sentence_fragment];
}

void SmoothedWordContextModels::store(std::ostream &out)
{
  unigram_model.store(out);
  bigram_model.store(out);
  trigram_model.store(out);

  out << unigram_coefficient << " " 
      << bigram_coefficient  << " " 
      << trigram_coefficient << std::endl;
}

SmoothedWordContextModels::SmoothedWordContextModels(std::istream &in):
  unigram_coefficient(0),
  bigram_coefficient(0),
  trigram_coefficient(0),
  unigram_model(0,in),
  bigram_model(1,in),
  trigram_model(2,in)
{ read_coefficients(in); }

void SmoothedWordContextModels::read_coefficients(std::istream &in)
{
  char line[50000];
  in.getline(line,50000);
  std::string coefficient_string(line);
  size_t space_pos_1 = coefficient_string.find(' ');
  size_t space_pos_2 = coefficient_string.find(' ',space_pos_1 + 1);

  std::string coefficient_1 = coefficient_string.substr(0,space_pos_1);
  std::string coefficient_2 = coefficient_string.substr(space_pos_1 + 1,
							space_pos_2 - 
							space_pos_1 - 1);
  std::string coefficient_3 = coefficient_string.substr(space_pos_2 + 1);

  std::istringstream coefficient_1_in(coefficient_1);
  std::istringstream coefficient_2_in(coefficient_2);
  std::istringstream coefficient_3_in(coefficient_3);

  coefficient_1_in >> unigram_coefficient;
  coefficient_2_in >> bigram_coefficient;
  coefficient_3_in >> trigram_coefficient;
}

#ifdef TESTING_SMOOTHED_WORD_CONTEXT_MODELS
#include <iostream>
#include <cassert>
#include <cstdlib>
int main(void)
{
  SmoothedWordContextModels model("a\nb\nc\na\nb\nd",0.1,0.3,0.6,'\n');

  double prob = model["a b c e"];

  double prob_a_b_c   = 0.5;
  double prob_b_c_e   = 1.0/5.0;
  double trigram_prob = 0.6*(prob_a_b_c*prob_b_c_e);

  double prob_a_b    = 1.0;
  double prob_b_c    = 0.5;
  double prob_c_e    = 1.0/6.0;
  double bigram_prob = 0.3*(prob_a_b*prob_b_c*prob_c_e);

  double prob_a       = 2.0/6.0;
  double prob_b       = 2.0/6.0;
  double prob_c       = 1.0/6.0;
  double prob_e       = 1.0/7.0;
  double unigram_prob = 0.1*(prob_a*prob_b*prob_c*prob_e);
  
  double comparison_prob = trigram_prob + bigram_prob + unigram_prob;

  assert(abs(prob - comparison_prob) < 0.0001);

  std::ostringstream out;
  model.store(out);

  std::string data = out.str();
  
  std::istringstream in(data);

  SmoothedWordContextModels model_copy(in);

  prob = model_copy["a b c e"];
  assert(abs(prob - comparison_prob) < 0.0001);
}
#endif // TESTING_SMOOTHED_WORD_CONTEXT_MODELS
