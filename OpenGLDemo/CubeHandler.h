#pragma once


#include "stdafx.h"
#include <GL\glew.h>
#include <GL\glut.h>
#include "Cube.h"
#include <glm.hpp>
#include <gtx\range.hpp>

class CubeHandler
{
public:

	/*init vertices, buffers and shaders*/
	void init(glm::mat4 * MVP);

	/*draw the cubes*/
	void draw();
	
	/*how many cube to instantiate and manage*/
	int n_cubes;

private:

	/*Cube references*/
	Cube ** cubes;

	/*Inits the shader program for this object*/
	void initShader();

	GLint fs, vs;
};