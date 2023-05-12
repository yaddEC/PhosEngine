#pragma once
#include "LowRenderer/Light/ILight.hpp"
#include "Resource/Texture.hpp"

#include "dllInclude.hpp"

namespace LowRenderer
{
	class PHOSENGINE_API SpotLight : public ILight
	{
	public:
		SpotLight();
		~SpotLight();

		void Render(const Resource::ShaderProgram& shaderProg, int number) override;
		void RenderShadowMap() override;

		void Start() override;
		void Update() override;
		void GUIUpdate() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;

		Maths::Mat4 GetVP() const { return m_VP; }
	private:
		float m_linearAttenuation, m_constantAttenuation, m_quadraticAttenuation;
		float m_angle;
		Resource::Texture* m_shadowTexture;
		Maths::Mat4 m_VP;
	};

}