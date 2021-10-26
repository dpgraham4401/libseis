project('libseis', 'c',
  version : '0.0.1',
  )

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_LIBTEST']

shlib = shared_library('libseis', 'libseis.c',
  install : true,
  c_args : lib_args,
  gnu_symbol_visibility : 'hidden',
)

test_exe = executable('libseis_test', 'libseis_test.c',
  link_with : shlib)
test('libseis', test_exe)

# Make this library usable as a Meson subproject.
libseis_dep = declare_dependency(
  include_directories: include_directories('.'),
  link_with : shlib)

# Make this library usable from the system's
# package manager.
install_headers('libseis.h', subdir : 'libseis')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : 'libseis',
  filebase : 'libseis',
  description : 'Meson sample project.',
  subdirs : 'libseis',
  libraries : shlib,
  version : '0.0.1',
)
