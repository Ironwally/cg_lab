cmake_minimum_required (VERSION 3.9)
project (asteroids_3d)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)

# Find SDL2 package
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

add_executable(main_game main_game.cc
        game.cc
        wavefront.cc
        sdl2_renderer.cc opengl_renderer.cc
        sdl2_game_controller.cc
        math.cc
        matrix.cc
        geometry.cc
        physics.cc
        sound.cc
        timer.cc)

target_link_libraries(main_game SDL2 SDL2_mixer OPENGL32 GLEW32) # MinGW
#target_link_libraries(main_game SDL2 SDL2_mixer GL GLEW ${SDL2_INCLUDE_DIRS}) # Linux

enable_testing()
add_executable(math_test math_test.cc math.cc)
target_link_libraries(math_test gtest gtest_main)
add_executable(matrix_test matrix_test.cc matrix.cc math.cc)
target_link_libraries(matrix_test gtest gtest_main)
add_executable(geometry_test geometry_test.cc geometry.cc math.cc)
target_link_libraries(geometry_test gtest gtest_main)
add_executable(physics_test physics_test.cc physics.cc geometry.cc math.cc timer.cc)
target_link_libraries(physics_test gtest gtest_main SDL2)
add_executable(game_test game_test.cc game.cc physics.cc geometry.cc math.cc timer.cc)
target_link_libraries(game_test gtest gtest_main SDL2)

