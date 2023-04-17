#include <utility>
#include <limits>
#include "pch.h"
#include <iostream>

#include "Wrapper/Window.hpp"

bool Wrapper::Window::InitGLFW()
{
	if (!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
		return false;
	}
	return true;
}

void Wrapper::Window::TernimateGLFW()
{
	glfwTerminate();
}

bool Wrapper::Window::InitGlew()
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

bool Wrapper::Window::Init(const Maths::Vec2& size, const std::string& name)
{
	window = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);
	if (!window)
	{
		std::cout << "FAILED TO CREATE A WINDOW" << std::endl;
		return false;
	}
	MakeCurrentContext();
	return true;
}

void Wrapper::Window::Destroy()
{
	glfwDestroyWindow(window);
}

Maths::Vec2 Wrapper::Window::GetSize()
{
	return Maths::Vec2();
}

bool Wrapper::Window::ShouldClose()
{
	return false;
}

void Wrapper::Window::SwapBuffer()
{
}

void Wrapper::Window::PollEvents()
{
}

void Wrapper::Window::MakeCurrentContext()
{
}

Wrapper::Window* Wrapper::Window::GetCurrentContext()
{
	return nullptr;
}
