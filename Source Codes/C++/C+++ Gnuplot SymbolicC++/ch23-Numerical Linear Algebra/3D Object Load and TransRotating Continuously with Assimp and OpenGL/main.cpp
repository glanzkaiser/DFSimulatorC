// g++ -o main main.cpp /root/SourceCodes/CPP/src/glad.c -lstdc++  -lassimp -lGLEW -lglfw -lGL
// Learn OpenGL chapter 20

// Merci beaucoup Freya et Sentinel

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h" // we do not use this since ' #include "stb_image.h" ' already included in /usr/include/learnopengl/model.h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 30.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	// glfw: initialize and configure
	// -----------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// -----------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// -----------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -----------
	Shader ourShader("model_loading.vs", "model_loading.fs");

	// load models
	// -----------
	// The default filesystem is the first place we build LearnOpenGL at /sources/Hamzstlab/LearnOpenGL
	//Model ourModel(FileSystem::getPath("backpack.obj")); 
	Model ourModel("airplane.obj"); 

	 // load and create a texture 
	// -----------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char *data = stbi_load("/root/SourceCodes/CPP/Assets/Textures/freya1.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
		stbi_image_free(data);


	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float X = 0, Y = 0, Z = 0;
	float percent = 0.01f;
	int direction = 1;
	float theta = 0;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
	// per-frame time logic
	// -----------
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// input
	// -----
	processInput(window);

	// render
	// ------
	glClearColor(0.30f, 0.55f, 0.65f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

	// don't forget to enable shader before setting uniforms
	ourShader.use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	ourShader.setMat4("projection", projection);
	ourShader.setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);

	// to scale the model
	glm::mat4 scale_mat = glm::mat4(1.0f);
	scale_mat = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));	// if the model is too big for our scene, scale it down here
	// for airplane.obj best at glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f))

	// to translate the model
	glm::mat4 translation_mat = glm::mat4(1.0f);
	translation_mat = glm::translate(translation_mat, glm::vec3(X, Y, Z)); // translate the object

	X += 2.0f * percent * direction;
	Y += 1.0f * percent * direction;
	Z += 2.0f * percent * direction;
	
	if (X >= 7 || X <=0 )
	{	
		direction = -direction;
	}

	std::cout << "X = " << X << " \t --- \t Y = " << Y << "\t --- \t Z = " << Z << "\n";
	
	// to rotate the model
	theta +=1.7f ;
	if (theta > 720)
	{
		theta -=720;
	}
	
	glm::mat4 rotation_mat = glm::mat4(1.0f);
	rotation_mat = glm::rotate(rotation_mat,1.5f*glm::radians(theta), glm::vec3(1.0f, 0.5f, 0.0f));	
	
	// scale the model first, then rotate and translate
	model = translation_mat * rotation_mat * scale_mat ;
	ourShader.setMat4("model", model);
	ourModel.Draw(ourShader);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -----------
	glfwSwapBuffers(window);
	glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// -----------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// -----------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// -----------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -----------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// -----------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
