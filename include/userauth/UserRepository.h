#ifndef USER_REPOSITORY_H
#define	USER_REPOSITORY_H

#include <optional>
#include "userauth/User.h"

namespace userauth
{

  struct UserRepository
  {
    virtual std::optional<User> ofUsername(const std::string& username) const = 0;
    virtual void save(const User& user) = 0;
  };

}

#endif
