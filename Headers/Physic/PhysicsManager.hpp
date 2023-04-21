#pragma once

#include "dllInclude.hpp"
#include <Wrapper/PhysicsWrapper.hpp>


namespace Physic
{
   class PhysicsManager
    {
    public:


        void Init();
        void Update(float deltaTime);
        void Cleanup();

        PhysicsManager(const PhysicsManager&) = delete;
        PhysicsManager& operator=(const PhysicsManager&) = delete;

        static PhysicsManager& GetInstance()
        {
            static PhysicsManager instance;
            return instance;
        }


        Wrapper::Physics& getPhysics() { return physics; }

    private:
        PhysicsManager() {};
        ~PhysicsManager() ;
        Wrapper::Physics physics;

    };
}