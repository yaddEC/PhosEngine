// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <iostream>
#include "Engine/Input.hpp"
#include "Script/PlayerMouvement.hpp"
#include "Wrapper/GUI.hpp"
#include "Engine/Scene.hpp"
#include "Physic/Rigidbody.hpp"

Script::PlayerMouvement::PlayerMouvement()
{

}

Script::PlayerMouvement::~PlayerMouvement()
{
}

void Script::PlayerMouvement::Start()
{
    m_controller = Engine::Controller::C_NONE;
    m_cameraCenter = gameobject->FindChildByName("Camera Center")->transform;
    rb = gameobject->GetComponent<Physic::Rigidbody>();
}

void Script::PlayerMouvement::Update()
{
	Engine::Input& input = Engine::Input::GetInstance();

    Maths::Vec3 forward = m_cameraCenter->GetForwardVector();
    forward.y = 0;

    Maths::Vec3 right = m_cameraCenter->GetRightVector();
    right.y = 0;

    Maths::Vec3 inputMove = Maths::Vec3{input.GetAxis("MoveX", m_controller), 0, input.GetAxis("MoveY", m_controller) };
    //transform->position += (forward * inputMove.z + right * inputMove.x) * input.GetDeltaTime() * m_playerSpeed;
    rb->AddForce((forward * inputMove.z + right * inputMove.x) * m_playerSpeed);
    Maths::Vec2 inputRot = Maths::Vec2(-input.GetAxis("LookX", m_controller), input.GetAxis("LookY", m_controller));
    inputRot.Normalize();
    float mult = Maths::DEG2RAD;

    if (m_controller == Engine::Controller::C_KEYBOARD)
    {
        mult *= m_lookSpeedMouse * input.GetDeltaTime();
    }
    else
    {
        mult *= m_lookSpeedGamepad * input.GetDeltaTime();
    }
    

    m_cameraCenter->SetRotation(Maths::Vec3(Maths::Clamp(m_cameraCenter->rotationEuler.x - inputRot.y * mult *
        (m_controller == Engine::Controller::C_KEYBOARD ? -1 : 1), -1.4f, 1.4f),
        m_cameraCenter->rotationEuler.y, 0));
    m_cameraCenter->RotateY(-inputRot.x * mult);
}


void Script::PlayerMouvement::OnInspector()
{
    MonoBehaviour::OnInspector();
    Wrapper::GUI::DisplayText("Controller : %s", Engine::ControllerName[(int)m_controller + 2]);
}


void Script::PlayerMouvement::SetController(Engine::Controller ID)
{
    m_controller = ID;
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
            ClassMemberInfo("LookSpeedGamepad", offsetof(PlayerMouvement, m_lookSpeedGamepad), MemberType::T_FLOAT),
            ClassMemberInfo("LookSpeedMouse", offsetof(PlayerMouvement, m_lookSpeedMouse), MemberType::T_FLOAT)
        };
        computed = true;
    }
    return result;
}
