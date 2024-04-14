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
glm::mat4 pMat, vMat, mMat, mvMat, rxMat, ryMat, rzMat, rxvMat, ryvMat, rzvMat;

glm::mat4 rtranslateMat, rtranslateleftMat, rtranslaterightMat;;

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
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
	cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
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
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
	rxMat = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(-1.0f, 0.0f, 0.0f));
        // Pitch movement toward user positive z axis between y axis and z axis
	rxvMat = vMat * rxMat;
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(rxvMat)); 
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
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
	rxMat = glm::rotate(glm::mat4(1.0f),  (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
        // Pitch movement toward monitor negative z axis between y axis and z axis
	rxvMat = vMat * rxMat;
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(rxvMat)); 
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
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
	rzMat = glm::rotate(glm::mat4(1.0f),  (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // Roll movement counter clockwise between x axis and y axis
	rzvMat = vMat * rzMat;
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(rzvMat)); 
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
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
	rzMat = glm::rotate(glm::mat4(1.0f),  (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -1.0f));
        // Roll movement clockwise between x axis and y axis
	rzvMat = vMat * rzMat;
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(rzvMat)); 
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
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
	ryMat = glm::rotate(glm::mat4(1.0f),  (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
	// Yaw movement counter clockwise between x axis and z axis.
        ryvMat = vMat * ryMat;
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(ryvMat)); 
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
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
	ryMat = glm::rotate(glm::mat4(1.0f),  (float)glfwGetTime(), glm::vec3(0.0f, -1.0f, 0.0f));
	// Yaw movement clockwise between x axis and z axis.
        ryvMat = vMat * ryMat;
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(ryvMat)); 
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
	rtranslateMat = glm::translate(glm::mat4(1.0f), 
			glm::vec3((0.05f*(float)glfwGetTime())*-2.0f, 
				cos(0.52f*currentTime)*0.0f, 
				sin(0.7f*currentTime)*0.0f));
	
	// Yaw movement counter clockwise between x axis and z axis.
        rtranslateleftMat = vMat * rtranslateMat;
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(rtranslateleftMat)); 
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

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
	rtranslateMat = glm::translate(glm::mat4(1.0f), 
				glm::vec3((0.05f*(float)glfwGetTime())*1.0f,0.0f, 0.0f));
	
	// Yaw movement counter clockwise between x axis and z axis.
        rtranslaterightMat = vMat * rtranslateMat;
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(rtranslaterightMat)); 
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