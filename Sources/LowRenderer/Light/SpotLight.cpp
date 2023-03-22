// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Engine/Transform.hpp"

#define SPOTLIGHT_EXPORTS
#include "LowRenderer/Light/SpotLight.hpp"


LowRenderer::SpotLight::SpotLight() {}

LowRenderer::SpotLight::~SpotLight() {}

void LowRenderer::SpotLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{

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