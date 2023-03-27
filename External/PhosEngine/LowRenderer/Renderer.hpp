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
	class DirectionalLight;
	class PointLight;
	class SpotLight;

	class RENDERER_API Renderer
	{
	public:
		
		void ComputeShadowMap() {}; // Empty for now
		void RenderAll(Camera* mainCamera, Maths::Vec2 viewportSize, bool renderAllCameras); 

		void AddMeshRenderer(MeshRenderer* rend) { m_meshRenderers.push_back(rend); }
		void DeleteMeshRenderer(MeshRenderer* rend);

		std::vector<MeshRenderer*> GetMeshRenderers();
		Maths::Vec3 GetAmbiente() const;
	private:

		std::vector<MeshRenderer*> m_meshRenderers;
		std::vector<Camera*> m_cameras;
		std::vector<DirectionalLight*> m_directionalLights;
		std::vector<PointLight*> m_pointLights;
		std::vector<SpotLight*> m_spotLights;
		Maths::Vec3 ambiente = Maths::Vec3(0);
	};


}