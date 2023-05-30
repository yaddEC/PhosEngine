#include <pch.h>
#include "Physic/Joint.hpp"
#include "Wrapper/PhysicsWrapper.hpp"

#include "Physic/Rigidbody.hpp"
Physic::Joint::Joint():MonoBehaviour(false)
{
    physicsJoint = nullptr;
    p_breakForce = INF;
    p_breakTorque = INF;
}

Physic::Joint::~Joint()
{
	delete physicsJoint;
}

void Physic::Joint::Update()
{
    if(GetGameObjectId() && GetGameObjectId()!=-1 && !GetOtherRigidbody() )
        physicsJoint->OnGuiChanged();
}

void Physic::Joint::Start()
{
    p_selfRigidbody = this->gameobject->GetComponent<Physic::Rigidbody>();
	physicsJoint = new Wrapper::PhysicsJoint();
    physicsJoint->joint = this;
    physicsJoint->Setup();
    
}

void Physic::Joint::GUIUpdate()
{
    if(physicsJoint)
        physicsJoint->OnGuiChanged();

}

Reflection::ClassMetaData& Physic::Joint::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "Joint";
        result.memberList = {

        };
        computed = true;
    }
    return result;
}

Physic::FixedJoint::FixedJoint()
{
}

Reflection::ClassMetaData& Physic::FixedJoint::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "Fixed Joint";
        result.memberList = {
            ClassMemberInfo("Collider", offsetof(FixedJoint, p_gameObjectId), MemberType::T_GAME_OBJECT),

            ClassMemberInfo("BreakForce", offsetof(FixedJoint, p_breakForce), MemberType::T_INF_FLOAT),
            ClassMemberInfo("BreakTorque", offsetof(FixedJoint, p_breakTorque), MemberType::T_INF_FLOAT),
        };        computed = true;
    }
    return result;
}

Physic::HingeJoint::HingeJoint()
{
}

Reflection::ClassMetaData& Physic::HingeJoint::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "Hinge Joint";
        result.memberList = {
            ClassMemberInfo("Collider", offsetof(HingeJoint, p_gameObjectId), MemberType::T_GAME_OBJECT),

            ClassMemberInfo("BreakForce", offsetof(HingeJoint, p_breakForce), MemberType::T_INF_FLOAT),
            ClassMemberInfo("BreakTorque", offsetof(HingeJoint, p_breakTorque), MemberType::T_INF_FLOAT),
        };
        computed = true;
    }
    return result;
}

Physic::SpringJoint::SpringJoint()
{
}

Reflection::ClassMetaData& Physic::SpringJoint::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "Spring Joint";
        result.memberList = {
            ClassMemberInfo("Collider", offsetof(SpringJoint, p_gameObjectId), MemberType::T_GAME_OBJECT),

            ClassMemberInfo("BreakForce", offsetof(SpringJoint, p_breakForce), MemberType::T_INF_FLOAT),
            ClassMemberInfo("BreakTorque", offsetof(SpringJoint, p_breakTorque), MemberType::T_INF_FLOAT),
        };
        computed = true;
    }
    return result;
}

Physic::ConfigurableJoint::ConfigurableJoint()
{
}

Reflection::ClassMetaData& Physic::ConfigurableJoint::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "Configurable Joint";
        result.memberList = {
            ClassMemberInfo("Collider", offsetof(ConfigurableJoint, p_gameObjectId), MemberType::T_GAME_OBJECT),

            ClassMemberInfo("BreakForce", offsetof(ConfigurableJoint, p_breakForce), MemberType::T_INF_FLOAT),
            ClassMemberInfo("BreakTorque", offsetof(ConfigurableJoint, p_breakTorque), MemberType::T_INF_FLOAT),
        };
        computed = true;
    }
    return result;
}
