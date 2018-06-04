# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES
	main.cpp
  # user-validity-test.cpp
  user-password-validation-test.cpp
  login-test.cpp
  login-rehash-test.cpp
	)

ADD_EXECUTABLE(tests ${TEST_SOURCES})

target_include_directories(tests
	PUBLIC
  ${LIBSODIUM_INCLUDE_DIRS}
	)

target_link_libraries(tests Catch userauth ${LIBSODIUM_BINARY_FILE})

enable_testing()
