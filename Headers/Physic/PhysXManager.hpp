#pragma once

#include <Physx/PxPhysicsAPI.h>
#include <memory>

#ifdef PHYSXMANAGER_EXPORTS
#define PHYSXMANAGER_API __declspec(dllexport)
#else
#define PHYSXMANAGER_API __declspec(dllimport)
#endif

using namespace physx;
namespace Physic
{
    enum MaterialType {
        ROCK,
        BOUNCY_BALL,
        ICE,
        RUBBER,
        WOOD,
        METAL,
        GLASS
    };

    class PhysXManager
    {
    public:
        PhysXManager();
        ~PhysXManager();

        void Init();
        void Update(float deltaTime);
        void Cleanup();
        PxPhysics* getPhysics() const { return mPhysics; }
        PxScene* getScene() const { return mScene; }
        PxMaterial* createMaterialByType(const PxPhysics* const& physics, MaterialType type);

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
}