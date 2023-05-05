#pragma once
#include "LowRenderer/Light/ILight.hpp"
#include "Resource/Texture.hpp"

#include "dllInclude.hpp"

namespace LowRenderer
{
	class PHOSENGINE_API DirectionalLight : public ILight
	{
	public:
		DirectionalLight();
		~DirectionalLight();

		void Render(const Resource::ShaderProgram& shaderProg, int number) override;
		void RenderShadowMap() override {};

		void Start() override;
		void Update() override;
		void GUIUpdate() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;

	private:
		Resource::Texture m_shadowTexture;
	};


}
