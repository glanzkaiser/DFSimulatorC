// https://open.gl/content/code/c4_3d.txt
// g++ -c main.cpp
// g++ main.o -o result -L/usr/lib -lSOIL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system -lGL
//
// g++ *.cpp -o result -L/usr/lib -lSOIL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system -lGL

// Link statically with GLEW
#define GLEW_STATIC

// Headers
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include <SFML/Window.hpp>
#include <chrono>
#include <iostream>

using namespace std;

// Shader sources
const GLchar* vertexSource = R"glsl(
    #version 330 core
    in vec2 position;
    in vec3 color;
    in vec2 texcoord;
    out vec3 Color;
    out vec2 Texcoord;
    uniform mat4 trans;
    void main()
    {
        Color = color;
        Texcoord = texcoord;
        gl_Position = trans * vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 330 core
    in vec3 Color;
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D texFreya;
    uniform sampler2D texScrooge;
    void main()
    {
        outColor = mix(texture(texFreya, Texcoord), texture(texScrooge, Texcoord), 0.5);
    }
)glsl";

int main()
{
	auto t_start = std::chrono::high_resolution_clock::now();

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	sf::Window window(sf::VideoMode(1200, 800, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
	//  Position      Color             Texcoords
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
	0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
		};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	// Load textures
	GLuint textures[2];
	glGenTextures(2, textures);

	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
        image = SOIL_load_image("/root/SourceCodes/CPP/images/sample.png", &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texFreya"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	image = SOIL_load_image("/root/SourceCodes/CPP/images/sample2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texScrooge"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
	// cout << "Press A to shear the image in the x-direction, then reflect it about the line y=x" << endl;
        cout << "Press A to reflect the image about the line y=x, then shear it in the x-direction" << endl;
	cout << "Press Spacebar to return the image at the original position" << endl;
        
	bool running = true;
	GLfloat reflectiondirection = 0.0f;
	GLfloat reflectionxaxis = 1.0f;
	GLfloat reflectionyaxis = 0.0f;
	GLfloat k = 0.0f;
	
	while (running)
	{
	sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
	{
		switch (windowEvent.type)
		{
		case sf::Event::Closed:
		running = false;
		break;

		case sf::Event::KeyPressed:
		if (windowEvent.key.code == sf::Keyboard::A) {
                    	reflectiondirection += 180.0f;
			reflectionxaxis = 1.0f;
			reflectionyaxis = 1.0f;
			k = 2.0f;
			// cout << "Shear the image in the x-direction, then reflect it about the line y=x " << endl;
			cout << "Reflect the image about the line y=x, then shear it in the x-direction " << endl;
                }
                if (windowEvent.key.code == sf::Keyboard::Space) {
                    	reflectionxaxis = 1.0f;
			reflectionyaxis = 0.0f;
			reflectiondirection = 0.0f;	
			k = 0.0f;
		cout << "Normal position" << endl;
                }	
		break;
            }
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Calculate transformation
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        glm::mat4 reflectionMat = glm::mat4(1.0f);
	reflectionMat = glm::rotate(reflectionMat,
					glm::radians(reflectiondirection), // to see animation time*glm::radians(reflectiondirection)
					glm::vec3(reflectionxaxis, reflectionyaxis, 0.0f));  

	glm::mat4 shearMat = glm::mat4(1.0f);
	// change to shearY3D -> Shear in the x-direction
	shearMat = glm::shearY3D(shearMat,
					k, // the factor k
					0.0f); // z = 0 so it will looks like we are in 2-dimensional space

	glm::mat4 resultMat = glm::mat4(1.0f);
	
	// First composition
	// resultMat = reflectionMat*shearMat;
	// Second composition
	resultMat = shearMat*reflectionMat;
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(resultMat));
	
        // Draw a rectangle from the 2 triangles using 6 indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap buffers
        window.display();
    }

    glDeleteTextures(2, textures);

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    window.close();

    return 0;
}