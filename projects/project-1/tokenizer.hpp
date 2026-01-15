#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <string>
#include <vector>
const std::string NAME_FILE = "names.txt";//this file will contain the names used for the userID
const std::string RAW_OUTPUT_FILE = "rawdata.txt";//this is an intermediate file used to store randomly generated passwords for each user
const std::string ENCRYPTED_OUTPUT_FILE = "encrypteddata.txt";//this file will contain userIDs and ciphered passwords for each user
class Tokenizer{
  int capacity;
  int size;
  std::string* users;
  void reAllocate();
  bool generateRawData(std::string filename = RAW_OUTPUT_FILE);
  bool encryptData(std::string infile = RAW_OUTPUT_FILE, std::string outfile = ENCRYPTED_OUTPUT_FILE);
  public:
  Tokenizer();
  ~Tokenizer();
  bool load(std::string filename = NAME_FILE);
  std::vector<std::pair<std::string, std::string>> fetchTestPairs();
};

#endif