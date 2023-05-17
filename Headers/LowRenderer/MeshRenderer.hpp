#pragma once
#include "Maths/Maths.hpp"
#include "Engine/MonoBehaviour.hpp"
#include <map>

#include "dllInclude.hpp"

namespace Resource
{
	class ShaderProgram;
	class Mesh;
	class Material;
	struct Bone;
}

namespace Engine
{
	class Transform;
	class GameObject;
}

namespace LowRenderer
{
	class PHOSENGINE_API MeshRenderer : public Engine::MonoBehaviour
	{
	public:

		MeshRenderer(Resource::Mesh* mesh = nullptr);
		virtual ~MeshRenderer();


		void Render(const Maths::Mat4& viewProj) const;
		void IdPickerRender(const Maths::Mat4& viewProj) const;

		void Start() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;

		void SetMesh(Resource::Mesh* _mesh) { m_mesh = _mesh; }
		Resource::Mesh* GetMesh() { return m_mesh; }

		void SetMaterial(Resource::Material* _material) { m_material = _material; }
		Resource::Material* GetMaterial() { return m_material; }

		void SetSkinningMatrices();
	private:


		Engine::GameObject* GenerateBonesObject(const Resource::Bone& bone);
		void AssignBoneObject(Engine::Transform* go);

		// must keep empty if no animation
		std::vector<Maths::Mat4> m_animatedBoneMatrices;
		std::vector<Engine::Transform*> m_boneObjectList;

		Resource::Mesh* m_mesh = nullptr;
		Resource::Material* m_material = nullptr;

	};
}


