// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Engine/Input.hpp"
#include "Script/PlayerMouvement.hpp"

Script::PlayerMouvement::PlayerMouvement()
{
    m_playerSpeed = 1.5f;
}

Script::PlayerMouvement::~PlayerMouvement()
{
}

void Script::PlayerMouvement::Start()
{
    
}

void Script::PlayerMouvement::Update()
{
	Engine::Input& input = Engine::Input::GetInstance();

	if (input.IsKeyPressed(GLFW_KEY_W) || input.IsKeyPressed(GLFW_KEY_S))
    {
        transform->position.z += input.deltaTime * input.GetVerticalAxis() * m_playerSpeed;
    }
    if (input.IsKeyPressed(GLFW_KEY_A) || input.IsKeyPressed(GLFW_KEY_D))
	{
		transform->position.x += input.deltaTime * input.GetHorizontalAxis() * m_playerSpeed;
	}
}

void Script::PlayerMouvement::GUIUpdate()
{
}

void Script::PlayerMouvement::OnInspector()
{
    MonoBehaviour::OnInspector();
}

void Script::PlayerMouvement::OnDestroy()
{
}

Reflection::ClassMetaData& Script::PlayerMouvement::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "PlayerMovement";
        result.memberList = {
            ClassMemberInfo("Speed", offsetof(PlayerMouvement, m_playerSpeed), MemberType::T_FLOAT),

        };
        computed = true;
    }
    return result;
}
