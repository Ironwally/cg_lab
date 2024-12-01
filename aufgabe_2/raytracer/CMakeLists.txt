cmake_minimum_required (VERSION 3.9)
project (raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)

include_directories("C:/msys64/ucrt64/include")
link_directories("C:/msys64/ucrt64/lib")

add_executable(math_test math_test.cc math.cc
        geometry_test.cc
        geometry.tcc
        geometry.cc
        math.tcc
        raytracer.cc
        raytracer/configuration/configuration.h
        raytracer/tracer/Tracer.h
        raytracer/objects/Screen.h
        raytracer_test.cc
        raytracer/objects/Camera.h
        raytracer/objects/Camera.h
        raytracer/objects/Sphere3d.h
        raytracer/objects/Material.h
        raytracer/objects/Triangle3d.h
        raytracer/objects/Object3d.h
        raytracer/renderer/renderer.h
)
target_link_libraries(math_test raytracer_test gtest gtest_main)

add_executable(raytracer math_test math_test.cc math.cc
        geometry_test.cc
        geometry.tcc
        geometry.cc
        math.tcc
        raytracer.cc
        raytracer/configuration/configuration.h
        raytracer/tracer/Tracer.h
        raytracer/objects/Screen.h
        raytracer_test.cc
        raytracer/objects/Camera.h
        raytracer/objects/Camera.h
        raytracer/objects/Sphere3d.h
        raytracer/objects/Triangle3d.h
        raytracer/objects/Object3d.h
        raytracer/renderer/renderer.h
)
