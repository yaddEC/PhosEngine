#pragma once
#include "Engine/MonoBehaviour.hpp"
#include "Maths/Maths.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class ShaderProgram;
}
namespace LowRenderer
{
	class PHOSENGINE_API ILight : public Engine::MonoBehaviour
	{
	public:
		ILight();

		virtual void Render(const Resource::ShaderProgram& shaderProg, int number) = 0;


	protected:
		Maths::Vec3 p_color ;
		float p_intensity = 1;
		Maths::Vec3 p_direction;
	};
}