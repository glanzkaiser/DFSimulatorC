cmake_minimum_required(VERSION 3.8)

# https://cmake.org/cmake/help/latest/command/project.html
project(result VERSION 2.4.1)
add_executable(result main.cpp)
target_link_libraries(result box2d)
target_include_directories(result PUBLIC)
