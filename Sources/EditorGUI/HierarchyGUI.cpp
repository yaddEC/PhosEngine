#include "EditorGUI/HierarchyGUI.hpp"
#include "Wrapper/GUI.hpp"
#include "Engine/Transform.hpp"

EditorGUI::HierarchyGUI::HierarchyGUI() : IEditorGUI("Hierarchy", true)
{

}

void EditorGUI::HierarchyGUI::DoUpdate()
{
	m_selectedClicked = false;
	std::vector<Engine::GameObject*> goList = m_currentScene->GetGameObjects();
	for (Engine::GameObject* go : goList)
	{
		if (go->transform->GetParent() == nullptr)
		{
			DisplayHierarchy(go);
		}
	}
	
}

Engine::GameObject* EditorGUI::HierarchyGUI::GetSelected()
{
	if (m_selectedClicked)
		return m_selected;
	else
		return nullptr;
}

void EditorGUI::HierarchyGUI::DisplayHierarchy(Engine::GameObject* current)
{
	std::vector<Engine::Transform*> children = current->transform->GetChildren();
	bool opened = GUI::TreeNode(current->name, m_selected == current, children.size() == 0);
			
	if (GUI::BeginPopupContextItem("Test"))
	{
		GUI::DisplayText("Example text");
		GUI::EndPopup();
	}
	
	if (GUI::IsItemClicked(1)) GUI::OpenPopup("Test");
	if (GUI::IsItemClicked(0))
	{
		m_selected = current;
		m_selectedClicked = true;
	}

	if (opened)
	{
		for (auto child : children)
		{
			DisplayHierarchy(child->GetGameObject());
		}

		GUI::TreePop();
	}
}
