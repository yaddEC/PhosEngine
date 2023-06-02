// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Engine/Input.hpp"
#include "Engine/Scene.hpp"
#include "Script/PlayerMouvement.hpp"
#include "Script/InputManager.hpp"

Script::InputManager::InputManager()
{
}

Script::InputManager::~InputManager()
{
}

void Script::InputManager::Start()
{
    m_gamepads = Engine::Input::GetInstance().GetGamepad();
    std::vector<Engine::GameObject*> gameObjects = gameobject->GetScene()->FindAllGameObjectWithTag("Player");
    for (Engine::GameObject* go : gameObjects)
    {
        if (go->GetComponent<PlayerMouvement>())
        {
            m_playerMovement.push_back(go->GetComponent<PlayerMouvement>());
            go->GetComponent<PlayerMouvement>()->SetController(Engine::Controller::C_NONE);
        }
    }
}

void Script::InputManager::Update()
{
    std::vector<Engine::Controller> availableGamepads;
    std::vector<PlayerMouvement*> availablePlayers;

    bool isKeyboardAvailable = true;

    for (auto player : m_playerMovement)
    {
        if (player->GetController() == -1)
            isKeyboardAvailable = false;
    }

    for (size_t i = 0; i < Engine::MAX_CONTROLLER; i++)
    {
        if (m_gamepads[i].IDconnexion != -1)
        {
            bool isUsed = false;
            for (auto player : m_playerMovement)
            {
                if (player->GetController() == i)
                {
                    isUsed = true;
                    break;
                }
            }
            if (!isUsed)
                availableGamepads.push_back((Engine::Controller)m_gamepads[i].IDconnexion);
        }
    }

    for (auto player : m_playerMovement)
    {

        if (player->GetController() >= 0)
        {
            if (m_gamepads[player->GetController()].IDconnexion == -1)
            {
                player->SetController(Engine::Controller::C_NONE);
            }
        }
        if (player->GetController() < 0)
        {
            if (isKeyboardAvailable)
            {
                player->SetController(Engine::Controller::C_KEYBOARD);
                isKeyboardAvailable = false;
                availablePlayers.push_back(player);
            }
            else
            {
                availablePlayers.insert(availablePlayers.begin(), player);
            }
        }

    }


    for (Engine::Controller gamepad : availableGamepads)
    {
        for (auto player : availablePlayers)
        {
            player->SetController(gamepad);
            break;
        }
    }
}

void Script::InputManager::GUIUpdate()
{
}

void Script::InputManager::OnInspector()
{
    MonoBehaviour::OnInspector();
}

void Script::InputManager::OnDestroy()
{
}

Reflection::ClassMetaData& Script::InputManager::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "Input Manager";
        result.memberList = {
        };
        computed = true;
    }
    return result;
}
