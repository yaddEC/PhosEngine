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




void Physic::Collider::Init()
{
	Rigidbody* rigidbody = gameobject->GetComponent<Rigidbody>();
	if (rigidbody)
		rb = rigidbody;

	physicsCollider->collider = this;
	physicsCollider->Init();
	
}

void Physic::Collider::Update()
{

}



Physic::BoxCollider::BoxCollider(Maths::Vec3 _size)
{
	size = _size;
	Maths::Vec3 seg = size / 2.0f;


}






#pragma region Sphere


Physic::SphereCollider::SphereCollider(float _radius)
{
	radius = _radius;
}






#pragma endregion

#pragma region Capsule


Physic::CapsuleCollider::CapsuleCollider(float _radius, float _height)
{
	radius = _radius;
	height = _height;
}






#pragma endregion
