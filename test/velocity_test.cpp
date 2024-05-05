#include "gtest/gtest.h"
extern "C" {
#include "velocity.h"
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

TEST(SimpleVelocityModel, ShouldApplyCorrectGradient) {
  int rows = 5;
  int cols = 10;
  double gradient = 2.0;
  double startingVelocity = 1.0;
  VelocityModel *model = allocate_velocity_model(rows, cols);
  model = simple_velocity_model(model, gradient, startingVelocity);
  for (int i = 0; i < model->rows; i++) {
    for (int j = 0; j < model->cols; j++) {
      ASSERT_EQ(model->data[i][j], startingVelocity + gradient * i);
    }
  }
  free(model);
}

TEST(SimpleVelocityModel, ShouldHandleZeroGradient) {
  int rows = 5;
  int cols = 10;
  double gradient = 0.0;
  double startingVelocity = 1.0;
  VelocityModel *model = allocate_velocity_model(rows, cols);
  model = simple_velocity_model(model, gradient, startingVelocity);
  for (int i = 0; i < model->rows; i++) {
    for (int j = 0; j < model->cols; j++) {
      ASSERT_EQ(model->data[i][j], startingVelocity);
    }
  }
  free(model);
}