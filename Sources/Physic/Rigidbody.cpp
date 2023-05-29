#include "..\..\..\PhosEditor\External\PhosEngine\Physic\Rigidbody.hpp"
// Include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Physic/Collider.hpp"
#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Wrapper/PhysicsWrapper.hpp"
#include "Wrapper/GUI.hpp"
#include <Physic/Rigidbody.hpp>

namespace Physic {

    Rigidbody::Rigidbody()
        : MonoBehaviour(false) {
        physicsRigidbody = new Wrapper::PhysicsRigidbody();
        physicsRigidbody->rigidbody = this;
    }

    void Rigidbody::Init() {}

    void Rigidbody::Start()
    {
        Collider* collider = gameobject->GetComponent<BoxCollider>();
        if (!collider)
        {
            collider = gameobject->GetComponent<SphereCollider>();
            if (!collider)
            {
                collider = gameobject->GetComponent<CapsuleCollider>();
            }
        }
        col = collider;

        if (col)
        {
            col->rb = this;
            if(col->physicsCollider)
                col->physicsCollider->UpdateType();
        }
    }

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

    void Rigidbody::OnDestroy()
    {
        //delete physicsRigidbody;
    }

    void Rigidbody::GUIUpdate()
    {
        physicsRigidbody->OnGuiChanged();
    }

    void Rigidbody::OnInspector()
    {
        MonoBehaviour::OnInspector();
        Maths::Vec3 velocity = (0, 0, 0);
        if (physicsRigidbody->GetRigidActor())
            velocity = GetVelocity();
        Wrapper::GUI::EditVec3("Velocity", velocity);

    }

    void Rigidbody::SetGravity(Maths::Vec3 gravity)
    {
        m_gravity = gravity;
        physicsRigidbody->OnGuiChanged();
    }

    Maths::Vec3 Rigidbody::GetVelocity()
    {
        return physicsRigidbody->GetVelocity();
    }

    void Rigidbody::SetVelocity(Maths::Vec3 velocity)
    {
        physicsRigidbody->SetVelocity(velocity);
        physicsRigidbody->OnGuiChanged();
    }

    void Rigidbody::AddForce(Maths::Vec3 force)
    {
        physicsRigidbody->AddForce(force);
    }

    void Rigidbody::SetMass(float mass)
    {
        m_mass = mass;
        physicsRigidbody->OnGuiChanged();
    }

    bool Rigidbody::IsGravityDifferent()
    {
        return m_differentGravity;
    }

    void Rigidbody::setDifferentGravity(bool ownGravity)
    {
        m_differentGravity = ownGravity;
        physicsRigidbody->OnGuiChanged();
    }

    bool Rigidbody::IsKinematic()
    {
        return m_isKinematic;
    }

    void Rigidbody::setKinematic(bool kinematic)
    {
        m_isKinematic = kinematic;
    }

    Reflection::ClassMetaData& Rigidbody::GetMetaData() {
        using namespace Reflection;

        static bool computed = false;
        static ClassMetaData result;
        if (!computed) {
            result.name = "RigidBody";
            result.memberList = {
                ClassMemberInfo("mass", offsetof(Rigidbody, m_mass), MemberType::T_FLOAT),
                ClassMemberInfo("Different_Gravity", offsetof(Rigidbody, m_differentGravity), MemberType::T_BOOL),
                ClassMemberInfo("isKinematic", offsetof(Rigidbody, m_isKinematic), MemberType::T_BOOL),
                ClassMemberInfo("Gravity", offsetof(Rigidbody, m_gravity), MemberType::T_VEC3),
            };
            computed = true;
        }
        return result;
    }

} 
