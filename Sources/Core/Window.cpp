
// include needed
#include <utility>
#include <limits>
#include "pch.h"

#define WINDOW_EXPORTS
#include "Core/Window.hpp"

Core::Window::~Window()
{
}

bool Core::Window::Create(const char* windowName, int clientWidth, int clientHeight)
{
	name = windowName;
	width = clientWidth;
	height = clientHeight;

	/* Initialize the library */
	if (!glfwInit())
	{
		return false;
	}

	window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (!window) return false;
	return true;
}

void Core::Window::Destroy()
{
	glfwDestroyWindow(window);
}

void Core::Window::Update()
{
	glfwGetWindowSize(window, &width, &height);
}
