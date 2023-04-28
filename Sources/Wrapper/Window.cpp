#include <utility>
#include <limits>
#include "pch.h"
#include <iostream>

#include "Wrapper/Window.hpp"

using namespace Wrapper;

std::unordered_map<WindowAPIType*, Window*> Wrapper::Window::m_windowMap;

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
	m_window = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);
	if (!m_window)
	{
		std::cout << "FAILED TO CREATE A WINDOW" << std::endl;
		return false;
	}
	MakeCurrentContext();
	m_windowMap.emplace(m_window, this);
	return true;
}

void Wrapper::Window::Destroy()
{
	glfwDestroyWindow(m_window);
	m_windowMap.erase(m_window);
}

Maths::Vec2 Wrapper::Window::GetSize() const
{
	return Maths::Vec2();
}

bool Wrapper::Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

void Wrapper::Window::SwapBuffer()
{
	glfwSwapBuffers(m_window);
}

void Wrapper::Window::PollEvents()
{
	glfwPollEvents();
}

Maths::Vec2 Wrapper::Window::GetPos() const
{
	int x, y;
	glfwGetWindowPos(m_window, &x, &y);
	return Maths::Vec2(x, y);
}

void Wrapper::Window::MakeCurrentContext()
{
	glfwMakeContextCurrent(m_window);
}

Wrapper::Window* Wrapper::Window::GetCurrentContext()
{
	WindowAPIType* w = glfwGetCurrentContext();
	if (m_windowMap.count(w))
	{
		return m_windowMap[w];
	}
}

double Wrapper::Window::GetTime()
{
	return glfwGetTime();
}

void Wrapper::Window::SetSwapInterval(bool active)
{
	glfwSwapInterval(false);
}
