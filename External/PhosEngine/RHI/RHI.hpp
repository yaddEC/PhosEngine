#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Maths/Maths.hpp"

#ifdef RHI_EXPORTS
#define RHI_API __declspec(dllexport)
#else
#define RHI_API __declspec(dllimport)
#endif

namespace RHI
{
	GLFWwindow* InitWindow(int width, int height, const char* windowName);
	bool InitGlew();
	void SwapBuffer(GLFWwindow* window);
	Maths::Vec2 GetWindowSize(GLFWwindow* window);
	void PollEvents();
	void DestroyWindow(GLFWwindow* window);
	GLFWwindow* GetCurrentContext();
	void SetCurrentContext(GLFWwindow* window);
}