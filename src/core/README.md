# Seismic library core modules

C++ library and Python extension modules for seismic data processing and analysis.

Modules are created using [pybind11](https://pybind11.readthedocs.io/en/stable/) and
built using [CMake](https://cmake.org/).

## Organization

The core libraries are not exposed (currently, 06/2025) directly, but are used to create
private Python modules which we are selectively exposed to the user.
