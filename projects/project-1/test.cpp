#include "test.hpp"
#include <iostream>

int Test::testHashTable(HashTable hashtable) {
  std::pair<std::string, std::string> testPairs[100];
  for (int i = 0; i < 100; i++) {
    std::string user = generateRandomCharStr(12);
    std::string PW = generateRandomCharStr(9);
    std::pair<std::string, std::string> curr;
    curr.first = user;
    curr.second = PW;
    testPairs[i] = curr;
    hashtable.insert(curr);
  }
  for (int i = 0; i < 100; i++) {
    if (hashtable.lookup(testPairs[i].first) == -1) return -1;
    std::string randomTest = generateRandomCharStr(10);
    if (hashtable.lookup(randomTest) != -1) return -2;
  }
  std::cout << "Pass Hash Table tests 1 and 2" << std::endl;
  for (int i = 0; i < 100; i++) {
    if (!hashtable.remove(testPairs[i].first)) return -3;
    std::string randomTest = generateRandomCharStr(15);
    if (hashtable.remove(randomTest)) return -4;
  }
  std::cout << "Pass Hash Table tests 1 and 2" << std::endl;
  return 1;
}