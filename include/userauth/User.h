#ifndef USER_H
#define	USER_H

#include <string>
#include <sodium.h>

namespace userauth {

  struct User
  {
    User()
      : valid{false}
    {}

    User(std::string _id, std::string _username)
      : User{_id, _username, ""}
    {}

    User(std::string _id, std::string _username, std::string _passwordHash)
      : id{_id}, username{_username}, passwordHash{_passwordHash}, valid{true}
    {}

    std::string getUsername() const;
    std::string getPasswordHash() const;
    void setPassword(std::string password);
    bool validatePassword(std::string password) const;
    bool passwordNeedsRehash() const;
    bool isValid() const;

    private:
    std::string id;
    std::string username;
    std::string passwordHash;
    bool valid;
  };

}

#endif
