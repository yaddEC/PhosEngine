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

void  Wrapper::Physics::saveLayerInfo()
{
    std::map < std::pair<PxU32, PxU32>, bool>* layerInteractionMatrix = Wrapper::Physics::GetLayerInteractions();
    std::vector<std::string>* layerNames = Wrapper::Physics::GetLayerNames();
    std::map<std::string, PxU32>* layerNameToIndexMap = Wrapper::Physics::GetNameToIndex();

    std::ofstream out("CollisionSettings.phs");
    if (!out) {
        std::cerr << "Failed to open CollisionSettings.phs for writing.\n";
        return;
    }

    out << layerNames->size() << '\n';
    for (const auto& name : *layerNames) {
        out << name << '\n';
    }

    out << layerNameToIndexMap->size() << '\n';
    for (const auto& kv : *layerNameToIndexMap) {
        out << kv.first << ' ' << kv.second << '\n';
    }

    out << layerInteractionMatrix->size() << '\n';
    for (const auto& kv : *layerInteractionMatrix) {
        out << kv.first.first << ' ' << kv.first.second << ' ' << kv.second << '\n';
    }
}


void Wrapper::Physics::LoadLayerInfo()
{

    std::map < std::pair<PxU32, PxU32>, bool>* layerInteractionMatrix = Wrapper::Physics::GetLayerInteractions();
    std::vector<std::string>* layerNames = Wrapper::Physics::GetLayerNames();
    std::map<std::string, PxU32>* layerNameToIndexMap = Wrapper::Physics::GetNameToIndex();
   
    std::ifstream in("CollisionSettings.phs");
    if (!in) {
        std::cerr << "Failed to open CollisionSettings.phs for reading.\n";
        std::ofstream out("CollisionSettings.phs");
        layerNames->push_back("Default");
        (*layerNameToIndexMap)["Default"] = 0;
        (*layerInteractionMatrix)[std::make_pair(0, 0)] = true;
        return;
    }
    if (in.peek() == std::ifstream::traits_type::eof())
    {
        layerNames->push_back("Default");
        (*layerNameToIndexMap)["Default"] = 0;
        (*layerInteractionMatrix)[std::make_pair(0, 0)] = true;
        return;
    }

    layerNames->clear();
    layerNameToIndexMap->clear();
    layerInteractionMatrix->clear();

    std::size_t numNames;
    in >> numNames;
    in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    layerNames->resize(numNames);
    for (std::string& name : *layerNames) {
        std::getline(in, name);
    }

    std::size_t numMappings;
    in >> numMappings;
    in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    for (std::size_t i = 0; i < numMappings; ++i) {
        std::string name;
        PxU32 index;
        in >> name >> index;
        (*layerNameToIndexMap)[name] = index;
        in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }

    std::size_t numInteractions;
    in >> numInteractions;
    in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    for (std::size_t i = 0; i < numInteractions; ++i) {
        PxU32 key1, key2;
        bool value;
        in >> key1 >> key2 >> value;
        (*layerInteractionMatrix)[std::make_pair(key1, key2)] = value;
        (*layerInteractionMatrix)[std::make_pair(key2, key1)] = value;
        in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
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
        case MaterialType::BOUNCY_BALL:
            staticFriction = 0.5f;
            dynamicFriction = 0.3f;
            restitution = 0.8f;
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
        default: //MaterialType::ROCK
            staticFriction = 0.5f;
            dynamicFriction = 0.3f;
            restitution = 0.8f;
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
            Maths::Vec3 boxSize = boxCollider->GetSize();
            m_geometry.box = PxBoxGeometry(worldModel.data_4_4[0][0] * boxSize.x , worldModel.data_4_4[1][1] * boxSize.y , worldModel.data_4_4[2][2] * boxSize.z );
            m_shape = PxRigidActorExt::createExclusiveShape(*m_physxActor, m_geometry.box, *material);
        }
        else if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider))
        {
            m_geometry.sphere = PxSphereGeometry(worldModel.data_4_4[0][0] * sphereCollider->GetRadius());
            m_shape = PxRigidActorExt::createExclusiveShape(*m_physxActor, m_geometry.sphere, *material);
        }
        else if (CapsuleCollider* capsuleCollider = dynamic_cast<CapsuleCollider*>(collider))
        {
            m_geometry.capsule = PxCapsuleGeometry(worldModel.data_4_4[0][0] * capsuleCollider->GetRadius(), worldModel.data_4_4[1][1] * capsuleCollider->GetHeight()  * 0.5f);
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

    void PhysicsRigidbody::Init()
    {
        rigidbody->gameobject->transform->RegisterTransformChangedCallback([this]() { OnTransformChanged(); });

        Maths::Quaternion eulerRot = Maths::Quaternion::ToQuaternion(rigidbody->gameobject->transform->rotationEuler);
        Maths::Vec3 collCenter = rigidbody->col->GetCenter();
       PxTransform pose(PxVec3(rigidbody->gameobject->transform->position.x+collCenter.x, rigidbody->gameobject->transform->position.y + collCenter.y, rigidbody->gameobject->transform->position.z + collCenter.z), PxQuat( eulerRot.b, eulerRot.c, eulerRot.d, eulerRot.a));
       m_physxActor->setGlobalPose(pose);
       m_physxActor->is<PxRigidDynamic>()->setMass(rigidbody->GetMass());

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
                    Maths::Vec3 velocity = rigidbody->GetVelocity();
                    PxVec3 force = PxVec3(velocity.x, velocity.y, velocity.z) * rigidbody->GetMass();

                    dynamicActor->addForce(force);

                    PxTransform updatedTransform = dynamicActor->getGlobalPose();
                    Maths::Vec3 newPosition = Maths::Vec3(updatedTransform.p.x, updatedTransform.p.y, updatedTransform.p.z);
                    rigidbody->gameobject->transform->position = newPosition-rigidbody->col->GetCenter();
                    PxQuat updatedRotation = updatedTransform.q;
                    
                    Maths::Quaternion newRotation = Maths::Quaternion(updatedRotation.w, updatedRotation.x, updatedRotation.y, updatedRotation.z) ;

                      
                    rigidbody->gameobject->transform->rotation = newRotation;
                    rigidbody->gameobject->transform->rotationEuler = newRotation.ToEulerAngles();
                    
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
        if (this && m_physxActor)
        {
            m_physxActor->is<PxRigidDynamic>()->setMass(rigidbody->GetMass());
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