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

#include "Wrapper/GUI.hpp"

#include "LowRenderer/Renderer.hpp"

#define DIRECTIONALLIGHT_EXPORTS
#include "LowRenderer/Light/DirectionalLight.hpp"

LowRenderer::DirectionalLight::DirectionalLight()
	: ILight()
{
	p_color = Maths::Vec3(1, 1, 1);
}

LowRenderer::DirectionalLight::~DirectionalLight() {}

void LowRenderer::DirectionalLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{
	if (isActive)
	{
		shaderProg.SetUniformVec3("dirLights[" + std::to_string( number ) + "].direction", p_direction);
		shaderProg.SetUniformVec3("dirLights[" + std::to_string( number ) + "].color", p_color);
		shaderProg.SetUniformFloat("dirLights[" + std::to_string( number ) + "].intensity", p_intensity);
	}
}

void LowRenderer::DirectionalLight::Start() 
{
	gameobject->GetScene()->GetRenderer()->AddDirLight(this);
}

void LowRenderer::DirectionalLight::Update()
{
	p_direction = (gameobject->transform->GetGlobalMatrix() * Maths::Vec4(0, -1, 0, 0)).xyz();
}

void LowRenderer::DirectionalLight::GUIUpdate()
{
	if (Wrapper::GUI::CollapsingHeader("Directionnal Light"))
	{
		Wrapper::GUI::DisplayText("Color: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditColorRGB("##Color", p_color);
		Wrapper::GUI::DisplayText("Intensity: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditFloat("##Intensity", p_intensity, 0.001f, 0.f, 3.0f);
	}
}

void LowRenderer::DirectionalLight::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeleteDirLight(this);
}
