### Libseis
cmake_minimum_required(VERSION 3.22.0)

project("libseis")

### Variables
set(CMAKE_CXX_STANDARD 11)

set(LIB_NAME "seis")
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

set(SRC_DIR "src")

### create libseis library
include_directories(src)
add_library(${LIB_NAME} SHARED ${SRC_DIR}/libseis.c ${SRC_DIR}/velocity.c)


set_target_properties(
        ${LIB_NAME} PROPERTIES
        VERSION "v${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
        PUBLIC_HEADER ${SRC_DIR}/libseis.h
        PUBLIC_HEADER ${SRC_DIR}/velocity.h
)

install(
        TARGETS ${LIB_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

### Google Test ###
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(libseis_test test/libseis_test.cpp)
add_executable(velocity_test test/velocity_test.cpp)
target_link_libraries(libseis_test ${LIB_NAME} GTest::gtest_main)
target_link_libraries(velocity_test ${LIB_NAME} GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(libseis_test)
gtest_discover_tests(velocity_test)
