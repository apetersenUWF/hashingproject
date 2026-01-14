#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <vector>
#include "chain.hpp"
const int HASHTABLECAPACITY = 10007;

class HashTable{
  int capacity;
  int size;
  std::vector<Chain*> buckets;
  int hash(const std::string key) const;
  public:
  HashTable();
  HashTable(int capacity);
  ~HashTable();
  void insert(std::pair<std::string, std::string> data);
  int lookup(std::string user);
  bool remove(std::string user);
};

#endif