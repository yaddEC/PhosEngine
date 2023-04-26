// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <iostream>
#include <algorithm>
#include <array>
#include "Engine/Transform.hpp"
#include "Engine/Scene.hpp"
#include "Physx/PxPhysicsAPI.h"
#include "Physic/Collider.hpp"
#include "Physic/Rigidbody.hpp"
#include "Engine/GameObject.hpp"

#define PHYSICSWRAPPER_EXPORTS
#include "Wrapper/PhysicsWrapper.hpp"

MySimulationEventCallback::MySimulationEventCallback()
{

}

MySimulationEventCallback::~MySimulationEventCallback()
{
}

bool Wrapper::RayCast(Maths::Vec3 origin, Maths::Vec3 direction, float maxDistance, RayCastHit& hit)
{
    PxVec3 pxOrigin = PxVec3(origin.x, origin.y, origin.z);

    PxVec3 pxDirection = PxVec3(direction.x, direction.y, direction.z);

    PxRaycastBuffer pxHit;
    PxQueryFilterData filterData(PxQueryFlag::eSTATIC);

    bool raycastHit = Physic::PhysicsManager::GetInstance().getPhysics().getScene()->raycast(pxOrigin,pxDirection,maxDistance,pxHit, PxHitFlag::eDEFAULT, filterData);

    if(raycastHit)
    { 
    hit.distance = pxHit.block.distance;
    hit.impactPos = Maths::Vec3(pxHit.block.position.x, pxHit.block.position.y, pxHit.block.position.z);
    hit.normHit = Maths::Vec3(pxHit.block.normal.x, pxHit.block.normal.y, pxHit.block.normal.z);
    hit.objectHit = reinterpret_cast<Engine::GameObject*>(pxHit.block.actor->userData);
    }

    return raycastHit;
}

PxFilterFlags CustomFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
    PxFilterObjectAttributes attributes1, PxFilterData filterData1,
    PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
    bool isTrigger0 = PxFilterObjectIsTrigger(attributes0);
    bool isTrigger1 = PxFilterObjectIsTrigger(attributes1);
    if (isTrigger0 || isTrigger1)
    {
        pairFlags = PxPairFlag::eDETECT_DISCRETE_CONTACT | PxPairFlag::eDETECT_CCD_CONTACT;
        if (isTrigger0 && isTrigger1)
        {
            return PxFilterFlag::eSUPPRESS;
        }
        else
        {
            pairFlags = PxPairFlag::eTRIGGER_DEFAULT;

        }
    }
    else
    {
        pairFlags = PxPairFlag::eCONTACT_DEFAULT;
    }
    pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
    pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
    pairFlags |= PxPairFlag::eNOTIFY_TOUCH_PERSISTS;
    return PxFilterFlag::eDEFAULT;
}

void MySimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{

    for (PxU32 i = 0; i < nbPairs; i++)
    {
        const PxContactPair& cp = pairs[i];

        Engine::GameObject* contact0 = reinterpret_cast<Engine::GameObject*>(pairHeader.actors[0]->userData);
        Engine::GameObject* contact1 = reinterpret_cast<Engine::GameObject*>(pairHeader.actors[1]->userData);
        if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            contact0->OnCollisionEnter(contact1);
            contact1->OnCollisionEnter(contact0);
        }
        if (cp.events & PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
        {
            contact0->OnCollisionStay(contact1);
            contact1->OnCollisionStay(contact0);
        }

        if (cp.events & PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            contact0->OnCollisionExit(contact1);
            contact1->OnCollisionExit(contact0);
        }
    }
}
void MySimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
    for (PxU32 i = 0; i < count; i++)
    {
        PxTriggerPair& pair = pairs[i];
        PxShape* triggerShape = pair.triggerShape;

        Engine::GameObject* triggerActor = reinterpret_cast<Engine::GameObject*>(pair.triggerActor->userData);
        Engine::GameObject* otherActor = reinterpret_cast<Engine::GameObject*>(pair.otherActor->userData);

        bool isOtherTrigger = pair.otherShape->getFlags() & PxShapeFlag::eTRIGGER_SHAPE;

        if (pair.status == PxPairFlag::eNOTIFY_TOUCH_FOUND && !isOtherTrigger)
        {
            triggerActor->OnTriggerEnter(otherActor);
        }


        if (pair.status == PxPairFlag::eNOTIFY_TOUCH_PERSISTS && !isOtherTrigger)
        {
            triggerActor->OnTriggerStay(otherActor);
        }

        if (pair.status == PxPairFlag::eNOTIFY_TOUCH_LOST && !isOtherTrigger)
        {
            triggerActor->OnTriggerExit(otherActor);
        }

    

    }

}

namespace Wrapper
{

    
    PxDefaultErrorCallback Physics::gDefaultErrorCallback;
    PxDefaultAllocator Physics::gDefaultAllocatorCallback;



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
        MySimulationEventCallback* mySimulationEventCallback = new MySimulationEventCallback();
        PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
        sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
        sceneDesc.filterShader = CustomFilterShader;
        sceneDesc.flags |= PxSceneFlag::eENABLE_PCM;
        sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
        sceneDesc.simulationEventCallback = mySimulationEventCallback;
        sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
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
        
        if (collider->rb) {
            PxTransform pose(PxVec3(-collider->gameobject->transform->position.x, collider->gameobject->transform->position.y, collider->gameobject->transform->position.z));
            PhysxActor= Physic::PhysicsManager::GetInstance().getPhysics().getPhysics()->createRigidDynamic(pose);
            PhysxActor->is<PxRigidDynamic>()->setMass(collider->rb->mass);
            collider->rb->physicsRigidbody->setRigidActor(PhysxActor);
            collider->rb->physicsRigidbody->Init();
        }
        else {
            Maths::Vec3 eulerRotation = collider->gameobject->transform->rotationEuler;
            Maths::Quaternion rotationQuat = Maths::Quaternion::ToQuaternion(eulerRotation);
            PxTransform pose(PxVec3(-collider->gameobject->transform->position.x, collider->gameobject->transform->position.y, collider->gameobject->transform->position.z), PxQuat(rotationQuat.a, rotationQuat.b, rotationQuat.c, rotationQuat.d));
            PhysxActor = Physic::PhysicsManager::GetInstance().getPhysics().getPhysics()->createRigidStatic(pose);
        }
        PhysxActor->userData = collider->gameobject;
        Maths::Quaternion rotCol = collider->transform->rotation.ToQuaternion(collider->transform->rotationEuler);
        rotCol.Conjugate();
        Maths::Mat4 worldModel = collider->transform->GetGlobalMatrix() * rotCol.ToRotationMatrix() ;
        PxMaterial* material = createMaterialByType(Physic::PhysicsManager::GetInstance().getPhysics().getPhysics(), PhysxMaterial);
        if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
        {
            geometry.box = PxBoxGeometry(worldModel.data_4_4[0][0] * boxCollider->size.x , worldModel.data_4_4[1][1] * boxCollider->size.y , worldModel.data_4_4[2][2] * boxCollider->size.z );
            shape = PxRigidActorExt::createExclusiveShape(*PhysxActor, geometry.box, *material);
        }
        else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
        {
            geometry.sphere = PxSphereGeometry(worldModel.data_4_4[0][0] * sphereCollider->radius);
            shape = PxRigidActorExt::createExclusiveShape(*PhysxActor, geometry.sphere, *material);
        }
        else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
        {
            geometry.capsule = PxCapsuleGeometry(worldModel.data_4_4[0][0] * capsuleCollider->radius, worldModel.data_4_4[1][1] * capsuleCollider->height  * 0.5f);
            shape = PxRigidActorExt::createExclusiveShape(*PhysxActor, geometry.capsule, *material);
        }
        
        if (collider->isTrigger)
        {
            shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
            shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
        }

        Physic::PhysicsManager::GetInstance().getPhysics().getScene()->addActor(*PhysxActor);

    }

    int countRigidActors(PxScene* scene) {
        const PxU32 maxActors = 1000;

        PxActor* actors[maxActors];

        PxU32 numActors = scene->getActors(PxActorTypeFlag::eRIGID_STATIC | PxActorTypeFlag::eRIGID_DYNAMIC, actors, maxActors);

 
        int rigidActorCount = 0;

        for (PxU32 i = 0; i < numActors; ++i) {
            PxActor* actor = actors[i];

            if (actor->getConcreteType() == PxConcreteType::eRIGID_STATIC || actor->getConcreteType() == PxConcreteType::eRIGID_DYNAMIC) {
                ++rigidActorCount;
            }
        }
        return rigidActorCount;
    }


 
    void PhysicsCollider::Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material)
    {

        if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
        {
            boxCollider->size = size;
        }
        else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
        {
            sphereCollider->radius = size.x;
        }
        else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
        {
            capsuleCollider->radius = size.x;
            capsuleCollider->height = size.y;

        }
        collider->center = center* Maths::Vec3(-1,0,0);
        collider->isTrigger = trigger;
    }
 

    void PhysicsCollider::Update()
    {
        if (!collider->rb)
        {
            Maths::Mat4 worldModel = collider->gameobject->transform->GetGlobalMatrix();
            PxVec3 position(-worldModel.data_4_4[0][3] + collider->center.x, worldModel.data_4_4[1][3] + collider->center.y, worldModel.data_4_4[2][3] + collider->center.z);
            Maths::Vec3 eulerRotation = collider->gameobject->transform->rotationEuler;
            Maths::Quaternion rotationQuat = Maths::Quaternion::ToQuaternion(eulerRotation);
            PxQuat pxRotation(-rotationQuat.a, rotationQuat.d, -rotationQuat.c, rotationQuat.b);

 
          

            PxTransform pose(position, pxRotation);
            PhysxActor->setGlobalPose(pose);

            //change scale in runtime
            /*
            PxShape* shape;
            PhysxActor->getShapes(&shape, 1);
            PxGeometryHolder geometryHolder = shape->getGeometry();

            switch (geometryHolder.getType())
            {
            case PxGeometryType::eBOX:
            {
                PxBoxGeometry boxGeometry = geometryHolder.box();
                boxGeometry.halfExtents = PxVec3(boxGeometry.halfExtents.x * collider->gameobject->transform->scale.x, boxGeometry.halfExtents.y * collider->gameobject->transform->scale.y, boxGeometry.halfExtents.z * collider->gameobject->transform->scale.z);
                shape->setGeometry(boxGeometry);
                break;
            }
            case PxGeometryType::eSPHERE:
            {
                PxSphereGeometry sphereGeometry = geometryHolder.sphere();
                std::array<float, 3> scaleValues = { collider->gameobject->transform->scale.x,collider->gameobject->transform->scale.y, collider->gameobject->transform->scale.z };
                float max_scale = *std::max_element(scaleValues.begin(), scaleValues.end());

                sphereGeometry.radius *= max_scale;
                shape->setGeometry(sphereGeometry);
                break;
            }
            case PxGeometryType::eCAPSULE:
            {
                PxCapsuleGeometry capsuleGeometry = geometryHolder.capsule();s
                std::array<float, 2> scaleValues = { collider->gameobject->transform->scale.x, collider->gameobject->transform->scale.y };
                float max_scale = *std::max_element(scaleValues.begin(), scaleValues.end());
                capsuleGeometry.radius *= max_scale;
                capsuleGeometry.halfHeight *= worldModel.data_4_4[2][2];
                shape->setGeometry(capsuleGeometry);
                break;
            }
            default:
                break;
            }*/
        
        }
    }

    void PhysicsRigidbody::Init()
    {
        
        Maths::Quaternion eulerRot = Maths::Quaternion::ToQuaternion(rigidbody->gameobject->transform->rotationEuler);
       PxTransform pose(PxVec3(-rigidbody->gameobject->transform->position.x, rigidbody->gameobject->transform->position.y, rigidbody->gameobject->transform->position.z), PxQuat(-eulerRot.b, eulerRot.c, eulerRot.d, -eulerRot.a));

        PhysxActor->setGlobalPose(pose);

    }

    void PhysicsRigidbody::Update()
    {
        if (PhysxActor)
        {
            if ( PhysxActor && PhysxActor->is<PxRigidDynamic>())
            {
                PxRigidDynamic* dynamicActor = PhysxActor->is<PxRigidDynamic>();

                PxVec3 force = PxVec3(rigidbody->velocity.x, rigidbody->velocity.y, rigidbody->velocity.z) * rigidbody->mass;

                dynamicActor->addForce(force);

                PxTransform updatedTransform = dynamicActor->getGlobalPose();
                Maths::Vec3 newPosition = Maths::Vec3(-updatedTransform.p.x, updatedTransform.p.y, updatedTransform.p.z);
                rigidbody->gameobject->transform->position = newPosition;
                PxQuat updatedRotation = updatedTransform.q;
                
                Maths::Quaternion newRotation = Maths::Quaternion(updatedRotation.w, updatedRotation.x, -updatedRotation.y, -updatedRotation.z) ;
                  

                rigidbody->gameobject->transform->rotation = newRotation;

            }

        }
    }

}