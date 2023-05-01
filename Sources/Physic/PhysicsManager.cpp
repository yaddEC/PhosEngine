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
	m_physics.Init();
}

void Physic::PhysicsManager::Update(float deltaTime)
{
	if(deltaTime>0)
		m_physics.Update(deltaTime);
}

void Physic::PhysicsManager::Cleanup()
{
	m_physics.Cleanup();
}
