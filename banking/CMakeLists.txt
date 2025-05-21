cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)

add_library(banking
    Account.cpp
    Transaction.cpp
)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)
    
    file(GLOB BANKING_TEST_SOURCES tests/*.cpp)
    add_executable(banking_tests ${BANKING_TEST_SOURCES})
    target_link_libraries(banking_tests banking gtest gmock_main)
    add_test(NAME banking_tests COMMAND banking_tests)
endif()
