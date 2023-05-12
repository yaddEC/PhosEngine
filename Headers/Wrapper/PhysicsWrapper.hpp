#pragma once
#include <Physx/PxPhysicsAPI.h>
#include <Maths/Maths.hpp>
#include <map>

#include "dllInclude.hpp"

namespace Physic
{
    class Collider;
    class Rigidbody;
}

namespace Engine
{
    class GameObject;
}

using namespace physx;
using namespace Physic;

class MySimulationEventCallback : public PxSimulationEventCallback
{
public:
    MySimulationEventCallback();
    ~MySimulationEventCallback();

    void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;
    void onTrigger(PxTriggerPair* pairs, PxU32 count) override;
    void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override {};
    void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override {};
    void onWake(PxActor** actors, PxU32 count) override {};
    void onSleep(PxActor** actors, PxU32 count) override {};
};

namespace Wrapper
{
    int countRigidActors(PxScene* scene);

    enum MaterialType
    {
        ROCK,
        BOUNCY_BALL,
        ICE,
        RUBBER,
        WOOD,
        METAL,
        GLASS
    };

    enum class ColliderType
    {
        BOX,
        SPHERE,
        CAPSULE
    };

    class PHOSENGINE_API Physics
    {
    public:
        Physics() {};
        ~Physics();

        void Init();
        void Update(float deltaTime);
        void Cleanup();

        inline PxPhysics* GetPhysics() const { return m_physics; }
        inline PxScene* GetScene() const { return m_scene; }
        std::map<std::pair<PxU32, PxU32>, bool> layerInteractionMatrix;
    private:
        static PxDefaultErrorCallback m_defaultErrorCallback;
        static PxDefaultAllocator m_defaultAllocatorCallback;

        PxFoundation* m_foundation = nullptr;
        PxPhysics* m_physics = nullptr;
        PxScene* m_scene = nullptr;
        PxPvd* m_pvd = nullptr;

        void CreateFoundation();
        void CreatePhysics();
        void CreateScene();
        void SetupVisualDebugger();
       
        static PxFilterFlags CustomFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
            PxFilterObjectAttributes attributes1, PxFilterData filterData1,
            PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);
    };

    class PHOSENGINE_API PhysicsCollider
    {
    public:
        PhysicsCollider() {};
        ~PhysicsCollider() {};

        void Init();
        void Update();
        void Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material);
        void OnGuiChanged();

        Collider* collider;

    private:

        void OnTransformChanged();
        union Geometry
        {
            PxBoxGeometry box;
            PxSphereGeometry sphere;
            PxCapsuleGeometry capsule;
            Geometry() {}
        } m_geometry;

        PxShape* m_shape = nullptr;
        PxRigidActor* m_physxActor = nullptr;
        MaterialType m_physxMaterial;

        
    };

    class PHOSENGINE_API RayCastHit
    {
    public:
        Engine::GameObject* objectHit;
        float distance;
        Maths::Vec3 normHit;
        Maths::Vec3 impactPos;
    };

    class PHOSENGINE_API PhysicsRigidbody
    {
    public:
        PhysicsRigidbody() {};
        ~PhysicsRigidbody() {};

        void Init();
        void Update();
        void OnGuiChanged();

        Rigidbody* rigidbody;

        inline PxRigidActor* GetRigidActor() { return m_physxActor; }
        inline void SetRigidActor(PxRigidActor* actor) { m_physxActor = actor; }

    private:
        void OnTransformChanged();
        PxRigidActor* m_physxActor = nullptr;
        bool m_transformChangedExternally ;
    };

     bool RayCast(Maths::Vec3 origin, Maths::Vec3 direction, float maxDistance, RayCastHit& hit);
}
