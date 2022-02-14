#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "param.h"  // parametrization helper

#include <tuple>
#include <list>

extern "C" {
    #include <facul.h>
}

TEST_CASE("Test the facul function") {
    std::list<std::tuple<int, int>> params = {
        std::make_tuple(0, 1),
        std::make_tuple(1, 1),
        std::make_tuple(2, 2),
        std::make_tuple(3, 6),
        std::make_tuple(4, 24)
    }; // must be iterable - std::vector<> would work as well

    std::tuple<int, int> val_exp;
    DOCTEST_VALUE_PARAMETERIZED_DATA(val_exp, params);

    int value = std::get<0>(val_exp);
    int expected = std::get<1>(val_exp);
    CHECK(facul(value) == expected);
}
