#include "test.hpp"
#include <set>
#include <iostream>

void Test::runTestCases() {
  std::cout << "Results of rand.hpp tests: " << std::endl;
  std::cout << testRand() << std::endl;
  std::cout << "Results of tokenizer tests: " << std::endl;
  std::cout << testTokenizer() << std::endl;
  std::cout << "Results of hash table tests: " << std::endl;
  std::cout << testHashTable() << std::endl;
}
int Test::testHashTable() {
  std::pair<std::string, std::string> testPairs[100];
  for (int i = 0; i < 100; i++) {//generates 100 random user and PW pairs and inserts them into the table
    std::string user = generateRandomCharStr(12);
    std::string PW = generateRandomCharStr(9);
    std::pair<std::string, std::string> curr;
    curr.first = user;
    curr.second = PW;
    testPairs[i] = curr;
    hashtable->insert(curr);
  }
  for (int i = 0; i < 100; i++) {//tests lookup feature
    if (hashtable->lookup(testPairs[i].first) == -1) return -1;//make sure the names are in the table
    std::string randomTest = generateRandomCharStr(10);
    if (hashtable->lookup(randomTest) != -1) return -2;//make sure random name isnt found
  }
  std::cout << "Pass Hash Table tests 1 and 2" << std::endl;
  for (int i = 0; i < 100; i++) {
    if (!hashtable->remove(testPairs[i].first)) return -3;//try to remove each of the pairs
    if (hashtable->lookup(testPairs[i].first) != -1) return -4;//make sure they are not in the table
    std::string randomTest = generateRandomCharStr(15);
    if (hashtable->remove(randomTest)) return -5;//tests removing an id that doesnt exist
  }
  std::cout << "Pass Hash Table tests 3 4 and 5" << std::endl;
  return 1;
}
int Test::testRand() {
  std::string testNames[500];
  std::set<std::string> uniqueNames;
  for (int j = 9; j <= 15; j+= 3) {//tests for randomstr length of 9, 12, and 15
    for (int i = 0; i < 500; i++) {//generates 500 names and checks if they are all unique
      testNames[i] = generateRandomCharStr(j);
      if (testNames[i].size() != j) return -1;
      auto result = uniqueNames.insert(testNames[i]);//ignores the low possibility of duplicates, run multiple tests
      if (!result.second) return -2;//if the insert failed due to there being a duplicate
    }
    uniqueNames.clear();
  }
  std::cout << "Pass random string generator tests" << std::endl;
  std::string cipheredNames[500];
  std::cout << "Encrypting on the key: " << KEY << std::endl;
  for (int i = 0; i < 500; i++) {
    cipheredNames[i] = vigenere(testNames[i]);
    if ((i % 100) == 0) std::cout << testNames[i] << " " << cipheredNames[i] << std::endl;//test by visual inspection
    if (testNames[i] == cipheredNames[i]) return -3;//make sure the name was changed
    if (testNames[i].size() != cipheredNames[i].size()) return -4;//make sure the size did not change
  }
  std::cout << "Pass vigenere cipher tests" << std::endl;
  return 1;
}
int Test::testTokenizer() {//makes sure the file io doesnt fail, inspect generated files manually for formatting
  if (!tokenizer->load()) return -1;
  if (!tokenizer->generateRawData()) return -2;
  if (!tokenizer->encryptData()) return -3;
  std::cout << "Pass tokenizer tests" << std::endl;
  return 1;
}
Test::Test() {
  hashtable = new HashTable;
  tokenizer = new Tokenizer;
}
Test::~Test() {
  delete hashtable;
  delete tokenizer;
}