#pragma once
#include "Maths/Maths.hpp"
#include <vector>

#ifdef VERTEX_EXPORTS
#define VERTEX_API __declspec(dllexport)
#else
#define VERTEX_API __declspec(dllimport)
#endif


#ifdef SUBMESH_EXPORTS
#define SUBMESH_API __declspec(dllexport)
#else
#define SUBMESH_API __declspec(dllimport)
#endif

namespace Resource
{
	class Material;

	struct VERTEX_API Vertex
	{
		Maths::Vec3 position;
		Maths::Vec3 normal;
		Maths::Vec2 UVCoords;
	};

	class SUBMESH_API SubMesh
	{
	public:
		SubMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, class Texture* _texture);

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		// TEMP : meant to be replaced by material.
		class Texture* texture;

		void Render(const class ShaderProgram& shaderProgram, const class Material& material) const;

		void Unload();

		void SetUpSubMesh();
	private:
		unsigned int m_VAO, m_VBO, m_EBO;

	};
}


