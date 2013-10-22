#include <sstream>

#include "WeightMap.h"

#define MAX_BUFFER 500000

WeightMap::WeightMap(void):
  penalty(0.0)
{}

WeightMap::WeightMap(const WeightMap &another):
  penalty(another.penalty),
  weight_map(another.weight_map)
{}

double &WeightMap::operator[] (const std::string &key)
{
  if (weight_map.find(key) == weight_map.end())
    { weight_map[key] = penalty; }
  return weight_map[key];
}

void WeightMap::set_penalty(double penalty_weight)
{ penalty = penalty_weight; }

void WeightMap::store(std::ostream &out)
{
  out << "WeightMap begin" << std::endl;
  out << penalty << std::endl;
  
  for (WeightMap_::const_iterator it = weight_map.begin();
       it != weight_map.end();
       ++it)
    { out << it->first << "\t" << it->second << std::endl; }

  out << "WeightMap end" << std::endl;
}

WeightMap::WeightMap(std::istream &in)
{
  if (not read_header(in))
    { throw SyntaxErrorInFile(1); }

  penalty = read_penalty(in);
  if (penalty == -1)
    { throw SyntaxErrorInFile(2); }

  size_t line_number = 2;
  WeightedString line("",0);
  while (line.second != -1)
    {
      weight_map[line.first] = line.second;
      line = read_line(in);
      ++line_number;
    }
  
  if (not is_end(line.first))
    { throw SyntaxErrorInFile(line_number); }
}

bool WeightMap::read_header(std::istream &in)
{
  char line[MAX_BUFFER];
  in.getline(line,MAX_BUFFER);
  if (std::string(line) == "WeightMap begin")
    { return true; }
  else
    { return false; }
}

double WeightMap::read_penalty(std::istream &in)
{
  char line[MAX_BUFFER];
  in.getline(line,MAX_BUFFER);
  std::istringstream str_in(line);
  double weight;
  str_in >> weight;
  if (str_in.fail())
    { weight = -1; }
  return weight;
}

WeightMap::WeightedString WeightMap::read_line(std::istream &in)
{
  char line[MAX_BUFFER];
  in.getline(line,MAX_BUFFER);
  std::string entry(line);

  size_t pos = entry.find('\t');

  if (pos == std::string::npos)
    { return WeightedString(entry,-1); }
  else 
    {
      std::string key = entry.substr(0,pos);
      std::string weight_string = entry.substr(pos+1);
      std::istringstream str_in(weight_string);
      double weight;
      str_in >> weight;
      if (str_in.fail())
	{ weight = -1; }
      return WeightedString(key,weight);
    }
}

bool WeightMap::is_end(std::string &line)
{ return line == "WeightMap end"; }

SyntaxErrorInFile::SyntaxErrorInFile(size_t line_number):
  line_number(line_number)
{}


#ifdef TESTING_WEIGHT_MAP
#include <cassert>
#include <cstdlib>
int main(void)
{
  WeightMap weight_map;

  weight_map["foo"] = 0;
  assert(weight_map["foo"] == 0);

  weight_map.set_penalty(1);
  assert(weight_map["foo"] == 0);
  assert(weight_map["bar"] == 1);
  
  std::ostringstream out;
  weight_map.store(out);

  std::string data = out.str();

  std::istringstream in(data);

  WeightMap weight_map_copy(in);
  assert(weight_map_copy["foo"] == 0);
  assert(weight_map_copy["bar"] == 1);
  assert(weight_map_copy["baz"] == 1);
}
#endif // TESTING_WEIGHT_MAP
