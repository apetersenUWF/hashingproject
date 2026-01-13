#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "user.hpp"
class Tokenizer{
  int capacity;
  int size;
  User* users;
  bool generateRawData(std::string& filename);
  void reAllocate();
  public:
  Tokenizer();
  ~Tokenizer();
  bool load(std::string filename = "names.txt");
  void test();
};

#endif