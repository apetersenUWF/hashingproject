#include "rand.hpp"
#include <random>
#include <string>
std::string generateRandomAlphaStr(int length) {//this function generates a randiom string 
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());//uses the mersene twister engine for fast random numbers
  std::uniform_int_distribution<> distr('a', 'z');//defines the range from ascii a to z
  std::string randomAlphaStr;
  for (int i = 0; i < length; i++) {
    int random_num = distr(generator);//generates a number
    randomAlphaStr.push_back(random_num); //adds that character to the string
  }
  return randomAlphaStr;
}
