// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/RHI.hpp"

#include "Resource/ShaderProgram.hpp"

#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "Engine/MonoBehaviour.hpp"

#include "LowRenderer/Renderer.hpp"

#define POINTLIGHT_EXPORTS
#include "LowRenderer/Light/PointLight.hpp"

LowRenderer::PointLight::PointLight() 
{
	color = Maths::Vec3(1, 1, 1);
	linearAttenuation = 0.09f;
	constantAttenuation = 1.0f;
	quadraticAttenuation = 0.032f;
}

LowRenderer::PointLight::~PointLight() {}

void LowRenderer::PointLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{
	if (isActive)
	{
		shaderProg.SetUniformVec3("pointLights[" + std::to_string(number) + "].position", transform->position);
		shaderProg.SetUniformVec3("pointLights[" + std::to_string(number) + "].color", color);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].intensity", intensity);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].constant", constantAttenuation);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].linear", linearAttenuation);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].quadratic", quadraticAttenuation);
	}
}

void LowRenderer::PointLight::Start()
{
	gameobject->GetScene()->GetRenderer()->AddPointLight(this);
}

void LowRenderer::PointLight::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeletePointLight(this);
}

void LowRenderer::PointLight::GUIUpdate()
{

}