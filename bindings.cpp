//
// Created by dg on 6/7/25.
//
#include "library.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(mylib, m) {
  m.def("add", &mylib::add, "A function which adds two numbers");
}
