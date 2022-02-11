add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

set(TESTNAME test_myapp)
set(SOURCES ${PROJECT_SOURCE_DIR}/src/)

include_directories("${SOURCES}")

add_executable(${TESTNAME} 
    ${SOURCES}/myapp.c 
    ${SOURCES}/facul.c 
    ${SOURCES}/filter.c 
    test_filter.cpp
    test_facul.cpp
    test_myapp.cpp
    )
target_compile_options(${TESTNAME} PRIVATE -Wall -Wextra -Werror -DTESTING --coverage)
target_link_libraries(${TESTNAME} gtest gmock gtest_main --coverage)
