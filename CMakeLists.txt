cmake_minimum_required(VERSION 3.15)

project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)

# Include core modules
add_subdirectory(src/core)

# Python bindings with pybind11
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

pybind11_add_module(_num MODULE src/core/bindings.cpp)
target_link_libraries(_num PRIVATE libseis)
install(TARGETS _num DESTINATION libseis)

pybind11_add_module(_gather MODULE src/core/bindings.cpp)
target_link_libraries(_gather PRIVATE libseis)
install(TARGETS _gather DESTINATION libseis)

# Testing ###
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(libseis_test src/core/add/add_test.cpp)
target_link_libraries(libseis_test libseis Python::Python GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(libseis_test)
