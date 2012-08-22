#ifndef HFST_TAGGER_HEADER_SEQUENCER_H
#define HFST_TAGGER_HEADER_SEQUENCER_H

#include "LexicalModel.h"
#include <hfst/implementations/compose_intersect/ComposeIntersectLexicon.h>
#include <hfst/implementations/compose_intersect/ComposeIntersectRule.h>
#include <hfst/implementations/compose_intersect/ComposeIntersectFst.h>

using hfst::implementations::ComposeIntersectRule;

class Sequencer : public LexicalModel
{
 public:
  Sequencer(StreamReinitializer stream_reinitializer,std::string name);

  Sequencer(const std::string filename);
  
  HfstTransducer &operator[](HfstTransducer &fst);

 protected:
  ComposeIntersectRule sequencer;
  
  void smoothe_tag_probabilities
    (const WeightStringVectorVector &prefix_tag_probabilities,
     WeightStringVector &tag_probabilities);
    

};

#endif // HFST_TAGGER_HEADER_SEQUENCER_H
