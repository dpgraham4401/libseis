#include "libseis.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float *read_float(char path[], int nt, int nx) {
    FILE *fptr;
    float *data;
    data = (float *) malloc(nt * nx * sizeof(float));
    fptr = fopen(path, "rb");
    if (fptr == NULL) {
        printf("unable to open file at %s\n", path);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nt * nx; i++) {
        fread(&data[i], sizeof(float), 1, fptr);
    }
    fclose(fptr);
    return data;
}

void write_float(char path[], float *data, int nt, int nx) {
    FILE *fptr;
    fptr = fopen(path, "wb");
    if (fptr == NULL) {
        printf("unable to open file at %s\n", path);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nx * nt; i++) {
        fwrite(&data[i], sizeof(float), 1, fptr);
    }
    fclose(fptr);
}

float *gain(const float *data, int nt, int nx, float dt, float pow) {
    float *gained_data;
    gained_data = (float *) malloc(nt * nx * sizeof(float));
    for (int n = 1; n < nx + 1; n++) {
        for (int t = 0; t < nt; t++) {
            float t_float = (float) t;
            gained_data[n * t] = data[n * t] * (dt * t_float * pow);
        }
    }
    return gained_data;
}

