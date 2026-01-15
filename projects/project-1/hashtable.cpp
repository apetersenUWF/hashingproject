#include "hashtable.hpp"
#include <fstream>

int HashTable::hash(const std::string key) const{
  std::string hashCode;
  unsigned long long hashCodeVal = 0;
  for (int i = 0; i < key.size(); i++) {
    hashCodeVal = (hashCodeVal * 31) + key.at(i); //use the prime number 31 to scramble the value more
  }
  return hashCodeVal % capacity;
}

HashTable::HashTable(): capacity(HASHTABLECAPACITY), size(0), buckets(capacity) {}//uses prime 10007 as default capacity for scrambling

HashTable::HashTable(int capacity): capacity(capacity), size(0), buckets(capacity) {}

HashTable::HashTable(const std::string& filename) {
  std::ifstream inFS;
  capacity = HASHTABLECAPACITY;
  size = 0;
  buckets.resize(capacity);
  inFS.open(filename);
  if (!inFS.is_open()) return;
  std::string user, PW;
  while(getline(inFS, user, ',')) {
    getline(inFS, PW);
    std::pair<std::string, std::string> curr;
    curr.first = user;
    curr.second = PW;
    insert(curr);
    size++;
  }
}

HashTable::~HashTable() {
  for (int i = 0; i < capacity; i++) {
      Chain* currNode = buckets.at(i);
      while (currNode != nullptr) {
        Chain* nodeToDelete = currNode;
        currNode = currNode->getNext();
        delete nodeToDelete;
      }
    }
}

void HashTable::insert(std::pair<std::string, std::string> data) {
  int index = hash(data.first);//find the index
  Chain* curr = buckets.at(index);
  while (curr != nullptr) {//checks if the user already exists in this bucket
    if (curr->getData().first == data.first) return;//duplicates not allowed
    curr = curr->getNext();
  }
  Chain* node = new Chain(data);
  node->setNext(buckets.at(index));
  buckets.at(index) = node;//make this node the head
  size++;
  }
std::string HashTable::lookup(const std::string& user) {
  int index = hash(user);
  Chain* currNode = buckets.at(index);
  while (currNode != nullptr) {
    std::pair<std::string, std::string> data = currNode->getData();
    if (data.first == user) return data.second;
    currNode = currNode->getNext();
  }
  return "";
}
bool HashTable::remove(const std::string& user) {
  if (lookup(user) == "") return false; //user doesnt exist
  int index = hash(user);
  Chain* currNode = buckets.at(index);
  std::pair<std::string, std::string> data = currNode->getData();
  if (data.first == user) {//head node is the user
    buckets.at(index) = currNode->getNext();//assign the successor as the new head
    delete currNode;//delete the user
    size--;
    return true;
  }
while (currNode->getNext() != nullptr){
  data = currNode->getNext()->getData();//gets the data from the next node
  if (data.first == user) {//if this is the user we want to delete
    Chain* nextSuccessor = currNode->getNext()->getNext();//save the successor of the user we are deleting
    delete currNode->getNext();//delete the user
    currNode->setNext(nextSuccessor);//assign the successor to currNodes next node
    return true;
  }
  currNode = currNode->getNext();
}
return false;
}