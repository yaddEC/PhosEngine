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

		void AddDirLight(DirectionalLight* dir) { m_directionalLights.push_back(dir); }
		void DeleteDirLight(DirectionalLight* dir);

		void AddPointLight(PointLight* point) { m_pointLights.push_back(point); }
		void DeletePointLight(PointLight* point);

		void AddSpotLight(SpotLight* spot) { m_spotLights.push_back(spot); }
		void DeleteSpotLight(SpotLight* dir);

		std::vector<MeshRenderer*> GetMeshRenderers();
		Maths::Vec4 GetAmbient() const;
	private:

		std::vector<MeshRenderer*> m_meshRenderers;
		std::vector<Camera*> m_cameras;
		std::vector<DirectionalLight*> m_directionalLights;
		std::vector<PointLight*> m_pointLights;
		std::vector<SpotLight*> m_spotLights;
		Maths::Vec4 ambient = Maths::Vec4(1);
	};


}