#include <utility>
#include <limits>
#include "pch.h"
#include <Engine/GameObject.hpp>
#include <Engine/Transform.hpp>
#include "Engine/Scene.hpp"
#include "LowRenderer/Renderer.hpp"
#include <Wrapper/PhysicsWrapper.hpp>
#include <Physic/Rigidbody.hpp>
#include <Physic/Collider.hpp>
#include "Resource/ResourceManager.hpp"
#include "Resource/ResourceIncludes.hpp"

namespace Physic {

    Collider::Collider()
        : MonoBehaviour(false)
    {
    }

    void Collider::Start()
    {
        physicsCollider = new Wrapper::PhysicsCollider();
        physicsCollider->collider = this;

        Rigidbody* rigidbody = gameobject->GetComponent<Rigidbody>();
            rb = rigidbody;
        if (rigidbody)
        {
            rb->col = this;
        }

        physicsCollider->Init();
    }

    void Collider::Update()
    {
        physicsCollider->Update();
    }

    void Collider::GUIUpdate()
    {
        physicsCollider->OnGuiChanged();
    }

    void Collider::OnDestroy()
    {
        delete physicsCollider;
    }

    void Collider::Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material)
    {
        physicsCollider->Setup(center, size, trigger, material);
    }

    void Collider::SetTriggerState(bool isTrigger)
    {
        p_isTrigger = isTrigger;
        physicsCollider->OnGuiChanged();
    }

    void Collider::SetMaterial(Wrapper::MaterialType material)
    {
        p_material = material;
        physicsCollider->OnGuiChanged();
    }

    void Collider::SetCenter(Maths::Vec3 center)
    {
        p_center = center;
        physicsCollider->OnGuiChanged();
    }

    Reflection::ClassMetaData& Collider::GetMetaData()
    {
        using namespace Reflection;

        static bool computed = false;
        static ClassMetaData result;
        if (!computed)
        {
            result.name = "Collider";
            result.memberList = {};
            computed = true;
        }
        return result;
    }

    BoxCollider::BoxCollider(Maths::Vec3 _size)
        : Collider()
    {
        m_size = _size;
    }

    Reflection::ClassMetaData& BoxCollider::GetMetaData()
    {
        using namespace Reflection;

        static bool computed = false;
        static ClassMetaData result;
        if (!computed)
        {
            result.name = "Box Collider";
            result.memberList = {
                ClassMemberInfo("isTrigger", offsetof(BoxCollider, p_isTrigger), MemberType::T_BOOL),
                ClassMemberInfo("Center", offsetof(BoxCollider, p_center), MemberType::T_VEC3),
                ClassMemberInfo("Size", offsetof(BoxCollider, m_size), MemberType::T_VEC3),
                ClassMemberInfo("MaterialType", offsetof(BoxCollider,p_material), MemberType::T_PHYSIC_MATERIAL),
            };
            computed = true;
        }
        return result;
    }

    void BoxCollider::SetSize(Maths::Vec3 size)
    {
        m_size = size;
        physicsCollider->OnGuiChanged();
    }

    SphereCollider::SphereCollider(float _radius)
        : Collider()
    {
        m_radius = _radius;
    }

    Reflection::ClassMetaData& SphereCollider::GetMetaData()
    {
        using namespace Reflection;

        static bool computed = false;
        static ClassMetaData result;
        if (!computed)
        {
            result.name = "Sphere Collider";
            result.memberList = {
                ClassMemberInfo("isTrigger", offsetof(SphereCollider, p_isTrigger), MemberType::T_BOOL),
                ClassMemberInfo("Center", offsetof(SphereCollider, p_center), MemberType::T_VEC3),
                ClassMemberInfo("Radius", offsetof(SphereCollider, m_radius), MemberType::T_FLOAT),
                ClassMemberInfo("MaterialType", offsetof(SphereCollider,p_material), MemberType::T_PHYSIC_MATERIAL),
            };
            computed = true;
        }
        return result;
    }

    void SphereCollider::SetRadius(float radius)
    {
        m_radius = radius;
        physicsCollider->OnGuiChanged();
    }

    CapsuleCollider::CapsuleCollider(float _radius, float _height)
        : Collider()
    {
        m_radius = _radius;
        m_height = _height;
    }
    Reflection::ClassMetaData& CapsuleCollider::GetMetaData()
    {
        using namespace Reflection;

        static bool computed = false;
        static ClassMetaData result;
        if (!computed)
        {
            result.name = "Capsule Collider";
            result.memberList = {
                ClassMemberInfo("isTrigger", offsetof(CapsuleCollider, p_isTrigger), MemberType::T_BOOL),
                ClassMemberInfo("Center", offsetof(CapsuleCollider, p_center), MemberType::T_VEC3),
                ClassMemberInfo("Height", offsetof(CapsuleCollider, m_height), MemberType::T_FLOAT),
                ClassMemberInfo("Radius", offsetof(CapsuleCollider, m_radius), MemberType::T_FLOAT),
                ClassMemberInfo("MaterialType", offsetof(CapsuleCollider,p_material), MemberType::T_PHYSIC_MATERIAL)
            };
            computed = true;
        }
        return result;
    }
    void CapsuleCollider::SetRadius(float radius)
    {
        m_radius = radius;
        physicsCollider->OnGuiChanged();
    }
    void CapsuleCollider::SetHeight(float height)
    {
        m_height = height;
        physicsCollider->OnGuiChanged();
    }
}