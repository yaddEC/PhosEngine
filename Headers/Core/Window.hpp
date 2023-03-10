#pragma once

#ifdef WINDOW_EXPORTS
#define WINDOW_API __declspec(dllexport)
#else
#define WINDOW_API __declspec(dllimport)
#endif

#include <GLFW/glfw3.h>


class WINDOW_API Window
{
public:

	~Window();

	Window* Create(const char* windowName, int clientWidth, int clientHeight);
	void Destroy();
	inline GLFWwindow* GetWindow() { return window; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

private:

	GLFWwindow* window;
	const char* name;

	int width, height;

};
