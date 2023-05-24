// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "LowRenderer/CameraComponent.hpp"

void LowRenderer::CameraComponent::Start()
{
}

void LowRenderer::CameraComponent::OnDestroy()
{
}

Reflection::ClassMetaData& LowRenderer::CameraComponent::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Camera Component";
		result.memberList =
		{
			ClassMemberInfo("Field of view", offsetof(CameraComponent, CameraComponent::m_fov), MemberType::T_FLOAT),
			ClassMemberInfo("Use Skybox", offsetof(CameraComponent, CameraComponent::m_useSkybox), MemberType::T_BOOL),
			ClassMemberInfo("BackGround Color", offsetof(CameraComponent, CameraComponent::m_backgroundColor), MemberType::T_COLOR),
		};
		computed = true;
	}
	return result;
}

void LowRenderer::CameraComponent::Render(const std::vector<LowRenderer::MeshRenderer*>& rendList, const Maths::Vec2& viewportSize, const Resource::CubeMap* skybox)
{

}

Resource::Texture& LowRenderer::CameraComponent::GetRenderTexture()
{
	// TODO: insérer une instruction return ici
	return m_renderTexture;
}

void LowRenderer::CameraComponent::ComputeViewProjMatrix(const Maths::Vec2& viewportSize)
{
	m_projMatrix = Maths::Mat4::CreateProjectionMatrix(m_fov, 0.01f, 400, viewportSize.y / viewportSize.x);
	m_viewMatrix = Maths::Mat4::LookAt(transform->GetGlobalPosition(),
		transform->GetGlobalPosition() + transform->GetForwardVector(),
		transform->GetGlobalPosition() + transform->GetUpVector());
}

void LowRenderer::CameraComponent::ApplyPostProcessing(const Maths::Vec2& viewPort)
{

}
