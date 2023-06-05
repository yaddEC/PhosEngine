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

}

void Physic::Joint::Start()
{
    p_selfRigidbody = this->gameobject->GetComponent<Physic::Rigidbody>();
	physicsJoint = new Wrapper::PhysicsJoint();
    physicsJoint->joint = this;
    physicsJoint->Setup();

    if (GetGameObjectId() && GetGameObjectId() != -1 && !GetOtherRigidbody())
        physicsJoint->OnGuiChanged();
    
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

Physic::ConfigurableJoint::ConfigurableJoint(): Joint()
{
        p_gameObjectId = -1;
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
            ClassMemberInfo("Axis", offsetof(ConfigurableJoint, m_axis), MemberType::T_VEC3),
            ClassMemberInfo("Anchor", offsetof(ConfigurableJoint, m_anchor), MemberType::T_VEC3),
            ClassMemberInfo("Connect_Anchor", offsetof(ConfigurableJoint, m_connectedAnchor), MemberType::T_VEC3),
            ClassMemberInfo("Motion", offsetof(ConfigurableJoint, m_motion), MemberType::T_VEC3),
            ClassMemberInfo("Ang._Motion", offsetof(ConfigurableJoint, m_angularMotion), MemberType::T_VEC3),

            ClassMemberInfo("Lin.Lim.Spring_Damp", offsetof(ConfigurableJoint, m_linearLimitSpring.damper), MemberType::T_FLOAT),
            ClassMemberInfo("Lin.Lim.Spring_Spring", offsetof(ConfigurableJoint, m_linearLimitSpring.spring), MemberType::T_FLOAT),

            ClassMemberInfo("Lin_Limit", offsetof(ConfigurableJoint, m_linearLimit.limit), MemberType::T_FLOAT),
            ClassMemberInfo("Lin_Limit_Bounciness", offsetof(ConfigurableJoint, m_linearLimit.bounciness), MemberType::T_FLOAT),
            ClassMemberInfo("Lin_Limit_Contact_Dist", offsetof(ConfigurableJoint, m_linearLimit.contactDistance), MemberType::T_FLOAT),

            ClassMemberInfo("XDrive_Max_Force ", offsetof(ConfigurableJoint, m_xDrive.maximumForce), MemberType::T_FLOAT),
            ClassMemberInfo("XDrive_Pos_Damper", offsetof(ConfigurableJoint, m_xDrive.positionDamper), MemberType::T_FLOAT),
            ClassMemberInfo("XDrive_Pos_Spring", offsetof(ConfigurableJoint, m_xDrive.positionSpring), MemberType::T_FLOAT),

            ClassMemberInfo("YDrive_Max_Force ", offsetof(ConfigurableJoint, m_yDrive.maximumForce), MemberType::T_FLOAT),
            ClassMemberInfo("YDrive_Pos_Damper", offsetof(ConfigurableJoint, m_yDrive.positionDamper), MemberType::T_FLOAT),
            ClassMemberInfo("YDrive Pos Spring", offsetof(ConfigurableJoint, m_yDrive.positionSpring), MemberType::T_FLOAT),

            ClassMemberInfo("ZDrive_Max_Force ", offsetof(ConfigurableJoint, m_zDrive.maximumForce), MemberType::T_FLOAT),
            ClassMemberInfo("ZDrive_Pos_Damper", offsetof(ConfigurableJoint, m_zDrive.positionDamper), MemberType::T_FLOAT),
            ClassMemberInfo("ZDrive Pos Spring", offsetof(ConfigurableJoint, m_zDrive.positionSpring), MemberType::T_FLOAT),

            ClassMemberInfo("Ang_XDrive_Max_Force", offsetof(ConfigurableJoint, m_angularXDrive.maximumForce), MemberType::T_FLOAT),
            ClassMemberInfo("Ang_XDrive_Pos_Damper", offsetof(ConfigurableJoint, m_angularXDrive.positionDamper), MemberType::T_FLOAT),
            ClassMemberInfo("Ang_XDrive_Pos_Spring", offsetof(ConfigurableJoint, m_angularXDrive.positionSpring), MemberType::T_FLOAT),

            ClassMemberInfo("Ang_YDrive_Max_Force ", offsetof(ConfigurableJoint, m_angularYDrive.maximumForce), MemberType::T_FLOAT),
            ClassMemberInfo("Ang_YDrive_Pos_Damper", offsetof(ConfigurableJoint, m_angularYDrive.positionDamper), MemberType::T_FLOAT),
            ClassMemberInfo("Ang_YDrive_Pos_Spring", offsetof(ConfigurableJoint, m_angularYDrive.positionSpring), MemberType::T_FLOAT),

            ClassMemberInfo("Ang_ZDrive_Max_Force ", offsetof(ConfigurableJoint, m_angularZDrive.maximumForce), MemberType::T_FLOAT),
            ClassMemberInfo("Ang_ZDrive_Pos_Damper", offsetof(ConfigurableJoint, m_angularZDrive.positionDamper), MemberType::T_FLOAT),
            ClassMemberInfo("Ang_ZDrive_Pos_Spring", offsetof(ConfigurableJoint, m_angularZDrive.positionSpring), MemberType::T_FLOAT),

            ClassMemberInfo("Ang_YZDrive_Max_Force ", offsetof(ConfigurableJoint, m_angularZDrive.maximumForce), MemberType::T_FLOAT),
            ClassMemberInfo("Ang_YZDrive_Pos_Damper", offsetof(ConfigurableJoint, m_angularZDrive.positionDamper), MemberType::T_FLOAT),
            ClassMemberInfo("Ang_YZDrive_Pos_Spring", offsetof(ConfigurableJoint, m_angularZDrive.positionSpring), MemberType::T_FLOAT),

            ClassMemberInfo("Target_Pos", offsetof(ConfigurableJoint, m_targetPosition), MemberType::T_FLOAT),
            ClassMemberInfo("Target_Velocity", offsetof(ConfigurableJoint, m_targetVelocity), MemberType::T_FLOAT),
            ClassMemberInfo("Target_Ang_Velocity", offsetof(ConfigurableJoint, m_targetAngularVelocity), MemberType::T_FLOAT),
            ClassMemberInfo("BreakForce", offsetof(ConfigurableJoint, p_breakForce), MemberType::T_INF_FLOAT),
            ClassMemberInfo("BreakTorque", offsetof(ConfigurableJoint, p_breakTorque), MemberType::T_INF_FLOAT),
        };
        computed = true;
    }
    return result;
}
