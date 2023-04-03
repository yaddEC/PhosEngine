// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <Physic/Collider.hpp>
#include <Engine/Transform.hpp>
#define RIGIDBODY_EXPORTS
#include <Physic/Rigidbody.hpp>

Physic::Rigidbody::Rigidbody()
{
}

void Physic::Rigidbody::Init()
{
	
	Collider* c = gameobject->GetComponent<Collider>();
	if (c)
		c->rb = this;
}

void Physic::Rigidbody::Update()
{
	
	if (PhysxActor)
	{
		if (!isStatic && PhysxActor && PhysxActor->is<PxRigidDynamic>())
		{
			PxRigidDynamic* dynamicActor = PhysxActor->is<PxRigidDynamic>();

			// Set the updated velocity
			PxVec3 force = PxVec3(velocity.x, velocity.y, velocity.z) * mass;

			// Apply the force to the dynamic actor
			dynamicActor->addForce(force);

			// Update the GameObject's transform
			PxTransform updatedTransform = dynamicActor->getGlobalPose();
			Vec3 newPosition = Vec3(updatedTransform.p.x, updatedTransform.p.y, updatedTransform.p.z);
			gameobject->transform->position = newPosition;

		}

	}
	//velocity += AppState::deltatime * gravity;
}

