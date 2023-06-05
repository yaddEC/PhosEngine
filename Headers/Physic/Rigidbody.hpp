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

        Collider* col;
        Wrapper::PhysicsRigidbody* physicsRigidbody;


        void Init();
        void Start() override;
        void Update() override;
        void Awake() override;
        void OnTriggerEnter(Engine::GameObject* go) override {};
        void OnTriggerStay(Engine::GameObject* go) override {};
        void OnTriggerExit(Engine::GameObject* go) override {};
        void OnCollisionEnter(Engine::GameObject* go) override {};
        void OnCollisionStay(Engine::GameObject* go) override {};
        void OnCollisionExit(Engine::GameObject* go) override {};
        void GUIUpdate() override;
        void OnInspector() override;
        void OnDestroy() override;
        Maths::Vec3 GetGravity() { return m_gravity; };
        float GetMass() { return m_mass; };
        void SetGravity(Maths::Vec3 gravity);
        Maths::Vec3 GetVelocity();
        void SetVelocity(Maths::Vec3 velocity);
        void AddForce(Maths::Vec3 force);
        void ClearForce();
    
        void SetMass(float mass);
        bool IsGravityDifferent();
        void setDifferentGravity(bool ownGravity);

        bool IsKinematic();
        void setKinematic(bool kinematic);

        Reflection::ClassMetaData& GetMetaData() override;

    private:
        bool m_differentGravity;
        bool m_isKinematic = false;
        Maths::Vec3 m_gravity = Maths::Vec3(0, -20, 0);
        Maths::Vec3 m_velocity;
        float m_mass = 1;

    };
}