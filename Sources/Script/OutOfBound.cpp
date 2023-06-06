// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Script/OutOfBound.hpp"

Script::OutOfBound::OutOfBound()
{
}

Script::OutOfBound::~OutOfBound()
{
}

void Script::OutOfBound::Start()
{
    m_initPos = transform->position;
}

void Script::OutOfBound::OnInspector()
{
    MonoBehaviour::OnInspector();
}

Reflection::ClassMetaData& Script::OutOfBound::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "OutOfBound";
        result.memberList = {
        };
        computed = true;
    }
    return result;
}
