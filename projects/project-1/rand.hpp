#ifndef RAND_HPP
#define RAND_HPP
#include <string>
const int passwordLength = 9;// pw length of 9 for this project
std::string generateRandomAlphaStr(const int length);//generates a random string of alphanumeric characters of length length
std::string viginere(std::string input, std::string key); //performs the vigenere ciphere using a random key
#endif