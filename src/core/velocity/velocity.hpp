//
// Created by dg on 6/8/25.
//

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

class VelocityModel {
public:
  VelocityModel(int rows, int cols);

  double &at(int row, int col);
  const double &at(int row, int col) const;

  int rows() const { return _rows; }
  int cols() const { return _cols; }

  void initialize_simple_model(double gradient, double starting_velocity);

private:
  int _rows;
  int _cols;
  std::vector<double> _data; // flattened 2D array
};
