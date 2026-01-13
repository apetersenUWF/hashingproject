#include "tokenizer.hpp"
#include "rand.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Tokenizer::Tokenizer() {//default constructor, makes a tokenizer class with capacity of 10000 users
  capacity = 10000;
  size = 0;
  users = new std::string[capacity];
}
Tokenizer::~Tokenizer() {delete [] users;}
void Tokenizer::reAllocate() {
  capacity *= 2;
  std::string* newTable = new std::string[capacity*2]; //when array is full create a new array with twice the capacity
  for (int i = 0; i < size; i++) {
    newTable[i] = users[i];
  }
  delete [] users;
  users = newTable;
}
bool Tokenizer::load(std::string filename) {
  ifstream inFS;
  inFS.open(filename);
  if (!inFS.is_open()) return false;//if file wasnt opened return false
  std::string userName;
  std::string throwAway;
  while (getline(inFS, userName, ' ')) {//get the data line up to the first space which is where the username is
    if (size == capacity) reAllocate();//table is full, allocate more memory
    users[size] = userName;//set the username in the table
    size++;
    getline(inFS, throwAway);//get and trash the rest of the line
  }
  inFS.close();
  return true;
}

void Tokenizer::test() {
  bool a = load();
  bool b = generateRawData();
  bool c = encryptData();
  cout << size << endl;
  if (!a || !b || !c) cout << "error";
  else cout << "good";
}

  bool Tokenizer::generateRawData(std::string filename) {
    ofstream oFS(filename);//open the file
    if (!oFS.is_open()) return false; //if file open fails return false
      for (int i = 0; i < size; i++) {
        oFS << users[i] << "," << generateRandomAlphaStr(passwordLength) << endl; //put all users and pw in a file
      }
      oFS.close();
      return true;
  }
  bool Tokenizer::encryptData(std::string infile, std::string outfile) {
    ifstream inFS;
    inFS.open(infile);
    if (!inFS.is_open()) return false;
    ofstream oFS(outfile);
    if (!oFS.is_open()) return false;
    std::string key = generateRandomAlphaStr(passwordLength);//generate a random key to use for the viginere cipher
    std::string user;
    std::string rawPW;
    while (getline(inFS, user, ',')) {//while we can keep reading usernames from infile
      getline(inFS, rawPW);//also store the raw password
      std::string encryptedPW = viginere(rawPW, key);//encrypt the raw password using the viginere key
      oFS << user << "," << encryptedPW << endl;//put the username and encrypted PW in a new file
    }
    inFS.close();
    oFS.close();
    return true;
  }