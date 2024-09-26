cmake_minimum_required(VERSION 3.17)

project(result LANGUAGES CXX)

#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
	
#include_directories(SYSTEM "path/to/glad/include")
	
add_executable(result main.cpp)
target_link_libraries(result glfw
		/root/SourceCodes/CPP/src/glad.c )