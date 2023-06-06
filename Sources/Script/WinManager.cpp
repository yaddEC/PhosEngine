// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <iostream>

#include "Script/WinManager.hpp"

Script::WinManager::WinManager()
{
}

Script::WinManager::~WinManager()
{
}

void Script::WinManager::Start()
{
    //std::vector<Engine::GameObject*> gameObjects = gameobject->GetScene()->FindAllGameObjectWithTag("Player");
}

void Script::WinManager::AddCount(bool isLeftSide)
{
	isLeftSide ? m_leftCount++ : m_rightCount++;
}

void Script::WinManager::ReduceCount(bool isLeftSide)
{
	isLeftSide ? m_leftCount-- : m_rightCount--;
}

void Script::WinManager::Update()
{
	if (m_leftCount != 0 && m_leftCount == m_rightCount)
	{
		std::cout << "WIN" << std::endl;
		//WIN ACTION
	}
}

void Script::WinManager::OnInspector()
{
	MonoBehaviour::OnInspector();
}

Reflection::ClassMetaData& Script::WinManager::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "WinManager";
        result.memberList = {
            ClassMemberInfo("LeftCount", offsetof(WinManager, m_leftCount), MemberType::T_INT),
            ClassMemberInfo("RightCount", offsetof(WinManager, m_rightCount), MemberType::T_INT)
        };
        computed = true;
    }
    return result;
}
