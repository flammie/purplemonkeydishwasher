#ifndef HFST_TAGGER_HEADER_SENTENCE_STREAM_H
#define HFST_TAGGER_HEADER_SENTENCE_STREAM_H

#include <vector>
#include <string>
#include <iostream>

typedef std::vector<std::string> StringVector;

class SentenceStream
{
 public:
  SentenceStream(std::istream &in);
  bool is_good();
  StringVector get_next_sentence(void);
 protected:
  std::istream &in;
};

#endif // HFST_TAGGER_HEADER_SENTENCE_STREAM_H
