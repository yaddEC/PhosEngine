#pragma once

#include "dllInclude.hpp"

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