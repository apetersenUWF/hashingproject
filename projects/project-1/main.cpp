#include "tokenizer.hpp"
#include "hashtable.hpp"
#include "rand.hpp"
#include <iostream>
int testHashTable(HashTable hashtable) {
  std::pair<std::string, std::string> testPairs[100];
  for (int i = 0; i < 100; i++) {
    std::string user = generateRandomAlphaStr(12);
    std::string PW = generateRandomAlphaStr(9);
    std::pair<std::string, std::string> curr;
    curr.first = user;
    curr.second = PW;
    testPairs[i] = curr;
    hashtable.insert(curr);
  }
  for (int i = 0; i < 100; i++) {
    if (hashtable.lookup(testPairs[i].first) == -1) return -1;
    std::string randomTest = generateRandomAlphaStr(10);
    if (hashtable.lookup(randomTest) != -1) return -2;
  }
  for (int i = 0; i < 100; i++) {
    if (!hashtable.remove(testPairs[i].first)) return -3;
    std::string randomTest = generateRandomAlphaStr(15);
    if (hashtable.remove(randomTest)) return -4;
  }
  std::cout << "Success!" << std::endl;
  return 1;
}
int main() {
  //Tokenizer test;
  HashTable hashtable;
  std::cout << testHashTable(hashtable);
  //test.test();
  return 0;
  //for (int i = 0; i < 100; i++) std::cout << generateRandomAlphaStr(9) << std::endl;
}
//g++ -o run main.cpp rand.cpp tokenizer.cpp
//g++ -o run main.cpp rand.cpp hashtable.cpp

