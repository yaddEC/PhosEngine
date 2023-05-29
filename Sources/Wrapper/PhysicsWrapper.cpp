// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <iostream>
#include <algorithm>
#include <array>
#include <limits>
#include "Engine/Transform.hpp"
#include "Engine/Scene.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Input.hpp"
#include "Physx/PxPhysicsAPI.h"
#include "Physic/Collider.hpp"
#include "Physic/Rigidbody.hpp"
#include "Physic/Joint.hpp"


#include "Wrapper/PhysicsWrapper.hpp"
#include <thread>



MySimulationEventCallback::MySimulationEventCallback()
{
   
}

MySimulationEventCallback::~MySimulationEventCallback()
{
}

void  Wrapper::Physics::CreateLayer(const std::string layerName)
{
    std::vector<std::string>* layerNames =Wrapper::Physics::GetLayerNames();
    std::map<std::string, PxU32>* layerNameToIndexMap = Wrapper::Physics::GetNameToIndex();
    PxU32 newLayerIndex = static_cast<unsigned int>(layerNames->size());
    layerNames->push_back(layerName);
    (*layerNameToIndexMap)[layerName] = newLayerIndex;

    for (const auto& otherLayerName : *layerNames)
    {
        PxU32 otherLayerIndex = (*layerNameToIndexMap)[otherLayerName];
        SetLayerCollision(layerName, otherLayerName, true);
    }
}


std::string Wrapper::Physics::GetLayerName(unsigned int Layer)
{
    std::map<std::string, PxU32> layerNameToIndexMap = *Wrapper::Physics::GetNameToIndex();
    std::vector<std::string>* layerNames = Wrapper::Physics::GetLayerNames();

    for (const auto& pair : layerNameToIndexMap) {
        if (pair.second == Layer) {
           return pair.first;
            break;
        }
    }
    return "Default";
}

unsigned int Wrapper::Physics::GetLayerID(const std::string layerName)
{
    std::map<std::string, PxU32> layerNameToIndexMap = *Wrapper::Physics::GetNameToIndex();
    return layerNameToIndexMap[layerName];
}

bool  Wrapper::Physics::GetLayerCollision(std::string layerA, std::string layerB)
{
    std::map < std::pair<PxU32, PxU32>, bool> layerInteractionMatrix = *Wrapper::Physics::GetLayerInteractions();
    std::map<std::string, PxU32> layerNameToIndexMap = *Wrapper::Physics::GetNameToIndex();
    return layerInteractionMatrix[std::make_pair(layerNameToIndexMap[layerA], layerNameToIndexMap[layerB])];
}

void  Wrapper::Physics::SetLayerCollision(std::string layerA, std::string layerB, bool shouldCollide)
{
    std::map < std::pair<PxU32, PxU32>, bool>* layerInteractionMatrix = Wrapper::Physics::GetLayerInteractions();
    std::map<std::string, PxU32> layerNameToIndexMap = *Wrapper::Physics::GetNameToIndex();
    (*layerInteractionMatrix)[std::make_pair(layerNameToIndexMap[layerA], layerNameToIndexMap[layerB])] = shouldCollide;
    (*layerInteractionMatrix)[std::make_pair(layerNameToIndexMap[layerB], layerNameToIndexMap[layerA])] = shouldCollide;
}



std::vector<std::string>* Wrapper::Physics::GetLayerNames()
{
    return  &Physic::PhysicsManager::GetInstance().GetPhysics().layerNames;
}

std::map<std::pair<PxU32, PxU32>, bool>* Wrapper::Physics::GetLayerInteractions()
{
    return &Physic::PhysicsManager::GetInstance().GetPhysics().layerInteractionMatrix;
}

std::map<std::string, PxU32>* Wrapper::Physics::GetNameToIndex()
{
    return &Physic::PhysicsManager::GetInstance().GetPhysics().layerNameToIndexMap;
}

PxFilterFlags CustomFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSiz)
{
    std::map < std::pair<PxU32, PxU32>, bool> layerInteractionMatrix = *Wrapper::Physics::GetLayerInteractions();
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
    else if (layerInteractionMatrix[std::make_pair(filterData0.word0, filterData1.word0)])
    {
        pairFlags = PxPairFlag::eCONTACT_DEFAULT;
    }
    else
    {
        return PxFilterFlag::eSUPPRESS;
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
        //Cleanup();
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
        //delete m_scene.simulationEventCallback;
    }

    void Physics::SetGravity(Maths::Vec3 gravity)
    {
        Physic::PhysicsManager::GetInstance().GetPhysics().GetScene()->setGravity(PxVec3(gravity.x, gravity.y, gravity.z));
    }

    PxMaterial* CreateMaterialByType( PxPhysics* physics, MaterialType type)
    {
        PxReal staticFriction, dynamicFriction, restitution;

        switch (type) {
        case MaterialType::BOUNCY_BALL:
            staticFriction = 1;
            dynamicFriction = 1;
            restitution = 1;
            break;
        case MaterialType::ROCK:
            staticFriction = 0.5f;
            dynamicFriction = 0.3f;
            restitution = 0.2f;
            break;
        case MaterialType::ICE:
            staticFriction = 0.1f;
            dynamicFriction = 0.05f;
            restitution = 0.2f;
            break;
        case MaterialType::RUBBER:
            staticFriction = 0.7f;
            dynamicFriction = 0.5f;
            restitution = 0.6f;
            break;
        case MaterialType::WOOD:
            staticFriction = 0.6f;
            dynamicFriction = 0.4f;
            restitution = 0.3f;
            break;
        case MaterialType::METAL:
            staticFriction = 0.4f;
            dynamicFriction = 0.2f;
            restitution = 0.1f;
            break;
        case MaterialType::GLASS:
            staticFriction = 0.6f;
            dynamicFriction = 0.5f;
            restitution = 0.2f;
            break;
        default: //MaterialType::WOOD
            staticFriction = 0.6f;
            dynamicFriction = 0.4f;
            restitution = 0.3f;
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
        const int numThreads = std::thread::hardware_concurrency();
        sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(numThreads);
        sceneDesc.solverType = PxSolverType::eTGS;

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
        UpdateType();
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

    std::string ToString(MaterialType materialType)
    {
        switch (materialType)
        {
        case MaterialType::ROCK:
            return "ROCK";
        case MaterialType::BOUNCY_BALL:
            return "BOUNCY_BALL";
        case MaterialType::ICE:
            return "ICE";
        case MaterialType::RUBBER:
            return "RUBBER";
        case MaterialType::WOOD:
            return "WOOD";
        case MaterialType::METAL:
            return "METAL";
        case MaterialType::GLASS:
            return "GLASS";
        default:
            return "";
        }
    }

    MaterialType ToMaterialType(const std::string& str)
    {
        if (str == "ROCK")
            return MaterialType::ROCK;
        else if (str == "BOUNCY_BALL")
            return MaterialType::BOUNCY_BALL;
        else if (str == "ICE")
            return MaterialType::ICE;
        else if (str == "RUBBER")
            return MaterialType::RUBBER;
        else if (str == "WOOD")
            return MaterialType::WOOD;
        else if (str == "METAL")
            return MaterialType::METAL;
        else if (str == "GLASS")
            return MaterialType::GLASS;
        else
            return MaterialType::WOOD;
    }


 
    void PhysicsCollider::Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material)
    {

        if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
        {
            Maths::Vec3 boxSize = boxCollider->GetSize();
            boxSize = size;
        }
        else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
        {
            sphereCollider->SetRadius(size.x);
        }
        else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
        {
            capsuleCollider->SetRadius(size.x);
            capsuleCollider->SetHeight(size.y);

        }
        collider->SetCenter(center);
        collider->SetTriggerState(trigger);
    }
 

    void PhysicsCollider::Update()
    {

    }

    void PhysicsCollider::UpdateType()
    {
        if(m_physxActor)
            Physic::PhysicsManager::GetInstance().GetPhysics().GetScene()->removeActor(*m_physxActor);

        if (collider->rb) {
            PxTransform pose(PxVec3(collider->gameobject->transform->position.x, collider->gameobject->transform->position.y, collider->gameobject->transform->position.z));
            m_physxActor = Physic::PhysicsManager::GetInstance().GetPhysics().GetPhysics()->createRigidDynamic(pose);
            collider->rb->physicsRigidbody->SetRigidActor(m_physxActor);
            collider->rb->physicsRigidbody->Init();
        }
        else {
            Maths::Vec3 eulerRotation = collider->gameobject->transform->rotationEuler;
            Maths::Quaternion rotationQuat = Maths::Quaternion::ToQuaternion(eulerRotation);
            PxTransform pose(PxVec3(collider->gameobject->transform->position.x, collider->gameobject->transform->position.y, collider->gameobject->transform->position.z), PxQuat(rotationQuat.b, rotationQuat.c, rotationQuat.d, rotationQuat.a));
            m_physxActor = Physic::PhysicsManager::GetInstance().GetPhysics().GetPhysics()->createRigidStatic(pose);
        }
        m_physxActor->userData = collider->gameobject;
        Maths::Quaternion rotCol = collider->transform->rotation.ToQuaternion(collider->transform->rotationEuler);
        rotCol.Conjugate();
        Maths::Mat4 worldModel = collider->transform->GetGlobalMatrix() * rotCol.ToRotationMatrix();
        m_physxMaterial = collider->GetMaterial();
        PxMaterial* material = CreateMaterialByType(Physic::PhysicsManager::GetInstance().GetPhysics().GetPhysics(), m_physxMaterial);
        if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
        {
            Maths::Vec3 boxSize = boxCollider->GetSize();
            m_geometry.box = PxBoxGeometry(worldModel.data_4_4[0][0] * boxSize.x, worldModel.data_4_4[1][1] * boxSize.y, worldModel.data_4_4[2][2] * boxSize.z);
            m_shape = PxRigidActorExt::createExclusiveShape(*m_physxActor, m_geometry.box, *material);
        }
        else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
        {
            m_geometry.sphere = PxSphereGeometry(worldModel.data_4_4[0][0] * sphereCollider->GetRadius());
            m_shape = PxRigidActorExt::createExclusiveShape(*m_physxActor, m_geometry.sphere, *material);
        }
        else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
        {
            m_geometry.capsule = PxCapsuleGeometry(worldModel.data_4_4[0][0] * capsuleCollider->GetRadius(), worldModel.data_4_4[1][1] * capsuleCollider->GetHeight() * 0.5f);
            m_shape = PxRigidActorExt::createExclusiveShape(*m_physxActor, m_geometry.capsule, *material);
        }

        if (collider->GetTriggerState())
        {
            m_shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
            m_shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
        }
        PxFilterData filterData;
        filterData.word0 = collider->gameobject->GetLayer();
        m_shape->setSimulationFilterData(filterData);
        Physic::PhysicsManager::GetInstance().GetPhysics().GetScene()->addActor(*m_physxActor);

    }

    void Wrapper::PhysicsCollider::OnGuiChanged()
    {
        if (this)
        {
            Maths::Mat4 worldModel = collider->gameobject->transform->GetGlobalMatrix();
            PxShape* shapes[1];
            m_physxActor->getShapes(shapes, 1);
            shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, collider->GetTriggerState());
            PxFilterData filterData;
            filterData.word0 = collider->gameobject->GetLayer();
            shapes[0]->setSimulationFilterData(filterData);
            Maths::Vec3 collCenter = collider->GetCenter();
            PxVec3 position = PxVec3(worldModel.data_4_4[0][3] + collCenter.x, worldModel.data_4_4[1][3] + collCenter.y, worldModel.data_4_4[2][3] + collCenter.z);
            m_physxActor->setGlobalPose(PxTransform(position));
            m_physxMaterial = collider->GetMaterial();
            PxMaterial* material = CreateMaterialByType(Physic::PhysicsManager::GetInstance().GetPhysics().GetPhysics(), m_physxMaterial);
            PxMaterial* materials[] = { material };
            shapes[0]->setMaterials(materials, 1);
            if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
            {
                Maths::Vec3 boxSize = boxCollider->GetSize();
                PxVec3 newDimensions(boxSize.x * collider->gameobject->transform->scale.x, boxSize.y * collider->gameobject->transform->scale.y, boxSize.z * collider->gameobject->transform->scale.z);
                PxBoxGeometry boxGeometry;
                shapes[0]->getBoxGeometry(boxGeometry);
                boxGeometry.halfExtents = newDimensions * 0.5f;
                shapes[0]->setGeometry(boxGeometry);
            }
            else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
            {

                PxSphereGeometry sphereGeometry;
                shapes[0]->getSphereGeometry(sphereGeometry);
                sphereGeometry.radius = sphereCollider->GetRadius() * collider->gameobject->transform->scale.x;
                shapes[0]->setGeometry(sphereGeometry);
            }
            else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
            {
                PxCapsuleGeometry capsuleGeometry;
                shapes[0]->getCapsuleGeometry(capsuleGeometry);
                capsuleGeometry.radius = capsuleCollider->GetRadius() * collider->gameobject->transform->scale.x;
                capsuleGeometry.halfHeight = capsuleCollider->GetHeight() * collider->gameobject->transform->scale.y;
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
            Maths::Vec3 collCenter = collider->GetCenter();
            position = PxVec3(worldModel.data_4_4[0][3] + collCenter.x, worldModel.data_4_4[1][3] + collCenter.y, worldModel.data_4_4[2][3] + collCenter.z);
            m_physxActor->setGlobalPose(PxTransform(position, pxRotation));
            PxShape* shape;
            m_physxActor->getShapes(&shape, 1);

            if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider))
            {
                Maths::Vec3 boxSize = boxCollider->GetSize();
                m_geometry.box.halfExtents = PxVec3(boxSize.x * collider->gameobject->transform->scale.x, boxSize.y * collider->gameobject->transform->scale.y, boxSize.z * collider->gameobject->transform->scale.z);
                shape->setGeometry(m_geometry.box);
            }
            else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
            {
                std::array<float, 3> scaleValues = { collider->gameobject->transform->scale.x,collider->gameobject->transform->scale.y, collider->gameobject->transform->scale.z };
                float max_scale = *std::max_element(scaleValues.begin(), scaleValues.end());

                m_geometry.sphere.radius = sphereCollider->GetRadius() * max_scale;
                shape->setGeometry(m_geometry.sphere);


            }
            else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
            {
                std::array<float, 2> scaleValues = { collider->gameobject->transform->scale.x, collider->gameobject->transform->scale.y };
                float max_scale = *std::max_element(scaleValues.begin(), scaleValues.end());
                m_geometry.capsule.radius = capsuleCollider->GetRadius() * max_scale;
                m_geometry.capsule.halfHeight = capsuleCollider->GetHeight() * worldModel.data_4_4[2][2];
                shape->setGeometry(m_geometry.capsule);
            }
        }
      
    }


    Wrapper::PhysicsJoint::PhysicsJoint()
    {
        d6joint = nullptr;
    }

    Wrapper::PhysicsJoint::~PhysicsJoint()
    {
        if (d6joint)
        {
            d6joint->release();
            d6joint = nullptr;
        }
    }

    void Wrapper::PhysicsJoint::Setup()
    {
        PxPhysics *gPhysics = Physic::PhysicsManager::GetInstance().GetPhysics().GetPhysics();
        PxRigidActor* selfRigidActor = joint->GetSelfRigidbody()->physicsRigidbody->GetRigidActor();

        if (FixedJoint* fixedJoint = dynamic_cast<FixedJoint*>(joint))
        {
            d6joint = PxD6JointCreate(*gPhysics, selfRigidActor, PxTransform(PxVec3(0)), nullptr, PxTransform(PxVec3(0)));
            d6joint->setMotion(PxD6Axis::eX, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eY, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eZ, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eTWIST, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLOCKED);

        }
        else if (HingeJoint* hingeJoint = dynamic_cast<HingeJoint*>(joint))
        {
            PxVec3 anchor = PxVec3(hingeJoint->GetAnchor().x, hingeJoint->GetAnchor().y, hingeJoint->GetAnchor().z);
            Maths::Quaternion axisQuat = Maths::Quaternion::ToQuaternion(hingeJoint->GetAxis());
            PxQuat axis = PxQuat(axisQuat.b, axisQuat.c, axisQuat.d, axisQuat.a);
            PxVec3 connectedAnchor = PxVec3(hingeJoint->GetConnectedAnchor().x, hingeJoint->GetConnectedAnchor().y, hingeJoint->GetConnectedAnchor().z);

            d6joint = PxD6JointCreate(*gPhysics, selfRigidActor, PxTransform(anchor,axis), nullptr, PxTransform(connectedAnchor));

            d6joint->setMotion(PxD6Axis::eX, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eY, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eZ, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eTWIST, PxD6Motion::eFREE);
            d6joint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLOCKED);

            PxD6JointDrive drive(hingeJoint->GetMotorForce(), hingeJoint->GetMotorSpeed(), true);
            d6joint->setDrive(PxD6Drive::eTWIST, drive);

        }
        else if (SpringJoint* springJoint = dynamic_cast<SpringJoint*>(joint))
        {
            PxTransform anchor(PxVec3(springJoint->GetAnchor().x, springJoint->GetAnchor().y, springJoint->GetAnchor().z));
            d6joint = PxD6JointCreate(*gPhysics, selfRigidActor, anchor, nullptr, PxTransform(PxVec3(0)));

            d6joint->setMotion(PxD6Axis::eX, PxD6Motion::eFREE);
            d6joint->setMotion(PxD6Axis::eY, PxD6Motion::eFREE);
            d6joint->setMotion(PxD6Axis::eZ, PxD6Motion::eFREE);
            d6joint->setMotion(PxD6Axis::eTWIST, PxD6Motion::eFREE);
            d6joint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eFREE);
            d6joint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eFREE);

            PxSpring spring(springJoint->GetSpring().spring, springJoint->GetSpring().damper);
            d6joint->setLinearLimit(PxD6Axis::eX, PxJointLinearLimitPair(springJoint->GetMinDistance(), springJoint->GetMaxDistance(), spring));
            d6joint->setLinearLimit(PxD6Axis::eY, PxJointLinearLimitPair(springJoint->GetMinDistance(), springJoint->GetMaxDistance(), spring));
            d6joint->setLinearLimit(PxD6Axis::eZ, PxJointLinearLimitPair(springJoint->GetMinDistance(), springJoint->GetMaxDistance(), spring));

        }
        else if (ConfigurableJoint* configurableJoint = dynamic_cast<ConfigurableJoint*>(joint))
        {

            PxTransform anchor(PxVec3(configurableJoint->GetAnchor().x, configurableJoint->GetAnchor().y, configurableJoint->GetAnchor().z));
            PxTransform connectedAnchor(PxVec3(configurableJoint->GetConnectedAnchor().x, configurableJoint->GetConnectedAnchor().y, configurableJoint->GetConnectedAnchor().z));

            d6joint = PxD6JointCreate(*gPhysics, selfRigidActor, anchor, nullptr, connectedAnchor);

            // Set motion
            d6joint->setMotion(PxD6Axis::eX, configurableJoint->GetMotion().x == 1 ? PxD6Motion::eFREE : PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eY, configurableJoint->GetMotion().y == 1 ? PxD6Motion::eFREE : PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eZ, configurableJoint->GetMotion().z == 1 ? PxD6Motion::eFREE : PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eTWIST, configurableJoint->GetAngularMotion().x == 1 ? PxD6Motion::eFREE : PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eSWING1, configurableJoint->GetAngularMotion().y == 1 ? PxD6Motion::eFREE : PxD6Motion::eLOCKED);
            d6joint->setMotion(PxD6Axis::eSWING2, configurableJoint->GetAngularMotion().z == 1 ? PxD6Motion::eFREE : PxD6Motion::eLOCKED);

            Spring linearLimitSpring = configurableJoint->GetLinearLimitSpring();
            Limit linearLimit = configurableJoint->GetLinearLimit();

            PxReal limitExtent = linearLimit.limit;
            PxSpring limitSpring = { linearLimitSpring.spring, linearLimitSpring.damper };

            PxJointLinearLimit linearLimitX(limitExtent, limitSpring);
            PxJointLinearLimit linearLimitY(limitExtent, limitSpring);
            PxJointLinearLimit linearLimitZ(limitExtent, limitSpring);

            linearLimitX.contactDistance = linearLimit.contactDistance;
            linearLimitX.bounceThreshold = linearLimit.bounciness;

            linearLimitY.contactDistance = linearLimit.contactDistance;
            linearLimitY.bounceThreshold = linearLimit.bounciness;

            linearLimitZ.contactDistance = linearLimit.contactDistance;
            linearLimitZ.bounceThreshold = linearLimit.bounciness;

            PxD6JointDrive driveX(configurableJoint->GetXDrive().positionSpring, configurableJoint->GetXDrive().positionDamper, configurableJoint->GetXDrive().maximumForce);
            PxD6JointDrive driveY(configurableJoint->GetYDrive().positionSpring, configurableJoint->GetYDrive().positionDamper, configurableJoint->GetYDrive().maximumForce);
            PxD6JointDrive driveZ(configurableJoint->GetZDrive().positionSpring, configurableJoint->GetZDrive().positionDamper, configurableJoint->GetZDrive().maximumForce);
            PxD6JointDrive driveSwing(configurableJoint->GetAngularYZDrive().positionSpring, configurableJoint->GetAngularYZDrive().positionDamper, configurableJoint->GetAngularYZDrive().maximumForce);
            PxD6JointDrive driveTwist(configurableJoint->GetAngularXDrive().positionSpring, configurableJoint->GetAngularXDrive().positionDamper, configurableJoint->GetAngularXDrive().maximumForce);
            PxD6JointDrive driveSlerp(configurableJoint->GetAngularYDrive().positionSpring, configurableJoint->GetAngularYDrive().positionDamper, configurableJoint->GetAngularYDrive().maximumForce);
            d6joint->setDrive(PxD6Drive::eX, driveX);
            d6joint->setDrive(PxD6Drive::eY, driveY);
            d6joint->setDrive(PxD6Drive::eZ, driveZ);
            d6joint->setDrive(PxD6Drive::eSWING, driveSwing);
            d6joint->setDrive(PxD6Drive::eTWIST, driveTwist);
            d6joint->setDrive(PxD6Drive::eSLERP, driveSlerp);

            //target+linear needed
        }
        d6joint->setBreakForce(joint->GetBreakForce(), joint->GetBreakTorque());
        
    }

    void Wrapper::PhysicsJoint::Init()
    {
    }

    void Wrapper::PhysicsJoint::OnGuiChanged()
    {
    }

    void PhysicsRigidbody::Init()
    {
        rigidbody->gameobject->transform->RegisterTransformChangedCallback([this]() { OnTransformChanged(); });

        if (rigidbody->IsGravityDifferent())
            m_physxActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
        else
            m_physxActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);

        Maths::Quaternion eulerRot = Maths::Quaternion::ToQuaternion(rigidbody->gameobject->transform->rotationEuler);
        Maths::Vec3 collCenter = rigidbody->col->GetCenter();
        PxTransform pose(PxVec3(rigidbody->gameobject->transform->position.x+collCenter.x, rigidbody->gameobject->transform->position.y + collCenter.y, rigidbody->gameobject->transform->position.z + collCenter.z), PxQuat( eulerRot.b, eulerRot.c, eulerRot.d, eulerRot.a));
        m_physxActor->setGlobalPose(pose);
        m_physxActor->is<PxRigidDynamic>()->setMass(rigidbody->GetMass());
    }

    Maths::Vec3 PhysicsRigidbody::GetVelocity()
    {
        if (m_physxActor)
        {
            PxRigidDynamic* dynamicActor = m_physxActor->is<PxRigidDynamic>();
            PxVec3 vel = dynamicActor->getLinearVelocity();
            return Maths::Vec3(vel.x, vel.y, vel.z);
        }


    }

    void Wrapper::PhysicsRigidbody::SetVelocity(Maths::Vec3 velocity)
    {
        if (m_physxActor)
        {
            PxRigidDynamic* dynamicActor = m_physxActor->is<PxRigidDynamic>();
            dynamicActor->setLinearVelocity(PxVec3(velocity.x, velocity.y, velocity.z), false);
        }
    }

    void Wrapper::PhysicsRigidbody::AddForce(Maths::Vec3 force)
    {
        if (m_physxActor)
        {
            PxRigidDynamic* dynamicActor = m_physxActor->is<PxRigidDynamic>();
            dynamicActor->addForce(PxVec3(force.x, force.y, force.z));
        }
        
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

                PxRigidDynamic* dynamicActor = m_physxActor->is<PxRigidDynamic>();

                if (!m_transformChangedExternally)
                {
                    if (dynamicActor->isSleeping())
                        dynamicActor->wakeUp();

                    if (rigidbody->IsGravityDifferent())
                    {
                        Maths::Vec3 gravity = rigidbody->GetGravity();
                        PxVec3 force = PxVec3(gravity.x, gravity.y, gravity.z);
                        dynamicActor->addForce(force);
                    }


                    PxTransform updatedTransform = dynamicActor->getGlobalPose();
                    Maths::Vec3 newPosition = Maths::Vec3(updatedTransform.p.x, updatedTransform.p.y, updatedTransform.p.z);
                    rigidbody->gameobject->transform->position = newPosition-rigidbody->col->GetCenter();
                    PxQuat updatedRotation = updatedTransform.q;
                    
                    Maths::Quaternion newRotation = Maths::Quaternion(updatedRotation.w, updatedRotation.x, updatedRotation.y, updatedRotation.z) ;

                    
                      
                    rigidbody->gameobject->transform->rotation = newRotation;
                    rigidbody->gameobject->transform->rotationEuler = newRotation.ToEulerAngles();
                    
                }
                else if (m_transformChangedExternally)
                {
                    dynamicActor->putToSleep();
                    rigidbody->SetVelocity(Maths::Vec3(0, 0, 0));

                    m_delay -= Engine::Input::deltaTime;
                    if(m_delay<=0)
                        m_transformChangedExternally = false;
                }
            }

        }
    }

    void Wrapper::PhysicsRigidbody::OnGuiChanged()
    {
        if (this && m_physxActor)
        {
            m_physxActor->is<PxRigidDynamic>()->setMass(rigidbody->GetMass());

            if (rigidbody->IsGravityDifferent())
                m_physxActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
            else
                m_physxActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
        }
    }

    void PhysicsRigidbody::OnTransformChanged()
    {
        if (this)
        {

            m_transformChangedExternally = true;

            m_delay = 1.5f;
        }
    }

  

}