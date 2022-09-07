#include "gtest/gtest.h"

extern "C" {
#include "libseis.h"
}

int const nt_test = 10;
int const nx_test = 1;

float float_trace[nt_test] = {
    0.000,
    0.000,
    0.000,
    0.001,
    -0.001,
    0.000,
    0.021,
    -0.016,
    0.009,
    -0.004,
};

TEST(HelloTest, ExampleTest) {
    EXPECT_EQ(7 * 6, 42);
}

TEST(LibseisIO, ReadWriteFloat) {
    char tmp_file[] = "/tmp/data.bin";
    write_float(tmp_file, float_trace, nt_test, nx_test);
    float *data = read_float(tmp_file, nt_test, nx_test);
    for (int i = 0; i < nt_test; i++) {
        printf("data %d: %.3g\n", i, data[i]);
        EXPECT_EQ(data[i], float_trace[i]);
    }
}

TEST(Gain, GainsTimeSample) {
    float *gained_data = gain(float_trace, nt_test, nx_test, 0.1, 2);
    for (int i = 0; i < nt_test; i++) {
        printf("data %d: %.3g\n", i, gained_data[i]);
    }
}
