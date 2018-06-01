ADD_LIBRARY(userauth
  User.cpp
  InMemoryUserRepository.cpp
  LogIn.cpp
)

target_include_directories(userauth
        PUBLIC
        ${USERAUTH_INCLUDE_DIRS}
        )
