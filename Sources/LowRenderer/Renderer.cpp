// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "LowRenderer/Camera.hpp"
#include "LowRenderer/CameraComponent.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "Resource/Material.hpp"
#include "LowRenderer/Light/SpotLight.hpp"

#include "Resource/ShaderProgram.hpp"
#include "Physic/Collider.hpp"

#include "Maths/Maths.hpp"
#include "Engine/Transform.hpp"
#include "Resource/ResourceManager.hpp"
#include "Wrapper/RHI.hpp"
#include "LowRenderer/Renderer.hpp"

using namespace LowRenderer;

void LowRenderer::Renderer::PreComputeShaderData()
{
	for (MeshRenderer* rend : m_meshRenderers)
	{
		if (rend->GetMesh() && rend->GetMesh()->GetArmature())
		{
			rend->SetSkinningMatrices();
		}
	}

	std::vector<Resource::ShaderProgram*> shaderList;
	for (MeshRenderer* rend : m_meshRenderers)
	{
		if (!rend->GetMesh() || !rend->GetMaterial()) continue;
		bool isShaderInList = false;
		for (Resource::ShaderProgram* shader : shaderList)
		{
			if (rend->GetMaterial()->GetShader() == shader)
			{
				isShaderInList = true;
				break;
			}
		}
		if (isShaderInList) continue;
		else shaderList.push_back(rend->GetMaterial()->GetShader());
	}

	for (Resource::ShaderProgram* shader : shaderList)
	{
		if (!shader)continue;
		shader->Use();

		shader->SetUniformInt("lenghtDirLight", static_cast<int>(m_directionalLights.size()));
		shader->SetUniformInt("lenghtPointLight", static_cast<int>(m_pointLights.size()));
		shader->SetUniformInt("lenghtSpotLight", static_cast<int>(m_spotLights.size()));

		for (int i = 0; i < m_directionalLights.size(); i++)
		{
			m_directionalLights[i]->Render(*shader, i);
		}

		for (int i = 0; i < m_pointLights.size(); i++)
		{
			m_pointLights[i]->Render(*shader, i);
		}

		for (int i = 0; i < m_spotLights.size(); i++)
		{
			m_spotLights[i]->Render(*shader, i);
		}
	}
}

void Renderer::RenderAll(Camera* mainCamera, const Maths::Vec2& viewportSize, bool renderAllCameras)
{
	if (renderAllCameras)
	{
		for (CameraComponent* cam : m_cameras)
		{
			cam->ComputeViewProjMatrix(viewportSize);
			cam->Render(m_meshRenderers, viewportSize, m_skybox);
		}
	}
	if (mainCamera)
	{
		mainCamera->ComputeViewProjMatrix(viewportSize);
		mainCamera->Render(m_meshRenderers, viewportSize, m_skybox);
	}
	
}

//void LowRenderer::Renderer::RenderCollider(Camera* mainCamera, Engine::Scene* scene, const Maths::Vec2& viewportSize)
//{
//	if (mainCamera)
//	{
//		mainCamera->ComputeViewProjMatrix(viewportSize);
//		mainCamera->RenderMeshList(scene, viewportSize);
//	}
//}

void LowRenderer::Renderer::DrawGizmo(Camera* mainCamera, const Maths::Vec2& viewportSize)
{
	if (mainCamera)
	{
		mainCamera->ComputeViewProjMatrix(viewportSize);
		mainCamera->RenderGizmoList(m_gizmoList, viewportSize);
	}
}

int Renderer::IdPicker(Camera* mainCamera, Maths::Vec2 viewportSize, Maths::Vec2 TabPos)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	rm.pickingShader->Use();

	mainCamera->IdPickerRender(m_meshRenderers, viewportSize);

	rm.iconShaderForPicking->Use();
	mainCamera->IdPickerIcon(m_directionalLights, m_pointLights, m_spotLights, viewportSize);

	std::array<char, 4> pixelColor = Wrapper::RHI::GetPixelColor(viewportSize, TabPos);
	int pickedID =
		pixelColor[0] +
		pixelColor[1] * 256 +
		pixelColor[2] * 256 * 256;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return pickedID;
}

void Renderer::RenderIcon(Camera* mainCamera, Maths::Vec2 viewportSize)
{
	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	rm.iconShader->Use();
	mainCamera->RenderIcon(m_directionalLights, m_pointLights, m_spotLights, viewportSize);
}

void LowRenderer::Renderer::DeleteMeshRenderer(MeshRenderer* rend)
{
	for (std::vector<MeshRenderer*>::iterator it = m_meshRenderers.begin(); it != m_meshRenderers.end(); ++it)
	{
		if (*it == rend)
		{
			it = m_meshRenderers.erase(it);
			return;
		}
	}
}

void LowRenderer::Renderer::DeleteCamera(CameraComponent* cam)
{
	for (std::vector<CameraComponent*>::iterator it = m_cameras.begin(); it != m_cameras.end(); ++it)
	{
		if (*it == cam)
		{
			it = m_cameras.erase(it);
			return;
		}
	}
}

void LowRenderer::Renderer::DeleteDirLight(DirectionalLight* dir)
{
	for (std::vector<DirectionalLight*>::iterator it = m_directionalLights.begin(); it != m_directionalLights.end(); ++it)
	{
		if (*it == dir)
		{
			it = m_directionalLights.erase(it);
			return;
		}
	}
}

void LowRenderer::Renderer::DeletePointLight(PointLight* point)
{
	for (std::vector<PointLight*>::iterator it = m_pointLights.begin(); it != m_pointLights.end(); ++it)
	{
		if (*it == point)
		{
			it = m_pointLights.erase(it);
			return;
		}
	}
}

void LowRenderer::Renderer::DeleteSpotLight(SpotLight* dir)
{
	for (std::vector<SpotLight*>::iterator it = m_spotLights.begin(); it != m_spotLights.end(); ++it)
	{
		if (*it == dir)
		{
			it = m_spotLights.erase(it);
			return;
		}
	}
}


std::vector<MeshRenderer*> LowRenderer::Renderer::GetMeshRenderers()
{
	return m_meshRenderers;
}

Maths::Vec3 LowRenderer::Renderer::GetAmbient() const
{
	return m_ambient;
}

void LowRenderer::Renderer::SphereGizmo(const Maths::Vec3& position, const Maths::Vec3& scale, const Maths::Vec3& color)
{
	m_gizmoList.push_back(Gizmo(Resource::ResourceManager::GetInstance().sphere, position, Maths::Vec3(), scale, color));
}

void LowRenderer::Renderer::BoxGizmo(const Maths::Vec3& position, const Maths::Vec3& rotation,
	const Maths::Vec3& scale, const Maths::Vec3& color)
{
	m_gizmoList.push_back(Gizmo(Resource::ResourceManager::GetInstance().cube, position, rotation, scale, color));
}

void LowRenderer::Renderer::CapsuleGizmo(const Maths::Vec3& position, const Maths::Vec3& rotation,
	const Maths::Vec3& scale, const Maths::Vec3& color)
{
	m_gizmoList.push_back(Gizmo(Resource::ResourceManager::GetInstance().capsule, position, rotation, scale, color));
}
