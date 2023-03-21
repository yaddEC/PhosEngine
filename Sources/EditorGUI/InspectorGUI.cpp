#include "EditorGUI/InspectorGUI.hpp"
#include "Engine/Transform.hpp"
#include "Wrapper/GUI.hpp"

void EditorGUI::InspectorGUI::DoUpdate()
{
	float min = Maths::Min(3.5f, 2.5f);
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


	GUI::DisplayText(m_gameobject->name);
	GUI::Separator();
	if (GUI::CollapsingHeader("Transform"))
	{
		m_gameobject->transform->OnGUI();
	}
}

void EditorGUI::InspectorGUI::DisplayResource()
{
	if (!m_resource) return;

}
