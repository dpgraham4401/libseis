#include "gtest/gtest.h"

extern "C" {
#include "libseis.h"
}

int const nt_test = 10;
int const nx_test = 1;

double double_trace1[nt_test] = {
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

double cmp_array[nt_test * 2] = {
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
    write_double(tmp_file, double_trace1, nt_test, nx_test);
    double *data = read_double(tmp_file, nt_test, nx_test);
    for (int i = 0; i < nt_test; i++) {
        EXPECT_EQ(data[i], double_trace1[i]);
    }
}

TEST(GainCmp, GainsCmpGather) {
    double t_pow = 2;
    Gather *foo = gain_gather(&cmp, t_pow);
    printf("%d\n", foo->nt);
    EXPECT_EQ(0, 0);
}
