#include "gtest/gtest.h"

extern "C" {
#include "libseis.h"
}

TEST(HelloTest, ExampleTest) {
    EXPECT_EQ(7 * 6, 42);
}
