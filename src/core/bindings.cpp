//
// Created by David Graham on 6/8/25.
//

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "add/add.hpp"
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
      .def(py::init<int, int, int, double>())
      .def_readwrite("id", &Gather::id)
      .def_readwrite("dt", &Gather::dt)
      .def_readwrite("nt", &Gather::nt)
      .def_readwrite("nx", &Gather::nx)
      .def_property(
          "_data",
          // Getter: return numpy array (zero-copy)
          [](Gather& self) -> py::array {
            return py::array({self.nt, self.nx}, {sizeof(double) * self.nx, sizeof(double)},
                             self.data.data(), py::cast(&self));
          },
          // Setter: accept 2D NumPy array and copy into C++ vector
          [](Gather& self,
             const py::array_t<double, py::array::c_style | py::array::forcecast>& arr) {
            if (arr.ndim() != 2)
              throw std::runtime_error("data must be 2D");
            if (arr.shape(0) != self.nt || arr.shape(1) != self.nx)
              throw std::runtime_error("Shape mismatch with (nt, nx)");

            std::memcpy(self.data.data(), arr.data(), sizeof(double) * self.nt * self.nx);
          })
      .def("__str__", &Gather::display)
      .def("from_bin_file", &Gather::from_bin_file);
}
