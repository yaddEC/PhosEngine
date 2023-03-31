#include "EditorGUI/InspectorGUI.hpp"
#include "Engine/Transform.hpp"
#include "Wrapper/GUI.hpp"
#include "Engine/MonoBehaviour.hpp"
#include <typeinfo>

EditorGUI::InspectorGUI::InspectorGUI() : IEditorGUI("Inspector", true)
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


	Wrapper::GUI::DisplayText(m_gameobject->name);
	Wrapper::GUI::Separator();
	if (Wrapper::GUI::CollapsingHeader("Transform"))
	{
		m_gameobject->transform->OnGUI();
	}

	for (Engine::MonoBehaviour* component : m_gameobject->GetComponents())
	{
		component->GUIUpdate();
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
