extern "C" {
    #include "filter.h"
}

// test fixture for the filter, which resets the filter on setup
class FilterTestSuite : public testing::Test
{
    void SetUp(){
        memset(&my_filter, 0, sizeof(my_filter));
        readIdx = 0;
        writeIdx = 0;
    }

    void TearDown(){}
};

// forward declaration, because we want to use fake register (which is
// part of the mocked implementation) in other tests as well
extern "C" {
    extern int fake_register;
}
