cmake_minimum_required(VERSION 3.10)

project(helloc VERSION 1.0
               DESCRIPTION "googletest / C example"
               LANGUAGES C CXX)

add_subdirectory(src)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()
