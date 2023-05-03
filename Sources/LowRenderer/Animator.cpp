// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>

#include "Resource/Animation.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Resource/ResourceIncludes.hpp"
#include "Resource/AnimBone.hpp"
#include "Resource/ResourceManager.hpp"
#include "LowRenderer/Animator.hpp"

LowRenderer::Animator::Animator()
{
}

void LowRenderer::Animator::Start()
{
	m_meshRenderer = gameobject->GetComponent<MeshRenderer>();
	m_currentAnimation = Resource::ResourceManager::GetInstance().GetResource<Resource::Animation>("Assets\\Model\\Walking.anim");
	/*if (m_meshRenderer)
	{
		if (Resource::Armature* arm = m_meshRenderer->GetMesh()->GetArmature())
		{
			if (arm->boneMap.size() != m_currentAnimation->GetAnimBones().size())
			{
				m_meshRenderer = nullptr;
				std::cout << "bone count did not match" << std::endl;
			}
		}
	}*/

}

void LowRenderer::Animator::Update()
{
	if (!m_meshRenderer)
		return;

	for (auto bone : m_currentAnimation->GetAnimBones())
	{
		if(!bone->GetParent())
			ComputeAnimBoneMatrices(Maths::Mat4::CreateDiagonalMatrix(1), bone);
	}
}

void LowRenderer::Animator::GUIUpdate()
{

}

void LowRenderer::Animator::OnDestroy()
{

}

Reflection::ClassMetaData& LowRenderer::Animator::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Animator";
		result.memberList =
		{
			ClassMemberInfo("Speed", offsetof(Animator, Animator::m_speed),
			MemberType::T_FLOAT, 0.01f, 0, 1)
		};
		computed = true;
	}
	return result;
}

void LowRenderer::Animator::ComputeAnimBoneMatrices(Maths::Mat4 parentMatrix, Resource::AnimBone* bone)
{
	Maths::Mat4 matrix = bone->GetGlobalMatrix(m_timeline, parentMatrix);
	m_meshRenderer->SetAnimMatrix(bone->GetName(), matrix);
	for (Resource::AnimBone* child : bone->GetChildren())
	{
		ComputeAnimBoneMatrices(matrix, child);
	}
}
