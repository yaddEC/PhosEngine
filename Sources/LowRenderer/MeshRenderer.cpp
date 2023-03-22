// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/Mesh.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "LowRenderer/Renderer.hpp"

#define MESHRENDERER_EXPORTS
#include "LowRenderer/MeshRenderer.hpp"


using namespace LowRenderer;
using namespace Engine;
using namespace Resource;

MeshRenderer::MeshRenderer(Mesh* _mesh)
	: MonoBehaviour(true)
{
	m_mesh = _mesh;
	transform = new Transform();
}

MeshRenderer::~MeshRenderer()
{
	delete transform;
	delete m_mesh;
}

void MeshRenderer::Render(const ShaderProgram* shader, const Maths::Mat4& viewProj) const
{
	shader->SetUniformMatrix("model", transform->GetGlobalMatrix());
	shader->SetUniformMatrix("mvp", transform->GetGlobalMatrix() * viewProj);

	m_mesh->Render(*shader);

}

void LowRenderer::MeshRenderer::Start()
{
	gameobject->GetScene()->GetRenderer()->AddMeshRenderer(this);
}

void LowRenderer::MeshRenderer::Update()
{

}

void LowRenderer::MeshRenderer::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeleteMeshRenderer(this);
}
