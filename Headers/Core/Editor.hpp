#pragma once

#include "Maths/Maths.hpp"
#include "Engine/Scene.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include "Window.hpp"


namespace EditorGUI
{
	class SceneGUI;
	class AssetExplorer;
	class HierarchyGUI;
	class InspectorGUI;
	class MenuBar;
	class RendererGUI;
}


namespace Core
{
	class Editor
	{
	public:

		Editor(GLFWwindow* window, Maths::Vec2& windowSize);
		~Editor();

		bool Init();
		void Run();
		void Destroy();

	private:
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
		EditorGUI::MenuBar* m_MenuBar;
		EditorGUI::RendererGUI* m_RendererGUI;

		Engine::Scene* m_mainScene; // TEMP

		GLFWwindow* m_window;
		Maths::Vec2& m_windowSize;

	};
}


