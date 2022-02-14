#include <catch.hpp>

#include <tuple>

extern "C" {
    #include <facul.h>
}

TEST_CASE("Test the facul function", "[facul]") {
    auto val_exp = GENERATE(
        std::make_tuple(0, 1),
        std::make_tuple(1, 1),
        std::make_tuple(2, 2),
        std::make_tuple(3, 6),
        std::make_tuple(4, 24)
        );
    int value = std::get<0>(val_exp);
    int expected = std::get<1>(val_exp);
    REQUIRE(facul(value) == expected);
}
