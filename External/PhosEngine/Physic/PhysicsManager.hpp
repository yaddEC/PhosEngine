#pragma once

#include "dllInclude.hpp"
#include <Wrapper/PhysicsWrapper.hpp>

namespace Physic {

    class PhysicsManager {
    public:
        PhysicsManager() = default;
        PhysicsManager(const PhysicsManager&) = delete;
        ~PhysicsManager();

        void Init();
        void Update(float deltaTime);
        void Cleanup();

        PhysicsManager& operator=(const PhysicsManager&) = delete;

        static PhysicsManager& GetInstance() {
            static PhysicsManager instance;
            return instance;
        }

        inline Wrapper::Physics& GetPhysics() { return m_physics; }

    private:
        Wrapper::Physics m_physics;
    };

}