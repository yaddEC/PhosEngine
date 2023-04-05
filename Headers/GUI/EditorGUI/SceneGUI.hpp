#pragma once
#include "GUI/IGUI.hpp"
#include "LowRenderer/Camera.hpp"
#include "Engine/Scene.hpp"

namespace EditorGUI
{
	class SceneGUI : public APPGUI::IGUI
	{
	public:
		SceneGUI();

		void SetCurrentScene(Engine::Scene* newScene) { m_currentScene = newScene; }

		void DoUpdate() override;
	private:
		LowRenderer::Camera m_sceneCamera;
		Engine::Scene* m_currentScene;

	};
}


