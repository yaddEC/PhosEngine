#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>

#include "dllInclude.hpp"

namespace Wrapper
{
    class PhysicsCollider;
    enum class MaterialType;
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
        void GUIUpdate() override;
        void OnDestroy() override;
        void Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material);
        void SetTriggerState(bool isTrigger);
        bool GetTriggerState() { return p_isTrigger; };
        void SetCenter(Maths::Vec3 center);
        Maths::Vec3 GetCenter() { return p_center; };
        Reflection::ClassMetaData& GetMetaData() override;
    protected:
        bool p_isTrigger = false;
        Maths::Vec3 p_center;
    };

    class PHOSENGINE_API BoxCollider : public Collider
    {
    public:
        BoxCollider(Maths::Vec3 _size = Maths::Vec3(1, 1, 1));
        Reflection::ClassMetaData& GetMetaData() override;
        void SetSize(Maths::Vec3 size);
        Maths::Vec3 GetSize() { return m_size; };
    private:
        Maths::Vec3 m_size;
    };

    class PHOSENGINE_API SphereCollider : public Collider
    {
    public:
        SphereCollider(float _radius = 1);
        Reflection::ClassMetaData& GetMetaData() override;
        void SetRadius(float radius);
        float GetRadius() { return m_radius; };
    private:
        float m_radius;
    };

    class PHOSENGINE_API CapsuleCollider : public Collider
    {
    public:
        CapsuleCollider(float _radius = 1, float _height = 1);
        Reflection::ClassMetaData& GetMetaData() override;
        void SetRadius(float radius);
        float GetRadius() { return m_radius; };
        void SetHeight(float height);
        float GetHeight() { return m_height; };
    private:
        float m_radius;
        float m_height;
    };
}