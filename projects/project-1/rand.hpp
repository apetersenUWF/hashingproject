#ifndef RAND_HPP
#define RAND_HPP
#include <string>
const int passwordLength = 9;// pw length of 9 for this project
const std::string KEY = "fortnight";
std::string generateRandomAlphaStr(const int length);//generates a random string of alphanumeric characters of length length
std::string viginere(const std::string& input, const std::string& key = KEY); //performs the vigenere ciphere using a random key
#endif