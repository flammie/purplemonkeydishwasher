#ifndef HFST_TAGGER_HEADER_H_M_M_TAGGER_H
#define HFST_TAGGER_HEADER_H_M_M_TAGGER_H

#include "Tagger.h"

class HMMTagger : public Tagger
{
 public:
  HMMTagger(std::istream &in,const std::string &name);
  HMMTagger(const std::string &lexical_model_file_name,
	    const std::string &sequence_model_file_name);
};

#endif // HFST_TAGGER_HEADER_H_M_M_TAGGER_H
