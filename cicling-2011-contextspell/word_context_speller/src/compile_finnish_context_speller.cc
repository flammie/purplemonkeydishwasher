#include <iostream>
#include <cstdlib>
#include <fstream>

#include "WordContextSpeller.h"

double unigram_model_weight = 0.120306;
double bigram_model_weight  = 0.614619;
double trigram_model_weight = 0.265075;

int main(int argc, char * argv[])
{
  if (argc != 3)
    {
      std::cerr << "usage: " << argv[0] << " training_data_file output_file" 
		<< std::endl;
      exit(1);
    }

  std::ifstream in(argv[1],std::ios::in);

  if (in.bad() or in.fail())
    {
      std::cerr << "Trainig data file " << argv[1] << " couldn't be read."
		<< std::endl;
      exit(1);
    }

  WordContextSpeller finnish_speller(in,
				     unigram_model_weight,
				     bigram_model_weight,
				     trigram_model_weight,
				     1.0);

  finnish_speller.store(argv[2]);
}

