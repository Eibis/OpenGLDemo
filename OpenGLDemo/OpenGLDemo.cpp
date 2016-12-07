//Author: Matteo Bevan
//Contact: matteo.bevan@gmail.com

#include "stdafx.h"
#include<iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include "CubeHandler.h"

#define M_PI 3.14159265358979323846f

//Main function
int main(int argc, char **argv)
{
	if (!glfwInit())
	{
		std::cout << "GLFW Initialization failed!";
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Opengl Demo", NULL, NULL);

	if (!window)
	{
		std::cout << "Error creating the window!";
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	// Makes sure all extensions will be exposed in GLEW and initialize GLEW.
	glewExperimental = GL_TRUE;

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	
	//glewinit throws a fake error, let's remove it
	glGetError();

	// Set up our background color
	static const GLfloat clear_color[] = { 0.0f, 0.15f, 0.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);
	
	/* Adjust cube position to be asthetic angle. */
	glm::mat4 proj = glm::perspective(40.0f, 800.0f / 600.0f, 1.0f, 100.0f);

	glm::mat4 model = glm::mat4(1.0f);

	float cameraRadius = -12.0f;
	float y = 5.0f;

	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f, y, cameraRadius),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 mvp = proj * view * model;

	CubeHandler cubeHandler;
	cubeHandler.init(&mvp);

	float i = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		float z = cameraRadius * cos(i / 2000);
		float x = cameraRadius * sin(i / 2000);

		i++;

		if (i > 2 * M_PI * 2000)
			i = 0.0f;

		view = glm::lookAt(
			glm::vec3(x, y, z),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

		mvp = proj * view * model;

		// Clear the entire buffer with our green color (sets the background to be green).
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);

		cubeHandler.draw();

		// Swap the buffers so that what we drew will appear on the screen.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	
	return 0;
}