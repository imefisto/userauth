#include <sodium.h>
#include "catch2/catch.hpp"
#include "userauth/User.h"

SCENARIO("Password validation", "[User]") {

  GIVEN("A user instantiated with password hash") {

    auto hash = "some-hash";
    auto user = userauth::User{"some-id", "some-username", hash};

    WHEN("The hash is used as password") {

      auto result = user.validatePassword(hash);

      THEN("A failed validation is expected") {
        REQUIRE(user.getPasswordHash() == hash);
        REQUIRE(!result);
      }
    }
  }

  GIVEN("A user with a hash created from password") {

    auto password = "some-password";
    auto user = userauth::User{"some-id", "some-username"};
    user.setPassword(password);

    WHEN("The password is validated") {

      auto result = user.validatePassword(password);

      THEN("A successful validation is expected and the password does not match with the hash") {
        REQUIRE(result);
        REQUIRE(user.getPasswordHash() != password);
      }
    }
  }

  GIVEN("A user instantiated with argon2 hash") {
    std::string password = "some-password";
    char hashedPassword[crypto_pwhash_STRBYTES];

    auto hashSuccess = crypto_pwhash_str(
        hashedPassword, 
        password.c_str(), 
        password.size(),
        crypto_pwhash_OPSLIMIT_INTERACTIVE, 
        crypto_pwhash_MEMLIMIT_INTERACTIVE);

    auto user = userauth::User{"some-id", "some-username", hashedPassword};

    WHEN("The password is validated") {

      auto result = user.validatePassword(password);

      THEN("A successful validation is expected and the hash is the same as generated") {
        REQUIRE(result);
        REQUIRE(user.getPasswordHash() == hashedPassword);
      }
    }
  }

  GIVEN("A user instantiated with argon2 with a hash with a minor memlimit and opslimit") {
    std::string password = "some-password";
    char hashedPassword[crypto_pwhash_STRBYTES];

    auto hashSuccess = crypto_pwhash_str(
        hashedPassword, 
        password.c_str(), 
        password.size(),
        crypto_pwhash_OPSLIMIT_MIN, 
        crypto_pwhash_MEMLIMIT_MIN);

    auto user = userauth::User{"some-id", "some-username", hashedPassword};
    WHEN("The hash is verified to determined if it needs rehash") {

      auto needsRehash = user.passwordNeedsRehash();

      THEN("The result should indicate that it needs rehash") {
        REQUIRE(needsRehash);
      }
    }
  }
}
