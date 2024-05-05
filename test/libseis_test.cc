#include "gtest/gtest.h"

extern "C" {
#include "libseis.h"
#include <math.h>
}

int const nt_test = 10;
int const nx_test = 1;

double double_trace1[nt_test] = {
    0.000, 2.000, 4.000, 8.000, 1.000, 2.000, 3.000, 4.000, 5.000, 6.000,
};

double cmp_array[nt_test * 2] = {
    0.000, 2.000, 4.000, 8.000, 1.000, 2.000,  3.000, 4.000, 5.000,  6.000,
    0.000, 0.000, 1.000, 0.020, 0.301, -0.101, 0.035, 0.011, -0.006, 0.009,
};

struct Gather cmp = {1, nt_test, 2, 1, cmp_array, DOUBLE};

TEST(LibseisIO, ReadWriteFloat) {
  char tmp_file[] = "/tmp/data.bin";
  write_double(tmp_file, double_trace1, nt_test, nx_test);
  double *data = read_double(tmp_file, nt_test, nx_test);
  for (int i = 0; i < nt_test; i++) {
    EXPECT_EQ(data[i], double_trace1[i]);
  }
}

TEST(GainCmp, GainsCmpGather) {
  double t_pow = 2;
  Gather *foo = gain_gather(&cmp, t_pow);

  printf("Check that the t^power function operates correctly");
  for (int i = 0; i < foo->nt; i++) {
    printf("%f * (%f^%f) = %f\n", cmp.data[i], foo->dt * i, t_pow,
           foo->data[i]);
    double t_powered = cmp.data[i] * pow(foo->dt * i, t_pow);
    EXPECT_EQ(foo->data[i], t_powered);
  }
}

TEST(Gather, GatherDisplay) { display_gather(&cmp); }

TEST(VelocityModelTest, AllocateVelocityModel) {
  int rows = 5;
  int cols = 5;

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

  // Free the allocated memory
  for (int i = 0; i < rows; i++) {
    free(model->data[i]);
  }
  free(model->data);
  free(model);
}