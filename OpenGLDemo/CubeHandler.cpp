#include "stdafx.h"
#include "CubeHandler.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <math.h>   
#include <iostream>

#define M_PI 3.14159265358979323846

void CubeHandler::init(glm::mat4 * MVP)
{
	n_cubes = 20;

	cubes = new Cube*[n_cubes];

	for (int i = 0; i < n_cubes; i++)
	{
		cubes[i] = new Cube(i, &n_cubes, MVP);
	}

	initShader();
}

void CubeHandler::draw()
{
	for (int i = 0; i < n_cubes; i++)
	{
		cubes[i]->draw();
	}
}

/*
Inits the shader program for this object
*/
void CubeHandler::initShader()
{
	//get per vertex shader
	std::ifstream file_v("per_vertex_light.vs");
	std::string strv;

	file_v.seekg(0, std::ios::end);
	strv.reserve(file_v.tellg());
	file_v.seekg(0, std::ios::beg);

	strv.assign((std::istreambuf_iterator<char>(file_v)),
		std::istreambuf_iterator<char>());
	static const char * vs_source = strv.c_str();

	//get per fragment shader
	std::ifstream file_f("per_vertex_light.fs");
	std::string strf;

	file_f.seekg(0, std::ios::end);
	strf.reserve(file_f.tellg());
	file_f.seekg(0, std::ios::beg);

	strf.assign((std::istreambuf_iterator<char>(file_f)),
		std::istreambuf_iterator<char>());
	static const char * fs_source = strf.c_str();

	// We create a shader with our fragment shader source code and compile it.
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);

	// We create a shader with our vertex shader source code and compile it.
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);

	GLint success = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		//Setup Error Log
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog[0]);
		std::string log;
		for (int i = 0; i < errorLog.size(); i++) {
			log += errorLog[i];
		}

		std::cout << log << std::endl;

		glDeleteShader(vs);
	}
	else
		std::cout << "Shader compilation ok" << std::endl;

	for (int i = 0; i < n_cubes; i++)
	{
		cubes[i]->initShader(fs, vs);
	}
}