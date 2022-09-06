cmake_minimum_required(VERSION 3.22.0)

project("libseis")

set(LIB_NAME "seis")

add_library(${LIB_NAME} SHARED libseis.c)

set_target_properties(
        ${LIB_NAME} PROPERTIES
        VERSION "0.1.0"
        PUBLIC_HEADER libseis.h
)

install(
        TARGETS ${LIB_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)