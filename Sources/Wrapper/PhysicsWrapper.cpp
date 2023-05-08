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

    
    PxDefaultErrorCallback Physics::m_defaultErrorCallback;
    PxDefaultAllocator Physics::m_defaultAllocatorCallback;

    bool RayCast(Maths::Vec3 origin, Maths::Vec3 direction, float maxDistance, RayCastHit& hit)
    {
        PxVec3 pxOrigin = PxVec3(origin.x, origin.y, origin.z);

        PxVec3 pxDirection = PxVec3(-direction.x, direction.y, -direction.z);

        PxRaycastBuffer pxHit;
        PxQueryFilterData filterData(PxQueryFlag::eSTATIC);

        bool raycastHit = Physic::PhysicsManager::GetInstance().GetPhysics().GetScene()->raycast(pxOrigin, pxDirection, maxDistance, pxHit, PxHitFlag::eDEFAULT, filterData);

        if (raycastHit)
        {
            hit.distance = pxHit.block.distance;
            hit.impactPos = Maths::Vec3(pxHit.block.position.x, pxHit.block.position.y, pxHit.block.position.z);
            hit.normHit = Maths::Vec3(pxHit.block.normal.x, pxHit.block.normal.y, pxHit.block.normal.z);
            hit.objectHit = reinterpret_cast<Engine::GameObject*>(pxHit.block.actor->userData);
        }

        return raycastHit;
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
        if (m_scene)
        {
            m_scene->simulate(deltaTime);
            m_scene->fetchResults(true);
        }
    }

    void Physics::Cleanup()
    {
        if (m_scene)
            m_scene->release();

        if (m_physics)
            m_physics->release();

        if (m_pvd)
            m_pvd->release();

        if (m_foundation)
            m_foundation->release();
    }

    PxMaterial* CreateMaterialByType( PxPhysics* physics, MaterialType type)
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
        m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocatorCallback, m_defaultErrorCallback);
        if (!m_foundation)
            throw std::runtime_error("PxCreateFoundation failed!");
    }

    void Physics::CreatePhysics()
    {
        m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, PxTolerancesScale(), true, m_pvd);
        if (!m_physics)
            throw std::runtime_error("PxCreatePhysics failed!");
    }

    void Physics::CreateScene()
    {
        MySimulationEventCallback* mySimulationEventCallback = new MySimulationEventCallback();
        PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
        sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
        sceneDesc.filterShader = CustomFilterShader;
        sceneDesc.flags |= PxSceneFlag::eENABLE_PCM;
        sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
        sceneDesc.simulationEventCallback = mySimulationEventCallback;
        sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
        m_scene = m_physics->createScene(sceneDesc);
        if (!m_scene)
            throw std::runtime_error("createScene failed!");
    }

    void Physics::SetupVisualDebugger()
    {

        m_pvd = PxCreatePvd(*m_foundation);
        PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        m_pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

    }


    void PhysicsCollider::Init()
    {
        collider->gameobject->transform->RegisterTransformChangedCallback([this]() { OnTransformChanged(); });
        if (collider->rb) {
            PxTransform pose(PxVec3(collider->gameobject->transform->position.x, collider->gameobject->transform->position.y, collider->gameobject->transform->position.z));
            m_physxActor = Physic::PhysicsManager::GetInstance().GetPhysics().GetPhysics()->createRigidDynamic(pose);
            collider->rb->physicsRigidbody->SetRigidActor(m_physxActor);
            collider->rb->physicsRigidbody->Init();
        }
        else {
            Maths::Vec3 eulerRotation = collider->gameobject->transform->rotationEuler;
            Maths::Quaternion rotationQuat = Maths::Quaternion::ToQuaternion(eulerRotation);
            PxTransform pose(PxVec3(collider->gameobject->transform->position.x, collider->gameobject->transform->position.y, collider->gameobject->transform->position.z), PxQuat( rotationQuat.b, rotationQuat.c, rotationQuat.d, rotationQuat.a));
            m_physxActor = Physic::PhysicsManager::GetInstance().GetPhysics().GetPhysics()->createRigidStatic(pose);
        }
        m_physxActor->userData = collider->gameobject;
        Maths::Quaternion rotCol = collider->transform->rotation.ToQuaternion(collider->transform->rotationEuler);
        rotCol.Conjugate();
        Maths::Mat4 worldModel = collider->transform->GetGlobalMatrix() * rotCol.ToRotationMatrix() ;
        PxMaterial* material = CreateMaterialByType(Physic::PhysicsManager::GetInstance().GetPhysics().GetPhysics(), m_physxMaterial);
        if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
        {
            m_geometry.box = PxBoxGeometry(worldModel.data_4_4[0][0] * boxCollider->size.x , worldModel.data_4_4[1][1] * boxCollider->size.y , worldModel.data_4_4[2][2] * boxCollider->size.z );
            m_shape = PxRigidActorExt::createExclusiveShape(*m_physxActor, m_geometry.box, *material);
        }
        else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
        {
            m_geometry.sphere = PxSphereGeometry(worldModel.data_4_4[0][0] * sphereCollider->radius);
            m_shape = PxRigidActorExt::createExclusiveShape(*m_physxActor, m_geometry.sphere, *material);
        }
        else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
        {
            m_geometry.capsule = PxCapsuleGeometry(worldModel.data_4_4[0][0] * capsuleCollider->radius, worldModel.data_4_4[1][1] * capsuleCollider->height  * 0.5f);
            m_shape = PxRigidActorExt::createExclusiveShape(*m_physxActor, m_geometry.capsule, *material);
        }
        
        if (collider->isTrigger)
        {
            m_shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
            m_shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
        }

        Physic::PhysicsManager::GetInstance().GetPhysics().GetScene()->addActor(*m_physxActor);

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
        collider->center = center;
        collider->isTrigger = trigger;
    }
 

    void PhysicsCollider::Update()
    {

    }

    void Wrapper::PhysicsCollider::OnGuiChanged()
    {
        if (this)
        {
            Maths::Mat4 worldModel = collider->gameobject->transform->GetGlobalMatrix();
            PxShape* shapes[1];
            m_physxActor->getShapes(shapes, 1);
            shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, collider->isTrigger);
            PxVec3 position = PxVec3(worldModel.data_4_4[0][3] + collider->center.x, worldModel.data_4_4[1][3] + collider->center.y, worldModel.data_4_4[2][3] + collider->center.z);
            m_physxActor->setGlobalPose(PxTransform(position));

            if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
            {
                PxVec3 newDimensions(boxCollider->size.x * collider->gameobject->transform->scale.x, boxCollider->size.y * collider->gameobject->transform->scale.y, boxCollider->size.z * collider->gameobject->transform->scale.z);
                PxBoxGeometry boxGeometry;
                shapes[0]->getBoxGeometry(boxGeometry);
                boxGeometry.halfExtents = newDimensions * 0.5f;
                shapes[0]->setGeometry(boxGeometry);
            }
            else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
            {

                PxSphereGeometry sphereGeometry;
                shapes[0]->getSphereGeometry(sphereGeometry);
                sphereGeometry.radius = sphereCollider->radius * collider->gameobject->transform->scale.x;
                shapes[0]->setGeometry(sphereGeometry);
            }
            else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
            {
                PxCapsuleGeometry capsuleGeometry;
                shapes[0]->getCapsuleGeometry(capsuleGeometry);
                capsuleGeometry.radius = capsuleCollider->radius * collider->gameobject->transform->scale.x;
                capsuleGeometry.halfHeight = capsuleCollider->height * collider->gameobject->transform->scale.y;
                shapes[0]->setGeometry(capsuleGeometry);
            }
        }
     
    }

    void Wrapper::PhysicsCollider::OnTransformChanged()
    {
        if (this)
        {
            Maths::Mat4 worldModel = collider->gameobject->transform->GetGlobalMatrix();
            Maths::Quaternion rotationQuat = Maths::Quaternion::ToQuaternion(collider->gameobject->transform->rotationEuler);
            PxQuat pxRotation(rotationQuat.b, rotationQuat.c, rotationQuat.d, rotationQuat.a);
            PxVec3 position;
            position = PxVec3(worldModel.data_4_4[0][3] + collider->center.x, worldModel.data_4_4[1][3] + collider->center.y, worldModel.data_4_4[2][3] + collider->center.z);
            m_physxActor->setGlobalPose(PxTransform(position, pxRotation));

            PxShape* shape;
            m_physxActor->getShapes(&shape, 1);

            if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
            {
                m_geometry.box.halfExtents = PxVec3(boxCollider->size.x * collider->gameobject->transform->scale.x, boxCollider->size.y * collider->gameobject->transform->scale.y, boxCollider->size.z * collider->gameobject->transform->scale.z);
                shape->setGeometry(m_geometry.box);
            }
            else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
            {
                std::array<float, 3> scaleValues = { collider->gameobject->transform->scale.x,collider->gameobject->transform->scale.y, collider->gameobject->transform->scale.z };
                float max_scale = *std::max_element(scaleValues.begin(), scaleValues.end());

                m_geometry.sphere.radius = sphereCollider->radius * max_scale;
                shape->setGeometry(m_geometry.sphere);


            }
            else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
            {
                std::array<float, 2> scaleValues = { collider->gameobject->transform->scale.x, collider->gameobject->transform->scale.y };
                float max_scale = *std::max_element(scaleValues.begin(), scaleValues.end());
                m_geometry.capsule.radius = capsuleCollider->radius * max_scale;
                m_geometry.capsule.halfHeight = capsuleCollider->height * worldModel.data_4_4[2][2];
                shape->setGeometry(m_geometry.capsule);
            }
        }
      
    }

    void PhysicsRigidbody::Init()
    {
        rigidbody->gameobject->transform->RegisterTransformChangedCallback([this]() { OnTransformChanged(); });

        Maths::Quaternion eulerRot = Maths::Quaternion::ToQuaternion(rigidbody->gameobject->transform->rotationEuler);
       PxTransform pose(PxVec3(rigidbody->gameobject->transform->position.x+rigidbody->col->center.x, rigidbody->gameobject->transform->position.y + rigidbody->col->center.y, rigidbody->gameobject->transform->position.z + rigidbody->col->center.z), PxQuat( eulerRot.b, eulerRot.c, eulerRot.d, eulerRot.a));
       m_physxActor->setGlobalPose(pose);
       m_physxActor->is<PxRigidDynamic>()->setMass(rigidbody->mass);

    }

    void UpdateRotationEuler(Maths::Vec3& rotationEuler, const Maths::Quaternion& newRotation) {
        Maths::Vec3 newEulerAngles = newRotation.ToEulerAngles();

        for (int i = 0; i < 3; ++i) {
            float deltaAngle = newEulerAngles.xyz[i] - std::fmod(rotationEuler.xyz[i], 360.0f);
            rotationEuler.xyz[i] += deltaAngle;
        }
    }

    void PhysicsRigidbody::Update()
    {
        if (m_physxActor)
        {
            if ( m_physxActor && m_physxActor->is<PxRigidDynamic>())
            {
                if (!m_transformChangedExternally)
                {

                
                    PxRigidDynamic* dynamicActor = m_physxActor->is<PxRigidDynamic>();

                    PxVec3 force = PxVec3(rigidbody->velocity.x, rigidbody->velocity.y, rigidbody->velocity.z) * rigidbody->mass;

                    dynamicActor->addForce(force);

                    PxTransform updatedTransform = dynamicActor->getGlobalPose();
                    Maths::Vec3 newPosition = Maths::Vec3(updatedTransform.p.x, updatedTransform.p.y, updatedTransform.p.z);
                    rigidbody->gameobject->transform->position = newPosition-rigidbody->col->center;
                    PxQuat updatedRotation = updatedTransform.q;
                    
                    Maths::Quaternion newRotation = Maths::Quaternion(updatedRotation.w, updatedRotation.x, updatedRotation.y, updatedRotation.z) ;

                      

                    rigidbody->gameobject->transform->rotation = newRotation;
                    
                }
                else
                {
                    m_transformChangedExternally = false;
                }
            }

        }
    }

    void Wrapper::PhysicsRigidbody::OnGuiChanged()
    {
        if (this)
        {
            m_physxActor->is<PxRigidDynamic>()->setMass(rigidbody->mass);
        }
    }

    void PhysicsRigidbody::OnTransformChanged()
    {
        if (this)
        {
            m_transformChangedExternally = true;
        }
    }

  

}