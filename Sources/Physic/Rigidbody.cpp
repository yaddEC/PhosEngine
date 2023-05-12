// Include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Physic/Collider.hpp"
#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Wrapper/PhysicsWrapper.hpp"
#include <Physic/Rigidbody.hpp>

namespace Physic {

    Rigidbody::Rigidbody()
        : MonoBehaviour(true) {
        physicsRigidbody = new Wrapper::PhysicsRigidbody();
        physicsRigidbody->rigidbody = this;
    }

    void Rigidbody::Init() {}

    void Rigidbody::Update() {
        physicsRigidbody->Update();

       /* // Use of the Raycast
        Wrapper::RayCastHit test;
        Maths::Vec3 dir = gameobject->transform->GetForwardVector();

        if (Wrapper::RayCast(gameobject->transform->position, dir, 6, test)) {
            printf("Forward %s %d\n", gameobject->name.c_str(), rand());
        }

        dir = gameobject->transform->GetRightVector();

        if (Wrapper::RayCast(gameobject->transform->position, dir, 6, test)) {
            printf("Right %s %d\n", gameobject->name.c_str(), rand());
        }

        dir = gameobject->transform->GetUpVector();

        if (Wrapper::RayCast(gameobject->transform->position, dir, 6, test)) {
            printf("UP %s %d\n", gameobject->name.c_str(), rand());
        }*/
    }

    void Rigidbody::GUIUpdate()
    {
        physicsRigidbody->OnGuiChanged();
    }

    void Rigidbody::SetGravity(Maths::Vec3 gravity)
    {
        m_gravity = gravity;
        physicsRigidbody->OnGuiChanged();
    }

    void Rigidbody::SetVelocity(Maths::Vec3 velocity)
    {
        m_velocity = velocity;
        physicsRigidbody->OnGuiChanged();
    }

    void Rigidbody::SetMass(float mass)
    {
        m_mass = mass;
        physicsRigidbody->OnGuiChanged();
    }

    Reflection::ClassMetaData& Rigidbody::GetMetaData() {
        using namespace Reflection;

        static bool computed = false;
        static ClassMetaData result;
        if (!computed) {
            result.name = "RigidBody";
            result.memberList = {
                ClassMemberInfo("Gravity", offsetof(Rigidbody, m_gravity), MemberType::T_VEC3),
                ClassMemberInfo("Velocity", offsetof(Rigidbody, m_velocity), MemberType::T_VEC3),
                ClassMemberInfo("mass", offsetof(Rigidbody, m_mass), MemberType::T_FLOAT),
                ClassMemberInfo("reset", offsetof(Rigidbody, reset), MemberType::T_BOOL),
            };
            computed = true;
        }
        return result;
    }

} 
