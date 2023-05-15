// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/Texture.hpp"
#include "Resource/ResourceIncludes.hpp"
#include "Resource/Material.hpp"
#include "Resource/ResourceManager.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "LowRenderer/Renderer.hpp"
#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "LowRenderer/Light/SpotLight.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Transform.hpp"
#include "Engine/Input.hpp"
#include "Physic/PhysicsManager.hpp"
#include "Physic/Collider.hpp"
#include "Physic/Rigidbody.hpp"
#include "Wrapper/PhysicsWrapper.hpp"
#include "Resource/Parser.hpp"

using namespace Engine;
using namespace LowRenderer;
using namespace Resource;
using namespace Physic;

Scene::Scene() : m_renderer(nullptr)
{
	
}

Engine::Scene::~Scene()
{
	//Physic::PhysicsManager::GetInstance().Cleanup();
	delete m_renderer;
}

void Scene::GameObjectFromBuffer()
{

	for (Engine::GameObject* newGo : m_gameObjectBuffer)
	{
		unsigned int id = 1;
		for (Engine::GameObject* go : m_gameObjects)
		{
			if (go->GetID() > id) break;
			id++;
		}
		newGo->SetID(id);
		m_gameObjects.insert(m_gameObjects.begin() + (static_cast<size_t>(id) - 1), newGo);
	}
	m_gameObjectBuffer.clear();
}

void Scene::Update()
{
	if(m_IsGameMode)
		Physic::PhysicsManager::GetInstance().Update(Input::deltaTime);
	
	if(m_gameObjectBuffer.size() != 0)
	{
		GameObjectFromBuffer();
	}


	for (GameObject* go : m_gameObjects)
	{
		if(!go->transform->GetParent())
			go->transform->ComputeGlobalMatrix(Maths::Mat4::CreateDiagonalMatrix(1.f));
	}

	for (GameObject* go : m_gameObjects)
	{
		go->Update();
	}
}

GameObject* Engine::Scene::Instantiate(GameObject* newGameObject)
{
	newGameObject->SetScene(this);
	m_gameObjectBuffer.push_back(newGameObject);
	return newGameObject;
}

GameObject* Engine::Scene::InstantiatePrefab(const Resource::Prefab& prefab)
{
	std::vector<Engine::GameObject*> goList = prefab.GetCopy();
	for (auto go : goList)
	{
		Instantiate(go);
	}
	return goList[0];
}

void Engine::Scene::DeleteGameObjectFromList(GameObject* go)
{
	m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), go), m_gameObjects.end());
}


void Engine::Scene::StartGameMode()
{
	Save();
	Unload();
	m_IsGameMode = true;
	Load();
}

void Engine::Scene::StopGameMode()
{
	Unload();
	m_IsGameMode = false;
	Load();
}

void Engine::Scene::Load()
{
	m_renderer = new Renderer();
	Physic::PhysicsManager::GetInstance().Init();

	m_gameObjects.clear();
	m_gameObjectBuffer.clear();
	std::vector<std::string> fileData = Parser::ConvertFileToStringArray(GetFilePath());
	size_t lineIndex = 0;
	while (lineIndex < fileData.size() - 2)
	{
		ParseGameObject(fileData, lineIndex);
		lineIndex++;
	}

}

void Engine::Scene::Unload()
{
	for (GameObject* go : m_gameObjects)
	{
		if (!go->transform->GetParent())
			go->Destroy();
	}
	delete m_renderer;
	Physic::PhysicsManager::GetInstance().Cleanup();
}

void Engine::Scene::Save()
{
	
	std::fstream progFile;
	progFile.open((p_directory + "\\" + p_name).c_str(), std::fstream::out | std::fstream::trunc);

	if (progFile)
	{
		for (GameObject* go : m_gameObjects)
		{
			if (!go->transform->GetParent())
				SaveGameObject(go, progFile);
		}
	}
}

void Engine::Scene::SaveGameObject(Engine::GameObject* gameObject, std::fstream& file, int depth)
{
	std::string tab = std::string(depth, '\t');
	gameObject->transform->SetRotation(gameObject->transform->rotationEuler);
	file << tab << "name \"" << gameObject->name << "\"\n"
		<< tab << "id " << gameObject->GetID() << '\n'
		<< tab << "transform " << gameObject->transform->position.x << ' ' << gameObject->transform->position.y << ' ' << gameObject->transform->position.z
		<< ' ' << gameObject->transform->rotationEuler.x << ' ' << gameObject->transform->rotationEuler.y << ' ' << gameObject->transform->rotationEuler.z
		<< ' ' << gameObject->transform->scale.x << ' ' << gameObject->transform->scale.y << ' ' << gameObject->transform->scale.z << '\n';
	for (auto comp : gameObject->GetComponents())
	{
		file << comp->GetMetaData().Save(comp, depth + 1);
	}
	for (auto child : gameObject->transform->GetChildren())
	{
		file << tab << "child\n";
		SaveGameObject(child->GetGameObject(), file, depth + 1);
	}
	file << tab << "end\n";
}

GameObject* Engine::Scene::ParseGameObject(const std::vector<std::string>& fileData, size_t& lineIndex)
{
	GameObject* newGameObject = new GameObject();
	Instantiate(newGameObject);
	for (; lineIndex < fileData.size(); lineIndex++)
	{
		std::vector<std::string> tokens = Parser::Tokenize(fileData[lineIndex], ' ', '\t');

		if (tokens[0] == "name")
		{
			newGameObject->name = tokens[1];
		}
		else if (tokens[0] == "id")
		{
			newGameObject->SetID((unsigned int)std::stof(tokens[1]));
		}
		else if (tokens[0] == "transform")
		{
			newGameObject->transform->position = Maths::Vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
			newGameObject->transform->rotationEuler = Maths::Vec3(std::stof(tokens[4]), std::stof(tokens[5]), std::stof(tokens[6]));
			newGameObject->transform->SetRotation(newGameObject->transform->rotationEuler);
			newGameObject->transform->scale = Maths::Vec3(std::stof(tokens[7]), std::stof(tokens[8]), std::stof(tokens[9]));
		}
		else if (tokens[0] == "component")
		{
			Engine::MonoBehaviour* comp = Reflection::ClassMetaData::AddComponent(tokens[1], newGameObject);
			if (comp)
				comp->GetMetaData().Parse(fileData, ++lineIndex, comp);
		}
		else if (tokens[0] == "child")
		{
			newGameObject->transform->AddChild(ParseGameObject(fileData, ++lineIndex)->transform);
		}
		else if (tokens[0] == "end")
		{
			return newGameObject;
		}
	}
}


