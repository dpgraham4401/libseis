//
// Created by David Graham on 6/8/25.
//

#ifndef GATHER_H
#define GATHER_H
#include <string>
#include <vector>

class Gather {
 public:
  int id;
  int nt;
  int nx;
  double dt;
  std::vector<double> data;

  Gather(int id, int nt, int nx, double dt);

  [[nodiscard]] std::string display() const;

  static Gather from_bin_file(const std::string& path, int nt, int nx,
                              double dt);
};

#endif  // GATHER_H
