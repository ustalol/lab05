cmake_minimum_required(VERSION 3.14)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)

add_library(banking
    Account.cpp
    Transaction.cpp
)

if(BUILD_TESTS)
    include(FetchContent)
    
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(googletest)
    enable_testing()

    file(GLOB TEST_SOURCES tests/*.cpp tests/mocks/*.cpp)
    
    add_executable(banking_tests ${TEST_SOURCES})
    
    target_link_libraries(banking_tests
        banking
        gtest_main
        gmock_main
    )
    
    add_test(NAME banking_tests COMMAND banking_tests)
endif()
