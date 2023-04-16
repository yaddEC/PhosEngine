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
	: MonoBehaviour(true)
{
	physicsRigidbody = new Wrapper::PhysicsRigidbody();
	physicsRigidbody->rigidbody = this;
}


void Physic::Rigidbody::Init()
{

}

void Physic::Rigidbody::Update()
{
	
	physicsRigidbody->Update();
	//velocity += AppState::deltatime * gravity;
}

Reflection::ClassMetaData& Physic::Rigidbody::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "RigidBody";
		result.memberList =
		{
		};
		computed = true;
	}
	return result;
}

