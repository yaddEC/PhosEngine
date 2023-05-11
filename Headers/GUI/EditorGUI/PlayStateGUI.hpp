#pragma once
#include "GUI/IGUI.hpp"

namespace Engine 
{
	class Scene;
}

namespace EditorGUI
{
	class PlayStateGUI : public APPGUI::IGUI
	{
	public:
		PlayStateGUI();

	
		void setScene(Engine::Scene* currentScene) { m_currentScene = currentScene; };
		void DoUpdate() override;


	private:
		
		void PlayStateButton();
		Engine::Scene* m_currentScene;
	};
}
