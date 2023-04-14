#pragma once
#include "Resource/IResource.hpp"
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Resource/SubMesh.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class Material;

	class PHOSENGINE_API Mesh : public IResource
	{
	public:
		Mesh() : IResource()
		{
			m_boundingBoxMin = Maths::Vec3(INT32_MAX, INT32_MAX, INT32_MAX);
			m_boundingBoxMax = Maths::Vec3(INT32_MIN, INT32_MIN, INT32_MIN);
		};


		void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;
		virtual ~Mesh();
		std::string GetTypeName() { return "Mesh"; }

		void Render(const class ShaderProgram& shaderProgram, const class Material& material) const;

		Texture* GenerateFileIcon() override;

		SubMesh& GetSubMesh(int index) { return m_subMeshes[index]; }
		std::vector<SubMesh>& GetSubMeshes() { return m_subMeshes; }

	private:
		std::vector<SubMesh> m_subMeshes;
		Maths::Vec3 m_boundingBoxMin, m_boundingBoxMax;

		void ProcessNode(aiNode* node, const aiScene* scene, const std::string& filepath);
		SubMesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& filepath);
		class Texture* ProcessTexture(aiMaterial* mat, aiTextureType type, const std::string& filepath);

		void GenerateMaterial(aiMaterial* mat);
	};
}

