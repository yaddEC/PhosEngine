#pragma once
#include <Physx/PxPhysicsAPI.h>
#include <Maths/Maths.hpp>

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

    void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)override {};
    void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)override {};
    void onWake(PxActor** actors, PxU32 count) override {};
    void onSleep(PxActor** actors, PxU32 count)override {};



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
    enum ColliderType
    {
        BOX,
        SPHERE,
        CAPSULE
    };

	class PHOSENGINE_API Physics //class to change in case we use other physics library
	{
    public:
        Physics() {};
        ~Physics();
        void Init();
        void Update(float deltaTime);
        void Cleanup();
        PxPhysics* getPhysics() const { return mPhysics; }
        PxScene* getScene() const { return mScene; }

    private:
        static PxDefaultErrorCallback gDefaultErrorCallback;
        static PxDefaultAllocator gDefaultAllocatorCallback;

        PxFoundation* mFoundation = nullptr;
        PxPhysics* mPhysics = nullptr;
        PxScene* mScene = nullptr;
        PxPvd* mPvd = nullptr;

        void CreateFoundation();
        void CreatePhysics();
        void CreateScene();
        void SetupVisualDebugger();

	};

    class PHOSENGINE_API PhysicsCollider
    {
    public:
        PhysicsCollider() {};
        ~PhysicsCollider();
        void Init();
        void Update();
        void Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material);

        Collider* collider;


    private:

        union Geometry
        {
            PxBoxGeometry box;
            PxSphereGeometry sphere;
            PxCapsuleGeometry capsule;
            Geometry() {}

        } geometry;

        PxShape* shape = nullptr;
        PxRigidActor* PhysxActor = nullptr;
        MaterialType PhysxMaterial;

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

        Rigidbody* rigidbody;

        PxRigidActor* getRigidActor() { return PhysxActor; }
        void setRigidActor(PxRigidActor* actor) { PhysxActor = actor; }
    private:
        PxRigidActor* PhysxActor = nullptr;
    

    };

     bool RayCast(Maths::Vec3 origin, Maths::Vec3 direction, float maxDistance, RayCastHit& hit);
}
