set(CATCH_BUILD_STATIC_LIBRARY ON)
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/catch2 extern/catch2)

set(TESTNAME test_myapp)
set(SOURCES ${PROJECT_SOURCE_DIR}/src/)

include_directories(
    ${SOURCES}
    ${PROJECT_SOURCE_DIR}/extern/catch2/include
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
