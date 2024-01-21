// g++ -o result main.cpp -lm -lglut -lGLEW -lGL -lsymbolicc++ -lboost_iostreams
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glut.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "symbolicc++.h" // for symbolic computation
#include <boost/math/differentiation/autodiff.hpp>

#include "../common/shader_utils.h"

GLuint program;
GLint attribute_coord2d;
GLint uniform_color;
GLint uniform_transform;

float offset_x = 0;
float scale_x = 1;
int mode = 0;

struct point {
	GLfloat x;
	GLfloat y;
};
GLuint vbo_derivative;
GLuint vbo[3];

const int border = 10;
const int ticksize = 10;

template <typename T>
T get_x_coordinate(T const & phi)
{
	return phi; 
}

int init_resources() {
	program = create_program("graph.v.glsl", "graph.f.glsl");
	if (program == 0)
		return 0;

	attribute_coord2d = get_attrib(program, "coord2d");
	uniform_transform = get_uniform(program, "transform");
	uniform_color = get_uniform(program, "color");

	if (attribute_coord2d == -1 || uniform_transform == -1 || uniform_color == -1)
		return 0;

	// Create the vertex buffer object
	glGenBuffers(3, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// Create our own temporary buffer
	point graph[2000];
	point graph_derivative[2000];

	// Fill it in just like an array
	for (int i = 0; i < 2000; i++) 
	{
		float x = (i ) / 10.0;

		graph[i].x = x;
		graph[i].y = (x*x*x) + (x*x);	
	}

	// Tell OpenGL to copy our array to the buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof graph, graph, GL_STATIC_DRAW);

	// Create a VBO for the border
	static const point border[4] = { {-1, -1}, {1, -1}, {1, 1}, {-1, 1} };
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof border, border, GL_STATIC_DRAW);

	return 1;
}

// Create a projection matrix that has the same effect as glViewport().
// Optionally return scaling factors to easily convert normalized device coordinates to pixels.
//
glm::mat4 viewport_transform(float x, float y, float width, float height, float *pixel_x = 0, float *pixel_y = 0) {
	// Map OpenGL coordinates (-1,-1) to window coordinates (x,y),
	// (1,1) to (x + width, y + height).

	// First, we need to know the real window size:
	float window_width = glutGet(GLUT_WINDOW_WIDTH);
	float window_height = glutGet(GLUT_WINDOW_HEIGHT);

	// Calculate how to translate the x and y coordinates:
	float offset_x = (2.0 * x + (width - window_width)) / window_width;
	float offset_y = (2.0 * y + (height - window_height)) / window_height;

	// Calculate how to rescale the x and y coordinates:
	float scale_x = width / window_width;
	float scale_y = height / window_height;

	// Calculate size of pixels in OpenGL coordinates
	if (pixel_x)
		*pixel_x = 2.0 / width;
	if (pixel_y)
		*pixel_y = 2.0 / height;

	return glm::scale(glm::translate(glm::mat4(1), glm::vec3(offset_x, offset_y, 0)), glm::vec3(scale_x, scale_y, 1));
}

void display() {
	int window_width = glutGet(GLUT_WINDOW_WIDTH);
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);

	glUseProgram(program);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	/* ---------------------------------------------------------------- */
	/* Draw the graph */

	// Set our viewport, this will clip geometry
	glViewport(border + ticksize, border + ticksize, window_width - border * 2 - ticksize, window_height - border * 2 - ticksize);

	// Set the scissor rectangle,this will clip fragments
	glScissor(border + ticksize, border + ticksize, window_width - border * 2 - ticksize, window_height - border * 2 - ticksize);

	glEnable(GL_SCISSOR_TEST);

	// Set our coordinate transformation matrix
	glm::mat4 transform = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(scale_x, 1, 1)), glm::vec3(offset_x, 0, 0));
	glUniformMatrix4fv(uniform_transform, 1, GL_FALSE, glm::value_ptr(transform));

	// Set the color to green
	GLfloat green[4] = { 0, 1, 0, 1 };
	glUniform4fv(uniform_color, 1, green);

	// Draw using the vertices in our vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glEnableVertexAttribArray(attribute_coord2d);
	glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINE_STRIP, 0, 2000);

	// Stop clipping
	glViewport(0, 0, window_width, window_height);
	glDisable(GL_SCISSOR_TEST);

	/* ---------------------------------------------------------------- */
	/* Draw the borders */

	float pixel_x, pixel_y;

	// Calculate a transformation matrix that gives us the same normalized device coordinates as above
	transform = viewport_transform(border + ticksize, border + ticksize, window_width - border * 2 - ticksize, window_height - border * 2 - ticksize, &pixel_x, &pixel_y);

	// Tell our vertex shader about it
	glUniformMatrix4fv(uniform_transform, 1, GL_FALSE, glm::value_ptr(transform));

	// Set the color to black
	GLfloat black[4] = { 0, 0, 0, 1 };
	glUniform4fv(uniform_color, 1, black);

	// Draw a border around our graph
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	/* ---------------------------------------------------------------- */
	/* Draw the y tick marks */

	point ticks[42];

	for (int i = 0; i <= 20; i++) {
		float y = -1 + i * 0.1;
		float tickscale = (i % 10) ? 0.5 : 1;

		ticks[i * 2].x = -1;
		ticks[i * 2].y = y;
		ticks[i * 2 + 1].x = -1 - ticksize * tickscale * pixel_x;
		ticks[i * 2 + 1].y = y;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof ticks, ticks, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, 42);

	/* ---------------------------------------------------------------- */
	/* Draw the x tick marks */

	float tickspacing = 0.1 * powf(10, -floor(log10(scale_x)));	// desired space between ticks, in graph coordinates
	float left = -1.0 / scale_x - offset_x;	// left edge, in graph coordinates
	float right = 1.0 / scale_x - offset_x;	// right edge, in graph coordinates
	int left_i = ceil(left / tickspacing);	// index of left tick, counted from the origin
	int right_i = floor(right / tickspacing);	// index of right tick, counted from the origin
	float rem = left_i * tickspacing - left;	// space between left edge of graph and the first tick

	float firsttick = -1.0 + rem * scale_x;	// first tick in device coordinates

	int nticks = right_i - left_i + 1;	// number of ticks to show

	if (nticks > 21)
		nticks = 21;	// should not happen

	for (int i = 0; i < nticks; i++) {
		float x = firsttick + i * tickspacing * scale_x;
		float tickscale = ((i + left_i) % 10) ? 0.5 : 1;

		ticks[i * 2].x = x;
		ticks[i * 2].y = -1;
		ticks[i * 2 + 1].x = x;
		ticks[i * 2 + 1].y = -1 - ticksize * tickscale * pixel_y;
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof ticks, ticks, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, nticks * 2);

	// And we are done.

	glDisableVertexAttribArray(attribute_coord2d);
	switch (mode) 
	{
	case 0:
		glDrawArrays(GL_LINE_STRIP, 0, 2000);
		break;
	case 1:
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(border + ticksize, border + ticksize, window_width - border * 2 - ticksize, window_height - border * 2 - ticksize);

		glScissor(border + ticksize, border + ticksize, window_width - border * 2 - ticksize, window_height - border * 2 - ticksize);

		glEnable(GL_SCISSOR_TEST);

		// Set our coordinate transformation matrix
		glm::mat4 transform = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(scale_x, 1, 1)), glm::vec3(offset_x, 0, 0));
		glUniformMatrix4fv(uniform_transform, 1, GL_FALSE, glm::value_ptr(transform));

		// Set the color to green
		GLfloat green[4] = { 0, 1, 0, 1 };
		glUniform4fv(uniform_color, 1, green);

		glGenBuffers(1, &vbo_derivative);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_derivative);

		// Create our own temporary buffer
		point graph_derivative[2000];

		// Fill it in just like an array
		for (int i = 0; i < 2000; i++) 
		{
			float var_x = (i ) / 10.0;
			double const phi{var_x};
			auto const x{::boost::math::differentiation::make_fvar<double, 5>(phi)}; // to find derivative till order 5
			auto const dx{get_x_coordinate(x*x*x + x*x)}; // we define the function f(x) here : get_x_coordinate(f(x))

			graph_derivative[i].x = var_x;
			graph_derivative[i].y = dx.derivative(1);
		}
		// Tell OpenGL to copy our array to the buffer object
		glBufferData(GL_ARRAY_BUFFER, sizeof graph_derivative, graph_derivative, GL_STATIC_DRAW);

		// Draw using the vertices in our vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, vbo_derivative);

		glEnableVertexAttribArray(attribute_coord2d);
		glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDrawArrays(GL_LINE_STRIP, 0, 2000); //this draw the function

		// Stop clipping
		glViewport(0, 0, window_width, window_height);
		glDisable(GL_SCISSOR_TEST);
		break;
	}
	glutSwapBuffers();
}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		mode = 0;
		printf("Drawing the original function.\n");
		break;
	case GLUT_KEY_F2:
		mode = 1;
		printf("Drawing the derivative.\n");
		break;
	case GLUT_KEY_LEFT:
		offset_x -= 0.03;
		break;
	case GLUT_KEY_RIGHT:
		offset_x += 0.03;
		break;
	case GLUT_KEY_UP:
		scale_x *= 1.5;
		break;
	case GLUT_KEY_DOWN:
		scale_x /= 1.5;
		break;
	case GLUT_KEY_HOME:
		offset_x = 0.0;
		scale_x = 1.0;
		break;
	}

	glutPostRedisplay();
}

void free_resources() {
	glDeleteProgram(program);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(1280, 800);
	glutCreateWindow("Graphs of Function and Its Derivative");

	GLenum glew_status = glewInit();

	// Showing the symbolic derivative
	Symbolic x("x");
	Symbolic y, dy;
	y = (x*x*x)+ (x*x);
	cout << "Plot y = f(x) and its derivative " << y << endl;
	cout << "y = " << y << endl;
	dy = df(y, x);       
	cout << "derivative of y = " << dy << endl;
	cout << endl;

	if (GLEW_OK != glew_status) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return 1;
	}

	if (!GLEW_VERSION_2_0) {
		fprintf(stderr, "No support for OpenGL 2.0 found\n");
		return 1;
	}

	printf("Use left/right to move horizontally.\n");
	printf("Use up/down to change the horizontal scale.\n");
	printf("Press home to reset the position and scale.\n");
	printf("Press F1 to draw the original function.\n");
	printf("Press F2 to draw the derivative.\n");

	if (init_resources()) {
		glutDisplayFunc(display);
		glutSpecialFunc(special);
		glutMainLoop();
	}

	free_resources();
	return 0;
}
