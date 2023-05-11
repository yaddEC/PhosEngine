
#include "GUI/IGUI.hpp"
#include "Engine/Scene.hpp"
#include "Engine/Input.hpp"


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
