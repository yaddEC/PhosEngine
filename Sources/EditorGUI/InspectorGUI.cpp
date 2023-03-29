#include "EditorGUI/InspectorGUI.hpp"
#include "Engine/Transform.hpp"
#include "Wrapper/GUI.hpp"
#include "Engine/MonoBehaviour.hpp"

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


	GUI::DisplayText(m_gameobject->name);
	GUI::Separator();
	if (GUI::CollapsingHeader("Transform"))
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

}
