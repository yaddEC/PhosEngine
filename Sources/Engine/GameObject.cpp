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

