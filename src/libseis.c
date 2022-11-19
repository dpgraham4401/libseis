#include "libseis.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

Gather *gain_cmp(Gather *gather, float pow) {
    Gather new_gather = {
        gather->id,
        gather->nt,
        gather->nx,
        gather->dt,
        malloc(gather->nt * gather->nx * sizeof(float)),

    };
    float *new_data = malloc(gather->nt * gather->nx * sizeof(float));
    for (int trace_index = 0; trace_index < gather->nx; trace_index++) {
        for (int sample_index = 0; sample_index < gather->nt; sample_index++) {
            float time = (float) sample_index * new_gather.dt;
            float t_pow = powf(time, pow);
            int data_index = (trace_index * new_gather.nt) + sample_index;
            new_gather.data[data_index] = gather->data[data_index] * t_pow;
        }
    }
    Gather *new_gather_ptr = &new_gather;
    return new_gather_ptr;
}
