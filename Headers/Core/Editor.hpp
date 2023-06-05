#pragma once

#include "Maths/Maths.hpp"
#include "Engine/Scene.hpp"
#include "Wrapper/Window.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace EditorGUI
{
	class SceneGUI;
	class AssetExplorer;
	class HierarchyGUI;
	class InspectorGUI;
	class RendererGUI;
	class PhysicsSettingsGUI;
	class PlayStateGUI;
	class GeneralSettingsGUI;
	class GameGUI;
	class InputGUI;
	class CanvasEditor;
}


namespace Core
{
	class Editor
	{
	public:

		Editor(Wrapper::Window& window );
		~Editor();

		bool Init();
		void Run();
		void Destroy();
		
	private:
		bool InitEditorGUI();
		void UpdateEditorGUI();
		void Top();

		void CreateGuiIni();

#ifndef PHOS_GAME


		EditorGUI::SceneGUI* m_sceneGUI;
		EditorGUI::GameGUI* m_gameGUI;
		EditorGUI::AssetExplorer* m_AssetExplorer;
		EditorGUI::HierarchyGUI* m_Hierarchy;
		EditorGUI::InspectorGUI* m_Inspector;
		EditorGUI::RendererGUI* m_RendererGUI;
		EditorGUI::PhysicsSettingsGUI* m_PhysicsSettingsGUI;
		EditorGUI::PlayStateGUI* m_PlayStateGUI;
		EditorGUI::GeneralSettingsGUI* m_GeneralSettingsGUI;
		EditorGUI::InputGUI* m_InputGUI;
		EditorGUI::CanvasEditor* m_canvasEditor;

#else


#endif // PHOS_GAME

		Engine::Scene* m_mainScene;

		Wrapper::Window& m_window;

		bool m_vsync;

	};
}


