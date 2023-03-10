// include needed
#include <utility>
#include <limits>
#include "pch.h"

#define WINDOW_EXPORTS
#include "Core/Window.hpp"

Window::~Window()
{
	Destroy();
}

Window* Window::Create(const char* windowName, int clientWidth, int clientHeight)
{
	name = windowName;
	width = clientWidth;
	height = clientHeight;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	return this;
}

void Window::Destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
