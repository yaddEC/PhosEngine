// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/Scene.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ResourceIncludes.hpp"
#include "LowRenderer/Renderer.hpp"
#include "LowRenderer/CameraComponent.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Resource/Texture.hpp"
#include "Wrapper/RHI.hpp"
#include "Wrapper/GUI.hpp"

LowRenderer::CameraComponent::CameraComponent()
    : MonoBehaviour(true)
    , m_framebuffer(FrameBuffer(10, 10))
    , m_postProFramebuffer(FrameBuffer(10, 10, false))
    , m_renderTexture(Resource::Texture())
    , m_postProRenderTexture(Resource::Texture())
{
    m_renderTexture.Bind();
    m_framebuffer.AttachTexture(&m_renderTexture);

    m_postProRenderTexture.Bind();
    m_postProFramebuffer.AttachTexture(&m_postProRenderTexture);
}

void LowRenderer::CameraComponent::Start()
{
	gameobject->GetScene()->GetRenderer()->AddCamera(this);
}

void LowRenderer::CameraComponent::OnInspector()
{
    MonoBehaviour::OnInspector();
}

void LowRenderer::CameraComponent::Update()
{
    if (gameobject->GetScene()->GetIsGameMode())
    {
        if (m_canvas)
            m_canvas->Update(windowPos, m_viewportSize);
    }
}

void LowRenderer::CameraComponent::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeleteCamera(this);
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
			ClassMemberInfo("FOV", offsetof(CameraComponent, CameraComponent::m_fov), MemberType::T_FLOAT),
			ClassMemberInfo("UseSkybox", offsetof(CameraComponent, CameraComponent::m_useSkybox), MemberType::T_BOOL),
			ClassMemberInfo("BackGroundColor", offsetof(CameraComponent, CameraComponent::m_backgroundColor), MemberType::T_COLOR),
            ClassMemberInfo("PostProcessingShader", offsetof(CameraComponent, CameraComponent::m_postPro), MemberType::T_POST_PROCESSING_SHADER),
            ClassMemberInfo("Canvas", offsetof(CameraComponent, CameraComponent::m_canvas), MemberType::T_CANVAS)
		};
		computed = true;
	}
	return result;
}

void LowRenderer::CameraComponent::Render(const std::vector<LowRenderer::MeshRenderer*>& rendList, const Maths::Vec2& viewportSize, const Resource::CubeMap* skybox)
{
    using namespace Maths;

    Mat4 viewProj = m_viewMatrix * m_projMatrix;
    m_framebuffer.Bind(true, (int)viewportSize.x, (int)viewportSize.y);
    m_framebuffer.Clear(Maths::Vec4(m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z, 1));
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (skybox && m_useSkybox) // Skybox
    {
        Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
        rm.skyboxShader->Use();

        glCullFace(GL_BACK);
        glDepthMask(GL_FALSE);

        Mat4 skyBoxView = m_viewMatrix;
        skyBoxView.data4V[0].w = 0;
        skyBoxView.data4V[1].w = 0;
        skyBoxView.data4V[2].w = 0;

        rm.skyboxShader->SetCubeMap("skybox", 0, *skybox);
        rm.skyboxShader->SetUniformMatrix("ViewProj", (skyBoxView * m_projMatrix));

        Wrapper::RHI::RenderSubMesh(rm.cube->GetSubMesh(0).GetVAO(), rm.cube->GetSubMesh(0).indices);
    }

    glCullFace(GL_FRONT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    for (MeshRenderer* rend : rendList)
    {
        rend->Render(viewProj, transform->position);
    }

    if (m_postPro)
    {
        glCullFace(GL_BACK);
        ApplyPostProcessing(viewportSize);
    }

    if(m_canvas)
        m_canvas->RenderUI(viewportSize);
    // unbind the framebuffer
    Wrapper::RHI::UnbindFrameBuffer();
}

Resource::Texture& LowRenderer::CameraComponent::GetRenderTexture()
{
    if (m_postPro)
        return m_postProRenderTexture;
    else
        return m_renderTexture;
}

void LowRenderer::CameraComponent::ComputeViewProjMatrix(const Maths::Vec2& viewportSize)
{
    m_viewportSize = viewportSize;
	m_projMatrix = Maths::Mat4::CreateProjectionMatrix(m_fov, 0.01f, 400, viewportSize.y / viewportSize.x);
	m_viewMatrix = Maths::Mat4::LookAt(transform->GetGlobalPosition(),
		transform->GetGlobalPosition() - transform->GetForwardVector(),
        transform->GetUpVector());
}

void LowRenderer::CameraComponent::ApplyPostProcessing(const Maths::Vec2& viewPort)
{
    Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
    m_postProFramebuffer.Bind(true, (int)viewPort.x, (int)viewPort.y);
    m_postProFramebuffer.Clear();
    m_postPro->Use();
    m_postPro->SetTexture("screenTexture", 0, m_renderTexture);
    Wrapper::RHI::RenderSubMesh(rm.quad->GetSubMesh(0).GetVAO(), rm.quad->GetSubMesh(0).indices);
    //Wrapper::RHI::UnbindFrameBuffer();
}
