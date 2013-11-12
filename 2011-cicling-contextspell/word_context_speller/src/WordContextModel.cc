#include "WordContextModel.h"

#include <cstdlib>

WordContextModel::WordContextModel(size_t order, 
				   std::string input_data,
				   char list_separator):
  order(order)
{
  size_t start_pos     = 0;
  size_t separator_pos = 0;

  StringCountMap n_gram_counts;
  StringCountMap n_minus_one_gram_counts;

  size_t total_n_gram_count = 0;

  replace_separator(input_data,list_separator);

  std::cerr << "Reading input data" << std::endl;

  while ((separator_pos = 
	  get_n_gram_past_end(input_data,start_pos,order+1))
	 != std::string::npos)
    {
      std::string n_gram = input_data.substr(start_pos,
					     separator_pos - start_pos);
      ++n_gram_counts[n_gram];

      std::string n_minus_one_gram = remove_last_word(n_gram);
      ++n_minus_one_gram_counts[n_minus_one_gram];

      start_pos = input_data.find(' ',start_pos + 1);
      if (start_pos != std::string::npos)
	{ ++start_pos; }
      
      ++total_n_gram_count;
      std::cerr << total_n_gram_count << "\r";
    }
  
  std::cerr << std::endl;

  std::cerr << "Bulding n-gram map." << std::endl;

  size_t pos = 0;
  size_t total = n_gram_counts.size();

  size_t highest_divisor = 0;

  for (StringCountMap::const_iterator it = n_gram_counts.begin();
       it != n_gram_counts.end();
       ++it)
    {
      std::cerr << ++pos << " of " << total << "\r";

      weight_map[it->first] =
	it->second * 1.0 
	/ 
	n_minus_one_gram_counts[remove_last_word(it->first)];

      if (highest_divisor < 
	  n_minus_one_gram_counts[remove_last_word(it->first)])
	{ highest_divisor = 
	    n_minus_one_gram_counts[remove_last_word(it->first)]; }
    }	
  
  std::cerr << std::endl;
  
  std::cerr << "Set penalty to " << 1.0/(highest_divisor + 1) << std::endl;

  weight_map.set_penalty(1.0/(highest_divisor + 1));
}

void WordContextModel::store(std::ostream &out)
{ weight_map.store(out); }

WordContextModel::WordContextModel(size_t order,std::istream &in):
  order(order),
  weight_map(in)
{}

double WordContextModel::operator[](const std::string &sentence_fragment)
{
  size_t start_pos     = 0;
  size_t separator_pos = 0;

  double total_weight = 1.0;

  while ((separator_pos = 
	  get_n_gram_past_end(sentence_fragment,start_pos,order+1))
	 != std::string::npos)
    {
      std::string n_gram = sentence_fragment.substr(start_pos,
						    separator_pos - start_pos);
      
      total_weight = total_weight*weight_map[n_gram];

      start_pos = sentence_fragment.find(' ',start_pos + 1);
      if (start_pos != std::string::npos)
	{ ++start_pos; }      
    }

  return total_weight;
}

size_t WordContextModel::get_n_gram_past_end
(const std::string &sentence_fragment,
 size_t start_pos, 
 size_t n)
{
  if (start_pos >= sentence_fragment.size())
    { return std::string::npos; }

  size_t separator_pos = start_pos;
  
  for (size_t i = 0; i < n; ++i)
    {
      separator_pos = sentence_fragment.find(' ',separator_pos + 1);
      
      if (separator_pos == std::string::npos)
	{
	  if (i + 1 == n)
	    { return sentence_fragment.size(); }
	  else
	    { break; }
	}
    }
  
  return separator_pos;
}

std::string WordContextModel::remove_last_word(const std::string &n_gram)
{
  size_t separator_pos = n_gram.find_last_of(' ');
  
  if (separator_pos == std::string::npos)
    { return ""; }
  else
    { return n_gram.substr(0,separator_pos); } 
}

void WordContextModel::replace_separator(std::string &input_data,
					 char list_separator)
{
  if (list_separator == ' ')
    { return; }

  size_t old_pos = 0;
  size_t pos     = 0;

  while ((pos = input_data.find(list_separator,old_pos + 1)) 
	 != std::string::npos)
    {
      input_data[pos] = ' ';
      old_pos = pos;
    }
}

#ifdef TESTING_WORD_CONTEXT_MODEL
#include <cassert>
#include <iostream>
int main(void)
{
  assert(WordContextModel::remove_last_word("a b c") == "a b");
  assert(WordContextModel::remove_last_word("a") == "");
  assert(WordContextModel::remove_last_word("aa bb") == "aa");

  assert(WordContextModel::get_n_gram_past_end("the big dog bit me",3,3)
	 == 15);
  assert(WordContextModel::get_n_gram_past_end("the big dog bit me",3,4)
	 == std::string("the big dog bit me").size());
  assert(WordContextModel::get_n_gram_past_end("the big dog bit",3,4)
	 == std::string::npos);

  WordContextModel word_context_model(2,
				      "a\nb\nc\na\nb\nd");

  assert(abs(word_context_model["a b c"] - 0.5) < 0.0001);
  assert(abs(word_context_model["a b d"] - 0.5) < 0.0001);
  assert(abs(word_context_model["c a b"] - 1.0) < 0.0001);
  assert(abs(word_context_model["foo bar baz"] - 1.0 / 5.0) < 0.0001);

  assert(abs(word_context_model["a b c a b d"] - 0.5*1.0*1.0*0.5) < 0.0001);

  WordContextModel word_context_model_zero(0,
					   "a\nb\nc\na\nb\nd");

  assert(abs(word_context_model_zero["a"] - 2.0/6.0) < 0.0001);
  assert(abs(word_context_model_zero["a b c"] - 2.0*2.0*1.0/216.0) < 0.0001);
}
#endif // TESTING_WORD_CONTEXT_MODEL
