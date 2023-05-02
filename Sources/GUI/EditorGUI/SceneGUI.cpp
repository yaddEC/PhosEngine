#include "GUI/EditorGUI/SceneGUI.hpp"
#include "Engine/Transform.hpp"
#include "Resource/ResourceManager.hpp"
#include "LowRenderer/Renderer.hpp"
#include "Engine/GameObject.hpp"
#include "Wrapper/RHI.hpp"
#include "Wrapper/Window.hpp"

using namespace Maths; 
using namespace Wrapper;
using namespace EditorGUI;
using namespace Engine;

SceneGUI::SceneGUI() : IGUI("Scene",true), m_speedModifier(1.000f)
{
	
}

void SceneGUI::UpdateCamera(Input& input)
{
	
	Vec3 direction = Vec3(Vec2(0, 1).GetRotated(Vec2(), -m_sceneCamera.transform->rotationEuler.y), 0);
	Vec3 forward = Vec3(direction.x, 0, direction.y);
	Vec3 left = Vec3(forward.z, 0, -forward.x);


	float speed = 0.4f;

	int scroDel = input.GetScrollDelta();

	if (!input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
	{
		return;
	}
	 m_sceneCamera.transform->rotationEuler += (Vec3(input.GetMouseDelta().y, input.GetMouseDelta().x, 0) * speed * 0.05f) ;
	 m_sceneCamera.transform->rotation = m_sceneCamera.transform->rotation.ToQuaternion(m_sceneCamera.transform->rotationEuler * DEG2RAD);

	if (input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		speed *= 2;

	if (scroDel != 0)
	{
		if (m_speedModifier + scroDel / 10.f <= 0.0001f)
			m_speedModifier /= 10;
		else if (m_speedModifier < 0.1f)
			m_speedModifier *= 10;
		else
			m_speedModifier += ((float)scroDel / 10.f);

		if (m_speedModifier > 2)
			m_speedModifier = 2;
		if (m_speedModifier < 0.001)
			m_speedModifier = 0.001;
	}
	speed *= m_speedModifier;

	//std::cout << speedModifier << std::endl;

	m_sceneCamera.transform->position += forward * input.GetVerticalAxis() * speed;
	m_sceneCamera.transform->position += left * input.GetHorizontalAxis() * speed;

	if (input.IsKeyPressed(GLFW_KEY_E))
		m_sceneCamera.transform->position.y += 1 * speed;
	if (input.IsKeyPressed(GLFW_KEY_Q))
		m_sceneCamera.transform->position.y += -1 * speed;
}

Engine::GameObject* EditorGUI::SceneGUI::GetSelected()
{
	if (m_selectedId == 0) return nullptr;
	std::vector<Engine::GameObject*> GObject = m_currentScene->GetGameObjects();
	for (int i = 0; i < GObject.size(); i++)
	{
		if (GObject[i]->GetID() == m_selectedId)
		{
			//m_selectedId = 0;
			return GObject[i];
		}
	}
	return nullptr;

}

void SceneGUI::DoUpdate()
{
	m_frameCount++;
	m_elapsedTime += Input::deltaTime;
	if (m_elapsedTime >= 1.0f)
	{
		m_fps = static_cast<float>(m_frameCount) / m_elapsedTime;
		m_elapsedTime = 0.0f;
		m_frameCount = 0;
	}
	using namespace Wrapper;
	selectedClicked = false;
	Input& input = Input::GetInstance();

	if (p_isOnFocus)
	{
		UpdateCamera(input);
		if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1) && GUI::IsWindowHovered())
		{
			m_selectedId = m_currentScene->GetRenderer()->IdPicker(&m_sceneCamera, p_size - Vec2(10, 35),
				GUI::GetWindowPos(*Window::GetCurrentContext()));
			selectedClicked = true;
		}

	}

	Maths::Vec2 cursorPos = GUI::GetCursorPos();

	if (m_currentScene) 
	{
		m_currentScene->GetRenderer()->RenderAll(&m_sceneCamera, size - Vec2(10, 35), false);
		m_currentScene->GetRenderer()->RenderIcon(&m_sceneCamera, size - Vec2(10, 35));
	}

	GUI::Image(m_sceneCamera.GetRenderTexture(), Maths::Vec2(p_size.x - 10, p_size.y - 35));
	m_sceneCamera.OnGUI();

	GUI::SetCursorPos(cursorPos + Maths::Vec2(p_size.x / 2 - 10, 0));
	
	
	if (m_currentScene->GetIsGameMode())
	{
		if (GUI::Button("Stop"))
		{
			m_currentScene->StopGameMode();
		}
	}
	else
	{
		if (GUI::Button("Play"))
		{
			m_currentScene->StartGameMode();
		}
	}
	GUI::DisplayText("%.2f FPS", m_fps);
}
