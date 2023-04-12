#pragma once
#include "Maths/Maths.hpp"
#include <vector>

#include "dllInclude.hpp"

namespace Resource
{
	class Material;

	struct PHOSENGINE_API Vertex
	{
		Maths::Vec3 position;
		Maths::Vec3 normal;
		Maths::Vec2 UVCoords;
		Maths::Vec3 tangents;
		Maths::Vec3 bitangents;
	};

	class PHOSENGINE_API SubMesh
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

		unsigned int GetVAO() { return m_VAO; }
	private:
		unsigned int m_VAO, m_VBO, m_EBO;

	};
}


