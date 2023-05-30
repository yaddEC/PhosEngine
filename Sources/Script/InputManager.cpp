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
            playerMovement.push_back(go->GetComponent<PlayerMouvement>());
    }
}

void Script::InputManager::Update()
{
    for (int i = 0; i < playerMovement.size(); i++)
    {
        playerMovement[i]->SetIdUser(gamepads[i].IDconnexion);
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
