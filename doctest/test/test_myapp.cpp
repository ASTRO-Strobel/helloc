#include "doctest/doctest.h"

#include "test_filter.h"

extern "C" {
    #include <myapp.h>
    #include <filter.h>

    // forward declaration for a private function in myapp.c, which is
    // not included in the public header files
    int myapp_task();
}


TEST_CASE("Test the app") {
    FilterTestFixture filter_test_fixture = FilterTestFixture();
    filter_test_fixture.set_up();

    SUBCASE("myapp_task_should_return_correct_delay_for_one_element") {
        fake_register = 10;
        REQUIRE(10 == myapp_task());
    }

    SUBCASE("myapp_task_should_return_correct_delay_for_two_elements") {
        fake_register = 10;
        myapp_task();
        fake_register = 20;
        REQUIRE(15 == myapp_task());
    }
}
