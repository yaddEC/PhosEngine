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
    gamepads = Engine::Input::GetInstance().GetGamepad();
    std::vector<Engine::GameObject*> gameObjects = gameobject->GetScene()->FindAllGameObjectWithTag("Player");
    for (Engine::GameObject* go : gameObjects)
    {
        if (go->GetComponent<PlayerMouvement>())
        {
            playerMovement.push_back(go->GetComponent<PlayerMouvement>());
            go->GetComponent<PlayerMouvement>()->SetIdUser(-2);
        }
    }
}

void Script::InputManager::Update()
{
    /*for (int i = 0; i < playerMovement.size(); i++)
    {
        if ((i == 0 && playerMovement[1]->GetIdUser() == gamepads[i].IDconnexion )||
            (i == 1 && playerMovement[0]->GetIdUser() == gamepads[i].IDconnexion))
        {
            playerMovement[i]->SetIdUser(-2);
        }
        else
        {
            playerMovement[i]->SetIdUser(gamepads[i].IDconnexion);
        }
    }*/
    std::vector<int> availableGamepads;
    std::vector<PlayerMouvement*> availablePlayers;

    bool isKeyboardAvailable = true;

    for (auto player : playerMovement)
    {
        if (player->GetIdUser() == -1)
            isKeyboardAvailable = false;
    }

    for (size_t i = 0; i < Engine::MAX_CONTROLLER; i++)
    {
        if (gamepads[i].IDconnexion != -1)
        {
            bool isUsed = false;
            for (auto player : playerMovement)
            {
                if (player->GetIdUser() == i)
                {
                    isUsed = true;
                    break;
                }
            }
            if(!isUsed)
                availableGamepads.push_back(gamepads[i].IDconnexion);
        }
    }

    for (auto player : playerMovement)
    {
        
        if (player->GetIdUser() >= 0)
        {
            if (gamepads[player->GetIdUser()].IDconnexion == -1)
            {
                player->SetIdUser(-2);
            }
        }
        if (player->GetIdUser() < 0)
        {
            if (isKeyboardAvailable)
            {
                player->SetIdUser(-1);
                isKeyboardAvailable = false;
                availablePlayers.push_back(player);
            }
            else
            {
                availablePlayers.insert(availablePlayers.begin(), player);
            }
        }
        
    }


    for (int gamepad : availableGamepads)
    {
        for (auto player : availablePlayers)
        {
            player->SetIdUser(gamepad);
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
