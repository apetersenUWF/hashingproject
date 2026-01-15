#include "test.hpp"
#include <iostream>

int main() {
  Test testobj;
  testobj.runTestCases();
  return 0;
}
//g++ -o run main.cpp rand.cpp tokenizer.cpp
//g++ -o run main.cpp rand.cpp hashtable.cpp test.cpp tokenizer.cpp

