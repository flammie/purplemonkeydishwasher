#include "StreamMarkovizer.h"

StreamMarkovizer::StreamMarkovizer(size_t n,std::istream &in):
  StreamTransformer(in)
{
  LineJoiner line_joiner(n);
  transform_input_data(line_joiner);
}

StreamMarkovizer::LineJoiner::LineJoiner(size_t n):
  n(n)
{}

void StreamMarkovizer::LineJoiner::input_line(const std::string &line)
{
  push(line);

  if (string_queue.size() == n)
    { transformed_line = get_string(); }
}

void StreamMarkovizer::LineJoiner::push(const std::string &s)
{
  if (string_queue.size() == n)
    { string_queue.pop(); }
  string_queue.push(s);  
}

std::string StreamMarkovizer::LineJoiner::get_string(void)
{
  StringQueue string_queue_copy(string_queue);

  std::string result;
  while (not string_queue_copy.empty())
    {
      result += string_queue_copy.front();
      string_queue_copy.pop();
      if (not string_queue_copy.empty())
	{ result += "\t"; }
    }
  return result;
}

#ifdef HFST_TAGGER_TEST_StreamMarkovizer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_data =
    "the	DT\n"
    "cat	NN\n"
    "sat	VBD\n"
    "under	ADP\n"
    "the	DT\n"
    "tree	NN\n"
    ;

  std::istringstream in(input_data);
  
  StreamMarkovizer stream_markovizer(3,in);

  std::istream &markovized_in = stream_markovizer.get_stream();

  char line[1000];

  markovized_in.getline(line,1000);
  assert(not markovized_in.eof());
  assert(std::string(line) == "the\tDT\tcat\tNN\tsat\tVBD");

  markovized_in.getline(line,1000);
  assert(not markovized_in.eof());
  assert(std::string(line) == "cat\tNN\tsat\tVBD\tunder\tADP");

  markovized_in.getline(line,1000);
  assert(not markovized_in.eof());
  assert(std::string(line) == "sat\tVBD\tunder\tADP\tthe\tDT");

  markovized_in.getline(line,1000);
  assert(not markovized_in.eof());
  assert(std::string(line) == "under\tADP\tthe\tDT\ttree\tNN");

  (void)markovized_in.peek();
  assert(markovized_in.eof());

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_StreamMarkovizer
