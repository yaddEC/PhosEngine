#pragma once
#include "EditorGUI/IEditorGUI.hpp"
#include "Engine/Scene.hpp"

namespace EditorGUI
{
	class RendererGUI : public IEditorGUI
	{
	public:
		RendererGUI() : IEditorGUI("Renderer", true){}

		void SetCurrentScene(Engine::Scene* newScene) { m_currentScene = newScene; }

		void DoUpdate() override;
	private:
		Engine::Scene* m_currentScene;

	};
}
