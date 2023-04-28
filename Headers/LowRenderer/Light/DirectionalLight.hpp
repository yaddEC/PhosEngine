#pragma once
#include "LowRenderer/Light/ILight.hpp"

#include "dllInclude.hpp"

namespace LowRenderer
{
	class PHOSENGINE_API DirectionalLight : public ILight
	{
	public:
		DirectionalLight();
		~DirectionalLight();

		void Render(const Resource::ShaderProgram& shaderProg, int number) override;

		void Start() override;
		void Update() override;
		void OnTriggerEnter(Engine::GameObject* go)   override {};
		void OnTriggerStay(Engine::GameObject* go)  override {};
		void OnTriggerExit(Engine::GameObject* go)  override {};
		void OnCollisionEnter(Engine::GameObject* go)  override {};
		void OnCollisionStay(Engine::GameObject* go)  override {};
		void OnCollisionExit(Engine::GameObject* go)  override {};
		void GUIUpdate() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;

	private:

	};


}