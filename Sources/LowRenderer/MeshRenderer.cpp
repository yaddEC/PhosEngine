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
#include "Resource/Armature.hpp"
#include "LowRenderer/Renderer.hpp"
#include "Wrapper/GUI.hpp"
#include "Resource/ResourceManager.hpp"
#include "Wrapper/RHI.hpp"

#include <iostream>

#include "LowRenderer/MeshRenderer.hpp"


using namespace LowRenderer;
using namespace Engine;
using namespace Resource;

MeshRenderer::MeshRenderer(Mesh* _mesh)
	: MonoBehaviour(true)
{
	m_mesh = _mesh;
}

MeshRenderer::~MeshRenderer()
{
	delete m_mesh;
}

void MeshRenderer::Render(const Maths::Mat4& viewProj, const Maths::Vec3& viewPos) const
{
	if (!m_mesh || !m_material) return;

	m_material->GetShader()->Use();
	m_material->GetShader()->SetUniformVec3("viewPos", viewPos);
	m_material->GetShader()->SetUniformMatrix("model", transform->GetGlobalMatrix());
	m_material->GetShader()->SetUniformMatrix("viewProj", viewProj);
	m_material->GetShader()->SetUniformMatrix("mvp", transform->GetGlobalMatrix() * viewProj);
	if (m_mesh->GetArmature())
	{
		m_material->GetShader()->SetUniformMatrixArray("skinMat", m_animatedBoneMatrices);
		m_material->GetShader()->SetUniformBool("isSkinned", true);
	}
	else
	{
		m_material->GetShader()->SetUniformBool("isSkinned", false);
	}

	m_mesh->Render(*m_material);

}

void LowRenderer::MeshRenderer::RenderOutline(const Maths::Mat4& viewProj) const
{
	if (!m_mesh) return;
	
	ShaderProgram* outlineShader = Resource::ResourceManager::GetInstance().outlineShader;

	outlineShader->Use();
	outlineShader->SetUniformMatrix("model", transform->GetGlobalMatrix());
	outlineShader->SetUniformMatrix("viewProj", viewProj);
	outlineShader->SetUniformMatrix("mvp", transform->GetGlobalMatrix() * viewProj);
	if (m_mesh->GetArmature())
	{
		outlineShader->SetUniformMatrixArray("skinMat", m_animatedBoneMatrices);
		outlineShader->SetUniformBool("isSkinned", true);
	}
	else
	{
		outlineShader->SetUniformBool("isSkinned", false);
	}

	glCullFace(GL_BACK);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLineWidth(4);

	m_mesh->Render(*m_material);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void LowRenderer::MeshRenderer::SetSkinningMatrices()
{
	for (size_t i = 0; i < m_boneObjectList.size(); i++)
	{
		m_animatedBoneMatrices[i] = m_boneObjectList[i]->GetGlobalMatrix();
	}
}

Engine::GameObject* LowRenderer::MeshRenderer::GenerateBonesObject(const Bone& bone)
{
	Engine::GameObject* go = new GameObject();
	go->name = bone.name;
	gameobject->GetScene()->Instantiate(go);
	m_boneObjectList.push_back(go->transform);

	for (auto child : bone.children)
	{
		go->transform->AddChild(GenerateBonesObject(*child)->transform);
	}

	return go;
}

void LowRenderer::MeshRenderer::AssignBoneObject(Engine::Transform* tr)
{
	m_boneObjectList.push_back(tr);
	for (auto child : tr->GetChildren())
	{
		AssignBoneObject(child);
	}
}


void MeshRenderer::IdPickerRender(const Maths::Mat4& viewProj) const
{
	if (!m_mesh) return;

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
	if (!m_mesh) return;
	if (m_mesh->GetArmature())
	{
		for (auto bone : m_mesh->GetArmature()->boneMap)
		{
			m_animatedBoneMatrices.push_back(Maths::Mat4::CreateDiagonalMatrix(1));
		}
		for (auto child : transform->GetChildren())
		{
			if (child->GetGameObject()->name == m_mesh->GetArmature()->boneMap[0].name)
			{
				AssignBoneObject(child);
				return;
			}
		}
		transform->AddChild(GenerateBonesObject(m_mesh->GetArmature()->boneMap[0])->transform);
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

