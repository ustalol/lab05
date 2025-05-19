cmake_minimum_required(VERSION 3.14)
project(banking VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Enable code coverage" ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_library(banking
  Account.cpp
  Transaction.cpp
)

target_include_directories(banking PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BUILD_TESTS)
  enable_testing()

  add_executable(banking_tests
    tests/test_account.cpp
    tests/test_transaction.cpp
    tests/mocks/mock_account.h
  )

  target_include_directories(banking_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks
  )

  target_link_libraries(banking_tests
    banking
    gtest_main
    gmock
  )

  add_test(NAME banking_tests COMMAND banking_tests)

  if(BUILD_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(banking_tests PRIVATE
      --coverage
      -fprofile-arcs
      -ftest-coverage
    )
    target_link_options(banking_tests PRIVATE --coverage)
  endif()
endif()
