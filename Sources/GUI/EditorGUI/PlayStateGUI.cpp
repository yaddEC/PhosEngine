#include "GUI/EditorGUI/PlayStateGUI.hpp"
#include "Engine/Scene.hpp"
#include "Wrapper/RHI.hpp"
#include "Wrapper/GUI.hpp"
#include "Engine/Input.hpp"




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
