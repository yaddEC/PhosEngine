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

		bool showFps;

	private:
		unsigned int m_frameCount = 0;
		float m_elapsedTime = 0.0f;
		float m_fps;
		void PlayStateButton();
		Engine::Scene* m_currentScene;
	};
}
