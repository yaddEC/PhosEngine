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
