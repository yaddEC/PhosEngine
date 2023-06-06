// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Engine/GameObject.hpp"
#include "Physic/Rigidbody.hpp"
#include "Script/OutOfBound.hpp"
#include "Script/DeathDetection.hpp"

Script::DeathDetection::DeathDetection()
{
}

Script::DeathDetection::~DeathDetection()
{
}

void Script::DeathDetection::OnTriggerEnter(Engine::GameObject* go)
{
	OutOfBound* gameObjet = go->GetComponent<OutOfBound>();
    
	if (gameObjet)
	{   
        Physic::Rigidbody* rb = go->GetComponent<Physic::Rigidbody>();
        rb->SetPos(gameObjet->GetInitPos());
		//player->transform->position = player->GetInitPos();  
	}
}

void Script::DeathDetection::OnInspector()
{
    MonoBehaviour::OnInspector();
}

Reflection::ClassMetaData& Script::DeathDetection::GetMetaData()
{
    using namespace Reflection;

    static bool computed = false;
    static ClassMetaData result;
    if (!computed)
    {
        result.name = "Detection";
        result.memberList ={
        };
        computed = true;
    }
    return result;
}
