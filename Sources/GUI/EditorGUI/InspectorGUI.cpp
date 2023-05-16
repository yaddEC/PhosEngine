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

	GUI::BeginGroup();
	Wrapper::GUI::DisplayText(m_gameobject->name.c_str());
	
	std::vector<std::string> layerNames = *Wrapper::Physics::GetLayerNames();
	std::string selected = Wrapper::Physics::GetLayerName(m_gameobject->GetLayer());
	if (GUI::Combo("Layer", layerNames, selected))
	{
		m_gameobject->SetLayer(Wrapper::Physics::GetLayerID(selected));
	}
	
	GUI::EndGroup();
	Wrapper::GUI::Separator();
	if (Wrapper::GUI::CollapsingHeader("Transform"))
	{
		m_gameobject->transform->OnGUI();
	}

	for (Engine::MonoBehaviour* component : m_gameobject->GetComponents())
	{
		component->GetMetaData().GUIUpdate(component);
	}
}

void EditorGUI::InspectorGUI::DisplayResource()
{
	if (!m_resource) return;
	Wrapper::GUI::SetWindowFontSize(2.f);
	Wrapper::GUI::DisplayText(m_resource->GetName().c_str());
	Wrapper::GUI::SetWindowFontSize(1);
	Wrapper::GUI::SetCursorPos(Wrapper::GUI::GetCursorPos() + Maths::Vec2(0, 5));
	Wrapper::GUI::Separator();
	m_resource->GUIUpdate();
}
