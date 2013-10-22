#include "WordContextSpeller.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#define MAX_BUFFER 500000 

WordContextSpeller::WordContextSpeller(std::istream &training_data_in,
				       double unigram_coefficient,
				       double bigram_coefficient,
				       double trigram_coefficient,
				       double context_coefficient):
  model(0),
  context_coefficient(context_coefficient)
{
  std::string training_data = read_data(training_data_in);
  model = new SmoothedWordContextModels(training_data,
					unigram_coefficient,
					bigram_coefficient,
					trigram_coefficient);
}

WordContextSpeller::~WordContextSpeller(void)
{ delete model; }

WordContextSpeller::WordContextSpeller(std::string speller_binary_filename):
  model(0)
{
  std::ifstream in(speller_binary_filename.c_str());
  model = new SmoothedWordContextModels(in);
  
  get_context_coefficient(in);
}

WordContextSpeller::WordContextSpeller(std::istream &speller_binary_in):
  model(0)
{
  model = new SmoothedWordContextModels(speller_binary_in);
  
  get_context_coefficient(speller_binary_in);
}

void WordContextSpeller::set_context_coefficient(double coefficient)
{ 
  context_coefficient = coefficient; 
}

void WordContextSpeller::get_context_coefficient(std::istream &in)
{
  char line[MAX_BUFFER];
  in.getline(line,MAX_BUFFER);
  std::istringstream str_in(line);
  str_in >> context_coefficient;
  if (str_in.fail())
    { context_coefficient = -1; }
}

void WordContextSpeller::store(const std::string &filename)
{
  std::ofstream out(filename.c_str());
  model->store(out);
  out << context_coefficient << std::endl;
  out.close();
}

void WordContextSpeller::store(std::ostream &out)
{
  model->store(out);
  out << context_coefficient << std::endl;
}

std::string WordContextSpeller::read_data(std::istream &in)
{
  std::string data = "||\n||";

  char line[MAX_BUFFER];

  while (in.peek() != EOF)
    {
      in.getline(line,MAX_BUFFER);
      data += std::string("\n") + std::string(line);
    }
  return data;
}

void WordContextSpeller::reorder_suggestions(WeightedStringVector &suggestions,
					     const std::string &left_context,
					     const std::string &right_context)
{
  for (WeightedStringVector::iterator it = suggestions.begin();
       it != suggestions.end();
       ++it)
    {
      std::string suggestion_string = it->second;
      std::string suggestion_in_context = 
	left_context + " " + suggestion_string + " " + right_context;
      double context_model_weight = model->operator[] (suggestion_in_context);

      it->first = it->first + context_coefficient * context_model_weight;
    }
  
  std::sort(suggestions.begin(),suggestions.end());
  std::reverse(suggestions.begin(),suggestions.end());
}

#ifdef TESTING_WORD_CONTEXT_SPELLER
#include <sstream>
#include <cassert>
int main(void)
{
  std::string data = "a\nb\nc\na\nb\nd";

  std::istringstream in(data);

  WordContextSpeller speller(in,0.1,0.3,0.6,0.5);
  
  std::string left_context  = "a";
  std::string right_context = "c";

  WeightedStringVector suggestions;
  suggestions.push_back(WeightedString(0.5*0.20,"f"));
  suggestions.push_back(WeightedString(0.5*0.45,"c"));
  suggestions.push_back(WeightedString(0.5*0.35,"b"));


  speller.reorder_suggestions(suggestions,left_context,right_context);

  double old_prob = 1;
  
  for (WeightedStringVector::const_iterator it = suggestions.begin();
       it != suggestions.end();
       ++it)
    {
      double prob = it->first;
      assert(prob <= old_prob);
      old_prob = prob;
    }

  std::ostringstream out;
  speller.store(out);

  std::string out_data = out.str();

  std::istringstream data_in(out_data);

  WordContextSpeller speller_copy(data_in);
  
  suggestions.clear();
  suggestions.push_back(WeightedString(0.5*0.20,"f"));
  suggestions.push_back(WeightedString(0.5*0.45,"c"));
  suggestions.push_back(WeightedString(0.5*0.35,"b"));
  
  
  speller_copy.reorder_suggestions(suggestions,left_context,right_context);
  
  old_prob = 1;
  
  for (WeightedStringVector::const_iterator it = suggestions.begin();
       it != suggestions.end();
       ++it)
    {
      double prob = it->first;
      assert(prob <= old_prob);
      old_prob = prob;
    }

  assert(suggestions.at(0).second == "b");
  assert(suggestions.at(1).second == "c");
  assert(suggestions.at(2).second == "f");
}
#endif // TESTING_WORD_CONTEXT_SPELLER
