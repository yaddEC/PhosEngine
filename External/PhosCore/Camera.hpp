#pragma once
#include "Maths/Maths.hpp"

#include <vector>
#include "LowRenderer/Framebuffer.hpp"
#include "Resource/Texture.hpp"

#ifdef CAMERA_EXPORTS
#define CAMERA_API __declspec(dllexport)
#else
#define CAMERA_API __declspec(dllimport)
#endif


namespace Resource
{
	class ShaderProgram;
	class Mesh;
}

namespace LowRenderer
{
	class MeshRenderer;
}

namespace Engine
{
	class Transform;
}

class CAMERA_API Camera
{
public:
	Camera();
	~Camera();

	Engine::Transform* transform;

	void Render(const std::vector<LowRenderer::MeshRenderer*>& rendList,
		const Maths::Vec2& viewportSize);

	inline unsigned int GetRenderTextureKey() { return renderTexture.GetTextureKey(); }

	void OnGUI();

	static Resource::Texture* TakePhoto(const  Resource::Mesh& mesh, const Engine::Transform& meshTransform, const Engine::Transform& camTransform, const Resource::ShaderProgram& shaderProgram, float fov = 50.f);

private:

	LowRenderer::FrameBuffer framebuffer;
	Resource::Texture renderTexture;

	// For testing
	Resource::ShaderProgram* shaderProgram;

	float fov = 50.f;
};