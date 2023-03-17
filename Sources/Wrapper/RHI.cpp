// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>

#define RHI_EXPORTS
#include "Wrapper/RHI.hpp"

using namespace Wrapper;

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

void RHI::BindTexture(unsigned int* textureKey, unsigned char* data, int channel, int width, int height)
{
	glGenTextures(1, textureKey);
	glBindTexture(GL_TEXTURE_2D, *textureKey);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		if (channel == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		if (channel == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		if (channel == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		if (channel == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Wrapper::RHI::ResizeTexture(unsigned int* textureKey, int channel, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, *textureKey);

	if (channel == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	if (channel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
}
