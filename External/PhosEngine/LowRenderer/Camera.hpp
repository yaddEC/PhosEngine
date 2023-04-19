#pragma once
#include "Maths/Maths.hpp"

#include <vector>
#include "LowRenderer/Framebuffer.hpp"
#include "Resource/Texture.hpp"

#include "dllInclude.hpp"


namespace Resource
{
	class ShaderProgram;
	class Mesh;
	class Material;
	class CubeMap;
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

		Resource::Texture& GetRenderTexture();
		Resource::ShaderProgram& GetShaderProg();
		void OnGUI();

		static Resource::Texture* TakePhoto(const  Resource::Mesh& mesh, const Engine::Transform& meshTransform,
			const Engine::Transform& camTransform, const Resource::Material& material, float fov = 50.f);

	private:

		LowRenderer::FrameBuffer m_framebuffer;
		Resource::Texture m_renderTexture;

		enum class BackGround
		{
			BG_Skybox,
			BG_Color
		};

		BackGround m_backgroundMode;
		Maths::Vec4 m_backgroundColor;

		float fov = 50.f;
	};
}

