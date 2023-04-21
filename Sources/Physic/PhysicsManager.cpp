// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <iostream>
#define PHYSICSMANAGER_EXPORTS
#include <Physic/PhysicsManager.hpp>


Physic::PhysicsManager::~PhysicsManager()
{
}

void Physic::PhysicsManager::Init()
{
	physics.Init();
}

void Physic::PhysicsManager::Update(float deltaTime)
{
	physics.Update(deltaTime);
}

void Physic::PhysicsManager::Cleanup()
{
	physics.Cleanup();
}
