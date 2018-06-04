#ifndef LOGINRESPONSE_H
#define	LOGINRESPONSE_H

#include <optional>
#include "userauth/User.h"

namespace userauth {

  struct LogInResponse
  {
    std::optional<User> user;
    bool success;
  };

}
#endif
