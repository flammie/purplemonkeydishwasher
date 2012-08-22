#ifndef HFST_TAGGER_HEADER_SEQUENCE_COUNTER_H
#define HFST_TAGGER_HEADER_SEQUENCE_COUNTER_H

#include <map>
#include <string>

class SequenceCounter
{

 public:

  class NonExistentSymbol
  {};

  typedef std::map<std::string,size_t> SequenceCounter_;
  typedef SequenceCounter_::const_iterator const_iterator;

  // Return a reference to the count of @a symbol.
  size_t &operator[] (const std::string &symbol);
  // Return a constant reference to the count of @a symbol.
  const size_t &operator[] (const std::string &symbol) const;

  const_iterator begin(void) const;
  const_iterator end(void) const;
  size_t count(const std::string &symbol) const;

protected:

  SequenceCounter_ map_;

};

#endif // HFST_TAGGER_HEADER_SEQUENCE_COUNTER_H
