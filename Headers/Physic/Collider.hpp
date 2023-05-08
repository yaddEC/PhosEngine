#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>

#include "dllInclude.hpp"

namespace Wrapper
{
    class PhysicsCollider;
    enum MaterialType;
}

namespace Engine
{
    class GameObject;
    class Transform;
}

namespace Physic
{
    class Rigidbody;

    class PHOSENGINE_API Collider : public Engine::MonoBehaviour
    {
    public:
        Collider();

        bool isTrigger = false;
        Maths::Vec3 center;
        Rigidbody* rb;
        Wrapper::PhysicsCollider* physicsCollider;

        void Update() override;
        void Start() override;
        void OnTriggerEnter(Engine::GameObject* go) override {};
        void OnTriggerStay(Engine::GameObject* go) override {};
        void OnTriggerExit(Engine::GameObject* go) override {};
        void OnCollisionEnter(Engine::GameObject* go) override {};
        void OnCollisionStay(Engine::GameObject* go) override {};
        void OnCollisionExit(Engine::GameObject* go) override {};
        void GUIUpdate() override ;
        void OnDestroy() override {};
        void Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material);
        Reflection::ClassMetaData& GetMetaData() override;
    };

    class BoxCollider : public Collider
    {
    public:
        BoxCollider(Maths::Vec3 _size = Maths::Vec3(1, 1, 1));

        Maths::Vec3 size;

        Reflection::ClassMetaData& GetMetaData() override;
    };

    class PHOSENGINE_API SphereCollider : public Collider
    {
    public:
        SphereCollider(float _radius = 1);

        float radius;

        Reflection::ClassMetaData& GetMetaData() override;
    };

    class PHOSENGINE_API CapsuleCollider : public Collider
    {
    public:
        CapsuleCollider(float _radius = 1, float _height = 1);

        float radius;
        float height;

        Reflection::ClassMetaData& GetMetaData() override;
    };
}