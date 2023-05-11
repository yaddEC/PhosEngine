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
	if (m_mesh->GetArmature())
	{
		m_material->GetShader()->SetUniformMatrixArray("skinMat", m_animatedBoneMatrices);
		m_material->GetShader()->SetUniformBool("isSkinned", true);
	}
	else
	{
		m_material->GetShader()->SetUniformBool("isSkinned", false);
	}

	m_mesh->Render(*m_material->GetShader(), *m_material);

}

void MeshRenderer::SetAnimMatrix(int index, Maths::Mat4 matrix) 
{
	m_animatedBoneMatrices[index] = m_mesh->GetArmature()->boneMap[index].inverseBind * matrix;
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

void LowRenderer::MeshRenderer::Update()
{
	if (m_mesh->GetArmature())
	{
		m_boneObjectList[0]->ComputeGlobalMatrix();

		for (size_t i = 0; i < m_boneObjectList.size(); i++)
		{
			m_animatedBoneMatrices[i] = m_boneObjectList[i]->GetGlobalMatrix();
		}
	}
}

void LowRenderer::MeshRenderer::GUIUpdate()  
{
	/*if (Wrapper::GUI::CollapsingHeader("Mesh Renderer"))
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
	}*/
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

