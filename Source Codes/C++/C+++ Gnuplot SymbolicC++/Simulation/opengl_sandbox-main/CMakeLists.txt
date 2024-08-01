cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
project(OpenGL-Sandbox)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/ CACHE PATH "Output directory of all executables.")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

# GLFW
find_package(glfw3 3.3 REQUIRED)

set(RES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/res)

include_directories(inc src/vendor)
add_subdirectory(src)
add_subdirectory(app)
