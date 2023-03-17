#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>




#include "Maths/Maths.hpp"

#ifdef RHI_EXPORTS
#define RHI_API __declspec(dllexport)
#else
#define RHI_API __declspec(dllimport)
#endif

namespace Wrapper 
{
	class RHI_API RHI
	{
	public:
		static GLFWwindow* InitWindow(int width, int height, const char* windowName);
		static bool  InitGlew();

		static bool WindowShouldClose(GLFWwindow* window);
		static void SwapBuffer(GLFWwindow* window);
		static void PollEvents();

		static Maths::Vec2 GetWindowSize(GLFWwindow* window);

		static void DestroyWindow(GLFWwindow* window);

		static GLFWwindow* GetCurrentContext();
		static void SetCurrentContext(GLFWwindow* window);

		static void EnableCulling(); // TEMP
		static void EnableDepthTest(); // TEMP

		//Resource
		static void BindTexture(unsigned int* textureKey, unsigned char* data, int channel, int width, int height);
		static void ResizeTexture(unsigned int* textureKey, int channel, int width, int height);
	};
}