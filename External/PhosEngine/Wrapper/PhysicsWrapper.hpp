#pragma once
#include <Physx/PxPhysicsAPI.h>
#include <Maths/Maths.hpp>
#include <map>
#include <vector>
#include "dllInclude.hpp"

namespace Physic
{
    class Collider;
    class Rigidbody;
    class Joint;
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

    enum class MaterialType
    {
        WOOD,
        BOUNCY_BALL,
        ICE,
        RUBBER,
        ROCK,
        METAL,
        GLASS
    };

    std::string ToString(MaterialType materialType);

    MaterialType ToMaterialType(const std::string& str);

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

        static void SetGravity(Maths::Vec3 gravity);

        inline PxPhysics* GetPhysics() const { return m_physics; }
        inline PxScene* GetScene() const { return m_scene; }


        static void CreateLayer(const std::string layerName);
        static std::string GetLayerName(unsigned int Layer);
        static unsigned int GetLayerID(const std::string layerName);
        static bool GetLayerCollision(std::string layerA, std::string layerB);
        static void SetLayerCollision(std::string layerA, std::string layerB, bool shouldCollide);


        static std::vector<std::string>* GetLayerNames();
        static std::map<std::pair<PxU32, PxU32>, bool>* GetLayerInteractions();
        static std::map<std::string, PxU32>* GetNameToIndex();

        std::map<std::pair<PxU32, PxU32>, bool> layerInteractionMatrix;
        std::vector<std::string> layerNames;
        std::map<std::string, PxU32> layerNameToIndexMap;
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


    };

    class PHOSENGINE_API PhysicsCollider
    {
    public:
        PhysicsCollider() {};
        ~PhysicsCollider() {};

        void Init();
        void Update();
        void UpdateType();
        void Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material);
        void OnGuiChanged();

        Collider* collider = nullptr;

    private:

        void OnTransformChanged();
        union Geometry
        {
            PxBoxGeometry box;
            PxSphereGeometry sphere;
            PxCapsuleGeometry capsule;
            Geometry() : box() {}
        } m_geometry;

        PxShape* m_shape = nullptr;
        PxRigidActor* m_physxActor = nullptr;
        MaterialType m_physxMaterial = MaterialType::ROCK;

    };

    class PHOSENGINE_API RayCastHit
    {
    public:
        Engine::GameObject* objectHit = nullptr;
        float distance = 0;
        Maths::Vec3 normHit;
        Maths::Vec3 impactPos;
    };

    class PHOSENGINE_API PhysicsJoint
    {

    public:

        PhysicsJoint();
        ~PhysicsJoint();

        void Setup();
        void Init();

        void OnGuiChanged();

        Joint* joint;

        PxD6Joint* d6joint;
    private:


    };

    class PHOSENGINE_API PhysicsRigidbody
    {
    public:
        PhysicsRigidbody() {};
        ~PhysicsRigidbody() {};

        void Init();
        void Update();
        void OnGuiChanged();

        Maths::Vec3 GetVelocity();
        void SetVelocity(Maths::Vec3 velocity);
        void AddForce(Maths::Vec3 force);
        Rigidbody* rigidbody = nullptr;

        inline PxRigidActor* GetRigidActor() { return m_physxActor; }
        inline void SetRigidActor(PxRigidActor* actor) { m_physxActor = actor; }

    private:
        void OnTransformChanged();
        PxRigidActor* m_physxActor = nullptr;
        bool m_transformChangedExternally = false;
        float m_delay;
    };

    bool RayCast(Maths::Vec3 origin, Maths::Vec3 direction, float maxDistance, RayCastHit& hit);
}
