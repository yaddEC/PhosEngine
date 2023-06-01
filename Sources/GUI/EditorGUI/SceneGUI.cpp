#include "GUI/EditorGUI/SceneGUI.hpp"
#include "Engine/Transform.hpp"
#include "Resource/ResourceManager.hpp"
#include "LowRenderer/Renderer.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Engine/GameObject.hpp"
#include "Wrapper/RHI.hpp"
#include "Wrapper/Window.hpp"
#include "imgui.h"
#include "imgui_internal.h"
using namespace Maths; 
using namespace Wrapper;
using namespace EditorGUI;
using namespace Engine;


void RemoveParentTranslation(Vec3& position, Transform* transform)
{
	position -= transform->position;
	if (transform->GetParent())
		RemoveParentTranslation(position, transform->GetParent());
}

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
			m_speedModifier = 0.001f;
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
	return m_selectedObject;
}

Engine::GameObject* EditorGUI::SceneGUI::FindSelectedObject(unsigned int ID)
{
	if (ID == 0) return nullptr;
	std::vector<Engine::GameObject*> GObject = m_currentScene->GetGameObjects();
	for (int i = 0; i < GObject.size(); i++)
	{
		if (GObject[i]->GetID() == ID)
		{
			//m_selectedId = 0;
			return GObject[i];
		}
	}
	return nullptr;
}


void EditorGUI::SceneGUI::DeselectCurrentObject()
{
	m_selectedObject = nullptr;
	m_selectedRenderer = nullptr;
}

void SceneGUI::DoUpdate()
{
	using namespace Wrapper;
	selectedClicked = false;
	Input& input = Input::GetInstance();

	if (p_isOnFocus)
	{
		
		UpdateCamera(input);
		if (input.IsMouseButtonReleased(GLFW_MOUSE_BUTTON_1) && GUI::IsWindowHovered() && !m_guizmoSelected)
		{
			unsigned int objectID = m_currentScene->GetRenderer()->IdPicker(&m_sceneCamera, p_size - Vec2(10, 35),
			GUI::GetWindowPos(*Window::GetCurrentContext()));
			m_selectedObject = FindSelectedObject(objectID);
			if (m_selectedObject)
			{
				m_selectedRenderer = m_selectedObject->GetComponent<LowRenderer::MeshRenderer>();
				selectedClicked = true;
			}
			else 
			{
				DeselectCurrentObject();
			}
		}
		if (input.IsKeyDown(GLFW_KEY_C))
			m_displayShapeGizmo = !m_displayShapeGizmo;


	}

	Maths::Vec2 cursorPos = GUI::GetCursorPos();

	if (m_currentScene) 
	{
		m_sceneCamera.ClearBuffers(p_size - Vec2(10, 35));
		//m_currentScene->GetRenderer()->RenderCollider(&m_sceneCamera, m_currentScene, p_size - Vec2(10, 35));

		if (m_displayShapeGizmo)
		{
			for (Engine::GameObject* go : m_currentScene->GetGameObjects())
			{
				for (Engine::MonoBehaviour* component : go->GetComponents())
				{
					component->OnGizmo();
				}
			}
			m_currentScene->GetRenderer()->DrawGizmo(&m_sceneCamera, p_size - Vec2(10, 35));
		}
		

		m_currentScene->GetRenderer()->RenderAll(&m_sceneCamera, p_size - Vec2(10, 35), false);
		m_currentScene->GetRenderer()->RenderIcon(&m_sceneCamera, p_size - Vec2(10, 35));
	}
	if (m_selectedRenderer)
	{
		m_selectedRenderer->RenderOutline(m_sceneCamera.GetViewMatrix() * m_sceneCamera.GetProjMatrix());
	}

	GUI::SameLine();

	if (m_drawCameraData)
	{
		m_sceneCamera.OnGUI();
	}

	GUI::Image(m_sceneCamera.GetRenderTexture(), Maths::Vec2(p_size.x , p_size.y - 35));
	GameObject* selected = GetSelected();
	static GameObject* lastSelected;
	if (selected != nullptr )
	{
		if(input.IsMouseButtonUp(GLFW_MOUSE_BUTTON_2))
		{ 
			if (input.IsKeyPressed(87) )
				gizMode = 0;//TRANSLATE
			else if (input.IsKeyPressed(69))
				gizMode = 1;//ROTATE
			else if (input.IsKeyPressed(82))
				gizMode = 2;//SCALE
		}
		float* temp = selected->transform->GetGlobalMatrix().GetTranspose().data;

		if(m_guizmoSelected && input.IsMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
			m_guizmoSelected = false;

		if (GUI::drawGizmo(gizMode, m_sceneCamera.GetViewMatrix().GetTranspose().data, m_sceneCamera.GetProjMatrix().GetTranspose().data, temp, false) && (selected == lastSelected ))
		{
			
			Vec3 position;
			Vec3 rotation;
			Vec3 scale;
			m_guizmoSelected = true;


			GUI::GizmoDecomposeMatrixToComponents(temp, position.xyz, rotation.xyz, scale.xyz);

			if (selected->transform->GetParent())
			{
				RemoveParentTranslation(position, selected->transform->GetParent());

				rotation = rotation - (selected->transform->GetParent()->rotationEuler * RAD2DEG);
				//position = position - selected->transform->GetParent()->position;

			}



			if (selected->transform->position != position && gizMode!=1)
			{
				selected->transform->position = position;
			}
			if (selected->transform->scale != scale)
			{
				selected->transform->scale = scale;
			}
			if (selected->transform->rotationEuler != rotation * DEG2RAD)
			{
				selected->transform->rotationEuler = rotation * DEG2RAD;
				Quaternion newQuat = selected->transform->rotation.ToQuaternion(selected->transform->rotationEuler);
				selected->transform->SetRotation(newQuat);
			}
			for (auto& callback : selected->transform->transformChangedCallbacks)
			{
				callback();
			}
			lastSelected = nullptr;
			
		}
		else
		{
				lastSelected = GetSelected();
		}

		
			

		
	}
}

void EditorGUI::SceneGUI::SetSelected(Engine::GameObject* selected)
{
	m_selectedObject = selected;
	if(m_selectedObject)
		m_selectedRenderer = m_selectedObject->GetComponent<LowRenderer::MeshRenderer>();
}
