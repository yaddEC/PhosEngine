#pragma once

#include "imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Maths/Maths.hpp"
#include "Engine/Scene.hpp"

//#include "Window.hpp"


namespace EditorGUI
{
	class SceneGUI;
	class AssetExplorer;
	class HierarchyGUI;
	class InspectorGUI;
}



namespace Core
{
	class Editor
	{
	public:

		Editor()
			:m_io(GetIO())
		{}

		bool Init();
		void Run();
		void Destroy();

		GLFWwindow* GetWindow() { return m_window; }

	private:

		bool InitImGui();
		bool InitEditorGUI();
		void UpdateEditorGUI();

		//Only if not existing
		void CreateGuiIni();

		//class SceneWindow* sceneWindow;
		//class AssetsExplorer* assetsExplorer;

		EditorGUI::SceneGUI* m_sceneGUI;
		EditorGUI::AssetExplorer* m_AssetExplorer;
		EditorGUI::HierarchyGUI* m_Hierarchy;
		EditorGUI::InspectorGUI* m_Inspector;

		Engine::Scene* m_mainScene; // TEMP

		ImGuiIO& m_io;

		GLFWwindow* m_window;
		Maths::Vec2 m_windowSize;


		ImGuiIO& GetIO()
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			return ImGui::GetIO();
		}
	};
}


