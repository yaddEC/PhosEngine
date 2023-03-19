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

Engine::GameObject::GameObject(Scene* _scene, Transform* _transform)
	: scene(_scene)
	, transform(_transform)
{
	// transform.gameobject = this;
}

void Engine::GameObject::Start()
{
	for (MonoBehaviour* component : components)
	{
		component->Start();
	}
}

void Engine::GameObject::Update()
{
	for (MonoBehaviour* comp : componentsBuffer)
	{
		components.push_back(comp);
		comp->Start();
	}
	componentsBuffer.clear();


	for (MonoBehaviour* comp : components)
	{
		comp->Update();
	}
}

void Engine::GameObject::OnDestroy()
{
	for (MonoBehaviour* component : components)
	{
		component->OnDestroy();
	}
	transform->Destroy();
}

void Engine::GameObject::AddComponent(MonoBehaviour* newComponent)
{
	newComponent->gameobject = this;
	newComponent->transform = transform;
	componentsBuffer.push_back(newComponent);
}
