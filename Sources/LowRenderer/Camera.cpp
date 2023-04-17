// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Wrapper/RHI.hpp"
#include "Resource/ShaderProgram.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Engine/Transform.hpp"
#include "Resource/ResourceIncludes.hpp"
#include "Resource/ResourceManager.hpp"
#include "Wrapper/GUI.hpp"

#define CAMERA_EXPORTS
#include "LowRenderer/Camera.hpp"


using namespace LowRenderer;
using namespace Resource;
using namespace Engine;
using namespace Maths;


Camera::Camera()
    : m_framebuffer(FrameBuffer(10, 10))
    , m_renderTexture(Texture())
{

    transform = new Transform;
    transform->position = Vec3(0, 0, -10);



    m_renderTexture.Bind();
    m_framebuffer.AttachTexture(&m_renderTexture);
}

Camera::~Camera()
{
    delete transform;
}

void Camera::Render(const std::vector<MeshRenderer*>& rendList, const Vec2& viewportSize, const Resource::CubeMap* skybox)
{

    Mat4 proj = Mat4::CreateProjectionMatrix(fov, 0.01f, 400, viewportSize.y / viewportSize.x);
    Mat4 view = Mat4::CreateViewMatrix(transform->position, transform->rotation.x, transform->rotation.y);
    Mat4 viewProj = view * proj;
   

    m_framebuffer.Bind(viewportSize.x, viewportSize.y);
    m_framebuffer.Clear(m_backgroundColor);

    if (skybox && m_backgroundMode == BackGround::BG_Skybox) // Skybox
    {
        Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
        rm.skyboxShader->Use();

        glCullFace(GL_BACK);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);

        Mat4 skyBoxView = view;
        skyBoxView.data4V[0].w = 0;
        skyBoxView.data4V[1].w = 0;
        skyBoxView.data4V[2].w = 0;

        rm.skyboxShader->SetCubeMap("skybox", 0, *skybox);
        rm.skyboxShader->SetUniformMatrix("ViewProj", (skyBoxView * proj));

        Wrapper::RHI::RenderSubMesh(rm.cube->GetSubMesh(0).GetVAO(), rm.cube->GetSubMesh(0).indices);
    }

    
    glCullFace(GL_FRONT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    

    for (MeshRenderer* rend : rendList)
    {
        rend->Render(viewProj);
    }

    // unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Camera::IdPickerRender(const std::vector<MeshRenderer*>& rendList, const Vec2& viewportSize)
{
    Mat4 proj = Mat4::CreateProjectionMatrix(fov, 0.01f, 400, viewportSize.y / viewportSize.x);
    Mat4 view = Mat4::CreateViewMatrix(transform->position, transform->rotation.x, transform->rotation.y);
    Mat4 viewProj = view * proj;

    m_framebuffer.Bind(viewportSize.x, viewportSize.y);
    m_framebuffer.Clear({0,0,0,255});

    glCullFace(GL_FRONT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    for (MeshRenderer* rend : rendList)
    {
        rend->IdPickerRender(viewProj);

    }

    // unbind the framebuffer
}

Resource::Texture& LowRenderer::Camera::GetRenderTexture()
{
    return m_renderTexture;
}


void Camera::OnGUI()
{
    using namespace Wrapper;
    if (GUI::CollapsingHeader("Camera"))
    {
        transform->OnGUI();
        GUI::EditFloat("Field of View : ", fov, 0.1f, 1, 180);


        static std::vector<std::string> bgModeName = { "Skybox", "Solid Color" };
        std::string selected = bgModeName[(int)m_backgroundMode];
        if (GUI::Combo("Background : ", bgModeName, selected))
        {
            if (selected == "Skybox") m_backgroundMode = BackGround::BG_Skybox;
            if (selected == "Solid Color") m_backgroundMode = BackGround::BG_Color;
        }
        if((int)m_backgroundMode)
            GUI::EditColorRGBA("Background Color : ", m_backgroundColor);

    }
}

Texture* Camera::TakePhoto(const Mesh& mesh, const Transform& meshTransform, const Transform& camTransform, const Resource::Material& material, float fov)
{
    Mat4 proj = Mat4::CreateProjectionMatrix(fov, 0.01f, 200, 1);
    Mat4 view = Mat4::CreateViewMatrix(camTransform.position, camTransform.rotation.x, camTransform.rotation.y);


    Mat4 model = meshTransform.GetGlobalMatrix();

    Mat4 viewProj = view * proj;

    FrameBuffer framebuffer{ 200, 200 };
    Texture* result = new Texture(nullptr, 200, 200, 4);

    result->Bind();
    framebuffer.AttachTexture(result);

    framebuffer.Bind(200, 200);
    framebuffer.Clear(Vec4(0, 0, 0, 0));

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);
    
    
    material.GetShader()->Use();
    material.GetShader()->SetUniformMatrix("model", model);
    material.GetShader()->SetUniformMatrix("mvp", model * viewProj);

    mesh.Render(*material.GetShader(), material);

    framebuffer.DetachTexture();

    return result;
}
