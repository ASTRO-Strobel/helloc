#include "doctest/doctest.h"

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

TEST_CASE("Test the filter") {
    FilterTestFixture filter_test_fixture = FilterTestFixture();
    filter_test_fixture.set_up();

    SUBCASE("get_average_should_return_zero_on_empty_filter") {
        CHECK(0 == filter_get_average());
    }   

    SUBCASE("addFirstFilterValAddsVal") {
        filter_add(42);
        CHECK(42 == my_filter[readIdx]);
    }

    SUBCASE("addFirstReturnsCorrectAverage") {
        filter_add(42);
        CHECK(42 ==filter_get_average());
    }


    SUBCASE("addTwoValuesReturnsCorrectAverage") {
        filter_add(42);
        filter_add(40);
        CHECK(41 == filter_get_average());
    }

    SUBCASE("get_average_should_return_average_of_full_filter") {
        for(int i = 0; i < MAX_ITEMS; i++){
            filter_add(i);
        }
        CHECK((0+1+2+3+4+5+6)/MAX_ITEMS == filter_get_average());
    }

    SUBCASE("get_average_should_return_average_of_wrapped_filter") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        CHECK((1+2+3+4+5+6+7)/MAX_ITEMS == filter_get_average());
    }

/// ....test buffer operations...


    SUBCASE("addFirstFilterValIncsWriteIdx") {
        filter_add(42);
        CHECK(writeIdx == 1);
        CHECK(1 == filter_len());
    }

    SUBCASE("addFilterValWrapsWriteIdx") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        CHECK(0 == writeIdx);
    }

    SUBCASE("addFilterValUpdatesReadIndex") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        CHECK(readIdx == 1);
        CHECK(MAX_ITEMS == filter_len());
    }

    SUBCASE("addFilterValWrapsReadIndex") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        for(int i = 0; i < BUFFER_SIZE-1; i++){
            filter_add(i);
        }
        CHECK(readIdx == 0);
        CHECK(MAX_ITEMS == filter_len());
    }

    SUBCASE("addFilterValGivesCorrectLen") {
        for(int i = 0; i < BUFFER_SIZE; i++){
            filter_add(i);
        }
        CHECK(readIdx == 1);
        CHECK(MAX_ITEMS == filter_len());
    }
}
