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

Scene::Scene()
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
		int id = 1;
		for (Engine::GameObject* go : m_gameObjects)
		{
			if (go->GetID() > id)
				break;

			id++;
		}
		newGo->SetID(id);
		m_gameObjects.insert(m_gameObjects.begin() + (id - 1), newGo);
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
	Load(p_directory + "\\" + p_name);
}

void Engine::Scene::StopGameMode()
{
	Unload();
	m_IsGameMode = false;
	Load(p_directory + "\\" + p_name);
}

void Engine::Scene::Load(const std::string& filepath)
{
	m_renderer = new Renderer();
	Physic::PhysicsManager::GetInstance().Init();

	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	Mesh* boo = rm.GetResource<Mesh>("Assets\\Model\\boo.obj");
	Mesh* ground = rm.GetResource<Mesh>("Assets\\Model\\cube.obj");
	Mesh* blaziken = rm.GetResource<Mesh>("Assets\\Model\\blaziken.obj");
	Mesh* sphere = rm.GetResource<Mesh>("DefaultAssets\\Model\\primitiveSphere.obj");

	Material* booMat = rm.GetResource<Material>("Assets\\Material\\boo_mat.001.phmat");
	Material* blazikenMat = rm.GetResource<Material>("Assets\\Material\\Blaziken.phmat");
	Material* basicMat = rm.GetResource<Material>("Assets\\Material\\Material.phmat");
	Material* metalGrid = rm.GetResource<Material>("Assets\\Material\\MetalGrid.phmat");
	

	
	/*
	GameObject* go = new GameObject();
	go->name = "Boo 1";
	MeshRenderer* rend = go->AddComponent<MeshRenderer>();
	rend->SetMesh(boo);
	rend->SetMaterial(booMat);
	go->transform->position.y = 10;


	Rigidbody* rb = go->AddComponent<Rigidbody>();
	SphereCollider* col = go->AddComponent<SphereCollider>();


	GameObject* go2 = new GameObject();
	go2->name = "Blaziken";
	MeshRenderer* rend2 = go2->AddComponent<MeshRenderer>();
	rend2->SetMesh(blaziken);
	rend2->SetMaterial(blazikenMat);
	//go2->transform->SetParent(go->transform);
	go2->transform->position.x = 10;
	go2->transform->rotationEuler.y = Maths::M_PI;
	go2->transform->scale = Maths::Vec3(0.5f, 0.5f, 0.5f);



	GameObject* go3 = new GameObject();
	go3->name = "Ground";
	MeshRenderer* rend3 = go3->AddComponent<MeshRenderer>();
	rend3->SetMesh(ground);
	rend3->SetMaterial(basicMat);
	go3->transform->position.y = -3;
	go3->transform->scale = Maths::Vec3(50, 1, 100);
	BoxCollider* col2 = go3->AddComponent<BoxCollider>();

	GameObject* go4 = new GameObject();
	go4->name = "testMat";
	MeshRenderer* rend4 = go4->AddComponent<MeshRenderer>();
	rend4->SetMesh(sphere);
	rend4->SetMaterial(metalGrid);


	//GameObject* light = new GameObject();
	//DirectionalLight* dirLight = light->AddComponent<LowRenderer::DirectionalLight>();
	//light->name = "DirLight";

	//GameObject* light1 = new GameObject();
	//PointLight* pointLight = light1->AddComponent<LowRenderer::PointLight>();
	//light1->name = "pointLight";	
	//light1->transform->position.y = 5;

	GameObject* light2 = new GameObject();
	SpotLight* spotLight = light2->AddComponent<LowRenderer::SpotLight>();
	light2->name = "SpotLight";
	light2->transform->position.y = 25;

	Instantiate(go);
	Instantiate(go2);
	Instantiate(go3);
	Instantiate(go4);
	//Instantiate(light);
	//Instantiate(light1);
	Instantiate(light2);

	//col->Setup(Maths::Vec3(0, 0, 0), Maths::Vec3(2, 2, 2), false, Wrapper::BOUNCY_BALL);
	//col2->Setup(Maths::Vec3(0, 0, 0), Maths::Vec3(1, 1, 1), false, Wrapper::BOUNCY_BALL);*/

	m_gameObjects.clear();
	m_gameObjectBuffer.clear();
	std::vector<std::string> fileData = Parser::ConvertFileToStringArray(filepath);
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
	//m_physicsManager->Cleanup();
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
			newGameObject->SetID(std::stof(tokens[1]));
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


