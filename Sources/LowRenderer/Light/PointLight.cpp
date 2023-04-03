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

#include "Wrapper/GUI.hpp"

#include "LowRenderer/Renderer.hpp"

#define POINTLIGHT_EXPORTS
#include "LowRenderer/Light/PointLight.hpp"

LowRenderer::PointLight::PointLight() 
{
	p_color = Maths::Vec3(1, 1, 1);
	m_linearAttenuation = 0.09f;
	m_constantAttenuation = 1.0f;
	m_quadraticAttenuation = 0.032f;
}

LowRenderer::PointLight::~PointLight() {}

void LowRenderer::PointLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{
	if (isActive)
	{
		shaderProg.SetUniformVec3("pointLights[" + std::to_string(number) + "].position", transform->position);
		shaderProg.SetUniformVec3("pointLights[" + std::to_string(number) + "].color", p_color);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].intensity", p_intensity);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].constant", m_constantAttenuation);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].linear", m_linearAttenuation);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].quadratic", m_quadraticAttenuation);
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
	if (Wrapper::GUI::CollapsingHeader("Spot Light"))
	{
		Wrapper::GUI::DisplayText("Color: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditColorRGB("##Color", p_color);
		Wrapper::GUI::DisplayText("Intensity: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditFloat("##Intensity", p_intensity, 0.001f, 0.f, 3.0f);
		Wrapper::GUI::DisplayText("Linear Attenuation: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditFloat("##Linear", m_linearAttenuation, 0.001f, 0.f, 1.0f);
		Wrapper::GUI::DisplayText("Quadratic Attenuation: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditFloat("##Quadratic", m_quadraticAttenuation, 0.001f, 0.f, 1.0f);
	}
}