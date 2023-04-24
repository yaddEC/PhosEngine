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
	physicsCollider = new Wrapper::PhysicsCollider();
	physicsCollider->collider = this;

	Rigidbody* rigidbody = gameobject->GetComponent<Rigidbody>();
	if (rigidbody)
		rb = rigidbody;
	physicsCollider->Init();
	
}

Physic::Collider::Collider()
	: MonoBehaviour(false)
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
	size = _size;
	Maths::Vec3 seg = size / 2.0f;
}


Reflection::ClassMetaData& Physic::BoxCollider::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Box Collider";
		result.memberList =
		{
			ClassMemberInfo("isTrigger", offsetof(BoxCollider, BoxCollider::isTrigger), MemberType::T_BOOL),
			ClassMemberInfo("Center", offsetof(BoxCollider, BoxCollider::center), MemberType::T_VEC3),
			ClassMemberInfo("Size", offsetof(BoxCollider, BoxCollider::size), MemberType::T_VEC3),
		};

		computed = true;
	}
	return result;
}



#pragma region Sphere


Physic::SphereCollider::SphereCollider(float _radius)
	: Collider()
{
	radius = _radius;
}



Reflection::ClassMetaData& Physic::SphereCollider::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Sphere Collider";
		result.memberList =
		{
			ClassMemberInfo("isTrigger", offsetof(SphereCollider, SphereCollider::isTrigger), MemberType::T_BOOL),
			ClassMemberInfo("Center", offsetof(SphereCollider, SphereCollider::center), MemberType::T_VEC3),
			ClassMemberInfo("Radius", offsetof(SphereCollider, SphereCollider::radius), MemberType::T_FLOAT),
		};

		computed = true;
	}
	return result;
}


#pragma endregion

#pragma region Capsule


Physic::CapsuleCollider::CapsuleCollider(float _radius, float _height)
	: Collider()
{

	radius = _radius;
	height = _height;
}

Reflection::ClassMetaData& Physic::CapsuleCollider::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Capsule Collider";
		result.memberList =
		{
			ClassMemberInfo("isTrigger", offsetof(CapsuleCollider, CapsuleCollider::isTrigger), MemberType::T_BOOL),
			ClassMemberInfo("Center", offsetof(CapsuleCollider, CapsuleCollider::center), MemberType::T_VEC3),
			ClassMemberInfo("Radius", offsetof(CapsuleCollider, CapsuleCollider::height), MemberType::T_FLOAT),
			ClassMemberInfo("Radius", offsetof(CapsuleCollider, CapsuleCollider::radius), MemberType::T_FLOAT),
		};

		computed = true;
	}
	return result;
}






#pragma endregion
