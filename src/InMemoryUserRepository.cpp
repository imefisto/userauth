#include "userauth/InMemoryUserRepository.h"

namespace userauth 
{
  auto InMemoryUserRepository::findByUsername(const std::string& username) const
  {
    return find_if(
        users.begin(), 
        users.end(), 
        [&username](const User& aUser) { return aUser.getUsername() == username; }
        );
  }

  User InMemoryUserRepository::ofUsername(const std::string& username) const
  {
    auto it = findByUsername(username);
    return it != users.end() ? *it : User();
  }

  void InMemoryUserRepository::save(const User& user)
  {
    auto it = findByUsername(user.getUsername());
    (*it) = user;
  }
}
