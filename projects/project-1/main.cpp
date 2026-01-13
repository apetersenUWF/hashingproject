#include "tokenizer.hpp"
#include "rand.hpp"
#include <iostream>
int main() {
  /*Tokenizer test;
  test.load();
  test.test();
  return 0;*/
  for (int i = 0; i < 100; i++) std::cout << generateRandomAlphaStr(9) << std::endl;
  return 0;
}
//g++ -o run main.cpp tokenizer.cpp
//g++ -o run main.cpp rand.cpp