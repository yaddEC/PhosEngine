#pragma once
#include "Maths/Maths.hpp"
#include <vector>

#include "dllInclude.hpp"

namespace Resource
{
	class CubeMap;
}

namespace LowRenderer
{
	class Camera;
	class MeshRenderer;
	class DirectionalLight;
	class PointLight;
	class SpotLight;

	class PHOSENGINE_API Renderer
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
		void DeleteSpotLight(SpotLight* spto);

		std::vector<MeshRenderer*> GetMeshRenderers();
		Maths::Vec3 GetAmbient() const;
		Resource::CubeMap* GetSkybox() const { return m_skybox; }
		void SetSkybox(Resource::CubeMap* cubeMap) { m_skybox = cubeMap; }
	private:

		std::vector<MeshRenderer*> m_meshRenderers;
		std::vector<Camera*> m_cameras;
		std::vector<DirectionalLight*> m_directionalLights;
		std::vector<PointLight*> m_pointLights;
		std::vector<SpotLight*> m_spotLights;
		Maths::Vec3 ambient = Maths::Vec3(0.3f, 0.3f, 0.3f);
		Resource::CubeMap* m_skybox = nullptr;
	};


}