#ifndef TEST_HPP
#define TEST_HPP
#include "rand.hpp"
#include "tokenizer.hpp"
#include "hashtable.hpp"
class Test{
  Tokenizer* tokenizer;
  HashTable* hashtable;
  int testHashTable();
  int testRand();
  int testTokenizer();
  public:
  Test();
  ~Test();
  void runTestCases();
  void visualTest();
};
#endif