#pragma once
#include "Maths/Maths.hpp"
#include "Engine/MonoBehaviour.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class ShaderProgram;
	class Mesh;
	class Material;
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
		void Update() override;
		void OnTriggerEnter(Engine::GameObject* go) override {};
		void OnTriggerStay(Engine::GameObject* go) override {};
		void OnTriggerExit(Engine::GameObject* go) override {};
		void OnCollisionEnter(Engine::GameObject* go) override {};
		void OnCollisionStay(Engine::GameObject* go) override {};
		void OnCollisionExit(Engine::GameObject* go) override {};
		void GUIUpdate() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;

		void SetMesh(Resource::Mesh* _mesh) { m_mesh = _mesh; }
		Resource::Mesh* GetMesh() { return m_mesh; }

		void SetMaterial(Resource::Material* _material) { m_material = _material; }
		Resource::Material* GetMaterial() { return m_material; }

		

	private:

		Resource::Mesh* m_mesh = nullptr;
		Resource::Material* m_material = nullptr;

	};
}


