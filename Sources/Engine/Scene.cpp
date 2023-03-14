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


#define SCENE_EXPORTS
#include "Engine/Scene.hpp"

using namespace Engine;
using namespace LowRenderer;
using namespace Resource;

Scene::Scene()
{

	Mesh* boo = new Mesh();
	boo->Load("Resources\\Model\\boo.obj");
	boo->Bind();
	MeshRenderer* rend = new MeshRenderer(boo);
	AddModel(rend);
}

void Scene::Update()
{
	for (MeshRenderer* rend : modelList)
	{
		rend->transform->ComputeGlobalMatrix(Maths::Mat4::CreateDiagonalMatrix(1.f));
	}

	glClearColor(1.0f, 1.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


