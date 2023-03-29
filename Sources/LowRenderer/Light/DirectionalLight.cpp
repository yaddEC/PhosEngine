// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include <string>

#include "Resource/ShaderProgram.hpp"
#include "Engine/MonoBehaviour.hpp"
#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "LowRenderer/Renderer.hpp"

#define DIRECTIONALLIGHT_EXPORTS
#include "LowRenderer/Light/DirectionalLight.hpp"

LowRenderer::DirectionalLight::DirectionalLight()
{
	color = Maths::Vec3(1, 1, 1);
}

LowRenderer::DirectionalLight::~DirectionalLight() {}

void LowRenderer::DirectionalLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{
	if (isActive)
	{
		shaderProg.SetUniformVec3("dirLights[" + std::to_string( number ) + "].direction", direction);
		shaderProg.SetUniformVec3("dirLights[" + std::to_string( number ) + "].color", color);
		shaderProg.SetUniformFloat("dirLights[" + std::to_string( number ) + "].intensity", intensity);
	}
}

void LowRenderer::DirectionalLight::Start() 
{
	gameobject->GetScene()->GetRenderer()->AddDirLight(this);
}

void LowRenderer::DirectionalLight::Update()
{
	direction.x = -sin(transform->rotation.y * Maths::DEG2RAD) * cos(transform->rotation.x * Maths::DEG2RAD);
	direction.y = sin(transform->rotation.x * Maths::DEG2RAD);
	direction.z = -cos(transform->rotation.x * Maths::DEG2RAD) * cos(transform->rotation.y * Maths::DEG2RAD);
}

void LowRenderer::DirectionalLight::GUIUpdate()
{

}

void LowRenderer::DirectionalLight::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeleteDirLight(this);
}
