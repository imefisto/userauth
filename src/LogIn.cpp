#include "userauth/LogIn.h"

userauth::LogInResponse userauth::LogIn::tryToIdentify(const string& username, const string& password)
{
  auto user = userRepository.ofUsername(username);

  if(!user) return {user, false};

  auto validationResult = user->validatePassword(password);

  if(validationResult && user->passwordNeedsRehash())
  {
    user->setPassword(password);
    userRepository.save(*user);
  }

  return {user, validationResult};
}
