#pragma once
#include "GUI/IGUI.hpp"
#include "Engine/Scene.hpp"



namespace EditorGUI
{
	class GameGUI : public APPGUI::IGUI
	{
	public:
		GameGUI();

		void SetCurrentScene(Engine::Scene* newScene) { m_currentScene = newScene; }
		Engine::Scene* GetCurrentScene() { return m_currentScene; };

		void DoUpdate() override;

	private:

		Engine::Scene* m_currentScene;
	};
}
