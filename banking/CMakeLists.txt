cmake_minimum_required(VERSION 3.10)
project(banking)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_library(banking
  Account.cpp
  Transaction.cpp
)

enable_testing()
add_executable(banking_tests
  tests/test_account.cpp
  tests/test_transaction.cpp
  tests/mocks/mock_account.h
  tests/mocks/mock_transaction.h
)

target_link_libraries(banking_tests
  banking
  gtest_main
  gmock
)

add_test(NAME banking_tests COMMAND banking_tests)
