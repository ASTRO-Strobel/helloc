#include "gtest/gtest.h"

extern "C" {
    #include <facul.h>
}

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
