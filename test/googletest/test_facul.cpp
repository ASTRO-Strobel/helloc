#include "gtest/gtest.h"

extern "C" {
    #include <facul.h>
}

// test facul function
class FaculTest :
    public testing::TestWithParam<std::tuple<int, int>> {
        protected:
        int get_value() {
            return std::get<0>(GetParam());
        }
        int get_expected() {
            return std::get<1>(GetParam());
        }
};
TEST_P(FaculTest, test_facul) {
    EXPECT_EQ(facul(get_value()), get_expected());
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
