cmake_minimum_required (VERSION 3.9)
project (raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(raytracer_exe configuration/configuration.h geometry/geometry.cc math/math.cc raytracer.cc
        renderer/Renderer.h
        objects/Sphere3d.h
        objects/Material.h
        tracer/Tracer.h
        objects/Scene.h
)
target_link_libraries(raytracer_exe ${SDL2_LIBRARIES})

