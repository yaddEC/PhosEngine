#pragma once
#include "GUI/IGUI.hpp"
#include "LowRenderer/Camera.hpp"
#include "Engine/Scene.hpp"
#include "Engine/Input.hpp"


namespace EditorGUI
{
	class SceneGUI : public APPGUI::IGUI
	{
	public:
		SceneGUI();

		void SetCurrentScene(Engine::Scene* newScene) { m_currentScene = newScene; }
		Engine::Scene* GetCurrentScene() { return m_currentScene; };
		Engine::GameObject* GetSelected();
		bool GetDebugCamera() { return m_drawCameraData; };
		void SetDebugCamera(bool setter) { m_drawCameraData = setter; }
		void DeselectCurrentObject();
		void DoUpdate() override;
		void SetSelected(Engine::GameObject* selected);
		bool selectedClicked;
		int gizMode = 0;
	private:

		Engine::GameObject* FindSelectedObject(unsigned int ID);
		void UpdateCamera(Engine::Input& input);
		LowRenderer::Camera m_sceneCamera;
		Engine::Scene* m_currentScene;

		Engine::GameObject* m_selectedObject;
		LowRenderer::MeshRenderer* m_selectedRenderer;
		bool m_displayShapeGizmo = false;

		float m_speedModifier;
		bool m_drawCameraData = false;
		bool m_guizmoSelected;
	};
}


