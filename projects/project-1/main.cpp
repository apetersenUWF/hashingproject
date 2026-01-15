#include "test.hpp"


int main() {
  Test testobj;
  testobj.runTestCases();
  testobj.visualTest();
  return 0;
}
//g++ -o run main.cpp rand.cpp tokenizer.cpp
//g++ -o run main.cpp rand.cpp hashtable.cpp test.cpp tokenizer.cpp

