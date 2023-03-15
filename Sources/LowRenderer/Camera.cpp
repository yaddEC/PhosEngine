// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Resource/ShaderProgram.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Engine/Transform.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Mesh.hpp"

#define CAMERA_EXPORTS
#include "LowRenderer/Camera.hpp"


using namespace LowRenderer;
using namespace Resource;
using namespace Engine;
using namespace Maths;


Camera::Camera()
    : m_framebuffer(FrameBuffer(10, 10))
    , m_renderTexture(Texture())
    , rm(ResourceManager::GetInstance())
{

    transform = new Transform;
    transform->position = Vec3(0, 0, -10);

    m_shaderProgram = ResourceManager::GetInstance().GetResource<ShaderProgram>("Assets\\Shader\\BasicShader.prog");


    m_renderTexture.Bind();
    m_framebuffer.AttachTexture(&m_renderTexture);
}

Camera::~Camera()
{
    delete transform;
}

void Camera::Render(const std::vector<MeshRenderer*>& rendList, const Vec2& viewportSize)
{

    Mat4 proj = Mat4::CreateProjectionMatrix(fov, 0.01f, 400, viewportSize.y / viewportSize.x);
    Mat4 view = Mat4::CreateViewMatrix(transform->position, transform->rotation.x, transform->rotation.y);

    Mat4 viewProj = view * proj;

    m_framebuffer.Bind(viewportSize.x, viewportSize.y);
    m_framebuffer.Clear(Maths::Vec4(0, 0.1f, 0.2f, 1));

    m_shaderProgram->Use();

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    for (MeshRenderer* rend : rendList)
    {
        rend->Render(m_shaderProgram, viewProj);
    }

    // unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Camera::OnGUI()
{
    /*if (ImGui::CollapsingHeader("Scene Camera"))
    {
        transform->OnGUI();
        ImGui::DragFloat("fov", &fov, 0.1f, 0.1f, 89);

    }*/
}

Texture* Camera::TakePhoto(const Mesh& mesh, const Transform& meshTransform, const Transform& camTransform, const ShaderProgram& shaderProgram, float fov)
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

    shaderProgram.Use();
    shaderProgram.SetUniformMatrix("model", model);
    shaderProgram.SetUniformMatrix("mvp", model * viewProj);

    mesh.Render(shaderProgram);

    framebuffer.DetachTexture();

    return result;
}
