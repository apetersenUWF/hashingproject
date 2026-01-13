#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "user.hpp"
class Tokenizer{
  int capacity;
  int size;
  std::string* users;
  void reAllocate();
  public:
  Tokenizer();
  ~Tokenizer();
  bool load(std::string filename = "names.txt");
  bool generateRawData(std::string filename = "rawdata.txt");
  bool encryptData(std::string infile = "rawdata.txt", std::string outfile = "encrypteddata.txt");
  void test();
};

#endif