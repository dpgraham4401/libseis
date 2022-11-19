#include "gtest/gtest.h"

extern "C" {
#include "libseis.h"
}

int const nt_test = 10;
int const nx_test = 1;

float float_trace1[nt_test] = {
    0.000,
    2.000,
    4.000,
    8.000,
    1.000,
    2.000,
    3.000,
    4.000,
    5.000,
    6.000,
};

float cmp_array[nt_test * 2] = {
    0.000,
    2.000,
    4.000,
    8.000,
    1.000,
    2.000,
    3.000,
    4.000,
    5.000,
    6.000,
    0.000,
    0.000,
    1.000,
    0.020,
    0.301,
    -0.101,
    0.035,
    0.011,
    -0.006,
    0.009,
};

struct Gather cmp = {
    1,
    nt_test,
    2,
    1,
    cmp_array,
    DOUBLE
};

TEST(HelloTest, ExampleTest) {
    EXPECT_EQ(7 * 6, 42);
}

TEST(LibseisIO, ReadWriteFloat) {
    char tmp_file[] = "/tmp/data.bin";
    write_float(tmp_file, float_trace1, nt_test, nx_test);
    float *data = read_float(tmp_file, nt_test, nx_test);
    for (int i = 0; i < nt_test; i++) {
        EXPECT_EQ(data[i], float_trace1[i]);
    }
}

TEST(GainCmp, GainsCmpGather) {
    float t_pow = 2;
    Gather *foo = gain_cmp(&cmp, t_pow);
    printf("%D\n", foo->nt);
    EXPECT_EQ(0, 0);
}
