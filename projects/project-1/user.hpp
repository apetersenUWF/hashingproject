#ifndef USER_HPP
#define USER_HPP
#include <string>
class User{
  std::string username;
  std::string password;
  public:
  User(std::string username = "", std::string password = "") {
    this->username = username;
    this->password = password;
  }
  void setUser(std::string& user) {username = user;}
  void setPW(std::string& pw) {password = pw;}
  std::string getUser() {return username;}
  std::string getPW() {return password;}
};
#endif