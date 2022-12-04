#include "libseis.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double *read_double(char path[], int nt, int nx) {
    FILE *fptr;
    double *data;
    data = (double *) malloc(nt * nx * sizeof(double));
    fptr = fopen(path, "rb");
    if (fptr == NULL) {
        printf("unable to open file at %s\n", path);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nt * nx; i++) {
        fread(&data[i], sizeof(double), 1, fptr);
    }
    fclose(fptr);
    return data;
}

void write_double(char path[], double *data, int nt, int nx) {
    FILE *fptr;
    fptr = fopen(path, "wb");
    if (fptr == NULL) {
        printf("unable to open file at %s\n", path);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nx * nt; i++) {
        fwrite(&data[i], sizeof(double), 1, fptr);
    }
    fclose(fptr);
}

Gather *gain_gather(Gather *gather, double power) {
    Gather *new_gather = malloc(sizeof(struct Gather));
    new_gather->id = gather->id;
    new_gather->nt = gather->nt;
    new_gather->nx = gather->nx;
    new_gather->dt = gather->dt;
    new_gather->data = malloc(gather->nt * gather->nt * sizeof(double));
    for (int trace_index = 0; trace_index < gather->nx; trace_index++) {
        for (int sample_index = 0; sample_index < gather->nt; sample_index++) {
            double time = (double) sample_index * new_gather->dt;
            double t_pow = pow(time, power);
            int data_index = (trace_index * new_gather->nt) + sample_index;
            new_gather->data[data_index] = gather->data[data_index] * t_pow;
        }
    }
    return new_gather;
}
