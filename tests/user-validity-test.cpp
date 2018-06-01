#include "catch2/catch.hpp"
#include "userauth/User.h"

SCENARIO("User validity", "[User]") {
  GIVEN("A user") {
    WHEN("Instantiated without parameters") {
      auto user = userauth::User();

      THEN("It is not a valid user") {
        REQUIRE(!user.isValid());
      }
    }

    WHEN("Instantiated with empty password") {
      auto user = userauth::User{"some-id", "some-username"};
      THEN("It is a valid user") {
        REQUIRE(user.isValid());
      }
    }

    WHEN("Instantiated with a hash") {
      auto user = userauth::User{"some-id", "some-username", "some-hash"};
      THEN("It is a valid user") {
        REQUIRE(user.isValid());
      }
    }
  }
}
