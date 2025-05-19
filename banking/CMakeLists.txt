cmake_minimum_required(VERSION 3.10)
project(banking VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(banking
    Account.cpp
    Transaction.cpp
)

target_include_directories(banking PUBLIC .)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/googletest)
    
    add_executable(banking_tests
        tests/test_account.cpp
        tests/test_transaction.cpp
    )
    
    target_link_libraries(banking_tests
        banking
        gtest_main
    )
    
    add_test(NAME banking_tests COMMAND banking_tests)
endif()
