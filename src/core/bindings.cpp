//
// Created by David Graham on 6/8/25.
//

#include "add/add.hpp"
#include <pybind11/pybind11.h>

#include "gather.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_num, m) {
  m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: libseis

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

  m.def("add", &libseis::add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}

PYBIND11_MODULE(_gather, m) {
  py::class_<Gather>(m, "Gather")
      .def(py::init<>())
      .def_readwrite("id", &Gather::id)
      .def_readwrite("dt", &Gather::dt)
      .def_readwrite("nt", &Gather::nt)
      .def_readwrite("nx", &Gather::nx)
      .def("__str__", &Gather::display);
}
