#include "GUI/EditorGUI/HierarchyGUI.hpp"
#include "Wrapper/GUI.hpp"
#include "Engine/Transform.hpp"
#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "LowRenderer/Light/SpotLight.hpp"
#include "LowRenderer/MeshRenderer.hpp"

using namespace Wrapper;

EditorGUI::HierarchyGUI::HierarchyGUI() : IGUI("Hierarchy", true)
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
	bool opened = Wrapper::GUI::TreeNode(current->name, m_selected == current, children.size() == 0);
			
	if (GUI::BeginPopupContextItem("GameObject Popup"))
	{
		GUI::DisplayText("Add GameObject");
		GUI::Separator();
		if (GUI::Selectable("Empty", false))
		{
			Engine::GameObject* newObject = new Engine::GameObject();
			newObject->name = "New GameObject";
			m_currentScene->Instantiate(newObject);
		}
		if(GUI::BeginMenu("Light"))
		{
			if (GUI::Selectable("Directional Light", false))
			{
				Engine::GameObject* newObject = new Engine::GameObject();
				newObject->name = "Directional Light";
				newObject->AddComponent<LowRenderer::DirectionalLight>();
				m_currentScene->Instantiate(newObject);
			}
			if (GUI::Selectable("Point Light", false))
			{

			}
			if (GUI::Selectable("Spot Light", false))
			{

			}
			GUI::EndMenu();
		}
		if (GUI::BeginMenu("3D Object"))
		{
			if (GUI::Selectable("Cube", false))
			{
				Engine::GameObject* newObject = new Engine::GameObject();
				newObject->name = "Cube";
				newObject->AddComponent<LowRenderer::MeshRenderer>();
				m_currentScene->Instantiate(newObject);
			}
			if (GUI::Selectable("Sphere", false))
			{

			}
			if (GUI::Selectable("Capsule", false))
			{

			}

			GUI::EndMenu();
		}
		GUI::Separator();
		if (GUI::Selectable("Delete", false))
		{

		}

		GUI::EndPopup();
	}

	if (GUI::IsItemClicked(1))
	{
		GUI::OpenPopup("GameObject Popup");
	}
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
