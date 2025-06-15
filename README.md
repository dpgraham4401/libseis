# Libseis

### Seismic library for geophysical processing

This is a learn-by-doing project
to reacquaint myself with the C/C++, geophysics, and binding with Python.

## Getting Started

### Prerequisites

- CMake
- C++ compiler (e.g., g++, clang++)
- Python > 3.12
- Python development headers
    - On Debian/Ubuntu: `sudo apt-get install python3-dev`
    - On Fedora: `sudo dnf install python3-devel`
    - On macOS: `brew install python`
- [uv](https://docs.astral.sh/uv/) for python project management

### Building the Library

1. Clone the repo
2. Navigate to the project directory
3. Create a virtual environment (optional but recommended)
   ```shell
   uv venv
   source .venv/bin/activate
   ```
4. Build and install the project
   ```shell
    uv sync
    ```
5. Run the Python tests

   With the virtual environment activated, libseis should be installed and available.

    ```shell
    pytest
    ```
6. Run the C++ tests
    ```shell
    cd build
    ctest
    ```
