// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Physic/Collider.hpp"

#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"

#include "Wrapper/PhysicsWrapper.hpp"

#define RIGIDBODY_EXPORTS
#include <Physic/Rigidbody.hpp>

Physic::Rigidbody::Rigidbody()
{
	physicsRigidbody->setMaterialType(Wrapper::ROCK);
}

Physic::Rigidbody::Rigidbody(Wrapper::MaterialType type)
{
	physicsRigidbody->setMaterialType(type);
}

void Physic::Rigidbody::Init()
{
	physicsRigidbody->rigidbody = this;
	Collider* c = gameobject->GetComponent<Collider>();
	if (c)
		c->rb = this;

}

void Physic::Rigidbody::Update()
{
	
	physicsRigidbody->Update();
	//velocity += AppState::deltatime * gravity;
}

