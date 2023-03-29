// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/ShaderProgram.hpp"

#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "Engine/MonoBehaviour.hpp"

#include "LowRenderer/Renderer.hpp"

#define SPOTLIGHT_EXPORTS
#include "LowRenderer/Light/SpotLight.hpp"


LowRenderer::SpotLight::SpotLight() 
{
	color = Maths::Vec3(1);
	linearAttenuation = 0.09f;
	constantAttenuation = 1.0f;
	quadraticAttenuation = 0.032f;
	angle = 12.f;
}

LowRenderer::SpotLight::~SpotLight() 
{}

void LowRenderer::SpotLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{
	if (isActive)
	{
		shaderProg.SetUniformVec3("spotLights[" + std::to_string(number) + "].position", transform->position);
		shaderProg.SetUniformVec3("spotLights[" + std::to_string(number) + "].direction", direction);

		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].cutoff", cosf(angle * Maths::DEG2RAD));
		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].outerCutoff", cosf(angle * 1.4 * Maths::DEG2RAD));

		shaderProg.SetUniformVec3("spotLights[" + std::to_string(number) + "].color", color);
		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].intensity", intensity);

		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].constant", constantAttenuation);
		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].linear", linearAttenuation);
		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].quadratic", quadraticAttenuation);
	}
}

void LowRenderer::SpotLight::Start()
{
	gameobject->GetScene()->GetRenderer()->AddSpotLight(this);
}

void LowRenderer::SpotLight::Update()
{
	direction.x = -sin(transform->rotation.y * Maths::DEG2RAD) * cos(transform->rotation.x * Maths::DEG2RAD);
	direction.y = sin(transform->rotation.x * Maths::DEG2RAD);
	direction.z = -cos(transform->rotation.x * Maths::DEG2RAD) * cos(transform->rotation.y * Maths::DEG2RAD);
}


void LowRenderer::SpotLight::GUIUpdate()
{

}

void LowRenderer::SpotLight::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeleteSpotLight(this);
}
