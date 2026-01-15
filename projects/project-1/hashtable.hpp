#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <vector>
#include "chain.hpp"
const int HASHTABLECAPACITY = 10007;//large prime number to avoid overfilling and for scrambling

class HashTable{
  int capacity;
  int size;
  std::vector<Chain*> buckets;
  int hash(const std::string key) const;
  public:
  HashTable();
  HashTable(int capacity);
  HashTable(const std::string& filename);
  ~HashTable();
  void insert(std::pair<std::string, std::string> data);
  std::string lookup(const std::string& user);
  bool remove(const std::string& user);
};

#endif