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
    user = 0;
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

    up = false;
    right = false;
    down = false;
    left = false;
    if (m_idUser <= -1)
    {
        if (input.IsKeyPressed(GLFW_KEY_W) || input.IsKeyPressed(GLFW_KEY_S))
        {
            transform->position.z += input.GetDeltaTime() * input.GetVerticalAxis() * m_playerSpeed;
        }
        if (input.IsKeyPressed(GLFW_KEY_A) || input.IsKeyPressed(GLFW_KEY_D))
        {
            transform->position.x += input.GetDeltaTime() * input.GetHorizontalAxis() * m_playerSpeed;
        }
    }
    else
    {
        transform->position.z += input.GetDeltaTime() * -input.GetGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_Y, m_idUser) * m_playerSpeed;
        transform->position.x += input.GetDeltaTime() * input.GetGamepadAxis(GLFW_GAMEPAD_AXIS_LEFT_X, m_idUser) * m_playerSpeed;
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

void Script::PlayerMouvement::SetIdUser(int ID)
{
    m_idUser = ID;
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
            ClassMemberInfo("IdUser", offsetof(PlayerMouvement, m_idUser), MemberType::T_FLOAT),
            ClassMemberInfo("up", offsetof(PlayerMouvement, up), MemberType::T_BOOL),
            ClassMemberInfo("right", offsetof(PlayerMouvement, right), MemberType::T_BOOL),
            ClassMemberInfo("down", offsetof(PlayerMouvement, down), MemberType::T_BOOL),
            ClassMemberInfo("left", offsetof(PlayerMouvement, left), MemberType::T_BOOL),

        };
        computed = true;
    }
    return result;
}
