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
#include "Physic/Collider.hpp"

#include "LowRenderer/Camera.hpp"

using namespace LowRenderer;
using namespace Resource;
using namespace Engine;
using namespace Maths;


Camera::Camera()
    : m_framebuffer(FrameBuffer(10, 10))
    , m_postProFramebuffer(FrameBuffer(10, 10))
    , m_renderTexture(Texture())
    , m_postProRenderTexture(Texture())
{

    transform = new Transform;
    transform->position = Vec3(0, 0, -10);



    m_renderTexture.Bind();
    m_framebuffer.AttachTexture(&m_renderTexture);

    m_postProRenderTexture.Bind();
    m_postProFramebuffer.AttachTexture(&m_postProRenderTexture);
}

Camera::~Camera()
{
    delete transform;
}

void Camera::Render(const std::vector<MeshRenderer*>& rendList, const Vec2& viewportSize, const Resource::CubeMap* skybox)
{
    Mat4 viewProj = m_viewMatrix * m_projMatrix;
   

    m_framebuffer.Bind(true, (int)viewportSize.x, (int)viewportSize.y);
    //m_framebuffer.Clear(m_backgroundColor);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (skybox && m_backgroundMode == BackGround::BG_Skybox) // Skybox
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
    // unbind the framebuffer
    Wrapper::RHI::UnbindFrameBuffer();
}

void LowRenderer::Camera::RenderGizmoList(const std::vector<Gizmo>& gizmoList, const Maths::Vec2& viewportSize)
{
    m_framebuffer.Bind(true, (int)viewportSize.x, (int)viewportSize.y);
    glCullFace(GL_FRONT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glLineWidth(3);

    Resource::ResourceManager::GetInstance().colorShader->Use();

    for (Gizmo gizmo : gizmoList)
    {
        Maths::Mat4 modelMat = Maths::Mat4::CreateTransformMatrix(gizmo.position, gizmo.rotationEuler, gizmo.scale);

        Resource::ResourceManager::GetInstance().colorShader->SetUniformMatrix("mvp",
            modelMat * m_viewMatrix * m_projMatrix);
        gizmo.mesh->RenderFlatColor(Maths::Vec3(0.1f, 0.8f, 0.1f));
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Wrapper::RHI::UnbindFrameBuffer();
}

void LowRenderer::Camera::RenderMeshList(Engine::Scene* scene, const Maths::Vec2& viewportSize)
{
    m_framebuffer.Bind(true, (int)viewportSize.x, (int)viewportSize.y);
    m_framebuffer.Clear(m_backgroundColor);
    glCullFace(GL_FRONT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glLineWidth(4);

    Resource::ResourceManager::GetInstance().colorShader->Use();

    for (auto go : scene->GetGameObjects())
    {
        Physic::Collider* col = nullptr;
        Resource::Mesh* mesh = nullptr;

        if (col = go->GetComponent<BoxCollider>())
        {
            mesh = Resource::ResourceManager::GetInstance().cube;
        }

        if (!col) continue;

        Resource::ResourceManager::GetInstance().colorShader->SetUniformMatrix("mvp",
            col->transform->GetGlobalMatrix() * m_viewMatrix * m_projMatrix);
        mesh->RenderFlatColor(Maths::Vec3(0.1f, 0.8f, 0.1f));
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Wrapper::RHI::UnbindFrameBuffer();
}

void Camera::IdPickerRender(const std::vector<MeshRenderer*>& rendList, const Vec2& viewportSize)
{
    Mat4 proj = Mat4::CreateProjectionMatrix(fov, 0.01f, 400, viewportSize.y / viewportSize.x);
    Mat4 view = Mat4::CreateViewMatrix(transform->position, transform->rotationEuler.x, transform->rotationEuler.y);
    Mat4 viewProj = view * proj;

    m_framebuffer.Bind(true, (int)viewportSize.x, (int)viewportSize.y);
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

void Camera::IdPickerIcon(const std::vector<DirectionalLight*>& m_directionalLights, std::vector<PointLight*>& m_pointLights, std::vector<SpotLight*>& m_spotLights, const Maths::Vec2& viewportSize)
{
    Mat4 proj = Mat4::CreateProjectionMatrix(fov, 0.01f, 400, viewportSize.y / viewportSize.x);
    Mat4 view = Mat4::CreateViewMatrix(transform->position, transform->rotationEuler.x, transform->rotationEuler.y);

    m_framebuffer.Bind(true, (int)viewportSize.x, (int)viewportSize.y);
    // m_framebuffer.Clear({ 0,0,0,255 });

    glCullFace(GL_FRONT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
    rm.iconShaderForPicking->SetUniformMatrix("projectionMatrix", proj);

    for (DirectionalLight* DLight : m_directionalLights)
    {
        rm.iconShaderForPicking->SetUniformMatrix("modelViewMatrix", DLight->transform->GetGlobalMatrix() * view);

        int r = (DLight->gameobject->GetID() & 0x000000FF) >> 0;
        int g = (DLight->gameobject->GetID() & 0x0000FF00) >> 8;
        int b = (DLight->gameobject->GetID() & 0x00FF0000) >> 16;

        rm.iconShaderForPicking->SetUniformVec4("PickingColor", { r / 255.0f, g / 255.0f, b / 255.0f, 1.0f });
        //rm.iconShaderForPicking->SetUniformVec4("PickingColor", { 1, 0, 0, 1.0f }); // DEBUG

        std::vector<SubMesh> LightSMesh = DLight->GetMetaData().PosModelForTexture->GetSubMeshes(); 

        for (int j = 0; j < LightSMesh.size(); j++)
        {
            glBindVertexArray(LightSMesh[j].GetVAO());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, static_cast<int>(LightSMesh[j].indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

    for (PointLight* PLight : m_pointLights)
    {
        rm.iconShaderForPicking->SetUniformMatrix("modelViewMatrix", PLight->transform->GetGlobalMatrix() * view);

        int r = (PLight->gameobject->GetID() & 0x000000FF) >> 0;
        int g = (PLight->gameobject->GetID() & 0x0000FF00) >> 8;
        int b = (PLight->gameobject->GetID() & 0x00FF0000) >> 16;

        rm.iconShaderForPicking->SetUniformVec4("PickingColor", { r / 255.0f, g / 255.0f, b / 255.0f, 1.0f });

        std::vector<SubMesh> LightSMesh = PLight->GetMetaData().PosModelForTexture->GetSubMeshes(); 

        for (int j = 0; j < LightSMesh.size(); j++)
        {
            glBindVertexArray(LightSMesh[j].GetVAO());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, static_cast<int>(LightSMesh[j].indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

    for (SpotLight* SLight : m_spotLights)
    {
        rm.iconShaderForPicking->SetUniformMatrix("modelViewMatrix", SLight->transform->GetGlobalMatrix() * view);

        int r = (SLight->gameobject->GetID() & 0x000000FF) >> 0;
        int g = (SLight->gameobject->GetID() & 0x0000FF00) >> 8;
        int b = (SLight->gameobject->GetID() & 0x00FF0000) >> 16;

        rm.iconShaderForPicking->SetUniformVec4("PickingColor", { r / 255.0f, g / 255.0f, b / 255.0f, 1.0f });

        std::vector<SubMesh> LightSMesh = SLight->GetMetaData().PosModelForTexture->GetSubMeshes(); 

        for (int j = 0; j < LightSMesh.size(); j++)
        {
            glBindVertexArray(LightSMesh[j].GetVAO());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, static_cast<int>(LightSMesh[j].indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}

void Camera::RenderIcon(const std::vector<DirectionalLight*>& m_directionalLights, std::vector<PointLight*>& m_pointLights, std::vector<SpotLight*>& m_spotLights, const Maths::Vec2& viewportSize)
{
    Mat4 proj = Mat4::CreateProjectionMatrix(fov, 0.01f, 400, viewportSize.y / viewportSize.x);
    Mat4 view = Mat4::CreateViewMatrix(transform->position, transform->rotationEuler.x, transform->rotationEuler.y);

    m_framebuffer.Bind(true, (int)viewportSize.x, (int)viewportSize.y);
    // m_framebuffer.Clear({ 0,0,0,255 });

    glCullFace(GL_FRONT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
    rm.iconShader->SetUniformMatrix("projectionMatrix", proj);
    
    for (DirectionalLight* DLight : m_directionalLights)
    {
        rm.iconShader->SetUniformMatrix("modelViewMatrix", DLight->transform->GetGlobalMatrix() * view);
        rm.iconShader->SetTexture("Texture", 0, *DLight->GetMetaData().PosTexture);

        std::vector<SubMesh> LightSMesh = DLight->GetMetaData().PosModelForTexture->GetSubMeshes(); //error 

        for (int j = 0; j < LightSMesh.size(); j++)
        {
            glBindVertexArray(LightSMesh[j].GetVAO());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, static_cast<int>(LightSMesh[j].indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

    for(PointLight* PLight : m_pointLights)
    {
        rm.iconShader->SetUniformMatrix("modelViewMatrix", PLight->transform->GetGlobalMatrix() * view);
        rm.iconShader->SetTexture("Texture", 0, *PLight->GetMetaData().PosTexture);

        std::vector<SubMesh> LightSMesh = PLight->GetMetaData().PosModelForTexture->GetSubMeshes(); //error 

        for (int j = 0; j < LightSMesh.size(); j++)
        {
            glBindVertexArray(LightSMesh[j].GetVAO());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, static_cast<int>(LightSMesh[j].indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

    for (SpotLight* SLight : m_spotLights)
    {
        rm.iconShader->SetUniformMatrix("modelViewMatrix", SLight->transform->GetGlobalMatrix() * view);
        rm.iconShader->SetTexture("Texture", 0, *SLight->GetMetaData().PosTexture);

        std::vector<SubMesh> LightSMesh = SLight->GetMetaData().PosModelForTexture->GetSubMeshes(); //error 

        for (int j = 0; j < LightSMesh.size(); j++)
        {
            glBindVertexArray(LightSMesh[j].GetVAO());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, static_cast<int>(LightSMesh[j].indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
    
}

Resource::Texture& LowRenderer::Camera::GetRenderTexture()
{
    if (m_postPro)
    {
        return m_postProRenderTexture;
    }
    return m_renderTexture;
}


void Camera::OnGUI()
{
    using namespace Wrapper;
    {
        transform->OnGUI();
        GUI::EditFloat("Field of View : ", fov, 1, true, 180);


        static std::vector<std::string> bgModeName = { "Skybox", "Solid Color" };
        std::string selected = bgModeName[(int)m_backgroundMode];
        if (GUI::Combo("Background : ", bgModeName, selected))
        {
            if (selected == "Skybox") m_backgroundMode = BackGround::BG_Skybox;
            if (selected == "Solid Color") m_backgroundMode = BackGround::BG_Color;
        }
        if((int)m_backgroundMode)
            GUI::EditColorRGBA("Background Color : ", m_backgroundColor);
        Wrapper::GUI::PickPostProcessing("Post Processing : ", &m_postPro);
    }
}

void LowRenderer::Camera::ApplyPostProcessing(const Maths::Vec2& viewPort)
{
    Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
    m_postProFramebuffer.Bind(true, (int)viewPort.x, (int)viewPort.y);
    m_postProFramebuffer.Clear(m_backgroundColor);
    m_postPro->Use(); 
    m_postPro->SetTexture("screenTexture", 0, m_renderTexture);
    Wrapper::RHI::RenderSubMesh(rm.quad->GetSubMesh(0).GetVAO(), rm.quad->GetSubMesh(0).indices);
    Wrapper::RHI::UnbindFrameBuffer();
}

Texture* Camera::TakePhoto(const Mesh& mesh, const Transform& meshTransform, const Transform& camTransform, const Resource::Material& material, float fov)
{
    Mat4 proj = Mat4::CreateProjectionMatrix(fov, 0.01f, 200, 1);
    Mat4 view = Mat4::CreateViewMatrix(camTransform.position, camTransform.rotationEuler.x, camTransform.rotationEuler.y);


    Mat4 model = meshTransform.GetGlobalMatrix();

    Mat4 viewProj = view * proj;

    FrameBuffer framebuffer{ 200, 200 };
    Texture* result = new Texture(nullptr, 200, 200, 4);

    result->Bind();
    framebuffer.AttachTexture(result);

    framebuffer.Bind(true, 200, 200);
    framebuffer.Clear(Vec4(0, 0, 0, 0));

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);
    
    
    material.GetShader()->Use();
    material.GetShader()->SetUniformMatrix("model", model);
    material.GetShader()->SetUniformMatrix("mvp", model * viewProj);

    mesh.Render(material);

    framebuffer.DetachTexture();

    return result;
}

void LowRenderer::Camera::ComputeViewProjMatrix(const Maths::Vec2& viewportSize)
{
    m_projMatrix = Mat4::CreateProjectionMatrix(fov, 0.01f, 400, viewportSize.y / viewportSize.x);
    m_viewMatrix = Mat4::CreateViewMatrix(transform->position, transform->rotationEuler.x, transform->rotationEuler.y);
}

void LowRenderer::Camera::ClearBuffers(const Maths::Vec2& viewportSize)
{
    m_framebuffer.Bind(true, viewportSize.x, viewportSize.y);
    m_framebuffer.Clear(m_backgroundColor);

    if (m_postPro)
    {
        m_postProFramebuffer.Bind(true, viewportSize.x, viewportSize.y);
        m_postProFramebuffer.Clear(m_backgroundColor);
    }

    Wrapper::RHI::UnbindFrameBuffer();
}
