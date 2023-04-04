#pragma once
#include <Physx/PxPhysicsAPI.h>


#ifdef PHYSICSWRAPPER_EXPORTS
#define  PHYSICSWRAPPER_API __declspec(dllexport)
#else
#define  PHYSICSWRAPPER_API __declspec(dllimport)
#endif

namespace Physic
{
    class Collider;
    class Rigidbody;
}

using namespace physx;
using namespace Physic;

namespace Wrapper
{
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

	class PHYSICSWRAPPER_API Physics //class to change in case we use other physics library
	{
    public:
        Physics();
        ~Physics();
        void Init();
        void Update(float deltaTime);
        void Cleanup();
        PxPhysics* getPhysics() const { return mPhysics; }
        PxScene* getScene() const { return mScene; }

    private:
        static PxDefaultErrorCallback gDefaultErrorCallback;
        static PxDefaultAllocator gDefaultAllocatorCallback;

        PxFoundation* mFoundation;
        PxPhysics* mPhysics;
        PxScene* mScene;
        PxPvd* mPvd;

        void CreateFoundation();
        void CreatePhysics();
        void CreateScene();
        void SetupVisualDebugger();

	};

    class PHYSICSWRAPPER_API PhysicsCollider
    {
    public:
        void Init();
        void InitCube();
        void InitSphere();
        void InitCapsule();

        Collider* collider;


    private:

        union Geometry
        {
            PxBoxGeometry box;
            PxSphereGeometry sphere;
            PxCapsuleGeometry capsule;

        } geometry;

        PxShape* shape;


    };

    class PHYSICSWRAPPER_API PhysicsRigidbody
    {
    public:

        void Update();

        Rigidbody* rigidbody;

        PxRigidActor* getRigidActor() { return PhysxActor; }
        MaterialType getMaterialType() { return PhysxMaterial; }
        void setMaterialType(MaterialType type) { PhysxMaterial = type; }
    private:
        PxRigidActor* PhysxActor;
        MaterialType PhysxMaterial;

    };

}
