#pragma once
#include "EditorGUI/IEditorGUI.hpp"
#include "PhosCore/Camera.hpp"
#include "PhosCore/Scene.hpp"

namespace EditorGUI
{
	class SceneGUI : public IEditorGUI
	{
	public:
		SceneGUI() : IEditorGUI("Scene") {}

		void DoUpdate() override;
	private:
		LowRenderer::Camera m_sceneCamera;
		Engine::Scene* m_currentScene;

	};
}


