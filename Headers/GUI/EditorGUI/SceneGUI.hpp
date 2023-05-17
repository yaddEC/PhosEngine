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

		void DoUpdate() override;

		bool selectedClicked;
	
	private:
		void UpdateCamera(Engine::Input& input);
		LowRenderer::Camera m_sceneCamera;
		Engine::Scene* m_currentScene;


		float m_speedModifier;
		unsigned int m_selectedId;
		bool m_drawCameraData = false;
	};
}


