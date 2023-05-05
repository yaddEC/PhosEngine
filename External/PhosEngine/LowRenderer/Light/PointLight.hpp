#pragma once
#include "LowRenderer/Light/ILight.hpp"
#include "Resource/CubeMap.hpp"

#include "dllInclude.hpp"



namespace LowRenderer
{
	class PHOSENGINE_API PointLight : public ILight
	{
	public:
		PointLight();
		~PointLight();

		void Render(const Resource::ShaderProgram& shaderProg, int number) override;
		void RenderShadowMap() override {};


		void Start() override;
		void Update() override {};
		void GUIUpdate() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;
	private:
		float m_linearAttenuation, m_quadraticAttenuation;
		Resource::CubeMap m_shadowCubeMap;

	};
}