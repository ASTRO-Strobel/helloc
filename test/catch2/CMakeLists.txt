find_package(Catch2 REQUIRED PATHS ${PROJECT_SOURCE_DIR}/install/catch2)

set(TESTNAME test_catch2)
set(SOURCES ${PROJECT_SOURCE_DIR}/src/)

include_directories(
    ${SOURCES}
)

add_executable(${TESTNAME} 
    ${SOURCES}/myapp.c 
    ${SOURCES}/facul.c 
    ${SOURCES}/filter.c 
    test_filter.cpp
    test_facul.cpp
    test_myapp.cpp
    )
target_compile_options(${TESTNAME} PRIVATE -Wall -Wextra -Werror -DTESTING --coverage)
target_link_libraries(${TESTNAME} PRIVATE Catch2::Catch2WithMain --coverage)
