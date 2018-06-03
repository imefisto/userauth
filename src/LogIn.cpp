#include "userauth/LogIn.h"

userauth::LogInResponse userauth::LogIn::tryToIdentify(const string& username, const string& password)
{
  auto user = userRepository.ofUsername(username);

  if(!user.isValid()) return {user, false};
  
  auto result = user.validatePassword(password);

  if(result && user.passwordNeedsRehash())
  {
    user.setPassword(password);
    userRepository.save(user);
  }

  return {user, result};
}
