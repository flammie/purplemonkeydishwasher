#ifndef WEIGHT_MAP_H
#define WEIGHT_MAP_H

#include <map>
#include <string>
#include <iostream>

class WeightMap
{
 public:
  WeightMap(void);
  WeightMap(std::istream &in);
  WeightMap(const WeightMap &another);
  double &operator[] (const std::string &key);
  void set_penalty(double penalty);
  void store(std::ostream &out);
 protected:
  typedef std::map<std::string,double> WeightMap_;
  typedef std::pair<std::string,double> WeightedString;

  double penalty;
  WeightMap_ weight_map;

  bool read_header(std::istream &in);
  double read_penalty(std::istream &in);
  WeightedString read_line(std::istream &in);
  bool is_end(std::string &line);
};

struct SyntaxErrorInFile
{
  size_t line_number;
  SyntaxErrorInFile(size_t line_number);
};

#endif // WEIGHT_MAP_H
