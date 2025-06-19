//
// Created by dg on 6/8/25.
//

#ifndef GATHER_H
#define GATHER_H
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

class Gather {
public:
  int id{};
  int nt{};
  int nx{};
  double dt{};
  std::vector<double> data;

  Gather() = default;

  Gather(const int id, const int nt, const int nx, const double dt)
      : id{id}, nt{nt}, nx{nx}, dt{dt} {
    data.resize(nt * nx);
  }

  /**
   * @brief a helper function used for Python __str__ method.
   */
  [[nodiscard]] std::string str() const {
    return "Gather id: " + std::to_string(id);
  }

  /**
   * @brief overload the output stream operator for Gather.
   */
  friend std::ostream &operator<<(std::ostream &os, const Gather &gather) {
    os << "Gather id: " << gather.id << std::endl;
    return os;
  }

  /**
   * @brief Read a binary file and create a Gather object.
   *
   * This function takes a file path (string), the number of time samples (nt),
   * and the number of traces (nx) to read from the binary file.
   *
   * @param path the path to the binary file.
   * @param nt the number of time samples per trace.
   * @param nx the number of traces per gather.
   * @return Gather object populated with data from the file.
   */
  static Gather from_bin_file(const std::string &path, int nt, int nx,
                              double dt = 0.0) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
      throw std::runtime_error("Unable to open file at " + path);
    }

    std::size_t total_values = static_cast<std::size_t>(nt) * nx;
    std::vector<double> buffer(total_values);

    file.read(reinterpret_cast<char *>(buffer.data()),
              total_values * sizeof(double));
    if (!file) {
      throw std::runtime_error("Failed to read data from file at " + path);
    }

    Gather result(0, nt, nx, dt);
    result.data = std::move(buffer);
    return result;
  }
};

#endif // GATHER_H
