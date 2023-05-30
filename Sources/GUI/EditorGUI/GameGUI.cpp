#include "GUI/EditorGUI/GameGUI.hpp"
#include "Wrapper/GUI.hpp"
#include "LowRenderer/Renderer.hpp"
#include "LowRenderer/CameraComponent.hpp"

EditorGUI::GameGUI::GameGUI()
	: IGUI("Game", true)
{

}

void EditorGUI::GameGUI::DoUpdate()
{

	int cameraCount = m_currentScene->GetRenderer()->GetCameraList().size();
	if (!cameraCount)
		return;

	switch (cameraCount)
	{
	case 1: 
	{
		m_currentScene->GetRenderer()->RenderAll(nullptr, Maths::Vec2(p_size.x, p_size.y - 42), true);
		LowRenderer::CameraComponent* cam = m_currentScene->GetRenderer()->GetCameraList()[0];
		Wrapper::GUI::Image(cam->GetRenderTexture(), Maths::Vec2(p_size.x, p_size.y - 42));
		break;
	}
		

	case 2: 
	{
		m_currentScene->GetRenderer()->RenderAll(nullptr, Maths::Vec2(p_size.x / 2.f, p_size.y - 42), true);
		LowRenderer::CameraComponent* cam1 = m_currentScene->GetRenderer()->GetCameraList()[0];
		LowRenderer::CameraComponent* cam2 = m_currentScene->GetRenderer()->GetCameraList()[1];
		Wrapper::GUI::Image(cam1->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, p_size.y - 42));
		Wrapper::GUI::SameLine();
		Wrapper::GUI::Image(cam2->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, p_size.y - 42));
		break;
	}
		

	default: break;
	}

	
}
