#include "hashtable.hpp"

int HashTable::hash(const std::string key) const{
  std::string hashCode;
  unsigned long long hashCodeVal = 0;
  for (int i = 0; i < key.size(); i++) {
    hashCodeVal = (hashCodeVal * 31) + key.at(i); //use the prime number 31 to scramble the value more
  }
  return hashCodeVal % capacity;
}

HashTable::HashTable(): capacity(10000), size(0), buckets(capacity) {}
HashTable::HashTable(int capacity): capacity(capacity), size(0), buckets(capacity) {}
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
  if (lookup(data.first) != -1) return; //duplicate keys not allowed
  int index = hash(data.first);//find the index
  Chain* node = new Chain(data);
    node->setNext(buckets.at(index));
    buckets.at(index) = node;//make this node the head
  }
int HashTable::lookup(std::string user) {
  int index = hash(user);
  Chain* currNode = buckets.at(index);
  if (currNode == nullptr) return -1; //empty spot found, user doesnt exist
  while (currNode != nullptr) {
    std::pair<std::string, std::string> data = currNode->getData();
    if (data.first == user) return index;//check if username matches
    currNode = currNode->getNext();
  }
  return -1;
}
bool HashTable::remove(std::string user) {
  int index = lookup(user);
  if (index == -1) return false; //user doesnt exist
  Chain* currNode = buckets.at(index);
  std::pair<std::string, std::string> data = currNode->getData();
  if (data.first == user) {//head node is the user
    buckets.at(index) = currNode->getNext();//assign the successor as the new head
    delete currNode;//delete the user
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