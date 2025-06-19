//
// Created by David Graham on 6/8/25.
//

#include "add/add.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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
      // .def(py::init<int, int, int, double>())
      .def(py::init<int, int, int, double>(), py::arg("id"), py::arg("nt"),
           py::arg("nx"), py::arg("dt"))
      .def_readwrite("id", &Gather::id)
      .def_readwrite("nt", &Gather::nt)
      .def_readwrite("nx", &Gather::nx)
      .def_readwrite("dt", &Gather::dt)
      .def_readonly("data", &Gather::data)
      .def("__str__", &Gather::str)
      .def("from_bin_file", &Gather::from_bin_file);
}
