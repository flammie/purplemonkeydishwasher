#ifndef HFST_TAGGER_HEADER_WORDFORM_PROBABILITY_LIST_TRANSFORMER_H
#define HFST_TAGGER_HEADER_WORDFORM_PROBABILITY_LIST_TRANSFORMER_H

#include "StreamTransformer.h"

#define WF_TAG    "<wf>"
#define DUMMY_TAG "<tag>"

class WordformProbabilityListTransformer : public StreamTransformer
{
 public:

  WordformProbabilityListTransformer(std::istream &in);
  
 protected:

  class WfTagger : public StreamTransformer::LineTransformer
    {
    public:
      void input_line(const std::string &line);
    };

};

#endif // HFST_TAGGER_HEADER_WORDFORM_PROBABILITY_LIST_TRANSFORMER_H
