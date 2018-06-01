#include "catch2/catch.hpp"
#include "userauth/User.h"
#include "userauth/InMemoryUserRepository.h"
#include "userauth/LogIn.h"

using namespace std;

SCENARIO( "User gets identified", "[LogInUseCase]" ) {

  GIVEN("A repository with users") {

    const auto validUsername = "some-username";
    const auto validPassword = "123";
    auto user1 = userauth::User{"u1", validUsername};
    user1.setPassword(validPassword);

    vector<userauth::User> users = { user1, userauth::User{"u2", "another username"} };
    userauth::InMemoryUserRepository userRepository(users);
    userauth::LogIn logInUseCase{userRepository};

    WHEN("Some inexistent username and some password are passed to the use case") {
      auto response = logInUseCase.tryToIdentify("some-wrong-username", validPassword);

      THEN("An unsuccessful response and an invalid user should be returned") {
        REQUIRE(!response.success);
        REQUIRE(!response.user.isValid());
      }
    }

    WHEN("Some correct username and correct password are passed to the use case") {
      auto response = logInUseCase.tryToIdentify(validUsername, validPassword);

      THEN("A successful response with a validuser should be returned") {
        REQUIRE(response.success);
        REQUIRE(response.user.isValid());
      }
    }

    WHEN("Some existing username and incorrect password are passed to the use case") {
      auto response = logInUseCase.tryToIdentify(validUsername, "some-wrong-password");

      THEN("An unsuccessful response with valid user should be returned") {
        REQUIRE(!response.success);
        REQUIRE(response.user.isValid());
      }
    }
  }
}
