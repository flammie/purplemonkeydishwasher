#ifndef WORD_CONTEXT_MODEL_H
#define WORD_CONTEXT_MODEL_H

#include <map>

#include "WeightMap.h"

typedef std::map<std::string, size_t> StringCountMap;


class WordContextModel
{
 public:
  double operator[] (const std::string &sentence_fragment);

#ifndef TESTING_WORD_CONTEXT_MODEL
 private:
#endif // TESTING_WORD_CONTEXT_MODEL
  WordContextModel(size_t order, 
		   std::string input_data,
		   char list_separator='\n');
  WordContextModel(size_t order,std::istream &in);
  void store(std::ostream &out);
 
  size_t    order;
  WeightMap weight_map;

  static size_t get_n_gram_past_end(const std::string &sentence_fragment,
				    size_t start_pos, 
				    size_t n);
  static std::string remove_last_word(const std::string &n_gram);
  static void replace_separator(std::string &input_data,char list_separator);

  friend class SmoothedWordContextModels;
};

#endif // WORD_CONTEXT_MODEL_H
