// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Script/WinZone.hpp"
#include "Script/PlayerMouvement.hpp"
#include "Script/WinManager.hpp"

Script::WinZone::WinZone()
{
}

Script::WinZone::~WinZone()
{
}

void Script::WinZone::OnInspector()
{
    MonoBehaviour::OnInspector();
}

void Script::WinZone::OnTriggerEnter(Engine::GameObject* go)
{
    PlayerMouvement* player = go->GetComponent<PlayerMouvement>();
    if (player)
    {
        transform->GetParent()->GetGameObject()->GetComponent<WinManager>()->AddCount(m_leftSide);
    }
}

void Script::WinZone::OnTriggerExit(Engine::GameObject* go)
{
    PlayerMouvement* player = go->GetComponent<PlayerMouvement>();
    if (player)
    {
        transform->GetParent()->GetGameObject()->GetComponent<WinManager>()->ReduceCount(m_leftSide);
    }
}

Reflection::ClassMetaData& Script::WinZone::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "WinZone";
        result.memberList = {
            ClassMemberInfo("LeftSide", offsetof(WinZone, m_leftSide), MemberType::T_BOOL)
        };
        computed = true;
    }
    return result;
}
