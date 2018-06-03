#ifndef IN_MEMORY_USER_REPOSITORY_H
#define	IN_MEMORY_USER_REPOSITORY_H

#include <algorithm>
#include <vector>
#include "userauth/User.h"
#include "userauth/UserRepository.h"

namespace userauth
{
  struct InMemoryUserRepository : public UserRepository
  {
    InMemoryUserRepository(std::vector<User>& _users)
      : users(_users)
    {}

    User ofUsername(const std::string& username) const override;
    void save(const User& user) override;

    private:
    auto findByUsername(const std::string& username) const;
    std::vector<User>& users;
  };
}

#endif
