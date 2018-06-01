#ifndef LOGIN_H
#define	LOGIN_H

#include "userauth/UserRepository.h"
#include "userauth/LogInResponse.h"

using namespace std;

namespace userauth {

  struct LogIn
  {
    LogIn(UserRepository& userRepository)
      : userRepository(userRepository)
    {}

    LogInResponse tryToIdentify(string username, string password);

    private:

    // non assignable
    LogIn& operator = (const LogIn &);
    // non copyable
    LogIn(const LogIn &);

    UserRepository& userRepository;
  };

}

#endif
