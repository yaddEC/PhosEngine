#include "GUI/EditorGUI/InspectorGUI.hpp"
#include "Engine/Transform.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"
#include "Engine/MonoBehaviour.hpp"
#include <typeinfo>


using namespace Wrapper;

EditorGUI::InspectorGUI::InspectorGUI() : IGUI("Inspector", true)
{

}

void EditorGUI::InspectorGUI::DoUpdate()
{
	if (m_typeToDisplay == ObjectType::GAME_OBJECT)
	{
		DisplayGameObject();
	}
	else if (m_typeToDisplay == ObjectType::RESOURCE)
	{
		DisplayResource();
	}
}


void EditorGUI::InspectorGUI::DisplayGameObject()
{
	if (!m_gameobject) return;

	if (GUI::Button("Display class info"))
	{
		for (Engine::MonoBehaviour* component : m_gameobject->GetComponents())
		{
			component->GetMetaData().DisplayClassInfo(component);
		}
	}


	Wrapper::GUI::DisplayText(m_gameobject->name);
	Wrapper::GUI::Separator();
	if (Wrapper::GUI::CollapsingHeader("Transform"))
	{
		m_gameobject->transform->OnGUI();
	}

	for (Engine::MonoBehaviour* component : m_gameobject->GetComponents())
	{
		//component->GUIUpdate();
		component->GetMetaData().GUIUpdate(component);
	}
}

void EditorGUI::InspectorGUI::DisplayResource()
{
	if (!m_resource) return;
	Wrapper::GUI::SetWindowFontSize(2.f);
	Wrapper::GUI::DisplayText(m_resource->GetName());
	Wrapper::GUI::SetWindowFontSize(1);
	Wrapper::GUI::SetCursorPos(Wrapper::GUI::GetCursorPos() + Maths::Vec2(0, 5));
	Wrapper::GUI::Separator();
	m_resource->GUIUpdate();
}
