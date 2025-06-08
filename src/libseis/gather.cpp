//
// Created by dg on 6/8/25.
//

#include "gather.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// Equivalent of the C struct. Ideally move to a header file.
struct Gather {
  int id;
  int nt;
  int nx;
  double dt;
  std::vector<double> data;
};

std::vector<double> read_double(const std::string &path, int nt, int nx) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file at " + path);
  }

  std::vector<double> data(nt * nx);
  file.read(reinterpret_cast<char *>(data.data()), nt * nx * sizeof(double));
  if (!file) {
    throw std::runtime_error("Failed to read data from file at " + path);
  }

  return data;
}

void write_double(const std::string &path, const std::vector<double> &data,
                  int nt, int nx) {
  std::ofstream file(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file at " + path);
  }

  file.write(reinterpret_cast<const char *>(data.data()),
             nt * nx * sizeof(double));
  if (!file) {
    throw std::runtime_error("Failed to write data to file at " + path);
  }
}

std::unique_ptr<Gather> gain_gather(const Gather &gather, double power) {
  auto new_gather = std::make_unique<Gather>(gather);
  new_gather->data.resize(gather.nt * gather.nx);

  for (int trace_index = 0; trace_index < gather.nx; ++trace_index) {
    for (int sample_index = 0; sample_index < gather.nt; ++sample_index) {
      double time = static_cast<double>(sample_index) * gather.dt;
      double t_pow = std::pow(time, power);
      int data_index = trace_index * gather.nt + sample_index;
      new_gather->data[data_index] = gather.data[data_index] * t_pow;
    }
  }

  return new_gather;
}

void display_gather(const Gather &gather) {
  std::cout << "--------------------\n";
  std::cout << "Gather: id " << gather.id << '\n';
  std::cout << "Sample Rate: " << gather.dt << " seconds\n";
  std::cout << "Sampling Frequency: " << 1.0 / gather.dt << " Hz\n";
  std::cout << "Nyquist Frequency: " << 1.0 / (2 * gather.dt) << " Hz\n";
  std::cout << "Samples per trace: " << gather.nt << '\n';
  std::cout << "Number of traces: " << gather.nx << '\n';
  std::cout << "--------------------\n";
}
