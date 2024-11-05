cmake_minimum_required (VERSION 3.9)
project (raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)

add_executable(math_test math_test.cc math.cc
        geometry_test.cc
        geometry.tcc
        geometry.cc
        math.tcc
        raytracer.cc
        raytracer/configuration/configuration.cpp
        raytracer/configuration/configuration.h
        raytracer/tracer/Tracer.cpp
        raytracer/tracer/Tracer.h
        raytracer/screen/Screen.cpp
        raytracer/screen/Screen.h
        raytracer_test.cc)
target_link_libraries(math_test raytracer_test gtest gtest_main)

