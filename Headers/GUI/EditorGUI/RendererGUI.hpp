#pragma once
#include "GUI/IGUI.hpp"
#include "Engine/Scene.hpp"

namespace EditorGUI
{
	class RendererGUI : public APPGUI::IGUI
	{
	public:
		RendererGUI() : IGUI("Renderer", true){}

		void SetCurrentScene(Engine::Scene* newScene) { m_currentScene = newScene; }

		void DoUpdate() override;
	private:
		Engine::Scene* m_currentScene;

	};
}