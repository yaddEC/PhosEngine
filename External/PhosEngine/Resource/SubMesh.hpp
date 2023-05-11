#pragma once
#include "Maths/Maths.hpp"
#include <vector>

#include "dllInclude.hpp"

namespace Resource
{
	class Material;

	constexpr size_t MAX_BONE_WEIGHTS = 4;

	struct Vertex
	{
		Maths::Vec3 position;
		Maths::Vec3 normal;
		Maths::Vec2 UVCoords;
		Maths::Vec3 tangents;
		Maths::Vec3 bitangents;
	};

	struct SkinnedVertex
	{
		Maths::Vec3 position;
		Maths::Vec3 normal;
		Maths::Vec2 UVCoords;
		Maths::Vec3 tangents;
		Maths::Vec3 bitangents;
		int boneIDs[MAX_BONE_WEIGHTS];
		float boneWeights[MAX_BONE_WEIGHTS];
	};

	class PHOSENGINE_API SubMesh
	{
	public:
		SubMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		SubMesh(std::vector<SkinnedVertex> vertices, std::vector<unsigned int> indices);

		std::vector<Vertex> vertices;
		std::vector<SkinnedVertex> skninnedVertices;
		std::vector<unsigned int> indices;
		bool isSkinned;


		void Render(const class ShaderProgram& shaderProgram, const class Material& material) const;

		void Unload();

		void SetUpSubMesh();

		unsigned int GetVAO() { return m_VAO; }
	private:
		unsigned int m_VAO, m_VBO, m_EBO;

	};
}


