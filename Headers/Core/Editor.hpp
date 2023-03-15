#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include "Window.hpp"


namespace EditorGUI
{
	class SceneGUI;
}

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

		bool InitImGui();
		bool InitEditorGUI();
		bool InitGLFWWindow();
		bool InitGlew();

		void ImGuiNewFrame();
		void RenderImGuiFrame();
		void UpdateEditorGUI();
		//class Scene* mainScene; // TEMP : load scene eventually
		//class SceneWindow* sceneWindow;
		//class AssetsExplorer* assetsExplorer;

		EditorGUI::SceneGUI* sceneGUI;

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


