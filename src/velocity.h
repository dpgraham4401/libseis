//
// Created by dg on 5/4/24.
//

#ifndef VELOCITY_H
#define VELOCITY_H

typedef struct {
  int rows;
  int cols;
  double **data;
} VelocityModel;

VelocityModel *allocate_velocity_model(int rows, int cols);

VelocityModel *simple_velocity_model(VelocityModel *model, double gradient,
                                     double startingVelocity);

#endif // VELOCITY_H
