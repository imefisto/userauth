#include "userauth/User.h"

std::string userauth::User::getUsername() const
{
  return username;
}

std::string userauth::User::getPasswordHash() const
{
  return passwordHash;
}

void userauth::User::setPassword(const std::string& password)
{
  char hashedPassword[crypto_pwhash_STRBYTES];

  if(!crypto_pwhash_str(
      hashedPassword, 
      password.c_str(), 
      password.size(),
      crypto_pwhash_OPSLIMIT_INTERACTIVE, 
      crypto_pwhash_MEMLIMIT_INTERACTIVE)) {
    // out of memory
  }

  passwordHash = hashedPassword;
}

bool userauth::User::validatePassword(const std::string& password) const
{
  return 0 == crypto_pwhash_str_verify(
      passwordHash.c_str(), 
      password.c_str(), 
      password.size()
      );  
}

bool userauth::User::passwordNeedsRehash() const
{
  return 1 == crypto_pwhash_str_needs_rehash(passwordHash.c_str(),
      crypto_pwhash_OPSLIMIT_INTERACTIVE, 
      crypto_pwhash_MEMLIMIT_INTERACTIVE
      );
}

bool userauth::User::isValid() const
{
  return valid;
}

