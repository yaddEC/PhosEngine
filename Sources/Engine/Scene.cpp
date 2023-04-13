// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/Texture.hpp"
#include "Engine/Transform.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/Material.hpp"
#include "Resource/ResourceManager.hpp"
#include "LowRenderer/Renderer.hpp"
#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "LowRenderer/Light/SpotLight.hpp"
#include "Resource/Mesh.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Transform.hpp"
#include "Physic/PhysicsManager.hpp"


#define SCENE_EXPORTS
#include "Engine/Scene.hpp"

using namespace Engine;
using namespace LowRenderer;
using namespace Resource;

Scene::Scene()
{
	renderer = new Renderer();

	Mesh* boo = Resource::ResourceManager::GetInstance().GetResource<Mesh>("Assets\\Model\\boo.obj");
	Mesh* ground = Resource::ResourceManager::GetInstance().GetResource<Mesh>("Assets\\Model\\cube.obj");
	Mesh* blaziken = Resource::ResourceManager::GetInstance().GetResource<Mesh>("Assets\\Model\\blaziken.obj");

	Material* booMat = Resource::ResourceManager::GetInstance().GetResource<Material>("Assets\\Material\\boo_mat.001.phmat");
	Material* blazikenMat = Resource::ResourceManager::GetInstance().GetResource<Material>("Assets\\Material\\Blaziken.phmat");
	Material* basicMat = Resource::ResourceManager::GetInstance().GetResource<Material>("Assets\\Material\\Material.phmat");

	GameObject* go = new GameObject();
	go->name = "Boo 1";
	MeshRenderer* rend = go->AddComponent<MeshRenderer>();
	rend->SetMesh(boo);
	rend->SetMaterial(booMat);
	

	GameObject* go2 = new GameObject();
	go2->name = "Blaziken";
	MeshRenderer* rend2 = go2->AddComponent<MeshRenderer>();
	rend2->SetMesh(blaziken);
	rend2->SetMaterial(blazikenMat);
	go2->transform->SetParent(go->transform);
	go2->transform->position.x = 10;
	go2->transform->rotation.y = Maths::M_PI;
	go2->transform->scale = Maths::Vec3(0.5f, 0.5f, 0.5f);

	GameObject* go3 = new GameObject();
	go3->name = "Ground";
	MeshRenderer* rend3 = go3->AddComponent<MeshRenderer>();
	rend3->SetMesh(ground);
	rend3->SetMaterial(basicMat);
	go3->transform->position.y = -3;
	go3->transform->scale = Maths::Vec3(100, 1, 100);

	//GameObject* light = new GameObject();
	//DirectionalLight* dirLight = light->AddComponent<LowRenderer::DirectionalLight>();
	//light->name = "DirLight";

	//GameObject* light1 = new GameObject();
	//PointLight* pointLight = light1->AddComponent<LowRenderer::PointLight>();
	//light1->name = "pointLight";	

	GameObject* light2 = new GameObject();
	SpotLight* spotLight = light2->AddComponent<LowRenderer::SpotLight>();
	light2->name = "SpotLight";
	light2->transform->position.y = 6;

	Instantiate(go);
	Instantiate(go2);
	Instantiate(go3);
	//Instantiate(light);
	//Instantiate(light1);
	Instantiate(light2);
}

void Scene::Update()
{
	for (GameObject* go : m_gameObjectBuffer)
	{
		m_gameObjects.push_back(go);
	}
	m_gameObjectBuffer.clear();

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

void Engine::Scene::DeleteGameObjectFromList(GameObject* go)
{
	m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), go), m_gameObjects.end());
}


