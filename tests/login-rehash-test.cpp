#include <sodium.h>
#include "catch2/catch.hpp"
#include "userauth/User.h"
#include "userauth/InMemoryUserRepository.h"
#include "userauth/LogIn.h"

using namespace std;

SCENARIO( "User gets identified and its password rehashed", "[LogInUseCase]" ) {
  GIVEN("A repository with users with a user with a password that needs rehash") {

    const auto validUsername = "some-username";
    const std::string validPassword = "123";
    char poorHashedPassword[crypto_pwhash_STRBYTES];
    auto hashSuccess = crypto_pwhash_str(
        poorHashedPassword, 
        validPassword.c_str(), 
        validPassword.size(),
        crypto_pwhash_OPSLIMIT_MIN, 
        crypto_pwhash_MEMLIMIT_MIN);
    auto user1 = userauth::User{"u1", validUsername, poorHashedPassword};

    vector<userauth::User> users = { user1, userauth::User{"u2", "another username"} };
    userauth::InMemoryUserRepository userRepository(users);
    userauth::LogIn logInUseCase{userRepository};

    WHEN("The user is identified") {

      auto response = logInUseCase.tryToIdentify(validUsername, validPassword);

      THEN("The password has to be rehashed as part of the process and the changes must be saved") {
        REQUIRE(response.success);
        REQUIRE(response.user.getPasswordHash() != poorHashedPassword);
        REQUIRE(!response.user.passwordNeedsRehash());

        auto savedUser = userRepository.ofUsername(validUsername);
        REQUIRE(savedUser.getPasswordHash() != poorHashedPassword);
        REQUIRE(!savedUser.passwordNeedsRehash());
      }
    }
  }
};
