#include <pch.h>
#include "Physic/Joint.hpp"
#include "Wrapper/PhysicsWrapper.hpp"

Physic::Joint::Joint():MonoBehaviour(true)
{
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
	physicsJoint = new Wrapper::PhysicsJoint();
}

void Physic::Joint::GUIUpdate()
{
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
        };
        computed = true;
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
        result.name = "Joint";
        result.memberList = {

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
        result.name = "Joint";
        result.memberList = {

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
        result.name = "Joint";
        result.memberList = {

        };
        computed = true;
    }
    return result;
}
