#include "GUI/EditorGUI/GameGUI.hpp"
#include "Wrapper/GUI.hpp"
#include "LowRenderer/Renderer.hpp"
#include "LowRenderer/CameraComponent.hpp"
#include "Wrapper/Window.hpp"

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
		cam->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam->GetRenderTexture(), Maths::Vec2(p_size.x, p_size.y - 42));
		break;
	}
		

	case 2: 
	{
		m_currentScene->GetRenderer()->RenderAll(nullptr, Maths::Vec2(p_size.x / 2.f, p_size.y - 42), true);
		LowRenderer::CameraComponent* cam1 = m_currentScene->GetRenderer()->GetCameraList()[0];
		LowRenderer::CameraComponent* cam2 = m_currentScene->GetRenderer()->GetCameraList()[1];
		cam1->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam1->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, p_size.y - 42));
		Wrapper::GUI::SameLine();
		cam2->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam2->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, p_size.y - 42));
		break;
	}

	case 3:
	{
		m_currentScene->GetRenderer()->RenderAll(nullptr, Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f), true);
		LowRenderer::CameraComponent* cam1 = m_currentScene->GetRenderer()->GetCameraList()[0];
		LowRenderer::CameraComponent* cam2 = m_currentScene->GetRenderer()->GetCameraList()[1];
		LowRenderer::CameraComponent* cam3 = m_currentScene->GetRenderer()->GetCameraList()[2];
		cam1->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam1->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		Wrapper::GUI::SameLine();
		cam2->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam2->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		cam3->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam3->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		break;
	}

	case 4:
	{
		m_currentScene->GetRenderer()->RenderAll(nullptr, Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f), true);
		LowRenderer::CameraComponent* cam1 = m_currentScene->GetRenderer()->GetCameraList()[0];
		LowRenderer::CameraComponent* cam2 = m_currentScene->GetRenderer()->GetCameraList()[1];
		LowRenderer::CameraComponent* cam3 = m_currentScene->GetRenderer()->GetCameraList()[2];
		LowRenderer::CameraComponent* cam4 = m_currentScene->GetRenderer()->GetCameraList()[3];
		cam1->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam1->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		Wrapper::GUI::SameLine();
		cam2->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam2->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		cam3->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam3->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		Wrapper::GUI::SameLine();
		cam4->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam4->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		break;
	}


	default:
		m_currentScene->GetRenderer()->RenderAll(nullptr, Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f), true);
		LowRenderer::CameraComponent* cam1 = m_currentScene->GetRenderer()->GetCameraList()[0];
		LowRenderer::CameraComponent* cam2 = m_currentScene->GetRenderer()->GetCameraList()[1];
		LowRenderer::CameraComponent* cam3 = m_currentScene->GetRenderer()->GetCameraList()[2];
		LowRenderer::CameraComponent* cam4 = m_currentScene->GetRenderer()->GetCameraList()[3];
		cam1->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam1->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		Wrapper::GUI::SameLine();
		cam2->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam2->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		cam3->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam3->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		Wrapper::GUI::SameLine();
		cam4->windowPos = Wrapper::GUI::GetCursorPos() + Wrapper::GUI::GetWindowPos();
		Wrapper::GUI::Image(cam4->GetRenderTexture(), Maths::Vec2(p_size.x / 2.f, (p_size.y - 42) / 2.f));
		break;
	
	}

	
}
