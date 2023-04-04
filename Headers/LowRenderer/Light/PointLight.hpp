#pragma once
#include "LowRenderer/Light/ILight.hpp"

#ifdef POINTLIGHT_EXPORTS
#define POINTLIGHT_API __declspec(dllexport)
#else
#define POINTLIGHT_API __declspec(dllimport)
#endif

namespace LowRenderer
{
	class POINTLIGHT_API PointLight : public ILight
	{
	public:
		PointLight();
		~PointLight();

		void Render(const Resource::ShaderProgram& shaderProg, int number) override;

		void Start() override;
		void Update() override {};
		void GUIUpdate() override;
		void OnDestroy() override;
	private:
		float m_linearAttenuation, m_constantAttenuation, m_quadraticAttenuation;

	};
}