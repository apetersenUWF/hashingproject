#include "tokenizer.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Tokenizer::Tokenizer() {//default constructor, makes a tokenizer class with capacity of 10000 users
  capacity = 10000;
  size = 0;
  users = new User[capacity];
}
Tokenizer::~Tokenizer() {delete [] users;}
void Tokenizer::reAllocate() {
  capacity *= 2;
  User* newTable = new User[capacity*2]; //when array is full create a new array with twice the capacity
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
    users[size].setUser(userName);//set the username in the table
    size++;
    getline(inFS, throwAway);//get and trash the rest of the line
  }
  inFS.close();
  return true;
}

void Tokenizer::test() {
  for (int i = 0; i < size; i++) {
    std::string user = users[i].getUser();
    cout << user << endl;
  }
  cout << size << endl;
}