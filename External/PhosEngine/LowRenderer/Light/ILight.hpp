#pragma once
#include "Engine/MonoBehaviour.hpp"
#include "Maths/Maths.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class ShaderProgram;
}

namespace Engine
{
	class GameObject;
}
namespace LowRenderer
{
	class FrameBuffer;
	class PHOSENGINE_API ILight : public Engine::MonoBehaviour
	{
	public:
		ILight();

		virtual void Render(const Resource::ShaderProgram& shaderProg, int number) = 0;
		virtual void RenderShadowMap() = 0;
		FrameBuffer* GetFrameBuffer() const { return p_shadowFrame; }
	protected:
		FrameBuffer* p_shadowFrame;
		Maths::Vec3 p_color ;
		float p_intensity = 1;
		Maths::Vec3 p_direction;
		bool p_useShadow;
	};
}