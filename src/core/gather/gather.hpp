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
  [[nodiscard]] std::string str() const;

  /**
     * @brief overload the output stream operator for Gather.
     */
  friend std::ostream& operator<<(std::ostream& os, const Gather& gather);

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
  static Gather from_bin_file(const std::string& path, int nt, int nx, double dt = 0.0);
};

#endif  // GATHER_H
