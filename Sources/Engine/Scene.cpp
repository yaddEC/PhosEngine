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
#define SCENE_EXPORTS
#include "Engine/Scene.hpp"

using namespace Engine;
using namespace LowRenderer;
using namespace Resource;
using namespace Physic;

Scene::Scene()
{
	renderer = new Renderer();
	m_physicsManager = new PhysicsManager();
	m_physicsManager->Init();
	Mesh* boo = Resource::ResourceManager::GetInstance().GetResource<Mesh>("Assets\\Model\\boo.obj");
	Mesh* ground = Resource::ResourceManager::GetInstance().GetResource<Mesh>("Assets\\Model\\cube.obj");
	Mesh* blaziken = Resource::ResourceManager::GetInstance().GetResource<Mesh>("Assets\\Model\\blaziken.obj");
	Mesh* sphere = Resource::ResourceManager::GetInstance().GetResource<Mesh>("DefaultAssets\\Model\\primitiveSphere.obj");

	Material* booMat = Resource::ResourceManager::GetInstance().GetResource<Material>("Assets\\Material\\boo_mat.001.phmat");
	Material* blazikenMat = Resource::ResourceManager::GetInstance().GetResource<Material>("Assets\\Material\\Blaziken.phmat");
	Material* basicMat = Resource::ResourceManager::GetInstance().GetResource<Material>("Assets\\Material\\Material.phmat");
	Material* metalGrid = Resource::ResourceManager::GetInstance().GetResource<Material>("Assets\\Material\\MetalGrid.phmat");

	GameObject* go = new GameObject();
	go->name = "Boo 1";
	MeshRenderer* rend = go->AddComponent<MeshRenderer>();
	rend->SetMesh(boo);
	rend->SetMaterial(booMat);
	go->transform->position.y = 10;


	//Rigidbody* rb = go->AddComponent<Rigidbody>();
	//SphereCollider* col = go->AddComponent<SphereCollider>();
	

	

	GameObject* go2 = new GameObject();
	go2->name = "Blaziken";
	MeshRenderer* rend2 = go2->AddComponent<MeshRenderer>();
	rend2->SetMesh(blaziken);
	rend2->SetMaterial(blazikenMat);
	//go2->transform->SetParent(go->transform);
	go2->transform->position.x = 10;
	go2->transform->rotation.y = Maths::M_PI;
	go2->transform->scale = Maths::Vec3(0.5f, 0.5f, 0.5f);

	

	GameObject* go3 = new GameObject();
	go3->name = "Ground";
	MeshRenderer* rend3 = go3->AddComponent<MeshRenderer>();
	rend3->SetMesh(ground);
	rend3->SetMaterial(basicMat);
	go3->transform->position.y = -3;
	go3->transform->scale = Maths::Vec3(50, 1, 100);
	//BoxCollider* col2 = go3->AddComponent<BoxCollider>();

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
	light2->transform->position.y = 6;

	Instantiate(go);
	Instantiate(go2);
	Instantiate(go3);
	Instantiate(go4);
	//Instantiate(light);
	//Instantiate(light1);
	Instantiate(light2);

	//col->Setup(Maths::Vec3(0, 0, 0), Maths::Vec3(2, 2, 2), false, Wrapper::BOUNCY_BALL);
	//col2->Setup(Maths::Vec3(0, 0, 0), Maths::Vec3(1, 1, 1), false, Wrapper::BOUNCY_BALL);
}

void Scene::GameObjectFromBuffer()
{
	/*for (unsigned int i = 0; i < m_gameObjects.size() + m_gameObjectBuffer.size(); i++)
	{
		if (i > m_gameObjects.size() - 1 || m_gameObjects.size() == 0)
		{
			m_gameObjects.push_back(m_gameObjectBuffer[0]);
			m_gameObjects[i]->SetID(i + 1);
			m_gameObjectBuffer.erase(m_gameObjectBuffer.begin());
		}
		else if (i + 1 != m_gameObjects[i]->GetID() && m_gameObjectBuffer.size() > 0)
		{
			m_gameObjects.insert(m_gameObjects.begin() + i, m_gameObjectBuffer[0]);
			m_gameObjects[i]->SetID(i + 1);
			m_gameObjectBuffer.erase(m_gameObjectBuffer.begin());
		}
	}
	m_gameObjectBuffer.clear();*/

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
	m_physicsManager->Update(Input::deltaTime);
	
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


