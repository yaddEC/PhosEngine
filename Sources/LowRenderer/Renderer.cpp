// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "LowRenderer/Camera.hpp"
#include "LowRenderer/MeshRenderer.hpp"

#define RENDERER_EXPORTS
#include "LowRenderer/Renderer.hpp"

using namespace LowRenderer;

void Renderer::RenderAll(Camera* mainCamera, Maths::Vec2 viewportSize, bool renderAllCameras)
{
	if (renderAllCameras)
	{
		for (Camera* cam : m_cameras)
		{
			if (cam == mainCamera) continue;
			cam->Render(m_meshRenderers, viewportSize);
		}
	}
	mainCamera->Render(m_meshRenderers, viewportSize);
}

void LowRenderer::Renderer::DeleteMeshRenderer(MeshRenderer* rend)
{
	for (std::vector<MeshRenderer*>::iterator it = m_meshRenderers.begin(); it != m_meshRenderers.end();)
	{
		if (*it == rend)
		{
			it = m_meshRenderers.erase(it);
			return;
		}
		else
		{
			++it;
		}
	}
}

std::vector<MeshRenderer*> LowRenderer::Renderer::GetMeshRenderers()
{
	return m_meshRenderers;
}

Maths::Vec3 LowRenderer::Renderer::GetAmbiente() const
{
	return ambiente;
}
