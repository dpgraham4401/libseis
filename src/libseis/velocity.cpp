//
// Created by dg on 6/8/25.
//

#include "velocity.hpp"

VelocityModel::VelocityModel(const int rows, const int cols)
    : _rows(rows), _cols(cols), _data(rows * cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("VelocityModel dimensions must be positive");
  }
}

double &VelocityModel::at(const int row, const int col) {
  return _data.at(row * _cols + col);
}

const double &VelocityModel::at(int row, int col) const {
  return _data.at(row * _cols + col);
}

void VelocityModel::initialize_simple_model(const double gradient,
                                            const double starting_velocity) {
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      at(i, j) = starting_velocity + gradient * i;
    }
  }
}
