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
		Engine::GameObject* GetSelected();

		void DoUpdate() override;

		bool selectedClicked;
	private:
		void UpdateCamera(Engine::Input& input);
		LowRenderer::Camera m_sceneCamera;
		Engine::Scene* m_currentScene;
		unsigned int frameCount = 0;
		float elapsedTime = 0.0f;
		float fps ;

		float speedModifier;
		unsigned int m_selectedId;
	};
}


