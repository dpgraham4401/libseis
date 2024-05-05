//
// Created by dg on 5/4/24.
//

#include <gtest/gtest.h>

extern "C" {
#include "libseis.h"
}

TEST(VelocityModel, AllocateVelocityModel) {
  constexpr int rows = 5;
  constexpr int cols = 5;

  // Call the function to test
  VelocityModel *model = allocate_velocity_model(rows, cols);

  // Check if the function returned a non-null pointer
  ASSERT_NE(model, nullptr);

  // Check if the rows and cols are correctly set
  EXPECT_EQ(model->rows, rows);
  EXPECT_EQ(model->cols, cols);

  // Check if the data array is correctly allocated
  ASSERT_NE(model->data, nullptr);

  // Check each row of the data array
  for (int i = 0; i < rows; i++) {
    ASSERT_NE(model->data[i], nullptr);
  }
}
