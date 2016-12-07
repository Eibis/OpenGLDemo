#include "stdafx.h"
#include "Cube.h"

#include<iostream>

/*Utility function to convert an hsv color to an rgb one*/
static void hsv2rgb(float * hsv, float * rgb)
{
	double hh, p, q, t, ff;
	long i;

	if (hsv[1] <= 0.0)
	{
		rgb[0] = hsv[2]; //R
		rgb[1] = hsv[2]; //G
		rgb[2] = hsv[2]; //B

		return;
	}

	hh = hsv[0];

	if (hh >= 360.0)
		hh = 0.0;

	hh /= 60.0;

	i = (long)hh;
	ff = hh - i;
	p = hsv[2] * (1.0 - hsv[1]);
	q = hsv[2] * (1.0 - (hsv[1] * ff));
	t = hsv[2] * (1.0 - (hsv[1] * (1.0 - ff)));

	switch (i) {
	case 0:
		rgb[0] = hsv[2];
		rgb[1] = t;
		rgb[2] = p;
		break;
	case 1:
		rgb[0] = q;
		rgb[1] = hsv[2];
		rgb[2] = p;
		break;
	case 2:
		rgb[0] = p;
		rgb[1] = hsv[2];
		rgb[2] = t;
		break;

	case 3:
		rgb[0] = p;
		rgb[1] = q;
		rgb[2] = hsv[2];
		break;
	case 4:
		rgb[0] = t;
		rgb[1] = p;
		rgb[2] = hsv[2];
		break;
	case 5:
	default:
		rgb[0] = hsv[2];
		rgb[1] = p;
		rgb[2] = q;
		break;
	}
}

Cube::Cube(int _number, int * _n_cubes, glm::mat4 * _MVP) : number(_number), n_cubes(_n_cubes), MVP(_MVP)
{}

Cube::~Cube()
{
	indices.clear();
	vertices.clear();
	normals.clear();
	colors.clear();
	
	glDeleteBuffers(1, &elementBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &colorBuffer);
}

void Cube::init()
{
	//setting up the vertices
	vertices.push_back(-1.0f); vertices.push_back(-1.0f); vertices.push_back(-1.0f);
	vertices.push_back(1.0f); vertices.push_back(-1.0f); vertices.push_back(-1.0f);
	vertices.push_back(1.0f); vertices.push_back(1.0f); vertices.push_back(-1.0f);
	vertices.push_back(-1.0f); vertices.push_back(1.0f); vertices.push_back(-1.0f);
	vertices.push_back(-1.0f); vertices.push_back(-1.0f); vertices.push_back(1.0f);
	vertices.push_back(1.0f); vertices.push_back(-1.0f); vertices.push_back(1.0f);
	vertices.push_back(1.0f); vertices.push_back(1.0f); vertices.push_back(1.0f);
	vertices.push_back(-1.0f); vertices.push_back(1.0f); vertices.push_back(1.0f);

	//setting up the normals
	normals.push_back(-0.333f); normals.push_back(-0.333f); normals.push_back(-0.333f);
	normals.push_back(0.333f); normals.push_back(-0.333f); normals.push_back(-0.333f);
	normals.push_back(0.333f); normals.push_back(0.333f); normals.push_back(-0.333f);
	normals.push_back(-0.333f); normals.push_back(0.333f); normals.push_back(-0.333f);
	normals.push_back(-0.333f); normals.push_back(-0.333f); normals.push_back(0.333f);
	normals.push_back(0.333f); normals.push_back(-0.333f); normals.push_back(0.333f);
	normals.push_back(0.333f); normals.push_back(0.333f); normals.push_back(0.333f);
	normals.push_back(-0.333f); normals.push_back(0.333f); normals.push_back(0.333f);

	//calculate the color depending to the position in the circle
	float hsv[3];
	hsv[0] = 360.0f * ((float)number) / ((float) *n_cubes);
	hsv[1] = 1.0f;
	hsv[2] = 1.0f;

	float rgb[3];
	hsv2rgb(hsv, rgb);

	//setting up the colors
	colors.push_back(rgb[0]); colors.push_back(rgb[1]); colors.push_back(rgb[2]);
	colors.push_back(rgb[0]); colors.push_back(rgb[1]); colors.push_back(rgb[2]);
	colors.push_back(rgb[0]); colors.push_back(rgb[1]); colors.push_back(rgb[2]);
	colors.push_back(rgb[0]); colors.push_back(rgb[1]); colors.push_back(rgb[2]);
	colors.push_back(rgb[0]); colors.push_back(rgb[1]); colors.push_back(rgb[2]);
	colors.push_back(rgb[0]); colors.push_back(rgb[1]); colors.push_back(rgb[2]);
	colors.push_back(rgb[0]); colors.push_back(rgb[1]); colors.push_back(rgb[2]);
	colors.push_back(rgb[0]); colors.push_back(rgb[1]); colors.push_back(rgb[2]);

	//setting up the indices
	indices.push_back(0); indices.push_back(5); indices.push_back(1);
	indices.push_back(0); indices.push_back(4); indices.push_back(5);
	indices.push_back(0); indices.push_back(7); indices.push_back(4);
	indices.push_back(0); indices.push_back(3); indices.push_back(7);
	indices.push_back(7); indices.push_back(3); indices.push_back(6);
	indices.push_back(3); indices.push_back(2); indices.push_back(6);
	indices.push_back(1); indices.push_back(6); indices.push_back(2);
	indices.push_back(1); indices.push_back(5); indices.push_back(6);
	indices.push_back(5); indices.push_back(4); indices.push_back(7);
	indices.push_back(6); indices.push_back(5); indices.push_back(7);
	indices.push_back(1); indices.push_back(2); indices.push_back(3);
	indices.push_back(1); indices.push_back(3); indices.push_back(0);
	
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(this->vaoID);

	//Filling the vertices buffer
	int locPos = glGetAttribLocation(program, "in_Position");

	glGenBuffers(1, &vertexBuffer);
	glBindVertexArray(vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(locPos); //
	glVertexAttribPointer((GLuint)locPos, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	
	//Filling the colors buffer
	int locColor = glGetAttribLocation(program, "in_Color");

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(locColor); //
	glVertexAttribPointer((GLuint)locColor, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	
	//Filling the normals buffer
	int locNorm = glGetAttribLocation(program, "in_Normal");

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(locNorm); //
	glVertexAttribPointer((GLuint)locNorm, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	
	// Generate a buffer for the indices
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Cube::draw()
{
	glUseProgram(program);
	glBindVertexArray(vaoID);

	float angle = 2 * M_PI / (*n_cubes);
	glm::mat4 tMVP = glm::translate(glm::mat4(1.0f), glm::vec3(radius * cos(angle * number), 0.0f, radius * sin(angle * number)));

	int M_loc = glGetUniformLocation(program, "M"); // Get the location of our MVP in the shader
	glUniformMatrix4fv(M_loc, 1, GL_FALSE, glm::value_ptr(tMVP)); // Send our model matrix to the shader

	tMVP = (*MVP) * tMVP;

	int MVP_loc = glGetUniformLocation(program, "MVP"); // Get the location of our MVP in the shader
	glUniformMatrix4fv(MVP_loc, 1, GL_FALSE, glm::value_ptr(tMVP)); // Send our model * view * matrix to the shader

	// buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);	

	glBindVertexArray(0);

	glUseProgram(0);
}

void Cube::initShader(GLuint fs, GLuint vs)
{
	// This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
	program = glCreateProgram();

	// We'll attach our two compiled shaders to the OpenGL program.
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	glUseProgram(program);
	glBindAttribLocation(program, 0, "in_Position");
	glBindAttribLocation(program, 1, "in_Color");
	glBindAttribLocation(program, 2, "in_Normal");
	glUseProgram(0);

	init();
}