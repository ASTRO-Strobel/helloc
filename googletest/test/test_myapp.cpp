#include "gtest/gtest.h"

#include "test_filter.h"

extern "C" {
    #include <myapp.h>
    #include <filter.h>

    // forward declaration for a private function in myapp.c, which is
    // not included in the public header files
    int myapp_task();
}


class MyAppTestSuite : public FilterTestSuite {
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
