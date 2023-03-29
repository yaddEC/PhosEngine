#pragma once
#include "EditorGUI/IEditorGUI.hpp"
#include "LowRenderer/Camera.hpp"
#include "Engine/Scene.hpp"

namespace EditorGUI
{
	class SceneGUI : public IEditorGUI
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


