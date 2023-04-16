#include "GUI/EditorGUI/HierarchyGUI.hpp"
#include "Engine/Transform.hpp"
#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "LowRenderer/Light/SpotLight.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ResourceIncludes.hpp"




using namespace Wrapper;

EditorGUI::HierarchyGUI::HierarchyGUI() : IGUI("Hierarchy", true)
{

}

void EditorGUI::HierarchyGUI::DoUpdate()
{
	selectedClicked = false;

	AddObjectPopup(nullptr);
	bool opened = GUI::TreeNode("Scene Root", false);

	if (GUI::IsItemClicked(1))
		GUI::OpenPopup("GameObject Popup null");

	if(opened)
	{
		std::vector<Engine::GameObject*> goList = m_currentScene->GetGameObjects();
		for (Engine::GameObject* go : goList)
		{
			//if (go->transform->GetParent() == nullptr)
			{
				DisplayHierarchy(go);
			}
		}
		GUI::TreePop();
	}


	for (auto objectPair : objectToParentBuffer)
	{
		objectPair.first->transform->AddChild(objectPair.second->transform);
	}
	objectToParentBuffer.clear();
}

Engine::GameObject* EditorGUI::HierarchyGUI::GetSelected()
{
	if (selectedClicked)
		return m_selected;
	else
		return nullptr;
}

void EditorGUI::HierarchyGUI::DisplayHierarchy(Engine::GameObject* current)
{
	std::vector<Engine::Transform*> children = current->transform->GetChildren();
	//GUI::PushID(current->GetID());
	bool opened = GUI::TreeNode(current->name + "##" + std::to_string(current->GetID()), m_selected == current, children.size() == 0);
			
	AddObjectPopup(current);

	if (GUI::IsItemClicked(0))
	{
		m_selected = current;
		selectedClicked = true;
	}
	if (GUI::IsItemClicked(1))
		GUI::OpenPopup("GameObject Popup " + current->name);

	GUI::DragDropSource("GameObject", current->name, &current);

	if (Engine::GameObject** newChild = (Engine::GameObject**)GUI::DragDropTarget("GameObject"))
	{
		objectToParentBuffer.push_back(std::pair(current, *newChild));
	}

	if (Resource::Prefab** newChild = (Resource::Prefab**)GUI::DragDropTarget("Prefab"))
	{
		auto goList = (*newChild)->GetCopy();
		for (auto go : goList)
		{
			m_currentScene->Instantiate(go);
		}
		//Engine::GameObject* go = m_currentScene->InstantiatePrefab(**newChild);
		//objectToParentBuffer.push_back(std::pair(current, goList.at(0)));
	}

	//GUI::PopID();

	if (opened)
	{
		for (auto child : children)
		{
			DisplayHierarchy(child->GetGameObject());
		}

		GUI::TreePop();
	}
}

void EditorGUI::HierarchyGUI::AddObjectPopup(Engine::GameObject* current)
{
	if (GUI::BeginPopupContextItem("GameObject Popup " + (current ? current->name : "null")))
	{
		Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();

		GUI::DisplayText("Add GameObject");
		GUI::Separator();
		if (GUI::Selectable("Empty", false))
		{
			Engine::GameObject* newObject = new Engine::GameObject();
			newObject->name = "New GameObject";
			if (current) newObject->transform->SetParent(current->transform);
			m_currentScene->Instantiate(newObject);
		}
		if (GUI::BeginMenu("Light"))
		{
			if (GUI::Selectable("Directional Light", false))
			{
				Engine::GameObject* newObject = new Engine::GameObject();
				newObject->name = "Directional Light";
				if (current) newObject->transform->SetParent(current->transform);
				newObject->AddComponent<LowRenderer::DirectionalLight>();
				m_currentScene->Instantiate(newObject);
			}
			if (GUI::Selectable("Point Light", false))
			{
				Engine::GameObject* newObject = new Engine::GameObject();
				newObject->name = "Point Light";
				if (current) newObject->transform->SetParent(current->transform);
				newObject->AddComponent<LowRenderer::PointLight>();
				m_currentScene->Instantiate(newObject);
			}
			if (GUI::Selectable("Spot Light", false))
			{
				Engine::GameObject* newObject = new Engine::GameObject();
				newObject->name = "Spot Light";
				if (current) newObject->transform->SetParent(current->transform);
				newObject->AddComponent<LowRenderer::SpotLight>();
				m_currentScene->Instantiate(newObject);
			}
			GUI::EndMenu();
		}
		if (GUI::BeginMenu("3D Object"))
		{
			if (GUI::Selectable("Cube", false))
			{
				Engine::GameObject* newObject = new Engine::GameObject();
				newObject->name = "Cube";
				if(current) newObject->transform->SetParent(current->transform);
				LowRenderer::MeshRenderer* mr = newObject->AddComponent<LowRenderer::MeshRenderer>();
				mr->SetMesh(rm.GetResource<Resource::Mesh>("DefaultAssets\\Model\\primitiveCube.obj"));
				mr->SetMaterial(rm.GetResource<Resource::Material>("DefaultAssets\\Material\\DefaultMat.phmat"));
				m_currentScene->Instantiate(newObject);
			}
			if (GUI::Selectable("Sphere", false))
			{
				Engine::GameObject* newObject = new Engine::GameObject();
				newObject->name = "Sphere";
				if (current) newObject->transform->SetParent(current->transform);
				LowRenderer::MeshRenderer* mr = newObject->AddComponent<LowRenderer::MeshRenderer>();
				mr->SetMesh(rm.GetResource<Resource::Mesh>("DefaultAssets\\Model\\primitiveSphere.obj"));
				mr->SetMaterial(rm.GetResource<Resource::Material>("DefaultAssets\\Material\\DefaultMat.phmat"));
				m_currentScene->Instantiate(newObject);
			}
			if (GUI::Selectable("Capsule", false))
			{
				Engine::GameObject* newObject = new Engine::GameObject();
				newObject->name = "Capsule";
				if (current) newObject->transform->SetParent(current->transform);
				LowRenderer::MeshRenderer* mr = newObject->AddComponent<LowRenderer::MeshRenderer>();
				mr->SetMesh(rm.GetResource<Resource::Mesh>("DefaultAssets\\Model\\primitiveCapsule.obj"));
				mr->SetMaterial(rm.GetResource<Resource::Material>("DefaultAssets\\Material\\DefaultMat.phmat"));
				m_currentScene->Instantiate(newObject);
			}

			GUI::EndMenu();
		}
		if (current)
		{
			GUI::Separator();
			if (GUI::Selectable("Delete", false))
			{
				current->Destroy();
				if (m_selected == current)
				{
					m_selected = nullptr;
					selectedClicked = true;
				}

			}
		}
		GUI::EndPopup();
	}
}
