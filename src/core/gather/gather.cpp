//
// Created by dg on 6/8/25.
//

#include "gather.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

std::string Gather::str() const {
  return "Gather id: " + std::to_string(id);
}

std::ostream& operator<<(std::ostream& os, const Gather& gather) {
  os << "Gather id: " << gather.id << std::endl;
  return os;
}

Gather Gather::from_bin_file(const std::string& path, int nt, int nx, double dt) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file at " + path);
  }
  std::size_t total_values = static_cast<std::size_t>(nt) * nx;
  std::vector<double> buffer(total_values);
  file.read(reinterpret_cast<char*>(buffer.data()), total_values * sizeof(double));
  if (!file) {
    throw std::runtime_error("Failed to read data from file at " + path);
  }
  Gather result(0, nt, nx, dt);
  result.data = std::move(buffer);
  return result;
}
