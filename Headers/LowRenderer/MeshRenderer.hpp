#pragma once
#include "Maths/Maths.hpp"

#ifdef MESHRENDERER_EXPORTS
#define MESHRENDERER_API __declspec(dllexport)
#else
#define MESHRENDERER_API __declspec(dllimport)
#endif

namespace Resource
{
	class ShaderProgram;
	class Mesh;
}

namespace Engine
{
	class Transform;
}

namespace LowRenderer
{
	class MESHRENDERER_API MeshRenderer
	{
	public:

		MeshRenderer(Resource::Mesh* mesh = nullptr);
		~MeshRenderer();

		Engine::Transform* transform; // TEMPORARY

		void Render(const Resource::ShaderProgram* shader, const Maths::Mat4& viewProj) const;
	private:
		Resource::Mesh* m_mesh;
	};
}


