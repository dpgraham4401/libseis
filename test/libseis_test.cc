#include "gtest/gtest.h"

extern "C" {
#include "libseis.h"
}

TEST(HelloTest, ExampleTest) {
    EXPECT_EQ(7 * 6, 42);
}

TEST(LibseisIO, ReadBinaryFile) {
    int nt = 1000;
    int nx = 3101;
    char path[] = "/home/dg/Projects/libseis/test/shot6220.bin";
    float *data = read_float(path, nt, nx);
    for (int i = 0; i < nt; i++) {
        printf("data %d: %.9g\n", i, data[1000 + i]);
    }
}
