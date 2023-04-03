#pragma once
#include "LowRenderer/Light/ILight.hpp"

#ifdef DIRECTIONALLIGHT_EXPORTS
#define DIRECTIONALLIGHT_API __declspec(dllexport)
#else
#define DIRECTIONALLIGHT_API __declspec(dllimport)
#endif

namespace LowRenderer
{
	class DIRECTIONALLIGHT_API DirectionalLight : public ILight
	{
	public:
		DirectionalLight();
		~DirectionalLight();

		void Render(const Resource::ShaderProgram& shaderProg, int number) override;

		void Start() override;
		void Update() override;
		void GUIUpdate() override;
		void OnDestroy() override;

	private:

	};


}
