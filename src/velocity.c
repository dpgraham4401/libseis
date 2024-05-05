#include "velocity.h"

#include <stdlib.h>

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
