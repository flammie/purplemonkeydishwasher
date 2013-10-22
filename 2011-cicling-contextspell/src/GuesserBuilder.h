#ifndef HFST_TAGGER_HEADER_GUESSER_BUILDER_H
#define HFST_TAGGER_HEADER_GUESSER_BUILDER_H

#include "TrieBuilder.h"

#define GUESS_TAG "<guess>"

class GuesserBuilder : public TrieBuilder
{
 public:
  GuesserBuilder(std::istream &in);
};

#endif // HFST_TAGGER_HEADER_GUESSER_BUILDER_H
