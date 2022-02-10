#include "gtest/gtest.h"

// Hide main
#define TESTING

int fake_register;
int myapp_do_dangerous_io()
{
	return fake_register;
}
#include <myapp.c>

// test facul function
class FaculTest :
    public testing::TestWithParam<std::tuple<int, int>> {
};
TEST_P(FaculTest, test_facul) {
    int value = std::get<0>(GetParam());
    int expected = std::get<1>(GetParam());
    EXPECT_EQ(facul(value), expected);
}
INSTANTIATE_TEST_SUITE_P(
    FaculTestSuite,
    FaculTest,
    testing::Values(
        std::make_tuple(0, 1),
        std::make_tuple(1, 1),
        std::make_tuple(2, 2),
        std::make_tuple(3, 6),
        std::make_tuple(4, 24)
    )
);


// test filter
class MyAppTestSuite : public testing::Test
{
	void SetUp(){
		memset(&my_filter, 0, sizeof(my_filter));
		readIdx = 0;
		writeIdx = 0;
	}

	void TearDown(){}
};

TEST_F(MyAppTestSuite, myapp_task_should_return_correct_delay_for_one_element) {
	fake_register = 10;
    EXPECT_EQ(10, myapp_task());
}

TEST_F(MyAppTestSuite, myapp_task_should_return_correct_delay_for_two_elements) {
	fake_register = 10;
	myapp_task();
	fake_register = 20;
    EXPECT_EQ(15, myapp_task());
}

TEST_F(MyAppTestSuite, get_average_should_return_zero_on_empty_filter) {
	ASSERT_EQ(0, myapp_get_average());
}

TEST_F(MyAppTestSuite, addFirstFilterValAddsVal) {
	filter_add(42);
	ASSERT_EQ(42, my_filter[readIdx]);
}

TEST_F(MyAppTestSuite, addFirstReturnsCorrectAverage) {
	filter_add(42);
	ASSERT_EQ(42, myapp_get_average());
}


TEST_F(MyAppTestSuite, addTwoValuesReturnsCorrectAverage) {
	filter_add(42);
	filter_add(40);
	ASSERT_EQ(41, myapp_get_average());
}

TEST_F(MyAppTestSuite, get_average_should_return_average_of_full_filter) {
	for(int i = 0; i < MAX_ITEMS; i++){
		filter_add(i);
	}
	ASSERT_EQ((0+1+2+3+4+5+6)/MAX_ITEMS, myapp_get_average());
}

TEST_F(MyAppTestSuite, get_average_should_return_average_of_wrapped_filter) {
	for(int i = 0; i < BUFFER_SIZE; i++){
		filter_add(i);
	}
	ASSERT_EQ((1+2+3+4+5+6+7)/MAX_ITEMS, myapp_get_average());
}

/// ....test buffer operations...


TEST_F(MyAppTestSuite, addFirstFilterValIncsWriteIdx) {
	filter_add(42);
	ASSERT_EQ(writeIdx, 1);
	ASSERT_EQ(1,filter_len());
}

TEST_F(MyAppTestSuite, addFilterValWrapsWriteIdx) {
	for(int i = 0; i < BUFFER_SIZE; i++){
		filter_add(i);
	}
	ASSERT_EQ(0, writeIdx);
}

TEST_F(MyAppTestSuite, addFilterValUpdatesReadIndex) {
	for(int i = 0; i < BUFFER_SIZE; i++){
		filter_add(i);
	}
	ASSERT_EQ(readIdx, 1);
	ASSERT_EQ(MAX_ITEMS, filter_len());
}

TEST_F(MyAppTestSuite, addFilterValWrapsReadIndex) {
	for(int i = 0; i < BUFFER_SIZE; i++){
		filter_add(i);
	}
	for(int i = 0; i < BUFFER_SIZE-1; i++){
		filter_add(i);
	}
	ASSERT_EQ(readIdx, 0);
	ASSERT_EQ(MAX_ITEMS, filter_len());
}

TEST_F(MyAppTestSuite, addFilterValGivesCorrectLen) {
	for(int i = 0; i < BUFFER_SIZE; i++){
		filter_add(i);
	}
	ASSERT_EQ(readIdx, 1);
	ASSERT_EQ(MAX_ITEMS, filter_len());
}
