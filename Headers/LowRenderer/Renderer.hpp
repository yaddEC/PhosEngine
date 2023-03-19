#pragma once
#include "Maths/Maths.hpp"
#include <vector>

#ifdef RENDERER_EXPORTS
#define RENDERER_API __declspec(dllexport)
#else
#define RENDERER_API __declspec(dllimport)
#endif

namespace LowRenderer
{
	class Camera;
	class MeshRenderer;

	class RENDERER_API Renderer
	{
	public:
		
		void ComputeShadowMap() {}; // Empty for now
		void RenderAll(Camera* mainCamera, Maths::Vec2 viewportSize, bool renderAllCameras); 


	private:

		std::vector<MeshRenderer*> m_meshRenderers;
		std::vector<Camera*> m_cameras;

	};


}