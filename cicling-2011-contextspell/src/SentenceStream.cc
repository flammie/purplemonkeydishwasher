#include "SentenceStream.h"

#define MAX_BUFFER 50000

static char line[MAX_BUFFER];

static const std::string BOUNDARY = "||";

SentenceStream::SentenceStream(std::istream &in):
  in(in)
{}

bool SentenceStream::is_good()
{
  (void)in.peek();
  return in.good();
}

StringVector SentenceStream::get_next_sentence(void)
{
  StringVector sentence;
  sentence.push_back(BOUNDARY);
  sentence.push_back(BOUNDARY);

  while (is_good())
    {
      in.getline(line,MAX_BUFFER);
      if (BOUNDARY != line)
	{ break; }      
    }

  sentence.push_back(line);

  do
    {
      in.getline(line,MAX_BUFFER);
      if (BOUNDARY == line)
	{ break; }  
      sentence.push_back(line);
    }
  while (is_good());

  if (is_good())
    {
      // Eat later boundary.
      in.getline(line,MAX_BUFFER);
    }

  sentence.push_back(BOUNDARY);
  sentence.push_back(BOUNDARY);

  return sentence;
}

#ifdef HFST_TAGGER_TEST_SentenceStream
#include <cassert>
#include <iostream>
#include <sstream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input =
    "||\n"
    "||\n"
    "The\n"
    "cat\n"
    "sat\n"
    "on\n"
    "the\n"
    "mat\n"  
    "||\n"
    "||\n"
    "The\n"
    "cat\n"
    "sat\n"
    "on\n"
    "the\n"
    "mats\n"
    "||\n"
    "||\n";

  const char * sentence1[10] = 
    {"||","||","The","cat","sat","on","the","mat","||","||"};
  
  StringVector sentence_vector1(sentence1,sentence1 + 10);
  
  const char * sentence2[10] = 
    {"||","||","The","cat","sat","on","the","mats","||","||"};
  
  StringVector sentence_vector2(sentence2,sentence2 + 10);
  
  std::istringstream in(input);
  
  SentenceStream sentence_stream(in);

  assert(sentence_stream.is_good());

  StringVector string_vector = sentence_stream.get_next_sentence();

  assert(string_vector == sentence_vector1);

  assert(sentence_stream.is_good());

  string_vector = sentence_stream.get_next_sentence();

  assert(string_vector == sentence_vector2);

  assert(not sentence_stream.is_good());

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_SentenceStream
