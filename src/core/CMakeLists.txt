# Gather sources into individual libraries
add_library(libadd STATIC add/add.cpp)
target_include_directories(libadd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/add)

add_library(libgather STATIC gather/gather.cpp)
target_include_directories(libgather PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/gather)

# add_library(libvelocity STATIC velocity/velocity.cpp)
# target_include_directories(libvelocity PUBLIC
# ${CMAKE_CURRENT_SOURCE_DIR}/velocity)

# Combined library: libseis aggregates all
add_library(libseis INTERFACE)
target_link_libraries(libseis INTERFACE libadd libgather)
# target_compile_features(libseis PRIVATE cxx_std_17)
# target_compile_options(libseis PRIVATE -Wall -Wpedantic -Weffc++ -Wextra
# -Wfatal-errors)
set_property(TARGET libseis PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(libseis PRIVATE ${Python_INCLUDE_DIRS})
