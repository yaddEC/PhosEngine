// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "LowRenderer/Camera.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "Resource/Material.hpp"
#include "LowRenderer/Light/SpotLight.hpp"

#include "Resource/ShaderProgram.hpp"

#include "Engine/Transform.hpp"
#include "Resource/ResourceManager.hpp"

#include "Wrapper/RHI.hpp"

#define RENDERER_EXPORTS
#include "LowRenderer/Renderer.hpp"

using namespace LowRenderer;

void Renderer::RenderAll(Camera* mainCamera, Maths::Vec2 viewportSize, bool renderAllCameras)
{



	std::vector<Resource::ShaderProgram*> shaderList;
	for (MeshRenderer* rend : m_meshRenderers)
	{
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
		shader->SetUniformVec3("ambientColor", m_ambient);
		shader->SetUniformVec3("viewPos", mainCamera->transform->position);

		shader->SetUniformInt("lenghtDirLight", m_directionalLights.size());
		shader->SetUniformInt("lenghtPointLight", m_pointLights.size());
		shader->SetUniformInt("lenghtSpotLight", m_spotLights.size());

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

	

	if (renderAllCameras)
	{
		for (Camera* cam : m_cameras)
		{
			if (cam == mainCamera) continue;
			cam->Render(m_meshRenderers, viewportSize, m_skybox);
		}
	}

	mainCamera->Render(m_meshRenderers, viewportSize, m_skybox);
	
}
int Renderer::IdPicker(Camera* mainCamera, Maths::Vec2 viewportSize, Maths::Vec2 TabPos)
{
	
	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	rm.pickingShader->Use();

	mainCamera->IdPickerRender(m_meshRenderers, viewportSize);

	unsigned char* pixelColor = Wrapper::RHI::GetPixelColor(viewportSize, TabPos);
	int pickedID =
		pixelColor[0] +
		pixelColor[1] * 256 +
		pixelColor[2] * 256 * 256;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return pickedID;
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
