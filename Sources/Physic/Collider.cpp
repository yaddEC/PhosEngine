// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <Engine/GameObject.hpp>
#include <Wrapper/PhysicsWrapper.hpp>
#include <Physic/Rigidbody.hpp>

#define COLLIDER_EXPORTS
#include <Physic/Collider.hpp>




void Physic::Collider::Start()
{
	Rigidbody* rigidbody = gameobject->GetComponent<Rigidbody>();
	if (rigidbody)
		rb = rigidbody;
	physicsCollider->Init();
	
}

Physic::Collider::Collider()
	: MonoBehaviour(true)
{
}

void Physic::Collider::Update()
{
	physicsCollider->Update();
}

void Physic::Collider::Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger = false, Wrapper::MaterialType material = Wrapper::ROCK)
{

	physicsCollider->Setup(center,size,trigger,material);

}

Reflection::ClassMetaData& Physic::Collider::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Collider";
		result.memberList =
		{
		};
		computed = true;
	}
	return result;
}



Physic::BoxCollider::BoxCollider(Maths::Vec3 _size)
	: Collider()
	
{
	physicsCollider = new Wrapper::PhysicsCollider();
	physicsCollider->collider = this;

	size = _size;
	Maths::Vec3 seg = size / 2.0f;
}






#pragma region Sphere


Physic::SphereCollider::SphereCollider(float _radius)
	: Collider()
{
	physicsCollider = new Wrapper::PhysicsCollider();
	physicsCollider->collider = this;

	radius = _radius;
}






#pragma endregion

#pragma region Capsule


Physic::CapsuleCollider::CapsuleCollider(float _radius, float _height)
	: Collider()
{
	physicsCollider = new Wrapper::PhysicsCollider();
	physicsCollider->collider = this;

	radius = _radius;
	height = _height;
}






#pragma endregion
