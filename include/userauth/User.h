#ifndef USER_H
#define	USER_H

#include <string>

namespace userauth {

  struct User
  {
    User(std::string _id, std::string _username)
      : User{_id, _username, ""}
    {}

    User(std::string _id, std::string _username, std::string _passwordHash)
      : id{_id}, username{_username}, passwordHash{_passwordHash}
    {}

    std::string getUsername() const;
    std::string getPasswordHash() const;
    void setPassword(const std::string& password);
    bool validatePassword(const std::string& password) const;
    bool passwordNeedsRehash() const;

    private:
    std::string id;
    std::string username;
    std::string passwordHash;
  };

}

#endif
