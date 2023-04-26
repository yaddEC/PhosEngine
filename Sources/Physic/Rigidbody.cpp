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
	//Use of the Raycast
	/*Wrapper::RayCastHit test;
	Maths::Vec3 dir = gameobject->transform->GetForwardVector();

	if (Wrapper::RayCast(gameobject->transform->position, dir, 6, test) )
		printf("Forward %s %d\n", gameobject->name.c_str(), rand());

	dir = gameobject->transform->GetRightVector();

	if (Wrapper::RayCast(gameobject->transform->position, dir, 6, test))
		printf("Right %s %d\n", gameobject->name.c_str(), rand());

	dir = gameobject->transform->GetUpVector();

	if (Wrapper::RayCast(gameobject->transform->position, dir, 6, test))
		printf("UP %s %d\n", gameobject->name.c_str(), rand());*/
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
			ClassMemberInfo("Gravity", offsetof(Rigidbody, Rigidbody::gravity), MemberType::T_VEC3),
			ClassMemberInfo("Velocity", offsetof(Rigidbody, Rigidbody::velocity), MemberType::T_VEC3),
			ClassMemberInfo("mass", offsetof(Rigidbody, Rigidbody::mass), MemberType::T_FLOAT),
			ClassMemberInfo("reset", offsetof(Rigidbody, Rigidbody::reset), MemberType::T_BOOL),
		};
		computed = true;
	}
	return result;
}

