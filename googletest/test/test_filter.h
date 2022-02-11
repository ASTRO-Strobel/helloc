extern "C" {
    #include "filter.h"
}
class FilterTestSuite : public testing::Test
{
    void SetUp(){
        memset(&my_filter, 0, sizeof(my_filter));
        readIdx = 0;
        writeIdx = 0;
    }

    void TearDown(){}
};

// forward declaration for mocked function, which shall be used in other
// tests as well
extern "C" {
    extern int fake_register;
}
