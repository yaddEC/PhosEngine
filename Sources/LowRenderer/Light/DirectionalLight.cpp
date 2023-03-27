// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <string>

#include "Resource/ShaderProgram.hpp"
#include "Engine/Transform.hpp"

#define DIRECTIONALLIGHT_EXPORTS
#include "LowRenderer/Light/DirectionalLight.hpp"

LowRenderer::DirectionalLight::DirectionalLight() {}

LowRenderer::DirectionalLight::~DirectionalLight() {}

void LowRenderer::DirectionalLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{
	if (isActive)
	{
		shaderProg.SetUniformVec3("dirLights[" + std::to_string( number ) + "].direction", direction);
		//shaderProg.SetUniformVec3("dirLights[" + std::to_string( number ) + "].diffuse", light->diffuseColor * 0.5f);
		//shaderProg.SetUniformVec3("dirLights[" + std::to_string( number ) + "].specular", light->specularColor);
	}
}

void LowRenderer::DirectionalLight::Start() {}

void LowRenderer::DirectionalLight::Update()
{
	direction.x = -sin(transform->rotation.y * Maths::DEG2RAD) * cos(transform->rotation.x * Maths::DEG2RAD);
	direction.y = sin(transform->rotation.x * Maths::DEG2RAD);
	direction.z = -cos(transform->rotation.x * Maths::DEG2RAD) * cos(transform->rotation.y * Maths::DEG2RAD);
}

void LowRenderer::DirectionalLight::GUIUpdate()
{

}