#include "SuggestionsInContext.h"

#define MAXBUFFER 500000
static char line[MAXBUFFER];

SuggestionsInContext::SuggestionsInContext(std::istream &in)
{  
  in.getline(line,MAXBUFFER);
  init_fields(line);
}

void SuggestionsInContext::init_fields(const std::string &l)
{
  StringVector entries = split_at_symbol(l,'\t');
  if (entries.size() < 4)
    { throw InvalidInput(); }

  typo = entries.at(0);
  correct_suggestion = entries.at(1);

  set_suggestions(entries.begin() + 2,entries.end() - 1);

  parse_context(entries.back());
}

StringVector SuggestionsInContext::split_at_symbol
(const std::string &l,char symbol)
{
  size_t last_tab_pos = std::string::npos;
  size_t tab_pos = std::string::npos;
  
  StringVector result;

  while ((tab_pos = l.find(symbol,last_tab_pos + 1)) != std::string::npos)
    {
      std::string token = l.substr(last_tab_pos + 1, 
				   tab_pos - last_tab_pos - 1);
      if (token.size() != 0)
	{ result.push_back(token); }
      last_tab_pos = tab_pos;
    }

  if (last_tab_pos + 1 != l.size())
    { result.push_back(l.substr(last_tab_pos + 1)); }

  return result;
}

void SuggestionsInContext::set_suggestions(StringVector::const_iterator begin,
					   StringVector::const_iterator end)
{
  for (StringVector::const_iterator it = begin; it != end; ++it)
    {
      WeightedString weighted_suggestion = parse_weighted_string(*it);
      suggestions.push_back(weighted_suggestion);
    }
}

void SuggestionsInContext::parse_context(const std::string context_string)
{
  StringVector context = split_at_symbol(context_string,' ');
  
  bool left = true;

  for (StringVector::const_iterator it = context.begin();
       it != context.end();
       ++it)
    {
      if (*it == "*")
	{ 
	  left = false;
	  continue;
	}
      if (left)
	{ left_context.push_back(*it); }
      else
	{ right_context.push_back(*it); }
    }
}

WeightedString SuggestionsInContext::parse_weighted_string
(const std::string &suggestion_string)
{
  const size_t opening_bracket_pos = suggestion_string.find('[');
  const size_t closing_bracket_pos = suggestion_string.find('[');

  if (not (opening_bracket_pos != std::string::npos or
	   closing_bracket_pos != std::string::npos or
	   opening_bracket_pos <  closing_bracket_pos or
	   closing_bracket_pos == suggestion_string.size() - 1))
    { throw InvalidInput(); }

  const std::string wf = suggestion_string.substr(0,opening_bracket_pos);
  const std::string weight_string = suggestion_string.substr
    (opening_bracket_pos + 1, closing_bracket_pos - opening_bracket_pos - 1);

  if (wf.empty())
    { throw InvalidInput(); }

  std::istringstream in(weight_string);
  float weight;
  in >> weight;

  if (in.fail())
    { weight = 1000000000.0; }

  return WeightedString(weight,wf);
}

#ifdef HFST_TAGGER_TEST_SuggestionsInContext
#include <cassert>
#include <cmath>
#include <iostream>

struct TestSuggestionsInContext
{
  StringVector test_split_at_symbol(const std::string &line,char symbol)
  { return SuggestionsInContext::split_at_symbol(line,symbol); }
  
  WeightedString test_parse_weighted_string(const std::string &s)
  { return SuggestionsInContext::parse_weighted_string(s); }
};

int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  TestSuggestionsInContext test_suggestions_in_context;
  
  StringVector v =
    test_suggestions_in_context.test_split_at_symbol(" s *   ss n ",' ');

  assert(v.size() == 4);
  assert(v.at(0) == "s");
  assert(v.at(1) == "*");
  assert(v.at(2) == "ss");
  assert(v.at(3) == "n");

  WeightedString weighted_string = 
    test_suggestions_in_context.test_parse_weighted_string("mist[36.049778]");

  assert(std::abs(weighted_string.first - 36.049778) < 0.001);
  assert(weighted_string.second == "mist");
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_SuggestionsInContext
