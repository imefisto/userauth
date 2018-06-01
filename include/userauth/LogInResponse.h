#ifndef LOGINRESPONSE_H
#define	LOGINRESPONSE_H

#include "userauth/User.h"

namespace userauth {

  struct LogInResponse
  {
    User user;
    bool success;
  };

}
#endif
