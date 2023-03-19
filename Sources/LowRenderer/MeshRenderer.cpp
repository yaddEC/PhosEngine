// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "LowRenderer/MeshRenderer.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Engine/Transform.hpp"

#define MESHRENDERER_EXPORTS
#include "LowRenderer/MeshRenderer.hpp"


using namespace LowRenderer;
using namespace Engine;
using namespace Resource;

MeshRenderer::MeshRenderer(Mesh* _mesh)
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