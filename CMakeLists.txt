cmake_minimum_required(VERSION 3.15)

project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

pybind11_add_module(_add MODULE src/libseis/add.cpp)
install(TARGETS _add DESTINATION libseis)

# Test ### Create static library to test the C++ code
add_library(libseis STATIC src/libseis/add.cpp)
target_compile_features(libseis PRIVATE cxx_std_17)
target_compile_options(libseis PRIVATE -Wall -Wpedantic -Weffc++ -Wextra
                                       -Wfatal-errors)
set_property(TARGET libseis PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(libseis PRIVATE ${Python_INCLUDE_DIRS})

# Fetch Google Test from GitHub
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(libseis_test src/libseis/add_test.cpp)
target_link_libraries(libseis_test libseis Python::Python GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(libseis_test)
