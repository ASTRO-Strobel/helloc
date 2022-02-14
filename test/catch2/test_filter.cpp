#include <catch2/catch.hpp>

#include "test_filter.h"
extern "C" {
    // we need to "mock" myapp_do_dangerous_io, so we declare a special
    // implementation for the test here (the original is excluded via
    // the preprocessor define "TESTING")
    int fake_register;
    int myapp_do_dangerous_io() {
        return fake_register;
    }
}


FilterTestFixture filter_test_fixture1 = FilterTestFixture();
TEST_CASE("Test the filter1", "[filter]") {
    filter_test_fixture1.set_up();

    SECTION("get_average_should_return_zero_on_empty_filter") {
        REQUIRE(0 == filter_get_average());
    }   

    SECTION("addFirstFilterValAddsVal") {
        filter_add(42);
        REQUIRE(42 == my_filter[readIdx]);
    }
}
    

FilterTestFixture filter_test_fixture2 = FilterTestFixture();
TEST_CASE("Test the filter2", "[filter]") {
    filter_test_fixture2.set_up();
    SECTION("addFirstReturnsCorrectAverage") {
        filter_add(42);
        REQUIRE(42 ==filter_get_average());
    }


    SECTION("addTwoValuesReturnsCorrectAverage") {
        filter_add(42);
        filter_add(40);
        REQUIRE(41 == filter_get_average());
    }

    SECTION("get_average_should_return_average_of_full_filter") {
        for(int i = 0; i < MAX_ITEMS; i++){
            filter_add(i);
        }
        REQUIRE((0+1+2+3+4+5+6)/MAX_ITEMS == filter_get_average());
    }

    SECTION("get_average_should_return_average_of_wrapped_filter") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        REQUIRE((1+2+3+4+5+6+7)/MAX_ITEMS == filter_get_average());
    }

/// ....test buffer operations...


    SECTION("addFirstFilterValIncsWriteIdx") {
        filter_add(42);
        REQUIRE(writeIdx == 1);
        REQUIRE(1 == filter_len());
    }

    SECTION("addFilterValWrapsWriteIdx") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        REQUIRE(0 == writeIdx);
    }

    SECTION("addFilterValUpdatesReadIndex") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        REQUIRE(readIdx == 1);
        REQUIRE(MAX_ITEMS == filter_len());
    }

    SECTION("addFilterValWrapsReadIndex") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        for(int i = 0; i < BUFFER_SIZE-1; i++){
            filter_add(i);
        }
        REQUIRE(readIdx == 0);
        REQUIRE(MAX_ITEMS == filter_len());
    }

    SECTION("addFilterValGivesCorrectLen") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        REQUIRE(readIdx == 1);
        REQUIRE(MAX_ITEMS == filter_len());
    }
}
