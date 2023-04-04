// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <iostream>
#include "Engine/Transform.hpp"
#include "Engine/Scene.hpp"
#include "Physx/PxPhysicsAPI.h"
#include "Physic/Collider.hpp"
#include "Physic/Rigidbody.hpp"
#include "Engine/GameObject.hpp"

#define PHYSICSWRAPPER_EXPORTS
#include "Wrapper/PhysicsWrapper.hpp"

namespace Wrapper
{

    
    PxDefaultErrorCallback Physics::gDefaultErrorCallback;
    PxDefaultAllocator Physics::gDefaultAllocatorCallback;

    Physics::Physics()
        : mFoundation(nullptr),
        mPhysics(nullptr),
        mScene(nullptr),
        mPvd(nullptr)
    {
    }

    Physics::~Physics()
    {
        Cleanup();
    }

    void Physics::Init()
    {
        CreateFoundation();
        SetupVisualDebugger();
        CreatePhysics();
        CreateScene();
    }

    void Physics::Update(float deltaTime)
    {
        if (mScene)
        {
            mScene->simulate(deltaTime);
            mScene->fetchResults(true);
        }
    }

    void Physics::Cleanup()
    {
        if (mScene)
            mScene->release();

        if (mPhysics)
            mPhysics->release();

        if (mPvd)
            mPvd->release();

        if (mFoundation)
            mFoundation->release();
    }

    PxMaterial* createMaterialByType( PxPhysics* physics, MaterialType type)
    {
        PxReal staticFriction, dynamicFriction, restitution;

        switch (type) {
        case ROCK:
            staticFriction = 0.8f;
            dynamicFriction = 0.7f;
            restitution = 0.1f;
            break;
        case BOUNCY_BALL:
            staticFriction = 0.5f;
            dynamicFriction = 0.3f;
            restitution = 0.8f;
            break;
        case ICE:
            staticFriction = 0.1f;
            dynamicFriction = 0.05f;
            restitution = 0.2f;
            break;
        case RUBBER:
            staticFriction = 0.7f;
            dynamicFriction = 0.5f;
            restitution = 0.6f;
            break;
        case WOOD:
            staticFriction = 0.6f;
            dynamicFriction = 0.4f;
            restitution = 0.3f;
            break;
        case METAL:
            staticFriction = 0.4f;
            dynamicFriction = 0.2f;
            restitution = 0.1f;
            break;
        case GLASS:
            staticFriction = 0.6f;
            dynamicFriction = 0.5f;
            restitution = 0.2f;
            break;
        default:

            break;
        }
     
        return physics->createMaterial(staticFriction, dynamicFriction, restitution);
    }


    void Physics::CreateFoundation()
    {
        mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
        if (!mFoundation)
            throw std::runtime_error("PxCreateFoundation failed!");
    }

    void Physics::CreatePhysics()
    {
        mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(), true, mPvd);
        if (!mPhysics)
            throw std::runtime_error("PxCreatePhysics failed!");
    }

    void Physics::CreateScene()
    {
        PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
        sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
        sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
        sceneDesc.filterShader = PxDefaultSimulationFilterShader;
        mScene = mPhysics->createScene(sceneDesc);
        if (!mScene)
            throw std::runtime_error("createScene failed!");
    }

    void Physics::SetupVisualDebugger()
    {

        mPvd = PxCreatePvd(*mFoundation);
        PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        mPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

    }


  

    void PhysicsCollider::Init()
    {
       
        
        PxTransform pose(PxVec3(collider->gameobject->transform->position.x, collider->gameobject->transform->position.y, collider->gameobject->transform->position.z));
        
        if (collider->rb->isStatic) {
            collider->gameobject->GetScene()->GetPhysicsManager()->getPhysics()->getPhysics()->createRigidStatic(pose);
        }
        else {
            collider->gameobject->GetScene()->GetPhysicsManager()->getPhysics()->getPhysics()->createRigidDynamic(pose);
            collider->rb->physicsRigidbody->getRigidActor()->is<PxRigidDynamic>()->setMass(collider->rb->mass);
        }
        
        PxMaterial* material = createMaterialByType(collider->gameobject->GetScene()->GetPhysicsManager()->getPhysics()->getPhysics(), collider->rb->physicsRigidbody->getMaterialType());
        if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
        {
            geometry.box = PxBoxGeometry(collider->gameobject->transform->scale.x * boxCollider->size.x * 0.5f, collider->gameobject->transform->scale.y * boxCollider->size.y * 0.5f, collider->gameobject->transform->scale.z * boxCollider->size.z * 0.5f);
            shape = PxRigidActorExt::createExclusiveShape(*collider->rb->physicsRigidbody->getRigidActor(), geometry.box, *material);
        }
        else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
        {
            geometry.sphere = PxSphereGeometry(collider->gameobject->transform->scale.x * sphereCollider->radius);
            shape = PxRigidActorExt::createExclusiveShape(*collider->rb->physicsRigidbody->getRigidActor(), geometry.sphere, *material);
        }
        else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
        {
            geometry.capsule = PxCapsuleGeometry(collider->gameobject->transform->scale.x * capsuleCollider->radius, collider->gameobject->transform->scale.y * capsuleCollider->height * 0.5f * 0.5f);
            shape = PxRigidActorExt::createExclusiveShape(*collider->rb->physicsRigidbody->getRigidActor(), geometry.capsule, *material);
        }
        
        if (collider->isTrigger)
            shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

        collider->gameobject->GetScene()->GetPhysicsManager()->getPhysics()->getScene()->addActor(*collider->rb->physicsRigidbody->getRigidActor());

    }


    void PhysicsRigidbody::Update()
    {
        if (PhysxActor)
        {
            if (!rigidbody->isStatic && PhysxActor && PhysxActor->is<PxRigidDynamic>())
            {
                PxRigidDynamic* dynamicActor = PhysxActor->is<PxRigidDynamic>();

                // Set the updated velocity
                PxVec3 force = PxVec3(rigidbody->velocity.x, rigidbody->velocity.y, rigidbody->velocity.z) * rigidbody->mass;

                // Apply the force to the dynamic actor
                dynamicActor->addForce(force);

                // Update the GameObject's transform
                PxTransform updatedTransform = dynamicActor->getGlobalPose();
                Maths::Vec3 newPosition = Maths::Vec3(updatedTransform.p.x, updatedTransform.p.y, updatedTransform.p.z);
                rigidbody->gameobject->transform->position = newPosition;

            }

        }
    }

}