#include "GUI/EditorGUI/PlayStateGUI.hpp"
#include "Wrapper/RHI.hpp"
#include "Wrapper/GUI.hpp"



EditorGUI::PlayStateGUI::PlayStateGUI()
	: IGUI("PlayState", true,true,false)
{
	m_currentScene = nullptr;
	isOpen = true;
}

void EditorGUI::PlayStateGUI::DoUpdate()
{
	PlayStateButton();
}

void EditorGUI::PlayStateGUI::PlayStateButton()
{
	m_frameCount++;
	m_elapsedTime += Engine::Input::deltaTime;
	if (m_elapsedTime >= 1.0f)
	{
		m_fps = static_cast<float>(m_frameCount) / m_elapsedTime;
		m_elapsedTime = 0.0f;
		m_frameCount = 0;
	}
	if(showFps)
		Wrapper::GUI::DisplayText("%.2f FPS", m_fps);
	Wrapper::GUI::BeginGroupCentered((0, 20));
	if (m_currentScene->GetIsGameMode())
	{
		if (Wrapper::GUI::Button(u8"\u2009\u2009\u25A0\u2009"))
		{
			m_currentScene->StopGameMode();
		}
	}
	else
	{
		if (Wrapper::GUI::Button(u8"\u2009\u25BA"))
		{
			m_currentScene->StartGameMode();
		}
	}
	Wrapper::GUI::SameLine();
	if (Wrapper::GUI::Button(u8" \u2009\u258D \u258D ")) {}
	Wrapper::GUI::EndGroup();
	
}
