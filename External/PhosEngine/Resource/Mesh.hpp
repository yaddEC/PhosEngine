#pragma once
#include "Resource/IResource.hpp"
#include <vector>
#include <unordered_map>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Resource/SubMesh.hpp"

#include "Armature.hpp"
#include "dllInclude.hpp"

namespace Resource
{
	struct NodeTest
	{
		std::string name;
		Maths::Vec3 position, rotation, scale;
		std::vector<NodeTest*> children;
	};

	class Material;

	class PHOSENGINE_API Mesh : public IResource
	{
	public:

		Mesh() : IResource()
		{
			m_boundingBoxMin = Maths::Vec3(FLT_MAX, FLT_MAX, FLT_MAX);
			m_boundingBoxMax = Maths::Vec3(FLT_MIN, FLT_MIN, FLT_MIN);
		};


		void Load() override;
		void Bind() override;
		void Unload() override;
		void GUIUpdate() override;
		virtual ~Mesh();
		std::string GetTypeName() { return "Mesh"; }

		void Render(const class ShaderProgram& shaderProgram, const class Material& material) const;
		void RenderShadowMap() const;

		Texture* GenerateFileIcon() override;

		SubMesh& GetSubMesh(int index) { return m_subMeshes[index]; }
		std::vector<SubMesh>& GetSubMeshes() { return m_subMeshes; }
		Armature* GetArmature() const { return m_armature; }

	private:
		std::vector<NodeTest*> nodeList; // test

		std::vector<SubMesh> m_subMeshes;
		Maths::Vec3 m_boundingBoxMin, m_boundingBoxMax;
		Armature* m_armature = nullptr;
		
		void ProcessNode(aiNode* node, const aiScene* scene, const std::string& filepath);
		SubMesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& filepath);
		SubMesh ProcessSkinnedMesh(aiMesh* mesh, const aiScene* scene, const std::string& filepath);
		void ProcessArmature(std::vector<SkinnedVertex>& vertices, aiMesh* mesh, const aiScene* scene);
		Bone* ProcessHierarchy(aiNode* node, const std::unordered_map<std::string, int>& boneMap);
		Maths::Mat4 GetStandardMatrix(const aiMatrix4x4& mat) 
		{
			Maths::Mat4 result;
			result.data4V[0] = Maths::Vec4{mat.a1, mat.a2, mat.a3, mat.a4};
			result.data4V[1] = Maths::Vec4{ mat.b1, mat.b2, mat.b3, mat.b4 };
			result.data4V[2] = Maths::Vec4{ mat.c1, mat.c2, mat.c3, mat.c4 };
			result.data4V[3] = Maths::Vec4{ mat.d1, mat.d2, mat.d3, mat.d4 };
			return result;
		}

		void GenerateMaterial(aiMaterial* mat);

		void DisplayHierarchy(Bone* node);
	};
}

