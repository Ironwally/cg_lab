cmake_minimum_required (VERSION 3.9)
project (raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(raytracer geometry/geometry.cc math/math.cc raytracer.cc
        output/renderer.cpp
        output/renderer.h
        objects/Sphere3d.h
        objects/Material.h
)
target_link_libraries(raytracer ${SDL2_LIBRARIES})

add_executable(test test/geometry_test.cc test/math_test.cc geometry/geometry.cc math/math.cc
        raytracer.cc
        test/renderer_test.cc
        output/Renderer.cpp
        output/Renderer.h
)

