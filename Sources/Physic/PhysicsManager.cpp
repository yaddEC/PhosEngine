// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <iostream>
#include <Wrapper/PhysicsWrapper.hpp>
#define PHYSICSMANAGER_EXPORTS
#include <Physic/PhysicsManager.hpp>


Physic::PhysicsManager::PhysicsManager()
{
	physics = new Wrapper::Physics();
}

Physic::PhysicsManager::~PhysicsManager()
{
	Cleanup();
}

void Physic::PhysicsManager::Init()
{
	physics->Init();
}

void Physic::PhysicsManager::Update(float deltaTime)
{
	physics->Update(deltaTime);
}

void Physic::PhysicsManager::Cleanup()
{
	physics->Cleanup();
}
