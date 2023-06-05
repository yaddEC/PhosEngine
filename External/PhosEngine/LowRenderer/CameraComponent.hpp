#pragma once
#include "Engine/MonoBehaviour.hpp"
#include "LowRenderer/Framebuffer.hpp"

namespace Resource
{
	class ShaderProgram;
	class Mesh;
	class Material;
	class CubeMap;
	class PostProcessingShader;
}

namespace UI
{
	class Canvas;
}


namespace LowRenderer
{
	class MeshRenderer;

	class PHOSENGINE_API CameraComponent : public Engine::MonoBehaviour
	{
	public:

		CameraComponent();

		void Start() override;
		void OnInspector() override;
		void Update() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;

		void Render(const std::vector<LowRenderer::MeshRenderer*>& rendList,
			const Maths::Vec2& viewportSize, const Resource::CubeMap* skybox);

		Resource::Texture& GetRenderTexture();
		void ComputeViewProjMatrix(const Maths::Vec2& viewportSize);

		Maths::Vec2 windowPos;

	private:

		void ApplyPostProcessing(const Maths::Vec2& viewPort);

		float m_fov = 50.f;

		LowRenderer::FrameBuffer m_framebuffer;
		LowRenderer::FrameBuffer m_postProFramebuffer;
		Resource::PostProcessingShader* m_postPro = nullptr;

		Resource::Texture m_renderTexture;
		Resource::Texture m_postProRenderTexture;

		bool m_useSkybox;
		Maths::Vec3 m_backgroundColor;

		Maths::Mat4 m_viewMatrix;
		Maths::Mat4 m_projMatrix;
		Maths::Vec2 m_viewportSize;
		UI::Canvas* m_canvas = nullptr;
	};
}