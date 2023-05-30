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
	class CameraComponent;
	class MeshRenderer;
	class DirectionalLight;
	class PointLight;
	class SpotLight;

	class PHOSENGINE_API Renderer
	{
	public:
		
		void ComputeShadowMap();

		void PreComputeShaderData();
		void RenderAll(Camera* mainCamera, Maths::Vec2 viewportSize, bool renderAllCameras);
		void RenderCollider(Camera* mainCamera, Maths::Vec2 viewportSize);

		int IdPicker(Camera* mainCamera, Maths::Vec2 viewportSize, Maths::Vec2 TabPos);
		void RenderIcon(Camera* mainCamera, Maths::Vec2 viewportSize);

		void AddMeshRenderer(MeshRenderer* rend) { m_meshRenderers.push_back(rend); }
		void DeleteMeshRenderer(MeshRenderer* rend);

		void AddCamera(CameraComponent* cam) { m_cameras.push_back(cam); }
		void DeleteCamera(CameraComponent* cam);
		std::vector<CameraComponent*> GetCameraList() const { return m_cameras; }


		void AddDirLight(DirectionalLight* dir) { m_directionalLights.push_back(dir); }
		void DeleteDirLight(DirectionalLight* dir);

		void AddPointLight(PointLight* point) { m_pointLights.push_back(point); }
		void DeletePointLight(PointLight* point);

		void AddSpotLight(SpotLight* spot) { m_spotLights.push_back(spot); }
		void DeleteSpotLight(SpotLight* spto);

		void AddColliderMesh(Physic::Collider* col) { m_colliderDebugList.push_back(col); }
		void DeleteColliderMesh(Physic::Collider* col);

		std::vector<MeshRenderer*> GetMeshRenderers();
		Maths::Vec3 GetAmbient() const;
		Resource::CubeMap* GetSkybox() const { return m_skybox; }
		void SetSkybox(Resource::CubeMap* cubeMap) { m_skybox = cubeMap; }
		
	private:

		std::vector<MeshRenderer*> m_meshRenderers;
		std::vector<Physic::Collider*> m_colliderDebugList;

		std::vector<CameraComponent*> m_cameras;
		std::vector<DirectionalLight*> m_directionalLights;
		std::vector<PointLight*> m_pointLights;
		std::vector<SpotLight*> m_spotLights;
		Maths::Vec3 m_ambient = Maths::Vec3(0.3f, 0.3f, 0.3f);
		Resource::CubeMap* m_skybox = nullptr;
	};


}