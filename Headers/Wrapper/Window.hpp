#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

#include "Maths/Maths.hpp"
#include "dllInclude.hpp"


namespace Wrapper
{
	using WindowAPIType = GLFWwindow;


	class PHOSENGINE_API Window
	{
	public:
		static bool InitGLFW();
		static void TernimateGLFW();
		static bool InitGlew();

		bool Init(const Maths::Vec2& size, const std::string& name);
		void Destroy();
		Maths::Vec2 GetSize();
		bool ShouldClose();
		void SwapBuffer();
		void PollEvents();

		void MakeCurrentContext();
		static Window* GetCurrentContext();

	private:
		WindowAPIType* window;

		static std::unordered_map<WindowAPIType*, Window> windowMap;
	};
}