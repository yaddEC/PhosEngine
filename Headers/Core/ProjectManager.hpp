#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ProjectManagerGUI
{
	class ProjectManagerGUI;
}

namespace Core
{
	class ProjectManager
	{
	public:
		ProjectManager(GLFWwindow* window);
		~ProjectManager();

		bool Init();
		void Run();
		void Destroy();
	private:
		bool InitProjectManagerGUI();
		void UpdateProjectManagerGUI();

		ProjectManagerGUI::ProjectManagerGUI* m_PManagerGUI;

		GLFWwindow* m_window;

	};
}