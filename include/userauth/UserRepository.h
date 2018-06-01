#ifndef USER_REPOSITORY_H
#define	USER_REPOSITORY_H

#include "userauth/User.h"

namespace userauth
{

  struct UserRepository
  {
    virtual User ofUsername(std::string username) const = 0;
    virtual void save(User user) = 0;
  };

}

#endif
