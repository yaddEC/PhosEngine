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
		Maths::Vec2 GetSize() const;
		bool ShouldClose() const;
		void SwapBuffer();
		static void PollEvents();
		WindowAPIType* GetWindow() const { return m_window; }
		Maths::Vec2 GetPos() const;
		void MakeCurrentContext();
		static Window* GetCurrentContext();
		static double GetTime();
		static void SetSwapInterval(bool active);

	private:
		WindowAPIType* m_window;

		static std::unordered_map<WindowAPIType*, Window*> m_windowMap;
	};
}