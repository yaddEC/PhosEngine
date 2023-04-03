// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Engine/Transform.hpp"
#define COLLIDER_EXPORTS
#include <Physic/Collider.hpp>




void Physic::Collider::Init(PxPhysics& physics, PxMaterial& material, PxScene& scene)
{
	Rigidbody* rigidbody = gameobject->GetComponent<Rigidbody>();
	if (rigidbody)
		rb = rigidbody;

	PxTransform pose(PxVec3(gameobject->transform->position.x, gameobject->transform->position.y, gameobject->transform->position.z));

	if (rb->isStatic) {
		rb->PhysxActor = physics.createRigidStatic(pose);
	}
	else {
		rb->PhysxActor = physics.createRigidDynamic(pose);
		rb->PhysxActor->is<PxRigidDynamic>()->setMass(rb->mass);
	}
	setShape(material);

	scene.addActor(*rb->PhysxActor);
}

void Physic::Collider::Update()
{

}



Physic::BoxCollider::BoxCollider(Vec3 _size)
{
	size = _size;
	Vec3 seg = size / 2.0f;
	geometry = PxBoxGeometry(seg.x, seg.y, seg.z);
	vertices.push_back(Vec3(-seg.x, -seg.y, seg.z));
	vertices.push_back(Vec3(seg.x, -seg.y, seg.z));
	vertices.push_back(Vec3(seg.x, seg.y, seg.z));
	vertices.push_back(Vec3(-seg.x, seg.y, seg.z));

	vertices.push_back(Vec3(-seg.x, -seg.y, -seg.z));
	vertices.push_back(Vec3(seg.x, -seg.y, -seg.z));
	vertices.push_back(Vec3(seg.x, seg.y, -seg.z));
	vertices.push_back(Vec3(-seg.x, seg.y, -seg.z));
}


void Physic::BoxCollider::setShape(PxMaterial& material)
{
	shape = PxRigidActorExt::createExclusiveShape(*rb->PhysxActor, geometry, material);
	if (isTrigger)
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
}



#pragma region Sphere


Physic::SphereCollider::SphereCollider(float _radius)
{
	radius = _radius;
	geometry = PxSphereGeometry(_radius);
}



void Physic::SphereCollider::setShape(PxMaterial& material)
{
	shape = PxRigidActorExt::createExclusiveShape(*rb->PhysxActor, geometry, material);
	if (isTrigger)
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
}


#pragma endregion

#pragma region Capsule


Physic::CapsuleCollider::CapsuleCollider(float _radius, float _height)
{
	radius = _radius;
	height = _height;
	geometry = PxCapsuleGeometry(_radius, _height * 0.5f);
	
}

void Physic::CapsuleCollider::setShape(PxMaterial& material)
{
	shape = PxRigidActorExt::createExclusiveShape(*rb->PhysxActor, geometry, material);
	if (isTrigger)
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
}




#pragma endregion
