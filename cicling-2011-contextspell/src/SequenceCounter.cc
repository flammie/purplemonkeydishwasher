#include "SequenceCounter.h"

size_t &SequenceCounter::operator[] (const std::string &symbol)
{ return map_[symbol]; }

const size_t &SequenceCounter::operator[] (const std::string &symbol) const
{
  if (map_.count(symbol) == 0)
    { throw NonExistentSymbol(); }
  return map_.find(symbol)->second;
}

SequenceCounter::const_iterator SequenceCounter::begin(void) const
{ return map_.begin(); }

SequenceCounter::const_iterator SequenceCounter::end(void) const
{ return map_.end(); }

size_t SequenceCounter::count(const std::string &symbol) const
{ return map_.count(symbol); }
