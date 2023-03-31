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
	transform = new Transform();
	transform->SetGameObject(this);
	// transform.gameobject = this;
}

void Engine::GameObject::Start()
{
	for (MonoBehaviour* comp : components)
	{
		if(scene->GetIsGameMode() || comp->renderingComponent)
			comp->Start();
	}
}

template <class T>
inline T* Engine::GameObject::GetComponentInChildren(unsigned int index )
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
	for (MonoBehaviour* comp : componentsBuffer)
	{
		components.push_back(comp);

		if (scene->GetIsGameMode() || comp->renderingComponent)
			comp->Start();
	}
	componentsBuffer.clear();


	for (MonoBehaviour* comp : components)
	{
		if (scene->GetIsGameMode() || comp->renderingComponent)
			comp->Update();
	}
}

void Engine::GameObject::OnDestroy()
{
	for (MonoBehaviour* comp : components)
	{
		if (scene->GetIsGameMode() || comp->renderingComponent)
			comp->OnDestroy();
	}
	transform->Destroy();
}

