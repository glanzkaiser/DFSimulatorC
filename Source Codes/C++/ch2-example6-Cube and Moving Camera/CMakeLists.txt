cmake_minimum_required(VERSION 3.17)

project(result LANGUAGES CXX)

add_executable(result main.cpp)
target_link_libraries(result /root/SourceCodes/CPP/src/glad.c SOIL GL glfw )
target_include_directories(result PRIVATE /usr/include)