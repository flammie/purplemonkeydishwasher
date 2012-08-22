#include <iostream>
#include <cstdlib>

#include "Speller.h"
#include "SuggestionsInContext.h"

#define MAXBUFFER 500000
char line[MAXBUFFER];

void print_usage_and_die(int argc, char * argv[])
{
  (void)argc;
  std::cerr << "Usage: cat suggestion_file | " << argv[0] 
	    << " lexical_model_filename sequence_model_file_name"
	    << " scaling_coefficient" << std::endl;
  exit(1);
}
int main(int argc, char * argv[])
{
  if (argc != 4)
    { print_usage_and_die(argc,argv); }
  
  std::string lexical_model_fn = argv[1];
  std::string sequence_model_fn = argv[2];

  std::istringstream coeff_in(argv[3]);
  float scaling_coefficient;
  coeff_in >> scaling_coefficient;
  
  if (coeff_in.fail())
    {
      std::cerr << "ERROR: scaling_coefficient needs to be a float." 
		<< std::endl;
      print_usage_and_die(argc,argv);
    }

  Speller speller(lexical_model_fn,sequence_model_fn,scaling_coefficient);

  while (std::cin.peek() != EOF)
    {
      try
	{
	  SuggestionsInContext suggestions_in_context(std::cin);

	  std::cout << suggestions_in_context.typo << "\t"
		    << suggestions_in_context.correct_suggestion << "\t";

	  std::string speller_suggestion = 
	    speller.get_correct_spelling(suggestions_in_context);
	  std::cout << speller_suggestion << std::endl;
	}
      catch (const InvalidInput &)
	{
	  std::cout << "<ERROR>\t<error>\t<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>";
	}
    }
}
