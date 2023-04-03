// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/Mesh.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Resource/Material.hpp"
#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "LowRenderer/Renderer.hpp"
#include "Wrapper/GUI.hpp"

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

void MeshRenderer::Render(const Maths::Mat4& viewProj) const
{
	m_material->GetShader()->Use();
	m_material->GetShader()->SetUniformMatrix("model", transform->GetGlobalMatrix());
	m_material->GetShader()->SetUniformMatrix("mvp", transform->GetGlobalMatrix() * viewProj);

	m_mesh->Render(*m_material->GetShader(), *m_material);

}

void LowRenderer::MeshRenderer::Start()
{
	gameobject->GetScene()->GetRenderer()->AddMeshRenderer(this);
}

void LowRenderer::MeshRenderer::Update()
{

}

void LowRenderer::MeshRenderer::GUIUpdate()
{
	if (Wrapper::GUI::CollapsingHeader("Mesh Renderer"))
	{
		Wrapper::GUI::DisplayText("Mesh : "); Wrapper::GUI::SameLine();
		Wrapper::GUI::Button(m_mesh->GetName());
		if (Resource::Mesh** mesh = (Mesh**)Wrapper::GUI::DragDropTarget("Mesh"))
		{
			m_mesh = *mesh;
		}

		Wrapper::GUI::DisplayText("Material : "); Wrapper::GUI::SameLine();
		Wrapper::GUI::Button(m_material->GetName());
		if (Resource::Material** mat = (Material**)Wrapper::GUI::DragDropTarget("Material"))
		{
			m_material = *mat;
		}
	}
}

void LowRenderer::MeshRenderer::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeleteMeshRenderer(this);
}

