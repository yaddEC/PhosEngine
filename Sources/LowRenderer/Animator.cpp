// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>

#include "Wrapper/GUI.hpp"
#include "Resource/Animation.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Resource/ResourceIncludes.hpp"
#include "Engine/Transform.hpp"
#include "Resource/AnimBone.hpp"
#include "Resource/ResourceManager.hpp"
#include "LowRenderer/Animator.hpp"

LowRenderer::Animator::Animator()
{
}

void LowRenderer::Animator::Start()
{
	m_currentAnimation = Resource::ResourceManager::GetInstance().GetResource<Resource::Animation>("Assets\\Model\\Walking.anim");
	SetAnimObjects();
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
	for (size_t i = 0; i < animObjectList.size(); i++)
	{
		Resource::AnimBone* animBone = m_currentAnimation->GetAnimBones()[i];
		//animObjectList[i]->position = animBone->GetInterpolationPosition(m_timeline * m_currentAnimation->GetTickRate());
		animObjectList[i]->rotation = animBone->GetInterpolationRotation(m_timeline * m_currentAnimation->GetTickRate());
		//animObjectList[i]->scale = animBone->GetInterpolationScale(m_timeline * m_currentAnimation->GetTickRate());
	}
}


void LowRenderer::Animator::OnInspector()
{
	MonoBehaviour::OnInspector();
	if(m_currentAnimation)
		Wrapper::GUI::SliderFloat("Timeline", m_timeline, true, 0, m_currentAnimation->GetDuration() / m_currentAnimation->GetTickRate());
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

void LowRenderer::Animator::SetAnimObjects()
{
	for (auto animBone : m_currentAnimation->GetAnimBones())
	{
		animObjectList.push_back(gameobject->FindChildByName(animBone->GetName())->transform);
	}
}

