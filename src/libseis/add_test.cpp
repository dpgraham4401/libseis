#include "add.hpp"
#include "gtest/gtest.h"

TEST(AddFunctionTest, HandlesPositiveNumbers) {
  EXPECT_EQ(libseis::add(1, 2), 3);
  EXPECT_EQ(libseis::add(10, 20), 30);
}
