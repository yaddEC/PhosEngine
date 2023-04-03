#pragma once
#include "LowRenderer/Light/ILight.hpp"

#ifdef SPOTLIGHT_EXPORTS
#define SPOTLIGHT_API __declspec(dllexport)
#else
#define SPOTLIGHT_API __declspec(dllimport)
#endif

namespace LowRenderer
{
	class SpotLight : public ILight
	{
	public:
		SpotLight();
		~SpotLight();

		void Render(const Resource::ShaderProgram& shaderProg, int number) override;

		void Start() override;
		void Update() override;
		void GUIUpdate() override;
		void OnDestroy() override;
	private:
		float m_linearAttenuation, m_constantAttenuation, m_quadraticAttenuation;
		float m_angle;
	};

}