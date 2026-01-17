#include "test.hpp"
#include <set>
#include <iostream>
#include <stdio.h>

Test::Test() {
  hashtable = new HashTable;
  tokenizer = new Tokenizer;
}

Test::~Test() {
  delete hashtable;
  delete tokenizer;
}

void Test::comparisonTest(){
  const std::string filename = ENCRYPTED_OUTPUT_FILE;//this file has the user and pw info
  tokenizer = new Tokenizer;
  tokenizer->load();//load the data files
  std::vector<std::pair<std::string, std::string>> testPairs = tokenizer->fetchTestPairs();//retrieve some names and raw PWs from the files for testing
  std::vector<std::pair<std::string, std::string>> modifiedTestPairs = testPairs;//duplicate the test pairs
  for (size_t i = 0; i < modifiedTestPairs.size(); i++) modifiedTestPairs.at(i).second.at(0)+=1;//change the first letter of each password
  hashtable = new HashTable(filename);//creates a hash table with information from the provided file
  const std::string HEADER1 = "USERID";
  const std::string HEADER2 = "Password(raw->enc)";
  const std::string HEADER3 = "Password(mod->enc)";
  const std::string HEADER4 = "Password(table)";
  const std::string HEADER5 = "Password(raw)";
  const std::string HEADER6 = "Password(raw->mod)";
  const std::string HEADER7 = "Result";
  std::cout << "LEGAL:\n\n";
  printf("%-12s%-20s%-20s%-20s%-10s\n", HEADER1.c_str(), HEADER5.c_str(), HEADER2.c_str(), HEADER4.c_str(), HEADER7.c_str());
  for (size_t i = 0; i < testPairs.size(); i++) {
    std::string user = testPairs.at(i).first;//gets a name from the test pairs
    std::string rawPW = testPairs.at(i).second;//gets the raw PW from the test pairs
    std::string cipheredPW = vigenere(rawPW);//performs the vigenere cipher on the raw PW
    std::string hashTablePW = hashtable->lookup(user);//gets the encrypted PW from the hash table
    std::string result = "mismatch";
    if (cipheredPW == hashTablePW) result = "match";//compares both ways of getting the password
    printf("%-12s%-20s%-20s%-20s%-10s\n", user.c_str(), rawPW.c_str(), cipheredPW.c_str(), hashTablePW.c_str(), result.c_str());
  }
  std::cout << "\nILLEGAL:\n\n";
  printf("%-12s%-20s%-20s%-20s%-10s\n", HEADER1.c_str(), HEADER6.c_str(), HEADER3.c_str(), HEADER4.c_str(), HEADER7.c_str());
  for (size_t i = 0; i < modifiedTestPairs.size(); i++) {
    std::string user = modifiedTestPairs.at(i).first;//gets the name from the test pairs
    std::string modifiedPW = modifiedTestPairs.at(i).second;//gets the modified PW from the test pairs
    std::string cipheredModPW = vigenere(modifiedPW);//performs the vigenere cipher on the modified PW
    std::string hashTablePW = hashtable->lookup(user);//gets the actual PW from the hash table
    std::string result = "match";
    if (cipheredModPW != hashTablePW) result = "mismatch";//compares the modified password to the one in the hash table
    printf("%-12s%-20s%-20s%-20s%-10s\n", user.c_str(), modifiedPW.c_str(), cipheredModPW.c_str(), hashTablePW.c_str(), result.c_str());
  }
}

void Test::runTestCases() {
  std::cout << "Results of rand.hpp tests: " << std::endl;
  std::cout << testRand() << std::endl;
  std::cout << "Results of tokenizer tests: " << std::endl;
  std::cout << testTokenizer() << std::endl;
  std::cout << "Results of hash table tests: " << std::endl;
  std::cout << testHashTable() << std::endl;
  delete hashtable;
  delete tokenizer;
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
    if (hashtable->lookup(testPairs[i].first) == "") return -1;//make sure the names are in the table
    std::string randomTest = generateRandomCharStr(10);
    if (hashtable->lookup(randomTest) != "") return -2;//make sure random name isnt found
  }
  std::cout << "Pass Hash Table tests 1 and 2" << std::endl;
  for (int i = 0; i < 100; i++) {
    if (!hashtable->remove(testPairs[i].first)) return -3;//try to remove each of the pairs
    if (hashtable->lookup(testPairs[i].first) != "") return -4;//make sure they are not in the table
    std::string randomTest = generateRandomCharStr(15);
    if (hashtable->remove(randomTest)) return -5;//tests removing an id that doesnt exist
  }
  std::cout << "Pass Hash Table tests 3 4 and 5" << std::endl;
  return 1;
}

int Test::testRand() {
  std::string testNames[500];
  std::set<std::string> uniqueNames;
  for (size_t j = 9; j <= 15; j+= 3) {//tests for randomstr length of 9, 12, and 15
    for (size_t i = 0; i < 500; i++) {//generates 500 names and checks if they are all unique
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
  std::cout << "Pass tokenizer test" << std::endl;
  return 1;
}

