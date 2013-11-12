#ifndef HFST_TAGGER_HEADER_SUGGESTIONS_IN_CONTEXT_H
#define HFST_TAGGER_HEADER_SUGGESTIONS_IN_CONTEXT_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <sstream>

typedef std::pair<double,std::string> WeightedString;
typedef std::vector<WeightedString> WeightedStringVector;
typedef std::pair<std::string,std::string> StringPair;
typedef std::vector<std::string> StringVector;
typedef std::vector<StringPair> StringPairVector;

class InvalidInput
{};

class SuggestionsInContext
{
 public:
  std::string typo;
  std::string correct_suggestion;
  
  StringVector left_context;
  WeightedStringVector suggestions;
  StringVector right_context;
  
  SuggestionsInContext(std::istream &in);

 protected:
  void init_fields(const std::string &l);
  static StringVector split_at_symbol(const std::string &l,char symbol);
  void set_suggestions(StringVector::const_iterator begin,
		       StringVector::const_iterator end);
  void parse_context(const std::string context_string);
  static WeightedString parse_weighted_string
    (const std::string &suggestion_string);

#ifdef HFST_TAGGER_TEST_SuggestionsInContext 
  friend class TestSuggestionsInContext;
#endif // HFST_TAGGER_TEST_SuggestionsInContext

};

#endif // HFST_TAGGER_HEADER_SUGGESTIONS_IN_CONTEXT_H
