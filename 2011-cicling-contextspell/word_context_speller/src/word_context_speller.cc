#include <cmath>

#include <iostream>

#include "WordContextSpeller.h"
#include "SuggestionsInContext.h"

std::string get_context_string
(const StringVector &context_vector)
{
  std::string context_string = "";

  for (StringVector::const_iterator it = context_vector.begin();
       it != context_vector.end();
       ++it)
    {
      context_string += *it;
      if (it + 1  != context_vector.end())
	{ context_string += " "; }
    }
  
  return context_string;
}

void scale_unigram_weights(WeightedStringVector &suggestions,
			   double coefficient,
			   bool coefficient_is_prob=true)
{
  for (WeightedStringVector::iterator it = suggestions.begin();
       it != suggestions.end();
       ++it)
    { 
      if (coefficient_is_prob)
	{
	  it->first = exp(log(coefficient) - it->first);
	}
      else
	{
	  it->first = exp(coefficient - it->first);
	}
    }
}

#include <cstdlib>
#include <cstdio>

int main(int argc, char * argv[])
{
  if (argc != 3 and argc != 4)
    {
      std::cerr << "Usage: " << argv[0] << " speller context_coefficient [ probability_type_parameter ]"
		<< std::endl;
      exit(1);
    }

  WordContextSpeller * word_context_speller = 0;

  std::cerr << "Loading model" << std::endl;
  try
    { word_context_speller = new WordContextSpeller(argv[1]); }
  catch (const SyntaxErrorInFile &e)
    { 
      std::cerr << "ERROR: speller file is damaged." << std::endl;
      exit(1);
    }

  bool probability_type = true;

  if (argc == 4)
    {
      std::string prob_choice_parameter(argv[3]);
      if (prob_choice_parameter == "--penalty")
	{
	  probability_type = false; 
	}
      else if (prob_choice_parameter != "--probability")
	{ 
	  std::cerr << "ERROR: probability type parameter is not correct." << std::endl;
	  exit(1);
	}
    }
  std::istringstream coeff_in(argv[2]);

  double context_coefficient;

  coeff_in >> context_coefficient;
  
  if (coeff_in.fail())
    {
      std::cerr << "ERROR: context_coefficient has to be a double." 
		<< std::endl << std::endl;
      std::cerr << "Usage: " << argv[0] << " speller context_coefficient"
		<< std::endl;
    }

  word_context_speller->set_context_coefficient(context_coefficient);

  std::cerr << "Spelling" << std::endl;
  size_t pos = 0;

  while (std::cin.peek() != EOF)
    {
      std::cerr << ++pos << "\r";

      try
	{
	  SuggestionsInContext suggestions_in_context(std::cin);
	  
	  StringVector::iterator left_context_begin = 
	    suggestions_in_context.left_context.begin();
	  while (suggestions_in_context.left_context.end() - left_context_begin
		 > 2)
	    { ++left_context_begin; }


	  StringVector left_context_vector
	    (left_context_begin,suggestions_in_context.left_context.end());

	  StringVector right_context_vector
	    (suggestions_in_context.right_context.begin(),
	     suggestions_in_context.right_context.size() < 2 ?
	     suggestions_in_context.right_context.end() :
	     suggestions_in_context.right_context.begin() + 2);

	  std::string left_context = get_context_string(left_context_vector);
	  std::string right_context = get_context_string(right_context_vector);
	  
	  scale_unigram_weights(suggestions_in_context.suggestions,
				1 - context_coefficient,
				probability_type);

	  word_context_speller->reorder_suggestions
	    (suggestions_in_context.suggestions,
	     left_context,
	     right_context);
	  
	  std::cout << suggestions_in_context.correct_suggestion << "\t";
	  
	  for (WeightedStringVector::const_iterator it = 
		 suggestions_in_context.suggestions.begin();
	       it != suggestions_in_context.suggestions.end();
	       ++it)
	    { std::cout << it->second << "[" << it->first << "]" << "\t"; }
	  
	  std::cout << std::endl;
	  
	}
      catch (const InvalidInput &e)
	{
	  std::cerr << std::endl << "Invalid input on line " << pos
		    << std::endl;
	  continue;
	}

    }

  std::cerr << std::endl;

  delete word_context_speller;
}
