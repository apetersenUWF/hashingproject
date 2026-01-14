#ifndef RAND_HPP
#define RAND_HPP
#include <string>

const int passwordLength = 9;//dictates the length of the random passwords
const std::string KEY = "fortnight";//key can be any length of lowercase characters

std::string generateRandomCharStr(const int length);//generates a random string of lowercase letters of length length
std::string viginere(const std::string& input, const std::string& key = KEY); //performs the vigenere ciphere using a 
                                                                              // key that can be any sequence of lowercase letters
#endif