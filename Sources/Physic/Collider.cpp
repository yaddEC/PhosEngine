#include <utility>
#include <limits>
#include "pch.h"
#include <Engine/GameObject.hpp>
#include <Engine/Transform.hpp>
#include <Wrapper/PhysicsWrapper.hpp>
#include <Physic/Rigidbody.hpp>
#include <Physic/Collider.hpp>

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
        if (rigidbody)
            rb = rigidbody;
        physicsCollider->Init();
    }

    void Collider::Update()
    {
        physicsCollider->Update();
    }

    void Collider::Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material)
    {
        physicsCollider->Setup(center, size, trigger, material);
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
        size = _size;
        Maths::Vec3 seg = size / 2.0f;
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
                ClassMemberInfo("isTrigger", offsetof(BoxCollider, isTrigger), MemberType::T_BOOL),
                ClassMemberInfo("Center", offsetof(BoxCollider, center), MemberType::T_VEC3),
                ClassMemberInfo("Size", offsetof(BoxCollider, size), MemberType::T_VEC3),
            };
            computed = true;
        }
        return result;
    }

    SphereCollider::SphereCollider(float _radius)
        : Collider()
    {
        radius = _radius;
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
                ClassMemberInfo("isTrigger", offsetof(SphereCollider, isTrigger), MemberType::T_BOOL),
                ClassMemberInfo("Center", offsetof(SphereCollider, center), MemberType::T_VEC3),
                ClassMemberInfo("Radius", offsetof(SphereCollider, radius), MemberType::T_FLOAT),
            };
            computed = true;
        }
        return result;
    }

    CapsuleCollider::CapsuleCollider(float _radius, float _height)
        : Collider()
    {
        radius = _radius;
        height = _height;
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
                ClassMemberInfo("isTrigger", offsetof(CapsuleCollider, isTrigger), MemberType::T_BOOL),
                ClassMemberInfo("Center", offsetof(CapsuleCollider, center), MemberType::T_VEC3),
                ClassMemberInfo("Height", offsetof(CapsuleCollider, height), MemberType::T_FLOAT),
                ClassMemberInfo("Radius", offsetof(CapsuleCollider, radius), MemberType::T_FLOAT),
            };
            computed = true;
        }
        return result;
    }
}