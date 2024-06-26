// g++ -c main.cpp 
// g++ main.o -o result -lGLEW -lglfw -lGL
// g++ *.cpp -o result -lGLEW -lglfw -lGL

// Computer Graphics Programming in OpenGL with C++
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp> 
#include "Utils.h"

using namespace std;

#define numVAOs 1
#define numVBOs 2

// camera for movement with keyboard
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, xyshearMat;

void setupVertices(void) { // 36 vertices, 12 triangles, makes 2x2x2 cube placed at origin
	float vertexPositions[108] = {
	-1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
	};
	glGenVertexArrays(1,vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void init(GLFWwindow* window){
	
	// Utils
 	renderingProgram = Utils::createShaderProgram(
        "vertShader.glsl",
        "fragShader.glsl");
	cameraX = 0.0f; cameraY = 2.5f; cameraZ = 10.0f;
	cubeLocX = 0.0f; cubeLocY = -5.0f; cubeLocZ = 0.0f;
	setupVertices();
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	
	// get the uniform variables for the MV and projection matrices
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	// build perspective matrix
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

	// build view matrix, model matrix, and model-view matrix
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, -cubeLocZ));
	mvMat = vMat * mMat;
	
	GLfloat k;
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
	k = -1.0f;
	glm::mat4 shearMat = glm::mat4(1.0f);
	// change to shearX3D -> Shear in the y-direction
	// change to shearY3D -> Shear in the x-direction
	xyshearMat = glm::shearY3D(shearMat,
					k*(float)currentTime, // the factor k
					0.0f); // z = 0 so it will looks like we are in 2-dimensional space
	// Pitch movement toward monitor negative z axis between y axis and z axis
	xyshearMat = vMat * xyshearMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(xyshearMat)); 
	// copy perspective and MV matrices to corresponding uniform variables
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	
	// associate VBO with the corresponding vertex attribute in the vertex shader
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	// adjust OpenGL settings and draw model
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES,0,36);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
	k = 1.0f;   
	glm::mat4 shearMat = glm::mat4(1.0f);
	// change to shearX3D -> Shear in the y-direction
	// change to shearY3D -> Shear in the x-direction
	xyshearMat = glm::shearY3D(shearMat,
					k, // the factor k
					0.0f); // z = 0 so it will looks like we are in 2-dimensional space
	// Pitch movement toward monitor negative z axis between y axis and z axis
	xyshearMat = vMat * xyshearMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(xyshearMat)); 
	// copy perspective and MV matrices to corresponding uniform variables
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	
	// associate VBO with the corresponding vertex attribute in the vertex shader
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	// adjust OpenGL settings and draw model
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES,0,36);     
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
	k = 0.0f;        
	glm::mat4 shearMat = glm::mat4(1.0f);
	// change to shearX3D -> Shear in the y-direction
	// change to shearY3D -> Shear in the x-direction
	xyshearMat = glm::shearY3D(shearMat,
					k, // the factor k
					0.0f); // z = 0 so it will looks like we are in 2-dimensional space
	// Pitch movement toward monitor negative z axis between y axis and z axis
	xyshearMat = vMat * xyshearMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(xyshearMat)); 
	// copy perspective and MV matrices to corresponding uniform variables
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	
	// associate VBO with the corresponding vertex attribute in the vertex shader
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	// adjust OpenGL settings and draw model
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES,0,36);
	}
	
	
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(window, true);
	}
}


int main(void)
{
	glfwInit(); //initialize GLFW and GLEW libraries
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(600, 600, "Pitch, Yaw, Roll for Interpolated Color Cube", NULL, NULL);
	glfwMakeContextCurrent(window);
	//glfwSetKeyCallback(window, updateKeyboard);
	if(glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);	
	}
	glfwSwapInterval(1);
	
	init(window);
	
	while(!glfwWindowShouldClose(window)) {
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);	
	//return 0;
}