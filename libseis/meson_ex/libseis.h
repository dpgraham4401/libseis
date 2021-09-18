#pragma once
#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_LIBSEIS
    #define LIBSEIS_PUBLIC __declspec(dllexport)
  #else
    #define LIBSEIS_PUBLIC __declspec(dllimport)
  #endif
#else
  #ifdef BUILDING_LIBSEIS
      #define LIBSEIS_PUBLIC __attribute__ ((visibility ("default")))
  #else
      #define LIBSEIS_PUBLIC
  #endif
#endif

int LIBSEIS_PUBLIC lib_func();

