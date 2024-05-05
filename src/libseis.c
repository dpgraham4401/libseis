#include "libseis.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *read_double(char path[], int nt, int nx) {
  FILE *fptr;
  double *data;
  data = (double *)malloc(nt * nx * sizeof(double));
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

/**
 * Creates a new gather with the same data as the input gather, but with each
 * sample multiplied by a power of its corresponding time value.
 *
 * @param gather The input gather to be multiplied.
 * @param power The power to raise the time values to.
 * @return A new gather with the same dimensions as the input gather, but with
 * modified data.
 */
Gather *gain_gather(Gather *gather, double power) {
  Gather *new_gather = malloc(sizeof(Gather));
  if (new_gather == NULL) {
    fprintf(stderr, "Error: input gather is NULL\n");
  }
  memcpy(new_gather, gather, sizeof(Gather));
  new_gather->data = malloc(gather->nt * gather->nx * sizeof(double));
  if (new_gather->data == NULL) {
    fprintf(stderr, "Error: input gather data is NULL\n");
  }
  memcpy(new_gather->data, gather->data,
         gather->nt * gather->nx * sizeof(double));
  for (int trace_index = 0; trace_index < gather->nx; trace_index++) {
    for (int sample_index = 0; sample_index < gather->nt; sample_index++) {
      double time = (double)sample_index * new_gather->dt;
      double t_pow = pow(time, power);
      int data_index = (trace_index * new_gather->nt) + sample_index;
      new_gather->data[data_index] = gather->data[data_index] * t_pow;
    }
  }
  return new_gather;
}

void display_gather(Gather *gather) {
  printf("--------------------\n");
  printf("Gather: id %d\n", gather->id);
  printf("Sample Rate: %f seconds\n", gather->dt);
  printf("Sampling Frequency: %f Hz\n", 1 / gather->dt);
  printf("Nyquist Frequency: %f Hz\n", 1 / (gather->dt * 2));
  printf("Samples per trace: %d\n", gather->nt);
  printf("Number of traces: %d\n", gather->nx);
  printf("--------------------\n");
}

VelocityModel *allocate_velocity_model(const int rows, const int cols) {
  VelocityModel *model = malloc(sizeof(VelocityModel));
  model->rows = rows;
  model->cols = cols;

  model->data = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++) {
    model->data[i] = (double *)malloc(cols * sizeof(double));
  }

  return model;
}
