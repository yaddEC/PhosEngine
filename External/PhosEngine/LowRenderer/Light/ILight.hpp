#pragma once
#include "Engine/MonoBehaviour.hpp"
#include "Maths/Maths.hpp"

#ifdef LIGHT_EXPORTS
#define LIGHT_API __declspec(dllexport)
#else
#define LIGHT_API __declspec(dllimport)
#endif

namespace Resource
{
	class ShaderProgram;
}
namespace LowRenderer
{
	class LIGHT_API ILight : public Engine::MonoBehaviour
	{
	public:
		ILight();
		ILight(Maths::Vec3 _color, float _intensity);

		virtual void Render(const Resource::ShaderProgram& shaderProg, int number) = 0;
	protected:
		Maths::Vec3 color ;
		float intensity = 1;
		Maths::Vec3 direction;
	};
}