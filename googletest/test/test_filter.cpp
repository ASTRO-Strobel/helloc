#include "gtest/gtest.h"

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


TEST_F(FilterTestSuite, get_average_should_return_zero_on_empty_filter) {
    ASSERT_EQ(0, filter_get_average());
}

TEST_F(FilterTestSuite, addFirstFilterValAddsVal) {
    filter_add(42);
    ASSERT_EQ(42, my_filter[readIdx]);
}

TEST_F(FilterTestSuite, addFirstReturnsCorrectAverage) {
    filter_add(42);
    ASSERT_EQ(42, filter_get_average());
}


TEST_F(FilterTestSuite, addTwoValuesReturnsCorrectAverage) {
    filter_add(42);
    filter_add(40);
    ASSERT_EQ(41, filter_get_average());
}

TEST_F(FilterTestSuite, get_average_should_return_average_of_full_filter) {
    for(int i = 0; i < MAX_ITEMS; i++){
        filter_add(i);
    }
    ASSERT_EQ((0+1+2+3+4+5+6)/MAX_ITEMS, filter_get_average());
}

TEST_F(FilterTestSuite, get_average_should_return_average_of_wrapped_filter) {
    for(int i = 0; i < BUFFER_SIZE; i++){
        filter_add(i);
    }
    ASSERT_EQ((1+2+3+4+5+6+7)/MAX_ITEMS, filter_get_average());
}

/// ....test buffer operations...


TEST_F(FilterTestSuite, addFirstFilterValIncsWriteIdx) {
    filter_add(42);
    ASSERT_EQ(writeIdx, 1);
    ASSERT_EQ(1,filter_len());
}

TEST_F(FilterTestSuite, addFilterValWrapsWriteIdx) {
    for(int i = 0; i < BUFFER_SIZE; i++){
        filter_add(i);
    }
    ASSERT_EQ(0, writeIdx);
}

TEST_F(FilterTestSuite, addFilterValUpdatesReadIndex) {
    for(int i = 0; i < BUFFER_SIZE; i++){
        filter_add(i);
    }
    ASSERT_EQ(readIdx, 1);
    ASSERT_EQ(MAX_ITEMS, filter_len());
}

TEST_F(FilterTestSuite, addFilterValWrapsReadIndex) {
    for(int i = 0; i < BUFFER_SIZE; i++){
        filter_add(i);
    }
    for(int i = 0; i < BUFFER_SIZE-1; i++){
        filter_add(i);
    }
    ASSERT_EQ(readIdx, 0);
    ASSERT_EQ(MAX_ITEMS, filter_len());
}

TEST_F(FilterTestSuite, addFilterValGivesCorrectLen) {
    for(int i = 0; i < BUFFER_SIZE; i++){
        filter_add(i);
    }
    ASSERT_EQ(readIdx, 1);
    ASSERT_EQ(MAX_ITEMS, filter_len());
}
