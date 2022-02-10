add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

set(TESTNAME test_myapp)
set(SOURCES ${PROJECT_SOURCE_DIR}/src/)

include_directories("${SOURCES}")

add_executable(${TESTNAME} helloc_testsuite.cpp)
target_compile_options(${TESTNAME} PRIVATE -Wall -Wextra -Werror)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
