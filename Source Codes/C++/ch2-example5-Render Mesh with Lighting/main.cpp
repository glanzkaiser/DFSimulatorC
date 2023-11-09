// g++ *.cpp -o result -lGLEW -lglfw -lGL

// GLEW needs to be included first
#include <GL/glew.h>

// GLFW is included next
#include <GLFW/glfw3.h>

void initGame();
void renderScene();
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"

GLuint textProgram;

Camera* camera;
LightRenderer* light;

void initGame() {
	// Enable the depth testing
	glEnable(GL_DEPTH_TEST); 
	ShaderLoader shader;
	textProgram = shader.createProgram("/root/SourceCodes/CPP/Assets/Shaders/text.vs", "/root/SourceCodes/CPP/Assets/Shaders/text.fs");

	GLuint flatShaderProgram = shader.createProgram("/root/SourceCodes/CPP/Assets/Shaders/FlatModel.vs", "/root/SourceCodes/CPP/Assets/Shaders/FlatModel.fs");
	
	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));

	light = new LightRenderer(MeshType::kCube, camera); // Define Mesh type -> see Mesh.h
	light->setProgram(flatShaderProgram);
	light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(1.0, 1.0, 0.0, 1.0);
	light->draw();
}

static void glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}

void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods){

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	// Press Q to see Quad, T for Triangle, C for Cube and S for Sphere
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		ShaderLoader shader;
		GLuint flatShaderProgram = shader.createProgram("/root/SourceCodes/CPP/Assets/Shaders/FlatModel.vs", "/root/SourceCodes/CPP/Assets/Shaders/FlatModel.fs");
		camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));
		light = new LightRenderer(MeshType::kCube, camera); 
		light->setProgram(flatShaderProgram);
		light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		ShaderLoader shader;
		GLuint flatShaderProgram = shader.createProgram("/root/SourceCodes/CPP/Assets/Shaders/FlatModel.vs", "/root/SourceCodes/CPP/Assets/Shaders/FlatModel.fs");
		camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));
		light = new LightRenderer(MeshType::kTriangle, camera); 
		light->setProgram(flatShaderProgram);
		light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));	
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		ShaderLoader shader;
		GLuint flatShaderProgram = shader.createProgram("/root/SourceCodes/CPP/Assets/Shaders/FlatModel.vs", "/root/SourceCodes/CPP/Assets/Shaders/FlatModel.fs");
		camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));
		light = new LightRenderer(MeshType::kQuad, camera); 
		light->setProgram(flatShaderProgram);
		light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		ShaderLoader shader;
		GLuint flatShaderProgram = shader.createProgram("/root/SourceCodes/CPP/Assets/Shaders/FlatModel.vs", "/root/SourceCodes/CPP/Assets/Shaders/FlatModel.fs");
		camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));
		light = new LightRenderer(MeshType::kSphere, camera); 
		light->setProgram(flatShaderProgram);
		light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));	
	}
}

int main(int argc, char **argv)
{
	glfwSetErrorCallback(&glfwError);
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, " Mesh in OpenGL ", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, updateKeyboard);
	glewInit();
	initGame();
	while (!glfwWindowShouldClose(window)){
		renderScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	delete camera;
	delete light;
	return 0;
}
