// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>

#define RHI_EXPORTS
#include "RHI/RHI.hpp"

GLFWwindow* RHI::InitWindow(int width, int height, const char* windowName)
{
	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
		return nullptr;
	}

	GLFWwindow* window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
	if (!window)
	{
		std::cout << "FAILED TO CREATE A WINDOW" << std::endl;
		return nullptr;
	}
	SetCurrentContext(window);

	return window;
}

bool RHI::InitGlew()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return false;
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	return true;
}

bool RHI::WindowShouldClose(GLFWwindow* window)
{
	return glfwWindowShouldClose(window);
}

void RHI::SwapBuffer(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

Maths::Vec2 RHI::GetWindowSize(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return Maths::Vec2(width, height);
}

void RHI::PollEvents()
{
	glfwPollEvents();
}

void RHI::DestroyWindow(GLFWwindow* window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* RHI::GetCurrentContext()
{
	return glfwGetCurrentContext();
}

void RHI::SetCurrentContext(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
}

void RHI::EnableCulling()
{
	glEnable(GL_CULL_FACE);
}

void RHI::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}
