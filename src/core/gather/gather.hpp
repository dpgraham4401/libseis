//
// Created by dg on 6/8/25.
//

#ifndef GATHER_H
#define GATHER_H
#include <string>

class Gather {
public:
  int id;
  int nt;
  int nx;
  double dt;
  [[nodiscard]] std::string display() const {
    return "Gather id: " + std::to_string(id);
  }
};

#endif // GATHER_H
