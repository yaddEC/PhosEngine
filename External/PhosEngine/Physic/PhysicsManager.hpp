#pragma once

#ifdef PHYSICSMANAGER_EXPORTS
#define PHYSICSMANAGER_API __declspec(dllexport)
#else
#define PHYSICSMANAGER_API __declspec(dllimport)
#endif

namespace Wrapper
{
    class Physics;
}

namespace Physic
{
   class PhysicsManager
    {
    public:
        PhysicsManager();
        ~PhysicsManager();

        void Init();
        void Update(float deltaTime);
        void Cleanup();

        Wrapper::Physics* getPhysics() { return physics; }

    private:
        Wrapper::Physics* physics;

    };
}