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
	m_currentScene->GetRenderer()->RenderAll(nullptr, Maths::Vec2(p_size.x, p_size.y - 37), true);

	if (m_currentScene->GetRenderer()->GetCameraList().size())
	{
		LowRenderer::CameraComponent* cam = m_currentScene->GetRenderer()->GetCameraList()[0];

		Wrapper::GUI::Image(cam->GetRenderTexture(), Maths::Vec2(p_size.x, p_size.y - 37));
	}
}
