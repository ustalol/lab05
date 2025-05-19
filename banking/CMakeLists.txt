cmake_minimum_required(VERSION 3.14)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(banking
    Account.cpp
    Transaction.cpp
)


target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(banking_tests
    tests/test_account.cpp
    tests/test_transaction.cpp
    tests/mocks/mock_account.h
)

target_include_directories(banking_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(banking_tests
    banking
    gtest_main
    gmock
)

add_test(NAME banking_tests COMMAND banking_tests)
