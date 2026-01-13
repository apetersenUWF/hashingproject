#include "rand.hpp"
#include <random>
#include <string>
std::string generateRandomAlphaStr(const int length) {//this function generates a randiom string 
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
std::string viginere(const std::string& input, const std::string& key) {
  std::string output;
  output.resize(input.size());//output will have same size as input
  for (int i = 0; i < input.size(); i++) {
    int alphabetOffset = key.at(i%key.size()) - 'a';//find alphabet offset from key position i
    int inputPos = (input.at(i) - 'a');
    char encryptedChar = ((inputPos + alphabetOffset) % 26) + 'a';//encrypt the character
    output.at(i) = encryptedChar;//put that encrypted character in the output
  }
  return output;
}
