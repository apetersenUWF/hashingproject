#ifndef CHAIN_HPP
#define CHAIN_HPP
#include <string>
class Chain{
  Chain* next;
  std::pair<std::string, std::string> data;
  public:
  Chain(): next(nullptr) {}
  Chain(std::pair<std::string, std::string> data, Chain* next = nullptr) {
    this->data = data;
    this->next = next;
  }
  void setNext(Chain* node) {next = node;}
  Chain* getNext() const {return next;}
  std::pair<std::string, std::string> getData() const {return data;}
};
#endif