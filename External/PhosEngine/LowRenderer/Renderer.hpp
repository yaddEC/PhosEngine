#pragma once
#include "Maths/Maths.hpp"
#include <vector>

#include "dllInclude.hpp"

namespace Resource
{
	class CubeMap;
	class Mesh;
}

namespace LowRenderer
{
	class Camera;
	class CameraComponent;
	class MeshRenderer;
	class DirectionalLight;
	class PointLight;
	class SpotLight;


	struct Gizmo
	{
		Resource::Mesh* mesh;
		Maths::Vec3 position;
		Maths::Vec3 rotationEuler;
		Maths::Vec3 scale;

		Gizmo(Resource::Mesh* _mesh, Maths::Vec3 _position, Maths::Vec3 _rotationEuler, Maths::Vec3 _scale)
			: mesh(_mesh), position(_position), rotationEuler(_rotationEuler), scale(_scale) {}
	};

	class PHOSENGINE_API Renderer
	{
	public:
		
		void ComputeShadowMap();

		void PreComputeShaderData();
		void RenderAll(Camera* mainCamera, const Maths::Vec2& viewportSize, bool renderAllCameras);
		//void RenderCollider(Camera* mainCamera, Engine::Scene* scene, const Maths::Vec2& viewportSize);
		void DrawGizmo(Camera* mainCamera, const Maths::Vec2& viewportSize);

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


		std::vector<MeshRenderer*> GetMeshRenderers();
		Maths::Vec3 GetAmbient() const;
		Resource::CubeMap* GetSkybox() const { return m_skybox; }
		void SetSkybox(Resource::CubeMap* cubeMap) { m_skybox = cubeMap; }

		void AddGizmo(const Gizmo& gizmo) { m_gizmoList.push_back(gizmo); }
		void ClearGizmo() { m_gizmoList.clear(); }
		
	private:

		std::vector<MeshRenderer*> m_meshRenderers;
		std::vector<Gizmo> m_gizmoList;
		std::vector<CameraComponent*> m_cameras;
		std::vector<DirectionalLight*> m_directionalLights;
		std::vector<PointLight*> m_pointLights;
		std::vector<SpotLight*> m_spotLights;
		Maths::Vec3 m_ambient = Maths::Vec3(0.3f, 0.3f, 0.3f);
		Resource::CubeMap* m_skybox = nullptr;
	};


}