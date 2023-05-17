// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Engine/Scene.hpp"
#include "Engine/Transform.hpp"
#include "Engine/MonoBehaviour.hpp"

#define GAMEOBJECT_EXPORTS
#include "Engine/GameObject.hpp"

using namespace Engine;

Engine::GameObject::GameObject()
{
	m_tag = 0;
	m_layer = 0;
	transform = new Transform();
	transform->SetGameObject(this);
	// transform.gameobject = this;
}

void Engine::GameObject::Start()
{
	for (MonoBehaviour* comp : m_components)
	{
		if(m_scene->GetIsGameMode() || comp->renderingComponent)
			comp->Start();
	}
}

template <class T>
T* Engine::GameObject::GetComponentInChildren(unsigned int index )
{
	T* res = nullptr;
	for (Transform child : transform->m_children)
	{
		for (MonoBehaviour* component : child.gameObject->components)
		{
			if (typeid(*component) == typeid(T))
			{
				res = (T*)component;
				if (index == 0)
					return res;
				else
					index--;
			}
		}
	}
	return res;
}

void Engine::GameObject::Update()
{
	for (MonoBehaviour* comp : m_componentsBuffer)
	{
		m_components.push_back(comp);
	}
	for (MonoBehaviour* comp : m_componentsBuffer)
	{
		if (m_scene->GetIsGameMode() || comp->renderingComponent)
			comp->Start();
	}
	m_componentsBuffer.clear();


	for (MonoBehaviour* comp : m_components)
	{
		if (m_scene->GetIsGameMode() || comp->renderingComponent)
			comp->Update();
	}
}

void Engine::GameObject::OnCollisionEnter(GameObject* gameobject)
{
	for (MonoBehaviour* comp : m_components)
	{
		comp->OnCollisionEnter(gameobject);
	}
}

void Engine::GameObject::OnCollisionStay(GameObject* gameobject)
{
	for (MonoBehaviour* comp : m_components)
	{
		comp->OnCollisionStay(gameobject);
	}
}

void Engine::GameObject::OnCollisionExit(GameObject* gameobject)
{
	for (MonoBehaviour* comp : m_components)
	{
		comp->OnCollisionExit(gameobject);
	}
}

void Engine::GameObject::OnTriggerEnter(GameObject* gameobject)
{
	for (MonoBehaviour* comp : m_components)
	{
		comp->OnTriggerEnter(gameobject);
	}
}

void Engine::GameObject::OnGuiChanged()
{
	for (MonoBehaviour* component : m_components)
	{
		component->GUIUpdate();
	}
}

void Engine::GameObject::OnTriggerStay(GameObject* gameobject)
{
	for (MonoBehaviour* comp : m_components)
	{
		comp->OnTriggerStay(gameobject);
	}
}

void Engine::GameObject::OnTriggerExit(GameObject* gameobject)
{
	for (MonoBehaviour* comp : m_components)
	{
		comp->OnTriggerExit(gameobject);
	}
}

Engine::GameObject* Engine::GameObject::FindChildByName(const std::string& name)
{
	GameObject* currentParent = this;

	for (auto child : currentParent->transform->GetChildren())
	{
		if (child->GetGameObject()->name == name)
		{
			return child->GetGameObject();
		}
		else
		{
			GameObject* result = child->GetGameObject()->FindChildByName(name);
			if (result) return result;
		}

	}

	return nullptr;
}

void Engine::GameObject::Destroy()
{
	for (MonoBehaviour* comp : m_components)
	{
		if (m_scene->GetIsGameMode() || comp->renderingComponent)
			comp->OnDestroy();
	}
	transform->Destroy();
	m_scene->DeleteGameObjectFromList(this);
}

