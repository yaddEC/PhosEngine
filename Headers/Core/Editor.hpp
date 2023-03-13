#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "EditorGUI/SceneGUI.hpp"


namespace Core
{
	class Editor
	{
	public:

		Editor()
			:io(GetIO()) {}



		bool Init();
		void Run();
		void Destroy();

		GLFWwindow* GetWindow() { return window; }

	private:

		//class Scene* mainScene; // TEMP : load scene eventually
		//class SceneWindow* sceneWindow;
		//class AssetsExplorer* assetsExplorer;

		SceneGUI* sceneGUI;

		ImGuiIO& io;

		GLFWwindow* window;
		int width, height;


		ImGuiIO& GetIO()
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			return ImGui::GetIO();
		}
	};
}


