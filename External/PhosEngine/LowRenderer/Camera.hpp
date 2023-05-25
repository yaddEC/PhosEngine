#pragma once
#include "Maths/Maths.hpp"

#include <vector>
#include "LowRenderer/Framebuffer.hpp"
#include "Resource/Texture.hpp"

#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "LowRenderer/Light/SpotLight.hpp"

#include "dllInclude.hpp"


namespace Resource
{
	class ShaderProgram;
	class Mesh;
	class Material;
	class CubeMap;
	class PostProcessingShader;
}

namespace LowRenderer
{
	class MeshRenderer;
}

namespace Engine
{
	class Transform;
}

namespace LowRenderer
{
	class PHOSENGINE_API Camera
	{
	public:
		Camera();
		~Camera();

		Engine::Transform* transform;

		void Render(const std::vector<LowRenderer::MeshRenderer*>& rendList,
			const Maths::Vec2& viewportSize, const Resource::CubeMap* skybox);
		void IdPickerRender(const std::vector<LowRenderer::MeshRenderer*>& rendList, const Maths::Vec2& viewportSize);
		void IdPickerIcon(const std::vector<DirectionalLight*>& m_directionalLights, std::vector<PointLight*>& m_pointLights, std::vector<SpotLight*>& m_spotLights, const Maths::Vec2& viewportSize);
		void RenderIcon(const std::vector<DirectionalLight*>& m_directionalLights, std::vector<PointLight*>& m_pointLights, std::vector<SpotLight*>& m_spotLights, const Maths::Vec2& viewportSize);

		Resource::Texture& GetRenderTexture();
		void OnGUI();
		void ApplyPostProcessing(const Maths::Vec2& viewPort);

		static Resource::Texture* TakePhoto(const  Resource::Mesh& mesh, const Engine::Transform& meshTransform,
			const Engine::Transform& camTransform, const Resource::Material& material, float fov = 50.f);

		Maths::Mat4 GetViewMatrix() const { return m_viewMatrix; }
		Maths::Mat4 GetProjMatrix() const { return m_projMatrix; }
		void ComputeViewProjMatrix(const Maths::Vec2& viewportSize);

	private:

		LowRenderer::FrameBuffer m_framebuffer;
		LowRenderer::FrameBuffer m_postProFramebuffer;
		Resource::PostProcessingShader* m_postPro;

		Resource::Texture m_renderTexture;
		Resource::Texture m_postProRenderTexture;

		enum class BackGround
		{
			BG_Skybox,
			BG_Color
		};

		BackGround m_backgroundMode;
		Maths::Vec4 m_backgroundColor;

		float fov = 50.f;
		Maths::Mat4 m_viewMatrix;
		Maths::Mat4 m_projMatrix;

	};
}

