#pragma once

#include "stdafx.h"
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtx\range.hpp>
#include <gtc\matrix_transform.hpp>

#define M_PI 3.14159265358979323846

/* this class represent a single cube */
class Cube
{
public:
	
	/*constructor*/
	Cube(int _number, int * _n_cubes, glm::mat4 * _MVP);
	
	/*Deconstructor*/
	~Cube();

	/*draw this cube*/
	void draw();

	/*Inits the shader program for this object*/
	void initShader(GLuint fs, GLuint vs);

private:

	std::vector<unsigned int> indices;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;
	std::vector<GLfloat> normals;

	/*we spawn in circle, this is the radius*/
	const float radius = 10.0f;

	/*the cube number id from 0 to n cubes*/
	int number;

	/*ref to the n_cubes of the cube handler*/
	int * n_cubes;

	/*id for the vertex buffer*/
	GLuint vertexBuffer;

	/*id for the vertex buffer*/
	GLuint normalBuffer;

	/*id for the vertex buffer*/
	GLuint colorBuffer;

	/*id for the element buffer*/
	GLuint elementBuffer;

	/*init*/
	void init();

	/*GL program with compiled shaders ref and such*/
	GLuint program;

	/*MVP global*/
	glm::mat4 * MVP;

	GLuint vaoID;
};