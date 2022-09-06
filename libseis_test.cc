#include "gtest/gtest.h"

extern "C" {
#include "libseis.h"
}

TEST(HelloTest, BasicAssertions) {
    EXPECT_EQ(7 * 6, 42);
}

TEST(AddTest, BasicAssertions) {
    int z = add(2, 4);
    EXPECT_EQ(z, 6);
}


