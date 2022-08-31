#include <gtest/gtest.h>

TEST(uci_tests, hello_world) {
    EXPECT_EQ(1+1, 2);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}