// g++ -o result main.cpp -lm -lglut -lGLEW -lGL 
// merci beaucoup Freya
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <iomanip> // to declare the manipulator of setprecision()
#include <fstream>
#include <bits/stdc++.h> //for setw(6) at display() function
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../common/shader_utils.h"

#include "res_texture.c"

GLuint program;
GLint attribute_coord2d;
GLint uniform_offset_x;
GLint uniform_offset_y;
GLint uniform_scale_x;
GLint uniform_scale_y;
GLint uniform_sprite;
GLuint texture_id;
GLint uniform_mytexture;

float offset_x = 0.0;
float offset_y = 0.0;
float scale_x = 1.0;
float scale_y = 1.0;
int mode = 0;

struct point {
	GLfloat x;
	GLfloat y;
};

const int N = 3;

GLuint vbo;

using namespace std;

// Function to calculate b
double calculateB(int x[], int y[], int n)
{     
	// sum of array x
	int sx = accumulate(x, x + n, 0);
	// sum of array y
	int sy = accumulate(y, y + n, 0);

	// for sum of product of x and y
	int sxsy = 0;

	// sum of square of x
	int sx2 = 0;
	for(int i = 0; i < n; i++) 
	{
	sxsy += x[i] * y[i];
	sx2 += x[i] * x[i];
	}
	double b = (double)(n * sxsy - sx * sy) /
			(n * sx2 - sx * sx);
 
	return b;
}

double calculateA(int X[], int Y[], int n)
{     
	double b = calculateB(X, Y, n);

	int meanX = accumulate(X, X + n, 0) / n;
	int meanY = accumulate(Y, Y + n, 0) / n;

	// Calculating a
	double a = meanY - b * meanX;
 
	return a;
}
 
// Function to find the least regression line
void leastRegLine(int X[], int Y[], int n)
{ 
	// Finding b
	double b = calculateB(X, Y, n);

	int meanX = accumulate(X, X + n, 0) / n;
	int meanY = accumulate(Y, Y + n, 0) / n;

	// Calculating a
	double a = meanY - b * meanX;

	// Printing regression line
	cout << ("Regression line:") << endl;
	cout << ("Y = ");
	printf("%.3f + ", a);
	printf("%.3f *X", b);
}
 
int* vecx() {
	static int x[N];
	std::fstream in("vectorX.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			x[i] =vectortiles[i];	
	}	
	return x;
}

int* vecy() {
	static int y[N];
	std::fstream in("vectorY.txt");
	float vectortiles[N];
	for (int i = 0; i < N; ++i) 
	{
			in >> vectortiles[i]; 
			y[i] =vectortiles[i];	
	}	
	return y;
}

int init_resources() {
	program = create_program("graph.v.glsl", "graph.f.glsl");
	if (program == 0)
		return 0;

	attribute_coord2d = get_attrib(program, "coord2d");
	uniform_offset_x = get_uniform(program, "offset_x");
	uniform_offset_y = get_uniform(program, "offset_y");
	uniform_scale_x = get_uniform(program, "scale_x");
	uniform_scale_y = get_uniform(program, "scale_y");
	uniform_sprite = get_uniform(program, "sprite");
	uniform_mytexture = get_uniform(program, "mytexture");

	if (attribute_coord2d == -1 || uniform_offset_y == -1 || uniform_offset_x == -1 || uniform_scale_y == -1 || uniform_scale_x == -1 || uniform_sprite == -1 || uniform_mytexture == -1)
		return 0;

	/* Enable blending */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Enable point sprites (not necessary for true OpenGL ES 2.0) */
#ifndef GL_ES_VERSION_2_0
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
#endif

	/* Upload the texture for our point sprites */
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res_texture.width, res_texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, res_texture.pixel_data);

	// Create the vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Take the vector data from textfile as pointer
	int* ptrvecx;
	ptrvecx = vecx();
	int* ptrvecy;
	ptrvecy = vecy();

	int X[N]; // declare an array name X with size of N
	int Y[N];  
	
	for (int i = 0; i < N; ++i)
	{
		X[i] = ptrvecx[i];
		Y[i] = ptrvecy[i];	
	}	
	int n = N;
	double a = calculateA(X, Y, n);
	double b = calculateB(X, Y, n);

	// Create our own temporary buffer
	//point graph[2000]; // to draw regression line

	// Fill it in just like an array, to draw the points 
	// to draw the regression line
	for (int i = 0; i < 2000; i++) {
		float x = (i -1000) / 10.0;
	//	graph[i].x = x;
	//	graph[i].y = a + b*x;		
	}	

	point graph[N]; // to draw points
	for (int i = 0; i < N; i++) {
		graph[i].x = ptrvecx[i];
		graph[i].y = ptrvecy[i];		
	}
	
	
	// Tell OpenGL to copy our array to the buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof graph, graph, GL_STATIC_DRAW);

	return 1;
}

void display() {
	glUseProgram(program);
	glUniform1i(uniform_mytexture, 0);

	glUniform1f(uniform_offset_x, offset_x);
	glUniform1f(uniform_offset_y, offset_y);
	glUniform1f(uniform_scale_x, scale_x);
	glUniform1f(uniform_scale_y, scale_y);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/* Draw using the vertices in our vertex buffer object */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(attribute_coord2d);
	glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);

	/* Push each element in buffer_vertices to the vertex shader */
	switch (mode) {
	case 0:
		glUniform1f(uniform_sprite, 0);
		glDrawArrays(GL_LINE_STRIP, 0, 2000);
		break;
	case 1:
		glUniform1f(uniform_sprite, 1);
		glDrawArrays(GL_POINTS, 0, 2000);
		break;
	case 2:
		glUniform1f(uniform_sprite, res_texture.width);
		glDrawArrays(GL_POINTS, 0, 2000);
		break;
	}

	glutSwapBuffers();
}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		mode = 0;
		printf("Now drawing using lines.\n");
		break;
	case GLUT_KEY_F2:
		mode = 1;
		printf("Now drawing using points.\n");
		break;
	case GLUT_KEY_F3:
		mode = 2;
		printf("Now drawing using point sprites.\n");
		break;
	case GLUT_KEY_LEFT:
		offset_x += 0.1;
		break;
	case GLUT_KEY_RIGHT:
		offset_x -= 0.1;
		break;
	case GLUT_KEY_UP:
		offset_y -= 0.1;
		break;
	case GLUT_KEY_DOWN:
		offset_y += 0.1;
		break;
	case GLUT_KEY_F4:
		scale_x += 0.1;
		break;
	case GLUT_KEY_F5:
		scale_x -= 0.1;
		break;
	case GLUT_KEY_F6:
		scale_y += 0.1;
		break;
	case GLUT_KEY_F7:
		scale_y -= 0.1;
		break;
	case GLUT_KEY_HOME:
		offset_x = 0.0;
		offset_y = 0.0;
		scale_x = 0.1;
		scale_y = 0.1;
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
	glutInitWindowSize(1024, 600);
	glutCreateWindow("Least Square Regression Line");

	GLenum glew_status = glewInit();

	if (GLEW_OK != glew_status) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return 1;
	}

	if (!GLEW_VERSION_2_0) {
		fprintf(stderr, "No support for OpenGL 2.0 found\n");
		return 1;
	}

	int* ptrvecx;
	ptrvecx = vecx();
	int* ptrvecy;
	ptrvecy = vecy();
	
	cout << "Vector / Data X: " << setw(30) << "Vector / Data Y: " << endl;
	for (int i = 0; i < N; ++i)
	{
		cout <<ptrvecx[i]<< "\t \t \t \t" << ptrvecy[i] << endl;	
	}	
	cout << endl;
	// Statistical data
	int X[N]; // declare an array name X with size of N
	int Y[N]; 
	
	for (int i = 0; i < N; ++i)
	{
		X[i] = ptrvecx[i];
		Y[i] = ptrvecy[i];	
	}	
	int n = N;	//int n = sizeof(X) / sizeof(X[0]);
	double a = calculateA(X, Y, n);
	cout << "a = " << a << endl;
	cout << endl;
	double b = calculateB(X, Y, n);
	cout << "b = " << b << endl;
	cout << endl;
	leastRegLine(X, Y, n);
	cout << endl;

	GLfloat range[2];

	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, range);
	if (range[1] < res_texture.width)
		fprintf(stderr, "WARNING: point sprite range (%f, %f) too small\n", range[0], range[1]);

	printf("Use left/right to move horizontally.\n");
	printf("Use up/down to move vertically.\n");
	printf("Press home to reset the position and scale.\n");
	printf("Press F1 to draw lines.\n");
	printf("Press F2 to draw points.\n");
	printf("Press F3 to draw point sprites.\n");
	printf("Press F4 to zoom in /F5 to zoom out the horizontal scale.\n");
	printf("Press F6 to zoom in /F7 to zoom out the vertical scale.\n");

	if (init_resources()) {
		glutDisplayFunc(display);
		glutSpecialFunc(special);
		glutMainLoop();
	}

	free_resources();
	return 0;
}