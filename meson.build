project('fourier-circles', ['c','cpp'], default_options: ['cpp_std=c++2a'])


cpp_warning_flags = [
  '-Wall',
  '-Wextra',
  '-pedantic-errors',
  '-Wdisabled-optimization',
  '-Werror=unused-result',
  '-Werror=return-type'
]

npp_proj = subproject('npp-utils')
npp_dep = npp_proj.get_variable('npputils_dep')
catch2_dep = npp_proj.get_variable('catch2_dep')

png_dep = dependency('libpng')

subdir('lib')
subdir('src')
