// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Resource/Texture.hpp"
#include "Engine/Transform.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Resource/Mesh.hpp"
#include "LowRenderer/Renderer.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Transform.hpp"


#define SCENE_EXPORTS
#include "Engine/Scene.hpp"

using namespace Engine;
using namespace LowRenderer;
using namespace Resource;

Scene::Scene()
{
	renderer = new Renderer();

	Mesh* boo = new Mesh();
	boo->Load("Assets\\Model\\boo.obj");
	boo->Bind();

	GameObject* go = new GameObject();
	go->name = "Boo 1";
	MeshRenderer* rend = go->AddComponent<MeshRenderer>();
	rend->SetMesh(boo);

	GameObject* go2 = new GameObject();
	go2->name = "Boo 2";
	MeshRenderer* rend2 = go2->AddComponent<MeshRenderer>();
	rend2->SetMesh(boo);
	go2->transform->SetParent(go->transform);
	go2->transform->position.x = 5;
	go2->transform->scale = Maths::Vec3(0.5f, 0.5f, 0.5f);

	Instantiate(go);
	Instantiate(go2);
}

void Scene::Update()
{
	for (GameObject* go : m_gameObjects)
	{
		if(!go->transform->GetParent())
			go->transform->ComputeGlobalMatrix(Maths::Mat4::CreateDiagonalMatrix(1.f));
	}

	for (GameObject* go : m_gameObjects)
	{
		go->Update();
	}

	glClearColor(1.0f, 1.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GameObject* Engine::Scene::Instantiate(GameObject* newGameObject)
{
	newGameObject->SetScene(this);
	m_gameObjects.push_back(newGameObject);
	return newGameObject;
}


