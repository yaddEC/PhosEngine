// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <iostream>
#include "Engine/Input.hpp"
#include "Script/GrabScript.hpp"
#include "Script/PlayerMouvement.hpp"
#include "Wrapper/GUI.hpp"
#include "Wrapper/PhysicsWrapper.hpp"
#include "Engine/Scene.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Physic/Rigidbody.hpp"
#include "Physic/Collider.hpp"

Script::GrabScript::GrabScript()
{
    m_player = nullptr;
    m_actualObject = nullptr;
    m_isPressed = false;
    m_input = nullptr;
    m_grabbedRB = nullptr;
    m_currPos = Maths::Vec3();

}

Script::GrabScript::~GrabScript()
{
}

void Script::GrabScript::Start()
{
    m_input = &Engine::Input::GetInstance();
    m_player = gameobject->transform->GetParent()->GetParent()->GetParent()->GetGameObject();
    m_playerMouvement = m_player->GetComponent<Script::PlayerMouvement>();
    m_selfCollider = gameobject->GetComponent<Physic::SphereCollider>();

}

void Script::GrabScript::OnTriggerEnter(Engine::GameObject* go)
{
    printf("TRIGGRE");
    if (go->GetScene()->GetTagName(go->GetTag()) == "Movable")
    {
        m_actualObject = go;
    }
}

void Script::GrabScript::OnTriggerExit(Engine::GameObject* go)
{
    if (m_actualObject )
        m_actualObject = nullptr;
}

void Script::GrabScript::Update()
{
    m_selfCollider->SetGlobalPos(gameobject->transform->GetGlobalPosition());
    if(m_actualObject)
    { 
        if ((m_input->IsButtonDown(Engine::BUTTON_RIGHT_BUMPER, (Engine::Controller)m_playerMouvement->GetController()) || ((Engine::Controller)m_playerMouvement->GetController() == Engine::Controller::C_KEYBOARD && m_input->IsMouseButtonDown(GLFW_MOUSE_BUTTON_1))))
            {
                m_isPressed = true;
                m_grabbedRB = m_actualObject->GetComponent<Physic::Rigidbody>();
                m_grabbedRB->setKinematic(true);
            }
    }
        if (m_grabbedRB)
        {
           
            m_prevPos = m_currPos;
            m_currPos = gameobject->transform->GetGlobalPosition();
            
            m_grabbedRB->gameobject->transform->position = m_currPos;

            m_velocity = (m_currPos - m_prevPos) / m_input->GetDeltaTime();

            if ((m_input->IsButtonReleased(Engine::BUTTON_RIGHT_BUMPER, (Engine::Controller)m_playerMouvement->GetController()) || ((Engine::Controller)m_playerMouvement->GetController() == Engine::Controller::C_KEYBOARD && m_input->IsMouseButtonReleased(GLFW_MOUSE_BUTTON_1))))
            {
                m_grabbedRB->setKinematic(false);
                m_grabbedRB->SetVelocity(m_velocity);
                m_grabbedRB->SetPos(gameobject->transform->GetGlobalPosition() + m_selfCollider->GetCenter());
                m_grabbedRB = nullptr;
            }
        }

    

}

Reflection::ClassMetaData& Script::GrabScript::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "Grab Script";
        result.memberList = {
            
        };
        computed = true;
    }
    return result;
}
