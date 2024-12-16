cmake_minimum_required (VERSION 3.9)
project (raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)

add_executable(raytracer geometry/geometry.cc math/math.cc raytracer.cc)
add_executable(test test/geometry_test.cc test/math_test.cc raytracer.cc geometry/geometry.cc math/math.cc raytracer.cc)

