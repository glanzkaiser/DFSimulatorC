// g++ -c main.cpp 
// g++ main.o -o test -lGLEW -lglfw -lGL

// with CMake
// mkdir build
// cd build
// cmake ..
// make
// ./result

// Computer Graphics Programming in OpenGL with C++
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void init(GLFWwindow* window){}

void display(GLFWwindow* window, double currentTime) {
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(void)
{
	glfwInit(); //initialize GLFW and GLEW libraries
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(600, 600, " Learn Open GL with GLFW", NULL, NULL);
	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);	
	}
	glfwSwapInterval(1);
	
	init(window);
	
	while(!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);	
	//return 0;
}