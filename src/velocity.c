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

VelocityModel *simple_velocity_model(VelocityModel *model,
                                     const double gradient,
                                     const double startingVelocity) {

  for (int i = 0; i < model->rows; i++) {
    for (int j = 0; j < model->cols; j++) {
      model->data[i][j] = startingVelocity + gradient * i;
    }
  };
  return model;
}
