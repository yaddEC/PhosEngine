#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>
#include "dllInclude.hpp"

namespace Wrapper
{
    class PhysicsRigidbody;
}

namespace Engine
{
    class GameObject;
}

namespace Physic
{
    class PHOSENGINE_API Rigidbody : public Engine::MonoBehaviour
    {
    public:
        Rigidbody();
        ~Rigidbody() {};


        Maths::Vec3 gravity = Maths::Vec3(0, -20, 0);
        Maths::Vec3 velocity;
        float mass = 1;
        bool reset = false;

        Wrapper::PhysicsRigidbody* physicsRigidbody;


        void Init();
        void Start() override {};
        void Update() override;
        void OnTriggerEnter(Engine::GameObject* go) override {};
        void OnTriggerStay(Engine::GameObject* go) override {};
        void OnTriggerExit(Engine::GameObject* go) override {};
        void OnCollisionEnter(Engine::GameObject* go) override {};
        void OnCollisionStay(Engine::GameObject* go) override {};
        void OnCollisionExit(Engine::GameObject* go) override {};
        void GUIUpdate() override {};
        void OnDestroy() override {};

        Reflection::ClassMetaData& GetMetaData() override;
    };
}