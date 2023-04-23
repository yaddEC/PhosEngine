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
#include "Resource/ResourceManager.hpp"
#include "Wrapper/RHI.hpp"

#include <iostream>

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

void MeshRenderer::IdPickerRender(const Maths::Mat4& viewProj) const
{
	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	rm.pickingShader->SetUniformMatrix("mvp", transform->GetGlobalMatrix() * viewProj);

	int r = (gameobject->GetID() & 0x000000FF) >> 0;
	int g = (gameobject->GetID() & 0x0000FF00) >> 8;
	int b = (gameobject->GetID() & 0x00FF0000) >> 16;

	rm.pickingShader->SetUniformVec4("PickingColor", { r / 255.0f, g / 255.0f, b / 255.0f, 1.0f });
	

	for (SubMesh mesh : m_mesh->GetSubMeshes())
    {
		Wrapper::RHI::RenderSubMesh(mesh.GetVAO(), mesh.indices);
    }
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

Reflection::ClassMetaData& LowRenderer::MeshRenderer::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Mesh Renderer";
		result.memberList = 
		{
			ClassMemberInfo("Mesh", offsetof(MeshRenderer, MeshRenderer::m_mesh), MemberType::T_MESH),
			ClassMemberInfo("Material", offsetof(MeshRenderer, MeshRenderer::m_material), MemberType::T_MATERIAL) 
		};
		computed = true;
	}
	return result;
}

