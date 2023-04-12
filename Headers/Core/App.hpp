#pragma once
#include "imgui.h"


#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Core/ProjectManager.hpp"
#include "Core/Editor.hpp"

namespace Core
{
	class App
	{
	public:
		App();
		~App();

		bool InitApp();
		bool InitProjectManager();
		bool InitEditor();

		void RunProjectManager();
		void RunEditor();

		void DestroyApp();
		void DestroyProjectManager();
		void DestroyEditor();

	private:
		Core::ProjectManager* m_PManager;
		Core::Editor* m_editor;

		GLFWwindow* m_window;
		Maths::Vec2 m_windowSize;
	};
}               