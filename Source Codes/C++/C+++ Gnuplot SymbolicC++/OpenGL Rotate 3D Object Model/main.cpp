#include <glad/glad.h> // GLAD: https://github.com/Dav1dde/glad
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
     
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
     
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
     
#include <vector>
#include <iostream>
#include <fstream> // Used in "shader_configure.h" to read the shader text files
#include <learnopengl/filesystem.h>
     
#include "load_model_meshes.h"
#include "shader_configure.h" // Used to create the shaders
     
int main()
{
	// (1) GLFW: Initialise & Configure
	// --------------------------------
	if (!glfwInit())
		exit(EXIT_FAILURE);
     
	//glfwWindowHint(GLFW_SAMPLES, 4); // Anti-aliasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
     
	int monitor_width = mode->width; // Monitor's width
	int monitor_height = mode->height;
     
	int window_width = (int)(monitor_width * 0.55f); // Window size will be 50% the monitor's size...
	int window_height = (int)(monitor_height * 0.55f); // ... Cast is simply to silence the compiler warning
     
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGL Maths (GLM) - Transformations", NULL, NULL);
     
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window); // Set the window to be used and then centre that window on the monitor
	glfwSetWindowPos(window, (monitor_width - window_width) / 2, (monitor_height - window_height) / 2);
     
	glfwSwapInterval(1); // Set VSync rate 1:1 with monitor's refresh rate.
     
	// (2) GLAD: Load OpenGL Function Pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glEnable(GL_DEPTH_TEST); // Enabling depth testing allows rear faces of 3D objects to be hidden behind front faces
	glEnable(GL_MULTISAMPLE); // Anti-aliasing
	glEnable(GL_BLEND); // GL_BLEND for OpenGL transparency which is further set within the fragment shader
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     
	// (3) Compile Shaders Read from Text Files
	// ----------------------------------------
	const char* vert_shader = "shader_glsl.vert";
	const char* frag_shader = "shader_glsl.frag";
     
	Shader main_shader(vert_shader, frag_shader);
	main_shader.use();
     
	unsigned int view_matrix_loc = glGetUniformLocation(main_shader.ID, "view");
	unsigned int projection_matrix_loc = glGetUniformLocation(main_shader.ID, "projection");
	unsigned int rotation_mat_loc = glGetUniformLocation(main_shader.ID, "rotation_mat");
     
	unsigned int image_sampler_loc = glGetUniformLocation(main_shader.ID, "image");
	unsigned int camera_position_loc = glGetUniformLocation(main_shader.ID, "camera_position");
     
	// (4) Load Models & Set Camera
	// ----------------------------
	Model plane("airplane.obj");
     
	glm::vec3 camera_position(0.0f, 0.0f, -10.0f); // -Z is into the screen
	glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
     
	glActiveTexture(GL_TEXTURE0); // Reusing the same texture unit for each model mesh
	glUniform1i(image_sampler_loc, 0);
     
	glUniform3f(camera_position_loc, camera_position.x, camera_position.y, camera_position.z);
     
	glm::mat4 view = glm::lookAt(camera_position, camera_target, camera_up);
	glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, glm::value_ptr(view)); // Transfer view matrix to vertex shader uniform
     
	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 10000.0f);
	// in orthographic projection read page 85 Joey de Vries book
	glm::mat4 projection = glm::ortho(-3300.0f, 3300.0f, -2000.0f, 2000.0f, 0.0f, 100000.0f); //for airplane
	//glm::mat4 projection = glm::ortho(-330.0f, 330.0f, -200.0f, 200.0f, 0.0f, 50.0f); // for spider object
	
	glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, glm::value_ptr(projection));
     
	glm::mat4 rotation_mat1(1.0f); // 1.0f initializes the mat4 to an identity matrix
	glm::mat4 rotation_mat2(1.0f);
	glm::mat4 rotation_comb(1.0f);
     
	float counter = 0;
     
	while (!glfwWindowShouldClose(window)) // Main Loop
	{
		counter += 0.7f;
     
		//if (counter < 35)
			rotation_mat1 = glm::rotate(rotation_mat1, glm::radians(1.0f), glm::normalize(glm::vec3(0.5f, 0, 0.1f)));
		//if (counter > 35 && counter < 70)
			rotation_mat2 = glm::rotate(rotation_mat2, glm::radians(1.0f), glm::normalize(glm::vec3(0.9f, 2.4f, 0)));
     
		rotation_comb = rotation_mat2 * rotation_mat1;
     
		glUniformMatrix4fv(rotation_mat_loc, 1, GL_FALSE, glm::value_ptr(rotation_comb)); // Pass model matrix to vertex shader
     
		// (5) Clear the Screen & Draw Model Meshes
		// ----------------------------------------
		glClearColor(0.30f, 0.55f, 0.65f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
		for (unsigned int i = 0; i < plane.num_meshes; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, plane.mesh_list[i].tex_handle); // Bind texture for the current mesh
     
			glBindVertexArray(plane.mesh_list[i].VAO);
			glDrawElements(GL_TRIANGLES, (GLsizei)plane.mesh_list[i].vert_indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// (6) Exit the Application
	// ------------------------
	glDeleteProgram(main_shader.ID); // This OpenGL function call is talked about in: shader_configure.h
     
	/* glfwDestroyWindow(window) // Call this function to destroy a specific window */
	glfwTerminate(); // Destroys all remaining windows and cursors, restores modified gamma ramps, and frees resources
     
	exit(EXIT_SUCCESS); // Function call: exit() is a C/C++ function that performs various tasks to help clean up resources
}