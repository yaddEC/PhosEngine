#pragma once

#ifdef WINDOW_EXPORTS
#define WINDOW_API __declspec(dllexport)
#else
#define WINDOW_API __declspec(dllimport)
#endif

#include <GLFW/glfw3.h>

namespace Core
{
	class WINDOW_API Window
	{
	public:

		
		~Window();

		bool Create(const char* windowName, int clientWidth, int clientHeight);
		void Destroy();
		void Update();

		inline GLFWwindow* GetWindow() { return window; }
		int GetWidth() { return width; }
		int GetHeight() { return height; }

	private:

		GLFWwindow* window;
		const char* name;

		int width, height;

	};
}



